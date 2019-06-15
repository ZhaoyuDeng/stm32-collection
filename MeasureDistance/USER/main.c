#include "stm32f10x.h"
#include "hcsr04.h"
#include "usart.h"
#include "delay.h"

/////////////////////////////////////////////
//³¬Éù²¨´«¸ÐÆ÷²â¾à³ÌÐò
//
//µËÕÑÓî
//2018/8/1
/////////////////////////////////////////////

int main(void)
{	
	float length;
        
	delay_init();
  uart_init(115200);    
  printf("USART Initialized\r\n");
    
  Hcsr04Init();    
  printf("Ultrasound Initialized\r\n");
	while(1){
		length = Hcsr04GetLength();
		if(length != 0)
				printf("Distance:%8.2f  \r\n",length);

	}
}
