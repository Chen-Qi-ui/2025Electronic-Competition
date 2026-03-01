#ifndef __LED_H__
#define __LED_H__
#include "stm32f10x.h"
void LEDInit(void);
void LED1Init(void);
void LED2Init(void);
void LED3Init(void);
void LED4Init(void);
void LED1_OFF(void);
void LED1_ON(void);
void LED2_OFF(void);
void LED2_ON(void);
void LED3_OFF(void);
void LED3_ON(void);
void LED(unsigned char Location);
void LED1_Rev(void);
void LED2_Rev(void);
void LED3_Rev(void);
void LED4_Rev(void);
#endif