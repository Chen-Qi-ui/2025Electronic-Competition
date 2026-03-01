#include "stm32f10x.h"                  // Device header
#include "Sysclock.h"
void RCC_HSE_Config(void)
{
	RCC_DeInit();
	RCC_HSEConfig (RCC_HSE_ON);
	if(RCC_WaitForHSEStartUp()==SUCCESS)
	{
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PCLK2Config(RCC_HCLK_Div1);
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);
		RCC_PLLCmd(ENABLE );
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		while(RCC_GetSYSCLKSource ()!=0x08);
	}
	
	
	
	
	
	
	
}