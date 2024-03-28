#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "main.h"

#define EEPROM_ADDR 0xA0

void eepromPageWrite(uint8_t addr, uint8_t *data, uint8_t len);
void eepromSequentialRead(uint8_t addr, uint8_t *buffer, uint8_t len);
uint8_t eepromTest(void);

#endif /*__EEPROM_H__*/
