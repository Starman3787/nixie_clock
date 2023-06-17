#ifndef DRIVERS_PULSE_H__
#define DRIVERS_PULSE_H__

#include <stdint.h>
#include <stdbool.h>

#define PULSE_PIN           (13)

int8_t Pulse_Init(void);
int8_t Pulse_Write(bool state);
int8_t Pulse_Toggle(void);

#endif