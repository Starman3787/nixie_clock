#ifndef DRIVERS_NIXIE_H__
#define DRIVERS_NIXIE_H__

#include <stdint.h>
#include <stdbool.h>

#define NIXIE_DIGIT_0A      (7)
#define NIXIE_DIGIT_0B      (6)
#define NIXIE_DIGIT_0C      (5)
#define NIXIE_DIGIT_0D      (4)

#define NIXIE_DIGIT_1A      (2)
#define NIXIE_DIGIT_1B      (4)
#define NIXIE_DIGIT_1C      (5)
#define NIXIE_DIGIT_1D      (6)

#define NIXIE_DIGIT_2A      (0)
#define NIXIE_DIGIT_2B      (1)
#define NIXIE_DIGIT_2C      (2)
#define NIXIE_DIGIT_2D      (3)

#define NIXIE_DIGIT_3A      (10)
#define NIXIE_DIGIT_3B      (12)
#define NIXIE_DIGIT_3C      (14)
#define NIXIE_DIGIT_3D      (15)

#define NIXIE_DIGIT_4A      (11)
#define NIXIE_DIGIT_4B      (12)
#define NIXIE_DIGIT_4C      (13)
#define NIXIE_DIGIT_4D      (14)

#define NIXIE_DIGIT_5A      (7) // GPIOE
#define NIXIE_DIGIT_5B      (8)
#define NIXIE_DIGIT_5C      (13)
#define NIXIE_DIGIT_5D      (11)

int8_t Nixie_Init(void);
int8_t Nixie_Display(uint8_t digit, uint8_t value);
int8_t Nixie_Scramble(bool brief);

uint8_t Nixie_DisplayCombinationsTable[10][4];
uint8_t Nixie_DisplayPinsTable[6][4];

#endif