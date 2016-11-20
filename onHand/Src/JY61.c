
#include "JY61.h"
#include "REG.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

JY61_Data_t JY61_Data = {0};
uint8_t chrTemp[18];

short CharToShort(unsigned char cData[]);
void ShortToChar(short sData,unsigned char cData[]);

void JY61_getAcc(float *ax,float *ay,float *az)
{
	*ax = (float)JY61_Data.Acc.x; 
	*ay = (float)JY61_Data.Acc.y; 
	*az = (float)JY61_Data.Acc.z;
}
void JY61_getGryo(float *wx,float *wy,float *wz)
{
	*wx = (float)JY61_Data.Gryo.x; 
	*wy = (float)JY61_Data.Gryo.y; 
	*wz = (float)JY61_Data.Gryo.z;
}
void JY61_getAngle(float *Anglex,float *Angley,float *Anglez)
{
	*Anglex = (float)JY61_Data.Angl.x; 
	*Angley = (float)JY61_Data.Angl.y; 
	*Anglez = (float)JY61_Data.Angl.z;
}

void JY61_Print()
{
	float a[3], w[3], agl[3];
	unsigned char str[200];
	
	JY61_getAcc(&a[0], &a[1], &a[2]);
	JY61_getGryo(&w[0], &w[1], &w[2]);
	JY61_getAngle(&agl[0], &agl[1], &agl[2]);
	sprintf((char*)str,"0x50:  a:%.3f %.3f %.3f; w:%.3f %.3f %.3f; Angle:%.3f %.3f %.3f; \r\n",\
		a[0], a[1], a[2], w[0], w[1], w[2], agl[0], agl[1], agl[2]);
	HAL_UART_Transmit(&huart1, str, strlen((char *)str), 500);
}

void JY61_fetchData()
{

	  HAL_I2C_Mem_Read_DMA (&hi2c2, 0x50, AX, I2C_MEMADD_SIZE_8BIT, chrTemp, 18);
	
}
void ShortToChar(short sData,unsigned char cData[])
{
	cData[0]=sData&0xff;
	cData[1]=sData>>8;
}
short CharToShort(unsigned char cData[])
{
	return ((short)cData[1]<<8)|cData[0];
}

