
#include "motor.h"

void Motor_Start(void);
void Motor_Stop(void);
void Motor_On(int micro);

void Motor_Start(void){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
}

void Motor_Stop(void){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
}

void Motor_Flip(void){
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_SET)
		Motor_Stop();
	else
		Motor_Start();
}

void Motor_On(int micro){
	HAL_TIM_OC_Stop(&htim2,TIM_CHANNEL_1);
	htim2.Instance->CCR1 = micro * 1E3 -1;
	HAL_TIM_OC_Start(&htim2,TIM_CHANNEL_1);
}
