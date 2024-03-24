#ifndef __STEPPINGMOTORCONTROL_H__
#define __STEPPINGMOTORCONTROL_H__

#include "main.h"
#include "tim.h"
#include "../../BSP/Beep/Beep.h"

#define MIN_PWM HCLKhz / ((PSC + 1) * (ARR + 1))

#define ARM_LENTH 100

#define MOTOR1_DIR_CHANGE(x)                                                                                                                                 \
    do                                                                                                                                                       \
    {                                                                                                                                                        \
        x ? HAL_GPIO_WritePin(MOTOR1_DIR_GPIO_Port, MOTOR1_DIR_Pin, GPIO_PIN_RESET) : HAL_GPIO_WritePin(MOTOR1_DIR_GPIO_Port, MOTOR1_DIR_Pin, GPIO_PIN_SET); \
    } while (0)
#define MOTOR2_DIR_CHANGE(x)                                                                                                                                 \
    do                                                                                                                                                       \
    {                                                                                                                                                        \
        x ? HAL_GPIO_WritePin(MOTOR2_DIR_GPIO_Port, MOTOR2_DIR_Pin, GPIO_PIN_RESET) : HAL_GPIO_WritePin(MOTOR2_DIR_GPIO_Port, MOTOR2_DIR_Pin, GPIO_PIN_SET); \
    } while (0)
#define MOTOR3_DIR_CHANGE(x)                                                                                                                                 \
    do                                                                                                                                                       \
    {                                                                                                                                                        \
        x ? HAL_GPIO_WritePin(MOTOR3_DIR_GPIO_Port, MOTOR3_DIR_Pin, GPIO_PIN_RESET) : HAL_GPIO_WritePin(MOTOR3_DIR_GPIO_Port, MOTOR3_DIR_Pin, GPIO_PIN_SET); \
    } while (0)
#define MOTOR4_DIR_CHANGE(x)                                                                                                                                 \
    do                                                                                                                                                       \
    {                                                                                                                                                        \
        x ? HAL_GPIO_WritePin(MOTOR4_DIR_GPIO_Port, MOTOR4_DIR_Pin, GPIO_PIN_RESET) : HAL_GPIO_WritePin(MOTOR4_DIR_GPIO_Port, MOTOR4_DIR_Pin, GPIO_PIN_SET); \
    } while (0)
#define MOTOR5_DIR_CHANGE(x)                                                                                                                                 \
    do                                                                                                                                                       \
    {                                                                                                                                                        \
        x ? HAL_GPIO_WritePin(MOTOR5_DIR_GPIO_Port, MOTOR5_DIR_Pin, GPIO_PIN_RESET) : HAL_GPIO_WritePin(MOTOR5_DIR_GPIO_Port, MOTOR5_DIR_Pin, GPIO_PIN_SET); \
    } while (0)

/* 电机状态 */
typedef enum
{
    IDLE = 0,        /* 电机空闲状态 */
    ACCEL = 1,       /* 电机加速状态 */
    AVESPEED = 2,    /* 电机匀速状态 */
    DECEL = 3,       /* 电机减速状态 */
    STOP = 4,        /* 电机停止状态 */
//    FINE_ADJUST = 5, /* 电机微调状态 */
} MotorState;

typedef enum
{
    CLOSE = 0,
    OPEN = 1,
    TRIANGLE = 3,
    SQUARE = 4,
    CIRCLE = 5,
    TRAPEZOID = 6,
} ClawState;

/* 电机编号 */
typedef enum
{
    MOTOR1 = 1,
    MOTOR2 = 2,
    MOTOR3 = 3,
    MOTOR4 = 4,
    MOTOR5 = 5,
} MOTOR;

/* 电机方向 */
typedef enum
{
    FORWARD = 0,  /* 正向 */
    BACKWARD = 1, /* 反向 */
} DIR;

/* 电机主要控制参数 */
typedef struct _MotorControl
{
    int32_t v1;          /* 末速度 单位 step/s */
    int32_t accStep;     /* 加速段的步数单位 step */
    int32_t decStep;     /* 加速段的步数单位 step */
    float *accTab;       /* 速度表格 单位 step/s 步进电机的脉冲频率 */
    float *decTab;       /* 速度表格 单位 step/s 步进电机的脉冲频率 */
    float *ptr;          /* 速度指针 */
    int32_t changePoint; /* 匀速到减速 */
    int32_t step;        /* 总步数 */
    int32_t pos;         /* 加减速中位置 */
    int32_t actPos;      /* 实际位置 */
    uint16_t pulse;      /* pulse */
    uint8_t i;           /* 两次中断输出一次脉冲 */
    MotorState state;    /* 电机状态 */
    MOTOR motor;         /* 电机编号 */
    DIR dir;             /* 电机方向 */
} MotorControl;

extern MotorControl motor1;
extern MotorControl motor2;
extern MotorControl motor3;
extern MotorControl motor4;
extern MotorControl motor5;

extern uint8_t errorBeep;

void motorInit(void);
void motorSpeedControlStar(MotorControl *motor, uint16_t pluse);
void motorSpeedControlStop(MotorControl *motor);
void motorMove2Pos(MotorControl *motor, int32_t v1, float accTime, float decTime, int32_t pos);
uint8_t clawStateChange(ClawState state);
uint8_t motorMove(MotorControl *motorControl, int32_t v1, float AccTime, float DecTime, int32_t step);

#endif /*__STEPPINGMOTORCONTROL_H__*/
