#include "FFT_C.h"
#include "fft_tab.h"
extern struct InfoStruct Info;

//FFT 频谱分析
//可以执行64/128/256/512/1024等点数的FFT计算
//所需要的变量:
//(FFT_N+1)*8 个字节左右
//正点原子@SUNTEK
//2010/3/23	 
//extern compx fftres[FFT_N]; //FFT数据段 				  
//m^n函数
u32 mypow_fft(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}   
//快速傅里叶变换
//32/64/128/256/512/1024点的FFT
//STM32 计算1024点费时35.7ms左右@72M 
//如果超频到120M,则时间只需要22ms左右了
//N:傅里叶变换的点数
//xin:输入数组大小为N+1
void FFT(compx *xin,u16 N)
{
	u16 f,m,LH,nm,i,k,j,L;
	u16 p;
	u16 le,B,ip;    		   
 	compx ws,t;
	LH=N/2;
	f=N;
	for(m=1;(f=f/2)!=1;m++);//求得M的值 
	nm=N-2;    
	j=N/2;		  
	for(i=1;i<=nm;i++)//码位倒置
	{
		if(i<j){t=xin[j];xin[j]=xin[i];xin[i]=t;}//码位家换
		k=LH;
		while(j>=k){j=j-k;k=k/2;}
		j=j+k;
	}    
	for(L=1;L<=m;L++) //fft  傅里叶变换
	{  
		le=mypow_fft(2,L);//用自己定义的乘方函数,效率比库函数高很多.这里如果采用移位计算,效率更高.	  
		B=le/2;	   	 
		for(j=0;j<=B-1;j++)
		{			  
			p=mypow_fft(2,m-L)*j;  //用自己定义的乘方函数,效率比库函数高很多.	   
			ws.real=cos_tab[p];
			ws.imag=sin_tab[p];
			for(i=j;i<=N-1;i=i+le)//遍历M级所有的碟形
			{ 
				ip=i+B;		 
				//执行复数乘法
				t.real=xin[ip].real*ws.real-xin[ip].imag*ws.imag;
				t.imag=xin[ip].real*ws.imag+xin[ip].imag*ws.real;

				xin[ip].real=xin[i].real-t.real;
				xin[ip].imag=xin[i].imag-t.imag;
				xin[i].real=xin[i].real+t.real;
				xin[i].imag=xin[i].imag+t.imag;
			}
		}
	}   
}

















