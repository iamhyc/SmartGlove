
#include "JY61.h"
#include "REG.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"


float a[3],w[3],h[3],Angle[3];
uint8_t chrTemp[18];

void JY61_getAcc(float *ax,float *ay,float *az)
{
	*ax = a[0]; *ay = a[1]; *az = a[2];
}
void JY61_getGryo(float *wx,float *wy,float *wz)
{
	*wx = w[0]; *wy = w[1]; *wz = w[2];
}
void JY61_getAngle(float *Anglex,float *Angley,float *Anglez)
{
	*Anglex = Angle[0]; *Angley = Angle[1]; *Anglez = Angle[2];
}

void Print()
{
		unsigned char str[100];
		sprintf((char*)str,"0x50:  a:%.3f %.3f %.3f w:%.3f %.3f %.3f  h:%.0f %.0f %.0f  Angle:%.3f %.3f %.3f \r\n",\
			a[0],a[1],a[2],w[0],w[1],w[2],h[0],h[1],h[2],Angle[0],Angle[1],Angle[2]);
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

