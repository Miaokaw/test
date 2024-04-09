#ifndef __KEY_H__
#define __KEY_H__

#include "main.h"

#define KEY0        HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin)     /* 读取KEY0引脚 */
#define KEY1        HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)     /* 读取KEY1引脚 */
#define KEY2        HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin)     /* 读取KEY2引脚 */
#define KEY3        HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin)     /* 读取KEY3引脚 */
#define KEY_UP      HAL_GPIO_ReadPin(KEY_UP_GPIO_Port, KEY_UP_Pin)     /* 读取WKUP引脚 */
    
#define ROW1 ROW1_GPIO_Port, ROW1_Pin
#define ROW2 ROW2_GPIO_Port, ROW2_Pin
#define ROW3 ROW3_GPIO_Port, ROW3_Pin
#define ROW4 ROW4_GPIO_Port, ROW4_Pin

#define COL1 COL1_GPIO_Port, COL1_Pin
#define COL2 COL2_GPIO_Port, COL2_Pin
#define COL3 COL3_GPIO_Port, COL3_Pin
#define COL4 COL4_GPIO_Port, COL4_Pin
    
#define READ(x) HAL_GPIO_ReadPin(x)
#define WRITE(x,y) do{ y ? HAL_GPIO_WritePin(x, GPIO_PIN_SET) : HAL_GPIO_WritePin(x, GPIO_PIN_RESET);}while(0) 

#define WRITE_ROW(x) do{WRITE(ROW1,x);WRITE(ROW2,x);WRITE(ROW3,x);WRITE(ROW4,x);}while(0)
#define WRITE_COL(x) do{WRITE(COL1,x);WRITE(COL2,x);WRITE(COL3,x);WRITE(COL4,x);}while(0)

#define KEY0_PRES    1              /* KEY0按下 */
#define KEY1_PRES    2              /* KEY1按下 */
#define KEY2_PRES    3              /* KEY2按下 */
#define KEY3_PRES    4              /* KEY3按下 */
#define KEY_UP_PRES  5              /* KEY_UP按下(即WK_UP) */

uint8_t  keyScan(uint8_t mode);

#endif /*__KEY_H__*/
