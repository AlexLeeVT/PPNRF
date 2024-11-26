#ifndef TRANSMITTER_H_
#define TRANSMITTER_H_

// C/C++ libraries
#include <bitset>
#include <cstdint>
#include <stdio.h>

// pico libraries
#include "pico/stdlib.h"
#include "bsp/board.h"

// tiny usb library
#include <tusb.h>

// HAL files
#include <HAL.h>

// radio library
#include <RF24.h>

RF24 radio(CE, CSN); // pin numbers connected to the radio's CE and CSN pins (respectively)
SPI spi;

struct t_DataPacket {
    uint16_t GPIO;
};
typedef struct t_DataPacket dataPacket;

std::bitset<PACKET_LENGTH> dataToSend;

unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 500; // send once per second

unsigned long startTimeCheck;

void app_setup();
void app_loop();

void initialize_usb();
void setup_radio();

void updateMessage();
void send();

int main()
{
    app_setup();

    while (true)
    {
        app_loop();
    }
};

#endif