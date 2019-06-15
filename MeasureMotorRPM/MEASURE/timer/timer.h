#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

typedef unsigned long long u64;

#define MODE_PERIOD 0
#define MODE_HLEVEL 1

void TIM3_Int_Init(u16 arr,u16 psc);
void TIM5_Cap_Init(u16 arr,u16 psc);
u32 TIM5_GetMeasureTime(u8 mode);
u32 TIM5_GetExactValue(u8 mode);
#endif
