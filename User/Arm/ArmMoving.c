#include "ArmMoving.h"

Arm controlData;

/**
 * 初始化机械臂运动状态
 * @param p 指向Arm结构体的指针，用于存储机械臂的各种状态参数
 */
void armMovingInit(Arm *p){
    // 初始化角度变化量和距离变化量为0
    p->deltaTheta = 0;
    p->delteDistanse = 0;
    // 初始化当前距离和角度为0
    p->distance = 0;
    p->theta = 0;
    // 初始化机械臂X轴坐标为0，Y轴坐标为设定的臂长
    p->x = 0;
    p->y = ARMLENGTH;
}

/**
 * 根据目标点计算机器人手臂的位移和角度变化
 * 
 * @param p 指向Arm结构体的指针，用于储存计算后手臂的位置和角度信息
 * @param d 目标点与机器人基座的距离（未使用）
 * @param x 目标点在水平面上的坐标
 * @param y 目标点在垂直面上的坐标
 * 
 * 注：本函数不返回任何值，而是通过修改Arm结构体的成员变量来输出结果。
 */
void getAnD(Arm *p, float d, float x, float y) 
{
    // 将坐标系转换为机器人手臂的工作空间坐标系
    x -= 104.0f;
    y = 105.0f - y;
    
    // 如果目标点在机器人手臂的工作空间内，则不做任何动作
    if (x <= 1 && x >= -1 && y <= 1 && y >= -1){
        p->deltaTheta = 0;
        p->delteDistanse = 0;
        return;
    }
    
    // 计算手臂应该移动的距离和角度变化
    float delta_x = x * 6 / 50;
    float delta_y = y * 6 / 50;

    // 计算手臂的新位置和角度，确保不超过最大允许距离
    if (p->x + delta_x <= ARMLENGTH)
    {
        p->deltaTheta = asin(((p->x) + delta_x) / ARMLENGTH) - p->theta;
        p->delteDistanse = delta_y - ARMLENGTH * (cos((p->theta) + p->deltaTheta) - cos(p->theta));
        if(fabs(p->distance + p->delteDistanse) > DISTANSEMAX)
        {
            delta_x = 0;
            delta_y = 0;
            p->deltaTheta = 0;
            p->delteDistanse = 0;
        }
    }
    else 
    {
        // 如果计算出的位置超出了手臂的长度范围，则将移动量和角度变化量设为0
        delta_x = 0;
        delta_y = 0;
    }

    // 更新手臂的位置和角度
    p->x += delta_x;
    p->y += delta_y;
    p->theta += p->deltaTheta;
    p->distance += p->delteDistanse;
    
}

/**
 * @brief 实现机器人的摇摆动作
 * 
 * 该函数通过控制舵机和步进电机实现机器人的摇摆动作。舵机控制摇摆角度，步进电机控制摇摆距离。
 * 
 * @param mMoveRange 步进电机移动范围的浮点数值，单位为mm。表示机器人摇摆的幅度。
 * @param sMoveRange 舵机调整角度的浮点数值，单位为度。表示机器人摇摆的频率。
 * @param servoAv ngel 初始角度的整数值，单位为度。决定机器人摇摆的起始方向。
 */
void shakeMoving(float mMoveRange, float sMoveRange, int servoAngel){
    for(uint8_t i = 0; i<10; i++){
        // 向前摇摆
        //servoAction(SPIN, servoAngel + (int)(sMoveRange * ANGELTOPWM), 10);
        motorMove(&motor1, 3200, 0, 0, (int)(mMoveRange * DISTOSTEP));
        waitS(motor1);
        
        // 向后摇摆
        //servoAction(SPIN, servoAngel - sMoveRange * ANGELTOPWM * 2, 10);
        motorMove(&motor1, 3200, 0, 0, (int)(-mMoveRange * DISTOSTEP*2));
        
        // 恢复到初始向前摇摆姿态
        //servoAction(SPIN, servoAngel + (int)(sMoveRange * ANGELTOPWM), 10);
        waitS(motor1);
        motorMove(&motor1, 3200, 0, 0, (int)(mMoveRange * DISTOSTEP));
        waitS(motor1);
    }
}
