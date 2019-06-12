#include "stm32f10x.h"
#include "usart.h"
#include "exti.h"
#include "led.h"
#include "scan_print.h"
#include "delay.h"

/////////////////////////////////////
//4*4º¸≈Ã ‰»Î≥Ã–Ú
//
//µÀ’—”Ó Isaac
//2018/7/21
/////////////////////////////////////

int main(void)
{
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	EXTIX_Init();
	uart_init(115200);
	scan_init();
	
	while(1){
		delay_ms(500);
		LED0 = ~LED0;
	}
}
