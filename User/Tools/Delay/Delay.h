#ifndef __DELAY_H__
#define __DELAY_H__

#include "main.h"

#define HCLK 72

void usDelay(uint32_t nus);            /* —” ±nus */
void msDelay(uint16_t nms);            /* —” ±nms */
//void HAL_Delay(uint32_t delay);

#endif /*__DELAY_H__*/
