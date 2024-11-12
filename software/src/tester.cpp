#include <tester.h>

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

    radio.openReadingPipe(1, address);
    radio.setDataRate(RF24_250KBPS);
    radio.printPrettyDetails();
}

void app_setup()
{
    stdio_init_all();
    initialize_usb();

    setup_radio();
}

void app_loop()
{

}