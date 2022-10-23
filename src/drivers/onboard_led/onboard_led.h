#ifndef DRIVERS_ONBOARDLED_H__
#define DRIVERS_ONBOARDLED_H__

#include <stdint.h>
#include <stdbool.h>

#define ONBOARDLED_PIN_0        (13)

int8_t OnboardLed_Init(void);
int8_t OnboardLed_Write(bool state);
int8_t OnboardLed_Toggle(void);

#endif