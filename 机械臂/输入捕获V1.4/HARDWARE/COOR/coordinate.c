#include "coordinate.h"


//coordinate coor = {0,0,0,0,0,0,0,0};
coordinate Curren;
coordinate Expect;
coordinate Recive;
/*
void GetCoor()
{ 
 //通信
	//coor.P_pixel = 600;
	//coor.O_pixel = 400;

	if(coor.P_pixel || coor.O_pixel) //坐标有效
	{
		coor.OldCountRoll = coor.NewCountRoll;
		coor.OldCountTran = coor.NewCountTran;
		if(coor.P_pixel)
		  coor.NewCountRoll = K_roll*atan(coor.P_pixel/coor.O_pixel);
		else
			coor.NewCountRoll = K_roll*90;
		coor.NewCountTran = K_tran*(320-sqrt(pow(coor.P_pixel-320,2)+pow(coor.O_pixel-240,2)));
		
		flag.MoveFinish = 0;           //开始动作
	}
	
}
*/
void CoorTurn(coordinate sorc,coordinate *dis)
{
		dis->Roll = sorc.Roll;
		dis->Tran = sorc.Tran;
/*	
	if(coor.P_pixel)
		coor.NewCountRoll = K_roll*atan(coor.P_pixel/coor.O_pixel);
	else
		coor.NewCountRoll = K_roll*90;
	coor.NewCountTran = K_tran*(320-sqrt(pow(coor.P_pixel-320,2)+pow(coor.O_pixel-240,2)));
*/
}
