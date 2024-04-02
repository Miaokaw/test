#ifndef __ARMMOVING_H__
#define __ARMMOVING_H__

#include "main.h"

#define ARMLENGTH 44.0
#define DISTANSEMAX 9.0
#define ARMHIGHT 40.0
#define ANGELTOPWM 11.1
#define DISTOSTEP 1600


typedef struct _Arm
{
    int theta;              /* theta  顺时针转动为正 distance 往前运动为正 */
    float distance;         /* 运动范围为 -distance_max ~ distance_max */
    float x;
    float y;
    float deltaTheta;
    float delteDistanse;
}Arm;

void armMovingInit(Arm *p);
void getAnD(Arm *p, float d, float x, float y);     /* 得到舵机运动角度和电机前后运动距离 */
void shakeMoving(float mMoveRange, float sMoveRange, int servoAngel); 

extern Arm controlData;

#endif
