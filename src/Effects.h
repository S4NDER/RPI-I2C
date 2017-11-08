#pragma once
#include "Led.h"
#include "TLC59116.h"


namespace RPI_I2C{

  class Effects{

    public:
        void cycle_RGB(Led ledArray[], TLC59116 * tlc59116);
        void running_light(void);
        void blink_light(void);
        void glow_light(void);
  };
};
