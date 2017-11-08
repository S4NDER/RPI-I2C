#pragma once
#include "restclient-cpp/restclient.h"
#include <cstdio>
#include <iostream>

namespace RPI_I2C{

  class Thumper{
  public:
      Thumper(void);
  public:
      void drive_forward(void);
      void drive_backward(void);
      void drive_left(void);
      void drive_right(void);
      void set_address(std::string address);

  private:
      std::string address;
      std::string post_drive;
  };
};
