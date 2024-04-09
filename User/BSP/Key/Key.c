#include "Key.h"

uint8_t keyScan(uint8_t mode)
{
    static uint8_t keyUp = 1;
    uint8_t keyVal = 0;

    if (mode) 
        keyUp = 1;
    
    if (keyUp && (KEY_UP|| KEY0 || KEY1))
    {
        HAL_Delay(10);
        keyUp = 0;
        
        if (KEY_UP)
            keyVal = KEY_UP_PRES;

        if (KEY0)
            keyVal = KEY0_PRES;

        if (KEY1)
            keyVal = KEY1_PRES;
        
    }
    else if (KEY_UP == 0 &&KEY0 == 0 && KEY1 == 0) /* 没有任何按键按下, 标记按键松开 */
    {
        keyUp = 1;
    }

    return keyVal; /* 返回键值 */
}

//uint8_t matrixKeyScan(uint8_t mode)

//{
//    uint8_t row = 0;
//    uint8_t col = 0;
//    uint8_t matrixKeyVal = 0;
//    static uint8_t matrixKeyUp = 1;
//    WRITE_ROW(1);
//    if (matrixKeyUp && (READ(COL1)|| READ(COL2) || READ(COL3) || READ(COL4))
//    {
//        HAL_Delay(10);
//        matrixKeyUp = 0;
//        
//        if (READ(COL1))
//            col = 1;
//        if (READ(COL2))
//            col = 2;
//        if (READ(COL3))
//            col = 3;
//        if (READ(COL4))
//            col = 4;
//        WRITE_ROW(0);
//        WRITE_COL(1);
//        if (matrixKeyUp && (READ(ROW1)|| READ(ROW2) || READ(ROW3) || READ(ROW4))
//        {
//            if (READ(ROW1))
//                row = 1;
//            if (READ(ROW2))
//                row = 2;
//            if (READ(ROW3))
//                row = 3;
//            if (READ(ROW4))
//                row = 4;
//            matrixKeyVal = (row - 1) * 4 + col;
//        }
//    }
//    else if (READ(COL1) == 0 && READ(COL2) == 0 && READ(COL3) == 0 && READ(COL4) == 0)
//    {
//        matrixKeyUp = 1;
//    }
//    
//    return matrixKeyVal;
//}


