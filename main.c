#include <reg51.h>
#include "LCD.h"
#include "sys.h"
#include "FC.h"
#include "lcd.h"
#include "LCDfunction.h"
#include "els.h"
#include "plane.h"
int main (void){
	TMOD = 0X01;
	TH0 = (65536-20000)/256;
	TH1 = (65536-20000)%256;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
	while(1){
	
	
	
			planeMain();	
	
	}
	return 0;
}
void T0_time() interrupt 1{
	TH0 = (65536-20000)/256;
	TH1 = (65536-20000)%256;
	FCkey = Read_Key_1();
	FCkey_p = Read_Key_1();	
	cnt++;
	if(cnt==255)
		cnt=0;



}