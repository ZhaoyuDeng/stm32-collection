#ifndef __SquareWave_H
#define __SquareWave_H
#include "sys.h"

#define PA6_UP GPIOA->BSRR = 1<<6
#define PA6_DOWN GPIOA->BSRR = 1<<6+16

void SquareWave_Init(void);
void SquareWave(void);

#endif
