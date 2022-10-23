#ifndef DRIVERS_DS3231_H__
#define DRIVERS_DS3231_H__

#include <stdint.h>

#define DS3231_PIN_CL      (6)
#define DS3231_PIN_DA      (7)

// typedef struct Ds3231_Data {
//     int16_t accelerometerX;
//     int16_t accelerometerY;
//     int16_t accelerometerZ;
//     int16_t temperature;
//     int16_t gyroX;
//     int16_t gyroY;
//     int16_t gyroZ;
// } Ds3231_Data;

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
// int8_t Ds3231_FetchAll(Ds3231_Data *data);

#endif