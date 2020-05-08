
//---����ͷ�ļ�---//
#include<reg51.h>
#include<intrins.h>
#include"XPT2046.h"


	//	temp = Read_AD_Data(0x94);		//   AIN0 ��λ��
	//	temp = Read_AD_Data(0xD4);		//   AIN1 ��������
	//	temp = Read_AD_Data(0xA4);		//   AIN2 ��������
	//	temp = Read_AD_Data(0xE4);		//   AIN3 �ⲿ����
/****************************************************************************
*��������TSPI_Start
*��  �룺��
*��  ������
*��  �ܣ���ʼ������SPI
****************************************************************************/

void SPI_Start(void)
{
	CLK = 0;
	CS  = 1;
	DIN = 1;
	CLK = 1;
	CS  = 0;		
}
/****************************************************************************
*��������SPI_Write
*��  �룺dat��д������
*��  ������
*��  �ܣ�ʹ��SPIд������
****************************************************************************/

void SPI_Write(uchar dat)
{
	uchar i;
	CLK = 0;
	for(i=0; i<8; i++)
	{
		DIN = dat >> 7;  	//�������λ
		dat <<= 1;
		CLK = 0;			//�����ط�������

		CLK = 1;

	}
}
/****************************************************************************
*��������SPI_Read
*��  �룺��
*��  ����dat����ȡ ��������
*��  �ܣ�ʹ��SPI��ȡ����
****************************************************************************/

uint SPI_Read(void)
{
	uint i, dat=0;
	CLK = 0;
	for(i=0; i<12; i++)		//����12λ����
	{
		dat <<= 1;

		CLK = 1;
		CLK = 0;

		dat |= DOUT;

	}
	return dat;	
}

/****************************************************************************
*��������Read_AD_Data
*��  �룺cmd����ȡ��X����Y
*��  ����endValue�������źŴ���󷵻ص�ֵ
*��  �ܣ���ȡ��������
****************************************************************************/
uint Read_AD_Data(uchar cmd)
{
	uchar i;
	uint AD_Value;
	CLK = 0;
	CS  = 0;
	SPI_Write(cmd);
	for(i=6; i>0; i--); 	//��ʱ�ȴ�ת�����
	CLK = 1;	  //����һ��ʱ�����ڣ����BUSY
	_nop_();
	_nop_();
	CLK = 0;
	_nop_();
	_nop_();
	AD_Value=SPI_Read();
	CS = 1;
	return AD_Value;	
}
uint GetMaxADCVal()
{
	unsigned int SVal,SValOld;
	char i=0;
	SVal=SValOld=Read_AD_Data(0xE4);
	//�ȹ��½�����
  while(SVal<=SValOld)
  {
		SValOld=SVal;
    SVal=Read_AD_Data(0xE4);
  }	
	//Ѱ����ߵ�
  while(SVal>=SValOld)
  {
    SValOld=SVal;
    SVal=Read_AD_Data(0xE4);
  }
	//�������ֵ
return SValOld;
}
