#include <receiver.h>

// application functions ----------------------------------------------------------------
void app_setup()
{
    stdio_init_all();
    initialize_usb();
    board_init();

    // setup_dancepad();
    
    setup_radio();

    dataReceived.reset();
}

void app_loop()
{
    getData();
    processData();

    // update_hid();
}

// radio functions ----------------------------------------------------------------------
void setup_radio()
{
    spi.begin(spi0, SCK, TX, RX); // spi0 or spi1 bus, SCK, TX, RX
    if (!radio.begin(&spi)) {
        printf("Radio hardware is not responding!\n");
        sleep_ms(500);
    }

    radio.setChannel(CHANNEL);
    radio.setDataRate(  RF24_2MBPS  );
    // radio.setAutoAck(false);

    radio.openReadingPipe(1, address);
    radio.startListening();
}

void getData() {
    if ( radio.available() ) {
        radio.read( &dataReceived, sizeof(dataReceived) );
        receivedData = true;
    }
}

void processData() {
    if (receivedData) {
        printf("Data received \n");
        printf("%s", dataReceived.to_string().c_str());
        printf("\n");
        receivedData = false;
    }
}

// // USB functions ------------------------------------------------------------------------
void initialize_usb()
{
    // while (!tud_cdc_connected())
    // {
    //     sleep_ms(10);
    // }
}

// hid_custom_report_t* hid_task()
// {
//     hid_custom_report_t *report = new hid_custom_report_t {
//         .buttons = 0
//     };

//     // int button = (board_millis() / 1000) % 15;
//     // report->buttons |= TU_BIT(button);
//         // way to read from bitset
//     for(int i = 0; i < dataReceived.size(); i++)
//     {
//         if(dataReceived[i])
//             report->buttons |= BIT_TO_BUTTON(i);
//     }

//     return report;
// }
