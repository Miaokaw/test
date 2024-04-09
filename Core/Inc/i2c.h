#ifndef __I2C_H__
#define __I2C_H__

#include "../../User/Tools/Delay/Delay.h"

#define I2C_SCL(x)                                                                                                                               \
    do                                                                                                                                           \
    {                                                                                                                                            \
        x ? HAL_GPIO_WritePin(I2C_SCL_GPIO_Port, I2C_SCL_Pin, GPIO_PIN_SET) : HAL_GPIO_WritePin(I2C_SCL_GPIO_Port, I2C_SCL_Pin, GPIO_PIN_RESET); \
    } while (0) /* SCL */

#define I2C_SDA(x)                                                                                                                               \
    do                                                                                                                                           \
    {                                                                                                                                            \
        x ? HAL_GPIO_WritePin(I2C_SDA_GPIO_Port, I2C_SDA_Pin, GPIO_PIN_SET) : HAL_GPIO_WritePin(I2C_SDA_GPIO_Port, I2C_SDA_Pin, GPIO_PIN_RESET); \
    } while (0) /* SDA */

#define I2C_READ_SDA HAL_GPIO_ReadPin(I2C_SDA_GPIO_Port, I2C_SDA_Pin) /* 读取SDA */

typedef enum
{
    ACK = 0,
    NACK = 1,
} AckType;

typedef enum
{
    WRITE = 0,
    READ = 1,
} RW;

void i2cStart(void);
void i2cStop(void);
uint8_t i2cWaitAck(void);
void i2cAck(void);
void i2cNAck(void);
void i2cSendByte(uint8_t data);
uint8_t i2cReadByte(void);

#define REPLY(x) x? i2cNAck():i2cAck();

#endif
