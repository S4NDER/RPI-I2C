# TouchBerry Pi
A project that make use of the TouchBerry Shield built for the RaspberryPi. It is a very basic, and not optimized (to drive very well) for the Thumper. The LED's on the Shield are just effects that can be looped.

* Arrow buttons: speak for themselves
* X: Stops the Thumper
* A: Toggle the leds.
* B: Go to next effect

## Getting Started
### Prerequisites
You need a RaspberryPi with preferably Raspbian running on it.
Git is also a must.

### Installing
Just clone the project and run the makefile on your Pi as it is native compiling!
```bash
git clone https://github.com/S4NDER/RPI-I2C
```
## Running it
```bash
./bin/touchshield
```
## Dependencies
```bash
sudo apt-get update && sudo apt-get install git build-essential autoconf automake libtool libcurl4-gnutls-dev
```

Compiling the library.
```bash
sudo su
cd /usr/local/src
git clone https://github.com/mrtazz/restclient-cpp.git
cd restclient-cpp
./autogen.sh
./configure
make install
ldconfig
```

```bash
sudo su
cd /usr/local/src
git clone https://github.com/nlohmann/json.git
cp json/src/json.hpp /usr/local/include/
```
Now you should be ready to run the makefile
```bash
cd RPI-I2C/
make clean
make
```
## License
This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
