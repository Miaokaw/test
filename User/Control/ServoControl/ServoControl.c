/**
 * @file ServoControl.c
 * @author MSuperHero (320314609@qq.com)
 * @brief 舵机驱动（幻尔舵机驱动板）
 * @date 2024-01-27
 *
 */
#include "ServoControl.h"

#define UART_TIMEOUT 0xFFFF

Servo servo[4] = {0};

uint8_t servoTxBuf[SERVO_NUM * 3 + 7];
/**
 * @brief 舵机位置初始化
 * @fn 1500即为中间位置
 */
void servoInit(void)
{
    ServoDataInit(&servoData);
    for (uint8_t i = 0; i < SERVO_NUM; i++)
    {
        servo[i].servoID = i;  /* 下标即为编号 */
        servo[i].Angel = 1500; /* 90度 */
    }
    servoAction(ARM, 1200, 5000);
    servoAction(SPIN, 580, 5000);
    servoAction(CLAW, 1320, 5000);
}

void servoAction(Tools tool, uint16_t targetAngel, uint16_t runTime)
{
    switch (tool)
    {
        case ARM:
            runServoAction(0, targetAngel, runTime);
            runServoAction(1, 3000 - targetAngel, runTime);
            break;
        case SPIN:
            runServoAction(2, targetAngel, runTime);
            break;
        case CLAW:
            runServoAction(3, targetAngel, runTime);
            break;

    }
}
/**
 * @brief 控制单个舵机的转动
 * @retval 无
 */
void runServoAction(uint8_t servoNum, uint16_t targetAngel, uint16_t time)
{
    servoTxBuf[0] = servoTxBuf[1] = FRAME_HEAD;
    servoTxBuf[2] = 8;
    servoTxBuf[3] = CMD_SERVO_MOVE;
    servoTxBuf[4] = 1;
    servoTxBuf[5] = GET_LOW_BYTE(time);
    servoTxBuf[6] = GET_HIGH_BYTE(time);
    servoTxBuf[7] = servoNum;
    servoTxBuf[8] = GET_LOW_BYTE(targetAngel);
    servoTxBuf[9] = GET_HIGH_BYTE(targetAngel);
    HAL_UART_Transmit(&huart2, servoTxBuf, 10, UART_TIMEOUT);
    servo[servoNum].Angel = targetAngel;
}

void runServosAction(uint8_t num, uint8_t *servos, uint16_t *targetAngel, uint16_t *time)
{
    for (uint8_t i = 0; i < num; i++)
    {
        runServoAction(servos[i], targetAngel[i], time[i]);
    }
}

/**
 * @brief 控制动作组运行
 * @param actionGroupNum 动作组编号
 * @param runTimes 运行次数 0则无限次、
 * @retval 无
 */
void runServosActionGroup(uint8_t actionGroupNum, uint8_t runTimes)
{
    servoData.rxFlag = 0;
    servoTxBuf[0] = servoTxBuf[1] = FRAME_HEAD;
    servoTxBuf[2] = 0x05;
    servoTxBuf[3] = CMD_ACTION_GROUP_RUN;
    servoTxBuf[4] = actionGroupNum;
    servoTxBuf[5] = GET_LOW_BYTE(runTimes);
    servoTxBuf[6] = GET_HIGH_BYTE(runTimes);

    HAL_UART_Transmit(&huart2, servoTxBuf, 0x07, UART_TIMEOUT);
    /* 这里缺少一句 */
}

/**
 * @brief 停止动作组运行
 * @retval 无
 */
void stopServosActionGroup(void)
{
    servoTxBuf[0] = servoTxBuf[1] = FRAME_HEAD;
    servoTxBuf[2] = 0x02;
    servoTxBuf[3] = CMD_ACTION_GROUP_STOP;

    HAL_UART_Transmit(&huart2, servoTxBuf, 0x04, UART_TIMEOUT);
}

/**
 * @brief 更改动作组速度
 * @param actionGroupNum 动作组编号 如 0xFF 则表示全部
 * @param runSpeed 速度比例 %
 * @retval 无
 */
void changeServosActionGroupSpeed(uint8_t actionGroupNum, uint16_t runSpeed)
{
    servoTxBuf[0] = servoTxBuf[1] = FRAME_HEAD;
    servoTxBuf[2] = 0x05;
    servoTxBuf[3] = CMD_ACTION_GROUP_SPEED;
    servoTxBuf[4] = actionGroupNum;
    servoTxBuf[5] = GET_LOW_BYTE(runSpeed);
    servoTxBuf[6] = GET_HIGH_BYTE(runSpeed);

    HAL_UART_Transmit(&huart2, servoTxBuf, 0x07, UART_TIMEOUT);
}
