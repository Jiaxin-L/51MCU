
#include "Time.h"

//#message "Time.h��ʹ��REGX52.Hͷ�ļ�"
#include <REGX52.H>

#define FOSC 12000000L      //System frequency
//#message Time.h�趨�ľ���Ƶ��Ϊ 12000000L
//---TMOD��������---//
#define  T0NoReload13B 0x00
#define  T0NoReload16B 0x01
#define  T0Reload8B    0x10
#define  T0dual8B      0x11
#define  T0Count       0x04
#define  T0GATE        0x08

#define  T1NoReload13B 0x00
#define  T1NoReload16B 0x01
#define  T1Reload8B    0x10
#define  T1UnUsed8B    0x11
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
void TimeInit()
{
  T0_RUN(0);//�ض�ʱ��
  //�趨����ģʽ
  TMOD &=0xf0;
  TMOD |= T0NoReload16B;
  TMOD &= ~T0Count;
	//IT0=0;//�͵�ƽ����
  //��ʼֵ�趨
	SystemTick=0;
	
  T0Reload=(65536-FOSC/12/1000)+9; //��������ֵ ���Զ����ز���9
  TH0=T0Reload>>8;
  TL0=T0Reload;
  EA=1;//�����ж�
  T0_EnIT(1);//����ʱ��0�ж�

}
/****************************
//Function Name:  ��ʱ��0�жϺ���
//Input : void
//Output: void
//Description:
//
//***************************/
void Time0() interrupt 1
{
  TH0=T0Reload>>8;
  TL0=T0Reload;
  T0_ClearFlag(0);
  SystemTick++;

}

void StartTime()
{
 //TimeInit();
	 T0_RUN(1);//����ʱ��
}
unsigned int GetTime()
{

return SystemTick;
}

void EndTime(TimeVal* val)
{
 T0_RUN(0);//�ض�ʱ��
	val->ms=SystemTick;
	val->us=((TH0<<8)+TL0)-T0Reload;
}