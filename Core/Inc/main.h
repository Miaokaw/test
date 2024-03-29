/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "malloc.h"
#include "../../User/BSP/OLED/OLED.h"
#include "../../User/BSP/Beep/Beep.h"
#include "../../User/BSP/Led/Led.h"
#include "../../User/BSP/Key/Key.h"
#include "../../User/BSP/EEPROM/EEPROM.h"
#include "../../User/BSP/Remote/Remote.h"
#include "../../User/APP/Menu/Menu.h"
#include "../../User/Tools/Delay/Delay.h"
#include "../../User/Tools/Tools/TOOLS.h"
#include "../../User/Control/Process/Process.h"
#include "../../User/Control/ServoControl/ServoControl.h"
#include "../../User/Control/SteppingMotorControl/SteppingMotorControl.h"
#include "../../User/Manager/MsgManage/MsgManage.h"
#include "../../User/Arm/ArmMoving.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PSC 18-1
#define ARR 0xFFFF - 1
#define USMART_ARR 1000
#define USMART_PSC 72 * 100 - 1
#define BRP 4
#define BEEP_Pin GPIO_PIN_2
#define BEEP_GPIO_Port GPIOE
#define KEY1_Pin GPIO_PIN_3
#define KEY1_GPIO_Port GPIOE
#define KEY0_Pin GPIO_PIN_4
#define KEY0_GPIO_Port GPIOE
#define LED_Pin GPIO_PIN_5
#define LED_GPIO_Port GPIOE
#define LIGHT_KEY6_Pin GPIO_PIN_6
#define LIGHT_KEY6_GPIO_Port GPIOE
#define LIGHT_KEY2_Pin GPIO_PIN_7
#define LIGHT_KEY2_GPIO_Port GPIOF
#define LIGHT_KEY3_Pin GPIO_PIN_8
#define LIGHT_KEY3_GPIO_Port GPIOF
#define LIGHT_KEY4_Pin GPIO_PIN_9
#define LIGHT_KEY4_GPIO_Port GPIOF
#define LIGHT_KEY5_Pin GPIO_PIN_10
#define LIGHT_KEY5_GPIO_Port GPIOF
#define MOTOR2_DIR_Pin GPIO_PIN_0
#define MOTOR2_DIR_GPIO_Port GPIOC
#define MOTOR1_DIR_Pin GPIO_PIN_1
#define MOTOR1_DIR_GPIO_Port GPIOC
#define MOTOR4_DIR_Pin GPIO_PIN_2
#define MOTOR4_DIR_GPIO_Port GPIOC
#define MOTOR3_DIR_Pin GPIO_PIN_3
#define MOTOR3_DIR_GPIO_Port GPIOC
#define KEY_UP_Pin GPIO_PIN_0
#define KEY_UP_GPIO_Port GPIOA
#define REMOTE_TIM_Pin GPIO_PIN_1
#define REMOTE_TIM_GPIO_Port GPIOA
#define MOTOR1_EN_Pin GPIO_PIN_4
#define MOTOR1_EN_GPIO_Port GPIOC
#define MOTOR3_EN_Pin GPIO_PIN_5
#define MOTOR3_EN_GPIO_Port GPIOC
#define MOTOR3_TIM_Pin GPIO_PIN_0
#define MOTOR3_TIM_GPIO_Port GPIOB
#define MOTOR4_EN_Pin GPIO_PIN_11
#define MOTOR4_EN_GPIO_Port GPIOF
#define MOTOR4_TIM_Pin GPIO_PIN_13
#define MOTOR4_TIM_GPIO_Port GPIOD
#define MOTOR2_EN_Pin GPIO_PIN_6
#define MOTOR2_EN_GPIO_Port GPIOG
#define FLASH_HOLD_Pin GPIO_PIN_7
#define FLASH_HOLD_GPIO_Port GPIOG
#define MOTOR2_TIM_Pin GPIO_PIN_6
#define MOTOR2_TIM_GPIO_Port GPIOC
#define MOTOR1_TIM_Pin GPIO_PIN_10
#define MOTOR1_TIM_GPIO_Port GPIOA
#define MOTOR5_EN_Pin GPIO_PIN_14
#define MOTOR5_EN_GPIO_Port GPIOG
#define MOTOR5_DIR_Pin GPIO_PIN_15
#define MOTOR5_DIR_GPIO_Port GPIOG
#define MOTOR5_TIM_Pin GPIO_PIN_3
#define MOTOR5_TIM_GPIO_Port GPIOB
#define I2C_SCL_Pin GPIO_PIN_8
#define I2C_SCL_GPIO_Port GPIOB
#define I2C_SDA_Pin GPIO_PIN_9
#define I2C_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define HCLKhz 72000000
#define FREQ 4000000
#define NULL 0
#define WAIT(flag)  \
    while (!(flag)) \
    {               \
    }

#define waitS(motor) WAIT(motor.state == IDLE)
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
