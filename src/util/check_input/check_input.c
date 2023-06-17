#include <stdint.h>
#include <stdbool.h>
#include "src/headers/stm32f412zx.h"
#include "src/util/check_input/check_input.h"
#include "src/drivers/option_switch/option_switch.h"
#include "src/drivers/mode_switch/mode_switch.h"

int8_t Util_CheckInput(uint8_t *mode, uint8_t *option, bool *modeDefined, bool *optionDefined)
{
    uint32_t inputValueC = ~(GPIOC->IDR);
    uint32_t inputValueA = ~(GPIOA->IDR);

    if (ModeSwitch_Interpret(inputValueC, mode) == 1)
        *modeDefined = false;
    else
        *modeDefined = true;

    if (OptionSwitch_Interpret_C(inputValueC, option) == 1)
    {
        if (OptionSwitch_Interpret_A(inputValueA, option) == 1)
            *optionDefined = false;
        else
            *optionDefined = true;
    }
    else
        *optionDefined = true;

    return 0;
}