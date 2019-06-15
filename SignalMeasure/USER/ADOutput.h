#ifndef __ADOutput_H
#define __ADOutput_H
#include "sys.h"

void ADOutput_Init(void);
void AddRec(u16* checkVolArr, u8 pos);
u16 getAverage(u16* checkVolArr, u8 length);

#endif
