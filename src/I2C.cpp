#include "I2C.h"

namespace RPI_I2C{
    I2C::I2C(){

    }

    void I2C::open_I2C(int i2c_addr, std::string i2c_dev ){
        //----- OPEN THE I2C BUS -----
        if ((file_i2c = open(i2c_dev.c_str(), O_RDWR)) < 0)
        {
            //ERROR HANDLING: you can check errno to see what went wrong
            std::cout << "Failed to open the i2c bus" << '\n';
            return;
        } else{
            std::cout << "Succeeded to open the i2c bus" << '\n';;
        }

        if (ioctl(file_i2c, I2C_SLAVE, i2c_addr) < 0)
        {
            std::cout << "Failed to acquire bus access and/or talk to slave.\n" << '\n';
            //ERROR HANDLING; you can check errno to see what went wrong
            return;
        } else {
            std::cout << "Succeeded to acquire bus access and/or talk to slave.\n" << '\n';

        }

    }

    bool I2C::read_I2C(int nr_of_bytes_to_read, char buffer[]) {
        //----- READ BYTES -----
        if (read(file_i2c, buffer, nr_of_bytes_to_read) != nr_of_bytes_to_read)		//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
        {
            //ERROR HANDLING: i2c transaction failed
            printf("Failed to read from the i2c bus.\n");
            return false;
        }
        else
        {
            return true;
        }
    }

    void I2C::write_I2C(int nr_of_bytes_to_write, char buffer[]) {
        //----- WRITE BYTES -----
        if (write(file_i2c, buffer, nr_of_bytes_to_write) != nr_of_bytes_to_write)		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
        {
            /* ERROR HANDLING: i2c transaction failed */
            printf("Failed to write to the i2c bus.\n");
        }
    }
};
