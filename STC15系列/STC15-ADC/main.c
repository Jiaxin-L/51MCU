#include "STC15F2K60S2.H"
#include "STC15_ADC.h"
void main()
{
	unsigned int ADC_value=0;
	ADCInit(0x01);//��ʼ��ADC
	while(1)
	{
		ADC_value = ADCRead(0);//��ȡ0ͨ������ADC��ֵ
		P2 = ADC_value& 0x00ff;
	}
}

