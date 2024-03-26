#ifndef __MYUSART_H__
#define __MYUSART_H__

#include "stdint.h"
#include "string.h"

#define FORMDATA_RXBUFFER_LEN 30

typedef struct _FormData
{
	uint8_t Rx_flag;							//接收完成标志
	uint8_t Rx_len;								//接收长度
	uint8_t frame_head[2];						//帧头
	uint8_t frame_tail;							//帧尾
	uint8_t color, shape;
	float cx, cy, distanse, area;
	uint8_t RxBuffer[FORMDATA_RXBUFFER_LEN];				//数据存储
} FormData;

void OpenMvData_Process(FormData *Data);
void FormData_Init(FormData *Data);
float getFloat (uint8_t *point);
extern FormData OpennMv_Data;

#endif /*__MYUSART_H__*/
