
#include "GY52.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

uint8_t GY52_pData[14];
GY52_Data_t GY52_Data = {0};

static uint8_t devAddr = GY52_DEFAULT_ADDRESS;

uint8_t generateCode(uint8_t start_bit, uint8_t length, uint8_t data){
	uint8_t mask = (0x01<<length) - 1;
	data &= mask;
	data <<= start_bit;
	return data;
}

void setClockSource(uint8_t source) {
	uint8_t *data;
	*data = generateCode(GY52_PWR1_CLKSEL_BIT, GY52_PWR1_CLKSEL_LENGTH, source);
	*data &= generateCode(GY52_PWR1_SLEEP_BIT, 1, 1);//enable sleep mode
	HAL_I2C_Mem_Write(&hi2c1, devAddr, GY52_RA_PWR_MGMT_1, I2C_MEMADD_SIZE_8BIT, (uint8_t *)data, 1, 10);
}

void setFullScaleGyroRange(uint8_t range) {
	uint8_t *data;
	*data = generateCode(GY52_GCONFIG_FS_SEL_BIT, GY52_GCONFIG_FS_SEL_LENGTH, range);
	HAL_I2C_Mem_Write(&hi2c1, devAddr, GY52_RA_GYRO_CONFIG, I2C_MEMADD_SIZE_8BIT, (uint8_t *)data, 1, 10);
}

void setFullScaleAccelRange(uint8_t range) {
	uint8_t *data;
	*data = generateCode(GY52_ACONFIG_AFS_SEL_BIT, GY52_ACONFIG_AFS_SEL_LENGTH, range);
	HAL_I2C_Mem_Write(&hi2c1, devAddr, GY52_RA_ACCEL_CONFIG, I2C_MEMADD_SIZE_8BIT, (uint8_t *)data, 1, 10);
}

void GY52_Init()
{
	setClockSource(GY52_CLOCK_PLL_XGYRO);
	setFullScaleGyroRange(GY52_GYRO_FS_2000);
	setFullScaleAccelRange(GY52_ACCEL_FS_16);
}

void GY52_fetchData()
{
	HAL_I2C_Mem_Read_DMA(&hi2c1, devAddr, GY52_RA_ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT, GY52_pData, 14);
}

void GY52_getAcc(float * ax, float* ay, float* az)
{
	*ax = (float)GY52_Data.Acc.x/32768*16;
	*ay = (float)GY52_Data.Acc.y/32768*16;
	*az = (float)GY52_Data.Acc.z/32768*16;
}

void GY52_getGryo(float* gx, float* gy, float* gz)
{
	*gx = (float)GY52_Data.Gryo.x/32768*2000;
	*gy = (float)GY52_Data.Gryo.y/32768*2000;
	*gz = (float)GY52_Data.Gryo.z/32768*2000;
}

void GY52_getMotion6(uint16_t* ax, uint16_t* ay, uint16_t* az, uint16_t* gx, uint16_t* gy, uint16_t* gz)
{
	*ax = GY52_Data.Acc.x;
	*ay = GY52_Data.Acc.y;
	*az = GY52_Data.Acc.z;

	*gx = GY52_Data.Gryo.x;
	*gy = GY52_Data.Gryo.y;
	*gz = GY52_Data.Gryo.z;
}

void GY52_print()
{
	unsigned char str[200];
	float a[3], w[3];
	
	GY52_getAcc(&a[0], &a[1], &a[2]);
	GY52_getGryo(&w[0], &w[1], &w[2]);
  	
  sprintf((char *)str, "a:%.3f %.3f %.3f\nw:%.3f %.3f %.3f", a[0], a[1], a[2], w[0], w[1], w[2]);
	HAL_UART_Transmit(&huart1, str, strlen((char *)str), 5);
}
