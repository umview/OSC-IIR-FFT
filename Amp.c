#include "Amp.h"
#include "Config.h"
extern struct InfoStruct Info;
extern uint8_t Flag_show;

void GetAmp(){
	uint16_t indexmax=0,indexmin=0;
	uint16_t MaxAmp=0,MinAmp=0;
	//Info.dsp=0;
	//while(!Info.dsp);
	if(Info.dsp){
		indexmax=FindMax((long*)(Info.RawData[1]),Info.length);
		MaxAmp=Info.RawData[1][indexmax];
		indexmin=FindMin((long*)(Info.RawData[1]),Info.length);
		MinAmp=Info.RawData[1][indexmin];
		Info.amp=((MaxAmp-MinAmp-25)/4096.0f*3280);
		//Info.dsp=0;
	}
}
void GetFFTAmp(){
	uint16_t k=0;
	double sum=0.0f;
	FFT1024();
	//Info.amp=(uint16_t)(Info.Amplitude[Info.freq_index]);
	if(Info.type==1){//Tri
		Info.amp=(uint16_t)(Info.Amplitude[Info.freq_index]);
		Info.amp+=getAmp(Info.freq_index*3,15);
		Info.amp+=getAmp(Info.freq_index*5,15);
	}
	if(Info.type==2){//Sqr
		Info.amp=(uint16_t)(Info.Amplitude[Info.freq_index]);
		//Info.amp+=getAmp(Info.freq_index*3,5);
	}
	if(Info.type==3){//Sin
		Info.amp=(uint16_t)(Info.Amplitude[Info.freq_index]);
		//Info.amp+=(uint16_t)(Info.Amplitude[Info.freq_index+1]);
		//Info.amp+=(uint16_t)(Info.Amplitude[Info.freq_index-1]);
		//Info.amp+=(uint16_t)(Info.Amplitude[Info.freq_index+2]);
		//Info.amp+=(uint16_t)(Info.Amplitude[Info.freq_index-2]);
	}else{
		Info.amp=(uint16_t)(Info.Amplitude[Info.freq_index]);
	}
//	sum+=Info.Amplitude[0]/(Info.length*1.0f);
	//sum+=Info.Amplitude[Info.length/2]/(Info.length*1.0f);
	//Info.length=256;
	//FFT256();
	//Info.amp=(uint16_t)(getAmp(Info.freq_index,20));

}
