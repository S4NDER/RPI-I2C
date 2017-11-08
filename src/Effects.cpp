#include "Effects.h"

namespace RPI_I2C{

    void Effects::next_effect(){
        if (effects_type < effects_count){
            this->effects_type++;
        } else {
            this->effects_type = 0;
        }
    }

    void Effects::keepAlive(){
        switch ((int)this->effects_type) {
            case 0: cycle_RGB(); break;
            case 1: running_light_left(); break;
            case 2: running_light_right();break;
            case 3: running_left_and_right(); break;
            case 4: blink_light(); break;
            case 5: glow_light(); break;
            case 6: running_from_center(); break;
        }
    }

    void Effects::set_effects_led_array(std::vector<Led> * ledArray){
        effects_led_array = *ledArray;
    }

    void Effects::set_effects_controller(TLC59116 * tlc59116){
        effects_controller = *tlc59116;
    }

    void Effects::cycle_RGB(void){
        int red =0;
        int green =0;
        int blue = 0;

        for (red = 0; red <= 255; red++) {
            for (int i = 0; i < effects_led_array.size(); i++) {
                effects_led_array[i].setLedColor(Color(red, green, blue));
                effects_controller.turn_on_led_number_x(i+1, effects_led_array[i]);
            }
            if(red == 255){
                red = 255;
            }
        }

        for (green = 0; green <= 255; green++) {
            red--;
            for (int i = 0; i < effects_led_array.size(); i++) {
                effects_led_array[i].setLedColor(Color(red, green, blue));
                effects_controller.turn_on_led_number_x(i+1, effects_led_array[i]);
            }

            if(green == 255){
                green = 255;
            }
        }

        for (blue = 0; blue <= 255; blue++) {
            green --;
            for (int i = 0; i < effects_led_array.size(); i++) {
                effects_led_array[i].setLedColor(Color(red, green, blue));
                effects_controller.turn_on_led_number_x(i+1, effects_led_array[i]);
            }
        }

        for (int i = 0; i < 255; i++) {
            blue--;
            red++;
            for (int i = 0; i < effects_led_array.size(); i++) {
                effects_led_array[i].setLedColor(Color(red, green, blue));
                effects_controller.turn_on_led_number_x(i+1, effects_led_array[i]);
            }
        }
    }

    void Effects::running_light_left(void){
        int intensity = 255;
        for (int i = 0; i < effects_led_array.size(); i++) {
            effects_led_array[i].setLedColor(Color(intensity, intensity, intensity));
            effects_controller.turn_on_led_number_x(i+1, effects_led_array[i]);
            usleep(running_light_speed);
            effects_controller.turn_off_led_number_x(i+1);
        }
    }

    void Effects::running_light_right(void){
        int intensity = 255;
        for (int i = effects_led_array.size(); i >= 0; i--) {
            effects_led_array[i].setLedColor(Color(intensity, intensity, intensity));
            effects_controller.turn_on_led_number_x(i+1, effects_led_array[i]);
            usleep(running_light_speed);
            effects_controller.turn_off_led_number_x(i+1);
        }
    }

    void Effects::running_left_and_right(void){
        int intensity = 255;

        for (int i = effects_led_array.size()/2; i >= 0; i--) {
            effects_led_array[i].setLedColor(Color(intensity, intensity, intensity));
            effects_controller.turn_on_led_number_x(i+1, effects_led_array[i]);
            usleep(running_light_speed);
            effects_controller.turn_off_led_number_x(i+1);
        }

        for (int i = effects_led_array.size()/2; i < effects_led_array.size(); i++) {
            effects_led_array[i].setLedColor(Color(intensity, intensity, intensity));
            effects_controller.turn_on_led_number_x(i+1, effects_led_array[i]);
            usleep(running_light_speed);
            effects_controller.turn_off_led_number_x(i+1);
        }
    }

    void Effects::blink_light(void){
        int intensity = 0;
        for (int i = 0; i < effects_led_array.size(); i++) {
            effects_led_array[i].setLedColor(Color(intensity, intensity, intensity));
            effects_controller.turn_on_led_number_x(i+1, effects_led_array[i]);
        }

        usleep (running_light_speed);

        intensity = 255;
        for (int i = 0; i < effects_led_array.size(); i++) {
            effects_led_array[i].setLedColor(Color(intensity, intensity, intensity));
            effects_controller.turn_on_led_number_x(i+1, effects_led_array[i]);
        }

        usleep (running_light_speed);


    }

    void Effects::glow_light(void){
        int intensity = 0;
        for (intensity = 0; intensity <= 255; intensity++) {
            for (int i = 0; i < effects_led_array.size(); i++) {
                effects_led_array[i].setLedColor(Color(intensity, intensity, intensity));
                effects_controller.turn_on_led_number_x(i+1, effects_led_array[i]);
            }
            if (intensity == 255){ intensity = 255; }
        }

        for (intensity = 255; intensity >= 0; intensity--) {
            for (int i = 0; i < effects_led_array.size(); i++) {
                effects_led_array[i].setLedColor(Color(intensity, intensity, intensity));
                effects_controller.turn_on_led_number_x(i+1, effects_led_array[i]);
            }
        }
    }

    void Effects::running_from_center(void){
        int intensity = 255;

        for (int i = 0; i < effects_led_array.size() ; i++) {
            effects_led_array[i].setLedColor(Color(intensity, intensity, intensity));
        }

        effects_controller.turn_on_led_number_x(3, effects_led_array[3]);
        usleep(running_light_speed/2);
        effects_controller.turn_off_led_number_x(3);

        effects_controller.turn_on_led_number_x(2, effects_led_array[2]);
        usleep(running_light_speed/5);
        effects_controller.turn_off_led_number_x(2);

        effects_controller.turn_on_led_number_x(4, effects_led_array[4]);
        usleep(running_light_speed/5);
        effects_controller.turn_off_led_number_x(4);

        effects_controller.turn_on_led_number_x(1, effects_led_array[1]);
        usleep(running_light_speed/5);
        effects_controller.turn_off_led_number_x(1);

        effects_controller.turn_on_led_number_x(5, effects_led_array[0]);
        usleep(running_light_speed/5);
        effects_controller.turn_off_led_number_x(5);
        /*

        effects_controller.turn_on_led_number_x(2, effects_led_array[1]);
        usleep(1000000);
        effects_controller.turn_off_led_number_x(2);

        effects_controller.turn_on_led_number_x(4, effects_led_array[3]);
        usleep(1000000);
        effects_controller.turn_off_led_number_x(4);

        effects_controller.turn_on_led_number_x(1, effects_led_array[0]);
        usleep(1000000);
        effects_controller.turn_off_led_number_x(1);

        effects_controller.turn_on_led_number_x(5, effects_led_array[4]);
        usleep(1000000);
        effects_controller.turn_off_led_number_x(5);*/

    }
};
