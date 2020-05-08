#include <REGX52.H>
#include "ADCDevice.h"

void Delay100us(); //@12.000MHz
void ADCInit()
{
  ADCDP = 0XFF; //ADC���ݽ��ս�
  CS = 1;       //ADC��������Ϊ������ʼʱ�򣬳�ʼ�����ߵ�ƽ
  ADC_RD = 1;       //ADC��������Ϊ������ʼʱ�򣬳�ʼ�����ߵ�ƽ
  NTR = 1;      //ADC��������Ϊ������ʼʱ�򣬳�ʼ�����ߵ�ƽ
}
void ADCEnd()
{

  ADC_RD = 1;   //��ADCͨѶ�������³�ʼ�����ߵ�ƽ״̬
  CS = 1;     //��ADCͨѶ�������³�ʼ�����ߵ�ƽ״̬
  NTR = 1; //��ADCͨѶ�������³�ʼ�����ߵ�ƽ״̬
  ADC_WR = 1;     //��ADCͨѶ�������³�ʼ�����ߵ�ƽ״̬
  Delay100us();
}
unsigned char ReadAdc()
{
	unsigned char ADCVal;
//  LE = 1;
  CS = 0;
  Delay100us();
  ADC_WR = 0;
  Delay100us();

  //�ȴ�ADCת������
  while (NTR == 0); 
  CS = 0;
  Delay100us();
  ADC_RD = 0;
  Delay100us();
//  LE = 0;
  ADCVal = ADCDP; //��ADCת���������ȡֵ
  ADCEnd();
  return ADCVal;
}
void Delay100us() //@12.000MHz
{
  unsigned char i;
  i = 47;
  while (--i);
}
unsigned char  GetMaxADCVal()
{
	unsigned char SVal,SValOld;
	char i=0;
	SVal=SValOld=ReadAdc();
	//�ȹ��½�����
  while(SVal<=SValOld)
  {
		SValOld=SVal;
    SVal=ReadAdc();
  }	
	//Ѱ����ߵ�
  while(SVal>=SValOld)
  {
    SValOld=SVal;
    SVal=ReadAdc();
  }
	//�������ֵ
return SValOld;
}