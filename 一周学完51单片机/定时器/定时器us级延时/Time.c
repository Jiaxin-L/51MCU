// Header: 8051�ں˵�Ƭ��ͨ�ö�ʱ��T0 T1ͷ�ļ�
// File Name: Time.h
// Author: ����plus
// Date: 2019��4��6��
// Version: V1.0

#include "Time.h"

//#message "Time.h��ʹ��REGX52.Hͷ�ļ�"
#include <REGX52.H>

#define FOSC 12000000L      //System frequency
//#message Time.h�趨�ľ���Ƶ��Ϊ 12000000L
//---TMOD��������---//
#define  T0NoReload13B 0x00
#define  T0NoReload16B 0x01
#define  T0Reload8B    0x02
#define  T0dual8B      0x03
#define  T0Count       0x04
#define  T0GATE        0x08

#define  T1NoReload13B 0x00
#define  T1NoReload16B 0x10
#define  T1Reload8B    0x20
#define  T1UnUsed8B    0x30
#define  T1Count       0x40
#define  T1GATE        0x80

//---TCON��������---//

//��ʱ������ֵ
unsigned int T0Reload,T1Reload;

//ȫ��ϵͳʱ��
unsigned int SystemTick =0;

/****************************
//Function Name:  ��ʱ��
//Input : FOSC ����Ƶ��
          Reload ����Ƶ�� Ƶ�ʷ�Χ(100~100000)
//Output: void
//Description:  ��ʱ����ʼ���������ö�ʱ��
//
//***************************/
void TimeInit(unsigned int Reload)
{
    T0_RUN(0);//�ض�ʱ��
    //�趨����ģʽ
    TMOD &=0xf0;
    TMOD |= T0NoReload16B;
    TMOD &= ~T0Count;
    //��ʼֵ�趨
    T0Reload=(65536-FOSC/12/Reload)+9; //��������ֵ ���Զ����ز���9
    TH0=T0Reload>>8;
    TL0=T0Reload;
    EA=1;//�����ж�
    T0_EnIT(1);//����ʱ��0�ж�
}
/****************************
//Function Name:  ��������ʱ����
//Input : void
//Output: ��ʱʱ���Ƿ���
//Description: ��ʱʱ�䲻��������������
//
//***************************/
void DelayNonBlocking(DelayTypedef* DelayStruct)
{
    if(DelayStruct->State ==Start)
    {
        DelayStruct->StartMs=SystemTick;
        DelayStruct->EndMs = DelayStruct->StartMs+DelayStruct->DelayMs;
    }
    if( DelayStruct->EndMs > DelayStruct->StartMs)
    {
        if( SystemTick > DelayStruct->EndMs)
        {
            DelayStruct->State=Ok;
        }
        else
        {
            DelayStruct->State=Wait;
        }
    }
    else
    {
        if( SystemTick<DelayStruct->StartMs && SystemTick > DelayStruct->EndMs)
        {
            DelayStruct->State=Ok;
        }
        else
        {
            DelayStruct->State=Wait;
        }
    }
}
/****************************
//Function Name:  ms����ʱ����
//Input : ��ʱʱ��
//Output: ��ʱ����˳�
//Description:
//
//***************************/
void DelayBlocking(unsigned int Time)
{
    unsigned int CurrentTime=SystemTick;
    while(Time)
    {
        if(CurrentTime!=SystemTick)
        {
            CurrentTime=SystemTick;
            Time--;
        }
    }
}
/**
  * @brief  ����ʱʵ�ֶ�ʱ
  * @note 	����ʱ�̶���ʱ ͨ���޸�_nop_������������ʱ��Χ����һ��_nop_��ʱ 5us
				û��һ��_nop_ ����1us 
  * @retval
  */
//#include <intrins.h>
extern void          _nop_     (void);
void Delay10us()
{//���뺯�� 2
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
}//�������� 2
/**
  * @brief  ʹ�ö�ʱ�����10~65535us������ʱ
  * @note 	���ڳ�ʼ�趨��Ҫ����ʱ�� ���������������ֿ�
  * @retval 
  */
void T1Delayus(unsigned int time)
{
	T1_RUN(0);//ֹͣT1
	T1_EnIT(0);//��T1�ж�
	T1_Flag(0);
	TMOD &=0x0f;//��ն�ʱ��1
	TMOD |=T1NoReload16B;
	TH1=-time>>8;
	TL1=-time;
}
/****************************
//Function Name:  ��ʱ��0�жϺ���
//Input : void
//Output: void
//Description:
//
//***************************/
void Time0(void) interrupt 1
{
    TH0=T0Reload>>8;
    TL0=T0Reload;
    T0_Flag(0);
    SystemTick++;

}
/****************************
//Function Name:  ��ʱ��1�жϺ���
//Input : void
//Output: void
//Description:
//
//***************************/
void Time1(void) interrupt 3
{

}