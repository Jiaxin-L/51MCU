#include <REGX52.H>
#include "Time.h"

void main()
{
    //�������С��ʱ
    P1_1=0;
    Delay10us();//�����ʱ
    P1_1=!P1_1;
    Delay10us();
    P1_1=!P1_1;

    //���Զ�ʱ��С��ʱ
    P1_1=0;
    //��������˳��Ҳ�ܽ������
    T1Delayus(100);
	T1_RUN(1);//��ʱ����ʱ
    P1_1=1;
    while(!TF1);
    P1_1=!P1_1;
	T1_RUN(0);
    T1_Flag(0);


    while(1)
    {
    }
}