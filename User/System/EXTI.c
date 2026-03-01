#include "stm32f10x.h"                  // Device header
#include "EXTI.h"


void EXTI0_GPIO_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
}

void EXTI1_GPIO_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
}

void EXTI0_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI0_GPIO_Init();
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);  //外部中断0的来源
 
  /* Configure EXTI0 line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0; //配置外部中断为外部中断0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;  //配置触发后进入中断
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //配置触发方式为下降延
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;  
  EXTI_Init(&EXTI_InitStructure);
	
}


void EXTI1_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI1_GPIO_Init();
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);  //外部中断1的来源
 
  /* Configure EXTI0 line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line1; //配置外部中断为外部中断1
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;  //配置触发后进入中断
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //配置触发方式为下降延
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;  
  EXTI_Init(&EXTI_InitStructure);
	
}

void EXTI11_GPIO_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
}

void EXTI11_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI1_GPIO_Init();
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);  //外部中断1的来源
 
  /* Configure EXTI0 line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line11 ; //配置外部中断为外部中断1
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;  //配置触发后进入中断
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //配置触发方式为下降延
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;  
  EXTI_Init(&EXTI_InitStructure);
	
}
