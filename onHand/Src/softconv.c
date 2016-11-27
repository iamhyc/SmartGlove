
#include "softconv.h"
#include "adc.h"
#include "usart.h"
#include "gpio.h"

const uint16_t ADC_MAX = 3000;
const uint16_t ADC_MIN = 1000;

uint32_t ADC_pData[5];
uint16_t ADC_RawData[10];
float ADC_realData[10];
static float tmp;

float ADC_mappingData(uint16_t);

void ADC_Init()
{
	HAL_ADCEx_Calibration_Start(&hadc1);
	HAL_ADCEx_Calibration_Start(&hadc2);
}

void ADC_fetchData(){
	HAL_ADC_Start(&hadc2);//  Activate the ADC peripheral (slave) and start conversions
	HAL_ADCEx_MultiModeStart_DMA(&hadc1, ADC_pData, 5);//Activate the ADC peripheral (master) and start conversions
}

void ADC_conveyData()
{
	for(int i = 0; i < 5; i++)
	{
		ADC_RawData[i] = ADC_pData[i] & 0xFFFF;
		ADC_RawData[i+1] = (ADC_pData[i] >> 16) & 0xFFFF;
	}
	
	#ifdef ADC_FILTTERING
		for(int i = 0; i < 10; i++)
		{
			tmp = ADC_mappingData(ADC_RawData[i]);
			ADC_realData[i] = (1-ADC_FILTER_ALPHA) * ADC_realData[i] \
													+ ADC_FILTER_ALPHA * tmp;
		}
	#else
		for(int i = 0; i < 10; i++)
		{
			ADC_realData[i] = ADC_mappingData(ADC_RawData[i]);
		}
	#endif
}

float ADC_mappingData(uint16_t data)
{
	float tmp = (float)( (data - ADC_MIN) / (ADC_MAX - ADC_MIN) * 90);
	return tmp;//(tmp>90?90:tmp);
}

float ADC_getChannel(int channel)
{
	return ADC_realData[channel];
}

float *ADC_getAll(void)
{
	return ADC_realData;
}

void ADC_print(){
	unsigned char str[200];
	sprintf((char *)str, "%d\t%d\t%d\t%d\t%d\n%d\t%d\t%d\t%d\t%d\n", \
					ADC_RawData[0], ADC_RawData[1], ADC_RawData[2], ADC_RawData[3], ADC_RawData[4], \
					ADC_RawData[5], ADC_RawData[6], ADC_RawData[7], ADC_RawData[8], ADC_RawData[9]);
	/*for(int i = 0; i < 10; i++)
	{
		sprintf((char *)str, "%sChannel %d:%.3f\t", (char *)str, (i+1), ADC_realData[i]);
	}*/
	HAL_UART_Transmit(&huart1, str, strlen((char *)str), 500);
}
