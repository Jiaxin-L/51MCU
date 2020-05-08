
#include <REGX52.H>
#include "keyBoard.h"


void delay2ms(void)   //��ʱ����
{
    unsigned char i,j;
    for(i=133; i>0; i--)
        for(j=6; j>0; j--);
}
unsigned char 	GetMatrixKeyboard()
{
    unsigned char KeyValue;
//������Ŷ�ȡ���ļ�ֵ
    MatrixKeyboard=0X0F;
    delay2ms();
    switch(MatrixKeyboard)
    {
    case(0X07):
        KeyValue=0;
        break;
    case(0X0b):
        KeyValue=4;
        break;
    case(0X0d):
        KeyValue=8;
        break;
    case(0X0e):
        KeyValue=12;
        break;
    default:
        KeyValue=17;	//������ظ�17��˼�ǰ������ȫ�����
        break;
    }
    //������
    MatrixKeyboard=0XF0;
    delay2ms();
    switch(MatrixKeyboard)
    {
    case(0X70):
        KeyValue=0+KeyValue;
        break;
    case(0Xb0):
        KeyValue=1+KeyValue;
        break;
    case(0Xd0):
        KeyValue=2+KeyValue;
        break;
    case(0Xe0):
        KeyValue=3+KeyValue;
        break;
        break;
    default:
        KeyValue=17;
        break;
    }
    return KeyValue;
}
sbit Key1=P2^4;
//sbit Key2=P1^2;
unsigned char IndependentKeyboard()
{
    unsigned char keyValue=0;
    keyValue=!Key1;
   // keyValue<<=1;
    //keyValue|=!Key2;
    return keyValue;
}
//�������
unsigned char key_scan(KeyStruct* KeyNum)
{
    unsigned char keyValue=0;
    unsigned char State=KeyNum->State;
    unsigned char KeyTemp=KeyNum->Value;
    /*******������̶�ȡ����******/
    keyValue =	IndependentKeyboard();//�����������
//  keyValue==0��ʾû�а�������
    /*******������̶�ȡ����***
    	keyValue=GetMatrixKeyboard()
        keyValue==17��ʾû�а�������
    ����������ע���޸� CheckKey��֧�ж�����
    *************************/
    switch(State)
    {
    case CheckKey:
        if(keyValue !=0)
        {
            KeyTemp=keyValue;
            State=DelayKey;
        }
        break;
    case DelayKey:
        delay2ms();
        State= KeyTemp==keyValue ? KeyFallEdge:CheckKey;
        break;
    case KeyFallEdge:
        State=KeyDown;
        break;
    case KeyDown:
        if(KeyTemp != keyValue)
        {
            State=KeyRisEdge;
            KeyNum->lastValue= KeyTemp;
        }
        break;
    case KeyRisEdge:
        State=CheckKey;
        break;
    default:
        break;
    }
    KeyNum->State=State;
    KeyNum->Value=keyValue;
    return State;
}
