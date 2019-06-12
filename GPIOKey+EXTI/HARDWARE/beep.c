#include "beep.h"

void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ENABLE CLOCK for B
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	//only use B8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//Output mode Push-pull
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	//configure PortB
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_8);
	
}
