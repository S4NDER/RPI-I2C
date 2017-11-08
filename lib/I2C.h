#pragma once

#include <cstdio>
#include <iostream>

#include <unistd.h>         //Needed for I2C port
#include <fcntl.h>			//Needed for I2C port
#include <sys/ioctl.h>	    //Needed for I2C port
#include <linux/i2c-dev.h>  //Needed for I2C port

namespace RPI_I2C{

    class I2C{
    private:
        int file_i2c;
        int length;

    public:
        I2C();

    public:
        void open_I2C (int i2c_addr, std::string i2c_dev);
        bool read_I2C (int nr_of_bytes_to_read, char buffer[]);
        void write_I2C(int nr_of_bytes_to_write, char buffer[]);
    };
};
