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
    int theta;              /* theta  ˳ʱ��ת��Ϊ�� distance ��ǰ�˶�Ϊ�� */
    float distance;         /* �˶���ΧΪ -distance_max ~ distance_max */
    float x;
    float y;
    float deltaTheta;
    float delteDistanse;
}Arm;

void armMovingInit(Arm *p);
void getAnD(Arm *p, float d, float x, float y);     /* �õ�����˶��ǶȺ͵��ǰ���˶����� */
void shakeMoving(float mMoveRange, float sMoveRange, int servoAngel); 

extern Arm controlData;

#endif
