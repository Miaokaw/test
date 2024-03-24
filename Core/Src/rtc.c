/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    rtc.c
 * @brief   This file provides code for the configuration
 *          of the RTC instances.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "rtc.h"

/* USER CODE BEGIN 0 */
Time time;
char *weekdays[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saterday"};
/* USER CODE END 0 */

RTC_HandleTypeDef hrtc;

/* RTC init function */
void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */
  uint16_t flag = 0;
  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /* USER CODE BEGIN RTC_Init 1 */
  __HAL_RCC_BKP_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
  HAL_PWR_EnableBkUpAccess();
  flag = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1);
  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_NONE;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */
  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x16;
  sTime.Minutes = 0x10;
  sTime.Seconds = 0x0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_SATURDAY;
  DateToUpdate.Month = RTC_MONTH_MARCH;
  DateToUpdate.Date = 0x23;
  DateToUpdate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */
  if (flag != 0x5050)
  {
    rtcSetTime(2024, 3, 23, 17, 32, 0);
  }
  __HAL_RTC_ALARM_ENABLE_IT(&hrtc, RTC_IT_SEC);
  /* USER CODE END RTC_Init 2 */

}

void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspInit 0 */
  /* USER CODE END RTC_MspInit 0 */
    HAL_PWR_EnableBkUpAccess();
    /* Enable BKP CLK enable for backup registers */
    __HAL_RCC_BKP_CLK_ENABLE();
    /* RTC clock enable */
    __HAL_RCC_RTC_ENABLE();

    /* RTC interrupt Init */
    HAL_NVIC_SetPriority(RTC_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(RTC_IRQn);
  /* USER CODE BEGIN RTC_MspInit 1 */
    rtcGetTime(); /* 更新时间 */
    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x5050);
  /* USER CODE END RTC_MspInit 1 */
  }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspDeInit 0 */

  /* USER CODE END RTC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();

    /* RTC interrupt Deinit */
    HAL_NVIC_DisableIRQ(RTC_IRQn);
  /* USER CODE BEGIN RTC_MspDeInit 1 */

  /* USER CODE END RTC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
static uint8_t rtcIsLeapYear(uint16_t year)
{
  /* 闰年规则: 四年闰百年不闰，四百年又�???? */
  if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    return 1;
  return 0;
}
uint8_t rtcSetTime(uint16_t syear, uint8_t smon, uint8_t sday, uint8_t hour, uint8_t min, uint8_t sec)
{
  uint32_t secCount = 0;

  secCount = rtcDate2Sec(syear, smon, sday, hour, min, sec); /* 将年月日时分秒转换成总秒钟数 */

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_RCC_BKP_CLK_ENABLE();
  HAL_PWR_EnableBkUpAccess();
  /* 上面三步是必须的! */

  RTC->CRL |= 1 << 4; /* 允许配置 */

  RTC->CNTL = secCount & 0xffff;
  RTC->CNTH = secCount >> 16;

  RTC->CRL &= ~(1 << 4); /* 配置更新 */

  WAIT(__HAL_RTC_ALARM_GET_FLAG(&hrtc, RTC_FLAG_RTOFF)); /* 等待RTC寄存器操作完�????, 即等待RTOFF == 1 */

  return 0;
}

uint8_t rtcSetAlarm(uint16_t syear, uint8_t smon, uint8_t sday, uint8_t hour, uint8_t min, uint8_t sec)
{
  uint32_t secCount = 0;

  secCount = rtcDate2Sec(syear, smon, sday, hour, min, sec); /* 将年月日时分秒转换成总秒钟数 */

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_RCC_BKP_CLK_ENABLE();
  HAL_PWR_EnableBkUpAccess();
  /* 上面三步是必须的! */

  RTC->CRL |= 1 << 4; /* 允许配置 */

  RTC->ALRL = secCount & 0xffff;
  RTC->ALRH = secCount >> 16;

  RTC->CRL &= ~(1 << 4); /* 配置更新 */

  WAIT(__HAL_RTC_ALARM_GET_FLAG(&hrtc, RTC_FLAG_RTOFF)); /* 等待RTC寄存器操作完, 即等待RTOFF == 1 */

  return 0;
}

void rtcGetTime(void)
{
  static uint16_t dayCnt = 0;
  uint32_t secCount = 0;
  uint32_t temp = 0;
  uint16_t temp1 = 0;
  const uint8_t monthTable[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; /* 平年的月份日期表 */

  secCount = RTC->CNTH;
  secCount <<= 16;
  secCount += RTC->CNTL;

  temp = secCount / 86400; /* 得到天数(秒钟数对应的) */

  if (dayCnt != temp)
  {
    dayCnt = temp;
    temp1 = 1970;

    while (temp >= 365)
    {
      if (rtcIsLeapYear(temp1)) /* 是闰�? */
      {
        if (temp < 366)
          break;
        temp -= 366; /* 闰年的秒钟数 */
      }
      else
        temp -= 365; /* 平年 */
      temp1++;
    }

    time.year = temp1; /* 得到年份 */
    temp1 = 0;

    while (temp >= 28) /* 超过了一个月 */
    {
      if (rtcIsLeapYear(time.year) && temp1 == 1) /* 当年是不是闰�?2月份 */
      {
        if (temp < 29)
          break;
        temp -= 29; /* 闰年的秒钟数 */
      }
      else
      {
        if (temp < monthTable[temp1])
          break;
        temp -= monthTable[temp1]; /* 平年 */
      }
      temp1++;
    }
    time.month = temp1 + 1; /* 得到月份 */
    time.date = temp + 1;   /* 得到日期 */
  }

  temp = secCount % 86400;                                  /* 得到秒钟�???? */
  time.hour = temp / 3600;                                  /* 小时 */
  time.min = (temp % 3600) / 60;                            /* 分钟 */
  time.sec = (temp % 3600) % 60;                            /* 秒钟 */
  time.week = rtcGetWeek(time.year, time.month, time.date); /* 获取星期 */
}
uint8_t rtcGetWeek(uint16_t year, uint8_t month, uint8_t day)
{
  uint8_t week = 0;
  if (month < 3)
  {
    month += 12;
    --year;
  }
  week = (day + 1 + 2 * month + 3 * (month + 1) / 5 + year + (year >> 2) - year / 100 + year / 400) % 7;
  return week;
}
static long rtcDate2Sec(uint16_t syear, uint8_t smon, uint8_t sday, uint8_t hour, uint8_t min, uint8_t sec)
{
  uint32_t Y, M, D, X, T;
  signed char monx = smon; /* 将月份转换成带符号的�????, 方便后面运算 */

  if (0 >= (monx -= 2)) /* 1..12 -> 11,12,1..10 */
  {
    monx += 12; /* Puts Feb last since it has leap day */
    syear -= 1;
  }

  Y = (syear - 1) * 365 + syear / 4 - syear / 100 + syear / 400; /* 公元元年1到现在的闰年�???? */
  M = 367 * monx / 12 - 30 + 59;
  D = sday - 1;
  X = Y + M + D - 719162;                      /* 减去公元元年�????1970年的天数 */
  T = ((X * 24 + hour) * 60 + min) * 60 + sec; /* 总秒钟数 */
  return T;
}
/* USER CODE END 1 */
