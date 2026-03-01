#ifndef __KEY_H__
#define __KEY_H__
#include "stm32f10x.h"                  // Device header
void Key1_Init(void);
void Key2_Init(void);
void Key3_Init(void);
void Key4_Init(void);
unsigned char GetKey1Sta(void);
unsigned char GetKey2Sta(void);
unsigned char GetKey3Sta(void);
unsigned char GetKey4Sta(void);
unsigned char GetKeyVal(void);
void LED1_Rev(void);
void LED2_Rev(void);
void LED3_Rev(void);
void LED4_Rev(void);
#endif