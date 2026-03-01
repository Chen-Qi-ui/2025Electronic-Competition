#include "sensor.h"



void sensor_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);    //2ÊÇDAT

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOC, &GPIO_InitStructure);    //0ÊÇCLK
		
}

uint8_t gw_gray_serial_read( uint16_t gpio_clk, uint16_t gpio_dat)
{
    uint8_t ret = 0;
    
    for(uint8_t i = 0; i < 8; i++) {
        GPIO_ResetBits(GPIOC, gpio_clk);  // ?????
        Delayxus(1);  // ????
        
        // ????????
        if(GPIO_ReadInputDataBit(GPIOC, gpio_dat)) {
            ret |= (1 << (7-i));  // MSB first
        }
        
        GPIO_SetBits(GPIOC, gpio_clk);  // ?????
        Delayxus(1);  // ????
    }
    
    return ret;
}


