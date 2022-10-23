#include "src/drivers/onboard_led/onboard_led.h"
#include "src/drivers/nixie/nixie.h"
#include "src/drivers/ds3231/ds3231.h"

void main(void)
{
    OnboardLed_Init();

    Nixie_Init();

    Ds3231_Init();

    while (1)
    {
        char dataSeconds;
        Ds3231_Read(0x00, &dataSeconds);
        Nixie_Display(0, 0);
        Nixie_Display(1, 0);
        Nixie_Display(2, 0);
        Nixie_Display(3, 0);
        Nixie_Display(4, 0);
        Nixie_Display(5, 0);
        for (long i = 0; i < 1000000; i++);
        Nixie_Display(0, 1);
        Nixie_Display(1, 1);
        Nixie_Display(2, 1);
        Nixie_Display(3, 1);
        Nixie_Display(4, 1);
        Nixie_Display(5, 1);
        for (long i = 0; i < 1000000; i++);
        Nixie_Display(0, 2);
        Nixie_Display(1, 2);
        Nixie_Display(2, 2);
        Nixie_Display(3, 2);
        Nixie_Display(4, 2);
        Nixie_Display(5, 2);
        for (long i = 0; i < 1000000; i++);
        Nixie_Display(0, 3);
        Nixie_Display(1, 3);
        Nixie_Display(2, 3);
        Nixie_Display(3, 3);
        Nixie_Display(4, 3);
        Nixie_Display(5, 3);
        for (long i = 0; i < 1000000; i++);
        Nixie_Display(0, 4);
        Nixie_Display(1, 4);
        Nixie_Display(2, 4);
        Nixie_Display(3, 4);
        Nixie_Display(4, 4);
        Nixie_Display(5, 4);
        for (long i = 0; i < 1000000; i++);
        Nixie_Display(0, 5);
        Nixie_Display(1, 5);
        Nixie_Display(2, 5);
        Nixie_Display(3, 5);
        Nixie_Display(4, 5);
        Nixie_Display(5, 5);
        for (long i = 0; i < 1000000; i++);
        Nixie_Display(0, 6);
        Nixie_Display(1, 6);
        Nixie_Display(2, 6);
        Nixie_Display(3, 6);
        Nixie_Display(4, 6);
        Nixie_Display(5, 6);
        for (long i = 0; i < 1000000; i++);
        Nixie_Display(0, 7);
        Nixie_Display(1, 7);
        Nixie_Display(2, 7);
        Nixie_Display(3, 7);
        Nixie_Display(4, 7);
        Nixie_Display(5, 7);
        for (long i = 0; i < 1000000; i++);
        Nixie_Display(0, 8);
        Nixie_Display(1, 8);
        Nixie_Display(2, 8);
        Nixie_Display(3, 8);
        Nixie_Display(4, 8);
        Nixie_Display(5, 8);
        for (long i = 0; i < 1000000; i++);
        Nixie_Display(0, 9);
        Nixie_Display(1, 9);
        Nixie_Display(2, 9);
        Nixie_Display(3, 9);
        Nixie_Display(4, 9);
        Nixie_Display(5, 9);
        for (long i = 0; i < 1000000; i++);
    }
}