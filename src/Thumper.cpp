#include "Thumper.h"
#include "json.hpp"
#include <unistd.h>

namespace RPI_I2C{

    Thumper::Thumper(void){

    }

    void Thumper::set_address(std::string address){
        this->address = address;
        this->post_drive = address + "speed";
        std::cout << post_drive << '\n';
    }

    void Thumper::drive_forward(void){
        nlohmann::json j ={
            {"left_speed", 100},
            {"right_speed", 100}
        };

        std::cout << "Driving forward" << '\n';
        RestClient::Response r = RestClient::post(post_drive, "application/json", j.dump());
        usleep(50000);
    }

    void Thumper::drive_backward(void){
        nlohmann::json j ={
            {"left_speed", -100},
            {"right_speed", -100}
        };

        std::cout << "Driving backward" << '\n';
        RestClient::Response r = RestClient::post(post_drive, "application/json", j.dump());
        usleep(50000);
    }

    void Thumper::drive_left(void){
        nlohmann::json j ={
            {"left_speed", 100},
            {"right_speed", 255}
        };

        std::cout << "Driving left" << '\n';
        RestClient::Response r = RestClient::post(post_drive, "application/json", j.dump());
        usleep(50000);
    }

    void Thumper::drive_right(void){
        nlohmann::json j ={
            {"left_speed", 255},
            {"right_speed", 100}
        };

        std::cout << "Driving right" << '\n';
        RestClient::Response r = RestClient::post(post_drive, "application/json", j.dump());
        usleep(50000);
    }

    void Thumper::stop(void){
        nlohmann::json j ={
            {"left_speed", 0},
            {"right_speed", 0}
        };

        std::cout << "Stopping" << '\n';
        RestClient::Response r = RestClient::post(post_drive, "application/json", j.dump());
    }
};
