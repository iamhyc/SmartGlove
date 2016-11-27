/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
//include for 'malloc' and 'free' function;used for allocate address memory for pointer
#include <stdlib.h>
//include for math function;like 'ceil', 'abs', etc.
#include <math.h>
/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define Thumb_upper_Pin GPIO_PIN_0
#define Thumb_upper_GPIO_Port GPIOA
#define Index_upper_Pin GPIO_PIN_1
#define Index_upper_GPIO_Port GPIOA
#define Middle_upper_Pin GPIO_PIN_2
#define Middle_upper_GPIO_Port GPIOA
#define Ring_Upper_Pin GPIO_PIN_3
#define Ring_Upper_GPIO_Port GPIOA
#define Little_Upper_Pin GPIO_PIN_4
#define Little_Upper_GPIO_Port GPIOA
#define Thumb_Lower_Pin GPIO_PIN_5
#define Thumb_Lower_GPIO_Port GPIOA
#define Index_Lower_Pin GPIO_PIN_6
#define Index_Lower_GPIO_Port GPIOA
#define Middle_Lower_Pin GPIO_PIN_7
#define Middle_Lower_GPIO_Port GPIOA
#define Ring_Lower_Pin GPIO_PIN_0
#define Ring_Lower_GPIO_Port GPIOB
#define Little_Lower_Pin GPIO_PIN_1
#define Little_Lower_GPIO_Port GPIOB
#define MotorBit_Pin GPIO_PIN_2
#define MotorBit_GPIO_Port GPIOB
#define JY61_SCL_Pin GPIO_PIN_10
#define JY61_SCL_GPIO_Port GPIOB
#define JY61_SDA_Pin GPIO_PIN_11
#define JY61_SDA_GPIO_Port GPIOB
#define GY52_SCL_Pin GPIO_PIN_6
#define GY52_SCL_GPIO_Port GPIOB
#define GY52_SDA_Pin GPIO_PIN_7
#define GY52_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define DATA_SEGMENT_4	0x04//[not used]
#define DATA_SEGMENT_8	0x08//[not used]
#define DATA_SEGMENT_16	0x10//[not used]

#define FLOAT_SIZE				0x0A	//correspoding to 2^10, equals to 0.001
#define	TYPE_SIGNED_5			0x05	//correspoding to 2^5, covers(-16, 16)
#define TYPE_UNSIGNED_7		0x07	//correspoding to 2^7, covers(0, 90)
#define TYPE_SIGNED_10		0x0A	//correspoding to 2^10, covers(-360, 360)
#define TYPE_SIGNED_12		0x0C	//correspoding to 2^12, covers(-2000,2000)

//define abs() function;[not used]
#define abs(a)(a>0?a:-a)
//function implented in 'main.c'
void SamplingTrans(void);
/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
