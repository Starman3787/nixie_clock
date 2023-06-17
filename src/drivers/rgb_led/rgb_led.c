#include <stdint.h>
#include "src/headers/stm32f412zx.h"
#include "src/drivers/rgb_led/rgb_led.h"

int8_t RgbLed_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;

    RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM13EN |
                    RCC_APB1ENR_TIM14EN;

    GPIOF->MODER |= (0b10 << (RGBLED_PIN_0_R * 2)) |
                    (0b10 << (RGBLED_PIN_0_G * 2)) |
                    (0b10 << (RGBLED_PIN_0_B * 2));

    GPIOF->AFR[0] |=    (0x03 << (RGBLED_PIN_0_G * 4));
    GPIOF->AFR[1] |=    (0x09 << ((RGBLED_PIN_0_B - 8) * 4)) |
                        (0x09 << ((RGBLED_PIN_0_R - 8) * 4));

    TIM11->PSC = 42 - 1;
    TIM13->PSC = 42 - 1;
    TIM14->PSC = 42 - 1;

    TIM11->ARR = 1000 - 1;
    TIM13->ARR = 1000 - 1;
    TIM14->ARR = 1000 - 1;

    TIM11->CNT = 0;
    TIM13->CNT = 0;
    TIM14->CNT = 0;

    TIM11->CCMR1 |= TIM_CCMR1_OC1M_2 | 
                    TIM_CCMR1_OC1M_1;
    TIM13->CCMR1 |= TIM_CCMR1_OC1M_2 | 
                    TIM_CCMR1_OC1M_1;
    TIM14->CCMR1 |= TIM_CCMR1_OC1M_2 | 
                    TIM_CCMR1_OC1M_1;

    TIM11->CCER |= TIM_CCER_CC1E;
    TIM13->CCER |= TIM_CCER_CC1E;
    TIM14->CCER |= TIM_CCER_CC1E;

    TIM11->CR1 |= TIM_CR1_CEN;
    TIM13->CR1 |= TIM_CR1_CEN;
    TIM14->CR1 |= TIM_CR1_CEN;

    return 0;
}

int8_t RgbLed_SetRgb(uint16_t r, uint16_t g, uint16_t b)
{
    TIM14->CCR1 = r;
    TIM11->CCR1 = g;
    TIM13->CCR1 = b;

    return 0;
}