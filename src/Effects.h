#pragma once
#include "Led.h"
#include "TLC59116.h"

#include <vector>


namespace RPI_I2C{

  class Effects{

    public:
        void cycle_RGB(std::vector<Led>& ledArray, TLC59116 * tlc59116);
        void running_light(std::vector<Led>& ledArray, TLC59116 * tlc59116);
        void blink_light(std::vector<Led>& ledArray, TLC59116 * tlc59116);
        void glow_light(std::vector<Led>& ledArray, TLC59116 * tlc59116);

    
  };
};
