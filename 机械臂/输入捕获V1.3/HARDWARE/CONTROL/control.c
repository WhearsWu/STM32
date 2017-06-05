#include "control.h"
#include "coordinate.h"
#include "timer.h"
#include "delay.h"
fla flag = {1,1,0,0,1,0,0,0,0};
duty  dut = {0,0,0,0};
MotorStat M_R;
MotorStat M_T; 

/******比较坐标*******************/
void Wait_Arrive(double x,double y)
{
	//Cap_Reset(); //捕获计数清零
	Expect.Roll = x;
	Expect.Tran = y;
	Roll_Move(x);
	Tran_Move(y);
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
	if(Expect.Roll > Curren.Roll)
	{
		Digital_TIM->CCR1 = Roll_corotation_dut;
		M_R.temp = tempP;
	}
	else
	{
		Digital_TIM->CCR1 = Roll_inversion_dut;
		M_R.temp = tempN;
	}
	while(Curren.Roll <= ang);   //条件苛刻可能永远也达不到
		Digital_TIM->CCR1 = 0;
}
void Tran_Move(double y)
{
//		switch(flag.TranTurn)
//	{
//		case 0: Digital_TIM->CCR2 = Tran_inversion_dut; break;
//		case 1: Digital_TIM->CCR2 = Tran_corotation_dut; break;
//	}
	if(Expect.Tran > Curren.Tran)
	{
		Digital_TIM->CCR2 = Tran_corotation_dut;
		M_T.temp = tempP;
	}
	else
	{
		Digital_TIM->CCR2 = Tran_inversion_dut;  
		M_T.temp = tempN;
	}		
	//Digital_TIM->CCR2 = Tran_corotation_dut; 
 	while(Curren.Tran <= y);
	Digital_TIM->CCR2 = 0;

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

