#include <stdint.h>
#include <stdbool.h>
#include "src/headers/stm32f411xe.h"
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
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN |
                    RCC_AHB1ENR_GPIOBEN;

    GPIOA->MODER = 0;
    GPIOB->MODER = 0;
    // 0
    GPIOB->MODER |= (0b01 << (NIXIE_DIGIT_0A * 2)) |
                    (0b01 << (NIXIE_DIGIT_0B * 2)) |
                    (0b01 << (NIXIE_DIGIT_0C * 2)) |
                    (0b01 << (NIXIE_DIGIT_0D * 2));
    // 1
    GPIOB->MODER |= (0b01 << (NIXIE_DIGIT_1A * 2)) |
                    (0b01 << (NIXIE_DIGIT_1B * 2)) |
                    (0b01 << (NIXIE_DIGIT_1C * 2)) |
                    (0b01 << (NIXIE_DIGIT_1D * 2));
    // 2
    GPIOA->MODER |= (0b01 << (NIXIE_DIGIT_2A * 2)) |
                    (0b01 << (NIXIE_DIGIT_2B * 2)) |
                    (0b01 << (NIXIE_DIGIT_2C * 2)) |
                    (0b01 << (NIXIE_DIGIT_2D * 2));
    // 3
    GPIOA->MODER |= (0b01 << (NIXIE_DIGIT_3A * 2)) |
                    (0b01 << (NIXIE_DIGIT_3B * 2)) |
                    (0b01 << (NIXIE_DIGIT_3C * 2)) |
                    (0b01 << (NIXIE_DIGIT_3D * 2));
    // 4
    GPIOA->MODER |= (0b01 << (NIXIE_DIGIT_4A * 2)) |
                    (0b01 << (NIXIE_DIGIT_4B * 2)) |
                    (0b01 << (NIXIE_DIGIT_4C * 2)) |
                    (0b01 << (NIXIE_DIGIT_4D * 2));
    // 5
    GPIOB->MODER |= (0b01 << (NIXIE_DIGIT_5A * 2)) |
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
        case 1:
        case 5:
            GPIOB->BSRR =   (0b1 << pinsTableCopy[0]) |
                            (0b1 << pinsTableCopy[1]) |
                            (0b1 << pinsTableCopy[2]) |
                            (0b1 << pinsTableCopy[3]);
        break;

        case 2:
        case 3:
        case 4:
            GPIOA->BSRR =   (0b1 << pinsTableCopy[0]) |
                            (0b1 << pinsTableCopy[1]) |
                            (0b1 << pinsTableCopy[2]) |
                            (0b1 << pinsTableCopy[3]);
        break;
    }
    return 0;
}