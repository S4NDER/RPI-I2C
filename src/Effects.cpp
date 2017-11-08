#include "Effects.h"

namespace RPI_I2C{

    void Effects::cycle_RGB(Led led){
        int red =0;
        int green =0;
        int blue = 0;
        while (true) {

            for (red = 0; red <= 255; red++) {
                for (int i = 0; i < 5; i++) {
                    led.setLedColor(Color(red, green, blue));
                }
                if(red == 255){
                    red = 255;
                }
            }

            for (green = 0; green <= 255; green++) {
                red--;
                for (int i = 0; i < 5; i++) {
                    led.setLedColor(Color(red, green, blue));
                }

                if(green == 255){
                    green = 255;
                }
            }

            for (blue = 0; blue <= 255; blue++) {
                green --;
                for (int i = 0; i < 5; i++) {
                    led.setLedColor(Color(red, green, blue));
                }
            }

            for (int i = 0; i < 255; i++) {
                blue--;
                red++;
                for (int i = 0; i < 5; i++) {
                    led.setLedColor(Color(red, green, blue));
                }
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
