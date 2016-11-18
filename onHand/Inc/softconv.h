#ifndef _SOFTCONV_H
#define _SOFTCONV_H

#include "stm32f1xx_hal.h"

extern uint32_t ADC_ConvertedValue[5];
extern float ADC_ConvertedValue_AfterMapping[10];
extern float ADC_ConvertedValue_Average[10];
extern uint16_t times;
extern uint8_t ChNumber;

uint32_t * get_ADC(uint8_t ChNumber);
float * mapping_ADC(uint8_t ChNumber);
float * get_ADC_AverageValue(uint16_t times, uint8_t ChNumber);
void ADC_print(void);

#endif

