#include <stdint.h>
#include "src/headers/stm32f412zx.h"
#include "src/drivers/option_switch/option_switch.h"

int8_t OptionSwitch_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    GPIOC->MODER &= ~(0b11 << (OPTIONSWITCH_OPT_0 * 2)) &
                    ~(0b11 << (OPTIONSWITCH_OPT_1 * 2)) &
                    ~(0b11 << (OPTIONSWITCH_OPT_2 * 2)) &
                    ~(0b11 << (OPTIONSWITCH_OPT_3 * 2)) &
                    ~(0b11 << (OPTIONSWITCH_OPT_4 * 2)) &
                    ~(0b11 << (OPTIONSWITCH_OPT_5 * 2)) &
                    ~(0b11 << (OPTIONSWITCH_OPT_6 * 2)) &
                    ~(0b11 << (OPTIONSWITCH_OPT_7 * 2)) &
                    ~(0b11 << (OPTIONSWITCH_OPT_8 * 2)) &
                    ~(0b11 << (OPTIONSWITCH_OPT_9 * 2));

    GPIOA->MODER &= ~(0b11 << (OPTIONSWITCH_OPT_10 * 2)) &
                    ~(0b11 << (OPTIONSWITCH_OPT_11 * 2));

    GPIOC->PUPDR |= (0b01 << (OPTIONSWITCH_OPT_0 * 2)) |
                    (0b01 << (OPTIONSWITCH_OPT_1 * 2)) |
                    (0b01 << (OPTIONSWITCH_OPT_2 * 2)) |
                    (0b01 << (OPTIONSWITCH_OPT_3 * 2)) |
                    (0b01 << (OPTIONSWITCH_OPT_4 * 2)) |
                    (0b01 << (OPTIONSWITCH_OPT_5 * 2)) |
                    (0b01 << (OPTIONSWITCH_OPT_6 * 2)) |
                    (0b01 << (OPTIONSWITCH_OPT_7 * 2)) |
                    (0b01 << (OPTIONSWITCH_OPT_8 * 2)) |
                    (0b01 << (OPTIONSWITCH_OPT_9 * 2));

    GPIOA->PUPDR |= (0b01 << (OPTIONSWITCH_OPT_10 * 2)) |
                    (0b01 << (OPTIONSWITCH_OPT_11 * 2));

    return 0;
}

int8_t OptionSwitch_Read(uint8_t *option)
{
    uint32_t inputValueC = ~(GPIOC->IDR);
    
    if (OptionSwitch_Interpret_C(inputValueC, option) == 1)
    {
        uint32_t inputValueA = ~(GPIOA->IDR);

        if (OptionSwitch_Interpret_A(inputValueA, option) == 1)
            return 1;
    }

    return 0;
}

int8_t OptionSwitch_Interpret_C(uint32_t inputValue, uint8_t *option)
{
    if (inputValue & (0b1 << OPTIONSWITCH_OPT_0))
        *option = 0;
    else if (inputValue & (0b1 << OPTIONSWITCH_OPT_1))
        *option = 1;
    else if (inputValue & (0b1 << OPTIONSWITCH_OPT_2))
        *option = 2;
    else if (inputValue & (0b1 << OPTIONSWITCH_OPT_3))
        *option = 3;
    else if (inputValue & (0b1 << OPTIONSWITCH_OPT_4))
        *option = 4;
    else if (inputValue & (0b1 << OPTIONSWITCH_OPT_5))
        *option = 5;
    else if (inputValue & (0b1 << OPTIONSWITCH_OPT_6))
        *option = 6;
    else if (inputValue & (0b1 << OPTIONSWITCH_OPT_7))
        *option = 7;
    else if (inputValue & (0b1 << OPTIONSWITCH_OPT_8))
        *option = 8;
    else if (inputValue & (0b1 << OPTIONSWITCH_OPT_9))
        *option = 9;
    else
        return 1;

    return 0;
}

int8_t OptionSwitch_Interpret_A(uint32_t inputValue, uint8_t *option)
{
    if (inputValue & (0b1 << OPTIONSWITCH_OPT_10))
        *option = 10;
    else if (inputValue & (0b1 << OPTIONSWITCH_OPT_11))
        *option = 11;
    else
        return 1;

    return 0;
}