#ifndef __FFT_H__
#define __FFT_H__	 
#include "Config.h"
//FFT 频谱分析
//可以执行64/128/256/512/1024等点数的FFT计算
//正点原子@SUNTEK
//2010/3/23
    
//傅里叶变换 输入和输出缓存区
typedef struct
{ 
	float real;
	float imag;
}compx;
					   
#define FFT_1024 //1024点的FFT 

#ifdef FFT_64
#define FFT_N 64
#endif
#ifdef FFT_128
#define FFT_N 128
#endif
#ifdef FFT_256
#define FFT_N 256
#endif
#ifdef FFT_512
#define FFT_N 512
#endif
#ifdef FFT_1024
#define FFT_N 1024
#endif	 
extern compx fftres[FFT_N];    //FFT数据段 
void FFT(compx *xin,u16 N);//N点FFT计算函数
#endif





















