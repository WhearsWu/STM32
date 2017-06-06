#include "PID.h"
void PID_Init(PID_TypDef *PID)//初始化PID结构体参数
{
	PID->Expect = 0;
	PID->Currn = 0;
	PID->Err0 = 0.0;
	PID->Err1 = 0.0;
	PID->Expect = 0.0;
	PID->Kp = 0;
	PID->Ki = 0;
	PID->Kd = 0;
}
double PID_run(PID_TypDef* PID,double exp,double currn)
{
	double output = 0;
	PID->Currn = currn;//从TIM3CCR寄存器获取解码器
	PID->Expect = exp;
	PID->Err0 = PID->Expect - PID->Currn;//误差=实际速度与目标速度的差
	PID->ErrInt += PID->Err0;
	output =(PID->Kp*PID->Err0 + PID->Ki*PID->ErrInt + PID->Kd*(PID->Err0-PID->Err1));
	PID->Err1 = PID->Err0;//当前误差赋给下一误差
	return output;
}

