#include "Process.h"

uint8_t pass = 0;
void testProcess(void)
{
    servoAction(ARM, 2150, 5000);
    clawStateChange(OPEN);
    motorMove(&motor1, 9600, 2, 2, 25500);
    waitS(motor1);
    motorMove(&motor2, 12800, 1.5, 1.5, 27200);
    waitS(motor2);
    clawStateChange(CIRCLE);
    waitS(motor5);
    motorMove(&motor2, 12800, 1.5, 2.5, -27200);
    waitS(motor2);
//    servoAction(SPIN, 1830, 5000);
//    HAL_Delay(5000);
    motorMove(&motor1, 9600, 2, 2, -25500);
    waitS(motor1)
    motorMove(&motor2, 9600, 1.5, 1.5, 17600);
    waitS(motor2);
    motorMove(&motor2, 3200, 0.5, 0.5, 9600);
    waitS(motor2);
    clawStateChange(OPEN);
    waitS(motor5);
    motorMove(&motor2, 12800, 1.5, 2.5, -27200);
    clawStateChange(CLOSE);
    waitS(motor2);
//    servoAction(SPIN, 580, 5000);
//    HAL_Delay(5000);
//    
////    
//    servoAction(ARM, 2150, 5000);
//    clawStateChange(OPEN);
//    motorMove(&motor1, 9600, 2, 2, 25500);
//    waitS(motor1);
//    motorMove(&motor2, 12800, 1.5, 1.5, 27200);
//    waitS(motor2);
//    clawStateChange(SQUARE);
//    waitS(motor5);
//    motorMove(&motor2, 12800, 1.5, 2.5, -27200);
//    waitS(motor2);
//    servoAction(SPIN, 1830, 5000);
//    HAL_Delay(5000);
//    motorMove(&motor1, 9600, 2, 2, -25500);
//    waitS(motor1)
//    motorMove(&motor2, 9600, 1.5, 1.5, 17600);
//    waitS(motor2);
//    HAL_Delay(2000);
//    motorMove(&motor2, 3200, 0.5, 0.5, 9600);
//    waitS(motor2);
//    clawStateChange(OPEN);
//    waitS(motor5);
//    motorMove(&motor2, 12800, 1.5, 2.5, -27200);
//    clawStateChange(CLOSE);
//    waitS(motor2);
//    servoAction(SPIN, 580, 5000);
//    HAL_Delay(5000);
////    
////    
//    servoAction(ARM, 2150, 5000);
//    clawStateChange(OPEN);
//    motorMove(&motor1, 9600, 2, 2, 25500);
//    waitS(motor1);
//    motorMove(&motor2, 12800, 1.5, 1.5, 27200);
//    waitS(motor2);
//    clawStateChange(CIRCLE);
//    waitS(motor5);
//    motorMove(&motor2, 12800, 1.5, 2.5, -27200);
//    waitS(motor2);
//    servoAction(SPIN, 1830, 5000);
//    HAL_Delay(5000);
//    motorMove(&motor1, 9600, 2, 2, -25500);
//    waitS(motor1)
//    motorMove(&motor2, 9600, 1.5, 1.5, 17600);
//    waitS(motor2);
//    HAL_Delay(2000);
//    motorMove(&motor2, 3200, 0.5, 0.5, 9600);
//    waitS(motor2);
//    clawStateChange(OPEN);
//    waitS(motor5);
//    motorMove(&motor2, 12800, 1.5, 2.5, -27200);
//    clawStateChange(CLOSE);
//    waitS(motor2);
//    servoAction(SPIN, 580, 5000);
//    HAL_Delay(5000);
//    
//    
//    servoAction(ARM, 1200, 5000);
//    HAL_Delay(5000);
}

void resetProcess(void)
{
    motorMove2Pos(&motor1, 3200, 0.5, 0.5, 0);
    motorMove2Pos(&motor2, 3200, 0.5, 0.5, 0);
    clawStateChange(CLOSE);
}
