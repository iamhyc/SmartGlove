
#ifndef __JY61_H
#define __JY61_H

#include "stm32f1xx_hal.h"

extern float a[3],w[3],h[3],Angle[3];
extern uint8_t chrTemp[18];

short CharToShort(unsigned char cData[]);
void ShortToChar(short sData,unsigned char cData[]);

void JY61_getAcc(float *,float *,float *);
void JY61_getGryo(float *,float *,float *);
void JY61_getAngle(float *,float *,float *);
void JY61_Print(void);
void JY61_fetchData(void);
#endif
