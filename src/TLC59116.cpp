#include "TLC59116.h"
#include <cstdio>
#include <iostream>

namespace RPI_I2C{
    TLC59116::TLC59116(){
        std::string i2c_dev = "/dev/i2c-1";
        i2c.open_I2C(0x60, i2c_dev);
        usleep(5000);   //Sleep 5ms
        reset_leds();
        operate_normal_mode();
        enable_all_leds();
    }

    void TLC59116::operate_normal_mode(){
        buffer[0] = 0x00;
        buffer[1] = 0x80;
        i2c.write_I2C(2, buffer);
        usleep(5000);
    }

    void TLC59116::enable_all_leds(){
        for (size_t i = 0; i < 4; i++) {
            buffer[0] = 0x14+i;
            buffer[1] = 0xAA;
            i2c.write_I2C(2, buffer);
        }
    }

    void TLC59116::reset_leds(){
        for (size_t i = 0; i < 15; i++) {
            buffer[0] = 0x02+i;
            buffer[1] = LED_OFF;
            i2c.write_I2C(2, buffer);
        }
    }

    void TLC59116::turn_on_all_leds(){
        for (size_t i = 0; i < 15; i++) {
            buffer[0] = 0x02+i;
            buffer[1] = LED_ON_PWM;
            i2c.write_I2C(2, buffer);
        }
    }

    void TLC59116::turn_on_led_number_x(int led_id, Led led){
            led_id -= 1;

            buffer[0] = 0x02 + led_id * 3;
            buffer[1] = led.getRed();
            i2c.write_I2C(2, buffer);

            buffer[0] = 0x03 + led_id * 3;
            buffer[1] = led.getGreen();
            i2c.write_I2C(2, buffer);

            buffer[0] = 0x04 + led_id * 3;
            buffer[1] = led.getBlue();
            i2c.write_I2C(2, buffer);
    }

    void TLC59116::turn_of_led_number_x(int led_id){
            led_id -= 1;

            buffer[0] = 0x02 + led_id * 3;
            buffer[1] = LED_OFF;
            i2c.write_I2C(2, buffer);

            buffer[0] = 0x03 + led_id * 3;
            buffer[1] = LED_OFF;
            i2c.write_I2C(2, buffer);

            buffer[0] = 0x04 + led_id * 3;
            buffer[1] = LED_OFF;
            i2c.write_I2C(2, buffer);
    }
};
