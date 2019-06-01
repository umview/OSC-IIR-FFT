#ifndef _CONFIG_
#define _CONFIG_
#include "Gpio.h"
#include "delay.h"
#include "USART.h"
#include "ADC.h"
#include "SDS.h"
#include "fsmc_sram.h"
#include "Timer.h"
#include "stm32_dsp.h"
#include "math.h"
#include "ForSin50Hz_1KHz.h"
#include "ForNonSin50Hz_200Hz.h"
#include "Function.h"
#include "Freq.h"
#include "Amp.h"
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
#include "Amp.h"
#include "WB_LCD.h"
//#include "HZ.h"
#include "AD9834.h" 

#include "FFT_C.h"
//#include "WB_LCD.h"
//#include "HZ.h"
//#include "hebut.h"
/********************************************************************/
#define LEN 1024
#define InitSampleFreq 20000
#define SearchFreqWidth 300
#define COE 5

struct InfoStruct {
	long buff[LEN];
	uint16_t cnt;
	uint32_t SampleFreq;
	long FArray[LEN/2];           //傅里叶数据
	long lBufMagArray[LEN/2];     //各次谐波幅值
	float omega[LEN/2];           //计算基波频率
	uint16_t flag280;
	uint16_t flagfft;
	uint16_t k ;
	uint8_t FIFO[2][280];
	uint8_t BUFF[2][280];
	float freq;
	float freqRough;
	float amp;
	long RawData[2][LEN];
	uint16_t Amplitude[LEN/2];
	uint8_t dsp;
	uint16_t DC;
	uint16_t length;
	uint16_t freqError;
	uint8_t freqOk;
	uint8_t ampOk;
	uint16_t freqErrorMax;
	int16_t slope[280];
	uint16_t integral;
	float ratio;
	float First;
	uint16_t index;
	float Third;
	float fre;
	uint16_t freq_index;
	uint16_t amp_max_index;
	uint8_t waveOk;
	uint8_t type;
//	compx XIN[LEN];
	//double FFT_Image[LEN];
	
};
#define ABS(x) ( (x)>0?(x):-(x) )
#define SCALE 3280
#define SetTimer(x)   (TIM1_Int_Init(((u32)(40000000.0f/(x*20.0f)))-1,18-1))

struct SinStruct {
	uint16_t max_index;
	uint16_t fun_amp;
	float fun_freq;
	float current;
};
struct NonSinStruct {
	uint16_t max_index;
	uint16_t fun_amp;
	uint16_t harmonic_1_amp;
	uint16_t harmonic_2_amp;
	uint16_t harmonic_3_amp;
	uint16_t harmonic_4_amp;
	uint16_t harmonic_5_amp;
	float fun_freq;
	float harmonic_1_freq;
	float harmonic_2_freq;
	float harmonic_3_freq;
	float harmonic_4_freq;
	float harmonic_5_freq;
};
#endif
