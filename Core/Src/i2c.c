#include "i2c.h"

static void i2cDelay(void)
{
    usDelay(2);
}

void i2cStart(void)
{
    I2C_SDA(1);
    I2C_SCL(1);
    i2cDelay();
    I2C_SDA(0);
    i2cDelay();
    I2C_SCL(0);
    i2cDelay();
}

void i2cStop(void)
{
    I2C_SDA(0);
    i2cDelay();
    I2C_SCL(1);
    i2cDelay();
    I2C_SDA(1);
    i2cDelay();
}

uint8_t i2cWaitAck(void)
{
    uint8_t waitTime = 0;
    AckType res = ACK;

    I2C_SDA(1);
    i2cDelay();
    I2C_SCL(1);
    i2cDelay();

    while (I2C_READ_SDA)
    {
        waitTime++;

        if (waitTime > 250)
        {
            i2cStop();
            res = NACK;
            break;
        }
    }

    I2C_SCL(0);
    i2cDelay();
    return res;
}

void i2cAck(void)
{
    I2C_SDA(0);
    i2cDelay();
    I2C_SCL(1);
    i2cDelay();
    I2C_SCL(0);
    i2cDelay();
    I2C_SDA(1);
    i2cDelay();
}

void i2cNAck(void)
{
    I2C_SDA(1);
    i2cDelay();
    I2C_SCL(1);
    i2cDelay();
    I2C_SCL(0);
    i2cDelay();
}

void i2cSendByte(uint8_t data)
{
    uint8_t t;
    for (t = 0; t < 8; t++)
    {
        I2C_SDA((data & 0x80) >> 7);
        i2cDelay();
        I2C_SCL(1);
        i2cDelay();
        I2C_SCL(0);
        data <<= 1;
    }
    I2C_SDA(1);
}

uint8_t i2cReadByte(void)
{
    uint8_t i, receive = 0;

    for (i = 0; i < 8; i++)
    {
        receive <<= 1;
        I2C_SCL(1);
        i2cDelay();

        if (I2C_READ_SDA)
        {
            receive++;
        }

        I2C_SCL(0);
        i2cDelay();
    }
    return receive;
}
