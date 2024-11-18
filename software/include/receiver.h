// C/C++ libraries
#include <cstdint>
#include <stdio.h>
#include <bitset>
#include <iostream>

// pico libraries
#include "pico/stdlib.h"
#include "bsp/board.h"

// tiny usb library
#include <tusb.h>

// radio library
#include <RF24.h>

#define CE  20
#define CSN 17
#define SCK 18
#define TX  19
#define RX  16

#define CHANNEL 0x7e

RF24 radio(CE, CSN); // pin numbers connected to the radio's CE and CSN pins (respectively)
SPI spi;

const uint8_t address[5] = {'R','x','A','A','A'};

std::bitset<28> dataReceived; // this must match dataToSend in the TX
bool newData = false;

void app_setup();
void app_loop();

void initialize_usb();
void setup_radio();

void getData();
void showData();

int main()
{
    app_setup();

    while (true)
    {
        app_loop();
    }
}