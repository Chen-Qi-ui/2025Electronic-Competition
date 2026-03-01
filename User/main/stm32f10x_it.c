#include "stm32f10x_it.h"                  // Device header
#include "LED.h"
#include "UART.h"
#include "PID.h"
#include "Encoder.h"
#include "PWM.h"
#include "Motor.h"
#include "Track.h"
#include "SPI_OLED.h"
#include "Delay.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "Track.h"
extern PID_t Track;
void NVIC_Config(void)
{
  NVIC_InitTypeDef   NVIC_InitStructure;
	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;  //ÇÀÕ¼ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;   //ÏàÓ¦ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;  //ÇÀÕ¼ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;   //ÏàÓ¦ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;  //ÇÀÕ¼ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;   //ÏàÓ¦ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;  //ÇÀÕ¼ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;   //ÏàÓ¦ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;  //ÇÀÕ¼ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x04;   //ÏàÓ¦ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;  //ÇÀÕ¼ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x05;   //ÏàÓ¦ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;  //ÇÀÕ¼ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x06;   //ÏàÓ¦ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;  //ÇÀÕ¼ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x07;   //ÏàÓ¦ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;  //ÇÀÕ¼ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;   //ÏàÓ¦ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;  //ÇÀÕ¼ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;   //ÏàÓ¦ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;  //ÇÀÕ¼ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x04;   //ÏàÓ¦ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;  //ÇÀÕ¼ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;   //ÏàÓ¦ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;  //ÇÀÕ¼ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x06;   //ÏàÓ¦ÓÅÏÈ¼¶
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

unsigned int Timer1Counter=0;
unsigned int Timer2Counter = 0;
unsigned int Timer3Counter=0;
unsigned int Timer4Counter=0;
unsigned int Timer5Counter=0;
unsigned int Timer6Counter=0;
unsigned int Timer7Counter=0;
unsigned int Timer8Counter=0;
extern unsigned char Servo_Tx[5];
extern PID_t Inner1;
extern PID_t Outer1;
extern PID_t Inner2;
extern PID_t Outer2;
extern uint8_t Digital_Final;
unsigned int Usart4_Data = 0;
//void EXTI0_IRQHandler(void)  //Íâ²¿ÖÐ¶Ï0µÄ·þÎñº¯Êý
//{Servo_Tx


//   if(EXTI_GetITStatus(EXTI_Line0) != RESET)  //ÅÐ¶ÏÍâ²¿ÖÐ¶Ï0ÊÇ²»ÊÇ·¢Éú
//  {
//    LED4_Rev();  //È¡·´
// 
//     /* Clear the  EXTI line 0 pending bit */
//    EXTI_ClearITPendingBit(EXTI_Line0);  //Çå³ýÍâ²¿ÖÐ¶Ï0±êÖ¾
//  }


//	
//	
//}



//void EXTI1_IRQHandler(void)  //Íâ²¿ÖÐ¶Ï0µÄ·þÎñº¯Êý
//{


//   if(EXTI_GetITStatus(EXTI_Line1) != RESET)  //ÅÐ¶ÏÍâ²¿ÖÐ¶Ï0ÊÇ²»ÊÇ·¢Éú
//  {
//    LED3_Rev();  //È¡·´
// 
//     /* Clear the  EXTI line 0 pending bit */
//    EXTI_ClearITPendingBit(EXTI_Line1);  //Çå³ýÍâ²¿ÖÐ¶Ï0±êÖ¾
//  }

//	
//}





//void EXTI15_10_IRQHandler(void)  //Íâ²¿ÖÐ¶Ï0µÄ·þÎñº¯Êý
//{


//   if(EXTI_GetITStatus(EXTI_Line11) != RESET)  //ÅÐ¶ÏÍâ²¿ÖÐ¶Ï0ÊÇ²»ÊÇ·¢Éú
//  {
//    LED1_Rev();
//		
// 
//     /* Clear the  EXTI line 0 pending bit */
//    EXTI_ClearITPendingBit(EXTI_Line11);  //Çå³ýÍâ²¿ÖÐ¶Ï0±êÖ¾
//  }

//}


// ?TIM1???
unsigned int Car_State1 = 1;
float Last_Yaw = 0, Delta_Yaw = 0, Total_Yaw = 0;
extern float yaw, pitch, roll;
extern int8_t Flag_Turn;

void TIM1_UP_IRQHandler(void) {
    LED2_Rev();
    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);

    // ??????(?? ±180° ??)
    Delta_Yaw = yaw - Last_Yaw;
    
    // ??????(?????? 180°,???????)
    if (Delta_Yaw > 180.0f) {
        Delta_Yaw -= 360.0f; // ??:350° - (-10°) = 360° ? ??? 0°
    } 
    else if (Delta_Yaw < -180.0f) {
        Delta_Yaw += 360.0f; // ??:-170° - 170° = -340° ? ??? +20°
    }

    // ?????(??:????????)
    Total_Yaw += Delta_Yaw;

    // ??? Total_Yaw ? ±360° ??(??)
    if (Total_Yaw > 360.0f) Total_Yaw -= 360.0f;
    if (Total_Yaw < -360.0f) Total_Yaw += 360.0f;
		if(fabs(Total_Yaw)>=90)
		{
			Total_Yaw=90;
			yaw=0;
		}

    // ?? Last_Yaw ??? yaw
    Last_Yaw = yaw;
}



//void TIM2_IRQHandler(void)
//{
//	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);   //Çå³ýÖÐ¶Ï±êÖ¾
//	LED2_Rev();
//  		Inner2.Actual=Encoder2_Get();
//		PID_Update(&Inner2);
//    Speed_Final2=Inner2.Out;
//	  MotorInitPWMB();
//		MotorSet(2,2);
//	  setMotorSpeed(2,Inner2.Out);
//	

//}



//void TIM3_IRQHandler(void)
//{
//	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);   //Çå³ýÖÐ¶Ï±êÖ¾
//	Timer3Counter++;
//	if(Timer3Counter==100)
//	{
//		Timer3Counter=0;
//		LED2_Rev();
//	}
//	
//}

//void TIM4_IRQHandler(void)
//{
//	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);   //Çå³ýÖÐ¶Ï±êÖ¾
//	Timer4Counter++;
//	if(Timer4Counter==100)
//	{
//		Timer4Counter=0;
//		LED3_Rev();
//	}
//	
//}




//void TIM5_IRQHandler(void)
//{
//	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);   //Çå³ýÖÐ¶Ï±êÖ¾
//	Timer5Counter++;
//	if(Timer5Counter==100)
//	{
//		Timer5Counter=0;
//		LED4_Rev();
//	}
//	
//}

//void TIM6_IRQHandler(void)
//{
//	TIM_ClearITPendingBit(TIM6, TIM_IT_Update);   //Çå³ýÖÐ¶Ï±êÖ¾
//	Timer6Counter++;
//	if(Timer6Counter==100)
//	{
//		Timer6Counter=0;

//	}
//	
//}




//void TIM7_IRQHandler(void)
//{
//	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);   //Çå³ýÖÐ¶Ï±êÖ¾
//	Timer7Counter++;
//	if(Timer7Counter==100)
//	{
//		Timer7Counter=0;

//	}
//	
//}

unsigned char Usart1Data=0;
unsigned char Usart2Data=0;
unsigned char Usart3Data=0;
unsigned char Uart4Data=0;
unsigned char Uart5Data=0;
unsigned char Usart1Sta=0;
unsigned char Shiwei=0;
unsigned char Gewei=0;
unsigned char Shifenwei=0;
float Temp=0.0;
//void USART1_IRQHandler(void)
//{
//	

//	if(USART_GetITStatus(USART1, USART_IT_RXNE))    //ÅÐ¶ÏÊÇ·ñ½ÓÊÕµ½Êý¾Ý
//	{
//		USART_ClearITPendingBit(USART1,USART_IT_RXNE);   //Çå³ýÖÐ¶Ï½ÓÊÕ±êÖ¾
//    Usart1Data = USART_ReceiveData(USART1);     //¶ÁÈ¡½ÓÊÕµ½µÄÊý¾Ý
////		USART_SendByte(USART1,Usart1Data);    //½«½ÓÊÕµ½µÄÊý¾Ý·¢»ØÈ¥
//		LED1_Rev();
//		switch(Usart1Sta)
//		{
//			case 0:
//				if(Usart1Data == 0xaa)
//					Usart1Sta = 1;
//				break;
//				
//			case 1:
//			if(Usart1Data == 0xbb)
//				Usart1Sta = 2;
//			else
//				Usart1Sta=0;
//				break;
//			
//			case 2:
//		     Shiwei=Usart1Data;
//			   Usart1Sta=3;
//			break;
//			
//			case 3:
//			Gewei=Usart1Data;
//			   Usart1Sta=0;
//			break;
//			
//			default:break;
//		}
			
		
		
		
		
		
		
		
		
		
//		switch(Usart1Sta)
//		{
//			case 0:
//				if(Usart1Data == 'T')
//					Usart1Sta=1;
//				break;
//				
//			case 1:
//				Shiwei=Usart1Data-'0';
//			Usart1Sta=2;
//			break;
//			
//			case 2:
//				Gewei=Usart1Data-'0';
//			Usart1Sta=3;
//			break;
//			
//			case 3:
//				if(Usart1Data == '.')
//					Usart1Sta=4;
//				else
//					Usart1Sta=0;
//				break;
//			
//			case 4:
//				Shifenwei=Usart1Data-'0';
//			Usart1Sta=0;
//			Temp=Shiwei*10+Gewei*1+0.1*Shifenwei;
//			break;
//			default:break;
//		}
//	}
//	}
//}
//	}



//void USART2_IRQHandler(void)
//{
//	if(USART_GetITStatus(USART2, USART_IT_RXNE))    //ÅÐ¶ÏÊÇ·ñ½ÓÊÕµ½Êý¾Ý
//	{
//		USART_ClearITPendingBit(USART2,USART_IT_RXNE);   //Çå³ýÖÐ¶Ï½ÓÊÕ±êÖ¾
//    Usart2Data = USART_ReceiveData(USART2);     //¶ÁÈ¡½ÓÊÕµ½µÄÊý¾Ý
//		USART_SendByte(USART2,Usart2Data);    //½«½ÓÊÕµ½µÄÊý¾Ý·¢»ØÈ¥

//	}
//	
//}

//void USART3_IRQHandler(void)
//{
//	if(USART_GetITStatus(USART3, USART_IT_RXNE))    //ÅÐ¶ÏÊÇ·ñ½ÓÊÕµ½Êý¾Ý
//	{
//		USART_ClearITPendingBit(USART3,USART_IT_RXNE);   //Çå³ýÖÐ¶Ï½ÓÊÕ±êÖ¾
//    Usart3Data = USART_ReceiveData(USART3);     //¶ÁÈ¡½ÓÊÕµ½µÄÊý¾Ý
//		USART_SendByte(USART3,Usart3Data);    //½«½ÓÊÕµ½µÄÊý¾Ý·¢»ØÈ¥
//	}
//	
//}

int8_t Uart4Sta=0;
int8_t First=0;
int8_t Second=0;
int8_t Third=0;
int8_t Car_State0=0;
int8_t Car_State2=0;
void UART4_IRQHandler()
{
	if(USART_GetITStatus(UART4,USART_IT_RXNE))
	{
		USART_ClearITPendingBit(UART4,USART_IT_RXNE);
		Usart4_Data=USART_ReceiveData(UART4);
////		USART_SendByte(USART1,Usart1Data);    //½«½ÓÊÕµ½µÄÊý¾Ý·¢»ØÈ¥
		LED1_Rev();
		switch(Uart4Sta)
		{
			case 0:
      First = Usart4_Data;
			Car_State2 = First-'0';
			Uart4Sta = 1;
				break;
				
			case 1:
			if(Usart4_Data == 0xaa)
				Uart4Sta = 2;
				break;
			
			case 2:
		     Second=Usart4_Data;
			if(Second == Car_State2)
			{
				Car_State0=Second;
				Uart4Sta=3;
			}
			else{
			   Uart4Sta=3;
			}
			break;
			
			case 3:
			if(Usart4_Data == 0xbb)
				Uart4Sta = 4;
			break;
			
			case 4:
				Third = Usart4_Data;
			if(Third == First)
			{
				Car_State0=Third;
				Uart4Sta = 5;
			}
			else
			{
				Uart4Sta = 5;
			}
			break;
			
			default:break;
		}
		
	
}
	}



//void UART5_IRQHandler(void)
//{
//	if(USART_GetITStatus(UART5, USART_IT_RXNE))    //ÅÐ¶ÏÊÇ·ñ½ÓÊÕµ½Êý¾Ý
//	{
//		USART_ClearITPendingBit(UART5,USART_IT_RXNE);   //Çå³ýÖÐ¶Ï½ÓÊÕ±êÖ¾
//    Uart5Data = USART_ReceiveData(UART5);     //¶ÁÈ¡½ÓÊÕµ½µÄÊý¾Ý
//		USART_SendByte(UART5,Uart5Data);    //½«½ÓÊÕµ½µÄÊý¾Ý·¢»ØÈ¥
//	}
//	
//}
	static uint8_t is_initialized = 0; 
extern int16_t TurnLeft_Speed1 ;
extern int16_t TurnLeft_Location1;
extern int16_t TurnLeft_Speed2 ;
extern int16_t TurnLeft_Location2;	
extern int16_t TurnRight_Speed1 ;
extern int16_t TurnRight_Location1 ;
extern int16_t TurnRight_Speed2 ;
extern int16_t TurnRight_Location2 ;	
extern int16_t Location_1;
extern int16_t Location_2;
void TIM8_UP_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM8, TIM_IT_Update);   //Çå³ýÖÐ¶Ï±êÖ¾
	TwoCircles2_PID(&Inner2,&Outer2);
//if(Car_State2==1)
//	{
//	  switch(Car_State1)
//	{
//		case 1:
//			Outer1.OutMax=20;
//		  Outer1.OutMin=-20;
//			TwoCircles1_PID(&Inner1, &Outer1);
//			TwoCircles2_PID(&Inner2,&Outer2);
//		  if(fabs(Outer2.Actual)>fabs(Outer2.Target)-20)
//		{
//			Car_State1=2;
//			Outer2.Actual=0;
//			Outer1.Actual=0;
//		}
//		break;
//		
//		case 2:
//			Outer1.Target = 0;
//		  Outer2.Target = 0;
//		  MotorSet(1,0);
//		  MotorSet(2,0);
//		  if(fabs(Encoder1_Get())<=0&&fabs(Encoder2_Get()) <= 0)
//			{
//				Car_State1 = 3;
//			  Location_1=0;
//				Location_2=0;
//				
//			}
//			break;
//			
//		case 3:
//    if (!is_initialized) {
//      TurnLeft_Location1 = 0;
//			TurnLeft_Location2 = 0;
//			TurnRight_Location1 = 0;
//			TurnRight_Location2 = 0;
//        is_initialized = 1;  // ??????
//    }
//		Outer1.OutMax = 5;
//		Outer2.OutMax = 5;
//		Outer1.OutMin = -5;
//		Outer2.OutMin = -5;
//		PID2_TurnRight(&Inner2,&Outer2,90);
//		PID1_TurnRight(&Inner1, &Outer1, 90);
//				  if(fabs(Outer2.Actual)>(fabs(Outer2.Target)-20))
//		{
//			Car_State1=4;
//		}

//		break;
//		
//				case 4:
//			Outer1.Target = 0;
//		  Outer2.Target = 0;
//		  MotorSet(1,0);
//		  MotorSet(2,0);
//		  if(fabs(Encoder1_Get())<=0&&fabs(Encoder2_Get()) <= 0)
//			{
//				Car_State1 = 5;
//			}
//			break;
//		
//		case 5:
//		
//		   Outer2.Target=3400;
//		Outer2.OutMax = 20;
//		Outer2.OutMin = -20;
//		   TwoCircles2_PID(&Inner2,&Outer2);
//								    
//            Outer1.Target = 3400;
//		Outer1.OutMax = 20;
//		Outer1.OutMin = -20;
//            TwoCircles1_PID(&Inner1, &Outer1);
//		 if(fabs(Outer2.Actual)>fabs(Outer2.Target)-20)
//		{
//			Car_State1=6;
//			Location_1=0;
//			Location_2=0;
//		}
//		break;
//		
//		case 6:
//			Outer1.Target = 0;
//		  Outer2.Target = 0;
//		  MotorSet(1,0);
//		  MotorSet(2,0);
//		  if(fabs(Encoder1_Get())<=0&&fabs(Encoder2_Get()) <= 0)
//			{
//				Car_State1 = 7;
//			Location_1=0;
//			Location_2=0;
//			}
//			break;
//		
//		case 7:
//    if (!is_initialized) {
//      TurnLeft_Location1 = 0;
//			TurnLeft_Location2 = 0;
//			TurnRight_Location1 = 0;
//			TurnRight_Location2 = 0;
//        is_initialized = 1;  // ??????
//    }
//		Outer1.OutMax = 5;
//		Outer2.OutMax = 5;
//		Outer1.OutMin = -5;
//		Outer2.OutMin = -5;
//		PID2_TurnLeft(&Inner2,&Outer2,180);
//		PID1_TurnLeft(&Inner1, &Outer1, 180);
//				  if(fabs(Outer2.Actual)>(fabs(Outer2.Target)-20))
//		{
//			Car_State1=8;
//		}

//		break;
//		break;
//		
//		case 8:
//		Outer2.Target = 3400;
//    Outer1.Target = 3400;
//		Outer1.OutMax = 20;
//		Outer2.OutMax = 20;
//		Outer1.OutMin = -20;
//		Outer2.OutMin = -20;
//    TwoCircles1_PID(&Inner1, &Outer1);
//		TwoCircles2_PID(&Inner2,&Outer2);
//				 if(fabs(Outer2.Actual)>fabs(Outer2.Target)-20)
//		{
//			Car_State1=9;
//			Outer2.Actual=0;
//			Outer1.Actual=0;
//			Location_1=0;
//			Location_2=0;
//			Inner1.Actual=0;
//			Inner1.Actual=0;
//		}
//			break;
//			
//		case 9:
//    if (!is_initialized) {
//      TurnLeft_Location1 = 0;
//			TurnLeft_Location2 = 0;
//			TurnRight_Location1 = 0;
//			TurnRight_Location2 = 0;
//        is_initialized = 1;  // ??????
//    }
//		Outer1.OutMax = 5;
//		Outer2.OutMax = 5;
//		Outer1.OutMin = -5;
//		Outer2.OutMin = -5;
//		PID2_TurnLeft(&Inner2,&Outer2,90);
//		PID1_TurnLeft(&Inner1, &Outer1, 90);
//				  if(fabs(Outer2.Actual)>(fabs(Outer2.Target)-20))
//		{
//			Car_State1=10;
//		}

//		break;
//		
//				case 10:
//			Outer1.Target = 0;
//		  Outer2.Target = 0;
//		  MotorSet(1,0);
//		  MotorSet(2,0);
//		  if(fabs(Encoder1_Get())<=0&&fabs(Encoder2_Get()) <= 0)
//			{
//			Car_State1 = 11;
//			Location_1=0;
//			Location_2=0;
//			}
//			break;
//    
//		
//		case 11:
//		   Outer2.Target=5344;
//		Outer2.OutMax = 20;
//		   TwoCircles2_PID(&Inner2,&Outer2);
//            Outer1.Target = 5344;
//		Outer1.OutMax = 20;
//            TwoCircles1_PID(&Inner1, &Outer1);
//		 if(fabs(Outer2.Actual)>fabs(Outer2.Target)-20)
//		{
//			Car_State1=12;
//			Location_1=0;
//		}
//		break;
//		
//		case 12:
//		Inner2.Target=0;
//		MotorSet(2,0);
//		MotorSet(1,0);
//		break;
//		
//		default:break;
//			
//		
//		
//	}

//}

//	if(Car_State2==2)
//	{
//	  switch(Car_State1)
//	{
//		case 1:
//			Outer1.OutMax=20;
//		  Outer1.OutMin=-20;
//			TwoCircles1_PID(&Inner1, &Outer1);
//			TwoCircles2_PID(&Inner2,&Outer2);
//		  if(fabs(Outer2.Actual)>fabs(Outer2.Target)-20)
//		{
//			Car_State1=2;
//			Outer2.Actual=0;
//			Outer1.Actual=0;
//		}
//		break;
//		
//		case 2:
//			Outer1.Target = 0;
//		  Outer2.Target = 0;
//		  MotorSet(1,0);
//		  MotorSet(2,0);
//		  if(fabs(Encoder1_Get())<=0&&fabs(Encoder2_Get()) <= 0)
//			{
//				Car_State1 = 3;
//			  Location_1=0;
//				Location_2=0;
//				
//			}
//			break;
//			
//		case 3:
//    if (!is_initialized) {
//      TurnLeft_Location1 = 0;
//			TurnLeft_Location2 = 0;
//			TurnRight_Location1 = 0;
//			TurnRight_Location2 = 0;
//        is_initialized = 1;  // ??????
//    }
//		Outer1.OutMax = 5;
//		Outer2.OutMax = 5;
//		Outer1.OutMin = -5;
//		Outer2.OutMin = -5;
//		PID2_TurnLeft(&Inner2,&Outer2,90);
//		PID1_TurnLeft(&Inner1, &Outer1, 90);
//				  if(fabs(Outer2.Actual)>(fabs(Outer2.Target)-20))
//		{
//			Car_State1=4;
//		}

//		break;
//		
//				case 4:
//			Outer1.Target = 0;
//		  Outer2.Target = 0;
//		  MotorSet(1,0);
//		  MotorSet(2,0);
//		  if(fabs(Encoder1_Get())<=0&&fabs(Encoder2_Get()) <= 0)
//			{
//				Car_State1 = 5;
//			}
//			break;
//		
//		case 5:
//		
//		   Outer2.Target=3400;
//		Outer2.OutMax = 20;
//		Outer2.OutMin = -20;
//		   TwoCircles2_PID(&Inner2,&Outer2);
//								    
//            Outer1.Target = 3400;
//		Outer1.OutMax = 20;
//		Outer1.OutMin = -20;
//            TwoCircles1_PID(&Inner1, &Outer1);
//		 if(fabs(Outer2.Actual)>fabs(Outer2.Target)-20)
//		{
//			Car_State1=6;
//			Location_1=0;
//			Location_2=0;
//		}
//		break;
//		
//		case 6:
//			Outer1.Target = 0;
//		  Outer2.Target = 0;
//		  MotorSet(1,0);
//		  MotorSet(2,0);
//		  if(fabs(Encoder1_Get())<=0&&fabs(Encoder2_Get()) <= 0)
//			{
//				Car_State1 = 7;
//			Location_1=0;
//			Location_2=0;
//				Outer1.Actual=0;
//				Outer2.Actual=0;
//			}
//			break;
//		
//		case 7:
//    if (!is_initialized) {
//      TurnLeft_Location1 = 0;
//			TurnLeft_Location2 = 0;
//			TurnRight_Location1 = 0;
//			TurnRight_Location2 = 0;
//        is_initialized = 1;  // ??????
//    }
//		Outer1.OutMax = 5;
//		Outer2.OutMax = 5;
//		Outer1.OutMin = -5;
//		Outer2.OutMin = -5;
//		PID2_TurnRight(&Inner2,&Outer2,180);
//		PID1_TurnRight(&Inner1, &Outer1, 180);
//				  if(fabs(Outer2.Actual)>(fabs(Outer2.Target)-20))
//		{
//			Car_State1=8;
//		}

//		break;
////		Outer2.Target = -3400;
////    Outer1.Target = -3400;
////    TwoCircles1_PID(&Inner1, &Outer1);
////		TwoCircles2_PID(&Inner2,&Outer2);
////				 if(fabs(Outer2.Actual)>fabs(Outer2.Target)-20)
////		{
////			Car_State1=8;
////			Outer2.Actual=0;
////			Outer1.Actual=0;
////			Location_1=0;
////			Location_2=0;
////			Inner1.Actual=0;
////			Inner1.Actual=0;
////		}
//		break;
//		
//		case 8:
//		Outer2.Target = 3400;
//    Outer1.Target = 3400;
//		Outer1.OutMax = 20;
//		Outer2.OutMax = 20;
//		Outer1.OutMin = -20;
//		Outer2.OutMin = -20;
//    TwoCircles1_PID(&Inner1, &Outer1);
//		TwoCircles2_PID(&Inner2,&Outer2);
//				 if(fabs(Outer2.Actual)>fabs(Outer2.Target)-20)
//		{
//						Outer2.Actual=0;
//			Outer1.Actual=0;
//			Location_1=0;
//			Location_2=0;
//			Inner1.Actual=0;
//			Inner1.Actual=0;
//			Car_State1=9;
//		}
//			break;
//		
//				case 9:
//			Outer1.Target = 0;
//		  Outer2.Target = 0;
//		  MotorSet(1,0);
//		  MotorSet(2,0);
//		  if(fabs(Encoder1_Get())<=0&&fabs(Encoder2_Get()) <= 0)
//			{
//						Outer2.Actual=0;
//			Outer1.Actual=0;
//			Location_1=0;
//			Location_2=0;
//			Inner1.Actual=0;
//			Inner1.Actual=0;
//				Car_State1 = 10;
//				
//			}
//			break;
//			
//		case 10:
//    if (!is_initialized) {
//      TurnLeft_Location1 = 0;
//			TurnLeft_Location2 = 0;
//			TurnRight_Location1 = 0;
//			TurnRight_Location2 = 0;
//        is_initialized = 1;  // ??????
//    }
//		Outer1.OutMax = 5;
//		Outer2.OutMax = 5;
//		Outer1.OutMin = -5;
//		Outer2.OutMin = -5;
//		PID2_TurnRight(&Inner2,&Outer2,90);
//		PID1_TurnRight(&Inner1, &Outer1, 90);
//				  if(fabs(Outer2.Actual)>(fabs(Outer2.Target)-20))
//		{
//			Car_State1=11;
//		}

//		
//		break;
//		
//				case 11:
//			Outer1.Target = 0;
//		  Outer2.Target = 0;
//		  MotorSet(1,0);
//		  MotorSet(2,0);
//		  if(fabs(Encoder1_Get())<=0&&fabs(Encoder2_Get()) <= 0)
//			{
//			Car_State1 = 12;
//			Location_1=0;
//			Location_2=0;
//			}
//			break;
//    
//		
//		case 12:
//		   Outer2.Target=5344;
//		Outer2.OutMax = 20;
//		   TwoCircles2_PID(&Inner2,&Outer2);
//            Outer1.Target = 5344;
//		Outer1.OutMax = 20;
//            TwoCircles1_PID(&Inner1, &Outer1);
//		 if(fabs(Outer2.Actual)>fabs(Outer2.Target)-20)
//		{
//			Car_State1=13;
//			Location_1=0;
//		}
//		break;
//		
//		case 13:
//		Inner2.Target=0;
//		MotorSet(2,0);
//		MotorSet(1,0);
//		break;
//		
//		default:break;
//			
//		
//		
//	}

//}
//	







//if((Car_State2==3) || (Car_State2==4) || (Car_State2==5) || (Car_State2==6) || (Car_State2==7) || (Car_State2==8) )
//	{
//	  switch(Car_State1)
//	{
//		case 1:
//			Outer1.Target = 10000;
//		  Outer2.Target = 10000;
//			TwoCircles1_PID(&Inner1, &Outer1);
//			TwoCircles2_PID(&Inner2,&Outer2);
//		  if(fabs(Outer2.Actual)>fabs(Outer2.Target)-20)
//		{
//			Car_State1=14;
//			Outer2.Actual=0;
//			Outer1.Actual=0;
//		}
//		break;
//		
//		
//		
//		case 2:
//		Outer1.OutMax = 20;
//		Outer2.OutMax = 20;
//		Outer1.OutMin = -20;
//		Outer2.OutMin = -20;
//		   Outer2.Target=1500;
//		   TwoCircles2_PID(&Inner2,&Outer2);
//								    
//       Outer1.Target = 1500;
//       TwoCircles1_PID(&Inner1, &Outer1);
//		 if(fabs(Outer2.Actual)>fabs(Outer2.Target)-20)
//		{
//			Car_State1=3;
//			Location_1=0;
//		}
//		break;
//		
//		
//			case 3:
//			Outer1.Target = 0;
//		  Outer2.Target = 0;
//		  MotorSet(1,0);
//		  MotorSet(2,0);
//		Outer1.OutMax = 3;
//		Outer2.OutMax = 3;
//		Outer1.OutMin = -3;
//		Outer2.OutMin = -3;
//		  if(fabs(Encoder1_Get())<=0&&fabs(Encoder2_Get()) <= 0)
//			{
//			Car_State1 = 4;
//			Location_1=0;
//			Location_2=0;
//			}
//			break;
//		
//		case 4:
//			if(Car_State2==Second)
//			{
//		Outer1.OutMax = 3;
//				
//		Outer2.OutMax = 3;
//		Outer1.OutMin = -3;
//		Outer2.OutMin = -3;
//		PID2_TurnLeft(&Inner2,&Outer2,90);
//		PID1_TurnLeft(&Inner1, &Outer1, 90);
//				  if(fabs(Outer1.Actual)>(fabs(Outer1.Target)-20))
//		{
//			Location_1=0;
//			Location_2=0;
//			Car_State1=5;
//		}
//	}
//			
//	else if(Third == Car_State2)
//	{
//		PID2_TurnRight(&Inner2,&Outer2,90);
//		PID1_TurnRight(&Inner1, &Outer1, 90);
//				  if(fabs(Outer2.Actual)>(fabs(Outer2.Target)-20))
//		{
//			Location_1=0;
//			Location_2=0;
//			Car_State1=5;
//		}
//	}
//	
//		break;
//		
//				case 5:
//			Outer1.Target = 0;
//		  Outer2.Target = 0;
//		  MotorSet(1,0);
//		  MotorSet(2,0);
//		  if(fabs(Encoder1_Get())<=0&&fabs(Encoder2_Get()) <= 0)
//			{
//			Car_State1 = 6;
//			Location_1=0;
//			Location_2=0;
//			}
//			break;
//	
//	
//		case 6:
//		Outer1.OutMax = 20;
//		Outer2.OutMax = 20;
//		Outer1.OutMin = -20;
//		Outer2.OutMin = -20;
//		   Outer2.Target=3400;
//		   TwoCircles2_PID(&Inner2,&Outer2);
//								    
//       Outer1.Target = 3400;
//       TwoCircles1_PID(&Inner1, &Outer1);
//		 if(fabs(Outer2.Actual)>fabs(Outer2.Target)-20)
//		{
//			Car_State1=7;
//			Location_1=0;
//		}
//		break;
//		
//			case 7:
//			Outer1.Target = 0;
//		  Outer2.Target = 0;
//		  MotorSet(1,0);
//		  MotorSet(2,0);
//		  if(fabs(Encoder1_Get())<=0&&fabs(Encoder2_Get()) <= 0)
//			{
//							Location_1=0;
//			Location_2=0;
//				Outer1.Actual=0;
//				Outer2.Actual=0;
//				Outer1.OutMax = 0;
//		    Outer2.OutMax = 0;
//				Outer1.OutMin = -0;
//		    Outer2.OutMin = -0;
//			Car_State1 = 8;

//			}
//			break;
//		
//		case 8:		 // ????,??????
//    if (!is_initialized) {
//      TurnLeft_Location1 = 0;
//			TurnLeft_Location2 = 0;
//			TurnRight_Location1 = 0;
//			TurnRight_Location2 = 0;
//        is_initialized = 1;  // ??????
//    }
//		Outer1.OutMax = 3;
//		Outer2.OutMax = 3;
//		Outer1.OutMin = -3;
//		Outer2.OutMin = -3;
//		PID2_TurnRight(&Inner2,&Outer2,180);
//		PID1_TurnRight(&Inner1, &Outer1, 180);
//				  if(fabs(Outer2.Actual)>(fabs(Outer2.Target)-20))
//		{
//			Car_State1=9;
//		}
//	
//		break;
//	
//					case 9:
//			Outer1.Target = 0;
//		  Outer2.Target = 0;
//		  MotorSet(1,0);
//		  MotorSet(2,0);
//		  if(fabs(Encoder1_Get())<=0&&fabs(Encoder2_Get()) <= 0)
//			{
//			Car_State1 = 10;
//			Location_1=0;
//			Location_2=0;
//			}
//			break;
//		
//		
//		case 10:
//		Outer1.OutMax = 20;
//		Outer2.OutMax = 20;
//		Outer1.OutMin = -20;
//		Outer2.OutMin = -20;
//		Outer2.Target = 3400;
//    Outer1.Target = 3400;
//    TwoCircles1_PID(&Inner1, &Outer1);
//		TwoCircles2_PID(&Inner2,&Outer2);
//				 if(fabs(Outer2.Actual)>fabs(Outer2.Target)-20)
//		{
//			Car_State1=11;
//			Outer2.Actual=0;
//			Outer1.Actual=0;
//			Location_1=0;
//			Location_2=0;
//			Inner1.Actual=0;
//			Inner1.Actual=0;
//		}
//		break;
//		
//		
//			case 11:
//			Outer1.Target = 0;
//		  Outer2.Target = 0;
//		  MotorSet(1,0);
//		  MotorSet(2,0);
//		  if(fabs(Encoder1_Get())<=0&&fabs(Encoder2_Get()) <= 0)
//			{
//			Car_State1 = 12;
//			Location_1=0;
//			Location_2=0;
//			}
//			break;
//		
//		case 12:
//			if(Car_State2==Second)
//			{
//		Outer1.OutMax = 3;
//		Outer2.OutMax = 3;
//	  Outer1.OutMin = -3;
//		Outer2.OutMin = -3;
//		PID2_TurnRight(&Inner2,&Outer2,90);
//		PID1_TurnRight(&Inner1, &Outer1, 90);
//				  if(fabs(Outer2.Actual)>(fabs(Outer2.Target)-20))
//		{
//			Car_State1=13;
//			Location_1=0;
//			Location_2=0;
//		}
//	}
//			
//	else if(Third == Car_State2)
//	{
//		Outer1.OutMax = 3;
//		Outer2.OutMax = 3;
//	  Outer1.OutMin = -3;
//		Outer2.OutMin = -3;
//		PID2_TurnLeft(&Inner2,&Outer2,90);
//		PID1_TurnLeft(&Inner1, &Outer1, 90);
//				  if(fabs(Outer2.Actual)>(fabs(Outer2.Target)-20))
//		{
//			Car_State1=13;
//			Location_1=0;
//			Location_2=0;
//		}
//	}
//	
//		break;
//    
//		
//		case 13:
//		Outer1.OutMax = 20;
//		Outer2.OutMax = 20;
//		Outer1.OutMin = -20;
//		Outer2.OutMin = -20;
//	  Outer2.Target=10688;
//    TwoCircles2_PID(&Inner2,&Outer2);
//    Outer1.Target = 10688;
//    TwoCircles1_PID(&Inner1, &Outer1);
//		 if(fabs(Outer2.Actual)>fabs(Outer2.Target)-20)
//		{
//			Car_State1=15;
//			Location_1=0;
//		}
//		break;
//		
//			
//		case 14:
//		MotorSet(2,0);
//		MotorSet(1,0);
//		if(Second!=0)
//		{
//			Car_State1=2;
//		}
//		break;
//		default:		MotorSet(2,0);
//		MotorSet(1,0);break;
//			
//		
//		
//	}
//}
//    Track_Speed(&Track,&Inner1);
}

