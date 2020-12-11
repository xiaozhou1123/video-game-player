#include <reg51.h>
#include <intrins.h>
#include "FC.h"
sbit Clock_1=P1^0;
sbit Latch_1=P1^1;
sbit Data_1=P1^2;//手柄一引脚定义

sbit Clock_2=P1^3;
sbit Latch_2=P1^4;
sbit Data_2=P1^5;//手柄二引脚定义
unsigned char Read_Key_1(void)
{
    unsigned char i,FC_Data_1 =0;
	Data_1 = 0;
	Clock_1 = 0;
	Latch_1 = 1;
	_nop_();
	_nop_();
	_nop_();		
	Latch_1 = 0; 
	
	for(i=0;i<8;i++)
	{
	Clock_1 = 0;
	_nop_();
	if(!Data_1)  //若有键按下
      FC_Data_1|=(0x01 << i);
	Clock_1 = 1;
	_nop_();	
	}

	return FC_Data_1;
}
unsigned char Read_Key_2(void)
{
    unsigned char i,FC_Data_2 =0;
	Data_2 = 0;
	Clock_2 = 0;
	Latch_2 = 1;
	_nop_();
	_nop_();
	_nop_();		
	Latch_2 = 0; 
	
	for(i=0;i<8;i++)
	{
	Clock_2 = 0;
	_nop_();
	if(!Data_2)  //若有键按下
      FC_Data_2|=(0x01 << i);
	Clock_2 = 1;
	_nop_();	
	}

	return FC_Data_2;
}

