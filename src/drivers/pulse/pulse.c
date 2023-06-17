#include <stdint.h>
#include <stdbool.h>
#include "src/headers/stm32f412zx.h"
#include "src/drivers/pulse/pulse.h"

int8_t Pulse_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;

    GPIOF->MODER |= (0b01 << (PULSE_PIN * 2));

    return 0;
}

int8_t Pulse_Write(bool state)
{
    if (state == true)
        GPIOF->ODR |= (0b1 << PULSE_PIN);
    else
        GPIOF->ODR &= ~(0b1 << PULSE_PIN);

    return 0;
}

int8_t Pulse_Toggle(void)
{
    GPIOF->ODR ^= (0b1 << PULSE_PIN);

    return 0;
}