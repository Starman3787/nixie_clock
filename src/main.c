#include <stdbool.h>
#include <stdint.h>
#include "src/drivers/onboard_led/onboard_led.h"
#include "src/drivers/nixie/nixie.h"
#include "src/drivers/ds3231/ds3231.h"
#include "src/drivers/rgb_led/rgb_led.h"
#include "src/drivers/pulse/pulse.h"
#include "src/drivers/option_switch/option_switch.h"
#include "src/drivers/mode_switch/mode_switch.h"
#include "src/util/check_input/check_input.h"

void main(void)
{
    OnboardLed_Init();

    Nixie_Init();

    Ds3231_Init();

    Pulse_Init();

    RgbLed_Init();

    OptionSwitch_Init();

    ModeSwitch_Init();

    uint16_t rgb[3] = {0, 0, 1000};
    uint8_t changing = 0;
    uint8_t previousChanging = 2;

    Nixie_Scramble(true);

    while (1)
    {
        int8_t hours, minutes, seconds;

        Ds3231_GetTime(&hours, &minutes, &seconds);

        Nixie_Display(0, hours / 10);
        Nixie_Display(1, hours % 10);
        Nixie_Display(2, minutes / 10);
        Nixie_Display(3, minutes % 10);
        Nixie_Display(4, seconds / 10);
        Nixie_Display(5, seconds % 10);

        if (seconds % 2 == 0)
            Pulse_Write(true);
        else
            Pulse_Write(false);

        rgb[changing] += 10;
        rgb[previousChanging] -= 10;

        if (rgb[changing] == 1000)
        {
            previousChanging = changing;
            if (++changing > 2)
                changing = 0;
            rgb[changing] = 0;
            rgb[previousChanging] = 1000;
        }

        RgbLed_SetRgb(rgb[0], rgb[1], rgb[2]);

        uint8_t mode, option;
        bool modeDefined = false, optionDefined = false;

        Util_CheckInput(&mode, &option, &modeDefined, &optionDefined);

        if (modeDefined == true && optionDefined == true)
        {
            switch (mode) {
                case 0:
                // hours
                Ds3231_SetHours(option + 12);
                break;
                case 1:
                // minutes
                Ds3231_SetMinutes(option * 5);
                break;
                case 2:
                // seconds
                Ds3231_SetSeconds(option * 5);
                break;
            }
        }

        if (minutes % 15 == 0 && seconds == 0 && modeDefined == false)
            Nixie_Scramble(false);

        for (uint32_t i = 0; i < 100000; i++);

    }
}