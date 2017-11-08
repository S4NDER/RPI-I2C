#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <thread>

#include "I2C.h"
#include "QT1070.h"
#include "TLC59116.h"
#include "Led.h"
#include "Effects.h"
#include "Thumper.h"

using namespace RPI_I2C;

Led ledArray[5];
I2C i2c;
TLC59116 tlc59116;
QT1070 qt1070;
Effects effects;
Thumper thumper;

volatile bool keepFading = false;
volatile bool keepReadingKey = false;
volatile bool keepAlive = false;


void cycleRGB(){
    while (keepAlive) {
        if (!keepAlive) {
            break;
        }
        while (keepFading) {
            if (!keepAlive) {
                break;
            }
            effects.cycle_RGB(ledArray, &tlc59116);
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
                case QT1070::X :    keepReadingKey = false;
                                    keepAlive = false;
                                    break;
                case QT1070::A :    keepFading = !keepFading;
                                    usleep(150000);
                                    std::cout << keepFading << '\n';
                                    break;
            }
        }
}

int main (void){

    tlc59116.turn_on_all_leds();
    usleep(500000);
    tlc59116.reset_leds();

    thumper.set_address("http://192.168.1.103:3000/");
    keepReadingKey = true;
    keepAlive = true;

    std::thread thread1(cycleRGB);
    std::thread thread2(read_keys);
/*
    for (size_t i = 0; i < 5; i++) {
        ledArray[i] = Led();
    }


    ledArray[0].setLedColor(Color(Color::RED));
    ledArray[1].setLedColor(Color(Color::GREEN));
    ledArray[2].setLedColor(Color(Color::BLUE));
    ledArray[3].setLedColor(Color(Color::WHITE));
    ledArray[4].setLedColor(Color(Color::MAGENTA));

    for (size_t i = 0; i < 5; i++) {
        tlc59116.turn_on_led_number_x(i+1, ledArray[i]);
        usleep(300000);
        tlc59116.turn_of_led_number_x(i+1);
    }
    */
    thread1.join();
    thread2.join();

    return 0;
}
