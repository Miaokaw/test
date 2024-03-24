/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    rtc.h
 * @brief   This file contains all the function prototypes for
 *          the rtc.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RTC_H__
#define __RTC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "../../User/BSP/OLED/OLED.h"
/* USER CODE END Includes */

extern RTC_HandleTypeDef hrtc;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_RTC_Init(void);

/* USER CODE BEGIN Prototypes */
  typedef struct _Time
  {
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    /* 公历年月日周 */
    uint16_t year;
    uint8_t month;
    uint8_t date;
    uint8_t week;
  } Time;

  extern Time time; /* 时间结构�? */

  extern char *weekdays[];

  static uint8_t
  rtcIsLeapYear(uint16_t year);                                                                                /* 判断当前年份是不是闰�?? */
  static long rtcDate2Sec(uint16_t syear, uint8_t smon, uint8_t sday, uint8_t hour, uint8_t min, uint8_t sec); /* 将年月日时分秒转换成秒钟�?? */

  /* 接口函数 */
  void rtcGetTime(void);                                                                                   /* 获取RTC时间信息 */
  uint8_t rtcGetWeek(uint16_t year, uint8_t month, uint8_t day);                                           /* 根据年月日获取星期几 */
  uint8_t rtcSetTime(uint16_t syear, uint8_t smon, uint8_t sday, uint8_t hour, uint8_t min, uint8_t sec);  /* 设置时间 */
  uint8_t rtcSetAlarm(uint16_t syear, uint8_t smon, uint8_t sday, uint8_t hour, uint8_t min, uint8_t sec); /* 设置闹钟时间 */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __RTC_H__ */

