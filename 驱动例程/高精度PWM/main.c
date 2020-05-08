#include <REGX52.H>

#define T2_PWMout P2_0  //PWM�������
unsigned int PWMcycle = 20000-1; //����
unsigned int PWMTimes = 499; //�ߵ�ƽʱ�� 20000us


void T2_Init();
void SetMotoangle (float angle); //�������
void changPWMValue (unsigned int value);//ռ�ձ�����
void SetDutyCycle (float value); //��������
void main()
{
  T2_Init();
  changPWMValue (999);
  while (1)
  {


  }

}
void SetMotoangle (float angle)
{
  //    //��ֹԽ������˵��
  //    if(angle > 175) angle = 175;
  //    if(angle <5) angle = 5;

  PWMTimes = 500 + angle * 2000.0 / 180; //������ߵ�ƽʱ��
}
void SetDutyCycle (float value)
{

  PWMTimes = value * PWMcycle;
}
void changPWMValue (unsigned int value)
{
  value = value > PWMcycle ? PWMcycle : value; //��ֹԽ��
  PWMTimes = value;
}
void T2_Init()
{
  // unsigned int time=65536-20000;
  CP_RL2 = 0;
  TCLK=0;
  RCLK=0;
  C_T2 = 0;
  TF2 = 0;
  RCAP2L = TL2 = PWMTimes;            //initial timer2 low byte
  RCAP2H = TH2 = PWMTimes >> 8;       //initial timer2 high byte
  TR2 = 1;                        //timer2 start running
  ET2 = 1;                        //enable timer2 interrupt
  EA = 1;                         //open global interrupt switch
}
/*****PWM����˵��************/
// 0xB1E0 = 65536-PWM����(20ms)
// PWMTimes Ϊ�ߵ�ƽ����ʱ��
/* Timer2 interrupt routine */
void tm2_isr() interrupt 5 using 1//PWM���ƶ�ʱ������
{
  T2_PWMout = ~T2_PWMout;
  TF2 = 0;//��־λ����

  if (T2_PWMout)
  {
    RCAP2L =0 - (PWMcycle - PWMTimes);
    RCAP2H = 0- (PWMcycle - PWMTimes) >> 8;
  }
  else
  {
    RCAP2L = (0 - PWMTimes);
    RCAP2H = (0 - PWMTimes) >> 8;
  }
}