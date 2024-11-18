#include <receiver.h>
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
    radio.setDataRate(  RF24_250KBPS  );
    radio.openReadingPipe(1, address);
    radio.startListening();
}

void getData() {
    if ( radio.available() ) {
        radio.read( &dataReceived, sizeof(dataReceived) );
        newData = true;
    }
}

void showData() {
    if (newData == true) {
        printf("Data received \n");
        printf("%s", dataReceived.to_string().c_str());
        printf("\n");
        newData = false;
    }
}

void app_setup()
{
    stdio_init_all();
    initialize_usb();
    
    setup_radio();

    dataReceived.reset();
}

void app_loop()
{
    getData();
    showData();
}