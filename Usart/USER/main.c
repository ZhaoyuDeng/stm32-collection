#include "stm32f10x.h"

void USART1_Init(void)
{
	//GPIO,USART,NVIC 初始化结构体
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	//使能相应端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	//按手册初始化A9
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;	//固定模式 查表
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	//按手册初始化A10
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//固定模式 查表
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	//按手册初始化串口
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//读取写入模式
	USART_InitStruct.USART_Parity = USART_Parity_No;	//奇偶校验
	USART_InitStruct.USART_StopBits = USART_StopBits_1;	//停止位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;	//字长(选择了无奇偶校验)
	USART_Init(USART1, &USART_InitStruct);	//串口初始化
	
	USART_Cmd(USART1, ENABLE);	//串口控制 使能
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	//串口中断设置 开启接收中断
	
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;	//中断请求 通道
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;//子优先级
	NVIC_Init(&NVIC_InitStruct);	//内嵌向量中断控制器初始化
	
}

void USART1_IRQHandler(void)
{
	u8 rec;
	if(USART_GetITStatus(USART1, USART_IT_RXNE)){
		rec = USART_ReceiveData(USART1);
		USART_SendData(USART1, rec);
	}
}

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	USART1_Init();
	while(1);

}
