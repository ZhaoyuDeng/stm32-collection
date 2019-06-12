#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "key.h"

//u8 tem;

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	//GPIO Init structure definition // CONTAIN: GPIO_Pin  GPIO_Speed  GPIO_Mode
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE, ENABLE); //ENABLE CLOCK for GPIO_A GPIO_E (PORT)
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4; //RELATE to Key 0-2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //SET Input Pull-up MODE
	GPIO_Init(GPIOE, &GPIO_InitStructure);	//Initialize GPIO_E Function
	// Structure can be reused after Init_Function
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	//RELATE to WK_UP
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//SET Input Pull-down MODE
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //Initialize GPIO_A

}

// Contain Piority
u8 KEY_Scan(u8 mode)
{
	static u8 key_up = 1; //mark of pressing
//	tem = 1;
	if(mode){
		key_up = 1;	//long press has effect 1 or not 0
		delay_ms(100);
	}
	if(key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0 || WK_UP == 1)){
		delay_ms(10); // AVOID vibrate
		key_up = 0;	//set be pressed
		if(KEY0 == 0) return KEY0_PRES;
		else if(KEY1 == 0) return KEY1_PRES;
		else if(KEY2 == 0) return KEY2_PRES;
		else if(WK_UP == 1) return WKUP_PRES;
	}else if(KEY0 == 1 && KEY1 == 1 && KEY2 == 1 && WK_UP == 0) key_up = 1;	//key_up=1 not press still assign ???
//	tem = 2;
	return 0;
}
