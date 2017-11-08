#pragma once
#include "Color.h"

namespace RPI_I2C{

    class Led{
        public:
            Led(void);

        public:
            void setLedColor(Color color);

            int getRed(void);
            int getGreen(void);
            int getBlue(void);

        private:
            int red;
            int green;
            int blue;
    };
};
