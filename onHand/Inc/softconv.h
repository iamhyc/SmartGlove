#ifndef _SOFTCONV_H
#define _SOFTCONV_H

#include "stm32f1xx_hal.h"

extern uint16_t ADC_RawData[10];
extern float ADC_realData[10];

#define ADC_FILTTERING 1
#define ADC_FILTER_ALPHA 0.5

void ADC_Init(void);
void ADC_fetchData(void);
void ADC_conveyData(void);
float ADC_getChannel(int channel);
float *ADC_getAll(void);

void ADC_print(void);

#endif

