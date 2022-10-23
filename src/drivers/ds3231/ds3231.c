#include <stdint.h>
#include "src/headers/stm32f411xe.h"
#include "src/drivers/ds3231/ds3231.h"

int8_t Ds3231_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    GPIOB->MODER |= (0b10 << (DS3231_PIN_CL * 2)) |
                    (0b10 << (DS3231_PIN_DA * 2));

    GPIOB->AFR[0] |= (0b0100 << (DS3231_PIN_CL * 4)) |
                    (0b0100 << (DS3231_PIN_DA * 4));

    GPIOB->OTYPER |= (0b1 << DS3231_PIN_CL) |
                    (0b1 << DS3231_PIN_DA);

    GPIOB->OSPEEDR |= (0b11 << (DS3231_PIN_CL * 2)) |
                        (0b11 << (DS3231_PIN_DA * 2));

    GPIOB->PUPDR |= (0b01 << (DS3231_PIN_CL * 2)) |
                        (0b01 << (DS3231_PIN_DA * 2));

    I2C1->CR1 = I2C_CR1_SWRST;

    I2C1->CR1 &= ~I2C_CR1_SWRST;

    I2C1->CR2 |= 0x08;

    I2C1->CCR = 0x78;

    I2C1->TRISE = 0x03;

    I2C1->CR1 |= I2C_CR1_PE;

    return 0;
}

int8_t Ds3231_Start(void)
{

    I2C1->CR1 |= I2C_CR1_START;

    while (!(I2C1->SR1 & I2C_SR1_SB));

    return 0;
}

int8_t Ds3231_SendAddress(char address)
{
    uint16_t reg;

    I2C1->DR = address;//(address << 1) | 0x01;

    while (!(I2C1->SR1 & I2C_SR1_ADDR));

    reg = I2C1->SR1 | I2C1->SR2;
    
    return 0;
}

int8_t Ds3231_SendData(char data)
{
    while (!(I2C1->SR1 & I2C_SR1_TXE));

    I2C1->DR = data;

    while (!(I2C1->SR1 & I2C_SR1_BTF));

    return 0;
}

char Ds3231_ReadData(void)
{

    while (!(I2C1->SR1 & I2C_SR1_RXNE));

    return I2C1->DR;

}

int8_t Ds3231_Stop(void)
{
    uint16_t reg;

    I2C1->CR1 &= ~I2C_CR1_ACK;

    reg = I2C1->SR1 | I2C1->SR2;

    I2C1->CR1 |= I2C_CR1_STOP;

    return 0;
}

int8_t Ds3231_Read(char address, char *data)
{
    uint16_t reg;

    I2C1->CR1 |= I2C_CR1_START |
                I2C_CR1_ACK;

    while (!(I2C1->SR1 & I2C_SR1_SB));

    I2C1->DR = 0b11010000;

    while (!(I2C1->SR1 & I2C_SR1_ADDR));

    reg = I2C1->SR1 | I2C1->SR2;

    while (!(I2C1->SR1 & I2C_SR1_TXE));

    I2C1->DR = address;

    while (!(I2C1->SR1 & I2C_SR1_BTF));

    I2C1->CR1 |= I2C_CR1_START;

    while (!(I2C1->SR1 & I2C_SR1_SB));

    I2C1->DR = 0b11010001;

    while (!(I2C1->SR1 & I2C_SR1_ADDR));

    reg = I2C1->SR1 | I2C1->SR2;

    I2C1->CR1 &= ~I2C_CR1_ACK;

    reg = I2C1->SR1 | I2C1->SR2;

    I2C1->CR1 |= I2C_CR1_STOP;

    while (!(I2C1->SR1 & I2C_SR1_RXNE));

    *data = I2C1->DR;

    return 0;
}

int8_t Ds3231_BurstRead(char address, char *data, uint8_t reads)
{
    uint16_t reg;

    I2C1->CR1 |= I2C_CR1_START |
                I2C_CR1_ACK;

    while (!(I2C1->SR1 & I2C_SR1_SB));

    I2C1->DR = 0b11010000;

    while (!(I2C1->SR1 & I2C_SR1_ADDR));

    reg = I2C1->SR1 | I2C1->SR2;

    while (!(I2C1->SR1 & I2C_SR1_TXE));

    I2C1->DR = address;

    while (!(I2C1->SR1 & I2C_SR1_BTF));

    I2C1->CR1 |= I2C_CR1_START;

    while (!(I2C1->SR1 & I2C_SR1_SB));

    I2C1->DR = 0b11010001;

    while (!(I2C1->SR1 & I2C_SR1_ADDR));

    reg = I2C1->SR1 | I2C1->SR2;

    for (uint8_t i = 0; i < reads; i++, data++)
    {
        if (i + 1 == reads)
        {
            I2C1->CR1 &= ~I2C_CR1_ACK;

            I2C1->CR1 |= I2C_CR1_STOP;
        }

        while (!(I2C1->SR1 & I2C_SR1_RXNE));

        *data = I2C1->DR;
    }

    return 0;
}

int8_t Ds3231_Write(char address, char data)
{
    uint16_t reg;

    I2C1->CR1 |= I2C_CR1_START |
                I2C_CR1_ACK;

    while (!(I2C1->SR1 & I2C_SR1_SB));

    I2C1->DR = 0b11010000;

    while (!(I2C1->SR1 & I2C_SR1_ADDR));

    reg = I2C1->SR1 | I2C1->SR2;

    while (!(I2C1->SR1 & I2C_SR1_TXE));

    I2C1->DR = address;

    while (!(I2C1->SR1 & I2C_SR1_BTF));

    while (!(I2C1->SR1 & I2C_SR1_TXE));

    I2C1->DR = data;

    while (!(I2C1->SR1 & I2C_SR1_BTF));

    I2C1->CR1 |= I2C_CR1_STOP;

    return 0;
}

int8_t Ds3231_BurstWrite(char address, char *data)
{
    uint16_t reg;

    I2C1->CR1 |= I2C_CR1_START |
                I2C_CR1_ACK;

    while (!(I2C1->SR1 & I2C_SR1_SB));

    I2C1->DR = 0b11010000;

    while (!(I2C1->SR1 & I2C_SR1_ADDR));

    reg = I2C1->SR1 | I2C1->SR2;

    while (!(I2C1->SR1 & I2C_SR1_TXE));

    I2C1->DR = address;

    while (!(I2C1->SR1 & I2C_SR1_BTF));

    while (*data != '\0')
    {
        while (!(I2C1->SR1 & I2C_SR1_TXE));

        I2C1->DR = *(data++);

        while (!(I2C1->SR1 & I2C_SR1_BTF));
    }

    I2C1->CR1 |= I2C_CR1_STOP;

    return 0;
}

// int8_t Mpu6050_FetchAll(Mpu6050_Data *data)
// {
//     char burstReadData[14];
//     Mpu6050_BurstRead(0x3B, burstReadData, 14);
//     data->accelerometerX = (burstReadData[0] << 8) | burstReadData[1];
//     data->accelerometerY = (burstReadData[2] << 8) | burstReadData[3];
//     data->accelerometerZ = (burstReadData[4] << 8) | burstReadData[5];
//     data->temperature = (burstReadData[6] << 8) | burstReadData[7];
//     data->gyroX = (burstReadData[8] << 8) | burstReadData[9];
//     data->gyroY = (burstReadData[10] << 8) | burstReadData[11];
//     data->gyroZ = (burstReadData[12] << 8) | burstReadData[13];
//     return 0;
// }