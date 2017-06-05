#include "control.h"

fla flag = {1,1,0,0,1,0,0,0,0};
duty  dut = {0,0,0,0};
MotorStat M_R;
MotorStat M_T; 

/******比较坐标*******************/
void Wait_Arrive(coordinate exp)
{
	//Cap_Reset(); //捕获计数清零
	//Expect.Roll = x;
	//Expect.Tran = y;
	//Roll_Move(exp.Roll);
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
void Tran_Move(double y)
{
	u32 temp=0; 
	char dis[20];
	if(y > Curren.Tran+10)
	{
		Digital_TIM->CCR2 = Tran_corotation_dut;
		M_T.temp = tempP;
			GPIO_SetBits(GPIOA,GPIO_Pin_1);
			delay_ms(2);
			GPIO_ResetBits(GPIOA,GPIO_Pin_1); 	
		while(Curren.Tran <= y-13)
		{
				
			sprintf( dis,"%d",(u32)Curren.Tran);	//打印总的高点平时间
			OLED_ShowString(10,0,(u8*)dis);
			if(TIM2CH1_CAPTURE_STA&0X80)//成功捕获到了一次高电平
			{
				temp=TIM2CH1_CAPTURE_STA&0X3F;
				temp*=65536;					//溢出时间总和
				temp+=TIM2CH1_CAPTURE_VAL;		//得到总的高电平时间
				Curren.Tran = 0.17*temp;

				TIM2CH1_CAPTURE_STA=0;			//开启下一次捕获
					GPIO_SetBits(GPIOA,GPIO_Pin_1);
			delay_ms(2);
			GPIO_ResetBits(GPIOA,GPIO_Pin_1); 	
			}
		}
		Digital_TIM->CCR2 = Roll_stop_dut;
	}
	if(y < Curren.Tran-10)
	{
		Digital_TIM->CCR2 = Tran_inversion_dut;  
		M_T.temp = tempN;
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
		delay_ms(2);
		GPIO_ResetBits(GPIOA,GPIO_Pin_1); 	
		while(Curren.Tran >= y+10)
		{
			
		 
			sprintf( dis,"%d",(u32)Curren.Tran);	//打印总的高点平时间
			OLED_ShowString(10,0,(u8*)dis);
			if(TIM2CH1_CAPTURE_STA&0X80)//成功捕获到了一次高电平
			{
				temp=TIM2CH1_CAPTURE_STA&0X3F;
				temp*=65536;					//溢出时间总和
				temp+=TIM2CH1_CAPTURE_VAL;		//得到总的高电平时间
				Curren.Tran = 0.17*temp;

				TIM2CH1_CAPTURE_STA=0;			//开启下一次捕获
					GPIO_SetBits(GPIOA,GPIO_Pin_1);
			delay_ms(2);
			GPIO_ResetBits(GPIOA,GPIO_Pin_1); 	
			}
		}
		Digital_TIM->CCR2 = Roll_stop_dut;
	}
	else
		Digital_TIM->CCR2 = Roll_stop_dut;
	//Digital_TIM->CCR2 = Tran_corotation_dut; 


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

