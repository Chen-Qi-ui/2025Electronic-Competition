#include "motor.h"
#include "PWM.h"
#include "LED.h"
//PC1: AIN1 PC2:AIN2 PB9:BIN1 PB5:BIN2
//PA2:PWMB PB8:PWMA
void MotorInitPWMB(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//Define GPIO Structure
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_3;//Config Port
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//PP OutPut
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;//Config Port
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//PP OutPut
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
	PWM2Init(100);
	PWM2IOInit(3,0);//PA2

	

}

void MotorInitPWMA(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1| GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // PWM ?? PB8 ? TIM4_CH3
    PWM3Init(100);
    PWM3IOInit(1, 1);   // PA15
}

void MotorSet(unsigned char motor, int8_t Speed)
{
	LED1_Rev(); 
    if (motor == 1)
    {
        if (Speed < 0) // ??
        {
            GPIO_SetBits(GPIOC, GPIO_Pin_1); // AIN1 = 1
            GPIO_ResetBits(GPIOC, GPIO_Pin_12); // AIN2 = 0
            PWM3Output(1, -Speed); // PWM ?????
        }
        else if (Speed > 0) // ??
        {
            GPIO_ResetBits(GPIOC, GPIO_Pin_1); // AIN1 = 0
            GPIO_SetBits(GPIOC, GPIO_Pin_12); // AIN2 = 1
            PWM3Output(1, Speed); // PWM ?????
        }
        else // ??? 0,????
        {
            GPIO_ResetBits(GPIOC, GPIO_Pin_1); // AIN1 = 0
            GPIO_ResetBits(GPIOC, GPIO_Pin_12); // AIN2 = 0
            PWM3Output(1, 0); // PWM ?? 0
        }
    }
    else if (motor == 2)
    {
        if (Speed < 0) // ??
        {
            GPIO_SetBits(GPIOB, GPIO_Pin_5); // BIN1 = 1
            GPIO_ResetBits(GPIOB, GPIO_Pin_3); // BIN2 = 0
            PWM2Output(3, -Speed); // PWM ?????
        }
        else if (Speed > 0) // ??
        {
            GPIO_ResetBits(GPIOB, GPIO_Pin_5); // BIN1 = 0
            GPIO_SetBits(GPIOB, GPIO_Pin_3); // BIN2 = 1
            PWM2Output(3, Speed); // PWM ?????
        }
        else // ??? 0,????
        {
            GPIO_ResetBits(GPIOB, GPIO_Pin_3); // BIN1 = 0
            GPIO_ResetBits(GPIOB, GPIO_Pin_9); // BIN2 = 0
            PWM2Output(3, 0); // PWM ?? 0
        }
    }
}


