#include "gpio.h"

extern int Motor_Count = -1;

void Motor_Start(void);
void Motor_Stop(void);
void Motor_On(int micro);

void Motor_Start(void){
	GPIO_PB2_Init();
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_BIT_SET);
	
}

void Motor_Stop(void){
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_BIT_RESET);
}

void Motor_Flip(void){
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2)==GPIO_BIT_SET)
		Motor_Stop();
	else
		Motor_Start();
}

void Motor_On(int micro){
	Motor_Count = 0;
	HAL_TIM_Base_Start(htim2);
	Motor_Start();
	
	while(Motor_Count<micro){
	}
	
	Motor_Stop();
}

