#include "QT1070.h"
#include <cstdio>
#include <iostream>
#include <unistd.h>


namespace RPI_I2C{

    QT1070::QT1070(){
        buffer[2];
        std::string i2c_dev = "/dev/i2c-1";
        i2c.open_I2C(0x1B, i2c_dev);
        usleep(5000);   //Sleep 5ms
    }

    void QT1070::calibrate (){

    }

    void QT1070::reset(){

    }

    int QT1070::getVendor(){
        buffer[2];
        i2c.read_I2C(1, buffer );
        std::cout << (int) buffer[0] << '\n';
    }

    std::string QT1070::getKeyPAD(){
        int key = giveKey();
        switch (key) {
            case UP: return "UP";
            case DOWN: return "DOWN";
            case LEFT: return "LEFT";
            case RIGHT: return "RIGHT";
            case X: return "X";
            case A: return "A";
            case B: return "B";
            default: return " ";
        }
    }

    int QT1070::giveKey(){
        buffer[0] = 3;
        usleep(5000);   //Sleep 5ms
        i2c.write_I2C(1, buffer);

        usleep(5000);   //Sleep 5ms
        i2c.read_I2C(1, buffer);

        return (int)buffer[0];
    }

};
