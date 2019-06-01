#include "FFT_C.h"
#include "fft_tab.h"
extern struct InfoStruct Info;

//FFT Ƶ�׷���
//����ִ��64/128/256/512/1024�ȵ�����FFT����
//����Ҫ�ı���:
//(FFT_N+1)*8 ���ֽ�����
//����ԭ��@SUNTEK
//2010/3/23	 
//extern compx fftres[FFT_N]; //FFT���ݶ� 				  
//m^n����
u32 mypow_fft(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}   
//���ٸ���Ҷ�任
//32/64/128/256/512/1024���FFT
//STM32 ����1024���ʱ35.7ms����@72M 
//�����Ƶ��120M,��ʱ��ֻ��Ҫ22ms������
//N:����Ҷ�任�ĵ���
//xin:���������СΪN+1
void FFT(compx *xin,u16 N)
{
	u16 f,m,LH,nm,i,k,j,L;
	u16 p;
	u16 le,B,ip;    		   
 	compx ws,t;
	LH=N/2;
	f=N;
	for(m=1;(f=f/2)!=1;m++);//���M��ֵ 
	nm=N-2;    
	j=N/2;		  
	for(i=1;i<=nm;i++)//��λ����
	{
		if(i<j){t=xin[j];xin[j]=xin[i];xin[i]=t;}//��λ�һ�
		k=LH;
		while(j>=k){j=j-k;k=k/2;}
		j=j+k;
	}    
	for(L=1;L<=m;L++) //fft  ����Ҷ�任
	{  
		le=mypow_fft(2,L);//���Լ�����ĳ˷�����,Ч�ʱȿ⺯���ߺܶ�.�������������λ����,Ч�ʸ���.	  
		B=le/2;	   	 
		for(j=0;j<=B-1;j++)
		{			  
			p=mypow_fft(2,m-L)*j;  //���Լ�����ĳ˷�����,Ч�ʱȿ⺯���ߺܶ�.	   
			ws.real=cos_tab[p];
			ws.imag=sin_tab[p];
			for(i=j;i<=N-1;i=i+le)//����M�����еĵ���
			{ 
				ip=i+B;		 
				//ִ�и����˷�
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

















