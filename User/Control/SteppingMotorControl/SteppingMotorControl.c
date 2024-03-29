/**
 * @file SteppingMotorControl.c
 * @author MSuperHero (320314609@qq.com)
 * @brief 步进电机驱动
 * @date 2024-02-06
 *
 */
#include "SteppingMotorControl.h"

uint8_t errorBeep = 0;

MotorControl motor1 = {0};
MotorControl motor2 = {0};
MotorControl motor3 = {0};
MotorControl motor4 = {0};
MotorControl motor5 = {0};

ClawState clawState = CLOSE;

/**
 * @brief 初始化函数
 *
 */
void motorInit(void)
{
    motor1.motor = MOTOR1;
    motor2.motor = MOTOR2;
    motor3.motor = MOTOR3;
    motor4.motor = MOTOR4;
    motor5.motor = MOTOR5;
}
/**
 * @brief 步进电机定时器参数更新
 *
 * @param motor
 */
void motorTIMUpgrade(MotorControl *motor)
{
    uint32_t timCount = 0;
    uint32_t tmp = 0;
    switch (motor->motor)
    {
    case MOTOR1:
        timCount = __HAL_TIM_GET_COUNTER(&htim1);
        tmp = 0xFFFF & (timCount + motor->pulse);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, tmp);
        break;
    case MOTOR2:
        timCount = __HAL_TIM_GET_COUNTER(&htim8);
        tmp = 0xFFFF & (timCount + motor->pulse);
        __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, tmp);
        break;
    case MOTOR3:
        timCount = __HAL_TIM_GET_COUNTER(&htim3);
        tmp = 0xFFFF & (timCount + motor->pulse);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, tmp);
        break;
    case MOTOR4:
        timCount = __HAL_TIM_GET_COUNTER(&htim4);
        tmp = 0xFFFF & (timCount + motor->pulse);
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, tmp);
    case MOTOR5:
        timCount = __HAL_TIM_GET_COUNTER(&htim2);
        tmp = 0xFFFF & (timCount + motor->pulse);
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, tmp);
    default:
        break;
    }
}
/**
 * @brief 步进电机定时器启用
 *
 * @param motor
 */
void motorTIMStar(MotorControl *motor)
{
    switch (motor->motor)
    {
    case MOTOR1:
        /* 重置计数器和比较器的值 */
        __HAL_TIM_SET_COUNTER(&htim1, 0);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, (uint16_t)motor->pulse / 2);
        /* 启动计时器的输出比较器 */
        HAL_TIM_OC_Start_IT(&htim1, TIM_CHANNEL_3);
        break;
    case MOTOR2:
        /* 重置计数器和比较器的值 */
        __HAL_TIM_SET_COUNTER(&htim8, 0);
        __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, (uint16_t)motor->pulse / 2);
        /* 启动计时器的输出比较器 */
        HAL_TIM_OC_Start_IT(&htim8, TIM_CHANNEL_1);
        break;
    case MOTOR3:
        /* 重置计数器和比较器的值 */
        __HAL_TIM_SET_COUNTER(&htim3, 0);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, (uint16_t)motor->pulse / 2);
        /* 启动计时器的输出比较器 */
        HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_3);
        break;
    case MOTOR4:
        /* 重置计数器和比较器的值 */
        __HAL_TIM_SET_COUNTER(&htim4, 0);
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, (uint16_t)motor->pulse / 2);
        /* 启动计时器的输出比较器 */
        HAL_TIM_OC_Start_IT(&htim4, TIM_CHANNEL_2);
        break;
    case MOTOR5:
        /* 重置计数器和比较器的值 */
        __HAL_TIM_SET_COUNTER(&htim2, 0);
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, (uint16_t)motor->pulse / 2);
        /* 启动计时器的输出比较器 */
        HAL_TIM_OC_Start_IT(&htim2, TIM_CHANNEL_2);
        break;
    default:
        break;
    }
}
/**
 * @brief 步进电机定时器停止
 *
 * @param motor
 */
void motorTIMStop(MotorControl *motor)
{
    switch (motor->motor)
    {
    case MOTOR1:
        HAL_TIM_OC_Stop_IT(&htim1, TIM_CHANNEL_3);
        break;
    case MOTOR2:
        HAL_TIM_OC_Stop_IT(&htim8, TIM_CHANNEL_1);
        break;
    case MOTOR3:
        HAL_TIM_OC_Stop_IT(&htim3, TIM_CHANNEL_3);
        break;
    case MOTOR4:
        HAL_TIM_OC_Stop_IT(&htim4, TIM_CHANNEL_2);
        break;
    case MOTOR5:
        HAL_TIM_OC_Stop_IT(&htim2, TIM_CHANNEL_2);
        break;
    default:
        break;
    }
}

/**
 * @brief 步进电机方向改变
 *
 * @param motor
 */
void motorDirChange(MotorControl *motor)
{
    switch (motor->motor)
    {
    case MOTOR1:
        MOTOR1_DIR_CHANGE(motor->dir);
        break;
    case MOTOR2:
        MOTOR2_DIR_CHANGE(motor->dir);
        break;
    case MOTOR3:
        MOTOR3_DIR_CHANGE(motor->dir);
        break;
    case MOTOR4:
        MOTOR4_DIR_CHANGE(motor->dir);
        break;
    case MOTOR5:
        MOTOR5_DIR_CHANGE(motor->dir);
        break;
    default:
        break;
    }
}

/**
 * @brief 根据给定的时间和速度计算出每个时间步的值
 *
 * @param t 时间
 * @param v0 初始速度 step/s
 * @param v1 终止速度 step/s
 * @return uint8_t 计算结果，成功返回0，失败返回1
 */
/**
 * @brief 根据给定的参数计算每个时间步的值
 *
 * @param motorControl 指向MotorControl结构体的指针
 * @param t 时间间隔
 * @param v0 初始速度
 * @param v1 终止速度
 * @return uint8_t 计算结果，0表示成功，1表示失败
 */
uint8_t perTabCal(MotorControl *motorControl, float t, int32_t v0, int32_t v1)
{
    uint8_t flag = 0;
    if (v0)
    {
        flag = 1;
        v1 = v0;
    }
    motorControl->v1 = v1;
    // int32_t jerk = fabs((v1 - v0) / (t * t));                       /* 加速度 */
    // int32_t jerkAccStep = (int32_t)(v0 * t + jerk * pow(t, 3) / 6); /* 加速度阶段的时间步 */
    // int32_t jerkDecStep = (int32_t)((v1 + v0) * t - jerkAccStep);   /* 减速度阶段的时间步 */
    float *perTab = NULL;                                         /* 存储每个时间步的值 */
    int32_t jerk = fabs(4.0f * v1 / (t * t));                     /* 加速度 */
    int32_t jerkAccStep = (int32_t)(jerk * pow(t, 3) / 48.0f);    /* 加速度阶段的时间步 */
    int32_t jerkDecStep = (int32_t)(v1 * t / 2.0f - jerkAccStep); /* 减速度阶段的时间步 */
    int32_t step = jerkAccStep + jerkDecStep;                     /* 总时间步数 */

    if (step % 2 != 0)
        step++;                                                    /* 如果步数为奇数，则加1(（int32_t）转换时出现的误差) */
    perTab = (float *)(mymalloc(OUT, (step + 1) * sizeof(float))); /* 分配内存空间 */
    if (perTab == NULL)
        return 1; // 内存分配失败，返回0

    float ti = pow(6.0f / jerk, 1 / 3.0f); /* 计算t1 */
    float tSum = ti;                       /* 初始化tSum */

    perTab[0] = jerk * pow(ti, 2) / 2.0f; /* 计算第一个时间步的值 */
    // perTab[0] = v0 + 0.5f * jerk * powf(ti, 2); /* 计算第一个时间步的值 */

    if (perTab[0] < MIN_PWM)
        perTab[0] = MIN_PWM; /* 如果第一个时间步的值小于最小PWM值，则设置为最小PWM值 */

    for (int32_t i = 1; i < step; i++)
    {
        ti = 1.0f / perTab[i - 1]; /* 计算ti */
        tSum += ti;                /* 更新tSum */
        if (i < jerkAccStep)
        {
            perTab[i] = 0.5f * jerk * powf(tSum, 2); /* 计算加速度阶段的时间步的值 */
            // perTab[i] = v0 + 0.5f * jerk * pow(tSum, 2); /* 计算加速度阶段的时间步的值 */

            if (i == jerkAccStep - 1)
                tSum = fabs(tSum - t / 2.0f); /* 如果是最后一个加速度阶段的时间步，则更新tSum为t的绝对值 */
            continue;
        }
        perTab[i] = v1 - 0.5f * jerk * pow(fabs(t / 2.0f - tSum), 2); /* 计算减速度阶段的时间步的值 */
        if (perTab[i] >= v1)
        {
            step = i; /* 如果时间步的值大于终止速度，则结束循环 */
            break;
        }
    }
    /* 如果正序，则将motorControl的accTab设置为perTab，并将accTab设置为step的值，然后返回0 */
    if (flag == 0)
    {
        motorControl->accTab = perTab;
        motorControl->accStep = step;
        return 0;
    }
    /* 初始化tabTmp为0 */
    float tabTmp = 0;
    /* 倒序 */
    for (int32_t i = 0; i < (step / 2); i++)
    {
        tabTmp = perTab[i];
        perTab[i] = perTab[step - i - 1];
        perTab[step - i - 1] = tabTmp;
    }
    motorControl->decTab = perTab;
    motorControl->decStep = step;
    return 0; /* 计算成功，返回0 */
}

uint8_t clawStateChange(ClawState state)
{
//    if (clawState == state)
        //return 1;
    switch (state)
    {
    case OPEN:
        motorMove2Pos(&motor4, 6400, 0.5, 0.5, 10000);
        break;
    case CLOSE:
        motorMove2Pos(&motor4, 4800, 0.5, 0.5, 0);
        break;
    case SQUARE:
        motorMove2Pos(&motor4, 4800, 0.5, 0.5, 2000);
        break;
    case CIRCLE:
        motorMove2Pos(&motor4, 6400, 0.5, 0.5, 1500);
    break;
    default:
        break;
    }
    clawState = state;
    return 0;
}


/**
 * @brief 控制电机移动
 *
 * @param motorControl 电机控制对象指针
 * @param v0 起始速度
 * @param v1 终止速度
 * @param AccTime 加速时间
 * @param DecTime 减速时间
 * @param step 步进数
 * @return uint8_t 返回操作结果，0表示成功，1表示内存不够，2表示步数不够
 */
uint8_t motorMove(MotorControl *motor, int32_t v1, float accTime, float decTime, int32_t step)
{
    /* 加速表计算 */
    if (perTabCal(motor, accTime, 0, v1) == 1)
        return 1;
    printf("motor%d malloc ACC %d\r\n", motor->motor, getMemoryUsage(OUT));
    /* 减速表计算 */
    if (perTabCal(motor, decTime, v1, 0) == 1)
        return 1;
    printf("motor%d malloc DEC %d\r\n", motor->motor, getMemoryUsage(OUT));

    /* 控制电机的正反转 */
    if (step > 0)
        motor->dir = FORWARD;
    else
    {
        motor->dir = BACKWARD;
        step = -step;
    }
    motorDirChange(motor);

    /* 检查步进数是否满足要求 */
    if (step < (motor->accStep + motor->decStep))
    {
        myfree(OUT, motor->accTab);
        myfree(OUT, motor->decTab);
        printf("Step too Low! %d", getMemoryUsage(OUT));
        return 2;
    }

    /* 初始化电机控制对象的参数 */
    motor->step = step;
    motor->changePoint = motor->step - motor->decStep;
    motor->pos = 0;
    motor->state = ACCEL;

    /* 初始化脉冲计数器 */
    motor->ptr = motor->accTab;
    motor->pulse = (uint32_t)(FREQ / (*motor->ptr));
    motor->ptr++;

    motorTIMStar(motor);

    return 0;
}

void motorMove2Pos(MotorControl *motor, int32_t v1, float accTime, float decTime, int32_t pos)
{
    int32_t step = pos - motor->actPos;
    int32_t flag = 1;
    uint8_t err = motorMove(motor, v1, accTime, decTime, step);
    if (step < 0){
        flag = -1;
    }
    if (err == 2){
        float time = (float )(flag * step / v1);
        motorMove(motor, v1, time, time, step);
    }
}
/**
 * @brief 步进电机超限保护
 *
 * @param motor
 */
void motorPosProtect(MotorControl *motor)
{
    if (motor->dir == FORWARD)
        motor->actPos++;
    else
        motor->actPos--;
//    if (motor->actPos >= 0 && motor->actPos <= motor->maxPos)
//        return;
//    if (motor->actPos < 0)
//    {
//        motor->actPos = 0;
//        motor->state = STOP;
//    }
//    else if (motor->actPos > motor->maxPos)
//    {
//        motor->actPos = motor->maxPos;
//        motor->state = STOP;
//    }
//    errorBeep = 1;
//    myfree(OUT, motor->accTab);
//    myfree(OUT, motor->decTab);
}

/**
 * @brief 步进电机状态更新
 *
 * @param motor
 */
void motorStateUpgrade(MotorControl *motor)
{
    motor->i++;        /* 定时器中断次数计数值加1 */
    if (motor->i == 2) /* 如果中断次数为2 */
    {
        motor->i = 0;

        /* 清零定时器中断次数计数值 */
        if ((motor->state != IDLE) && (motor->state != STOP)) /* 如果不是空闲状态和停止状态 */
        {
            motorPosProtect(motor);
            motor->pos++; /* 当前位置加1 */
        }
        switch (motor->state) /* 根据当前状态进行判断 */
        {
        case ACCEL: /* 加速状态 */
            motor->pulse = (uint16_t)(FREQ / *motor->ptr / 2);
            motor->ptr++; /* 指针加1 */
            if (motor->pos >= motor->accStep)
            {
                myfree(OUT, motor->accTab); /* 释放内存 */
                motor->state = AVESPEED;    /* 进入匀速状态 */
            }
            break;
        case DECEL: /* 减速状态 */
            motor->pulse = (uint16_t)(FREQ / *motor->ptr / 2);
            motor->ptr++; /* 下一步 */
            if (motor->pos >= motor->step)
            {
                myfree(OUT, motor->decTab); /* 释放内存 */
                motor->state = STOP;        /* 停止状态 */
            }
            break;
        case AVESPEED: /* 匀速状态 */
            motor->pulse = (uint16_t)(FREQ / motor->v1 / 2);
            if (motor->pos >= motor->changePoint)
            {
                motor->ptr = motor->decTab; /* 将减速段的速度表赋值给ptr */
                motor->state = DECEL;       /* 进入减速状态 */
            }
            break;
        case STOP:               /* 停止状态 */
            motorTIMStop(motor); /* 停止对应PWM通道 */
            printf("motor%d free %d\r\n", motor->motor, getMemoryUsage(OUT));
            motor->state = IDLE; /* 空闲状态 */
            break;
        case IDLE: /* 空闲状态 */
            break;
        default:
            break;
        }
    }
    motorTIMUpgrade(motor);
}

/**
 * @brief 定时器输出比较器延时回调函数
 * @brief 定时器输出比较器延时回调函数
 * @param htim 定时器句柄
 */
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{

    if (htim->Instance == TIM1) /* 判断定时器是否为TIM8 */
    {
        motorStateUpgrade(&motor1);
    }
    else if (htim->Instance == TIM8) /* 判断定时器是否为TIM1 */
    {
        motorStateUpgrade(&motor2);
    }
    else if (htim->Instance == TIM3)
    {
        motorStateUpgrade(&motor3);
    }
    else if (htim->Instance == TIM4)
    {
        motorStateUpgrade(&motor4);
    }
    else if (htim->Instance == TIM2)
    {
        motorStateUpgrade(&motor5);
    }
}
