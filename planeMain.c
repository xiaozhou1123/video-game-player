#include <reg51.h>
#include "LCD.h"
#include "sys.h"
#include "FC.h"
#include "lcd.h"
#include "LCDfunction.h"
#define W 16
#define H 26;
u8 FCkey_p1;
u8 FCkey_p2;
struct location{
	u8 x;
	u8 y;


};
struct location plane_A;
struct location bullet_A;
struct location plane_B;
struct location bullet_B;


// 画飞机A
void Drawplane_A(u16 X, u16 Y, color) {
	u16 X0 = X * 10;
	u16 Y0 = Y * 10;
	// 特征尺寸
	const unsigned char d1 = 3;
	const unsigned char d2 = 4;
	const unsigned char d3 = 3;
	const unsigned char d4 = 4;
	const unsigned char d5 = 4;
	// 开始画线
	LCD_DrawLine(X0, Y0, X0-d1, Y0+d1, color); // 1
	LCD_DrawLine(X0, Y0, X0+d1, Y0+d1, color); // 1
	LCD_DrawLine(X0-d1, Y0+d1, X0-d1, Y0+d1+d2+d3+d3+d4+d5, color); // 2
	LCD_DrawLine(X0+d1, Y0+d1, X0+d1, Y0+d1+d2+d3+d3+d4+d5, color); // 2
	LCD_DrawLine(X0-d1, Y0+d1+d4, X0-d1-d2, Y0+d1+d2+d4, color); // 3
	LCD_DrawLine(X0+d1, Y0+d1+d4, X0+d1+d2, Y0+d1+d2+d4, color); // 3
	LCD_DrawLine(X0-d1-d2, Y0+d1+d4+d2, X0-d1-d2, Y0+d1+d4+d2+d5+d3+d3, color); // 4
	LCD_DrawLine(X0+d1+d2, Y0+d1+d4+d2, X0+d1+d2, Y0+d1+d4+d2+d5+d3+d3, color); // 4
	LCD_DrawLine(X0-d1, Y0+d1+d4+d2+d5+d3+d3, X0-d1-d2, Y0+d1+d4+d2+d5+d3, color); // 5
	LCD_DrawLine(X0+d1, Y0+d1+d4+d2+d5+d3+d3, X0+d1+d2, Y0+d1+d4+d2+d5+d3, color); // 5
	LCD_DrawLine(X0-d1-d2, Y0+d1+d4+d2+d5+d3, X0-d1-d2-d3, Y0+d1+d4+d2+d5+d3+d3, color); // 6
	LCD_DrawLine(X0+d1+d2, Y0+d1+d4+d2+d5+d3, X0+d1+d2+d3, Y0+d1+d4+d2+d5+d3+d3, color); // 6
	LCD_DrawLine(X0-d1-d2, Y0+d1+d4+d2+d5, X0-d1-d2-d3-d3, Y0+d1+d4+d2+d5+d3+d3, color); // 7
	LCD_DrawLine(X0+d1+d2, Y0+d1+d4+d2+d5, X0+d1+d2+d3+d3, Y0+d1+d4+d2+d5+d3+d3, color); // 7
	LCD_DrawLine(X0-d1-d2-d3, Y0+d1+d4+d2+d5+d3+d3, X0-d1-d2-d3-d3, Y0+d1+d4+d2+d5+d3+d3, color); // 8
	LCD_DrawLine(X0+d1+d2+d3, Y0+d1+d4+d2+d5+d3+d3, X0+d1+d2+d3+d3, Y0+d1+d4+d2+d5+d3+d3, color); // 8
	LCD_DrawLine(X0, Y0+d1+d4+d2+d5+d3+d3, X0-d1, Y0+d1+d4+d2+d5+d3, color); // 9
	LCD_DrawLine(X0, Y0+d1+d4+d2+d5+d3+d3, X0+d1, Y0+d1+d4+d2+d5+d3, color); // 9
	LCD_DrawLine(X0, Y0+d1+d4+d2, X0-d1, Y0+d1+d4+d2+d5, color); // 10
	LCD_DrawLine(X0, Y0+d1+d4+d2, X0+d1, Y0+d1+d4+d2+d5, color); // 10
}
// 画飞机 B
void Drawplane_B(u16 X, u16 Y, color) {
	u16 X0 = X * 10;
	u16 Y0 = Y * 10;
	// 特征尺寸
	const unsigned char d1 = 3;
	const unsigned char d2 = 4;
	const unsigned char d3 = 3;
	const unsigned char d4 = 4;
	const unsigned char d5 = 4;
	// 开始画线
	LCD_DrawLine(X0, Y0, X0+d1, Y0-d1, color); // 1
	LCD_DrawLine(X0, Y0, X0-d1, Y0-d1, color); // 1
	LCD_DrawLine(X0+d1, Y0-d1, X0+d1, Y0-d1-d2-d3-d3-d4-d5, color); // 2
	LCD_DrawLine(X0-d1, Y0-d1, X0-d1, Y0-d1-d2-d3-d3-d4-d5, color); // 2
	LCD_DrawLine(X0+d1, Y0-d1-d4, X0+d1+d2, Y0-d1-d2-d4, color); // 3
	LCD_DrawLine(X0-d1, Y0-d1-d4, X0-d1-d2, Y0-d1-d2-d4, color); // 3
	LCD_DrawLine(X0+d1+d2, Y0-d1-d4-d2, X0+d1+d2, Y0-d1-d4-d2-d5-d3-d3, color); // 4
	LCD_DrawLine(X0-d1-d2, Y0-d1-d4-d2, X0-d1-d2, Y0-d1-d4-d2-d5-d3-d3, color); // 4
	LCD_DrawLine(X0+d1, Y0-d1-d4-d2-d5-d3-d3, X0+d1+d2, Y0-d1-d4-d2-d5-d3, color); // 5
	LCD_DrawLine(X0-d1, Y0-d1-d4-d2-d5-d3-d3, X0-d1-d2, Y0-d1-d4-d2-d5-d3, color); // 5
	LCD_DrawLine(X0+d1+d2, Y0-d1-d4-d2-d5-d3, X0+d1+d2+d3, Y0-d1-d4-d2-d5-d3-d3, color); // 6
	LCD_DrawLine(X0-d1-d2, Y0-d1-d4-d2-d5-d3, X0-d1-d2-d3, Y0-d1-d4-d2-d5-d3-d3, color); // 6
	LCD_DrawLine(X0+d1+d2, Y0-d1-d4-d2-d5, X0+d1+d2+d3+d3, Y0-d1-d4-d2-d5-d3-d3, color); // 7
	LCD_DrawLine(X0-d1-d2, Y0-d1-d4-d2-d5, X0-d1-d2-d3-d3, Y0-d1-d4-d2-d5-d3-d3, color); // 7
	LCD_DrawLine(X0+d1+d2+d3, Y0-d1-d4-d2-d5-d3-d3, X0+d1+d2+d3+d3, Y0-d1-d4-d2-d5-d3-d3, color); // 8
	LCD_DrawLine(X0-d1-d2-d3, Y0-d1-d4-d2-d5-d3-d3, X0-d1-d2-d3-d3, Y0-d1-d4-d2-d5-d3-d3, color); // 8
	LCD_DrawLine(X0, Y0-d1-d4-d2-d5-d3-d3, X0+d1, Y0-d1-d4-d2-d5-d3, color); // 9
	LCD_DrawLine(X0, Y0-d1-d4-d2-d5-d3-d3, X0-d1, Y0-d1-d4-d2-d5-d3, color); // 9
	LCD_DrawLine(X0, Y0-d1-d4-d2, X0+d1, Y0-d1-d4-d2-d5, color); // 10
	LCD_DrawLine(X0, Y0-d1-d4-d2, X0-d1, Y0-d1-d4-d2-d5, color); // 10
}
void Cleanplane_A(void){
	Drawplane_A(plane_A.x,plane_A.y,WHITE);

}
void Cleanplane_B(void){
	Drawplane_B(plane_B.x,plane_B.y,WHITE);

}
void DrawBullet_A(u8 bullet_x,u8 bullet_y){
	u16 x = bullet_x*10;
	u16 y = bullet_y*10;
	LCD_DrawRectangle(x-1,y,x+1,y-10,BLACK);	
	


}
void DrawBullet_B(u8 bullet_x,u8 bullet_y){
	u16 x = bullet_x*10;
	u16 y = bullet_y*10;
	LCD_DrawRectangle(x-1,y,x+1,y-10,BLACK);	
	


}
void CleanBullet_A(){
	u16 x = bullet_A.x*10;
	u16 y = bullet_A.y*10;
	LCD_DrawRectangle(x-1,y,x+1,y-10,WHITE);	

}
void CleanBullet_B(){
	u16 x = bullet_B.x*10;
	u16 y = bullet_B.y*10;
	LCD_DrawRectangle(x-1,y,x+1,y-10,WHITE);	

}
void Starup(void){

	LCD_Init();
	LCD_Fill(0,0,176,220,WHITE);
	plane_A.x=5;
	plane_A.y=17;
	plane_B.x=5;
	plane_B.y=5;
	bullet_A.x=0;
	bullet_A.y=0;
	bullet_B.x=0;
	bullet_B.y=0;
}
int check_(){
	if((bullet_B.x==plane_A.x)&&(bullet_B.y==plane_A.y))
		return 1;
	if((bullet_A.x==plane_B.x)&&(bullet_A.y==plane_B.y))
		return 2;
	else
		return 3;	


}
void upDatawithoutInput(void){
	char A[]="A win";
	char B[]="B win";
	u8 s = check_();
	if(s==3){
		if(bullet_B.y<19)
			bullet_B.y++;
		if(bullet_A.y>0)
			bullet_A.y--;
		}
		else{
				if(s==1){	
				LCD_Fill(30,50,100,100,WHITE);
				LCD_ShowString(32,70,18,B,0);
				}
				if(s==2){	
				LCD_Fill(30,50,100,100,WHITE);
				LCD_ShowString(32,70,18,A,0);
				}
				while(1);
			}
	  
}
void upDatawithInput(void){
	u8 i;	          
   	u8 temp_1 = FCkey_p1;
	u8 temp_2 = FCkey_p2;
	if(temp_2 & (0x01<<0)){
	    bullet_B.x = plane_B.x;
    	bullet_B.y = plane_B.y;
	}
	if(temp_1 & (0x01<<0)){
	    bullet_A.x = plane_A.x;
    	bullet_A.y = plane_A.y;
	}
		for(i = 6;i<8;i++){
		
			if(temp_1 & (0x01<<i)){
				switch(i){
				case 6:
				//	if(plane_A.x>2)
						Cleanplane_A();
						plane_A.x--;
						
					break;
				case 7:
				//	if(plane_A.x<W-2)
						Cleanplane_A();		
						plane_A.x++;
						
					break;
				

				}
			}
		}
		for(i = 6;i<8;i++){
			if(temp_2 & (0x01<<i)){
				switch(i){
				case 6:
				//	if(plane_A.x>2)
						Cleanplane_B();
						plane_B.x--;
						
					break;
				case 7:
				//	if(plane_A.x<W-2)
						Cleanplane_B();		
						plane_B.x++;
						
					break;
				

				}
			}
		}


}
void Show_p(){
	Drawplane_A(plane_A.x,plane_A.y,BLACK);
	Drawplane_B(plane_B.x,plane_B.y,BLACK);	
	if(bullet_A.y>0)
		DrawBullet_A(bullet_A.x,bullet_A.y);
	CleanBullet_A();
	if(bullet_B.y<19)
		DrawBullet_B(bullet_B.x,bullet_B.y);
	CleanBullet_B();


}
void planeMain(void){
	Starup();
	while(1){
		upDatawithInput();
		Show_p();
		upDatawithoutInput();
		
	
	}


}