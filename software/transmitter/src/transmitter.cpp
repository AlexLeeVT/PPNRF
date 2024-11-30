#include <transmitter.h>
#include "pico/sleep.h"

// app functions 
void app_setup()
{
    stdio_init_all();
    initialize_usb();

    setup_radio();

    dataToSend = (1 << 0);
}

void app_loop()
{
    currentMillis = millis();
    if (currentMillis - prevMillis >= txIntervalMillis) {
        send();
        prevMillis = millis();
    }
}

// radio functions
void setup_radio()
{
    spi.begin(spi0, SCK, TX, RX); // spi0 or spi1 bus, SCK, TX, RX
    if (!radio.begin(&spi)) {
        printf("Radio hardware is not responding!\n");
        sleep_ms(500);
    }
    // radio.setAutoAck(false);

    radio.setChannel(CHANNEL);
    radio.setDataRate(  RF24_2MBPS  );
    radio.setRetries(0, 3); // delay, count
    radio.openWritingPipe(address);

}

void initialize_usb()
{
    // while (!tud_cdc_connected())
    // {
    //     sleep_ms(10);
    // }
}

void updateMessage()
{
    // so you can see that new data is being sent
    dataToSend = (dataToSend) << 1;
    if (dataToSend == (1 << 10)) {
        dataToSend = (1 << 0);
    }
}

void send() {
    startTimeCheck = board_millis();

    bool rslt;
    rslt = radio.write( &dataToSend, sizeof(dataToSend) );
        // Always use sizeof() as it gives the size as the number of bytes.
        // For example if dataToSend was an int sizeof() would correctly return 2

    printf("Data Sent ");
    printf("%s", dataToSend.to_string().c_str());
    if (rslt) {
        unsigned long timeElapsed = board_millis() - startTimeCheck;
        printf("  Acknowledge received, time elapsed: %d\n", timeElapsed);
        updateMessage();
    }
    else {
        printf("  Tx failed\n");
    }
}
