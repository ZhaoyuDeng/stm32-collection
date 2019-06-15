#include "SquareWave.h"

//Output T=20us Square-wave from Port_A Pin_6

void SquareWave_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
 GPIO_Init(GPIOA, &GPIO_InitStructure);
// GPIO_SetBits(GPIOA,GPIO_Pin_6);

}

void SquareWave(void)
{
	u8 loop = 0xff;
	
  while(loop--)
	{
		delay_us(10);
		PA6_UP;
		delay_us(10);
		PA6_DOWN;
	}
}