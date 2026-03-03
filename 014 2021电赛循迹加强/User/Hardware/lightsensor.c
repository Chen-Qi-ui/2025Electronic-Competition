#include "lightsensor.h"

void sensorinit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//上拉输入模式
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
}


