#include <reg51.h>
#include <stdlib.h>
//#include <time.h>
#include "LCD.h"
#include "sys.h"
#include "FC.h"
#include "lcd.h"
//#include "font.h"
#include "LCDfunction.h"

//***********************************************游戏相关*******************************//
//***********************************************游戏相关*******************************//
//***********************************************游戏相关*******************************//
//***********************************************游戏相关*******************************//
//***********************************************游戏相关*******************************//
//***********************************************游戏相关*******************************//
//***********************************************游戏相关*******************************//
//***********************************************游戏相关*******************************//
//***********************************************游戏相关*******************************//
//***********************************************游戏相关*******************************//
//***********************************************游戏相关*******************************//
//***********************************************游戏相关*******************************//
//***********************************************游戏相关*******************************//
//***********************************************游戏相关*******************************//
//***********************************************游戏相关*******************************//
//***********************************************游戏相关*******************************//

#define BLOCK_W 10
#define BLOCK_H 10
#define MASK 1
sbit Clock_1=P1^0;
sbit Latch_1=P1^1;
sbit Data_1=P1^2;//手柄一引脚定义
u16  BackGround[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
u8 code form[][4][4]={//[形状][方向][每一行]
	{{0,0,4 ,14},{0,8 ,12,8},{0,0, 14,4},{0,4 ,12,4}},//品
	{{0 ,0,0,15},{8 ,8 ,8,8},{0 ,0,0,15},{8 ,8 ,8,8}},//一
	{{0,8 ,12,4},{0,0,6 ,12},{0,8 ,12,4},{0,8 ,12,4}},//s
	{{0,0,12,12},{0,0,12,12},{0,0,12,12},{0,0,12,12}},//田
	{{0,0,8,14 },{0,4 ,4,12},{0,0,14 ,2},{0 ,12 ,8,8}}
	};
sbit Clock_2=P1^3;
sbit Latch_2=P1^4;
sbit Data_2=P1^5;//手柄二引脚定义
u8 x,y;//小块的坐标  区别于像素的坐标
u8 form_x,form_y; //形状的坐标
u8 number,dir;//
u8 number_next;
u8 score = 0;
u8 FCkey;
u8 cnt = 0;
char *gameover = "GAME OVER!";
void DrawBlock(u8 dia_x,u8 dia_y){ //画一个小方块，左上角为坐标起点
	u16 x = dia_x*BLOCK_W+1;
	u16 y = dia_y*BLOCK_H+4;
	LCD_DrawRectangle(x,y,x+9,y+9,BLACK);
	LCD_Fill(x+1,y+1,x+9,y+9,GREEN);

} 

void CleanBlock(u8 dia_x,u8 dia_y){//清除一个小方块

	u16 x = dia_x*BLOCK_W+1;
	u16 y = dia_y*BLOCK_H+4;
	LCD_DrawRectangle(x,y,x+9,y+9,WHITE);
	LCD_Fill(x+1,y+1,x+9,y+9,WHITE);
}

void CleanForm(u8 form_x,u8 form_y){//清理一个形状，输入的是form_x,form_y
	u8 i,j;
	for(j=0;j<4;j++){
		for(i=0;i<4;i++){
			if(form[number][dir][j] & (MASK << (3-i))){
				CleanBlock(form_x+i,form_y+j);	
			}
		}
	}	
}


void DrawForm(u8 form_num,u8 dir,u8 form_x,u8 form_y){//form_x,form_y为左上角的块坐标,//num块种类，dir方向
	u8 i,j;
	for(j=0;j<4;j++){
		for(i=0;i<4;i++){
			if(form[form_num][dir][j] & (MASK << (3-i))){
				DrawBlock(form_x+i,form_y+j);	
			}
		}
	}	


}
bit Check(void){ //冲突检测

	if(((form[number][dir][3]<<(11-form_x)) | BackGround[form_y+4]) == ((form[number][dir][3]<<(11-form_x))+BackGround[form_y+4])){
		if(((form[number][dir][2]<<(11-form_x)) | BackGround[form_y+3]) == ((form[number][dir][2]<<(11-form_x))+BackGround[form_y+3])){
			if(((form[number][dir][1]<<(11-form_x)) | BackGround[form_y+2]) == ((form[number][dir][1]<<(11-form_x))+BackGround[form_y+2]))
				return 1;																						  
			}
		}
	else 
		return 0;	


}
void ProduceRandNewForm(void){
	srand(cnt);
	number_next = rand()%5;
		 

}


void Add2Background(void){
	u8 i;
	for(i=0;i<4;i++){
		BackGround[form_y+i] += (form[number][dir][i]<<(11-form_x)); 
	   }


}
void Checkfull(void){
	u8 i,j,k;
	for(i = 20;i > 0; i--){
		if(BackGround[i] == 32764){ //1 1111 1111 1110
		score ++;
		LCD_ShowNum(135,120,score,3,20);
		//	BackGround[i] = 0;
			for(j = i;j > 0 ; j--){
				if(BackGround[j]!=0){
	
					BackGround[j] = BackGround[j-1];
		
					for(k = 0;k < 13;k++){
						if(BackGround[j]&(MASK<<(14-k)))
							DrawBlock(k,j);
						else
							CleanBlock(k,j); 
						}					
					}
				else{
				//	BackGround[j] = 0;
					break;
				 }
			}
		//	BackGround[0] = 0;	
			break;
		}
	
	}


} 
void Startup(void){//初始化
	char *next = "NEXT:";
	char *score = "SCORE:";
	LCD_ShowNum(135,95,0,3,15);
	LCD_Init();
	LCD_Fill(0,0,176,220,WHITE);
	LCD_DrawRectangle(0,0,133,219,BLACK);
	LCD_DrawRectangle(0,0,132,219,BLACK);
	LCD_ShowString(140,10,15,next,1);
	LCD_ShowString(135,100,15,score,1);
//	BackGround[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8191};
	x=0;
	y=0;
	form_x = 5;
	form_y = 0;
	dir = 1;
	number = 0;
	score = 0;
	ProduceRandNewForm();
	DrawForm(number_next,dir,14,3);	//一开始就显示一次
}
void upDateWithInput(void){	 //输入更新
	char i,wall;	          
   	u8 temp = FCkey;
		for(i = 0;i<8;i++){
			if(temp & (0x01<<i)){
				switch(i){
					case 0:
						if(dir <3)
							dir++;
						else 
							dir = 0;
						break;
					case 4: 
						//if(dir <3)
						//	dir++;
					//	else 
					//		dir = 0;
						break;
					//case 5:
					//	if(form_y<19) 
					//		form_y++;
					//	break;
					case 6:
					
						if(form_x>0) 
							form_x--;
						break;
					case 7:

					if ((number==0&&dir==0)||(number==2&&((dir==1)||(dir==3)))){ 
						wall = 10;
					}
					else if (((number==0||number==2)&&dir==0)||number==3){ 
						wall = 11;
					}
					else if (number==1&&((dir==1)||(dir==3))){
						wall = 12;
					}
					else 
						wall = 9;
					if(form_x<wall)
						form_x++;
						break;
					
				 }
			 }
		}

	  FCkey = 0;

}

void upDateWithoutInput(void){

	 if(Check()&&form_y<17){
	 	
		form_y++;
		
		
	 	}
	  else{
	    
	  	Add2Background();
		if(BackGround[3]!=0){
			LCD_Fill(30,50,100,100,WHITE);
			LCD_ShowString(32,70,18,gameover,0);
			while(1);
		
		}
		number = number_next;
		dir = 0;form_x = 5;form_y = 0; //开始新的下降
		ProduceRandNewForm();		   //生成一个新的形状
		LCD_Fill(140,30,175,80 ,WHITE);//清除next区的图形
		DrawForm(number_next,1,14,3);//显示next区的图形

		Checkfull();					//检测满行并消除

	   }
}


void Show(void){
	
	DrawForm(number,dir,form_x,form_y);
	
	if(Check()&&form_y<17){
		CleanForm(form_x,form_y);
	}
	 
	 //delay();
	 //delay();

}
int main (void){
	TMOD = 0X01;
	TH0 = (65536-20000)/256;
	TH1 = (65536-20000)%256;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
	Startup();
	while(1){
		Show();
		upDateWithoutInput();	
		upDateWithInput();
	//	BackGround[19];
	//	BackGround[20];
	//	BackGround[21];
		
	}
	return 0;
}
void T0_time() interrupt 1{
	TH0 = (65536-20000)/256;
	TH1 = (65536-20000)%256;
	FCkey = Read_Key_1();	
	cnt++;
	if(cnt==255)
		cnt=0;



}