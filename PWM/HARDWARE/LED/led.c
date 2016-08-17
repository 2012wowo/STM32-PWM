# include "led.h"
//初始化链接LED的IO口为输出口，并使能这两个口的时钟
//LED I/O初始化
void LED_Init(void)
{
	RCC->APB2ENR|=1<<3;			//第一步，使能时钟；使能PORTB时钟	，配置参考RCC的结构定义，STM32参考手册中APB2ENR使能寄存器
	GPIOB->CRL &= 0xf00fffff;		//32位访问寄存器，参考STM32参考手册中CRL结构，用哪一位IO口，把CRL中控制这个IO口的位清零。
	GPIOB->CRL |= 0x03300000; 		//pB.5 推完输出。参考STM32参考手册中CRL配置IO口的内容，
    GPIOB->ODR |=3 << 5	;		    //PB.5输出高。参考STM32参考手册中ODR数据结构。
}
