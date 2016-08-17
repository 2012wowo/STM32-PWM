# include "sys.h"
# include "usart.h"
# include "delay.h"
# include "led.h"
# include "timer.h"
int main (void)
{
	u16 led0pwmval=0;
	u16 dir=1;
	Stm32_Clock_Init(9);
	uart_init(72,9600);
	delay_init(72);
	LED_Init();
	TIM3_PWM_Init(899,0);
	while(1)
	{
		delay_ms(10);
		if(dir)
			led0pwmval++;
		else led0pwmval--;
		if(led0pwmval>300) 
			dir=0;
		if(led0pwmval==0) 
			dir=1;
		LED0_PWM_VAL=led0pwmval;

	}
}
