#ifndef __OLED_H__
#define __OLED_H__

#include "i2c.h"
#include "../../Tools/Tools/Tools.h"
#include "OLEDLAB.h"

#define OLED_ADDRESS	0x78 //通过调整0R电阻,屏可以0x78和0x7A两个地址 -- 默认0x78

void oledWriteByte(uint8_t addr,uint8_t data);
void oledWriteCmd(uint8_t I2C_Command);
void oledWriteDat(uint8_t I2C_Data);
void oledInit(void);
void oledSetPos(uint8_t x, uint8_t y);
void oledFill(uint8_t fill_Data);
void oledCLS(void);
void oledON(void);
void oledOFF(void);
void oledShowStr(uint8_t x, uint8_t y, unsigned char ch[], uint8_t TextSize);
void oledShowFloat(uint8_t x, uint8_t y, float num, uint8_t textSize);
void oledShowCN(uint8_t x, uint8_t y, uint8_t N);
void oledDrawBMP(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t BMP[]);

#endif /*__OLED_H__*/
