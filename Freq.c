#include "Freq.h"
#include "Config.h"
extern struct InfoStruct Info;

void getRoughFreq(){
	Info.dsp=0;
	SetTimer(InitSampleFreq);
	//Delay_ms(500);
	while(!Info.dsp);
	//Info.dsp=0;
	//FFT1024();
	FFT1024();
//	C_FFT();
	//LCD_ShowNum(298,282,Info.amp,5,BLACK,WHITE);
	LCD_ShowNum(298,298,Info.freq,5,BLACK,WHITE);
	Info.freqRough=Info.freq;
	Info.dsp=0;
}
void searchFreq(){
	static uint8_t step=0;
	static uint8_t cnt=0;
	Info.freqErrorMax=50;
	if(step==0){
		Info.dsp=1;
		SetTimer(InitSampleFreq);
		//Info.dsp=0;
		step=1;
		Info.freqOk=0;
	}else if(step==1){
		if(Info.dsp){
			FFT1024();
			//LCD_ShowNum(298,282,Info.amp,5,BLACK,WHITE);
			LCD_ShowNum(298,298,Info.freq,5,BLACK,WHITE);
			Info.freqRough=Info.freq;
			//Info.dsp=0;
			step=2;
			Info.freqOk=0;
			if(Info.freqRough>5000.0f){
				Info.freqOk=1;
				step=0;
				return;
			}//else Info.freqOk=0;
		}
	}else	if(step==2){
		Info.SampleFreq=(uint16_t)(Info.freq*2);
		SetTimer(Info.SampleFreq);
		//Info.dsp=0;
		step=3;
		Info.freqOk=0;
	}else if(step==3){
		if(Info.dsp){
		FFT1024();
		//C_FFT();
		//LCD_ShowNum(298,282,Info.amp,5,BLACK,WHITE);
		LCD_ShowNum(298,298,Info.freq,5,BLACK,WHITE);
		Info.freqError=ABS(Info.freq*2-Info.SampleFreq);
		if(Info.freqError<=Info.freqErrorMax){
			Info.freqOk=1;
			step=0;
			return;
		}else{
			step=2;
			cnt++;
			if(cnt>=3){
				getRoughFreq();
				Info.freqOk=1;
				cnt=0;
			}
		}
		//Info.dsp=0;
	}
}

}
//void searchFreq(){
//	if(Info.freqRough>5000.0f){
//		Info.freqOk=1;
//		return;
//	}
//	Info.SampleFreq=(uint16_t)(Info.freq*2);
//	TIM3_Int_Init(((u32)(40000000.0f/(Info.SampleFreq*10.0f)))-1,7-1);//31//124 20.58//13
////	Delay_ms(1500);
//	Info.dsp=0;
//	//Delay_ms(500);
//	//Info.dsp=0;
//	while(!Info.dsp);
//	Info.dsp=0;
//	FFT1024();
//	//C_FFT();
//	Info.freqErrorMax=30;
//	Info.freqError=ABS(Info.freq*2-Info.SampleFreq);
//	if(Info.freqError<=Info.freqErrorMax){
//		Info.freqOk=1;
//		return;
//	}
//	LCD_ShowNum(298,282,Info.amp,5,BLACK,WHITE);
//	LCD_ShowNum(298,298,Info.freq,5,BLACK,WHITE);
//	Info.SampleFreq=(uint16_t)(Info.freq*2);
//	//Info.dsp=0;
//	TIM3_Int_Init(((u32)(40000000.0f/(Info.SampleFreq*10.0f)))-1,7-1);//31//124 20.58//13
////	Delay_ms(1500);
//	Info.dsp=0;
//	//Delay_ms(500);
//	//Info.dsp=0;
//	while(!Info.dsp);
//	Info.dsp=0;
//	FFT1024();
//	//C_FFT();
//	Info.freqError=ABS(Info.freq*2-Info.SampleFreq);
//	if(Info.freqError<=Info.freqErrorMax){
//		Info.freqOk=1;
//		return;
//	}
//	LCD_ShowNum(298,282,Info.amp,5,BLACK,WHITE);
//	LCD_ShowNum(298,298,Info.freq,5,BLACK,WHITE);
//	Info.SampleFreq=(uint16_t)(Info.freq*2);
//	Info.dsp=0;
//	TIM3_Int_Init(((u32)(40000000.0f/(Info.SampleFreq*10.0f)))-1,7-1);//31//124 20.58//13
////	Delay_ms(1500);
//	Info.dsp=0;
//	//Delay_ms(500);
//	//Info.dsp=0;
//	while(!Info.dsp);
//	Info.dsp=0;
//	FFT1024();
//	//C_FFT();
//	Info.freqError=ABS(Info.freq*2-Info.SampleFreq);
//	if(Info.freqError<=Info.freqErrorMax){
//		Info.freqOk=1;
//		return;
//	}
////	Info.fre=Info.freq;
//	LCD_ShowNum(298,282,Info.amp,5,BLACK,WHITE);
//	LCD_ShowNum(298,298,Info.freq,5,BLACK,WHITE);
//	Info.freqOk=1;
//}
