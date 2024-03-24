#include "Beep.h"

void beepBeep(uint8_t num)
{
    while(num > 0)
    {
        BEEP(1);
        HAL_Delay(250);
        BEEP(0);
        HAL_Delay(250);
        num--;
    }
}
