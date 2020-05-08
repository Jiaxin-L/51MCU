// Header: 8051�ں˵�Ƭ��ͨ�ö�ʱ��T0 T1ͷ�ļ�
// File Name: Time.h
// Author: ����plus
// Date: 2019��4��6��
// Version: V1.0

#ifndef  __TIME_H_
#define  __TIME_H_

typedef struct 
{
  unsigned int ms;
  unsigned int us;
} TimeVal;
#define T0_RUN(State) (TR0=State)
#define T1_RUN(State) (TR1=State)
#define T0_ClearFlag(State) (TF0=State)
#define T1_ClearFlag(State) (TF1=State)
#define T0_EnIT(State)  (ET0=State)
#define T1_EnIT(State)  (ET1=State)
//��ʱ����ʼ������ Reload ����Ƶ�� Ƶ�ʷ�ΧԼ(100~100000)
void TimeInit();

//��ȡ��ǰʱ��;
unsigned int GetTime();
/*���湦�������湦�ܳ�ͻֻ�ܵ���ʹ��*/
void StartTime();
void EndTime(TimeVal* val);

#endif