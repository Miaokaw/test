#ifndef __DELAY_H__
#define __DELAY_H__

#include "main.h"

#define HCLK 72

void usDelay(uint32_t nus);            /* ��ʱnus */
void msDelay(uint16_t nms);            /* ��ʱnms */
//void HAL_Delay(uint32_t delay);

#endif /*__DELAY_H__*/
