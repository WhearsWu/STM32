
// ADC 6ͨ���ɼ�ʵ��

#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_adc.h"
#include "sys.h"
#include "delay.h"
#include "24l01.h"
#include "oled.h"
#include "E39.h"
// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue[macNOFCHANEL];

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal[macNOFCHANEL];        

// �����ʱ
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
uint16_t i;
//uint16_t Cx = 0,Cy = 0;
int main(void)
{					 
	//uint8_t tmp_buf[4];
	delay_init(72);
	// ���ô���
	E39_int();
	
	//NRF24L01_Init();    //��ʼ��NRF24L01 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	OLED_Init();			//��ʼ��OLED  
	OLED_Clear(); 
	// ADC ��ʼ��
//	ADCx_Init();

	//printf("\r\n RX\r\n");
	
	//OLED_ShowChar(0,2,2);
	//while(NRF24L01_Check());//��ⲻ��24L01
	//RX_Mode();

	while (1)
	{			
	//printf("5");
		/*
		GPIOA->CRL = 0x3030;//C0C2 PP   C1C3AIN
		GPIOA->ODR = 0x02;//C0=1 C2=0


		ADC1->SQR3 = 0x00;
		ADC1->CR2 |= 0X40000;
		Delay(2);
		Cy = (double)ADC_ConvertedValue[0]/4096.0*88.0;
		

		GPIOA->CRL = 0x0303;//C0C2 PP   C1C3AIN
		GPIOA->ODR = 0x01;//C0=1 C2=0
		ADC1->SQR3 = 0x01;
		ADC1->CR2 |= 0X40000;
		Delay(2);
		Cx = (double)ADC_ConvertedValue[1]/4096.0*154.0;
		
		printf("x=%f\ny=%f/n",Cx,Cy);

		tmp_buf[0] = Cx;
		tmp_buf[1] = Cy;
		tmp_buf[2] = 0;
		NRF24L01_TxPacket(tmp_buf);
		
		Delay(1000000);
		*/
		/*
		if(NRF24L01_RxPacket(tmp_buf)==0)//һ�����յ���Ϣ,����ʾ����.
			{
				Cx = (tmp_buf[0]<<4) | (tmp_buf[1]>>4);
				Cy = ((tmp_buf[1]&0x0f)<<8) | tmp_buf[2];
				//printf("X:%d\n",Cx);
				//printf("Y:%d\n",Cy);
				OLED_ShowChar(0,0,Cx);
				OLED_ShowChar(0,20,Cy);
			}
			*/
	}
}
/*********************************************END OF FILE**********************/

