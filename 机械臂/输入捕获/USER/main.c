#include "led.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "control.h"
#include "coordinate.h"
#include "E39.h"
#include "bsp_usart1.h"
#include "oled.h"
#include "wave.h"
#include "bsp_adc.h"
 int main(void)
{	
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();	    	 //延时函数初始化	
	OLED_Init();			   //初始化OLED  
	OLED_Clear(); 
	LED_Init();		  	//初始化与LED连接的硬件接口
										//LED0 = 0;                   //亮灯
										//LED1 = 0; 
 	PWM_Init(); 	             //PWM
 	Init_Duty;
	//Snap_Init();               //回程开关
	WaveInit();                //超声波
    //Adc_Init();
	ADCx_Init();
	E39_int();                 //无线通信
	Expect.Tran = 300;
	
  while(1)
 {
	 //Get_voltage();
	if(ReFlag)
	{
		Wait_Arrive(Expect);
		ReFlag = 0;
	}
	 //GetCoor();
//	if(flag.MoveFinish == 0)
//	{
//	 Wait_Arrive(coor.Newx,coor.Newy); 
//	 flag.MoveFinish = 1;  
//	 flag.GetCoorFinish = 0;
//	}
/*		
		if(flag.affirm)
		{
		  switch(flag.GetBall)
			{
			  case 0:  
				{
				 GetBall();  
				 return_Attitude(); 
				}break;
				case 1: 
				{
					ReaseBall(); 
				  return_Attitude();
				}break;
			}
			flag.affirm = 0;
		}
*/		
   // 	printf("Finally_cap.RollCount:%d us\r\n",CapCount.Roll);	//旋转时间 (PA0)
   //	printf("Finally_cap.TranCount:%d us\r\n",CapCount.Tran);	//平移时间  (PA1)
	}
}
 


















