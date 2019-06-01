/*******************************************************************************
  * Company: Wang Electronic Technology Co., Ltd.
  ******************************************************************************
  * 文件名称：main.c
  * 功能说明：红牛板-ADC-模数转换实验
  * 版    本：V1.0
  * 作    者：openmcu666	
  * 日    期: 2016-05-04
********************************************************************************
  * 文件名称：
  * 功能说明：
  * 版    本：
  * 更新作者:	
  * 日    期：
  * 更新原因：
********************************************************************************/
#include "Gpio.h"
#include "delay.h"
#include "USART.h"
#include "ADC.h"
#include "DAC.h"
#include "SDS.h"
#include "fsmc_sram.h"
#include "Timer.h"
#include "stm32_dsp.h"
#include "math.h"
#include "ForSin50Hz_1KHz.h"
#include "ForNonSin50Hz_200Hz.h"
#include "Config.h"
#include "WB_LCD.h"
#include "HZ.h"
#include "AD9834.h" 
#include "FFT.h"
#include "wavetype.h"
//#include "..\Libraries\STM32F10x_DSP_Lib\stm32_dsp.h"
/*****************************************************************************
**   Main Function  main()
******************************************************************************/
extern float SDS[4];

//extern const unsigned char gImage_hebut[153600];

struct SinStruct Sin;
struct NonSinStruct NonSin;
extern struct InfoStruct Info;

uint16_t adcvalue,dacvalue;

void LOOP(void);
//void cr4_Info.length_1024_stm32(void *pssOUT, void *pssIN, uint16_t Nbin);
//void hebut()
//{
//	//LCD_DrawPicture(0,0,240,320,(u8*)gImage_hebut);
//	LCD_Fill(0,0, 70, 20, WHITE);
//	LCD_Fill(70,0, 80, 15, WHITE);

//}

	int8_t time=1;
	uint16_t k=0;
#include "Interface.h"
#include "OSC.h"
uint8_t Flag_show=0;


void data()
{
	uint16_t k=0;
	static float f=0;
	f+=1;
	for(k=0;k<280;k++){
	Info.FIFO[0][k] = (uint8_t)(40*sin(f/3.14f)+70);
	}
}
u32 fhz = 9920;

int main(void)
{  
  RCC_Config();                                             //系统频率在56MHz
	LED_Init();
	Info.SampleFreq=InitSampleFreq;
	USART1_Init();
	USART2_Init();
	Key_Init();
	FSMC_SRAM_Init(); 
	Delay_Init();                                             //systick初始化
	Init_AD9834();
	LCD_Init();
	ADC1_Init();
	DAC1_Init();
	Info.length=1024;
//	//Only Sine  AD9834_Select_Wave(0x2008); 0.2v示波器
//	//Sine+Sq    AD9834_Select_Wave(0x2028);   sq 1v示波器 无偏置
//	//Only Try   AD9834_Select_Wave(0x2002);   tr 0.2v示波器    
//	
	AD9834_Select_Wave(0x2028);
	AD9834_Set_Freq(FREQ_0,fhz);
	AD9834_Select_Wave(0x2008);

		LCD_Fill(0,281, 240, 320, WHITE);
		DisplayStr(2,282,"Amp",BLACK,WHITE);
		DisplayStr(2,298,"Freq",BLACK,WHITE);
		DisplayStr(100,282,"Type",BLACK,WHITE);
		DisplayStr(100,298,"RATE",BLACK,WHITE);
	
	//Info.SampleFreq=600000;
	
	Info.length=1024;
	//TIM_Cmd(TIM3, DISABLE);  //??TIM3					 
	for(;;){

		if(Info.freqOk==0){
			searchFreq();
		}else if(Info.freqOk==1){
			//Info.SampleFreq=20*Info.freq;
			//SetTimer(Info.SampleFreq);

			Wavetypefft();

			if(Info.waveOk)Info.freqOk=2;
			//Info.dsp=0;
		}
		if(Info.freqOk==2){
			//Wavetypefft();
			Info.SampleFreq=20*Info.freq;
			SetTimer(Info.SampleFreq);
			if(Info.freqOk==2)Info.freqOk=3;
		}

		if(Info.dsp){
			for(k=0;k<280;k++)Info.BUFF[0][k]=(uint8_t)(Info.RawData[1][k]/4096.0f*200.0f);
			GetAmp();
			SHOW();
			LCD_ShowNum(298,282,Info.amp,5,BLACK,WHITE);
			Info.dsp=0;	

		}


	}
}
void LOOP(){
	searchFreq();
	Wavetypefft();
	while(Info.freqOk);
}

/*******************FOR IIR**************/
#define NZEROS 10
#define NPOLES 10
#define GAIN   2.002186074e+03
static float xv[NZEROS+1], yv[NPOLES+1];

uint16_t IIR(uint16_t value){
				xv[0] = xv[1]; 
				xv[1] = xv[2];
				xv[2] = xv[3]; 
				xv[3] = xv[4]; 
				xv[4] = xv[5]; 
				xv[5] = xv[6]; 
				xv[6] = xv[7]; 
				xv[7] = xv[8]; 
				xv[8] = xv[9]; 
				xv[9] = xv[10]; 
        xv[10] = (float)(value) / GAIN;
        yv[0] = yv[1]; yv[1] = yv[2]; yv[2] = yv[3]; yv[3] = yv[4]; yv[4] = yv[5]; yv[5] = yv[6]; yv[6] = yv[7]; yv[7] = yv[8]; yv[8] = yv[9]; yv[9] = yv[10]; 
        yv[10] =   (xv[0] + xv[10]) + 10 * (xv[1] + xv[9]) + 45 * (xv[2] + xv[8])
                     + 120 * (xv[3] + xv[7]) + 210 * (xv[4] + xv[6]) + 252 * xv[5]
                     +( -0.0001487645 * yv[0]) + (  0.0026689124 * yv[1])
                     +( -0.0224985093 * yv[2]) + (  0.1157186252 * yv[3])
                     +( -0.4144462688 * yv[4]) + (  1.0545446211 * yv[5])
                     +( -2.0387206371 * yv[6]) + (  2.8185224265 * yv[7])
                     +( -3.0194828634 * yv[8]) + (  1.9924014816 * yv[9]);
        return (uint16_t)yv[10];
}

uint16_t cnt=0;
#include "math.h"

void SignalGen(){
	static uint16_t i=0;
	if(i>4094)i=0;
	i+=1;
	DAC_SetChannel2Data(DAC_Align_12b_R,2000*sin(i/200.0f/3.14f)+2050);
}
extern vu16 ADCValue;                                           //全局变量,用于转换后的AD值

//void TIM3_IRQHandler(void)   //TIM3??//1KHz Sample
//{
//	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //??TIM3???????
//	{
//		adcvalue=ADCValue;
//		if(!Info.dsp){
//			Info.RawData[0][Info.flagfft]=adcvalue<<16;
//			Info.RawData[1][Info.flagfft]=adcvalue;
//			Info.flagfft++;
//		}
//		if(Info.flagfft==Info.length){
//			Info.dsp=1;
//			Info.flagfft=0;
//		}
//		if(!Flag_show){
//			Info.BUFF[0][Info.flag280]=(uint8_t)(adcvalue/4096.0f*200.0f);
//			Info.flag280++;
//		}
//		if(Info.flag280==280){
//			Info.flag280=0;
//			Flag_show=1;
//		}
//		
//		LED_GPIO_PORT->ODR ^= LED1_GPIO_PIN;//turn PF6
//		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //??TIM3??????
//	}
//} 
void TIM1_UP_IRQHandler(void)   //TIM3??//1KHz Sample
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)  //??TIM3???????
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  //??TIM3??????
		if(!Info.dsp)Info.RawData[1][Info.flagfft++]=ADCValue;
		if(Info.flagfft==Info.length)Info.dsp=1,Info.flagfft=0;
		LED_GPIO_PORT->ODR ^= LED1_GPIO_PIN;//turn PF6
	}
} 
//void TIM3_IRQHandler(void)   //TIM3??//1KHz Sample
//{
//	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //??TIM3???????
//	{
//		
//		//SignalGen();
//		uint16_t k=0;
//		adcvalue=ADC_GetConversionValue(ADC1);
//		//dacvalue=IIR(adcvalue);
//		//DAC_SetChannel1Data(DAC_Align_12b_R,dacvalue);
//		
////			Info.buff[Info.cnt]=(int16_t)(adcvalue)<<16;
////		if(Info.cnt>=LEN-1)
////			{
////			TIM_Cmd(TIM3, DISABLE);  //??TIM3		
////			}
////		  else Info.cnt++;
//		
//		if(!Info.dsp){
//			Info.RawData[0][Info.flagfft]=adcvalue<<16;
//			Info.RawData[1][Info.flagfft]=adcvalue;
//			Info.flagfft++;
//		}
//		Info.FIFO[0][Info.flag280]=(uint8_t)(adcvalue/4096.0f*200.0f);
//		//Info.BUFF[0][Info.flag]=Info.FIFO[0][Info.flag];
//		Info.flag280++;
//		//if(Info.flag==2800){
//		
//			//for(k=0;k<280;k++){
//				//Info.BUFF[0][k]=Info.FIFO[0][k*10];
//			//}
//		if(Info.flagfft==Info.length){
//				Info.dsp=1;
//			Info.flagfft=0;
//		}
//		if(Info.flag280==280)
//		{
//			Info.flag280=0;
//				if(Flag_show==0){
//					for(k=0;k<280;k++){
//					Info.BUFF[0][k]=Info.FIFO[0][k];
//				}
//				Flag_show=1;
//			}
//		}
//		LED_GPIO_PORT->ODR ^= LED1_GPIO_PIN;//turn PF6
//		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //??TIM3??????
//	}
//} 


