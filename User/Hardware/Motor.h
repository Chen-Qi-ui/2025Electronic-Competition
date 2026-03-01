#ifndef __MOTOR_H__
#define __MOTOR_H__


#include "stm32f10x.h"
void MotorInitPWMB(void);
void MotorInitPWMA(void);
void MotorSet(unsigned char motor, int8_t Speed);
#endif