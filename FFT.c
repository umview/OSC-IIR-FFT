#include "FFT.h"
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
#include "AD9834.h" 
#include "FFT_C.h"
#include "wavetype.h"
extern struct InfoStruct Info;
extern float SDS[4];
compx fftres[FFT_N]; //FFT数据段 				  

void FFT1024(void){
		uint16_t k=0;
		for(k=0;k<Info.length;k++)Info.RawData[0][k]=Info.RawData[1][k]<<16;
		cr4_fft_1024_stm32(Info.FArray, Info.RawData[0], Info.length);
		GetPowerMag();
		Info.freq_index=FindRangeMax(Info.Amplitude,1,Info.length/2);
			Info.freq=(uint16_t)(Info.omega[Info.freq_index]);
			//Info.amp=(uint16_t)(Info.Amplitude[FindRangeMax(Info.Amplitude,1,Info.length/2)]);
			Info.DC=(uint16_t)(Info.Amplitude[0]/2.0f);
//		for(k=0;k<Info.length;k++)
//		{
//			SDS[2]=(uint16_t)(Info.RawData[1][k]);
//			//SDS[3]=(int16_t)(Info.ratio/10.0f);
//			Plot(SDS);
//		}
//		for(k=0;k<Info.length/2;k++)
//		{
//			SDS[0]=Info.Amplitude[k];
//			SDS[1]=(uint16_t)(Info.omega[k]);;
//			SDS[2]=(uint16_t)(Info.amp);
//			SDS[3]=(uint16_t)k;
//			Plot(SDS);
//		}
}
void FFT256(void){
		uint16_t k=0;
		for(k=0;k<Info.length;k++)Info.RawData[0][k]=Info.RawData[1][k]<<16;
		cr4_fft_256_stm32(Info.FArray, Info.RawData[0], Info.length);
		GetPowerMag();
			Info.freq=(uint16_t)(Info.omega[FindRangeMax(Info.Amplitude,1,Info.length/2)]);
			//Info.amp=(uint16_t)(Info.Amplitude[FindRangeMax(Info.Amplitude,1,Info.length/2)]);
			Info.DC=(uint16_t)(Info.Amplitude[0]/2.0f);
		for(k=0;k<Info.length;k++)
		{
			SDS[2]=(uint16_t)(Info.RawData[1][k]);
			//SDS[3]=(int16_t)(Info.ratio/10.0f);
			Plot(SDS);
		}
		for(k=0;k<Info.length/2;k++)
		{
			SDS[0]=Info.Amplitude[k];
			SDS[1]=(uint16_t)Info.omega[k];
			SDS[3]=(uint16_t)k;

			Plot(SDS);
		}
}
void FFT64(void){
		uint16_t k=0;
		for(k=0;k<Info.length;k++)Info.RawData[0][k]=Info.RawData[1][k]<<16;
		cr4_fft_64_stm32(Info.FArray, Info.RawData[0], Info.length);
		GetPowerMag();
			Info.freq=(uint16_t)(Info.omega[FindRangeMax(Info.Amplitude,1,Info.length/2)]);
			//Info.amp=(uint16_t)(Info.Amplitude[FindRangeMax(Info.Amplitude,1,Info.length/2)]);
			Info.DC=(uint16_t)(Info.Amplitude[0]/2.0f);
		for(k=0;k<Info.length;k++)
		{
			SDS[2]=(uint16_t)(Info.RawData[1][k]);
			//SDS[3]=(int16_t)(Info.ratio/10.0f);
			Plot(SDS);
		}
		for(k=0;k<Info.length/2;k++)
		{
			SDS[0]=Info.Amplitude[k];
			SDS[1]=(uint16_t)Info.omega[k];
			SDS[3]=(uint16_t)k;

			Plot(SDS);
		}
}
void GetFFT(void){
	SetTimer(Info.SampleFreq);
	//	Delay_ms(1500);
	Info.dsp=0;
	//Delay_ms(500);
	//Info.dsp=0;
	while(!Info.dsp);
	Info.dsp=0;
	FFT1024();
	LCD_ShowNum(298,282,Info.amp,5,BLACK,WHITE);
	LCD_ShowNum(298,298,Info.freq,5,BLACK,WHITE);
}
compx fftres[FFT_N];    //FFT数据段 
compx XIN[FFT_N+1];
//void C_FFT(){
//	uint16_t i=0;
//	for(i=0;i<FFT_N+1;i++){
//		XIN[i].real=Info.RawData[0][i];
//	}
//	//FFT((int*)Info.RawData[0],Info.FFT_Real,Info.FFT_Image);
//	FFT(XIN,1024);

//	
//	for(i=0;i<512;i++){
//		Info.Mag[i]=sqrt(fftres[i].imag*fftres[i].imag+fftres[i].real*fftres[i].real);
//	}
//		for(i=0;i<1024/2;i++)
//		{
//			SDS[0]=(int16_t)Info.Mag[i];
//			Plot(SDS);
//		}
//			Info.freq=(uint16_t)(FindRangeMax((uint16_t *)Info.Mag,1,Info.length/2)*20000/1024.0f);
//Info.amp=(uint16_t)(Info.Amplitude[FindRangeMax(Info.Amplitude,1,Info.length/2)]);
//			//Info.DC=(uint16_t)(Info.Amplitude[0]/2.0f);
//}
