#include <REGX52.H>
#include <stdio.h>
#include "Time.h"//��ʱ�������ļ�
#include "MulDigitalTube.h" //�������ʾ����
sbit InPutSign=P3^2;//�ź���������

TimeVal   timeCycle;//������ͳ��ʱ��
void CalcFreq();

void main()
{
  MulDigInit();
  T1init();

  while (1)
  {
    CalcFreq();

    if(timeCycle.ms>100)
    {
      float var=1000.0/timeCycle.ms;
      DigSetFData((unsigned int)var);
    }
    else
    {
      float var=timeCycle.ms+timeCycle.us*0.001;
      var=1000.0/var;
      DigSetFData((unsigned int)var);
    }
  }
}


void CalcFreq()
{
  InPutSign=1;
  T0Init();

  while(InPutSign==0);

  T0_RUN(1);//����ʱ��

  while(InPutSign==1)
  {
    if(GetTime()>2000)
    {
      EndTime(&timeCycle);
      return;
    }
  }

  while(InPutSign==1)
  {
    if(GetTime()>2000)
    {
      EndTime(&timeCycle);
      return;
    }
  }

  EndTime(&timeCycle);
}