#include <STC15F2K60S2.H>

void GPIOInit();
void main()
{
	GPIOInit();
	//XXXInit();
	while(1)
	{
	
	}
	
}	
void GPIOInit()
{
	//P1��8��LED �ߵ�ƽ���� ���� �����������
	P1M1 =0x00;
	P1M0 =0xff;
	//P2��8��LED �͵�ƽ���� ��© ������������
	P2M1 =0xff;
	P2M0 =0xff;
	//P3��8��LED 4�ߵ�ƽ���� 4�͵�ƽ 
	P3M1 =0x0f;
	P3M0 =0xff;
}