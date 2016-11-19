
#include "motor.h"
#include "main.h"

void Motor_Start(void){
	HAL_GPIO_WritePin(GPIOB, MotorBit_Pin, GPIO_PIN_SET);
}

void Motor_Stop(void){
	HAL_GPIO_WritePin(GPIOB, MotorBit_Pin, GPIO_PIN_RESET);
}

void Motor_Flip(void){
	if(HAL_GPIO_ReadPin(GPIOB, MotorBit_Pin) == GPIO_PIN_SET)
		Motor_Stop();
	else
		Motor_Start();
}

void Motor_Hold(int micro){
	Motor_Stop();
	Motor_Start();
	HAL_Delay(micro);
	Motor_Stop();
}

void Motor_On(int micro){
	//htim2.Instance->CCR1 = micro * 1E3 -1;
}
