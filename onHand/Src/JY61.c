
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
	*ax = JY61_Data.Acc.x; 
	*ay = JY61_Data.Acc.y; 
	*az = JY61_Data.Acc.z;
}
void JY61_getGryo(float *wx,float *wy,float *wz)
{
	*wx = JY61_Data.Gryo.x; 
	*wy = JY61_Data.Gryo.y; 
	*wz = JY61_Data.Gryo.z;
}
void JY61_getAngle(float *Anglex,float *Angley,float *Anglez)
{
	*Anglex = JY61_Data.Angl.x; 
	*Angley = JY61_Data.Angl.y; 
	*Anglez = JY61_Data.Angl.z;
}

void Print()
{
	float *ax, *ay, *az, *wx, *wy, *wz, *alx, *aly, *alz;
	unsigned char str[100];
	
	JY61_getAcc(ax, ay, az);
	JY61_getGryo(wx, wy, wz);
	JY61_getAngle(alx, aly, alz);
	sprintf((char*)str,"0x50:  a:%.3f %.3f %.3f; w:%.3f %.3f %.3f; Angle:%.3f %.3f %.3f; \r\n",\
		*ax, *ay, *az, *wx, *wy, *wz, *alx, *aly, *alz);
	HAL_UART_Transmit(&huart1, str, strlen((char *)str), 5);
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

