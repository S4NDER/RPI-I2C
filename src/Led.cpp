#include "Led.h"

namespace RPI_I2C{

    Led::Led(void){
        this->red = 0;
        this->green = 0;
        this->blue = 0;
    }

    void Led::setLedColor(Color color){
        this->red = color.getRed();
        this->green = color.getGreen();
        this->blue = color.getBlue();
    }

    int Led::getRed(){
        return this->red;
    }

    int Led::getGreen(){
        return this->green;
    }

    int Led::getBlue(){
        return this->blue;
    }
};
