#include <REGX52.H>
#include <stdio.h>
#include "LCD1602.h"
#include "ADCDevice.h"
#include "Time.h"
#include "keyBoard.h"
unsigned char *Mode = "MODE:";
unsigned char *Freq = "Freq:";
unsigned char *ModeStr[]= {"Sin","Tri","Squ"};
typedef enum {ZhengXian,SanJiao,FangBo} SingleMode;

KeyStruct keyVal;
TimeVal   timeCycle[3];
  char str[20];
unsigned int ADCMaxVal;
unsigned int FreqVal[2];
SingleMode checkMode();
void CalcFreq();
void CalcFreqSine();
void CaleFreqSqu();
void main()
{
  SingleMode SGmode;

  InitLcd1602();
  ADCInit();
  LcdShowStr(0, 0, Mode);
  LcdShowStr(0, 1, Freq);
  LcdShowStr(5,0,ModeStr[SGmode]);

  while (1)
  {
    if(key_scan(&keyVal)==KeyFallEdge)
    {
      SGmode =(SGmode+1)%3;
      LcdShowStr(5,0,ModeStr[SGmode]);
    }
    switch(SGmode)
    {
    case ZhengXian:
      CalcFreqSine();

      if(timeCycle[2].ms>100)
      {
        sprintf(str," %.3f",1000.0/timeCycle[2].ms);
      }
      else
      {
        sprintf(str," %.3f",1000.0/(timeCycle[2].ms+timeCycle[2].us*0.001));
      }

      LcdShowStr(5,1,str);
      sprintf(str,"%.3f",(ADCMaxVal*5.0/0xFF));
      LcdShowStr(9,0,str);
      break;

    case SanJiao:
			CalcFreqSine();
      if(timeCycle[2].ms>100)
      {
        sprintf(str," %.3f",1000.0/timeCycle[2].ms);
      }
      else
      {
        sprintf(str," %.3f",1000.0/(timeCycle[2].ms+timeCycle[2].us*0.001));
      }

      LcdShowStr(5,1,str);
      sprintf(str,"%.3f",(ADCMaxVal*5.0/0xFF));
      LcdShowStr(9,0,str);
      break;

    case FangBo:
      CaleFreqSqu();

      if(timeCycle[2].ms>100)
      {
        sprintf(str," %.3f",1000.0/timeCycle[2].ms);
      }
      else
      {
        sprintf(str," %.3f",1000.0/(timeCycle[2].ms+timeCycle[2].us*0.001));
      }

      LcdShowStr(5,1,str);
      sprintf(str,"%.3f",timeCycle[1].ms*1.0/timeCycle[2].ms);
      LcdShowStr(9,0,str);
      break;

    default:
      break;
    }
  }
}
//��������
void CaleFreqSqu()
{
  unsigned char ADCMax,ADCMin,Val,AveVal;
  TimeInit();
  T0_RUN(1);//����ʱ��
  ADCMin=ADCMax=	ReadAdc();

  //��÷����������С��Χ
  while(GetTime()<500)
  {
    Val=ReadAdc();

    if(Val>ADCMax)ADCMax=Val;
    else if(Val<ADCMin)ADCMin=Val;
  }

  AveVal=(ADCMax-ADCMin)/2+ADCMin;
    TimeInit();
  if(Val>AveVal)
  {
    //�ߵ�ƽ����
    while(ReadAdc()>AveVal);

    T0_RUN(1);//����ʱ��

    while(ReadAdc()<AveVal)
    {
      if(GetTime()>1000)
      {
        T0_RUN(0);
        return;
      }
    }

    EndTime(timeCycle);
    T0_RUN(1);//����ʱ��

    while(ReadAdc()>AveVal)
    {
      if(GetTime()>1000)
      {
        T0_RUN(0);
        return;
      }
    }

    EndTime(timeCycle+2);
    timeCycle[1].ms=timeCycle[2].ms-timeCycle[0].ms;
  }
  else
  {
    //�͵�ƽ����
    while(ReadAdc()<AveVal);
    T0_RUN(1);//����ʱ��

    while(ReadAdc()>AveVal)
    {
      if(GetTime()>1000)
      {
        T0_RUN(0);
        return;
      }
    }

    EndTime(timeCycle+1);
    T0_RUN(1);//����ʱ��

    while(ReadAdc()<AveVal)
    {
      if(GetTime()>1000)
      {
        T0_RUN(0);
        return;
      }
    }

    EndTime(timeCycle+2);
    timeCycle[0].ms=timeCycle[2].ms-timeCycle[1].ms;
  }
}
//�������Ҳ�Ƶ��
void CalcFreqSine()
{
  TimeInit();
  ADCMaxVal=GetMaxADCVal();
  T0_RUN(1);//����ʱ��
  ADCMaxVal=GetMaxADCVal();
  EndTime(timeCycle+2);
}
/*
void CalcFreq()
{
  InPutSign=1;
  TimeInit();
  T0_RUN(1);//����ʱ��

  if(InPutSign==0)
  {
    //�ȸߵ�ƽ��Ե
    while(InPutSign==0)
    {
      if(GetTime()>2000)
      {
        T0_RUN(0);
        return;
      }
    }

    TimeInit();
    T0_RUN(1);

//ͳ�Ƹߵ�ƽʱ��
    while(InPutSign==1)
    {
      if(GetTime()>2000)
      {
        T0_RUN(0);
        return;
      }
    }

    EndTime(timeCycle+1);
    //ͳ������ʱ��
    T0_RUN(1);

    while(InPutSign==0)
    {
      if(GetTime()>2000)
      {
        T0_RUN(0);
        return;
      }
    }

    EndTime(timeCycle+2);
    timeCycle[0].ms=timeCycle[2].ms-timeCycle[1].ms;
  }
  else
  {
    //�ȹ��ߵ�ƽ Ѱ�ҵ͵�ƽ
    while(InPutSign==1)
    {
      if(GetTime()>2000)
      {
        T0_RUN(0);
        return;
      }
    }

//��ʱ�͵�ƽʱ��
    TimeInit();
    T0_RUN(1);

    while(InPutSign==0)
    {
      if(GetTime()>2000)
      {
        T0_RUN(0);
        return;
      }
    }

    EndTime(timeCycle);
    //������ʱ�ߵ�ƽʱ��
    T0_RUN(1);

    while(InPutSign==1)
    {
      if(GetTime()>2000)
      {
        T0_RUN(0);
        return;
      }
    }

    EndTime(timeCycle+2);
    timeCycle[1].ms=timeCycle[2].ms-timeCycle[0].ms;
  }
}*/