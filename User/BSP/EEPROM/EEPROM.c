#include "EEPROM.h"
#include "i2c.h"

void eepromPageWrite(uint8_t addr, uint8_t *data, uint8_t len)
{
    i2cStart();
    i2cSendByte(EEPROM_ADDR + WRITE);
    i2cWaitAck();
    i2cSendByte(addr);
    i2cWaitAck();
    for (uint8_t i = 0; i < len; i++)
    {
        i2cSendByte(data[i]);
        i2cWaitAck();
    }
    i2cStop();
    HAL_Delay(10);
}

void eepromSequentialRead(uint8_t addr, uint8_t *buffer, uint8_t len)
{
    i2cStart();
    i2cSendByte(EEPROM_ADDR + WRITE);
    i2cWaitAck();
    i2cSendByte(addr);
    i2cWaitAck();
    i2cStart();
    i2cSendByte(EEPROM_ADDR + READ);
    i2cWaitAck();
    for (uint8_t i = 0; i < len - 1; i++)
    {
        buffer[i] = i2cReadByte();
        REPLY(ACK);
    }
    buffer[len - 1] = i2cReadByte();
    REPLY(NACK);
    i2cStop();
}

uint8_t eepromTest(void)
{
    uint8_t temp = 0x00;
    uint8_t data = 0x55;
    eepromSequentialRead(0xFF, &temp, 1);
    if (temp == 0x55)
        return 0;
    eepromPageWrite(0xFF, &data, 1);
    eepromSequentialRead(0xFF, &temp, 1);
    if (temp == 0x55)
        return 0;
    return 1;
}
