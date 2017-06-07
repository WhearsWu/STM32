#include "E39.h"

void E39_GPIOConfig()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* config USART1 clock */
	E39_APBxClock_FUN(E39_GPIO_CLK , ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  M0_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(M0_PORT, &GPIO_InitStructure);    
	
	GPIO_InitStructure.GPIO_Pin = M1_PIN;
	GPIO_Init(M1_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = AUX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(AUX_PORT, &GPIO_InitStructure);
}
void E39_Mode0()
{
	GPIOA->ODR &= ~0x1800;	
}
void E39_Mode1()
{
	GPIOA->ODR |= 0x1000;
}
void E39_int()
{
	USARTx_Config();
	E39_GPIOConfig();
	E39_Mode0();
}
char rx_buf[20];
uint16_t num = 0;
uint16_t STSPflag = 0;
uint16_t Cx = 0,Cy = 0;
u16 ReFlag = 0;
//char dis[5];
void macUSART_IRQHandler()
{
	if(USART_GetITStatus(macUSARTx,USART_IT_RXNE)!=RESET)
	{		
		rx_buf[num] = USART_ReceiveData(macUSARTx);
		//scanf("0xaax%dy%d0xff",Cx,Cy);
		if(rx_buf[num]==0x0a)
		{			
			//num=0x00;
			//sscanf(rx_buf,"x=%d,y=%d",&Cx,&Cy);
			//sscanf(rx_buf,"x=%lf,y=%lf",&Recive.Roll,&Recive.Tran);
			sscanf(rx_buf,"%lf,%lf",&Recive.Roll,&Recive.Tran);
			//coor.OldCountRoll = coor.NewCountRoll;
			//coor.OldCountTran = coor.NewCountTran;
			CoorTurn(Recive,&Expect);
			ReFlag = 1;
			for(;num!=0;num--)
				rx_buf[num]=0;
			//flag.MoveFinish = 1;  
			//flag.GetCoorFinish = 0;
			
		//sprintf(dis,"x=%d ",Cx);
		//OLED_ShowString(10,0,dis);
		//sprintf(dis,"y=%d ",Cy);
		//OLED_ShowString(60,0,dis);
		}
		else
			num++;
	}		
}
