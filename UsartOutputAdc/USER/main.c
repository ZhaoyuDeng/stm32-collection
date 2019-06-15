#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "adc.h"

int main(void)
{
	delay_init();
	uart_init(115200);
	Adc_Init();
	
	while(1){
		printf("%d\r\n",Get_Adc_Average(ADC_Channel_1,50));
		delay_ms(1000);
	}
	
}
