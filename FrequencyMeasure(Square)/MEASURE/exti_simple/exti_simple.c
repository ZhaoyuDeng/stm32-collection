#include "exti_simple.h"
#include "delay.h"
#include "usart.h"

void EXTI_SIMPLE_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
	
	//GPIOE.1 中断线以及中断初始化配置   上升沿触发
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource1);
  EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能 PE1 所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure); 

}

void EXTI1_IRQHandler(void)
{
	
}

