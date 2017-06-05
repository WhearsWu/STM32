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
	E39_Mode1();
}
uint8_t rx_buf[20];
uint16_t num = 0;
uint16_t STSPflag = 0;
void macUSART_IRQHandler()
{
	if(USART_GetITStatus(macUSARTx,USART_IT_RXNE)!=RESET)
	{		
		;
	}		
}
