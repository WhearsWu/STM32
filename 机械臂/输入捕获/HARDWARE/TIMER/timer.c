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
//capture CapCount = {0,0,0,0,0,0};
void Cap_Reset()
{
	Curren.Roll = 0;
	//Curren.RollOverFlow = 0;
	Curren.Tran  = 0;
	//Curren.TranOverFlow = 0;
}
