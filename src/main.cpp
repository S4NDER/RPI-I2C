#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <thread>
#include <vector>

#include "I2C.h"
#include "QT1070.h"
#include "TLC59116.h"
#include "Led.h"
#include "Effects.h"
#include "Thumper.h"

using namespace RPI_I2C;

int touchDelay = 250000;    //The delay for the toggle buttons A and B
int led_count = 5;

std::vector<Led> ledArray;
I2C i2c;
TLC59116 tlc59116;
QT1070 qt1070;
Effects effects;
//int effect_type = 0;
Thumper thumper;

volatile bool keepFading = false;
volatile bool keepReadingKey = false;
volatile bool keepAlive = false;


void effects_manager(){
    while (keepAlive) {
        if (!keepAlive) {
            break;
        }
        while (keepFading) {
            if (!keepAlive) {
                break;
            }
            effects.keepAlive();

        }
    }
}

void read_keys(){
    while (keepReadingKey) {
        int current_key_state = qt1070.getKeyPAD();

            switch (current_key_state) {
                case QT1070::UP : thumper.drive_forward(); break;
                case QT1070::DOWN : thumper.drive_backward(); break;
                case QT1070::LEFT : thumper.drive_left(); break;
                case QT1070::RIGHT : thumper.drive_right(); break;
                case QT1070::X :    for (int i = 0; i < 5; i++) {
                                        thumper.stop();
                                        usleep(20000);
                                    }
                                    keepAlive = false;
                                    keepReadingKey = false;

                                    break;
                case QT1070::A :    keepFading = !keepFading;
                                    usleep(touchDelay);
                                    std::cout << keepFading << '\n';
                                    break;
                case QT1070::B :    usleep(touchDelay);
                                    effects.next_effect();
                                    std::cout << "next effect" << '\n';
                break;
            }
        }
}

int main (void){

    tlc59116.turn_on_all_leds();
    usleep(500000);
    tlc59116.reset_leds();

    for (int i = 0; i < led_count; i++) {
        ledArray.push_back(Led());
    }
    std::string thumperAddress;
    std::cout << "Enter the IP address of the thumper without the port or http, only the address" << std::endl;
    std::cin >> thumperAddress;
    thumper.set_address("http://" + thumperAddress + ":3000/");
    effects.set_effects_controller(&tlc59116);
    effects.set_effects_led_array(&ledArray);
    keepReadingKey = true;
    keepAlive = true;

    std::thread thread1(effects_manager);
    std::thread thread2(read_keys);

    thread1.join();
    thread2.join();

    return 0;
}
