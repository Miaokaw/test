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
    x -= 96.4;
    y -= 116.4;
    d = sqrt(fabs(d * d - ARMHIGHT * ARMHIGHT));
    float angle = atan(y/x);
    float delta_x = d * cos(angle);
    float delta_y = d * sin(angle);
    
    /* 运动 */
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

    /* 更新 */
    p->x += delta_x;
    p->y += delta_y;
    p->theta += p->deltaTheta;
    p->distance += p->delteDistanse;
    
}
