#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
#include "adc.h"
#include "timer.h"
#include "key.h"
 
//////////////////////////////////////////////////
//音频信号测试程序
//采样 8kHz	//V-==GND  V+==3.3V
//
//邓昭宇
//2018/8/7
//////////////////////////////////////////////////
#define SAMPLE_SIZE 8000*3	//声音样本数量

u16 voiceSample[SAMPLE_SIZE] = {0};	//声音样本保存变量
extern u8 adcFlag;
	
int main(void)
{	
	u16 i = SAMPLE_SIZE;	//循环变量
	delay_init();
	KEY_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);
	Adc_Init();
	TIM3_Int_Init(100-1, 90-1);	//720kHz的计数频率(Tclk/(psc+1))，arr计数到90为8kHz，Tclk==72MHz
	printf("Initialized\r\n");
	
	while(1){
		while(KEY_Scan(0)){
			printf("Start Sampling:\r\n\r\n");
			for(i=0; i<SAMPLE_SIZE;){	//由TIM3中断改变标志位触发采样
				if(adcFlag){
					voiceSample[i] = Get_Adc(ADC_Channel_1);
					adcFlag = 0;
					i++;
				}
			}
			
			for(i=0; i<SAMPLE_SIZE; i++)	//串口输出数据
				printf("%d\r\n", voiceSample[i]);
		}
	}
}
