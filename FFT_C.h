#ifndef __FFT_H__
#define __FFT_H__	 
#include "Config.h"
//FFT Ƶ�׷���
//����ִ��64/128/256/512/1024�ȵ�����FFT����
//����ԭ��@SUNTEK
//2010/3/23
    
//����Ҷ�任 ��������������
typedef struct
{ 
	float real;
	float imag;
}compx;
					   
#define FFT_1024 //1024���FFT 

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
extern compx fftres[FFT_N];    //FFT���ݶ� 
void FFT(compx *xin,u16 N);//N��FFT���㺯��
#endif





















