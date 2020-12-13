#include<reg51.h>
#include "LCD.h"
#include "sys.h"
#include "FC.h"
#include "lcd.h"
 
//LCD的画笔颜色和背景色	   
u16 POINT_COLOR=0x0000;	//画笔颜色
u16 BACK_COLOR=YELLOW;  //背景色 
//管理LCD重要参数
//默认为竖屏
_lcd_dev lcddev;

void delay_ms(int count)  // /* X1ms */
{
    u8 i=0;
    while(count--)
	  while(i)
	     i++;
}
//******************************************************************
//函数名：  LCD_Write_Bus
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    向液晶屏总线写入数据(LCD驱动内部函数)
//输入参数：VH:高8位数据
//        	VL:低8位数据
//返回值：  无
//修改记录：无
//******************************************************************
#if LCD_USE8BIT_MODEL==1 //8位并行数据写入时序 
void LCD_Write_Bus(char VH,char VL)  
{	
	LCD_CS=0;
	LCD_DataPortH=VH;	
	LCD_WR=0;
	LCD_WR=1;
	LCD_DataPortH=VL;		
	LCD_WR=0;
	LCD_WR=1;
	LCD_CS=1;
}
#else	//16位并行数据写入时序 	
void LCD_Write_Bus(char VH,char VL)   
{
	LCD_CS=0;	
	LCD_DataPortH=VH;	
	LCD_DataPortL=VL;		
	LCD_WR=0;
	LCD_WR=1; 
	LCD_CS=1;
}
#endif

//
////******************************************************************
////函数名：  LCD_WR_DATA8
////作者：    xiao冯@全动电子
////日期：    2013-02-22
////功能：    向液晶屏总线写入写8位数据
////输入参数：VH:高8位数据
////        	VL:低8位数据
////返回值：  无
////修改记录：无
////******************************************************************
//void LCD_WR_DATA8(char VH,char VL) 
//{
//	LCD_RS=1;
//	LCD_Write_Bus(VH,VL);
//} 

//******************************************************************
//函数名：  LCD_WR_REG
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    向液晶屏总线写入写16位指令
//输入参数：Reg:待写入的指令值
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_WR_REG(int Reg)	 
{	
	LCD_RS=0;
	LCD_Write_Bus(Reg>>8,Reg);
} 

//******************************************************************
//函数名：  LCD_WR_DATA
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    向液晶屏总线写入写16位数据
//输入参数：Data:待写入的数据
//返回值：  无
//修改记录：无
//******************************************************************
 void LCD_WR_DATA(int Data)
{
	LCD_RS=1;
	LCD_Write_Bus(Data>>8,Data);
}

//******************************************************************
//函数名：  LCD_WriteReg
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    写寄存器数据
//输入参数：LCD_Reg:寄存器地址
//			LCD_RegValue:要写入的数据
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue)
{
  LCD_WR_REG(LCD_Reg);
	LCD_WR_DATA(LCD_RegValue);
}

//******************************************************************
//函数名：  LCD_WriteRAM_Prepare
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    开始写GRAM
//			在给液晶屏传送RGB数据前，应该发送写GRAM指令
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_WriteRAM_Prepare(void)
{
 	LCD_WR_REG(lcddev.wramcmd);	  
} 	 

//******************************************************************
//函数名：  LCD_Reset
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    LCD复位函数，液晶初始化前要调用此函数
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_Reset(void)
{
	LCD_RESET=1;
	delay_ms(50);	
	LCD_RESET=0;
	delay_ms(50);
	LCD_RESET=1;
	delay_ms(50);
}
//******************************************************************
//函数名：  LCD_DrawPoint 
//功能：    在指定位置写入一个像素点数据
//输入参数：(x,y):光标坐标
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_DrawPoint(u16 x,u16 y,u16 color)
{
	LCD_SetWindows(x,y,x,y);//设置光标位置 
	LCD_WR_DATA(color); 	    
}
//******************************************************************
//函数名：  LCD_DrawLine 
//功能：    GUI画线
//输入参数：x1,y1:起点坐标
//        	x2,y2:终点坐标 
//返回值：  无
//修改记录：无
//****************************************************************** 
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		LCD_DrawPoint(uRow,uCol,color);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}
//******************************************************************
//函数名：  LCD_DrawRectangle
//功能：    GUI画矩形(非填充)
//输入参数：(x1,y1),(x2,y2):矩形的对角坐标
//返回值：  无
//修改记录：无
//******************************************************************  
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
	LCD_DrawLine(x1,y1,x2,y1,color);
	LCD_DrawLine(x1,y1,x1,y2,color);
	LCD_DrawLine(x1,y2,x2,y2,color);
	LCD_DrawLine(x2,y1,x2,y2,color);
}

void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{  	
	u16 i,j;			
	u16 width=ex-sx+1; 		//得到填充的宽度
	u16 height=ey-sy+1;		//高度
	LCD_SetWindows(sx,sy,ex-1,ey-1);//设置显示窗口
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		LCD_WR_DATA(color);	//写入数据 	 
	}
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//恢复窗口设置为全屏
}

//******************************************************************
//函数名：  LCD_ShowChar
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    显示单个英文字符
//输入参数：(x,y):字符显示位置起始坐标
//        	fc:前置画笔颜色
//			bc:背景颜色
//			num:数值（0-94）
//			size:字体大小
//			mode:模式  0,填充模式;1,叠加模式
//返回值：  无
//修改记录：无
//******************************************************************  
void LCD_ShowChar(u16 x,u16 y,u16 fc, u16 bc, u8 num,u8 size,u8 mode)
{  
    u8 temp;
    u8 pos,t;
	u16 colortemp=POINT_COLOR;      
		   
	num=num-' ';//得到偏移后的值
	LCD_SetWindows(x,y,x+size/2-1,y+size-1);//设置单个文字显示窗口
	if(!mode) //填充模式
	{
		
		for(pos=0;pos<size;pos++)
		{
			if(size==12)temp=asc2_1206[num][pos];//调用1206字体
			else temp=asc2_1608[num][pos];		 //调用1608字体
			for(t=0;t<size/2;t++)
		    {                 
		        if(temp&0x01)LCD_WR_DATA(fc); 
				else LCD_WR_DATA(bc); 
				temp>>=1;				
		    }			
		}	
	}else//叠加方式
	{
		for(pos=0;pos<size;pos++)
		{
			if(size==12)temp=asc2_1206[num][pos];//调用1206字体
			else temp=asc2_1608[num][pos];		 //调用1608字体
			for(t=0;t<size/2;t++)
		    {   
				POINT_COLOR=fc;              
		        if(temp&0x01)LCD_DrawPoint(x+t,y+pos,fc);//画一个点    
		        temp>>=1; 
		    }
		}
	}
	POINT_COLOR=colortemp;	
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//恢复窗口为全屏    	   	 	  
} 
//******************************************************************
//函数名：  LCD_ShowString
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    显示英文字符串
//输入参数：x,y :起点坐标	 
//			size:字体大小
//			*p:字符串起始地址
//			mode:模式	0,填充模式;1,叠加模式
//返回值：  无
//修改记录：无
//******************************************************************  	  
void LCD_ShowString(u16 x,u16 y,u8 size,u8 *p,u8 mode)
{         
    while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
    {   
		if(x>(lcddev.width-1)||y>(lcddev.height-1)) 
		return;     
        LCD_ShowChar(x,y,POINT_COLOR,BACK_COLOR,*p,size,mode);
        x+=size/2;
        p++;
    }  
}
//******************************************************************
//函数名：  LCD_ShowNum	 
//功能：    显示单个数字变量值
//输入参数：x,y :起点坐标	 
//			len :指定显示数字的位数
//			size:字体大小(12,16)
//			color:颜色
//			num:数值(0~4294967295)
//返回值：  无
//修改记录：无
//******************************************************************
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}  			 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,POINT_COLOR,BACK_COLOR,' ',size,1);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,POINT_COLOR,BACK_COLOR,temp+'0',size,1); 
	}
} 

//功能：    显示一副16位BMP图像
//输入参数：x,y :起点坐标
// 			*p :图像数组起始地址
//返回值：  无
//修改记录：无
//******************************************************************  
void Drawbmp16(u16 x,u16 y,const unsigned char *p) //显示40*40 QQ图片
{
  	int i; 
	unsigned char picH,picL; 
	LCD_SetWindows(x,y,x+40-1,y+40-1);//窗口设置
    for(i=0;i<40*40;i++)
	{	
	 	picL=*(p+i*2);	//数据低位在前
		picH=*(p+i*2+1);				
		LCD_WR_DATA(picH<<8|picL);  						
	}	
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//恢复显示窗口为全屏
}
//******************************************************************
//函数名：  LCD_Init
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    LCD初始化
//输入参数：无
//返回值：  无
//修改记录：无
//******************************************************************
void LCD_Init(void)
{
	LCD_Reset(); //初始化之前复位
	LCD_RD=1;	 //RD引脚没有用到，拉高处理

	//=========================液晶屏初始化=============================//
	LCD_WriteReg(0X14,0X0030); 
	LCD_WriteReg(0X0F,0X0008); 
	LCD_WriteReg(0X11,0X0231); 
	LCD_WriteReg(0X12,0X0009); 
	LCD_WriteReg(0X13,0X2958); 
	LCD_WriteReg(0X10,0X5268);
	delay_ms(40);
	LCD_WriteReg(0X12,0X0019);
	delay_ms(40);
	LCD_WriteReg(0X10,0X3260); 
	LCD_WriteReg(0X13,0X1958); 
	delay_ms(40);
	//Gamma Setting
	LCD_WriteReg(0X30,0X0000);
	LCD_WriteReg(0X31,0X0501);
	LCD_WriteReg(0X32,0X0207);
	LCD_WriteReg(0X33,0X0502);
	LCD_WriteReg(0X34,0X0007);
	LCD_WriteReg(0X35,0X0601);
	LCD_WriteReg(0X36,0X0707);
	LCD_WriteReg(0X37,0X0305);
	LCD_WriteReg(0X38,0X040e);
	LCD_WriteReg(0X39,0X040e);
	LCD_WriteReg(0X3a,0X0101);
	LCD_WriteReg(0X3b,0X0101);
	LCD_WriteReg(0X3c,0X0101);
	LCD_WriteReg(0X3d,0X0101);
	LCD_WriteReg(0X3e,0X0001);
	LCD_WriteReg(0X3f,0X0001);
	
	LCD_WriteReg(0X21,0x0000);
	
	//Display Mode
	LCD_WriteReg(0X01,0X011B);//0x011b
	LCD_WriteReg(0X02,0X0700);
	LCD_WriteReg(0X03,0X1030);//1030 
	LCD_WriteReg(0X08,0X1010);
	LCD_WriteReg(0X0A,0X4420);
	LCD_WriteReg(0X0B,0X5030);
	LCD_WriteReg(0X0F,0X000D);
	delay_ms(10);
	//Display ON sequence
	LCD_WriteReg(0X07,0X0005);
	LCD_WriteReg(0X07,0X0025);
	LCD_WriteReg(0X07,0X0027);
	LCD_WriteReg(0X07,0X0037);
	//设置LCD属性参数
	LCD_SetParam();//设置LCD参数	 
	LCD_BL=1;//点亮背光	 
}
/*************************************************
函数名：LCD_SetWindows
功能：设置lcd显示窗口，在此区域写点数据自动换行
入口参数：xy起点和终点
返回值：无
*************************************************/
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
{	
	LCD_WR_REG(lcddev.setxcmd);
	LCD_WR_DATA((xEnd<<8)+xStar);
	
	LCD_WR_REG(lcddev.setycmd);
	LCD_WR_DATA((yEnd<<8)+yStar);
	
	LCD_WR_REG(0x0021);
#if USE_HORIZONTAL==1	//使用横屏
	LCD_WR_DATA((xStar<<8)+yStar);
#else
	LCD_WR_DATA((yStar<<8)+xStar);
#endif 	

	LCD_WriteRAM_Prepare();	//开始写入GRAM				
}   
//
///*************************************************
//函数名：LCD_SetCursor
//功能：设置光标位置
//入口参数：xy坐标
//返回值：无
//*************************************************/
//void LCD_SetCursor(u16 Xpos, u16 Ypos)
//{
//	LCD_WR_REG(lcddev.setxcmd);
//	LCD_WR_DATA((175<<8)+Xpos);
//	
//	LCD_WR_REG(lcddev.setycmd);
//	LCD_WR_DATA((219<<8)+Ypos);
//	
//	LCD_WR_REG(0x0021);
//#if USE_HORIZONTAL==1	//使用横屏
//	LCD_WR_DATA((Xpos<<8)+Ypos);
//#else
//	LCD_WR_DATA((Ypos<<8)+Xpos);
//#endif 
//	
//	LCD_WriteRAM_Prepare();	//开始写入GRAM 
//
//} 

//设置LCD参数
//方便进行横竖屏模式切换
void LCD_SetParam(void)
{ 	
	lcddev.wramcmd=0x0022;
#if USE_HORIZONTAL==1	//使用横屏	  
	lcddev.dir=1;//横屏
	lcddev.width=220;
	lcddev.height=176;
	lcddev.setxcmd=0x0045;
	lcddev.setycmd=0x0044;			
	LCD_WriteReg(0X03,0X1038);//0x011b
	LCD_WriteReg(0X01,0X031B);//0x011b
#else//竖屏
	lcddev.dir=0;//竖屏				 	 		
	lcddev.width=176;
	lcddev.height=220;
	lcddev.setxcmd=0x0044;
	lcddev.setycmd=0x0045;	
	LCD_WriteReg(0X03,0X1030);//0x011b
	LCD_WriteReg(0X01,0X011B);//0x011b
#endif
}








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
u16 code BackGround[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8191};
u8 code form[][4][4]={//[形状][方向][每一行]
	{{0,0,4 ,14},{0,8 ,12,8},{0,0, 14,4},{0,4 ,12,4}},//品
	{{0 ,0,0,15},{8 ,8 ,8,8},{0 ,0,0,15},{8 ,8 ,8,8}},//一
	{{0,8 ,12,4},{0,0,6 ,12},{0,8 ,12,4},{0,8 ,12,4}},//
	{{0,0,12,12},{0,0,12,12},{0,0,12,12},{0,0,12,12}},//田
	{{0,0,15,8 },{12,4 ,4,4},{0,0,1 ,15},{8 ,8 ,8,12}}
	};
sbit Clock_2=P1^3;
sbit Latch_2=P1^4;
sbit Data_2=P1^5;//手柄二引脚定义
u8 x;
u8 y;//小块的坐标  区别于像素的坐标
u8 form_x,form_y; //形状的坐标
u8 number,dir;//

void DrawBlock(u8 dia_x,u8 dia_y){ //画一个小方块，左上角为坐标起点
	u16 x = dia_x*BLOCK_W+1;
	u16 y = dia_y*BLOCK_H+1;
	LCD_DrawRectangle(x,y,x+10,y+10,BLACK);
	LCD_Fill(x+1,y+1,x+10,y+10,GREEN);

} 

void CleanBlock(u8 dia_x,u8 dia_y){//清除一个小方块

	u16 x = dia_x*BLOCK_W+1;
	u16 y = dia_y*BLOCK_H+1;
	LCD_DrawRectangle(x,y,x+10,y+10,WHITE);
	LCD_Fill(x+1,y+1,x+10,y+10,WHITE);
}

void CleanForm(u8 form_x,u8 form_y){//清理一个形状，输入的是form_x,form_y
	u16 x = form_x*BLOCK_W+1;
	u16 y = form_y*BLOCK_H+1;
	LCD_Fill(x,y,x+41,y+41,WHITE);
}

void delay(){

	u16 delay = 5000;
	while(delay--);
//	delay = 5000;
//	while(delay--);

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

	if(((form[number][dir][3]<<(13-form_x)) | BackGround[form_y+4]) == ((form[number][dir][3]<<(13-form_x))+BackGround[form_y+4]))
		return 1;
	else 
		return 0;	


}
void Startup(void){//初始化
	LCD_Init();
	LCD_Fill(0,0,176,220,WHITE);
	LCD_DrawRectangle(0,0,133,219,BLACK);
	LCD_DrawRectangle(0,0,132,219,BLACK);
//	BackGround[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8191};
	x=0;
	y=0;
	form_x = 5;
	form_y = 0;
	dir = 0;
	number = 0;
}


void upDateWithInput(void){	 //输入更新
	char i;	          
   	u8 temp = Read_Key_1();
		for(i = 0;i<8;i++){
			if(temp & (0x01<<i)){
				switch(i){
					case 4: 
						if(dir <3)
							dir++;
						else 
							dir = 0;
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
						if(form_x<9)
							form_x++;
						break;
				 }
			 }
		}



}
void upDateWithoutInput(void){

	 if(Check()){
	 	form_y++;
		CleanForm(form_x,form_y-1);
	 	}
	 



}


void Show(void){

	 DrawForm(number,dir,form_x,form_y);
	 delay();
	 delay();
	 //CleanForm(form_x,form_y);

}
int main (void){
	Startup();
	while(1){
		upDateWithInput();

		upDateWithoutInput();

		Show();			 
		

	
	
	
	}
	return 0;
}