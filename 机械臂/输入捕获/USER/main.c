#include "led.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "control.h"
#include "coordinate.h"
#include "E39.h"
#include "bsp_usart1.h"
#include "oled.h"
 int main(void)
{	
	// u32 temp=0; 
	//char dis[20];
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();	    	 //延时函数初始化	
	OLED_Init();			//初始化OLED  
	OLED_Clear(); 
	LED_Init();		  	//初始化与LED连接的硬件接口
										//LED0 = 0;                   //亮灯
										//LED1 = 0; 
 	PWM_Init(); 	
 	Init_Duty;
  Snap_Init();               //回程开关初始化
	Cap_Init(0XFFFF,72-1);		//以1Mhz的频率计数 
  E39_int();
	
  while(1)
 {
	 Wait_Arrive(Expect);
	 
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
 


















