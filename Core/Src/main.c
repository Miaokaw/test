/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
#include "main.h"
#include "can.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../../User/BSP/Beep/Beep.h"
#include "../../User/BSP/Led/Led.h"
#include "../../User/BSP/Key/Key.h"
#include "../../User/BSP/EEPROM/EEPROM.h"
#include "../../User/BSP/Remote/Remote.h"
#include "../../User/APP/Menu/Menu.h"
#include "../../User/Tools/Delay/Delay.h"
#include "../../User/Tools/Tools/TOOLS.h"
#include "../../User/Tools/USMART/usmart.h"
#include "../../User/Control/ZDTmotorControl/ZDTmotorControl.h"
#include "../../User/Control/SteppingMotorControl/SteppingMotorControl.h"
#include "../../User/Manager/MsgManage/MsgManage.h"
#include "../../User/Manager/TimManage/TimManage.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t key = 0;
uint8_t ledToggleTick = 0;
uint8_t tbuf[40];
char *str;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_FSMC_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM8_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_CAN_Init();
  MX_TIM5_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
  mallocInit();
  motorInit();
  usmart_dev.init(72);
  FormDataInit(&OpennMvData);
  beepBeep(getMemoryUsage(OUT));
  beepBeep(eepromTest());
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    key = remoteScan();

        if (key)
        {
            switch (key)
            {
            case 69:
                str = "1    ";
                motorMoveFast(&motor1,100,400);
                break;
            case 70:
                str = "2    ";
                motorMoveFast(&motor1,100,-400);
                break;
            case 71:
                str = "3    ";
                motorMove(&motor2,800,1.5,1.5,3200);
                waitMotor(2);
                break;
            case 68:
                str = "4    ";
                motorMove(&motor2,800,1,1,-3200);
                waitMotor(2);
                break;
            case 64:    
                str = "5    ";
                break;
            case 67:
                str = "6    ";
                break;
            case 7:
                str = "7    ";
                break;
            case 21:
                str = "8    ";
                break;
            case 9:
                str = "9    ";
                break;
            case 25:
                str = "0    ";
                break;
            case 13:
                str = "#    ";
                break;
            case 22:
                str = "*    ";
                break;
            case 24:
                str = "UP   ";
                break;
            case 82:
                str = "DOWM ";
                break;
            case 8:
                str = "LEFT ";
                break;
            case 90:
                str = "RIGHT";
                break;
            case 28:
                str = "OK   ";
                break;
            default:
                str = "NULL ";
                break;
            }
        }
        else
        {
            HAL_Delay(10);
        }

        ledToggleTick++;

        if (ledToggleTick == 50)
        {
            ledToggleTick = 0;
            lastSta = 0;
            LED_TOGGLE(); /* LED0闪烁 */
        }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
