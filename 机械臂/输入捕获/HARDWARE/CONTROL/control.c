#include "control.h"

fla flag = {1,1,0,0,1,0,0,0,0};
duty  dut = {0,0,0,0};
MotorStat M_R;
MotorStat M_T; 

PID_TypDef TranPID;
/******比较坐标*******************/
void Wait_Arrive(coordinate exp)
{
	//double speed;
	PID_Init(&TranPID);
	TranPID.Kp = 0.35;
	//double err = 0;
	//Cap_Reset(); //捕获计数清零
	//Expect.Roll = x;
	//Expect.Tran = y;
	//Roll_Move(exp.Roll);
	
	//Tran_Move(exp.Tran);
	
	Tran_Move(exp.Tran);	
	
}
void Roll_Move(double ang)
{
//	switch(flag.RollTurn)
//	{
//		case 0: Digital_TIM->CCR1 = Roll_inversion_dut; break;
//		case 1: Digital_TIM->CCR1 = Roll_corotation_dut; break;
//	}
	//double err;
	//err = Expect.Roll - Curren.Roll;	
	if(ang > Curren.Roll)
	{
		Digital_TIM->CCR1 = Roll_corotation_dut;
		M_R.temp = tempP;
		while(Curren.Roll <= ang);   //条件苛刻可能永远也达不到
		Digital_TIM->CCR1 = 0;
	}
	if(ang < Curren.Roll)
	{
		Digital_TIM->CCR1 = 0;
		M_R.temp = tempN;
		while(Curren.Roll >= ang);   //条件苛刻可能永远也达不到
		Digital_TIM->CCR1 = Roll_stop_dut;
	}
	else
		Digital_TIM->CCR1 = 0;

}
char dis_con[20];
void Tran_Move(double y)
{
	TempType motortemp = tempP; 
	double speed;
	double err;
	
	//char dis[20];
	//double err = 0;
	//err = y-Curren.Tran;
	if(y>Curren.Tran)
	{
		//Digital_TIM->CCR2 = Tran_corotation_dut;
		//M_T.temp = tempP;
		motortemp = tempP;
	}
	if(y<Curren.Tran)
	{
		//Digital_TIM->CCR2 = Tran_inversion_dut;  
		//M_T.temp = tempN;
		motortemp = tempN;
	}
	do
	{
		err = fabs(y-Curren.Tran);
		
		speed = PID_run(&TranPID,0,err*(-1));
		//sprintf(dis_con,"Roll=%3d",(u16)speed);
		//OLED_ShowString(0,0,(u8*)dis_con);
		moto_control(speed,motortemp);
	}while(err>2);
	Digital_TIM->CCR2 = 0;
	//Digital_TIM->CCR2 = Tran_corotation_dut; 
}
void moto_control(double per,TempType turn)
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

