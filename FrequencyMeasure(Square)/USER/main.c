#include "stm32f10x.h"
#include "timer.h"
#include "delay.h"
#include "usart.h"


///////////////////////////////////////
//方波的频率、占空比测量程序（预计编写几种方法）
//
//		邓昭宇 2018/7/25
///////////////////////////////////////

extern u8	MEASURE_MODE;		//0:测量模式   选择高电平测量  1:选择周期测量

int main(void)
{	
	u32 getPeriod = 0;
	u32 getHLevel = 0;
	
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
	
 	TIM5_Cap_Init(0XFFFF,72-1);	//以1Mhz的频率计数 oxFFFF溢出
	
	while(1)
	{
//		printf("OK\r\n");
		delay_ms(1000);
		if((getHLevel = TIM5_GetExactValue(MODE_HLEVEL)) != 0)
			printf("H-Level: %d us\r\n", getHLevel);
		if((getPeriod = TIM5_GetExactValue(MODE_PERIOD)) != 0)
			printf("Perior: %d us\r\n", getPeriod);
		printf("Duty_Ratio:%.2f%%\r\n\r\n", (float)((double)getHLevel/((double)getPeriod/100)));
	}
	
}
