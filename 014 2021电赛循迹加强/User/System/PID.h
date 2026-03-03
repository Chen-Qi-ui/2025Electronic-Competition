#ifndef __PID_H__
#define __PID_H__

typedef struct {
	int16_t Target;
	int16_t Actual;
	int16_t Out;
	
	float Kp;
	float Ki;
	float Kd;
	
	int16_t Error0;
	int16_t Error1;
	int16_t ErrorInt;
	int16_t ErrorInt_Max;
	int16_t ErrorInt_Min;
	
	int16_t OutMax;
	int16_t OutMin;
} PID_t;

int16_t PID_Update(PID_t *p);
void Location1_PID(PID_t *p_Location1);
void Location2_PID(PID_t *p_Location2);
void Speed1_PID(PID_t *p_Speed1);
void Speed2_PID(PID_t *p_Speed2);
void TwoCircles1_PID(PID_t *p_Speed1,PID_t *p_Location1);
void TwoCircles2_PID(PID_t *p_Speed2,PID_t *p_Location2);
void PID1_TurnLeft(PID_t *p_Speed1,PID_t *p_Location1,uint16_t angle);
void PID2_TurnLeft(PID_t *p_Speed2,PID_t *p_Location2,uint16_t angle);
void PID1_TurnRight(PID_t *p_Speed1,PID_t *p_Location1,uint16_t angle);
void PID2_TurnRight(PID_t *p_Speed2,PID_t *p_Location2,uint16_t angle);
void Specialspeed1_PID(PID_t *p_Speed1);
void Track_Speed(PID_t *Track,PID_t *p_Speed1);
#endif