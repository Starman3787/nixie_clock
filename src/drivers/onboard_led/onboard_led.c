#include <stdint.h>
#include <stdbool.h>
#include "src/headers/stm32f411xe.h"
#include "src/drivers/onboard_led/onboard_led.h"

int8_t OnboardLed_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    GPIOC->MODER |= (0b01 << (ONBOARDLED_PIN_0 * 2));

    return 0;
}

int8_t OnboardLed_Write(bool state)
{
    if (state == true)
        GPIOC->ODR |= (0b1 << ONBOARDLED_PIN_0);
    else
        GPIOC->ODR &= ~(0b1 << ONBOARDLED_PIN_0);

    return 0;
}

int8_t OnboardLed_Toggle(void)
{
    GPIOC->ODR ^= (0b1 << ONBOARDLED_PIN_0);

    return 0;
}