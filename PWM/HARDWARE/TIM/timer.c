# include "timer.h"
# include "led.h"
# include "usart.h"
//定时器中断服务程序
void TIM3_IRQHandler(void)
{
	if(TIM3->SR&0x0001) 
		LED1=!LED1;
	TIM3->SR&=~(1<<0);//~：位运算 取反
}
/*	**********************************************
	通用定时器3中断初始化
	时钟选择为APB1的2倍，而APB1为36MHz
	arr：自动重装值
	psc：时钟预分频数
**************************************************/
void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;	//TIM3时钟使能
	TIM3->ARR=arr;		//设定计数器重装值
	TIM3->PSC=psc;
	TIM3->DIER|=1<<0;  //TIM3->DIER最低位为允许更新中断
	TIM3->CR1|=0x01;	// 使能定时器3
	MY_NVIC_Init(1,3,TIM3_IRQChannel,2);//抢占1，子优先级3，组2
}
/*	**********************************************
	通用定时器3 PWM初始化
	PWM初始化
	arr：自动重装值
	psc：时钟预分频数
**************************************************/
void TIM3_PWM_Init(u16 arr,u16 psc)
{
	//1 开启TIM3时钟  配置PB5为复用输出
	RCC->APB1ENR|=1<<1;		//TIM3时钟使能
	RCC->APB2ENR|=1<<3;		//使能PORTB时钟
	GPIOB->CRL&=0xff0fffff;	

	//2 设置TIM3_CH2重映射到PB5
	GPIOB->CRL|=0x00b00000;	//复用功能
	RCC->APB2ENR|=1<<0;		//开启辅助时钟
	AFIO->MAPR&=0xfffff3ff;	//清除MAPR的[11:10]
	AFIO->MAPR|=1<<11;		//部分重映像，TIM3_CH2->PB5

	//3 设置TIM3的ARR和PSC
	TIM3->ARR=arr;
	TIM3->PSC=psc;

	//4 设置TIM3_CH2的PWM模式
	TIM3->CCMR1|=7<<12; 	//CH2 PWM2模式
	TIM3->CCMR1|=1<<4;		//CH2 预装载使能
	//5 使能TIM3_CH2输出 使能TIM3
	TIM3->CCER|=1<<4;  	//OC2输出使能
	TIM3->CR1=0x0080;		//ARPE 使能
	TIM3->CR1|=0x01;			//使能定时器
	//6 修改TIM3_CCR2来控制占空比
}
