
// ADC 6通道采集实验

#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_adc.h"
#include "sys.h"
#include "delay.h"
#include "24l01.h"
#include "E39.h"
// ADC1转换的电压值通过MDA方式传到SRAM
//extern __IO uint16_t ADC_ConvertedValue[macNOFCHANEL];
extern __IO uint16_t ADC_ConvertedValue;
uint16_t ADC_PDO = 0;
uint16_t ADC_PD;
// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal[macNOFCHANEL];        

// 软件延时
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
uint16_t Cx = 0,Cy = 0;
int main(void)
{					 
//	char tmp_buf[20];
	delay_init(72);
	// 配置串口
	E39_int();
	
	//NRF24L01_Init();    //初始化NRF24L01 
	
	// ADC 初始化
	ADCx_Init();

	//printf("\r\n ----这是一个ADC多通道采集实验----\r\n");
	
	//while(NRF24L01_Check());//检测不到24L01
	//TX_Mode();
	GPIOA->CRL &= 0xFF0000FF;
	GPIOA->CRL |= 0x00333300;//A2A3 PP   A0 A1 AIN
	while (1)
	{			
		/*
		GPIOA->CRL &= 0xFFFF0000;
		GPIOA->CRL |= 0x00003030;//C0C2 PP   C1C3AIN
		GPIOA->ODR |= 0x02;//A1=1 A3=0


		ADC1->SQR3 = 0x00;
		ADC1->CR2 |= 0X40000;
		Delay(2);
		Cy = ADC_ConvertedValue[0]/4096.0*+;
		//黑白Y  红灰X

		GPIOA->CRL &= 0xFFFF0000;//C0C2 PP   C1C3AIN
		GPIOA->CRL |= 0x00000303;
		GPIOA->ODR |= 0x01;//A0=0 A2=1
		ADC1->SQR3 = 0x01;
		ADC1->CR2 |= 0X40000;
		Delay(2);
		Cx = ADC_ConvertedValue[1]/4096.0*480;
		*/
		

		//GPIOA->ODR |= 0x038;//A2=0 A3=1 A4=4 A5=1
		GPIOA->BSRR = 0x40038;//A2=0 A3=1 A4=4 A5=1

		Delay(100);
		ADC_Cmd(macADCx, DISABLE);
		ADC_RegularChannelConfig(macADCx, macADC_CHANNEL1, 1, ADC_SampleTime_71Cycles5);
		ADC_Cmd(macADCx, ENABLE);
		ADC_SoftwareStartConvCmd(macADCx, ENABLE);
		Delay(100);
		ADC_PD = ADC_ConvertedValue;
		if(ADC_ConvertedValue!=0x00)
		{
			Delay(1000);
			//ADC_SoftwareStartConvCmd(macADCx, DISABLE);
			//GPIOA->CRL |= 0x00003030;//A1A3 PP   A0A1AIN
			GPIOA->BSRR = 0xC0030;//A2=0 A3=0 A4=4 A5=1
			//ADC1->SQR3 = 0x00;
			//ADC1->CR2 |= 0X40000;
			//ADC_Cmd(macADCx, DISABLE);
			ADC_SoftwareStartConvCmd(macADCx, ENABLE);
 			Delay(1000);
			
			Cx = ADC_ConvertedValue/3475.4*640;
			

			GPIOA->BSRR = 0x30000C;//A2=1 A3=1 A4=0 A5=0
			ADC_Cmd(macADCx, DISABLE);
			ADC_RegularChannelConfig(macADCx, macADC_CHANNEL2, 1, ADC_SampleTime_71Cycles5);
			ADC_Cmd(macADCx, ENABLE);
			ADC_SoftwareStartConvCmd(macADCx, ENABLE);
			Delay(100);
			Cy = ADC_ConvertedValue/3475.4*480;
			
		
			printf("x=%d,y=%d%c",Cx,Cy,0xf5);
			//                        printf("x=%d,y=%d\n",Cx,Cy);
/*
			tmp_buf[0] = ADC_ConvertedValue[1]>>4;
			tmp_buf[1] = ((ADC_ConvertedValue[1]&0xf)<<4)|(ADC_ConvertedValue[0]>>8);
			tmp_buf[2] = ADC_ConvertedValue[0]&0xff;
			tmp_buf[3] = 0;
*/			GPIOA->BSRR = 0x40038;//A2=0 A3=1 A4=4 A5=1
			Delay(100);
			ADC_Cmd(macADCx, DISABLE);
			ADC_RegularChannelConfig(macADCx, macADC_CHANNEL1, 1, ADC_SampleTime_71Cycles5);
			ADC_Cmd(macADCx, ENABLE);
			while(ADC_ConvertedValue!=0x00)
			{
				ADC_SoftwareStartConvCmd(macADCx, ENABLE);
				Delay(100);
			}
			Delay(1000000);
		}
		else
			Delay(1000);
		ADC_PDO = ADC_PD;
	}
}
/*********************************************END OF FILE**********************/

