#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "led.h"
#include "rcc.h"
#include "key.h"
#include "delay.h"
#include "exti.h"
#include "SPI_OLED.h"
#include "OLED_Font.h"
#include "timx.h"
#include "pwm.h"
#include "adc.h"
#include "UART.h"
#include "sensor.h"

extern float Temp;
//extern kalman_filter ADC_kalman;
//#define Sys_Voltage 3.30

uint8_t key_val,key_down,key_up,key_old;
uint8_t key_val_flag;
uint16_t led_val=GPIO_Pin_3;
uint8_t led_flag=1;
float test;

void key_proc(void);
void led_proc(void);
void oled_proc(void);

void SystemConfig(void)
{
	ledinit();
	keyinit();
	OLED12864_Init();
	PA1_Init();
	
//	ADC1_Configuration();
//	ADC1_CHInit(13);
	
	OLED12864_Clean();
	OLED12864_TurnBias(0x7f);
	rcc_hse_config();//72mhz
	nvic_config();//中断优先级配置
	timx_config();
//	exti0_config();//配置外部中断
	exti1_config();
//	exti3_config();
//	USART1_Configuration(0);
//	USART4_Configuration();
	
//方波输出，作业1
	PWM3Init(1000);  //PB4,1ms周期,最大为65536微秒
	PWM3IOInit(1,1);
	PWM3Output(1,280);
	
	sensor_init();
}

void led_proc(void)
{
	if(led_flag)
	{
	if(key_val_flag==1)
		{
			for(int i=0;i<4;i++)
			{
				int j=1;
				led_offdisp(j<<(i-1));
				led_disp(j<<i);
				Delayxms(100);
			}
			ledinit();
		}
	if(key_val_flag==2)
		{
			for(int i=4;i>0;i--)
			{
				int j=1;
				led_offdisp(j<<(i));
				led_disp(j<<(i-1));
				Delayxms(100);
			}
			ledinit();
		}
	}
}

void key_proc(void)
{
	
	key_val=key_scan();
	key_down=key_val&(key_old^key_val);
	key_up=~key_val&(key_old^key_val);
	key_old=key_val;
	
	if(key_down==1)
	{
		key_val_flag=1;
	}
	if(key_down==2)
	{
		key_val_flag=2;
	}
	if(key_down==3)
	{
		led_flag=0;
	}
	if(key_down==4)
	{
		led_flag=1;
	}
	
}

void oled_proc(void)
{

//	OLED12864_Format2(0,8,0,i);
//	OLED12864_Format4(0,16,0,test);
//	OLED12864_BigFormat1(30,8,0,i);
//	OLED12864_BigFormat4(
//	test+=0.01;
//	Delayxms(1000);
	
}
extern unsigned char Usart_Data;
unsigned short ADC_CH0_Val=0;
unsigned short ADC_CH1_Val=0;
unsigned char Servo_Rx[5]={0};
unsigned char Usart4sta=0;

unsigned int sec,min,hour;
unsigned int T=0;
unsigned int Timer3Counter_old;
unsigned int PWM_Duty;
int main(void)
{
	
	SystemConfig();
	Servo_Rx[0]='S';
	unsigned int i;
	float voltage=0.0;
	float sysvoltag=0.0;
//	unsigned char Usart4sta=0.0;
	unsigned int Digtal;
	
	while(1)
	{
		Digtal = gw_gray_serial_read(GPIOC, GPIO_Pin_10, GPIO_Pin_2);
		OLED12864_Format1(0,8,0,(Digtal>>3)&0x01);//第三个灯
	};
}



