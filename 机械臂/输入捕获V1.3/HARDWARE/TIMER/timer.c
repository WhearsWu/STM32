#include "timer.h"
#include "led.h"
#include "usart.h"
#include "sys.h"
#include "coordinate.h"
extern MotorStat M_R;
extern MotorStat M_T; 
void PWM_Init()
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_Servo_TIM  , ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_Servo_GPIO , ENABLE); 
	                                                                     	
	GPIO_InitStructure.GPIO_Pin = Digital_PIN_GPIO ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Digital_GPIO , &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = Analog_PIN_GPIO ;
	GPIO_Init(Analog_GPIO  , &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = Digital_Servo_arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =Digital_Servo_psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(Digital_TIM, &TIM_TimeBaseStructure);
	
	TIM_TimeBaseStructure.TIM_Period = Analog_Servo_arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =Analog_Servo_psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(Analog_TIM, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 0;  //占空比
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High ; 
	TIM_OC1Init(Digital_TIM , &TIM_OCInitStructure); 
  TIM_OC2Init(Digital_TIM , &TIM_OCInitStructure);  	
	TIM_OC1Init(Analog_TIM, &TIM_OCInitStructure); 
	TIM_OC2Init(Analog_TIM, &TIM_OCInitStructure);  

  TIM_CtrlPWMOutputs(Digital_TIM,ENABLE);	
  TIM_CtrlPWMOutputs(Analog_TIM,ENABLE);	

	TIM_OC1PreloadConfig(Digital_TIM, TIM_OCPreload_Enable); 
	TIM_OC2PreloadConfig(Digital_TIM, TIM_OCPreload_Enable);
	TIM_OC1PreloadConfig(Analog_TIM, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(Analog_TIM, TIM_OCPreload_Enable);  
	
	TIM_ARRPreloadConfig(Digital_TIM, ENABLE);
	TIM_ARRPreloadConfig(Analog_TIM, ENABLE); 
	TIM_Cmd(Digital_TIM, ENABLE); 
	TIM_Cmd(Analog_TIM, ENABLE); 
   
}
/********判断相位**************/
void Phase_Init(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_Phase_GPIO,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = Phase_Roll_GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
 	GPIO_Init(Phase_GPIO , &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = Phase_Tran_GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
 	GPIO_Init(Phase_GPIO, &GPIO_InitStructure);	
} 

TIM_ICInitTypeDef  TIM2_ICInitStructure;

void Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//使能TIM2时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIOA时钟
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1 ;  //PA0 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 输入  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);						 //PA0 下拉
	
	//初始化定时器2 TIM2	 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	//初始化TIM2输入捕获参数
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
	TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
	TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
	
	TIM_ITConfig(TIM2,TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	TIM_ITConfig(TIM2,TIM_IT_CC2,ENABLE);
	
  TIM_Cmd(TIM2,ENABLE ); 	//使能定时器2
 
}

//capture CapCount = {0,0,0,0,0,0};
void Cap_Reset()
{
	Curren.Roll = 0;
	//Curren.RollOverFlow = 0;
	Curren.Tran  = 0;
	//Curren.TranOverFlow = 0;
}
//定时器5中断服务程序	 
void TIM2_IRQHandler(void)
{ 
	if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{	
			//CapCount.Roll =CapCount.Roll + 1;	   			
			if(M_R.temp == tempP)
				Curren.Roll += K_roll;
			else
				Curren.Roll -= K_roll;
			TIM_ClearITPendingBit(TIM2, TIM_IT_CC1); //清除中断标志位		
		}
	if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)//捕获2发生捕获事件
		{	
			//CapCount.Tran =CapCount.Tran + 1;		
			if(M_T.temp == tempP)
				Curren.Tran += 1;//K_roll;
			else
				Curren.Tran -= 1;//K_roll;		
			TIM_ClearITPendingBit(TIM2, TIM_IT_CC2); //清除中断标志位	
		}
}
/**********正反相位*****************/
//void TIM2_IRQHandler(void)
//{ 
//	if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
//		{	
//			switch(Read_Phase_Roll_GPIO)
//			{
//				case 0:CapCount.Roll =CapCount.Roll + 1;	 	break;
//				case 1:CapCount.Roll =CapCount.Roll - 1;	    break;
//			}	    	   			
//      TIM_ClearITPendingBit(TIM2, TIM_IT_CC1); //清除中断标志位
//		}
//	if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)//捕获2发生捕获事件
//		{	
//			switch(Read_Phase_Tran_GPIO)
//			{
//				case 0:CapCount.Tran =CapCount.Tran + 1;		break;
//				case 1:CapCount.Tran =CapCount.Tran - 1;		break;
//			}
//        CapCount.Tran =CapCount.Tran + 1;				
//      TIM_ClearITPendingBit(TIM2, TIM_IT_CC2); //清除中断标志位
//		}
//}
