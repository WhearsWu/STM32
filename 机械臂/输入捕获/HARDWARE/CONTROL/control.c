#include "control.h"

fla flag = {1,1,0,0,1,0,0,0,0};
duty  dut = {0,0,0,0};
MotorStat M_R;
MotorStat M_T; 


/******比较坐标*******************/
void Wait_Arrive(coordinate exp)
{

	
	Tran_Move(exp.Tran);	
	
}
void Roll_Move(double ang)
{
	PID_TypDef RollPID;
	TempType motortemp = tempP; 
	double speed;
	double err;
	PID_Init(&RollPID);
	RollPID.Kp = 0.35;
	if(ang>Curren.Roll)
	{
		motortemp = tempP;
	}
	if(ang<Curren.Roll)
	{
		motortemp = tempN;
	}
	while((err = fabs(ang-Curren.Tran))>2)
	{
		err = fabs(ang-Curren.Tran);	
		speed = PID_run(&RollPID,0,err*(-1));
		RollMotorControl(speed,motortemp);
	}
}
char dis_con[20];
void Tran_Move(double y)
{
	PID_TypDef TranPID;
	TempType motortemp = tempP; 
	double speed;
	double err;
	PID_Init(&TranPID);
	TranPID.Kp = 0.35;
	if(y>Curren.Tran)
	{
		motortemp = tempP;
	}
	if(y<Curren.Tran)
	{
		motortemp = tempN;
	}
	while((err = fabs(y-Curren.Tran))>2)
	{	
		speed = PID_run(&TranPID,0,err*(-1));
		MoveMotorControl(speed,motortemp);
	}
}
void RollMotorControl(double per,TempType turn)
{

	if(per)
	{
		if(turn)
		{
			if(per>=100)
				Digital_TIM->CCR2 = 100;
			else
				Digital_TIM->CCR2 = 78+0.22*per;
		}
		else
		{
			if(per>=100)
				Digital_TIM->CCR2 = 52;
			else
				Digital_TIM->CCR2 = 74-0.22*per;
		}
	}
	else
		Digital_TIM->CCR2 = 0;    //0~30  74~78  122~1000 都行
}
void MoveMotorControl(double per,TempType turn)
{

	if(per)
	{
		if(turn)
		{
			if(per>=100)
				Digital_TIM->CCR2 = 100;
			else
				Digital_TIM->CCR2 = 78+0.22*per;
		}
		else
		{
			if(per>=100)
				Digital_TIM->CCR2 = 52;
			else
				Digital_TIM->CCR2 = 74-0.22*per;
		}
	}
	else
		Digital_TIM->CCR2 = 0;    //0~30  74~78  122~1000 都行
}
void Change_Duty(u16 Roll_duty,u16 Tran_duty,u16 Down_duty,u16 Get_duty)
{
  Digital_TIM->CCR1 = Roll_duty;  //PA6
	Digital_TIM->CCR2  = Tran_duty; //PA7
	Analog_TIM->CCR1 = Down_duty;   //PB6
	Analog_TIM->CCR2 = Get_duty;    //PB7
}
/******回归原点**************/
void return_Attitude() 
{
//	Digital_TIM->CCR1 = Roll_inversion_dut;
//	while(flag.RollBegin);
//	Digital_TIM->CCR1 = 0;
	
	Digital_TIM->CCR2 = Tran_inversion_dut; 
	while(flag.RightMax);
	Digital_TIM->CCR2 = 0;
	//怎么测在起始位置？
}
/********抓球**************/
void GetBall()      
{
	Analog_TIM->CCR1 = Servo_Down_dut;
	delay_ms(1000);
	Analog_TIM->CCR2 = Servo_Close_dut;
	delay_ms(1000);
	Analog_TIM->CCR1 = Servo_Up_dut;
	delay_ms(1000);
}
/********放球*************/
void ReaseBall()
{
	Analog_TIM->CCR1 = Servo_Down_dut;
	delay_ms(1000);
	Analog_TIM->CCR2 = Servo_Open_dut;
	delay_ms(1000);
	Analog_TIM->CCR1 = Servo_Up_dut;
	delay_ms(1000);
}

