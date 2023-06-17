#ifndef UTIL_CHECKINPUT_H__
#define UTIL_CHECKINPUT_H__

#include <stdint.h>
#include <stdbool.h>

int8_t Util_CheckInput(uint8_t *mode, uint8_t *option, bool *modeDefined, bool *optionDefined);

#endif