// #include <tester.h>

// void initialize_usb()
// {
//     // while (!tud_cdc_connected())
//     // while(!tud_connected())
//     // {
//     //     sleep_ms(10);
//     // }
// }

// void setup_radio()
// {
//     spi.begin(spi0, SCK, TX, RX); // spi0 or spi1 bus, SCK, TX, RX
//     if (!radio.begin(&spi)) {
//         printf("Radio hardware is not responding!\n");
//         sleep_ms(500);
//     }

//     radio.openReadingPipe(1, address);
//     radio.setDataRate(RF24_250KBPS);
//     radio.printPrettyDetails();
// }

// void app_setup()
// {
//     stdio_init_all();
//     initialize_usb();

//     setup_radio();
// }

// void app_loop()
// {

// }


#include <tester.h>
#include <algorithm>

const uint8_t num_channels = 128;
uint8_t values[num_channels];

//
// Setup
//

void setup(void)
{
  //
  // Print preamble
  //

//   Serial.begin(115200);
//   printf_begin();
  printf("\n\rRF24/examples/scanner/\n\r");

  //
  // Setup and configure rf radio
  //

  radio.begin();
  radio.setAutoAck(false);

  // Get into standby mode
  radio.startListening();
  radio.stopListening();

  // Print out header, high then low digit
  int i = 0;
  while ( i < num_channels )
  {
    printf("%x",i>>4);
    ++i;
  }
  printf("\n\r");
  i = 0;
  while ( i < num_channels )
  {
    printf("%x",i&0xf);
    ++i;
  }
  printf("\n\r");
}

//
// Loop
//

const int num_reps = 100;

void loop(void)
{
  // Clear measurement values
  memset(values,0,sizeof(values));

  // Scan all channels num_reps times
  int rep_counter = num_reps;
  while (rep_counter--)
  {
    int i = num_channels;
    while (i--)
    {
      // Select this channel
      radio.setChannel(i);

      // Listen for a little
      radio.startListening();
      delayMicroseconds(225);
      

      // Did we get a carrier?
      if ( radio.testCarrier() ){
        ++values[i];
      }
      radio.stopListening();
    }
  }

  // Print out channel measurements, clamped to a single hex digit
  int i = 0;
  while ( i < num_channels )
  {
    printf("%x",std::min(0xf,values[i]&0xf));
    ++i;
  }
  printf("\n\r");
}

int main()
{
    setup();

    while (true)
    {
        loop();
    }
};

// vim:ai:cin:sts=2 sw=2 ft=cpp
