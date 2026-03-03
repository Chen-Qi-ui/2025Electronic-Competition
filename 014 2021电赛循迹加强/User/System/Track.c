#include "stm32f10x.h"                  // Device header
#include "PID.h"
#include "sensor.h"
#include "Motor.h"

extern uint8_t Digital_Final0;
extern uint8_t Digital_Final1;
extern PID_t Inner1;
extern PID_t Outer1;
extern PID_t Inner2;
extern PID_t Outer2;
uint8_t OffTrackFlag = 0;
#define Middle1 20
#define Middle2 -20

float Track1_Err() 
{

    float Err =0;
    if(Digital_Final0 != 255)
		{
			OffTrackFlag = 0; 
    switch (Digital_Final0) 
    {
        case 231: Err = 0; break;   // 正中间
        case 207: Err = +3; break;     // 右侧小偏差 - 减小值使转向更平缓
        case 159: Err = +5.0; break;    // 右侧中等偏差
        case 63: Err = +8.0; break;     // 右侧大偏差 - 增大值使转向更果断
        case 243: Err = -3; break;    // 左侧小偏差 - 减小值使转向更平缓
        case 249: Err = -5.0; break;    // 左侧中等偏差
        case 252: Err = -8.0; break;    // 左侧大偏差 - 增大值使转向更果断
        case 239: Err = +2.0; break;     // 右侧轻微偏差
        case 223: Err = +5.0; break;     // 右侧中小偏差
        case 191: Err = +5; break;     // 右侧中小偏差
        case 127: Err = +10.0; break;     // 右侧极大偏差 - 大幅增大值
        case 247: Err =  -2.0; break;    // 左侧轻微偏差
        case 251: Err = -5.0; break;    // 左侧中小偏差
        case 253: Err = -6; break;    // 左侧中偏差
        case 254: Err = -10.0; break;    // 左侧极大偏差 - 大幅增大值
        case 31: Err = +10.0; break;     // 右侧极限偏差 - 特别大的值
        case 248: Err = -5.0; break;    // 左侧中小偏差
        case 143: Err = +10.0; break;   // 右侧极限偏差 - 特别大的值
        default: Err = 0; break;
    }
		Digital_Final1 = Digital_Final0; 
	}
		
		else 
		{
			  OffTrackFlag = 1; 
			switch (Digital_Final1) 
    {
        case 231: Err = 0; break;   // 正中间
        case 207: Err = +3; break;     // 右侧小偏差 - 减小值使转向更平缓
        case 159: Err = +5.0; break;    // 右侧中等偏差
        case 63: Err = +8.0; break;     // 右侧大偏差 - 增大值使转向更果断
        case 243: Err = -3; break;    // 左侧小偏差 - 减小值使转向更平缓
        case 249: Err = -5.0; break;    // 左侧中等偏差
        case 252: Err = -8.0; break;    // 左侧大偏差 - 增大值使转向更果断
        case 239: Err = +2.0; break;     // 右侧轻微偏差
        case 223: Err = +5.0; break;     // 右侧中小偏差
        case 191: Err = +5; break;     // 右侧中小偏差
        case 127: Err = +10.0; break;     // 右侧极大偏差 - 大幅增大值
        case 247: Err =  -2.0; break;    // 左侧轻微偏差
        case 251: Err = -5.0; break;    // 左侧中小偏差
        case 253: Err = -6; break;    // 左侧中偏差
        case 254: Err = -10.0; break;    // 左侧极大偏差 - 大幅增大值
        case 31: Err = +10.0; break;     // 右侧极限偏差 - 特别大的值
        case 248: Err = -5.0; break;    // 左侧中小偏差
        case 143: Err = +10.0; break;   // 右侧极限偏差 - 特别大的值
        default: Err = 0; break;
    }
		}
    return Middle1+Err;
	 

}




float Track2_Err() 
{

    float Err =0;
    if(Digital_Final0 != 255)
		{
			OffTrackFlag = 0; 
    switch (Digital_Final0) 
    {
        case 231: Err = 0; break;   // 正中间
        case 207: Err = 3; break;     // 右侧小偏差 - 减小值使转向更平缓
        case 159: Err = 5.0; break;    // 右侧中等偏差
        case 63: Err = -8.0; break;     // 右侧大偏差 - 增大值使转向更果断
        case 243: Err = -3; break;    // 左侧小偏差 - 减小值使转向更平缓
        case 249: Err = -5.0; break;    // 左侧中等偏差
        case 252: Err = -8.0; break;    // 左侧大偏差 - 增大值使转向更果断
        case 239: Err = 2.0; break;     // 右侧轻微偏差
        case 223: Err = 5.0; break;     // 右侧中小偏差
        case 191: Err = 5; break;     // 右侧中小偏差
        case 127: Err = -10.0; break;     // 右侧极大偏差 - 大幅增大值
        case 247: Err =  -2.0; break;    // 左侧轻微偏差
        case 251: Err = -5.0; break;    // 左侧中小偏差
        case 253: Err = -6; break;    // 左侧中偏差
        case 254: Err = -10.0; break;    // 左侧极大偏差 - 大幅增大值
        case 31: Err = -10.0; break;     // 右侧极限偏差 - 特别大的值
        case 248: Err = -5.0; break;    // 左侧中小偏差
        case 143: Err = -10.0; break;   // 右侧极限偏差 - 特别大的值
        default: Err = 0; break;
    }
		Digital_Final1 = Digital_Final0; 
	}
		
		else 
		{
			  OffTrackFlag = 1; 
			switch (Digital_Final1) 
    {
        case 231: Err = 0; break;   // 正中间
        case 207: Err = -3; break;     // 右侧小偏差 - 减小值使转向更平缓
        case 159: Err = -5.0; break;    // 右侧中等偏差
        case 63: Err = -8.0; break;     // 右侧大偏差 - 增大值使转向更果断
        case 243: Err = -3; break;    // 左侧小偏差 - 减小值使转向更平缓
        case 249: Err = -5.0; break;    // 左侧中等偏差
        case 252: Err = -8.0; break;    // 左侧大偏差 - 增大值使转向更果断
        case 239: Err = -2.0; break;     // 右侧轻微偏差
        case 223: Err = -5.0; break;     // 右侧中小偏差
        case 191: Err = -5; break;     // 右侧中小偏差
        case 127: Err = -10.0; break;     // 右侧极大偏差 - 大幅增大值
        case 247: Err =  -2.0; break;    // 左侧轻微偏差
        case 251: Err = -5.0; break;    // 左侧中小偏差
        case 253: Err = -6; break;    // 左侧中偏差
        case 254: Err = -10.0; break;    // 左侧极大偏差 - 大幅增大值
        case 31: Err = -10.0; break;     // 右侧极限偏差 - 特别大的值
        case 248: Err = -5.0; break;    // 左侧中小偏差
        case 143: Err = -10.0; break;   // 右侧极限偏差 - 特别大的值
        default: Err = 0; break;
    }
		}
    return Middle2+Err;
	 

}



