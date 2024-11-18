#include <transmitter.h>
#include <pico/cyw43_arch.h>

void initialize_usb()
{
    while (!tud_cdc_connected())
    {
        sleep_ms(10);
    }
}

void setup_radio()
{
    spi.begin(spi0, SCK, TX, RX); // spi0 or spi1 bus, SCK, TX, RX
    if (!radio.begin(&spi)) {
        printf("Radio hardware is not responding!\n");
        sleep_ms(500);
    }

    radio.setChannel(CHANNEL);
    radio.setDataRate( RF24_250KBPS );
    radio.setRetries(3,5); // delay, count
    radio.openWritingPipe(address);
}

void app_setup()
{
    stdio_init_all();
    initialize_usb();

    setup_radio();

    dataToSend = (1 << 0);
}

void updateMessage() {
    // so you can see that new data is being sent
    dataToSend = (dataToSend) << 1;
    if (dataToSend == (1 << PACKET_LENGTH)) {
        dataToSend = (1 << 0);
    }
}

void send() {

    bool rslt;
    rslt = radio.write( &dataToSend, sizeof(dataToSend) );
        // Always use sizeof() as it gives the size as the number of bytes.
        // For example if dataToSend was an int sizeof() would correctly return 2

    printf("Data Sent ");
    printf("%s", dataToSend.to_string().c_str());
    if (rslt) {
        printf("  Acknowledge received\n");
        updateMessage();
    }
    else {
        printf("  Tx failed\n");
    }
}

void app_loop()
{
    currentMillis = millis();
    if (currentMillis - prevMillis >= txIntervalMillis) {
        send();
        prevMillis = millis();
    }
}