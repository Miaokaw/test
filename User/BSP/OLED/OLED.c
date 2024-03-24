#include "OLED.h"

void oledByteWrite(uint8_t addr, uint8_t data)
{
	i2cStart();
	i2cSendByte(OLED_ADDRESS + WRITE);
	i2cWaitAck();
	i2cSendByte(addr);
	i2cWaitAck();
	i2cSendByte(data);
	i2cWaitAck();
	i2cStop();
}

void oledWriteCmd(uint8_t command) // 写命令
{
	oledByteWrite(0x00, command);
}

void oledWriteDat(uint8_t data) // 写数据
{
	oledByteWrite(0x40, data);
}

void oledInit(void)
{
	HAL_Delay(100); // 这里的延时很重要

	oledWriteCmd(0xAE); // display off
	oledWriteCmd(0x20); // Set Memory Addressing Mode
	oledWriteCmd(0x10); // 00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	oledWriteCmd(0xb0); // Set Page Start Address for Page Addressing Mode,0-7
	oledWriteCmd(0xc8); // Set COM Output Scan Direction
	oledWriteCmd(0x00); //---set low column address
	oledWriteCmd(0x10); //---set high column address
	oledWriteCmd(0x40); //--set start line address
	oledWriteCmd(0x81); //--set contrast control register
	oledWriteCmd(0xff); // 亮度调节 0x00~0xff
	oledWriteCmd(0xa1); //--set segment re-map 0 to 127
	oledWriteCmd(0xa6); //--set normal display
	oledWriteCmd(0xa8); //--set multiplex ratio(1 to 64)
	oledWriteCmd(0x3F); //
	oledWriteCmd(0xa4); // 0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	oledWriteCmd(0xd3); //-set display offset
	oledWriteCmd(0x00); //-not offset
	oledWriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
	oledWriteCmd(0xf0); //--set divide ratio
	oledWriteCmd(0xd9); //--set pre-charge period
	oledWriteCmd(0x22); //
	oledWriteCmd(0xda); //--set com pins hardware configuration
	oledWriteCmd(0x12);
	oledWriteCmd(0xdb); //--set vcomh
	oledWriteCmd(0x20); // 0x20,0.77xVcc
	oledWriteCmd(0x8d); //--set DC-DC enable
	oledWriteCmd(0x14); //
	oledWriteCmd(0xaf); //--turn on oled panel
    oledCLS();
}

void oledSetPos(uint8_t x, uint8_t y) // 设置起始点坐标
{
	oledWriteCmd(0xb0 + y);
	oledWriteCmd(((x & 0xf0) >> 4) | 0x10);
	oledWriteCmd((x & 0x0f) | 0x01);
}

void oledFill(uint8_t fill_Data) // 全屏填充
{
	uint8_t m, n;
	for (m = 0; m < 8; m++)
	{
		oledWriteCmd(0xb0 + m); // page0-page1
		oledWriteCmd(0x00);		// low column start address
		oledWriteCmd(0x10);		// high column start address
		for (n = 0; n < 128; n++)
		{
			oledWriteDat(fill_Data);
		}
	}
}

void oledCLS(void) // 清屏
{
	oledFill(0x00);
}

//--------------------------------------------------------------
// Prototype      : void OLED_ON(void)
// Calls          :
// Parameters     : none
// Description    : 将OLED从休眠中唤醒
//--------------------------------------------------------------
void oledON(void)
{
	oledWriteCmd(0X8D); // 设置电荷泵
	oledWriteCmd(0X14); // 开启电荷泵
	oledWriteCmd(0XAF); // OLED唤醒
}

//--------------------------------------------------------------
// Prototype      : void OLED_OFF(void)
// Calls          :
// Parameters     : none
// Description    : 让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
//--------------------------------------------------------------
void oledOFF(void)
{
	oledWriteCmd(0X8D); // 设置电荷泵
	oledWriteCmd(0X10); // 关闭电荷泵
	oledWriteCmd(0XAE); // OLED休眠
}

//--------------------------------------------------------------
// Prototype      : void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t ch[], uint8_t TextSize)
// Calls          :
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); ch[] -- 要显示的字符串; TextSize -- 字符大小(1:6*8 ; 2:8*16)
// Description    : 显示codetab.h中的ASCII字符,有6*8和8*16可选择
//--------------------------------------------------------------
void oledShowStr(uint8_t x, uint8_t y, unsigned char ch[], uint8_t textSize)
{
	uint8_t c = 0, i = 0, j = 0;
	switch (textSize)
	{
	case 1:
	{
		while (ch[j] != '\0')
		{
			c = ch[j] - 32;
			if (x > 126)
			{
				x = 0;
				y++;
			}
			oledSetPos(x, y);
			for (i = 0; i < 6; i++)
				oledWriteDat(F6x8[c][i]);
			x += 6;
			j++;
		}
	}
	break;
	case 2:
	{
		while (ch[j] != '\0')
		{
			c = ch[j] - 32;
			if (x > 120)
			{
				x = 0;
				y++;
			}
			oledSetPos(x, y);
			for (i = 0; i < 8; i++)
				oledWriteDat(F8X16[c * 16 + i]);
			oledSetPos(x, y + 1);
			for (i = 0; i < 8; i++)
				oledWriteDat(F8X16[c * 16 + i + 8]);
			x += 8;
			j++;
		}
	}
	break;
	}
}

void oledShowFloat(uint8_t x, uint8_t y, float num, uint8_t textSize)
{
    oledShowStr(x, y, float2str(num ,4), textSize);
}
//--------------------------------------------------------------
// Prototype      : void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
// Calls          :
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); N:汉字在codetab.h中的索引
// Description    : 显示codetab.h中的汉字,16*16点阵
//--------------------------------------------------------------
void oledShowCN(uint8_t x, uint8_t y, uint8_t N)
{
	uint8_t wm = 0;
	uint32_t adder = 32 * N;
	oledSetPos(x, y);
	for (wm = 0; wm < 16; wm++)
	{
		oledWriteDat(F16x16[adder]);
		adder += 1;
	}
	oledSetPos(x, y + 1);
	for (wm = 0; wm < 16; wm++)
	{
		oledWriteDat(F16x16[adder]);
		adder += 1;
	}
}
//--------------------------------------------------------------
// Prototype      : void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
// Calls          :
// Parameters     : x0,y0 -- 起始点坐标(x0:0~127, y0:0~7); x1,y1 -- 起点对角线(结束点)的坐标(x1:1~128,y1:1~8)
// Description    : 显示BMP位图
//--------------------------------------------------------------
void oledDrawBMP(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t BMP[])
{
	unsigned int j = 0;
	uint8_t x, y;

	if (y1 % 8 == 0)
		y = y1 / 8;
	else
		y = y1 / 8 + 1;
	for (y = y0; y < y1; y++)
	{
		oledSetPos(x0, y);
		for (x = x0; x < x1; x++)
		{
			oledWriteDat(BMP[j++]);
		}
	}
}
