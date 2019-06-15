#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

								    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能PORTA时钟

	//初始化 WK_UP-->GPIOA.0	  下拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0

}

//按键处理函数，核心板用(仅一个按键)
//mode:0,不支持连续按;1,支持连续按;
//返回按键值
//0，没有任何按键按下
//1，KEY3按下 WK_UP
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&WK_UP==0)
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(WK_UP==0)	return WKUP_PRES;
	}else if(WK_UP==1)	key_up=1; 	    
 	return 0;// 无按键按下
}
