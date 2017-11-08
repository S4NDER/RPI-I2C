# This C++ compiler
PREFIX=/home/sander/rpi-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-
CC=$(PREFIX)g++


LIBS= -lpthread
# The compiler flags
CFLAGS=-Wall -c -std=c++11

EXECUTABLE=RPI_I2C

all: $(EXECUTABLE)

$(EXECUTABLE): main.o I2C.o QT1070.o TLC59116.o Color.o Led.o Effects.o
	$(CC) main.o I2C.o QT1070.o TLC59116.o Color.o Led.o Effects.o -o $(EXECUTABLE) $(LIBS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

I2C.o: lib/I2C.cpp
	$(CC) $(CFLAGS) lib/I2C.cpp

QT1070.o: lib/QT1070.cpp
	$(CC) $(CFLAGS) lib/QT1070.cpp

TLC59116.o: lib/TLC59116.cpp
	$(CC) $(CFLAGS) lib/TLC59116.cpp

Color.o: lib/Color.cpp
	$(CC) $(CFLAGS) lib/Color.cpp

Led.o: lib/Led.cpp
	$(CC) $(CFLAGS) lib/Led.cpp

Effects.o: lib/Effects.cpp
	$(CC) $(CFLAGS) lib/Effects.cpp

clean:
	rm -f *.o $(EXECUTABLE)
