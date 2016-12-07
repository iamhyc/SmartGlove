/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "adc.h"
#include "crc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
	//include all the functional head file
#include "softconv.h"
#include "JY61.h"
#include "GY52.h"
#include "motor.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
static uint16_t pkt_size = 72;//packet size defined in bytes;almost const(with FLOAT_SIZE= 0x0A)
static uint32_t seq = 0;//HEADER{Timestamp, **seq**, data}
uint8_t RX_pData[4];//Array used for receive packet from HOST;constant 4 bytes
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
	//predefined built-in function
uint16_t floatEnconding(float, uint16_t, uint8_t*);
void onHandSystem_Init(void);
void fetchData_Async(void);
uint8_t* compressData(void);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/**
  * @brief  Encoding *float number* into *uint8*; \
	* SignBit(len:1) + IntegerPart(len:*type*) + DecimalPart(len:FLOAT_SIZE) \
	* THIS IS NOT COMPLEMENT CODING; E.g. -8.99945 --> 11000  11 1110 0111 (with TYPE_SIGNED_5)
  * @param  raw, raw data with *float* format
	*	@param  type, defined constatnt like TYPE_(UN)SIGNED_X in 'main.h'
	* @param  *data, the Encoded data in (uint8_t) format to take back
  * @retval uint16_t, the length of '*data' pointer(in bit)
  */
uint16_t floatEncoding(float raw, uint16_t type, uint8_t* data)
{
	uint8_t flag = 0;
	uint16_t *t1, *t2, mask1, mask2;
	mask1 = (1 << type) - 1;//mask for IntegerPart
	mask2 = (1 << FLOAT_SIZE) - 1;//mask for DecimalPart
	
	if(raw < 0)
	{
		raw = -raw;//remove negative sign; THIS IS NOT COMPLEMENT CODING
		flag = 1;//mark whether is negative
	}
	
	*t1 = (uint16_t)raw & mask1;//with mask on IntegerPart(without sign), set other bit 0
	*t2 = (uint16_t)((raw-(int)raw) * 1E3) & mask2;//with mask on DecimalPart, set other bit 0
	
	*data = ((*t1) << FLOAT_SIZE) & (*t2);//addup the both part
	if(flag == 1)	//negative number
		*data &= flag << (FLOAT_SIZE + type - 1);//add sign on the first bit
	return (FLOAT_SIZE + type);//return the length
}

/**
  * @brief  This is the function firstly called by USER\
	* to start the *procedure* of the system
  * @param  none
  * @retval none
  */
void onHandSystem_Init()
{
	//Init the sensor needed to init
	ADC_Init();
	GY52_Init();
	
	Motor_Hold(1000);//run in block-mode
	//sensor carlibration start, not implemented
	HAL_Delay(3000);
	//sensor carlibration stop, not implemented
	Motor_Hold(1000);//run in block-mode
	
	HAL_UART_Receive_IT(&huart1, RX_pData, 4);//wait to wakeup by Host
}

/**
  * @brief  This is the function invoking each sensor's \
	* fetchData function to fetch data Asynchronous
  * @param  none
  * @retval none
  */
void fetchData_Async()
{
	ADC_fetchData();//fill in ADC_realData[10]
	JY61_fetchData();//fill in JY61_Data_t JY61_Data
	GY52_fetchData();//fill in GY52_Data_t GY52_Data
}

/**
  * @brief  Building the packet; Calling 'floatEncoding' for each segment
  * @param  none
  * @retval (uint8_t *), the actual packet as the result
  */
uint8_t* compressData(void)
{
	uint8_t *data = (uint8_t *)malloc(8 * pkt_size);//allocate memory by user, so need 'free' it
	uint8_t *ptr, *tmp, size;//index pointer; temp data generated; temp data length;
	float JY61_data[9] = {0};
	float GY52_data[6] = {0};
	
	//RETRIEVE *ADC* DATA(LOCAL from MEMORY)
	float *ADC_data = ADC_getAll();
	//RETRIEVE *JY61* DATA(LOCAL from MEMORY)
	JY61_getAcc(&JY61_data[0], &JY61_data[1], &JY61_data[2]);
	JY61_getGryo(&JY61_data[3], &JY61_data[4], &JY61_data[5]);
	JY61_getAngle(&JY61_data[6], &JY61_data[7], &JY61_data[8]);
	//RETRIEVE *GY52* DATA(LOCAL from MEMORY)
	GY52_getAcc(&GY52_data[0], &GY52_data[1], &GY52_data[2]);
	GY52_getGryo(&GY52_data[3], &GY52_data[4], &GY52_data[5]);
	
	//maintain *ptr as index pointer to TRAVERSE the packet size
	ptr = data;
	
	/**
  * @brief  Add HEADER
	* STRUCTURE:[90 BYTES]
	* |---------------------------|
	* |					'LFT'/'RAT'				|(3 bytes)
	* |---------------------------|
	* |					TimeStamp					|(4 bytes)
	* |---------------------------|
	* |					Sequnce No.				|(4 bytes)
	* |---------------------------|
	* |'A'|		JY61ACCX		|		JY61ACCY		|		JY61ACCZ		|(1+6 bytes)
	* |---------------------------|
	* |'B'|		JY61GRYX		|		JY61GRYY		|		JY61GRYZ		|(1+9 bytes)
	* |---------------------------|
	* |'C'|		JY61AGLX		|		JY61AGLY		|		JY61AGLZ		|(1+9 bytes)
	* |---------------------------|
	* |'D'|		GY52ACCX		|		GY52ACCY		|		GY52ACCZ		|(1+6 bytes)
	* |---------------------------|
	* |'E'|		GY52GRYX		|		GY52GRYY		|		GY52GRYZ		|(1+9 bytes)
	* |---------------------------|
	* |'F'|											ADC1 * 5									|(1+15 bytes)
	* |---------------------------|
	* |'G'|											ADC2 * 5									|(1+15 bytes)
	* |---------------------------|
	* |					'END'							|(3 bytes)
	* |---------------------------|
  */
	uint32_t* Timestamp;
	*Timestamp = HAL_GetTick();
	memcpy(ptr, (uint8_t *)Timestamp, 4);	ptr += 4;
	memcpy(ptr, (uint8_t *)seq, 4);				ptr += 4;
	
	/**
  * 'A', for JY61.ACC, 3*(5+10)
  */
	*(ptr++) = (uint8_t)'A';//add sign 'A', and shift the pointer to next place
	for (int i = 0; i < 3; i++)
	{
		size = floatEncoding(JY61_data[i], TYPE_SIGNED_5, tmp);
		size = ceil(size/8);//int bytes, to cover all the bits
		memcpy(ptr, tmp, size);//copy the data from *tmp* to *ptr* with *size*
		ptr += size;//pointer shift to next
	}
	
	/**
  * 'B', for JY61.GRYO, 3*(12+10)
  */
	*(ptr++) = (uint8_t)'B';
	for (int i = 3; i < 6; i++)
	{
		size = floatEncoding(JY61_data[i], TYPE_SIGNED_12, tmp);
		size = ceil(size/8);
		memcpy(ptr, tmp, size);	
		ptr += size;
	}

	/**
  * 'C', for JY61.ANGL, 3*(10+10)
  */
	*(ptr++) = (uint8_t)'C';
	for (int i = 6; i < 9; i++)
	{
		size = floatEncoding(JY61_data[i], TYPE_SIGNED_10, tmp);
		size = ceil(size/8);
		memcpy(ptr, tmp, size);	
		ptr += size;
	}
	
	/**
  * 'D', for GY52.ACC, 3*(5+10)
  */
	*(ptr++) = (uint8_t)'D';
	for (int i = 0; i < 3; i++)
	{
		size = floatEncoding(GY52_data[i], TYPE_SIGNED_5, tmp);
		size = ceil(size/8);
		memcpy(ptr, tmp, size);	
		ptr += size;
	}
	
	/**
  * 'E', for GY52.GRYO, 3*(12+10)
  */
	*(ptr++) = (uint8_t)'E';
	for (int i = 3; i < 6; i++)
	{
		size = floatEncoding(GY52_data[i], TYPE_SIGNED_12, tmp);
		size = ceil(size/8);
		memcpy(ptr, tmp, size);	
		ptr += size;
	}
	
	/**
  * 'F', for ADC 1, 5*(7+10)
  */
	*(ptr++) = (uint8_t)'F';
	for (int i = 0; i < 5; i++)
	{
		size = floatEncoding(ADC_data[i], TYPE_UNSIGNED_7, tmp);
		size = ceil(size/8);
		memcpy(ptr, tmp, size);	
		ptr += size;
	}
	
	/**
  * 'F', for ADC 2, 5*(7+10)
  */
	*(ptr++) = (uint8_t)'G';
	for (int i = 5; i < 10; i++)
	{
		size = floatEncoding(ADC_data[i], TYPE_UNSIGNED_7, tmp);
		size = ceil(size/8);
		memcpy(ptr, tmp, size);	
		ptr += size;
	}
	
	return data;
}

/**
  * @brief  This is the function called by interept with TIM2
  * @param  none
  * @retval none
  */
void SamplingTrans()
{
	fetchData_Async();//call fetch data first
	uint8_t* pkt = compressData();//compress the data LAST TIME fetched(most possiblly)
	HAL_UART_Transmit_DMA(&huart1, pkt, pkt_size);//transmit the packet through DMA
	free(pkt);//remember to free the allocate memory
}
/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_CRC_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();

  /* USER CODE BEGIN 2 */
		//Initialization
		onHandSystem_Init();//call procedure start
		
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }

    /**Enables the Clock Security System 
    */
  HAL_RCC_EnableCSS();

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
