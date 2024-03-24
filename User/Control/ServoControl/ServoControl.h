#ifndef __SERVOCONTROL_H__
#define __SERVOCONTROL_H__

#include "main.h"
#include "usart.h"

#define FRAME_HEAD 0x55 /* 帧头 */

#define SERVO_NUM 4    /* 舵机数量 */
#define ALL_SERVO 0xFF /* 表示全部舵机 */

#define CMD_SERVO_MOVE 0x03         /* 控制任意个舵机的转动 */
#define CMD_ACTION_GROUP_RUN 0x06   /* 控制动作组运行 */
#define CMD_ACTION_GROUP_STOP 0x07  /* 停止正在运行的动作组 */
#define CMD_ACTION_GROUP_SPEED 0x0B /* 控制动作组的速度 */

#define GET_LOW_BYTE(DATA) ((uint8_t)(DATA))
#define GET_HIGH_BYTE(DATA) ((uint8_t)((DATA) >> 8))

typedef struct _Servo
{
    uint8_t servoID; /* 舵机编号 */
    uint16_t Angel;  /* 目标角度 */
} Servo;

typedef enum
{
    ARM = 0,
    CLAW = 1,
    SPIN = 2,
} Tools;

void servoInit(void);
void servoAction(Tools tool, uint16_t targetAngel, uint16_t runTime);
void runServoAction(uint8_t servoNum, uint16_t targetAngel, uint16_t time);
void runServosAction(uint8_t num, uint8_t *servos, uint16_t *targetAngel, uint16_t *time);
void runServosActionGroup(uint8_t actionGroupNum, uint8_t runTimes);
void stopServosActionGroup(void);
void changeServosActionGroupSpeed(uint8_t actionGroupNum, uint16_t runSpeed);

#endif /*__SERVOCONTROL_H__*/
