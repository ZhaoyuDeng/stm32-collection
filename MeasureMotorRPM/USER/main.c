#include "stm32f10x.h"
#include "timer.h"
#include "delay.h"
#include "usart.h"


///////////////////////////////////////
//动向轮转速测试程序	
//使用PA0
//
//邓昭宇 
//2018/8/2
///////////////////////////////////////

extern u8	MEASURE_MODE;		//0:测量模式   选择高电平测量  1:选择周期测量

int main(void)
{	
	u32 getPeriod = 0;
	u32 roundPerMin = 0;
	
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
	
 	TIM5_Cap_Init(0XFFFF,72-1);	//以1Mhz的频率计数 oxFFFF溢出	//提升频率以得到更高精度?
	
	while(1)
	{
//		printf("OK\r\n");
//		delay_ms(1000);

		if((getPeriod = TIM5_GetExactValue(MODE_PERIOD)) != 0){
			roundPerMin = 60000000 / (getPeriod * 13);
			printf("Period: %d us      RoundPerMinute: %d RPM  \r\n", getPeriod, roundPerMin);
		}	
	}
}
