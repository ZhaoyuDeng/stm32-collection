#include "timer.h"
#include "usart.h"
#include "qsort.h"


//arr：自动重装值。
//psc：时钟预分频数

//定时器5通道1输入捕获配置

TIM_ICInitTypeDef  TIM5_ICInitStructure;

void TIM5_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//使能TIM5时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIOA时钟
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;  //PA0 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 输入  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);						 //PA0 下拉
	
	//初始化定时器5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	//初始化TIM5输入捕获参数
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
  TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM5中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
	
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	
 	TIM_Cmd(TIM5,ENABLE ); 	//使能定时器5
   
}

u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM5CH1_CAPTURE_VAL;	//输入捕获值
u8	MEASURE_MODE = 0;	//测量模式   0:选择周期测量  1:选择高电平测量

//定时器5中断服务程序	 
void TIM5_IRQHandler(void)
{ 

 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM5CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM5CH1_CAPTURE_VAL=0XFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
				if(MEASURE_MODE)//--
					TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH1_CAPTURE_STA=0;			//清空
				TIM5CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM5,0);
				TIM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
				if(MEASURE_MODE)//--
					TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获---------
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
 
}

//获得输入捕获测得高电平持续时间
u32 TIM5_GetMeasureTime(u8 mode)
{
	u32 timeLast = 0;
	
	if(mode == MODE_HLEVEL)
		MEASURE_MODE = MODE_HLEVEL;
	else if(mode == MODE_PERIOD)
		MEASURE_MODE = MODE_PERIOD;
	else
		return 0;
	
	TIM_SetCompare2(TIM3,TIM_GetCapture2(TIM3)+1);

	if(TIM_GetCapture2(TIM3)==300)TIM_SetCompare2(TIM3,0);	
		 		 
 	if(TIM5CH1_CAPTURE_STA&0X80)	//成功捕获到了一次上升沿
	{
		timeLast = (TIM5CH1_CAPTURE_STA & 0X3F) * 0x10000 + TIM5CH1_CAPTURE_VAL;	//总的高电平时间
		TIM5CH1_CAPTURE_STA=0;	//开启下一次捕获
	}
	return timeLast;
}

#define SAMPLE 5

//测量一定次数的数值，获得其中值
u32 TIM5_GetExactValue(u8 mode)
{
	u8 order = 0;
	u32 temp = 0;
	u64 result = 0;
	u32 sample[SAMPLE] = {0};
	for(order = 0; order < SAMPLE;)	//获得一系列采样数据
	{
		if((temp = TIM5_GetMeasureTime(mode)) != 0)
		{
			sample[order] = temp;
//			printf("%d ", temp);
			order++;
		}
	}
	SelectionSort(sample, SAMPLE);	//排序函数
	for(order = (SAMPLE/2)-1; order <= (SAMPLE/2)+1; order++)	//取中间三个数据取平均值
	{
		result += sample[order];
//		printf("%d ", sample[order]);
	}
	result = result / 3 + 3;	//可加3微秒为软件补偿
	
	return (u32)result;
}

