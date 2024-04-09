#include "TimManage.h"
#include "tim.h"
#include "./../../User/Control/ZDTmotorControl/ZDTmotorControl.h"
#include "./../../User/BSP/Remote/Remote.h"


void readZDTMotor(void)
{
    for (uint8_t i = 1; i <= MOTOR_NUM; i++)
    {
        readSysParams(i, S_VEL);
        readSysParams(i, S_CPOS);
    }
}
void tenMsPeriodElapsedCallBack(void)
{
    readZDTMotor();
}
void remotePeriodElapsedCallBack(void)
{
    if (remoteFlag & 0x80) /* 上次有数据被接收到了 */
    {
        remoteFlag &= ~0X10; /* 取消上升沿已经被捕获标记 */

        if ((remoteFlag & 0X0F) == 0X00)
        {
            remoteFlag |= 1 << 6; /* 标记已经完成一次按键的键值信息采集 */
        }

        if ((remoteFlag & 0X0F) < 14)
        {
            remoteFlag++;
        }
        else
        {
            remoteFlag &= ~(1 << 7); /* 清空引导标识 */
            remoteFlag &= 0XF0;      /* 清空计数器 */
        }
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM6)
    {
        tenMsPeriodElapsedCallBack();
    }
    else if (htim->Instance == TIM5)
    {
        remotePeriodElapsedCallBack();
    }
}

void remoteCaptureCallBack(void)
{
    uint16_t dval; /* 下降沿时计数器的值 */

    if (REMOTE_READ_DATA) /* 上升沿捕获 */
    {
        __HAL_TIM_SET_CAPTUREPOLARITY(&htim5, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_FALLING); // CC4P=1 设置为下降沿捕获
        __HAL_TIM_SET_COUNTER(&htim5, 0);                                                       /* 清空定时器值 */
        remoteFlag |= 0X10;                                                                     /* 标记上升沿已经被捕获 */
    }
    else /* 下降沿捕获 */
    {
        dval = HAL_TIM_ReadCapturedValue(&htim5, TIM_CHANNEL_2);                               /* 读取CCR4也可以清CC4IF标志位 */
        __HAL_TIM_SET_CAPTUREPOLARITY(&htim5, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_RISING); /* 配置TIM4通道4上升沿捕获 */

        if (remoteFlag & 0X10) /* 完成一次高电平捕获 */
        {
            if (remoteFlag & 0X80) /* 接收到了引导码 */
            {

                if (dval > 300 && dval < 800) /* 560为标准值,560us */
                {
                    remoteData >>= 1;            /* 右移一位 */
                    remoteData &= ~(0x80000000); /* 接收到0 */
                }
                else if (dval > 1400 && dval < 1800) /* 1680为标准值,1680us */
                {
                    remoteData >>= 1;         /* 右移一位 */
                    remoteData |= 0x80000000; /* 接收到1 */
                }
                else if (dval > 2000 && dval < 3000) /* 得到按键键值增加的信息 2500为标准值2.5ms */
                {
                    remoteCnt++;        /* 按键次数增加1次 */
                    remoteFlag &= 0XF0; /* 清空计时器 */
                }
            }
            else if (dval > 4200 && dval < 4700) /* 4500为标准值4.5ms */
            {
                remoteFlag |= 1 << 7; /* 标记成功接收到了引导码 */
                remoteCnt = 0;        /* 清除按键次数计数器 */
            }
        }

        remoteFlag &= ~(1 << 4);
    }
}

/**
 * @brief       定时器输入捕获中断回调函数
 * @param       htim:定时器句柄
 * @retval      无
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM5)
    {
        remoteCaptureCallBack();
    }
}
