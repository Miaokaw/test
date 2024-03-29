#ifndef __REMOTE_H__
#define __REMOTE_H__

#include "main.h"

#define REMOTE_ID 0
#define REMOTE_READ_DATA HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)

typedef enum
{
    ONE = 69,
    TWO = 70,
    THREE = 71,
    FOUR = 68,
    FIVE = 64,
    SIX = 67,
    SEVEN = 7,
    EIGHT = 21,
    NINE = 9,
    ZERO = 25,
    POUND = 13,
    STAR = 22,
    UP = 24,
    DOWN = 82,
    LEFT = 8,
    RIGHT = 90,
    OK = 28,
    NOTHING = 0,
}KEYtype;

extern uint8_t remoteFlag;
extern uint32_t remoteData; /* ������յ������� */
extern uint8_t remoteCnt;  /* �������µĴ��� */

extern uint8_t lastSta;

uint8_t remoteScan(void);

#endif  /* __REMOTE_H__ */ 
