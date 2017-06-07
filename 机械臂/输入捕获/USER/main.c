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
	delay_init();	    	 //��ʱ������ʼ��	
	OLED_Init();			   //��ʼ��OLED  
	OLED_Clear(); 
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
										//LED0 = 0;                   //����
										//LED1 = 0; 
 	PWM_Init(); 	             //PWM
 	Init_Duty;
	//Snap_Init();               //�س̿���
	WaveInit();                //������
    //Adc_Init();
	ADCx_Init();
	E39_int();                 //����ͨ��
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
   // 	printf("Finally_cap.RollCount:%d us\r\n",CapCount.Roll);	//��תʱ�� (PA0)
   //	printf("Finally_cap.TranCount:%d us\r\n",CapCount.Tran);	//ƽ��ʱ��  (PA1)
	}
}
 


















