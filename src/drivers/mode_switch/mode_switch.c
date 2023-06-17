#include <stdint.h>
#include "src/headers/stm32f412zx.h"
#include "src/drivers/mode_switch/mode_switch.h"

int8_t ModeSwitch_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    GPIOC->MODER &= ~(0b11 << (MODESWITCH_OPT_0 * 2)) &
                    ~(0b11 << (MODESWITCH_OPT_1 * 2)) &
                    ~(0b11 << (MODESWITCH_OPT_2 * 2));

    GPIOC->PUPDR |= (0b01 << (MODESWITCH_OPT_0 * 2)) |
                    (0b01 << (MODESWITCH_OPT_1 * 2)) |
                    (0b01 << (MODESWITCH_OPT_2 * 2));

    return 0;
}

int8_t ModeSwitch_Read(uint8_t *mode)
{
    uint32_t inputValue = ~(GPIOC->IDR);
    
    if (ModeSwitch_Interpret(inputValue, mode) == 1)
        return 1;

    return 0;
}

int8_t ModeSwitch_Interpret(uint32_t inputValue, uint8_t *mode)
{
    if (inputValue & (0b1 << MODESWITCH_OPT_0))
        *mode = 0;
    else if (inputValue & (0b1 << MODESWITCH_OPT_1))
        *mode = 1;
    else if (inputValue & (0b1 << MODESWITCH_OPT_2))
        *mode = 2;
    else
        return 1;

    return 0;
}