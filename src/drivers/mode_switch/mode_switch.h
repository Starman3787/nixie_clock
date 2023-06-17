#ifndef DRIVERS_MODESWITCH_H__
#define DRIVERS_MODESWITCH_H__

#include <stdint.h>

#define MODESWITCH_OPT_0       (0)
#define MODESWITCH_OPT_1       (1)
#define MODESWITCH_OPT_2       (2)

int8_t ModeSwitch_Init(void);
int8_t ModeSwitch_Read(uint8_t *mode);
int8_t ModeSwitch_Interpret(uint32_t inputValue, uint8_t *mode);

#endif