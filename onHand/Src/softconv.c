#include "adc.h"
#include "softconv.h"
#include "gpio.h"

uint32_t ADC_ConvertedValue[5];
float ADC_ConvertedValue_AfterMapping[10];
float ADC_ConvertedValue_Average[10];


uint32_t *get_ADC(uint8_t ChNumber){

//HAL_ADCEx_MultiModeConfigChannel(&hadc1, hadc2);  //Optionally,for devices with several ADC instances
 
	
	HAL_ADC_Start(&hadc2);//  Activate the ADC peripheral (slave) and start conversions
	HAL_ADCEx_MultiModeStart_DMA(&hadc1,ADC_ConvertedValue,ChNumber);//Activate the ADC peripheral (master) and start conversions
	
	return ADC_ConvertedValue;


	//Conversion results are automatically transferred by DMA into destination variable address.	
	//HAL_ADCEx_MultiModeStop_DMA() //Stop conversion and disable the ADC peripheral (master)
	//HAL_ADC_Stop_IT()//Stop conversion and disable the ADC peripheral (master)
}

float *mapping_ADC(float maxvalue, float minvalue,uint8_t ChNumber){
	  get_ADC(ChNumber);
		float slope = 90/(maxvalue-minvalue);
		float offset =90*minvalue/(minvalue-maxvalue);
		for(int i;i<5;i++){
			ADC_ConvertedValue_AfterMapping[2*i] = slope*(ADC_ConvertedValue[i]>>16)+offset;
			ADC_ConvertedValue_AfterMapping[2*i+1] = slope*((uint16_t)(ADC_ConvertedValue[i]&0xffff))+offset;
		}

		return ADC_ConvertedValue_AfterMapping;
}



float *get_ADC_AverageValue(uint16_t times,uint16_t maxvalue, uint16_t minvalue, uint8_t ChNumber){
		uint8_t weight = 0;
		mapping_ADC(maxvalue,minvalue,ChNumber);
	  *ADC_ConvertedValue_Average = *ADC_ConvertedValue_AfterMapping;
		for(int i;i<times-1;i++){
				mapping_ADC(maxvalue,minvalue,ChNumber);
				for(int m;m<10;m++)
					ADC_ConvertedValue_Average[m]=weight*ADC_ConvertedValue_Average[i]+(1-weight)*ADC_ConvertedValue_AfterMapping[i];			
		}	
		return ADC_ConvertedValue_Average;
}



void ADC_print(){
	for(int i;i<10;i++)
		printf("Channel,%f, %f",i+1,ADC_ConvertedValue_Average[i]);
}
