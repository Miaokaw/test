#include "MsgManage.h"

Usart1Data usart1Data;
ServoData servoData = {0};

FormData OpennMv_Data;

union floatType{
	uint8_t c[4];
	float f;
}globaFdata;

void FormData_Init(FormData *Data)
{
	for(uint8_t i=0; i<20; i++){
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

float getFloat (uint8_t *point){
	for(uint8_t i=0;i<4;i++){
		globaFdata.c[i] = point[i];
	}
	return globaFdata.f;
}

void OpenMvData_Process(FormData *Data){
	//检查帧头帧尾
	if(Data->RxBuffer[0] != OpennMv_Data.frame_head[0]) return;
	if(Data->RxBuffer[1] != OpennMv_Data.frame_head[1]) return;
	if(Data->RxBuffer[20] != OpennMv_Data.frame_tail) return;
	Data->color = Data->RxBuffer[2];
	Data->shape = Data->RxBuffer[3];
	Data->cx = getFloat(&Data->RxBuffer[4]);
	Data->cy = getFloat(&Data->RxBuffer[8]);
	Data->distanse = getFloat(&Data->RxBuffer[12]);
	Data->area = getFloat(&Data->RxBuffer[16]);
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
