# include "key.h"
# include "delay.h"
//������ʼ������
void KEY_Init(void)
{
	RCC->APB2ENR|=1<<2;	//��һ����ʹ��ʱ�ӣ�ʹ��PORTAʱ��	�����òο�RCC�Ľṹ���壬STM32�ο��ֲ���APB2ENRʹ�ܼĴ���,��ͬλ��Ӧ��ͬ��ʱ��
	RCC->APB2ENR|=1<<6;// ʹ��PORTEʱ��
	GPIOA->CRL&=0xfffffff0;//PA0�ڵ����λ����Ϊ ģ������ģʽ Px_ODRĬ��Ϊ0��
	GPIOA->CRL|=0x00000008;
	GPIOE->CRL&=0xfff000ff;//PE2~4����Ϊ����
	GPIOE->CRL|=0x00088800;
	GPIOE->ODR|=7<<2;//����ģʽ
}
/*******************************************************************************************
������������������
��  �ã�KEY_Scan(mode)
��  ����u8 mode
����ֵ������ֵ
��  ����
ע  �ͣ�1��KEY0	 2��KEY1 3��KEY2 4��KEY3
		���ȼ�KEY0>KEY1>KEY2>KEY3
*******************************************************************************************/
u8 KEY_Scan(u8 mode)
{
  	static u8 key_up=1;//�����ɿ���־
	if (mode)
		key_up=1;//֧������
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==1))
	{
	  	delay_ms(10);//ȥ����
		key_up=0;
		if(KEY0==0) return 1;
		else if(KEY1==0) return 2;
		else if(KEY2==0) return 3;
		else if(KEY3==0) return 4;
	}
	else if (KEY0==1&&KEY1==1&&KEY2==1&&KEY3==0) key_up=1;
	return 0;  //�ް�������
}
