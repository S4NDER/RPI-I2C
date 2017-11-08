#pragma once
#include "Led.h"


namespace RPI_I2C{

  class Effects{

    public:
        void cycle_RGB(Led led);
        void running_light(void);
        void blink_light(void);
        void glow_light(void);

  };
};
