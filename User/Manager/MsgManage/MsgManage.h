#ifndef __MsgMANAGE_H__
#define __MsgMANAGE_H__

#include "main.h"

#define USART1_RXBUFFER_LEN 200   /* 定义最大接收字节数 200 */
#define USART1_HAL_RXBUFFER_LEN 1 /* 缓存大小 */

#define SERVO_RXBUFFER_LEN 10

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
