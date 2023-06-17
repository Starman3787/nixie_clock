#include <stdint.h>
#include <stdbool.h>
#include "src/headers/stm32f412zx.h"
#include "src/drivers/onboard_led/onboard_led.h"

int8_t OnboardLed_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    GPIOB->MODER = 0;

    GPIOB->MODER |= (0b01 << (ONBOARDLED_PIN_0 * 2));

    return 0;
}

int8_t OnboardLed_Write(bool state)
{
    if (state == true)
        GPIOB->ODR |= (0b1 << ONBOARDLED_PIN_0);
    else
        GPIOB->ODR &= ~(0b1 << ONBOARDLED_PIN_0);

    return 0;
}

int8_t OnboardLed_Toggle(void)
{
    GPIOB->ODR ^= (0b1 << ONBOARDLED_PIN_0);

    return 0;
}