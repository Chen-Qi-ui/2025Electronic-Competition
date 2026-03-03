#include "stm32f10x.h"                  // Device header
#ifndef __TRACK_H__
#define __TRACK_H__
float Track1_Err() ;
float Track2_Err() ;
float  Track_PID_Control(PID_t *p_PID);
#endif