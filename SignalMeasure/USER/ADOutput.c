#include "ADOutput.h"

//Get AD Output from Port_D

void ADOutput_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
 GPIO_Init(GPIOD, &GPIO_InitStructure);
// GPIO_SetBits(GPIOA,GPIO_Pin_6);
}

void AddRec(u16* checkVolArr, u8 pos)
{
	checkVolArr[pos] = (GPIOD->IDR) & 0x0fff;
}

u16 getAverage(u16* checkVolArr, u8 length)
{
	u16 sum = 0;
	u16 result;
	u16 pos;
	
	for(pos = 10; pos < length - 10; pos++)
	{
		sum += checkVolArr[pos];
	}
	
	result = sum /(length-10* 2);
	return result;
}
