#include "UsartManage.h"

Usart1Data usart1Data;
ServoData servoData = {0};

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
