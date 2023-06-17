#ifndef DRIVERS_DS3231_H__
#define DRIVERS_DS3231_H__

#include <stdint.h>

#define DS3231_PIN_CL      (1)
#define DS3231_PIN_DA      (0)

int8_t Ds3231_Init(void);
int8_t Ds3231_Start(void);
int8_t Ds3231_SendAddress(char address);
int8_t Ds3231_SendData(char data);
char Ds3231_ReadData(void);
int8_t Ds3231_Stop(void);
int8_t Ds3231_Read(char address, char *data);
int8_t Ds3231_BurstRead(char address, char *data, uint8_t reads);
int8_t Ds3231_Write(char address, char data);
int8_t Ds3231_BurstWrite(char address, char *data);
int8_t Ds3231_GetSeconds(char *seconds);
int8_t Ds3231_GetMinutes(char *minutes);
int8_t Ds3231_GetHours(char *hours);
int8_t Ds3231_GetTime(int8_t *hours, int8_t *minutes, int8_t *seconds);
int8_t Ds3231_SetSeconds(int8_t seconds);
int8_t Ds3231_SetMinutes(int8_t minutes);
int8_t Ds3231_SetHours(int8_t hours);

#endif