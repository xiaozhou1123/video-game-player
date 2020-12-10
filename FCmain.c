#include <reg52.h>
#include <intrins.h>

sbit Clock=P0^0;
sbit Latch=P0^1;
sbit Data=P0^2;

unsigned char Read_Key(void)
{
    unsigned char i,FC_Data =0;
	Data = 0;
	Clock = 0;
	Latch = 1;
	_nop_();
	_nop_();
	_nop_();		
	Latch = 0; 
	
	for(i=0;i<8;i++)
	{
	Clock = 0;
	_nop_();
	if(!Data)  //ÈôÓÐ¼ü°´ÏÂ
      FC_Data|=(0x01 << i);
	Clock = 1;
	_nop_();	
	}

	return FC_Data;
}

void main(void)
{
	unsigned char tmp=0;
	while(1)
	{
	tmp=Read_Key();
	
	if(tmp)
	   P3 = ~tmp;
	else
	   P3 = 0xff;
	}
}