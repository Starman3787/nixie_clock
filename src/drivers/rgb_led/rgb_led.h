#ifndef DRIVERS_RGBLED_H__
#define DRIVERS_RGBLED_H__

#include <stdint.h>

#define RGBLED_PIN_0_R      (9)
#define RGBLED_PIN_0_G      (7)
#define RGBLED_PIN_0_B      (8)

int8_t RgbLed_Init(void);
int8_t RgbLed_SetRgb(uint16_t r, uint16_t g, uint16_t b);

#endif