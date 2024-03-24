#ifndef __LED_H__
#define __LED_H__

#include "main.h"

#define LED(x)                                                                                                                      \
    do                                                                                                                               \
    {                                                                                                                                \
        x ? HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET) : HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET); \
    } while (0)

#define LED_TOGGLE()                                 \
    do                                                \
    {                                                 \
        HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin); \
    } while (0)


#endif /*__LED_H__*/
