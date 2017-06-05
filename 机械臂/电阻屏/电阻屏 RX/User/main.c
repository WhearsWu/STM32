
// ADC 6通道采集实验

#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_adc.h"
#include "sys.h"
#include "delay.h"
#include "24l01.h"
#include "oled.h"
#include "E39.h"
// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue[macNOFCHANEL];

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
uint16_t i;
//uint16_t Cx = 0,Cy = 0;
int main(void)
{					 
	//uint8_t tmp_buf[4];
	delay_init(72);
	// 配置串口
	E39_int();
	
	//NRF24L01_Init();    //初始化NRF24L01 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	OLED_Init();			//初始化OLED  
	OLED_Clear(); 
	// ADC 初始化
//	ADCx_Init();

	//printf("\r\n RX\r\n");
	
	//OLED_ShowChar(0,2,2);
	//while(NRF24L01_Check());//检测不到24L01
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
		if(NRF24L01_RxPacket(tmp_buf)==0)//一旦接收到信息,则显示出来.
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

