#include "ArmMoving.h"
//typedef struct _Arm
//{
//    int theta;              /* theta  顺时针转动为正 distance 往前运动为正 */
//    float distance;         /* 运动范围为 -distance_max ~ distance_max */
//}Arm;
Arm controlData;

void armMovingInit(Arm *p){
    p->deltaTheta = 0;
    p->delteDistanse = 0;
    p->distance = 0;
    p->theta = 0;
    p->x = 0;
    p->y = ARMLENGTH;
}

void getAnD(Arm *p, float d, float x, float y) /* 得到舵机运动角度和电机前后运动距离 */
{
    /* 画面转换为实际 */
    x -= 125.0f;
    y = 143.0f - y;
    if (x <= 1 && x >= -1 && y <= 1 && y >= -1){
        p->deltaTheta = 0;
        p->delteDistanse = 0;
        return;
    }
    float delta_x = x * 6 / 50;
    float delta_y = y * 6 / 50;

    /* 运动 */
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
    else //
    {
        delta_x = 0;
        delta_y = 0;
    }

    /* 更新 */
    p->x += delta_x;
    p->y += delta_y;
    p->theta += p->deltaTheta;
    p->distance += p->delteDistanse;
    
}

void shakeMoving(float mMoveRange, float sMoveRange, int servoAngel){
    for(uint8_t i = 0; i<10; i++){
        servoAction(SPIN, servoAngel + (int)(sMoveRange * ANGELTOPWM), 10);
        motorMove(&motor1, 3200, 0, 0, (int)(mMoveRange * DISTOSTEP));
        waitS(motor1);
        servoAction(SPIN, servoAngel - sMoveRange * ANGELTOPWM * 2, 10);
        motorMove(&motor1, 3200, 0, 0, (int)(-mMoveRange * DISTOSTEP));
        servoAction(SPIN, servoAngel + (int)(sMoveRange * ANGELTOPWM), 10);
        waitS(motor1);
    }
    
    
}
