#include "stm32f10x.h"
#include "stdio.h"

#include "SquareWave.h"
#include "ADOutput.h"

#define Length 100

int main(void)
{
	u16 checkVolArr[Length] = {0};
	u16 average;
	u16 pos;
	u8 decrease = 100;
	
	delay_init();
	uart_init(115200);
	SquareWave_Init();
	ADOutput_Init();
	

	while(decrease--)	
	{
		for(pos = 0; pos < Length; pos++)
		{
			SquareWave();
			AddRec(checkVolArr, pos);
		}
		
		average = getAverage(checkVolArr, Length);
//		printf("Average: %l", average);
	}
	return 0;
}
