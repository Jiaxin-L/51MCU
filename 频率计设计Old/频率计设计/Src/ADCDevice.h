#ifndef __ADCDEVICE_H_
#define __ADCDEVICE_H_


#define ADCDP P1
sbit CS=P2^0;                  //ADCģ��ͨѶ�ź�CS
sbit ADC_RD=P2^1;                  //ADCģ��ͨѶ�ź�ADC_RD
sbit NTR=P2^3;          //ADCģ��ͨѶ�ź�INT
//sbit LE=P2^4;                  //ADCģ����������������
sbit ADC_WR=P2^2;          //ADCģ��ͨѶ�ź�ADC_WR


void ADCInit();
unsigned char ReadAdc();
unsigned char  GetMaxADCVal();
#endif