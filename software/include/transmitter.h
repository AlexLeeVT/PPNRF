// C/C++ libraries
#include <bitset>
#include <cstdint>
#include <stdio.h>

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

#define PACKET_LENGTH 28

RF24 radio(CE, CSN); // pin numbers connected to the radio's CE and CSN pins (respectively)
SPI spi;

const uint8_t address[5] = {'R','x','A','A','A'};

struct t_DataPacket {
    uint16_t GPIO;
};
typedef struct t_DataPacket dataPacket;

std::bitset<PACKET_LENGTH> dataToSend;

unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 1000; // send once per second

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