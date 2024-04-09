#include "Delay.h"
/**
 * @brief       延时nus
 * @param       nus: 要延时的us数.
 * @note        注意: nus的值,不要大于1864135us(最大值即2^24 / g_fac_us  @g_fac_us = 9)
 * @retval      无
 */
void usDelay(__IO uint32_t nTime)
{
int old_val,new_val,val;
 
    if(nTime > 900)
    {
        for(old_val = 0; old_val < nTime / 900; old_val++)
        {
            usDelay(900);
        }
        nTime = nTime%900;
    }
 
    old_val = SysTick->VAL;
    new_val = old_val - HCLK * nTime;
    if(new_val >= 0)
    {
        do
        {
            val = SysTick->VAL;
        }
        while((val < old_val) && (val >= new_val));
    }
    else
    {
        new_val += HCLK *1000;
        do
        {
            val = SysTick->VAL;
        }
        while((val <= old_val) || (val > new_val));
    }
}

/**
 * @brief       延时nms
 * @param       nms: 要延时的ms数 (0< nms <= 65535)
 * @retval      无
 */
void msDelay(uint16_t nms)
{
    uint32_t repeat = nms / 1000;   /*  这里用1000,是考虑到可能有超频应用,
                                     *  比如128Mhz的时候, usDelay最大只能延时1048576us左右了
                                     */
    uint32_t remain = nms % 1000;

    while (repeat)
    {
        usDelay(1000 * 1000);      /* 利用usDelay 实现 1000ms 延时 */
        repeat--;
    }

    if (remain)
    {
        usDelay(remain * 1000);    /* 利用usDelay, 把尾数延时(remain ms)给做了 */
    }
}

/**
  * @brief HAL库内部函数用到的延时
           HAL库的延时默认用Systick，如果我们没有开Systick的中断会导致调用这个延时后无法退出
  * @param Delay 要延时的毫秒数
  * @retval None
  */
void HAL_Delay(uint32_t delay)
{
     msDelay(delay);
}
