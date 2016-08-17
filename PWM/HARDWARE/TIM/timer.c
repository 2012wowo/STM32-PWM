# include "timer.h"
# include "led.h"
# include "usart.h"
//��ʱ���жϷ������
void TIM3_IRQHandler(void)
{
	if(TIM3->SR&0x0001) 
		LED1=!LED1;
	TIM3->SR&=~(1<<0);//~��λ���� ȡ��
}
/*	**********************************************
	ͨ�ö�ʱ��3�жϳ�ʼ��
	ʱ��ѡ��ΪAPB1��2������APB1Ϊ36MHz
	arr���Զ���װֵ
	psc��ʱ��Ԥ��Ƶ��
**************************************************/
void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;	//TIM3ʱ��ʹ��
	TIM3->ARR=arr;		//�趨��������װֵ
	TIM3->PSC=psc;
	TIM3->DIER|=1<<0;  //TIM3->DIER���λΪ��������ж�
	TIM3->CR1|=0x01;	// ʹ�ܶ�ʱ��3
	MY_NVIC_Init(1,3,TIM3_IRQChannel,2);//��ռ1�������ȼ�3����2
}
/*	**********************************************
	ͨ�ö�ʱ��3 PWM��ʼ��
	PWM��ʼ��
	arr���Զ���װֵ
	psc��ʱ��Ԥ��Ƶ��
**************************************************/
void TIM3_PWM_Init(u16 arr,u16 psc)
{
	//1 ����TIM3ʱ��  ����PB5Ϊ�������
	RCC->APB1ENR|=1<<1;		//TIM3ʱ��ʹ��
	RCC->APB2ENR|=1<<3;		//ʹ��PORTBʱ��
	GPIOB->CRL&=0xff0fffff;	

	//2 ����TIM3_CH2��ӳ�䵽PB5
	GPIOB->CRL|=0x00b00000;	//���ù���
	RCC->APB2ENR|=1<<0;		//��������ʱ��
	AFIO->MAPR&=0xfffff3ff;	//���MAPR��[11:10]
	AFIO->MAPR|=1<<11;		//������ӳ��TIM3_CH2->PB5

	//3 ����TIM3��ARR��PSC
	TIM3->ARR=arr;
	TIM3->PSC=psc;

	//4 ����TIM3_CH2��PWMģʽ
	TIM3->CCMR1|=7<<12; 	//CH2 PWM2ģʽ
	TIM3->CCMR1|=1<<4;		//CH2 Ԥװ��ʹ��
	//5 ʹ��TIM3_CH2��� ʹ��TIM3
	TIM3->CCER|=1<<4;  	//OC2���ʹ��
	TIM3->CR1=0x0080;		//ARPE ʹ��
	TIM3->CR1|=0x01;			//ʹ�ܶ�ʱ��
	//6 �޸�TIM3_CCR2������ռ�ձ�
}
