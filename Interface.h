#include "WB_LCD.h"
#define DrawPoint(x,y) LCD_DrawPoint(x,y)
#define DrawPixel(x,y,color) LCD_DrawPixel(x,y,color)
#define ShowNum(x,y,num,size,color1,color2) 	LCD_ShowNum(x,y,num,size,color1,color2)
#define ShowChar(x,y,Char,size,color1,color2) LCD_ShowChar(u8 x, u16 y, u8 num, u8 size, u16 PenColor, u16 BackColor)
#define DrawLine(x1,y1,x2,y2,color) LCD_DrawLine(x1,y1,x2,y2,color)
#define DisplayStr(x,y,str,color1,color2) LCD_DisplayStr(x,y,str,color1,color2)
#define ShowCharString(x,y,p,color1,color2) LCD_ShowCharString(x,y,p,color1,color2)

//#define DrawHVLine(x,y,len,color,dir) LCD_DrawHVLine(x,y,len,color,dir)

