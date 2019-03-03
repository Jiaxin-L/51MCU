// Header:
// File Name:
// Author:chengmeng2018
// Date:2019��3��3��
// Version: 1.0

#include "Keyboard.h"

enum KeyState {keywait=0,keydelay,keycheck,KeyDown,keyWaitUp};
unsigned char GetKeyNumMatrixKeyboard();
unsigned char GetKeyNumIndependentButton();
//�������
unsigned char  keyScanf(unsigned char *Keynum)
{
	static unsigned char keyState=keywait;
	static unsigned char KeyLastTemp,LastTime;
	unsigned char KeyTemp=0;
	//��ⰴ��
	KeyTemp = GetKeyNumIndependentButton();//��ȡ��������
	//KeyTemp = GetKeyNumMatrixKeyboard();//��ȡ�������
	//KeyTemp==0 û�а�������
	//KeyTemp!=0  �а�������
	switch(keyState )
	{
	case keywait: //�ȴ���������
		if (KeyTemp !=0)
		{
			keyState = keydelay;
			KeyLastTemp=KeyTemp;
			LastTime=GetTime();
		}
		break;
	case keydelay: //��ʱ����
		if(LastTime+Time100ms<GetTime())
		{
			keyState = keycheck;
		}
		break;
	case keycheck://��鰴����һ����
		if( KeyLastTemp== KeyTemp)
		{
			keyState = KeyDown;
		}
		else
		{
			keyState = keywait;
		}
		break;
	case KeyDown://�������µ�״̬
		keyState = keyWaitUp;
		break;
	case keyWaitUp://��������������
		if( KeyLastTemp != KeyTemp)
		{
			keyState++;
		}

		break;
//case doublebutton: //�ٴμ�⵽�����İ��� ��˫���¼�

//break;
	default:
		keyState=keywait;
		KeyLastTemp=0x00;
		break;
	}
	*Keynum=KeyLastTemp;

	return keyState;
}
#define GPIO_KEY P1

unsigned char GetKeyNumMatrixKeyboard()
{
	unsigned char KeyValue;
//������Ŷ�ȡ���ļ�ֵ
	GPIO_KEY=0X0F;
// 			Delay10ms(1);
	switch(GPIO_KEY)
	{
	case(0X07):
		KeyValue=GPIO_KEY;
		break;
	case(0X0b):
		KeyValue=GPIO_KEY;
		break;
	case(0X0d):
		KeyValue=GPIO_KEY;
		break;
	case(0X0e):
		KeyValue=GPIO_KEY;
		break;
	case (0x0f):
		KeyValue=GPIO_KEY;
		break;
//				default:	KeyValue=17;	//������ظ�17��˼�ǰ������ȫ�����
	}
	//������
	GPIO_KEY=0XF0;
//			Delay10ms(1);
	switch(GPIO_KEY)
	{
	case(0X70):
		KeyValue=GPIO_KEY+KeyValue;
		break;
	case(0Xb0):
		KeyValue=GPIO_KEY+KeyValue;
		break;
	case(0Xd0):
		KeyValue=GPIO_KEY+KeyValue;
		break;
	case(0Xe0):
		KeyValue=GPIO_KEY+KeyValue;
		break;
	case (0xf0):
		KeyValue=GPIO_KEY+KeyValue;
		break;
//				default:	KeyValue=17;
	}
	return ~KeyValue;
}

//��������ģʽ ��ÿ������״̬ƴ����һ���Ĵ�����
unsigned char GetKeyNumIndependentButton()
{
	unsigned char KeyTemp=0;
	KeyTemp += (unsigned char)!key3;
	KeyTemp =  KeyTemp<<1;
	KeyTemp += (unsigned char)!key2;
	KeyTemp =  KeyTemp<<1;
	KeyTemp += (unsigned char)!key1;
	KeyTemp =  KeyTemp<<1;
	KeyTemp += (unsigned char)!key0;

	return KeyTemp;
}

