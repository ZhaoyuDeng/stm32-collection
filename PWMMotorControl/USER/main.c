#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "pwm.h"

////////////////////////////////////////
//PWM电机驱动程序
//使电机往复运作
//
//邓昭宇
//2018/7/31
////////////////////////////////////////

int main(void)
{	
	u8 i = 0;
	u16 pwmval=0;
	u8 dir=1, conv=1;
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
	TIM3_PWM_Init(7199,0);	//不分频。PWM频率=72000000/7200=10Khz
	
	pwmval = 3600;
	while(1)
	{
 		delay_ms(10);	 
		if(dir)pwmval += 10;
		else pwmval -= 10;

 		if(pwmval>3600)dir=0;
		if(pwmval==0){dir=1; conv = !conv;}
		if(conv == 0)
			TIM_SetCompare1(TIM3,pwmval);
		if(conv != 0)
			TIM_SetCompare2(TIM3,pwmval);
		
		
//		TIM_SetCompare1(TIM3,0);
//		TIM_SetCompare2(TIM3,7100);
//		for(i=0; i<5; i++)
//			delay_ms(1000);
//		
//		TIM_SetCompare2(TIM3,0);
//		TIM_SetCompare1(TIM3,7100);
//		for(i=0; i<10; i++)
//			delay_ms(1000);
//		
//		TIM_SetCompare1(TIM3,0);
//		TIM_SetCompare2(TIM3,0);
//		for(i=0; i<5; i++)
//			delay_ms(1000);
	}	 
}
