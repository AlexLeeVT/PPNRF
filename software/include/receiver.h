#ifndef RECEIVER_H_
#define RECEIVER_H_

// C/C++ libraries
#include <cstdint>
#include <stdio.h>
#include <iostream>
#include <bitset>

// pico libraries
#include "pico/stdlib.h"
#include "bsp/board.h"

// HAL import
#include <HAL.h>

// tiny usb library
#include <tusb.h>

// radio library
#include <RF24.h>

// HID library
// #include <DanceInputHandler.h>

RF24 radio(CE, CSN);            // pin numbers connected to the radio's CE and CSN pins (respectively)
SPI spi;

std::bitset<PACKET_LENGTH> dataReceived;   // this must match dataToSend in the TX
bool receivedData = false;

// application functions ----------------------------------------------------------------
void app_setup();               // setup application
void app_loop();                // application loop

// radio functions ----------------------------------------------------------------------
void setup_radio();             // initialize the radio
void getData();                 // receive data
void processData();             // format the data

// HID functions ------------------------------------------------------------------------
void initialize_usb();          // waits for connection to host device

// main loop ----------------------------------------------------------------------------
int main()
{
    app_setup();

    while (true)
    {
        app_loop();
    }
}

#endif