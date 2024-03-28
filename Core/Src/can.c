/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    can.c
 * @brief   This file provides code for the configuration
 *          of the CAN instances.
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
#include "can.h"

/* USER CODE BEGIN 0 */
CAN_TxHeaderTypeDef txMsg;
CAN_RxHeaderTypeDef rxMsg;
bool canRxFlag;
uint8_t canRxBuf[8];
/* USER CODE END 0 */

CAN_HandleTypeDef hcan;

/* CAN init function */
void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = BRP;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_9TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_8TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */
  __IO uint8_t ID, maskID;
  __IO uint16_t idHigh, idLow;
  __IO uint16_t maskIdHigh, maskIdLow;

  ID = (0x00);
  maskID = (0x00);

  idHigh = (uint16_t)((uint16_t)ID >> 5);
  idLow = (uint16_t)((uint16_t)ID << 11) | CAN_ID_EXT;

  maskIdHigh = (uint16_t)((uint16_t)maskID >> 5);
  maskIdLow = (uint16_t)((uint16_t)maskID << 11) | CAN_ID_EXT;

  CAN_FilterTypeDef sFilterConfig;
  sFilterConfig.FilterBank = 1;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh = idHigh;
  sFilterConfig.FilterIdLow = idLow;
  sFilterConfig.FilterMaskIdHigh = maskIdHigh;
  sFilterConfig.FilterMaskIdLow = maskIdLow;
  sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;
  HAL_CAN_ConfigFilter(&hcan, &sFilterConfig);
  HAL_CAN_Start(&hcan);
  /* USER CODE END CAN_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN GPIO Configuration
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN GPIO Configuration
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
uint8_t canSendCmd(uint8_t *cmd, uint8_t len)
{
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t k = 0; 
    uint8_t packNum =0;
    uint8_t *msg;
    uint32_t txMailBox = CAN_TX_MAILBOX0;
    
    j = len - 2;
    
    while(i < j)
    {
        k = j - i;
        
        txMsg.StdId = 0x00;
        txMsg.ExtId = ((uint32_t)cmd[0] << 8) | (uint32_t)packNum;
        txMsg.IDE = CAN_ID_EXT;
        txMsg.RTR = CAN_RTR_DATA;
        
        msg[0] = cmd[1];
        
        if(k < 8)
        {
            for (uint8_t l = 0; l < k; l++, i++)
                msg[l + 1] = cmd[i + 2];
            txMsg.DLC = k + 1;
        }
        else
        {
            for (uint8_t l = 0; l < 7; l++, i++)
                msg[l + 1] = cmd[i + 2];
            txMsg.DLC = 8;
        }
        if (HAL_CAN_AddTxMessage(&hcan, &txMsg, msg, &txMailBox) != HAL_OK)
            return 1;
        
    }
    return 0;
}




uint8_t canReceiveMsg(uint32_t id, uint8_t *buf)
{
  if (HAL_CAN_GetRxFifoFillLevel(&hcan, CAN_RX_FIFO0) == 0)
    return 0;
  if (HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &rxMsg, buf) != HAL_OK)
    return 0;
  if (rxMsg.StdId != id || rxMsg.IDE != CAN_ID_STD || rxMsg.RTR != CAN_RTR_DATA)
    return 0;

  return rxMsg.DLC;
}
/* USER CODE END 1 */
