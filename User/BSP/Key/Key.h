#ifndef __KEY_H__
#define __KEY_H__

#include "main.h"

#define KEY0        HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin)     /* 读取KEY0引脚 */
#define KEY1        HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)     /* 读取KEY1引脚 */
#define KEY2        HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin)     /* 读取KEY2引脚 */
#define KEY3        HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin)     /* 读取KEY3引脚 */
#define KEY_UP      HAL_GPIO_ReadPin(KEY_UP_GPIO_Port, KEY_UP_Pin)     /* 读取WKUP引脚 */

#define KEY0_PRES    1              /* KEY0按下 */
#define KEY1_PRES    2              /* KEY1按下 */
#define KEY2_PRES    3              /* KEY2按下 */
#define KEY3_PRES    4              /* KEY3按下 */
#define KEY_UP_PRES  5              /* KEY_UP按下(即WK_UP) */

uint8_t  keyScan(uint8_t mode);

#endif /*__KEY_H__*/
