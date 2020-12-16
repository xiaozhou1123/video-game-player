#include <reg51.h>
#include "LCD.h"
#include "sys.h"
#include "FC.h"
#include "lcd.h"
#include "LCDfunction.h"
#define W 16
#define H 26;
u8 FCkey_p;

struct location{
	u8 x;
	u8 y;


};
struct location plane;
struct location bullet;
void DrawPlane(u8 plane_x,u8 plane_y){
	u16 x = plane_x*10+1;
	u16 y = plane_y*10+4;
	LCD_DrawRectangle(x,y-10,x+9,y+1,BLACK);
	LCD_DrawRectangle(x,y,x+9,y+9,BLACK);
	LCD_DrawRectangle(x-10,y,x+19,y+9,BLACK);
	LCD_DrawRectangle(x-20,y+10,x+29,y+19,BLACK);
	LCD_DrawRectangle(x-10,y+20,x-1,y+29,BLACK);
	LCD_DrawRectangle(x+10,y+20,x+19,y+29,BLACK);
	LCD_Fill(x-10,y,x+18,y+9,RED);
	LCD_Fill(x,y-10,x+8,y+1,RED);
	LCD_Fill(x-20,y+10,x+29,y+19,RED);
}
void CleanPlane(void){
	u16 x = (plane.x) *10+1;
	u16 y = (plane.y) *10+4;
	LCD_Fill(x,y-10,x+10,y,WHITE);
	LCD_Fill(x,y,x+10,y+10,WHITE);
	LCD_Fill(x-10,y,x+20,y+10,WHITE);
	LCD_Fill(x-20,y+10,x+30,y+20,WHITE);
	LCD_Fill(x-10,y+20,x,y+30,WHITE);
	LCD_Fill(x+10,y+20,x+20,y+30,WHITE);
}
void DrawBullet(u8 bullet_x,u8 bullet_y){
	u16 x = bullet_x*10+1;
	u16 y = bullet_y*10+4;
	LCD_DrawRectangle(x-2,y,x+2,y+10,BLACK);	
	


}

void Starup(void){

	LCD_Init();
	LCD_Fill(0,0,176,220,WHITE);
	plane.x=5;
	plane.y=5;
	bullet.x=-1;
	bullet.y=-1;
	
}
void upDatawithInput(void){
	u8 i;	          
   	u8 temp = FCkey_p;
		for(i = 0;i<8;i++){
			if(temp & (0x01<<i)){
				switch(i){
				case 6:
					if(plane.x>2)
						plane.x--;
					break;
				case 7:
					if(plane.x<W-2)		
						plane.x++;
					break;
				case 4:
					plane.y--;break;
				case 5:
					plane.y++;break;
				case 0:
					bullet.x = plane.x;
					bullet.y = plane.y;

				}
			}
		}


}
void planeMain(void){
	Starup();
	while(1){
		upDatawithInput();
		DrawBullet(10,10);
		DrawPlane(plane.x,plane.y);
		if(FCkey_p)
		CleanPlane();
		DrawBullet(bullet.x,bullet.y);
	
	
	}


}