#ifndef __BEEP_H__
#define __BEEP_H__

#include "main.h"

#define BEEP(x)                                                                                                                      \
    do                                                                                                                               \
    {                                                                                                                                \
        x ? HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET) : HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET); \
    } while (0)

#define BEEP_TOGGLE()                                      \
    do                                                     \
    {                                                      \
        HAL_GPIO_TogglePin(BEEP_GPIO_Port, BEEP_GPIO_Pin); \
    } while (0) /* BEEP = !BEEP */

void beepBeep(uint8_t num);

#endif /*__BEEP_H__*/
