#include "Remote.h"
#include "tim.h"

/* 遥控器接收状态
 * [7]  : 收到了引导码标志
 * [6]  : 得到了一个按键的所有信息
 * [5]  : 保留
 * [4]  : 标记上升沿是否已经被捕获
 * [3:0]: 溢出计时器
 */
uint8_t remoteFlag = 0;
uint32_t remoteData = 0; /* 红外接收到的数据 */
uint8_t remoteCnt = 0;   /* 按键按下的次数 */
uint8_t lastSta = 0;
/**
 * @brief       处理红外按键(类似按键扫描)
 * @param       无
 * @retval      0   , 没有任何按键按下
 *              其他, 按下的按键键值
 */
uint8_t remoteScan(void)
{
    uint8_t sta = 0;
    uint8_t t1, t2;

    if (remoteFlag & (1 << 6)) /* 得到一个按键的所有信息了 */
    {
        t1 = remoteData;               /* 得到地址码 */
        t2 = (remoteData >> 8) & 0xff; /* 得到地址反码 */

        if ((t1 == (uint8_t)~t2) && t1 == REMOTE_ID) /* 检验遥控识别码(ID)及地址 */
        {
            t1 = (remoteData >> 16) & 0xff;
            t2 = (remoteData >> 24) & 0xff;

            if (t1 == (uint8_t)~t2 && t1 != lastSta)
            {
                sta = t1; /* 键值正确 */
            }
        }

        if ((sta == 0) || ((remoteFlag & 0X80) == 0)) /* 按键数据错误/遥控已经没有按下了 */
        {
            remoteFlag &= ~(1 << 6); /* 清除接收到有效按键标识 */
            remoteCnt = 0;           /* 清除按键次数计数器 */
        }
    }
    if (sta != 0)
    {
        lastSta = sta;
    }
    return sta;
}
