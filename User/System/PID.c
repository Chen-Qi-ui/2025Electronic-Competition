#include "stm32f10x.h"                  // Device header
#include "PID.h"
#include "Encoder.h"
#include "Motor.h"
#include "Track.h"
#include "math.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"

extern float yaw;
extern PID_t Inner1;
extern PID_t Inner2;
extern PID_t Outer1;
extern PID_t Outer2;
int16_t PID_Update(PID_t *p)
{
	float Kp_Out=0;
	float Ki_Out=0;
	float Kd_Out=0;
	p->Error1 = p->Error0;
	p->Error0 = p->Target - p->Actual;
	Kp_Out = p->Kp * p->Error0;
	
	Kd_Out = p->Kd*(p->Error0 - p->Error1);
	
	if(p->Kp !=0)
	{
		p->ErrorInt+=p->Error0;
	}
	else 
	{
		p->ErrorInt = 0;
	}
	Ki_Out = p->Ki * p->ErrorInt;
	
	p->Out = Kp_Out + Ki_Out + Kd_Out;
	
	if(p->ErrorInt > p->ErrorInt_Max){p->ErrorInt  = p->ErrorInt_Max;}
	if(p->ErrorInt < p->ErrorInt_Min){p->ErrorInt  = p->ErrorInt_Min;}
		if (p->Out > p->OutMax) {p->Out = p->OutMax;}	
	if (p->Out < p->OutMin) {p->Out = p->OutMin;}
	return p->Out ;
}
float PID_Speed1=0;
int16_t Location1 =0;
float Location1_Final =0;
void Location1_PID(PID_t *p_Location1)
{
	PID_Speed1 = Encoder1_Get();
	Location1 += PID_Speed1;
	p_Location1->Actual=Location1;
	PID_Update(p_Location1);
  Location1_Final = p_Location1->Out;
  MotorSet(1,Location1_Final);
	
}


float PID_Speed2=0;
int16_t Location2 =0;
float Location2_Final =0;
void Location2_PID(PID_t *p_Location2)
{
	PID_Speed2 = (float)Encoder2_Get();
	Location2 += PID_Speed2;
	p_Location2->Actual=Location2;
	PID_Update(p_Location2);
  Location2_Final = p_Location2->Out;
  MotorSet(2,Location2_Final);
}

float PID1_Speed1 = 0;
float Speed1_Final = 0;
void Speed1_PID(PID_t *p_Speed1)
{
	  PID1_Speed1=(float)Encoder1_Get();
    	if(p_Speed1->Target<0)
	{
		p_Speed1->Target = Track2_Err();
	}
		if(p_Speed1->Target>0)
	{
		p_Speed1->Target = Track1_Err();
	}
		p_Speed1->Actual=PID1_Speed1;
		PID_Update(p_Speed1);
    Speed1_Final=p_Speed1->Out;
    MotorSet(1,Speed1_Final);
	
	  
}


float PID2_Speed2 = 0;
float Speed2_Final = 0;
void Speed2_PID(PID_t *p_Speed2)
{
	  PID2_Speed2=(float)Encoder2_Get();

		p_Speed2->Actual=PID2_Speed2;
		PID_Update(p_Speed2);
    Speed2_Final=p_Speed2->Out;
    MotorSet(2,Speed2_Final);
	
	
}

void Specialspeed1_PID(PID_t *p_Speed1)
{
	  PID1_Speed1=(float)Encoder1_Get();
		p_Speed1->Actual=PID1_Speed1;
		PID_Update(p_Speed1);
    Speed1_Final=p_Speed1->Out;
    MotorSet(1,Speed1_Final);
	
	  
}
int16_t Speed1 = 0;
int16_t Location_1 = 0;
int16_t Speed_Final1 = 0;
int16_t Location_Final1 = 0;

void TwoCircles1_PID(PID_t *p_Speed1,PID_t *p_Location1)
{

		Speed1=(int16_t)Encoder1_Get();
		Location_1+=Speed1;

	  p_Speed1->Actual=Speed1;
		PID_Update(p_Speed1);
    Speed_Final1=p_Speed1->Out;
		MotorSet(1,Speed_Final1);


	
		p_Location1->Actual = Location_1;
		PID_Update(p_Location1);
		Location_Final1 = p_Location1->Out;
	if(p_Location1->Target<0)
	{
		p_Speed1->Target = Track2_Err();
	}
		if(p_Location1->Target>0)
	{
		p_Speed1->Target = Track1_Err();
	}
	  if(fabs(p_Location1->Actual)>fabs((p_Location1->Target)))
		{
			p_Speed1->Target=0;
			Location_1=0;
			Outer1.Actual=0;
		}
	
	


}
int16_t Speed2 = 0;
int16_t Location_2 = 0;
int16_t Speed_Final2 = 0;
int16_t Location_Final2 = 0;
void TwoCircles2_PID(PID_t *p_Speed2,PID_t *p_Location2)
{

		Speed2=(int16_t)Encoder2_Get();
		Location_2+=Speed2;
	

	  p_Speed2->Actual=Speed2;
		PID_Update(p_Speed2);
    Speed_Final2=p_Speed2->Out;
		MotorSet(2,Speed_Final2);


	
		p_Location2->Actual = Location_2;
		PID_Update(p_Location2);
		Location_Final2 = p_Location2->Out;
		p_Speed2->Target = p_Location2->Out;
	
	 	  if(fabs(p_Location2->Actual)>fabs(p_Location2->Target))
		{
			p_Speed2->Target=0;
			Location_2=0;
			Outer2.Actual=0;
		}
	}
	
	
	int16_t TurnRight_Speed1 =0;
int16_t TurnRight_Location1 = 0;
int16_t TurnRight_Speed2 =0;
int16_t TurnRight_Location2 = 0;
void PID2_TurnRight(PID_t *p_Speed2,PID_t *p_Location2,uint16_t angle)
{
	  p_Location2->Target = 5700*7.2*2*3.14*(angle-5)/360/80;
    TurnRight_Speed2=(int16_t)Encoder2_Get();
		TurnRight_Location2+=TurnRight_Speed2;
	

	  p_Speed2->Actual=TurnRight_Speed2;
		PID_Update(p_Speed2);
    Speed_Final2=p_Speed2->Out;
		MotorSet(2,Speed_Final2);


	
		p_Location2->Actual = TurnRight_Location2;
		PID_Update(p_Location2);
		Location_Final2 = p_Location2->Out;
		p_Speed2->Target = p_Location2->Out;
		 	  if(fabs(p_Location2->Actual)>fabs(p_Location2->Target))
		{
			p_Speed2->Target=0;
			TurnRight_Location2=0;
			Outer2.Actual=0;
		}

	
	
}


void PID1_TurnRight(PID_t *p_Speed1,PID_t *p_Location1,uint16_t angle)
{
	  p_Location1->Target = -5700*7.2*2*3.14*(angle-5)/360/80;
    TurnRight_Speed1=(int16_t)Encoder1_Get();
		TurnRight_Location1+=TurnRight_Speed1;
	

	  p_Speed1->Actual=TurnRight_Speed1;
		PID_Update(p_Speed1);
    Speed_Final1=p_Speed1->Out;

		MotorSet(1,Speed_Final1);


	
		p_Location1->Actual = TurnRight_Location1;
		PID_Update(p_Location1);
		Location_Final1 = p_Location1->Out;
p_Speed1->Target = p_Location1->Out;
	 	  if(fabs(p_Location1->Actual)>fabs(p_Location1->Target))
		{
			p_Speed1->Target=0;
			TurnRight_Location1=0;
			Outer1.Actual=0;
		}


	
	
	
	
	
}



int16_t TurnLeft_Speed1 =0;
int16_t TurnLeft_Location1 = 0;
int16_t TurnLeft_Speed2 =0;
int16_t TurnLeft_Location2 = 0;
void PID2_TurnLeft(PID_t *p_Speed2,PID_t *p_Location2,uint16_t angle)
{
	  p_Location2->Target = -5700*7.2*2*3.14*(angle-5)/360/80;

    TurnLeft_Speed2=(int16_t)Encoder2_Get();
		TurnLeft_Location2+=TurnLeft_Speed2;

	  p_Speed2->Actual=TurnLeft_Speed2;
		PID_Update(p_Speed2);
    Speed_Final2=p_Speed2->Out;
		MotorSet(2,Speed_Final2);


	
		p_Location2->Actual = TurnLeft_Location2;
		PID_Update(p_Location2);
		Location_Final2 = p_Location2->Out;
		p_Speed2->Target = p_Location2->Out;

	 		 	  if(fabs(p_Location2->Actual)>fabs(p_Location2->Target))
		{
			p_Speed2->Target=0;
			TurnLeft_Location2=0;
			Outer2.Actual=0;
		}
	
	
}


void PID1_TurnLeft(PID_t *p_Speed1,PID_t *p_Location1,uint16_t angle)
{
	  p_Location1->Target = 5700*7.2*2*3.14*(angle-5)/360/80;
    TurnLeft_Speed1=(int16_t)Encoder1_Get();
		TurnLeft_Location1+=TurnLeft_Speed1;
	

	  p_Speed1->Actual=TurnLeft_Speed1;
		PID_Update(p_Speed1);
    Speed_Final1=p_Speed1->Out;
		MotorSet(1,Speed_Final1);


	
		p_Location1->Actual = TurnLeft_Location1;
		PID_Update(p_Location1);
		Location_Final1 = p_Location1->Out;
p_Speed1->Target = p_Location1->Out;
	 	  if(fabs(p_Location1->Actual)>fabs(p_Location1->Target))
		{
			p_Speed1->Target=0;
			TurnLeft_Location1=0;
			Outer1.Actual=0;
		}

	
	
	
	
	}

	
	