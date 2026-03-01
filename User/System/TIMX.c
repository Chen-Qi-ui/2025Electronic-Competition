#include "stm32f10x.h"                  // Device header
#include "TIMX.h"
void TIMx_Config(void)
{
//	  TIM1_Config();
	  TIM2_Config();
//	  TIM3_Config();
//	TIM4_Config();
//	//TIM5_Config();
//	/*TIM6_Config();
////	TIM7_Config();*/
//	TIM1_Period(10000);   //定时时间为10ms
   TIM2_Period(10000);
//   TIM3_Period(10000);
//	TIM4_Period(10000);
//	//TIM5_Period(10000);
//	//TIM6_Period(10000);
//	//TIM7_Period(10000);
//	TIM_Cmd(TIM1, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
//    TIM_Cmd(TIM3, ENABLE);
//	TIM_Cmd(TIM4, ENABLE);
//	//TIM_Cmd(TIM5, ENABLE);
//	//TIM_Cmd(TIM6, ENABLE);
//	//TIM_Cmd(TIM7, ENABLE);


// TIM1_Config();
// TIM1_Period(10000); 
// TIM_Cmd(TIM1, ENABLE);
// TIM8_Config();
// TIM8_Period(10000); 
// TIM_Cmd(TIM8, ENABLE);
}


void TIM1_Config(void)
{
	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
 //TIM_TimeBaseStructure.TIM_Period = 20000;   //10000/0.5=20000（10毫秒）
 TIM_TimeBaseStructure.TIM_Prescaler = 36-1;   //定时器主频为72M  分频系数为36 72M/36=2M
 TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;        //时钟分割，无用
 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;    //向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x00;   //定时器重复的次数
 TIM_TimeBaseInit(TIM1, & TIM_TimeBaseStructure);     //一个周期=1s/2M即0.5us
	
 TIM_ClearITPendingBit(TIM1, TIM_IT_Update);    //清除中断标志 
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE );   //使能中断，必须有对应的中断服务函数，否则会GG
	
	TIM_Cmd(TIM1, DISABLE);   //定时器2使能
}

void TIM2_Config(void)
{
	
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
 //TIM_TimeBaseStructure.TIM_Period = 20000;   //10000/0.5=20000（10毫秒）
 TIM_TimeBaseStructure.TIM_Prescaler = 36-1;   //定时器主频为72M  分频系数为36 72M/36=2M
 TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;        //时钟分割，无用
 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;    //向上计数模式
 TIM_TimeBaseInit(TIM2, & TIM_TimeBaseStructure);     //一个周期=1s/2M即0.5us
	
 TIM_ClearITPendingBit(TIM2, TIM_IT_Update);    //清除中断标志 
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE );   //使能中断，必须有对应的中断服务函数，否则会GG
	
	TIM_Cmd(TIM2, DISABLE);   //定时器2使能
}

void TIM3_Config(void)
{
	
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
 //TIM_TimeBaseStructure.TIM_Period = 20000;   //10000/0.5=20000（10毫秒）
 TIM_TimeBaseStructure.TIM_Prescaler = 36-1;   //定时器主频为72M  分频系数为36 72M/36=2M
 TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;        //时钟分割，无用
 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;    //向上计数模式
 TIM_TimeBaseInit(TIM3, & TIM_TimeBaseStructure);     //一个周期=1s/2M即0.5us
	
 TIM_ClearITPendingBit(TIM3, TIM_IT_Update);    //清除中断标志 
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE );   //使能中断，必须有对应的中断服务函数，否则会GG
	
	TIM_Cmd(TIM3, DISABLE);   //定时器2使能
}

void TIM4_Config(void)
{
	
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 

 TIM_TimeBaseStructure.TIM_Prescaler = 36-1;   //定时器主频为72M  分频系数为36 72M/36=2M
 TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;        //时钟分割，无用
 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;    //向上计数模式
 TIM_TimeBaseInit(TIM4, & TIM_TimeBaseStructure);     //一个周期=1s/2M即0.5us
	
 TIM_ClearITPendingBit(TIM4, TIM_IT_Update);    //清除中断标志 
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE );   //使能中断，必须有对应的中断服务函数，否则会GG
	
	TIM_Cmd(TIM4, DISABLE);   //定时器2使能
}

void TIM5_Config(void)
{
	
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 

 TIM_TimeBaseStructure.TIM_Prescaler = 36-1;   //定时器主频为72M  分频系数为36 72M/36=2M
 TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;        //时钟分割，无用
 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;    //向上计数模式
 TIM_TimeBaseInit(TIM5, & TIM_TimeBaseStructure);     //一个周期=1s/2M即0.5us
	
 TIM_ClearITPendingBit(TIM5, TIM_IT_Update);    //清除中断标志 
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE );   //使能中断，必须有对应的中断服务函数，否则会GG
	
	TIM_Cmd(TIM5, DISABLE);   //定时器2使能
}

void TIM6_Config(void)
{
	
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 

 TIM_TimeBaseStructure.TIM_Prescaler = 36-1;   //定时器主频为72M  分频系数为36 72M/36=2M
 TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;        //时钟分割，无用
 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;    //向上计数模式
 TIM_TimeBaseInit(TIM6, & TIM_TimeBaseStructure);     //一个周期=1s/2M即0.5us
	
 TIM_ClearITPendingBit(TIM6, TIM_IT_Update);    //清除中断标志 
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE );   //使能中断，必须有对应的中断服务函数，否则会GG
	
	TIM_Cmd(TIM6, DISABLE);   //定时器2使能
}

void TIM7_Config(void)
{
	
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);
 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 

 TIM_TimeBaseStructure.TIM_Prescaler = 36-1;   //定时器主频为72M  分频系数为36 72M/36=2M
 TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;        //时钟分割，无用
 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;    //向上计数模式
 TIM_TimeBaseInit(TIM7, & TIM_TimeBaseStructure);     //一个周期=1s/2M即0.5us
	
 TIM_ClearITPendingBit(TIM7, TIM_IT_Update);    //清除中断标志 
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE );   //使能中断，必须有对应的中断服务函数，否则会GG
	
	TIM_Cmd(TIM7, DISABLE);   //定时器2使能
}


void TIM8_Config(void)
{
	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
 //TIM_TimeBaseStructure.TIM_Period = 20000;   //10000/0.5=20000（10毫秒）
 TIM_TimeBaseStructure.TIM_Prescaler = 36-1;   //定时器主频为72M  分频系数为36 72M/36=2M
 TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;        //时钟分割，无用
 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;    //向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x00;
 TIM_TimeBaseInit(TIM8, & TIM_TimeBaseStructure);     //一个周期=1s/2M即0.5us
	
 TIM_ClearITPendingBit(TIM8, TIM_IT_Update);    //清除中断标志 
	TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE );   //使能中断，必须有对应的中断服务函数，否则会GG
	
	TIM_Cmd(TIM8, DISABLE);   //定时器2使能
}


void TIM1_Period(unsigned int TimeLength)   //定时单位为us
{
	TIM1->ARR=TimeLength*2-1;
	
	
}

void TIM2_Period(unsigned int TimeLength)   //定时单位为us
{
	TIM2->ARR=TimeLength*2-1;
	
	
}

void TIM3_Period(unsigned int TimeLength)   //定时单位为us
{
	TIM3->ARR=TimeLength*2-1;
	
	
}

void TIM4_Period(unsigned int TimeLength)   //定时单位为us
{
	TIM4->ARR=TimeLength*2-1;
	
	
}

void TIM5_Period(unsigned int TimeLength)   //定时单位为us
{
	TIM5->ARR=TimeLength*2-1;
	
	
}

void TIM6_Period(unsigned int TimeLength)   //定时单位为us
{
	TIM6->ARR=TimeLength*2-1;
	
	
}

void TIM7_Period(unsigned int TimeLength)   //定时单位为us
{
	TIM7->ARR=TimeLength*2-1;
	
	
}

void TIM8_Period(unsigned int TimeLength)   //定时单位为us
{
	TIM8->ARR=TimeLength*2-1;
	
	
}


