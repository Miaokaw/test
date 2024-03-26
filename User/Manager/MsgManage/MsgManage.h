#ifndef __MsgMANAGE_H__
#define __MsgMANAGE_H__

#include "main.h"

#define USART1_RXBUFFER_LEN 200   /* 定义最大接收字节数 200 */
#define USART1_HAL_RXBUFFER_LEN 1 /* 缓存大小 */

#define SERVO_RXBUFFER_LEN 10

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

typedef struct _ServoData
{
    uint8_t rxFlag;
    uint8_t rxLen;
    uint8_t rxBuffer[SERVO_RXBUFFER_LEN];
} ServoData;

void ServoDataInit(ServoData *Data);

extern ServoData servoData;

typedef struct _Usart1Data
{
    uint16_t rxFlag;
    uint8_t halBuffer[USART1_HAL_RXBUFFER_LEN];
    uint8_t rxBuffer[USART1_RXBUFFER_LEN];
} Usart1Data;

extern Usart1Data usart1Data;

#endif /*__USARTMANAGE_H__*/
