#pragma once
#include "Led.h"
#include "TLC59116.h"

#include <vector>


namespace RPI_I2C{

  class Effects{

    public:

        void next_effect(void);
        void keepAlive(void);

        void set_effects_controller(TLC59116 * tlc59116);
        void set_effects_led_array(std::vector<Led> * ledArray);
        double effects_type = 0;    //Needs to be public or it fail to write to the I2C bus, very strange
        double effects_count = 6; // starting from 0
        double running_light_speed = 150000;

    private:
        TLC59116 effects_controller;
        std::vector<Led> effects_led_array;
        void cycle_RGB();
        void running_light_left();
        void running_light_right();
        void running_left_and_right();
        void running_from_center();
        void blink_light();
        void glow_light();
  };
};
