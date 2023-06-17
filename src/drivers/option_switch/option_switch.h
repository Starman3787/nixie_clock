#ifndef DRIVERS_OPTIONSWITCH_H__
#define DRIVERS_OPTIONSWITCH_H__

#include <stdint.h>

#define OPTIONSWITCH_OPT_0       (3)
#define OPTIONSWITCH_OPT_1       (4)
#define OPTIONSWITCH_OPT_2       (5)
#define OPTIONSWITCH_OPT_3       (6)
#define OPTIONSWITCH_OPT_4       (7)
#define OPTIONSWITCH_OPT_5       (8)
#define OPTIONSWITCH_OPT_6       (9)
#define OPTIONSWITCH_OPT_7       (10)
#define OPTIONSWITCH_OPT_8       (11)
#define OPTIONSWITCH_OPT_9       (12)
#define OPTIONSWITCH_OPT_10      (5)
#define OPTIONSWITCH_OPT_11      (6)

int8_t OptionSwitch_Init(void);
int8_t OptionSwitch_Read(uint8_t *mode);
int8_t OptionSwitch_Interpret_A(uint32_t inputValue, uint8_t *mode);
int8_t OptionSwitch_Interpret_C(uint32_t inputValue, uint8_t *mode);

#endif