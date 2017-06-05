#include "coordinate.h"


//coordinate coor = {0,0,0,0,0,0,0,0};
coordinate Curren;
coordinate Expect;
coordinate Recive;
/*
void GetCoor()
{ 
 //通信
	//coor.P_pixel = 600;
	//coor.O_pixel = 400;

	if(coor.P_pixel || coor.O_pixel) //坐标有效
	{
		coor.OldCountRoll = coor.NewCountRoll;
		coor.OldCountTran = coor.NewCountTran;
		if(coor.P_pixel)
		  coor.NewCountRoll = K_roll*atan(coor.P_pixel/coor.O_pixel);
		else
			coor.NewCountRoll = K_roll*90;
		coor.NewCountTran = K_tran*(320-sqrt(pow(coor.P_pixel-320,2)+pow(coor.O_pixel-240,2)));
		
		flag.MoveFinish = 0;           //开始动作
	}
	
}
*/
void CoorTurn(coordinate sorc,coordinate *dis)
{
		dis->Roll = sorc.Roll;
		dis->Tran = sorc.Tran;
/*	
	if(coor.P_pixel)
		coor.NewCountRoll = K_roll*atan(coor.P_pixel/coor.O_pixel);
	else
		coor.NewCountRoll = K_roll*90;
	coor.NewCountTran = K_tran*(320-sqrt(pow(coor.P_pixel-320,2)+pow(coor.O_pixel-240,2)));
*/
}
void ReFlahCoor()
{
	u32 temp = 0;
	char dis[20];
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	delay_ms(2);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1); 	
	if(TIM2CH1_CAPTURE_STA&0X80)//成功捕获到了一次高电平
	{
		temp=TIM2CH1_CAPTURE_STA&0X3F;
		temp*=65536;					//溢出时间总和
		temp+=TIM2CH1_CAPTURE_VAL;		//得到总的高电平时间
		Curren.Tran = 0.17*temp;
		TIM2CH1_CAPTURE_STA=0;			//开启下一次捕获
		sprintf(dis,"%d",(u32)Curren.Tran);	//打印总的高点平时间
		OLED_ShowString(10,0,(u8*)dis);
	}
}
