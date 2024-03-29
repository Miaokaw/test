#include "ArmMoving.h"
//typedef struct _Arm
//{
//    int theta;              /* theta  ˳ʱ��ת��Ϊ�� distance ��ǰ�˶�Ϊ�� */
//    float distance;         /* �˶���ΧΪ -distance_max ~ distance_max */
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

void getAnD(Arm *p, float d, float x, float y) /* �õ�����˶��ǶȺ͵��ǰ���˶����� */
{
    /* ����ת��Ϊʵ�� */
    x -= 96.4;
    y -= 116.4;
    d = sqrt(fabs(d * d - ARMHIGHT * ARMHIGHT));
    float angle = atan(y/x);
    float delta_x = d * cos(angle);
    float delta_y = d * sin(angle);
    
    /* �˶� */
    if (p->x + delta_x <= ARMLENGTH)
    {
        p->deltaTheta = asin(((p->x) + delta_x) / ARMLENGTH) - p->theta;
        p->delteDistanse = delta_y - ARMLENGTH * (cos((p->theta) + p->deltaTheta) - cos(p->theta));
        if((p->distance + p->delteDistanse) > DISTANSEMAX)
        {
            delta_x = 0;
            delta_y = 0;
            p->deltaTheta = 0;
            p->delteDistanse = 0;
        }
    }
    else
    {
        delta_x = 0;
        delta_y = 0;
    }

    /* ���� */
    p->x += delta_x;
    p->y += delta_y;
    p->theta += p->deltaTheta;
    p->distance += p->delteDistanse;
    
}
