#include "PID.h"
void PID_Init(PID_TypDef *PID)//��ʼ��PID�ṹ�����
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
	PID->Currn = currn;//��TIM3CCR�Ĵ�����ȡ������
	PID->Expect = exp;
	PID->Err0 = PID->Expect - PID->Currn;//���=ʵ���ٶ���Ŀ���ٶȵĲ�
	PID->ErrInt += PID->Err0;
	output =(PID->Kp*PID->Err0 + PID->Ki*PID->ErrInt + PID->Kd*(PID->Err0-PID->Err1));
	PID->Err1 = PID->Err0;//��ǰ������һ���
	return output;
}

