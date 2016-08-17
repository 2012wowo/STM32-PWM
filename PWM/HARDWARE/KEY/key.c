# include "key.h"
# include "delay.h"
//按键初始化程序
void KEY_Init(void)
{
	RCC->APB2ENR|=1<<2;	//第一步，使能时钟；使能PORTA时钟	，配置参考RCC的结构定义，STM32参考手册中APB2ENR使能寄存器,不同位对应不同的时钟
	RCC->APB2ENR|=1<<6;// 使能PORTE时钟
	GPIOA->CRL&=0xfffffff0;//PA0口的最低位设置为 模拟输入模式 Px_ODR默认为0；
	GPIOA->CRL|=0x00000008;
	GPIOE->CRL&=0xfff000ff;//PE2~4设置为输入
	GPIOE->CRL|=0x00088800;
	GPIOE->ODR|=7<<2;//上拉模式
}
/*******************************************************************************************
函数名：按键处理函数
调  用：KEY_Scan(mode)
参  数：u8 mode
返回值：按键值
结  果：
注  释：1，KEY0	 2，KEY1 3，KEY2 4，KEY3
		优先级KEY0>KEY1>KEY2>KEY3
*******************************************************************************************/
u8 KEY_Scan(u8 mode)
{
  	static u8 key_up=1;//按键松开标志
	if (mode)
		key_up=1;//支持连按
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==1))
	{
	  	delay_ms(10);//去抖动
		key_up=0;
		if(KEY0==0) return 1;
		else if(KEY1==0) return 2;
		else if(KEY2==0) return 3;
		else if(KEY3==0) return 4;
	}
	else if (KEY0==1&&KEY1==1&&KEY2==1&&KEY3==0) key_up=1;
	return 0;  //无按键按下
}
