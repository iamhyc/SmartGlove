
#ifndef __JY61_H
#define __JY61_H

#include "libstruct.h"

typedef struct
{
	DIM3_t Acc, Gryo, Angl;
}JY61_Data_t;

extern JY61_Data_t JY61_Data;
extern uint8_t chrTemp[18];

void ShortToChar(short sData, unsigned char cData[]);
short CharToShort(unsigned char cData[]);

void JY61_getAcc(float *,float *,float *);
void JY61_getGryo(float *,float *,float *);
void JY61_getAngle(float *,float *,float *);
void JY61_Print(void);
void JY61_fetchData(void);
#endif
