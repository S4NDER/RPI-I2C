#pragma once
#include "I2C.h"
#include "Led.h"

namespace RPI_I2C{

    enum LEDSTATES{
        LED_OFF = 00,
        LED_ON = 01,
        LED_ON_PWM = 10,
        LED_PWM_GROUP = 11
    };

  class TLC59116{
    public:
        TLC59116 (void);

    public:
        void enable_all_leds(void);
        void reset_leds(void);
        void turn_on_all_leds(void);
        void turn_on_led_number_x(int led_id, Led led);
        void turn_of_led_number_x(int led_id);

    private:
        I2C i2c;
        char buffer[2];
        void operate_normal_mode(void);

  };
};
