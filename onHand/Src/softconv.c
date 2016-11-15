#include "adc.h"

#include "gpio.h"

void get_ADC(uint8_t ChNumber, uint32_t ADC_ConvertedValue[], uint16_t ADC_ConvertedValue_AfterMaping[]){

//HAL_ADCEx_MultiModeConfigChannel(&hadc1, hadc2);  //Optionally,for devices with several ADC instances
  uint8_t slope = 0;
	uint8_t offset =0;
	uint8_t i = 0;
	
	HAL_ADC_Start(&hadc2);//  Activate the ADC peripheral (slave) and start conversions
	HAL_ADCEx_MultiModeStart_DMA(&hadc1,ADC_ConvertedValue,ChNumber);//Activate the ADC peripheral (master) and start conversions
	
	for(i,i<5,i++){
		ADC_ConvertedValue_AfterMaping[2*i] = slope*(ADC_ConvertedValue[i]>>16)+offset;
		ADC_ConvertedValue_AfterMaping[2*i+1] = slope*((uint16_t)(ADC_ConvertedValue[i]&0xffff))+offset;
	}

	
	

	//Conversion results are automatically transferred by DMA into destination variable address.	
	//HAL_ADCEx_MultiModeStop_DMA() //Stop conversion and disable the ADC peripheral (master)
	//HAL_ADC_Stop_IT()//Stop conversion and disable the ADC peripheral (master)
}