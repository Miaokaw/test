#include "MsgManage.h"

Usart1Data usart1Data;
ServoData servoData = {0};

FormData OpennMvData;

union floatType
{
	uint8_t c[4];
	float f;
} globaFdata;

void FormDataInit(FormData *Data)
{
	for (uint8_t i = 0; i < 20; i++)
	{
		Data->RxBuffer[i] = 0x00;
	}
	Data->frame_head[0] = 0x55;
	Data->frame_head[1] = 0x12;
	Data->frame_tail = 0x55;
	Data->color = 0x00;
	Data->shape = 0x00;
	Data->cx = 0;
	Data->cy = 0;
	Data->distanse = 0;
	Data->area = 0;
}

float getFloat(uint8_t *point)
{
	for (uint8_t i = 0; i < 4; i++)
	{
		globaFdata.c[i] = point[i];
	}
	return globaFdata.f;
}

void OpenMvDataProcess(FormData *Data)
{
	/* 检查帧头帧尾*/
	if (Data->RxBuffer[0] != OpennMvData.frame_head[0])
		return;
	if (Data->RxBuffer[1] != OpennMvData.frame_head[1])
		return;
	if (Data->RxBuffer[20] != OpennMvData.frame_tail)
		return;
	Data->color = Data->RxBuffer[2];
	Data->shape = Data->RxBuffer[3];
	Data->cx = getFloat(&Data->RxBuffer[4]);
	Data->cy = getFloat(&Data->RxBuffer[8]);
	Data->distanse = getFloat(&Data->RxBuffer[12]);
	Data->area = getFloat(&Data->RxBuffer[16]);
}

/**
 * @brief       串口数据接收回调函数
                数据处理在这里进行
 * @param       huart:串口句柄
 * @retval      无
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)                    /* 如果是串口1 */
    {
        if ((usart1Data.rxFlag & 0x8000) == 0)             /* 接收未完成 */
        {
            if (usart1Data.rxFlag & 0x4000)                /* 接收到了0x0d（即回车键） */
            {
                if (usart1Data.halBuffer[0] != 0x0a)             /* 接收到的不是0x0a（即不是换行键） */
                {
                    usart1Data.rxFlag = 0;                 /* 接收错误,重新开始 */
                }
                else                                    /* 接收到的是0x0a（即换行键） */
                {
                    usart1Data.rxFlag |= 0x8000;           /* 接收完成了 */
                }
            }
            else                                        /* 还没收到0X0d（即回车键） */
            {
                if (usart1Data.halBuffer[0] == 0x0d)
                    usart1Data.rxFlag |= 0x4000;
                else
                {
                    usart1Data.rxBuffer[usart1Data.rxFlag & 0X3FFF] = usart1Data.halBuffer[0];
                    usart1Data.rxFlag++;

                    if (usart1Data.rxFlag > (USART1_RXBUFFER_LEN - 1))
                    {
                        usart1Data.rxFlag = 0;             /* 接收数据错误,重新开始接收 */
                    }
                }
            }
        }
    }
}

/**
 * @brief 数据初始化
 *
 * @param Data
 * @retval 无
 */
void ServoDataInit(ServoData *Data)
{
	for (uint8_t i = 0; i < SERVO_RXBUFFER_LEN; i++)
		Data->rxBuffer[i] = 0;
	Data->rxFlag = 0;
	Data->rxLen = 0;
}

#pragma import(__use_no_semihosting)

struct __FILE
{
	int handle;
	/* Whatever you require here. If the only file you are using is */
	/* standard output using printf() for debugging, no file handling */
	/* is required. */
};

int _ttywrch(int ch)
{
	ch = ch;
	return ch;
}

void _sys_exit(int x)
{
	x = x;
}

char *_sys_command_string(char *cmd, int len)
{
	return NULL;
}

FILE __stdout;

int fputc(int ch, FILE *f)
{
	while ((USART1->SR & 0X40) == 0)
		; /* �ȴ���һ���ַ�������� */

	USART1->DR = (uint8_t)ch; /* ��Ҫ���͵��ַ� ch д�뵽DR�Ĵ��� */
	return ch;
}

void usart3Print(char *ch, uint8_t len){
    HAL_UART_Transmit(&huart3, (uint8_t *)ch, len, 0xFF);
    return ;
}
