#include "exti.h"
#include "usart.h"
#include "scan_print.h"
#include "delay.h"

u8 col = 0;	//从中断读取的按键列序数

//所需GPIO初始化函数
void GPIOX_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF, ENABLE);//使能PORT E,F 时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置成推挽输出		//原有输入识别要求，为开漏输出，但后来仅需识别，设推挽输出
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE 0,2,4,6

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置成下拉输入  
	GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIOF 0,2,4,6

}


//外部中断服务程序
void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

  GPIOX_Init();	//GPIO初始化函数

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

  //GPIOF.0 中断线以及中断初始化配置   上升沿触发
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource0);
  EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  //GPIOF.2	  中断线以及中断初始化配置  上升沿触发
 	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource2);
 	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
 	EXTI_Init(&EXTI_InitStructure);

	//GPIOF.4	  中断线以及中断初始化配置  上升沿触发
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource4);
  EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  EXTI_Init(&EXTI_InitStructure);

  //GPIOF.6	  中断线以及中断初始化配置  上升沿触发
 	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource6); 
  EXTI_InitStructure.EXTI_Line=EXTI_Line6;
  EXTI_Init(&EXTI_InitStructure);



  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能GPIOF.0所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure); 

  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能GPIOF.2所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能GPIOF.4所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能GPIOF.6所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
}

#define DELAY_SHAKE 200
//外部中断服务程序 
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0)){
		delay_ms(DELAY_SHAKE);
		if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_0)){	//判断方式似乎欠妥
			col = 0;
			scan_print(col);
			scan_init();
			EXTI_ClearITPendingBit(EXTI_Line0);
		}else{
			EXTI_ClearITPendingBit(EXTI_Line0);
		}
	}
}

void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2)){
		delay_ms(DELAY_SHAKE);
		if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_2)){
			col = 1;
			scan_print(col);
			scan_init();
			EXTI_ClearITPendingBit(EXTI_Line2);
		}else{
			EXTI_ClearITPendingBit(EXTI_Line2);
		}
	}
}

void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4)){
		delay_ms(DELAY_SHAKE);
		if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_4)){
			col = 2;
			scan_print(col);
			scan_init();
			EXTI_ClearITPendingBit(EXTI_Line4);
		}else{
			EXTI_ClearITPendingBit(EXTI_Line4);
		}
	}
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line6)){
		delay_ms(DELAY_SHAKE);
		if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_6)){
			col = 3;
			scan_print(col);
			scan_init();
			EXTI_ClearITPendingBit(EXTI_Line6);
		}else{
			EXTI_ClearITPendingBit(EXTI_Line6);
		}
	}
}
