#ifndef __MOTOR_H
#define __MOTOR_H

#include "gpio.h"
#include "tim.h"

void Motor_Start(void);
void Motor_Stop(void);
void Motor_On(int micro);

#endif
