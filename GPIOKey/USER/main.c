#include "led.h"
#include "delay.h"
#include "key.h"
#include "beep.h"
#include "sys.h"

int main(void)
{
	vu8 key = 0;	//volatile unsigned char
	delay_init();	//initialize all functions
	LED_Init();
	KEY_Init();
	BEEP_Init();
	
	LED0 = 0;	//light up first
	while(1){
		key = KEY_Scan(1);
		if(key){
			switch(key){
				case WKUP_PRES: BEEP =! BEEP; break;
				case KEY2_PRES: LED0 =! LED0; break;
				case KEY1_PRES: LED1 =! LED1; break;
				case KEY0_PRES: LED0 =! LED0; LED1 =! LED1; break;
			}
		}else delay_ms(10);
	}
}
