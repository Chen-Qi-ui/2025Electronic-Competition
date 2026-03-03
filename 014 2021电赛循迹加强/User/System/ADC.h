#ifndef __ADC_H__
#define __ADC_H__
#include "stm32f10x.h"
void ADC1_Configuration(void);					//ADC1转换器的初始化
void ADC1_CHInit(unsigned char CH);				//ADC1通道初始化
unsigned int GetADC1Result(unsigned char CH);	//获得ADC1的通道数据
unsigned int GetADC1Average(unsigned char CH);	//获得通道平均值
unsigned int GetADC1_CH17(void);
/******************************************************************************
 * 函数功能:卡尔曼滤波结构体
 * 备注：	无
 ******************************************************************************/
typedef struct  //卡尔曼滤波结构体
{
	float LastP;  	//前序协方差
	float Now_P; 	//当前协方差
	float out; 		//滤波结果
	float Kg; 		//卡尔曼增益
	float Q;  		//背景白噪声
	float R;		//器件方差
}kalman_filter;
void kalman(kalman_filter *ekf,float input);  //一维卡尔曼



#endif
