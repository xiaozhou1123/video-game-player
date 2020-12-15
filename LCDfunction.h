#ifndef _LCDfunction_H_
#define _LCDfunction_H_
void delay_ms(int count);


void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue);
void LCD_Reset(void);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);
void LCD_ShowChar(u16 x,u16 y,u16 fc, u16 bc, u8 num,u8 size,u8 mode);
void LCD_ShowString(u16 x,u16 y,u8 size,u8 *p,u8 mode);
u32 mypow(u8 m,u8 n);
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);
void Drawbmp16(u16 x,u16 y,const unsigned char *p);
void LCD_Init(void);
#endif