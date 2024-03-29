#include <stdint.h>
#include <stdbool.h>
#include "src/headers/stm32f412zx.h"
#include "src/drivers/nixie/nixie.h"

uint8_t Nixie_DisplayCombinationsTable[10][4] = {
    {0,0,0,0},
    {0,0,0,1},
    {0,0,1,0},
    {0,0,1,1},
    {0,1,0,0},
    {0,1,0,1},
    {0,1,1,0},
    {0,1,1,1},
    {1,0,0,0},
    {1,0,0,1}
};

uint8_t Nixie_DisplayPinsTable[6][4] = {
    {NIXIE_DIGIT_0D,NIXIE_DIGIT_0C,NIXIE_DIGIT_0B,NIXIE_DIGIT_0A},
    {NIXIE_DIGIT_1D,NIXIE_DIGIT_1C,NIXIE_DIGIT_1B,NIXIE_DIGIT_1A},
    {NIXIE_DIGIT_2D,NIXIE_DIGIT_2C,NIXIE_DIGIT_2B,NIXIE_DIGIT_2A},
    {NIXIE_DIGIT_3D,NIXIE_DIGIT_3C,NIXIE_DIGIT_3B,NIXIE_DIGIT_3A},
    {NIXIE_DIGIT_4D,NIXIE_DIGIT_4C,NIXIE_DIGIT_4B,NIXIE_DIGIT_4A},
    {NIXIE_DIGIT_5D,NIXIE_DIGIT_5C,NIXIE_DIGIT_5B,NIXIE_DIGIT_5A}
};

int8_t Nixie_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN |
                    RCC_AHB1ENR_GPIOEEN;

    GPIOD->MODER = 0;
    GPIOE->MODER = 0;

    // 0
    GPIOD->MODER |= (0b01 << (NIXIE_DIGIT_0A * 2)) |
                    (0b01 << (NIXIE_DIGIT_0B * 2)) |
                    (0b01 << (NIXIE_DIGIT_0C * 2)) |
                    (0b01 << (NIXIE_DIGIT_0D * 2));
    // 1
    GPIOE->MODER |= (0b01 << (NIXIE_DIGIT_1A * 2)) |
                    (0b01 << (NIXIE_DIGIT_1B * 2)) |
                    (0b01 << (NIXIE_DIGIT_1C * 2)) |
                    (0b01 << (NIXIE_DIGIT_1D * 2));
    // 2
    GPIOD->MODER |= (0b01 << (NIXIE_DIGIT_2A * 2)) |
                    (0b01 << (NIXIE_DIGIT_2B * 2)) |
                    (0b01 << (NIXIE_DIGIT_2C * 2)) |
                    (0b01 << (NIXIE_DIGIT_2D * 2));
    // 3
    GPIOE->MODER |= (0b01 << (NIXIE_DIGIT_3A * 2)) |
                    (0b01 << (NIXIE_DIGIT_3B * 2)) |
                    (0b01 << (NIXIE_DIGIT_3C * 2)) |
                    (0b01 << (NIXIE_DIGIT_3D * 2));
    // 4
    GPIOD->MODER |= (0b01 << (NIXIE_DIGIT_4A * 2)) |
                    (0b01 << (NIXIE_DIGIT_4B * 2)) |
                    (0b01 << (NIXIE_DIGIT_4C * 2)) |
                    (0b01 << (NIXIE_DIGIT_4D * 2));
    // 5
    GPIOE->MODER |= (0b01 << (NIXIE_DIGIT_5A * 2)) |
                    (0b01 << (NIXIE_DIGIT_5B * 2)) |
                    (0b01 << (NIXIE_DIGIT_5C * 2)) |
                    (0b01 << (NIXIE_DIGIT_5D * 2));

    return 0;
}

int8_t Nixie_Display(uint8_t digit, uint8_t value)
{
    if (value > 9)
        return -1;
    uint8_t pinsTableCopy[4];
    for (uint8_t i = 0; i < 4; i++)
    {
        pinsTableCopy[i] = Nixie_DisplayPinsTable[digit][i];
        if (Nixie_DisplayCombinationsTable[value][i] == 0)
            pinsTableCopy[i] = pinsTableCopy[i] + 16;
    }
    switch (digit)
    {
        case 0:
        case 2:
        case 4:
            GPIOD->BSRR =   (0b1 << pinsTableCopy[0]) |
                            (0b1 << pinsTableCopy[1]) |
                            (0b1 << pinsTableCopy[2]) |
                            (0b1 << pinsTableCopy[3]);
        break;

        case 1:
        case 3:
        case 5:
            GPIOE->BSRR =   (0b1 << pinsTableCopy[0]) |
                            (0b1 << pinsTableCopy[1]) |
                            (0b1 << pinsTableCopy[2]) |
                            (0b1 << pinsTableCopy[3]);
        break;
    }
    return 0;
}

int8_t Nixie_Scramble(bool brief)
{
    uint32_t iterations = 50;
    if (brief == true)
        iterations /= 2;
    for (uint16_t i = 0; i < iterations; i++)
    {
        for (uint8_t digit = 0; digit < 10; digit++)
        {
            Nixie_Display(0, digit);
            Nixie_Display(1, digit);
            Nixie_Display(2, digit);
            Nixie_Display(3, digit);
            Nixie_Display(4, digit);
            Nixie_Display(5, digit);

            for (uint32_t t = 0; t < 100000; t++);
        }
    }
    return 0;
}