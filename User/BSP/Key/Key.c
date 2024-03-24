#include "Key.h"

uint8_t keyScan(uint8_t mode)
{
    static uint8_t keyUp = 1;
    uint8_t keyVal = 0;

    if (keyUp && (KEY_UP == 1 || KEY0 == 1 || KEY1 == 1))
    {
        HAL_Delay(10);
        keyUp = 0;
        
        if (KEY_UP == 1)
            keyVal = KEY_UP_PRES;

        if (KEY0 == 1)
            keyVal = KEY0_PRES;

        if (KEY1 == 1)
            keyVal = KEY1_PRES;
        
    }
    else if (KEY_UP == 0 &&KEY0 == 0 && KEY1 == 0) /* 没有任何按键按下, 标记按键松开 */
    {
        keyUp = 1;
    }

    return keyVal; /* 返回键值 */
}


