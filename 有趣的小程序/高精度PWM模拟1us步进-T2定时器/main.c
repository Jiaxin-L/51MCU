// Header:������Ƴ���
// File Name:
// Author:�����ɣ�QQ1058515967��
// Date:2018��9��12��
//Description������12Tϵ�е�Ƭ������T2��ʱ���ĵ�Ƭ��������Ƴ���
//����������ƾ��ȸߣ�1us������ʱ���Զ����ƶ��ת��
/*------------------------------
Ӳ������ 12Tϵ�е�Ƭ����8051�ںˣ�
					 ӵ��T2��ʱ��
					 12Mʱ�Ӿ���
					 P2_0�������
					 ����Ƕȷ�Χ��0~180 �ߵ�ƽ��Χ0.5ms~2.5ms 20ms����
--------------------------------*/

#include <REGX52.H>

#define T2_PWMout P2_0  //������ƶ�
unsigned int PWMTimes=0;//�ߵ�ƽʱ��
unsigned char angle=0; //���ԽǶ�
void T2_Init();//��ʼ����ʱ��2
void SetMotoangle(float angle);//���ö���Ƕ�
void Delay100ms();		//@12.000MHz
void main()
{
    bit SWdir=0;
    T2_Init();//��ʼ����ʱ��
    while(1)//��ʾ���򣬶�����Ұڶ�
    {
        if(angle>180)SWdir=0;
        else if(angle==0)SWdir=1;

        SetMotoangle(SWdir?angle++:angle--);
        Delay100ms();
    }
}

void T2_Init()
{
    unsigned int time=65536-20000;
    RCAP2L = TL2 = time;            //initial timer2 low byte
    RCAP2H = TH2 = time >> 8;       //initial timer2 high byte
    TR2 = 1;                        //timer2 start running
    ET2 = 1;                        //enable timer2 interrupt
    EA = 1;                         //open global interrupt switch
}
void SetMotoangle(float angle)
{
    //��ֹԽ������˵��
    if(angle > 175) angle = 175;
    if(angle <5) angle = 5;

    PWMTimes=500+angle*2000.0/180;//������ߵ�ƽʱ��


}
/* Timer2 interrupt routine */
void tm2_isr() interrupt 5 using 1
{
    static  bit SW=0;
    unsigned int T2count;
    TF2 = 0;//��־λ����
    SW=~SW;//״̬ȡ��
    T2_PWMout=SW;//�������
    if(SW)//�͵�ƽʱ��
    {
        T2count=0xB1E0+PWMTimes;//0xB1E0��Ϊ20ms�ж���ʱ
        RCAP2L=T2count;
        RCAP2H=T2count>>8;
    }
    else//�ߵ�ƽʱ��
    {
        T2count=0-PWMTimes;
        RCAP2L=T2count;
        RCAP2H=T2count>>8;
    }

}
void Delay100ms()		//@12.000MHz
{
    unsigned char i, j;

    i = 195;
    j = 138;
    do
    {
        while (--j);
    }
    while (--i);
}

