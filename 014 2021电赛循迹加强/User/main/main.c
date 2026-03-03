#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"
#include "Sysclock.h"
#include "Key.h"
#include "EXTI.h"
#include "stm32f10x_it.h"
#include "TIMX.h"
#include "SPI_OLED.h"
#include "PWM.h"
#include "UART.h"
#include "ADC.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "PID.h"
#include "Motor.h"
#include "Encoder.h"
#include "sensor.h"
#include "IIC24C64.h"
PID_t Inner1 = {		
	.Target = 20,
	.Kp = 0.3,					
	.Ki = 0.5,					
	.Kd = 0,			
  .ErrorInt_Max = 300,	
	 .ErrorInt_Min = -300,
	.OutMax = 100,				
	.OutMin = -100,		
	.Out=0,
};

PID_t Outer1 = {		
  .Target = 5344,		
	.Kp = 0.3,				
	.Ki = 0,					
	.Kd = 0.4,				
	.ErrorInt_Max = 300,
	.ErrorInt_Min = -300,
	.OutMax = 20,			
	.OutMin = -20,
	.Out = 0,
};


PID_t Inner2 = {		
	.Target = 20,
	.Kp = 0.3,					
	.Ki = 0.5,					
	.Kd = 0,			
  .ErrorInt_Max = 300,
.ErrorInt_Min = -300,	
	.OutMax = 100,				
	.OutMin = -100,		
	.Out = 0,
};

PID_t Outer2 = {		
  .Target = 5344,		  //5700为80cm
	.Kp = 0.3,					
	.Ki = 0,					
	.Kd = 0.4,					
	.ErrorInt_Max = 300,
	.ErrorInt_Min = -300,
	.OutMax =20,
	.OutMin = -20,
  .Out = 0,	
};


extern unsigned int Timer1Counter;
extern unsigned int Timer8Counter;
extern unsigned int Car_State;

extern int8_t Uart4Sta;
extern int8_t First;
extern int8_t Second;
extern int8_t Third;
extern int8_t Car_State0;
extern int8_t Car_State2;
extern float yaw;
void SystemConfig(void)
{
	RCC_HSE_Config();
//// EXTI0_Config();
//// EXTI1_Config();
//// EXTI11_Config();
     NVIC_Config();
	ADC1_Configuration();
	ADC1_CHInit(13);

    LEDInit();
//	/*Key1_Init();
//	Key2_Init();
//	Key3_Init();
////	Key4_Init();*/
   TIMx_Config();
	
//	PWM3_Init(5000);   //周期50ms，不超过65ms
//	PWM3_IO_Init();
	OLED12864_Init();
	OLED12864_TurnBias(0x7f);
	OLED12864_Clean();
//	MPU6050_Init();
//  mpu_dmp_init();
//  IIC24C64_Init();
//	USART2_Configuration(0);
//	USART3_Configuration(0);
	USART4_Configuration();
//	USART5_Configuration();
MotorInitPWMA();
MotorInitPWMB();
Encoder1_Init();
Encoder2_Init();
sensor_init();
}
unsigned int GetDataCounter=0;
float pitch=0,roll=0,yaw=0;
extern float Total_Yaw;
extern float Last_Yaw;
int8_t Flag_Turn;
//void GetPRY(void)
//{
//	mpu_dmp_get_data(&pitch,&roll,&yaw);
//}

extern int16_t delta;
uint8_t Digital_Final0 = 0;
uint8_t Digital_Final1 = 0;
extern unsigned char Shiwei;
extern unsigned char Gewei;
extern unsigned int Usart4_Data;
extern unsigned int Car_State;
extern int16_t Location_2;
extern int16_t Location_1;
extern int16_t TurnRight_Location2;
extern int16_t TurnRight_Location1;
extern unsigned int Car_State1;
int main()
{
	   
  SystemConfig();
	
//	Outer.Actual = 0;
////  GPIO_SetBits(GPIOB,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
//	GPIO_ResetBits(GPIOB,GPIO_Pin_9|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
	unsigned int Digital=0;

	while(1)
	{
//		mpu_dmp_get_data(&pitch,&roll,&yaw);
		
//		LED2_Rev();
//		OLED12864_Format1(0,0,0,Inner.Actual);
		
//		OLED12864_Format1(0,0,0,Encoder_Get());
//   OLED12864_Format1(0,0,0,Speed_Final);
		

//    Delayxms(1000);
		Digital = gw_gray_serial_read(GPIOC, GPIO_Pin_0, GPIO_Pin_2);

  
		Digital_Final0 = (uint8_t)(Digital&0xFF);
		OLED12864_Format1(0,0,0,Inner1.Target);
		OLED12864_Format1(0,12,0, Inner1.Actual);
    OLED12864_Format1(0,24 , 0, Inner1.Out);
		OLED12864_Format1(48,0,0,Inner2.Target);
		OLED12864_Format1(48,12,0, Inner2.Actual);

    OLED12864_Format1(48,24 , 0, Inner2.Out);
				OLED12864_Format1(0,36,0,Outer1.Target);
		OLED12864_Format1(0,48,0, Outer1.Target);
OLED12864_Format1(0,48,0, Outer1.Actual);
						OLED12864_Format1(48,36,0,Outer2.Target);
		OLED12864_Format1(48,48,0, Outer2.Actual);

//		OLED12864_Format1(80,0,0, Uart4Sta);
//		OLED12864_Format1(85,12,0, Car_State2);
		OLED12864_Format1(85,24,0, Car_State1);
		OLED12864_Format1(85,36,0, Second);
//		OLED12864_Format1(85,48,0, Third);
//		OLED12864_Format1(80,48,0, Car_State0);
   OLED12864_Format1(85,48,0, Outer1.OutMax);






	}
}