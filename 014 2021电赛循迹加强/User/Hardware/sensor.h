#ifndef __sensor_h__
#define __sensor_h__
#include "stm32f10x.h"

void sensor_init(void);
uint8_t gw_gray_serial_read(GPIO_TypeDef *GPIOx, uint16_t gpio_clk, uint16_t gpio_dat);


#endif
