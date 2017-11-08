#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <thread>

#include "lib/I2C.h"
#include "lib/QT1070.h"
#include "lib/TLC59116.h"
#include "lib/Led.h"
#include "lib/Effects.h"

using namespace RPI_I2C;

Led ledArray[5];
I2C i2c;
TLC59116 tlc59116;
QT1070 qt1070;

volatile bool keepFading = false;
volatile bool keepReadingKey = false;

void cycleRGB(){
    int red =0;
    int green =0;
    int blue = 0;
    while (keepFading) {

        if (keepFading == false) {
            std::cout << "keepfading is false" << '\n';
            break;
        }

        for (red = 0; red <= 255; red++) {
            for (size_t i = 0; i < 5; i++) {
                ledArray[i].setLedColor(Color(red, green, blue));
                tlc59116.turn_on_led_number_x(i+1, ledArray[i]);
            }
            if(red == 255){
                red = 255;
            }
        }

        for (green = 0; green <= 255; green++) {
            red--;
            for (size_t i = 0; i < 5; i++) {
                ledArray[i].setLedColor(Color(red, green, blue));
                tlc59116.turn_on_led_number_x(i+1, ledArray[i]);
            }

            if(green == 255){
                green = 255;
            }
        }

        for (blue = 0; blue <= 255; blue++) {
            green --;
            for (size_t i = 0; i < 5; i++) {
                ledArray[i].setLedColor(Color(red, green, blue));
                tlc59116.turn_on_led_number_x(i+1, ledArray[i]);
            }
        }

        for (size_t i = 0; i < 255; i++) {
            blue--;
            red++;
            for (size_t i = 0; i < 5; i++) {
                ledArray[i].setLedColor(Color(red, green, blue));
                tlc59116.turn_on_led_number_x(i+1, ledArray[i]);
            }
        }
    }
}

void read_keys(){
    std::string previous_key_state=" ";
    std::string current_key_state = " ";
    while (keepReadingKey) {
        current_key_state = qt1070.getKeyPAD();
        if(current_key_state != " "){
            if (current_key_state != previous_key_state) {
                std::cout << current_key_state << '\n';
            }
        }
        previous_key_state = current_key_state;
    }
}

int main (void){

    tlc59116.turn_on_all_leds();
    usleep(500000);
    tlc59116.reset_leds();

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

    keepFading = true;
    keepReadingKey = true;

    std::thread thread1(cycleRGB);
    std::thread thread2(read_keys);

    usleep(10000000);

    keepFading = false;
    keepReadingKey = false;

    thread1.join();
    thread2.join();

    return 0;
}
