#ifndef HAL_H_
#define HAL_H_

// convert bit to a button mask
#define BIT_TO_BUTTON(x)    TU_BIT(x)

// GPIO Masks
#define MASK_GP0            (1 << 0)
#define MASK_GP1            (1 << 1)
#define MASK_GP2            (1 << 2)
#define MASK_GP3            (1 << 3)
#define MASK_GP4            (1 << 4)
#define MASK_GP5            (1 << 5)
#define MASK_GP6            (1 << 6)
#define MASK_GP7            (1 << 7)
#define MASK_GP8            (1 << 8)
#define MASK_GP9            (1 << 9)
#define MASK_GP10           (1 << 10)
#define MASK_GP11           (1 << 11)
#define MASK_GP12           (1 << 12)
#define MASK_GP13           (1 << 13)
#define MASK_GP14           (1 << 14)
#define MASK_GP15           (1 << 15)
#define MASK_GP16           (1 << 16)
#define MASK_GP17           (1 << 17)
#define MASK_GP18           (1 << 18)
#define MASK_GP19           (1 << 19)
#define MASK_GP20           (1 << 20)
#define MASK_GP21           (1 << 21)
#define MASK_GP22           (1 << 22)
#define MASK_GP23           (1 << 23)
#define MASK_GP24           (1 << 24)
#define MASK_GP25           (1 << 25)
#define MASK_GP26           (1 << 26)
#define MASK_GP27           (1 << 27)
#define MASK_GP28           (1 << 28)

// NRF24L01+ Radio SPI definitions
#define CE                  20
#define CSN                 17
#define SCK                 18
#define TX                  19
#define RX                  16

#define CHANNEL             0x7e

#define PACKET_LENGTH       28

const uint8_t address[5] = {'R','x','A','A','A'};

#endif