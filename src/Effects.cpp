#include "Effects.h"

namespace RPI_I2C{

    void Effects::cycle_RGB(Led ledArray[], TLC59116 * tlc59116){
        int red =0;
        int green =0;
        int blue = 0;

        for (red = 0; red <= 255; red++) {
            for (int i = 0; i < 5; i++) {
                ledArray[i].setLedColor(Color(red, green, blue));
                tlc59116->turn_on_led_number_x(i+1, ledArray[i]);
            }
            if(red == 255){
                red = 255;
            }
        }

        for (green = 0; green <= 255; green++) {
            red--;
            for (int i = 0; i < 5; i++) {
                ledArray[i].setLedColor(Color(red, green, blue));
                tlc59116->turn_on_led_number_x(i+1, ledArray[i]);
            }

            if(green == 255){
                green = 255;
            }
        }

        for (blue = 0; blue <= 255; blue++) {
            green --;
            for (int i = 0; i < 5; i++) {
                ledArray[i].setLedColor(Color(red, green, blue));
                tlc59116->turn_on_led_number_x(i+1, ledArray[i]);
            }
        }

        for (int i = 0; i < 255; i++) {
            blue--;
            red++;
            for (int i = 0; i < 5; i++) {
                ledArray[i].setLedColor(Color(red, green, blue));
                tlc59116->turn_on_led_number_x(i+1, ledArray[i]);
            }
        }

}

void Effects::running_light(void){

}

void Effects::blink_light(void){

}

void Effects::glow_light(void){

}
};
