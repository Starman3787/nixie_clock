#ifndef DRIVERS_NIXIE_H__
#define DRIVERS_NIXIE_H__

#include <stdint.h>

#define NIXIE_DIGIT_0A      (4)
#define NIXIE_DIGIT_0B      (8)
#define NIXIE_DIGIT_0C      (9)
#define NIXIE_DIGIT_0D      (3)

#define NIXIE_DIGIT_1A      (2)
#define NIXIE_DIGIT_1B      (10)
#define NIXIE_DIGIT_1C      (1)
#define NIXIE_DIGIT_1D      (5)

#define NIXIE_DIGIT_2A      (7)
#define NIXIE_DIGIT_2B      (6)
#define NIXIE_DIGIT_2C      (5)
#define NIXIE_DIGIT_2D      (4)

#define NIXIE_DIGIT_3A      (0)
#define NIXIE_DIGIT_3B      (1)
#define NIXIE_DIGIT_3C      (2)
#define NIXIE_DIGIT_3D      (3)

#define NIXIE_DIGIT_4A      (15)
#define NIXIE_DIGIT_4B      (12)
#define NIXIE_DIGIT_4C      (11)
#define NIXIE_DIGIT_4D      (10)

#define NIXIE_DIGIT_5A      (12)
#define NIXIE_DIGIT_5B      (13)
#define NIXIE_DIGIT_5C      (14)
#define NIXIE_DIGIT_5D      (15)

int8_t Nixie_Init(void);
int8_t Nixie_Display(uint8_t digit, uint8_t value);

uint8_t Nixie_DisplayCombinationsTable[10][4];
uint8_t Nixie_DisplayPinsTable[6][4];

#endif