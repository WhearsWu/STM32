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
	delay_init();	    	 //��ʱ������ʼ��	
	OLED_Init();			//��ʼ��OLED  
	OLED_Clear(); 
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
										//LED0 = 0;                   //����
										//LED1 = 0; 
 	PWM_Init(); 	
 	Init_Duty;
  Snap_Init();               //�س̿��س�ʼ��
	Cap_Init(0XFFFF,72-1);		//��1Mhz��Ƶ�ʼ��� 
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
   // 	printf("Finally_cap.RollCount:%d us\r\n",CapCount.Roll);	//��תʱ�� (PA0)
   //	printf("Finally_cap.TranCount:%d us\r\n",CapCount.Tran);	//ƽ��ʱ��  (PA1)
	}
}
 


















