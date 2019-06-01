#include "OSC.h"
#include "Interface.h"
#include "math.h"
#include "Config.h"
	uint16_t n=0;
	uint16_t m=0;
  uint16_t y=0;
//uint8_t FIFO[2][280]={20};
//uint8_t BUFF[2][280]={20};
extern uint16_t dacvalue,adcvalue;
struct InfoStruct Info;

void BackGround()
{
	//LCD_Fill(0,0, 240, 320, WHITE);

	//DrawPixel(220,300,RED);
	//DrawLine(0,0,240,YELLOW,Horizontal);
	//DrawLine(0,314,240,YELLOW,Horizontal);
	//黄色边框
/*
	DrawLine(0,0,0,320,YELLOW);
	DrawLine(240,0,240,320,YELLOW);
	DrawLine(0,0,240,0,YELLOW);
	DrawLine(0,314,240,314,YELLOW);*/
	//水平横轴
	LCD_Fill(0,0, 200, 280, BLACK);
	

	for(m=0;m<=200;m+=10)
		for(n=0;n<=280;n+=10){
			DrawPixel(m,n,RED);
		}
	//for(m=210;m<=210;m+=20)
		for(n=0;n<=290;n+=20){
			DrawPixel(202,n,BLACK);
		}
		


//之前存在
/*
for(m=0;m<=210;m+=20){
		//for(n=0;n<=290;n+=20){
			DrawPixel(m,282,BLACK);
		}
	
	for(n=0;n<=290;n+=20){
			DrawPixel(202,n,BLACK);
		}
*/
		
		
		
	//	reset();
		//UpdateFIFO();

	//DrawPixel(28,52,YELLOW);
	//DrawPixel(40,24,YELLOW);
		
//	DrawLine(200,0,200,314,RED);
//	DrawLine(0,280,240,280,RED);
			

/*	//for(m=0;m<=200;m+=50){
		DisplayStr(2,12,"2.97",BLACK,WHITE);
		DisplayStr(2,32,"2.64",BLACK,WHITE);
		DisplayStr(2,52,"2.31",BLACK,WHITE);
		DisplayStr(2,72,"1.98",BLACK,WHITE);
		DisplayStr(2,92,"1.65",BLACK,WHITE);
		DisplayStr(2,112,"1.32",BLACK,WHITE);
		DisplayStr(2,132,"0.99",BLACK,WHITE);
		DisplayStr(2,152,"0.66",BLACK,WHITE);
		DisplayStr(2,172,"0.33",BLACK,WHITE);
		
		DisplayStr(20,203,"0",BLACK,WHITE);
		
		DisplayStr(54,203,"1",BLACK,WHITE);
		DisplayStr(74,203,"2",BLACK,WHITE);
		DisplayStr(94,203,"3",BLACK,WHITE);
		DisplayStr(114,203,"4",BLACK,WHITE);
		DisplayStr(134,203,"5",BLACK,WHITE);
		DisplayStr(154,203,"6",BLACK,WHITE);
		DisplayStr(174,203,"7",BLACK,WHITE);
		DisplayStr(194,203,"8",BLACK,WHITE);
		DisplayStr(214,203,"9",BLACK,WHITE);
		DisplayStr(230,203,"10",BLACK,WHITE);
		DisplayStr(250,203,"11",BLACK,WHITE);
		DisplayStr(270,203,"12",BLACK,WHITE);
		DisplayStr(290,203,"13",BLACK,WHITE);
		//while(1);
		//DisplayStr(74,210,"10",BLCAK,WHITE);
		
		DisplayStr(2,32,"2.64",BLACK,WHITE);
		DisplayStr(2,52,"2.31",BLACK,WHITE);
		DisplayStr(2,72,"1.98",BLACK,WHITE);
		DisplayStr(2,92,"1.65",BLACK,WHITE);
		DisplayStr(2,112,"1.32",BLACK,WHITE);
		DisplayStr(2,132,"0.99",BLACK,WHITE);
		DisplayStr(2,152,"0.66",BLACK,WHITE);
		DisplayStr(2,172,"0.33",BLACK,WHITE);*/
	//DisplayStr(10,10,"9",RED,BLACK);
	//}
	//ShowChar(

}

void reset()
{
	for(m=0;m<=200;m+=10)
		for(n=0;n<=280;n+=10)
	  {
			DrawPixel(m,n,RED);
		}
	//for(m=210;m<=210;m+=20)

}

//void data()
//{
//	uint16_t k=0;
//	static float f=0;
//	f+=1;
//	for(k=0;k<280;k++){
//	Info.FIFO[0][k] = (uint8_t)(40*sin(f/3.14f)+70);
//	}
//}

//void Update(){

//	  uint16_t l=0;
	
//    DrawPixel(20,20,YELLOW);
//			UpdateFIFO();
//    FIFO[0][20]=(uint8_t)(ADC_GetConversionValue(ADC1)/4096.0f*200.0f);
//		DrawPixel(200-FIFO[0][l],l,YELLOW);
//	  DrawPixel(200-FIFO[1][l],l,WHITE);
//	  for(l=1;l<279;l++){
//  	DrawPixel(200-FIFO[0][l],l,YELLOW);
//    DrawPixel(200-FIFO[0][l],l,YELLOW);
//    DrawPixel(200-FIFO[1][l],l,WHITE);
//		DrawLine(200-FIFO[0][l-1],y-20,200-FIFO[0][l],y,YELLOW);
//	  DrawLine(200-FIFO[1][l-1],l-1,200-FIFO[1][l],l,WHITE);
//		l+=20;
//		if(l==280)l=1;
//		y+=40;
//		if(y>=280)y=0;	
//	}
//	DrawPixel(200-FIFO[1][l],l,YELLOW);
//	DrawPixel(200-FIFO[1][l],l,WHITE);
	//DrawLine(200-FIFO[0][l],l,200-FIFO[0][l-1],l-1,YELLOW);
	
	
//}
//void draw()
//{
//	uint16_t l=0;
//	for(l=1;l<279;l++)
//	{
//			DrawPixel(200- Info.BUFF[0][l],l,YELLOW);
//	}
////	 for(l=1;l<279;l++){
////	 DrawLine(200-BUFF[0][l-1],l-1,200-BUFF[0][l],l,YELLOW); 
////		}
//}

//void UpdateFIFO(){
//	uint16_t k=0;
//	for(k=279;k>0;k--)
//	{
//		FIFO[0][k]=(uint8_t)(adcvalue/4096.0f*200.0f);
//		//FIFO[0][k]=FIFO[0][k-1];
//		//FIFO[1][k]=FIFO[1][k-1];
//	}
//	
////	FIFO[0][0]=(uint8_t)(adcvalue/4096.0f*200.0f);//(uint8_t)(ADC_GetConversionValue(ADC1)/4096.0f*200.0f);
////	FIFO[1][0]=(uint8_t)(dacvalue/4096.0f*200.0f);//uint8_t)(40*sin(k/3.14f)+20);
//   
//	for(k=279;k>0;k--)
//	{
//		BUFF[0][k]=FIFO[0][k];
//	}
//	
//}

void SHOW(){
		static uint8_t i=0;

		LCD_Fill(0,0, 200, 280, BLACK);
		draw();
		reset();
		i++;
	if(!(i%10)){
		LCD_ShowNum(298,282,Info.amp,5,BLACK,WHITE);
		//LCD_ShowNum(298,298,Info.freq,5,BLACK,WHITE);
	}
}
//extern struct InfoStruct Info;

void draw()
{
	uint16_t l=0;
	for(l=0;l<280;l++)
	{
			DrawPixel(200-Info.BUFF[0][l],l,YELLOW);
			
	}
	for(l=0;l<128;l++)
	{
			//DrawPixel((200.0-(uint8_t)(Info.Amplitude[l])),l,WHITE);
			
	}

//	for(l=1;l<279;l++){
//		DrawLine(200-Info.BUFF[0][l-1],l-1,200-Info.BUFF[0][l],l,YELLOW); 
//		}
}	


