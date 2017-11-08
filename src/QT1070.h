#pragma once
#include "I2C.h"

namespace RPI_I2C{
    
    class QT1070{
        public:
            QT1070();
            enum Keypads {
                UP      = 4,
                DOWN    = 8,
                LEFT    = 1,
                RIGHT   = 2,
                X       = 64,
                A       = 32,
                B       = 16
            };

        public:
            void calibrate ();
            void reset();
            enum Keypads getKeyPAD();
            int getVendor();



        private:
            int giveKey();
            I2C i2c;
            char buffer[];
    };
};
