#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"
/*LED1=PA3
  LED2=PA4
  LED3=PA5
	LED4=PA6*/
	
#define LED1_APB_GPIO   RCC_APB2Periph_GPIOA
#define LED1_Pin        GPIO_Pin_3
#define LED2_Pin        GPIO_Pin_4
#define LED3_Pin        GPIO_Pin_5
#define LED4_Pin        GPIO_Pin_6
#define LED1_GPIO       GPIOA
void LEDInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
GPIO_SetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
}

void LED1Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
GPIO_SetBits(GPIOA, GPIO_Pin_3 );
}

void LED2Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
GPIO_SetBits(GPIOA, GPIO_Pin_4 );
}

void LED3Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
GPIO_SetBits(GPIOA, GPIO_Pin_5);
}

void LED4Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
GPIO_SetBits(GPIOA, GPIO_Pin_6);
}


void LED1_OFF(void)
{
	GPIO_SetBits(LED1_GPIO,LED1_Pin);
}

void LED1_ON(void)
{
	GPIO_ResetBits(LED1_GPIO,LED1_Pin);
}

void LED2_OFF(void)
{
	GPIO_SetBits(LED1_GPIO,LED2_Pin);
}

void LED2_ON(void)
{
	GPIO_ResetBits(LED1_GPIO,LED2_Pin);
}
void LED3_OFF(void)
{
	GPIO_SetBits(LED1_GPIO,LED3_Pin);
}

void LED3_ON(void)
{
	GPIO_ResetBits(LED1_GPIO,LED3_Pin);
}

void LED1_Rev(void)
{
	if(GPIO_ReadInputDataBit(GPIOA,LED1_Pin)==1)
		GPIO_ResetBits(GPIOA,LED1_Pin);
	else
		GPIO_SetBits(GPIOA,LED1_Pin);
	
}

void LED2_Rev(void)
{
	if(GPIO_ReadInputDataBit(GPIOA,LED2_Pin)==1)
		GPIO_ResetBits(GPIOA,LED2_Pin);
	else
		GPIO_SetBits(GPIOA,LED2_Pin);
	
}

void LED3_Rev(void)
{
	if(GPIO_ReadInputDataBit(GPIOA,LED3_Pin)==1)
		GPIO_ResetBits(GPIOA,LED3_Pin);
	else
		GPIO_SetBits(GPIOA,LED3_Pin);
	
}

void LED4_Rev(void)
{
	if(GPIO_ReadInputDataBit(GPIOA,LED4_Pin)==1)
		GPIO_ResetBits(GPIOA,LED4_Pin);
	else
		GPIO_SetBits(GPIOA,LED4_Pin);
	
}

void LED(unsigned char Location)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6);
	GPIO_Write(GPIOA,~(0x0008)<<(Location-1));
}














