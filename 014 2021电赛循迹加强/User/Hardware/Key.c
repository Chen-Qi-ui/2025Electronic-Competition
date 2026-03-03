#include "stm32f10x.h"                  // Device header
#include "Key.h"
#include "Delay.h"
#define KEY1_Pin GPIO_Pin_11
#define KEY2_Pin GPIO_Pin_10
#define KEY3_Pin GPIO_Pin_1
#define KEY4_Pin GPIO_Pin_0


void Key1_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE );
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode =GPIO_Mode_IPU  ;
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB ,&GPIO_Initstructure);

}

void Key2_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE );
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode =GPIO_Mode_IPU  ;
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB ,&GPIO_Initstructure);

}

void Key3_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE );
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode =GPIO_Mode_IPU  ;
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB ,&GPIO_Initstructure);

}

void Key4_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE );
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode =GPIO_Mode_IPU  ;
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB ,&GPIO_Initstructure);

}


unsigned char GetKey1Sta(void)
{
    return GPIO_ReadInputDataBit(GPIOB,KEY1_Pin);
	
}

unsigned char GetKey2Sta(void)
{
    return GPIO_ReadInputDataBit(GPIOB,KEY2_Pin);
	
}

unsigned char GetKey3Sta(void)
{
    return GPIO_ReadInputDataBit(GPIOB,KEY3_Pin);
	
}

unsigned char GetKey4Sta(void)
{
    return GPIO_ReadInputDataBit(GPIOB,KEY4_Pin);
	
}


unsigned char GetKeyVal(void)
{
	unsigned char KeyVal=0;
	if(GetKey1Sta()==0)
	{
		Delayxms(10);
		if(GetKey1Sta()==0)
			KeyVal=1;
		while(GetKey1Sta()==0);
	}
	
	if(GetKey2Sta()==0)
	{
		Delayxms(10);
		if(GetKey2Sta()==0)
			KeyVal=2;
		while(GetKey2Sta()==0);
	}
	
	if(GetKey3Sta()==0)
	{
		Delayxms(10);
		if(GetKey3Sta()==0)
			KeyVal=3;
		while(GetKey3Sta()==0);
	}
	
		if(GetKey4Sta()==0)
	{
		Delayxms(10);
		if(GetKey4Sta()==0)
			KeyVal=4;
		while(GetKey4Sta()==0);
	}
	return KeyVal;
}














