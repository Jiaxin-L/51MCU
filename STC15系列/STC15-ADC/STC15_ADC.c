// Header: STC15_ADC
// File Name:
// Author:	chengmeng2018
// Date: 2019��3��1��

#include "STC15_ADC.h"

#include "STC15F2K60S2.H"
/**
  * @brief  ADC���ų�ʼ������
  * @note 	���������Ϊ�������Ų���
  * @retval NULL
  */
void ADCInit(unsigned char ADC_Pins)
{
	//P1 ������Ϊ���ù��ܺ���ܶ�ȡADC
	P1ASF =ADC_Pins;
	ADC_CONTR =ADC_POWER|ADC_SPEED540;
	ADC_CONTR &=~ADC_FLAG;//���ת����ɱ�־λ
	CLK_DIV &=~0x20;//�趨���ݸ�ʽ
	//delay();����������Ҫ����ʱ
}
/**
  * @brief  ��λ�ر�ADCģ��
  * @note 	�����ʼ�����û�ԭĬ��״̬
  * @retval NULL
  */
void ADCDeInit()
{
	ADC_CONTR=0x00;
	P1ASF=0x00;
}
/**
  * @brief  ��ȡAC����
  * @note 	ADC_CHS��ֵ��Χ��0~7;
  * @retval 
  */
unsigned int ADCRead(unsigned char ADC_CHS)
{
	unsigned int ADC_VAL=3;
	ADC_RES=0;//����λ����
	ADC_RESL=0;
	ADC_CONTR =ADC_POWER |(ADC_CHS&0x07) |ADC_START;//ͨ�� ѡ��ͨ�� ��ʼת��
	while(ADC_VAL--);//�򵥵�һ��
	while(ADC_CONTR&ADC_FLAG ==0);//�ȴ�ת�����
	ADC_VAL=(ADC_RES<<2) |(ADC_RESL&0x03);//10λ����ƴ�ӱ���
	return ADC_VAL;
}
/**
  * @brief  �޸�ADCģ���ٶ�����
  * @note   һ���ڳ�ʼ��֮�����޸�
	* ADC_SPEED�ٶȷ�Χ�������漸��ѡ�� 
	*             ADC_SPEED90 
	*             ADC_SPEED180
	*             ADC_SPEED360
  *             ADC_SPEED540
	* @retval NULL
  */
void ADCSetSpeed(unsigned char  ADC_SPEED)
{

	ADC_CONTR &= ~ADC_SPEEDMASK;//���speedλ
	ADC_CONTR |=(ADC_SPEED & ADC_SPEEDMASK);     //���ù����ٶ�
}