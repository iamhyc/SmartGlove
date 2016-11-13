#include "gpio.h"
#include "REG.h"
#include "JY61.h"

static float a[3],w[3],h[3],Angle[3];

extern I2C_HandleTypeDef hi2c1;

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
}

void JY61_TxAndRx()
{
	  unsigned char chrTemp[18];
    HAL_I2C_Master_Transmit (&hi2c1, 0x50, (uint8_t *)AX, sizeof (AX), 1) ;		
		while(HAL_I2C_GetState (&hi2c1)!=HAL_I2C_STATE_BUSY_TX);	
		HAL_I2C_Master_Receive_DMA(&hi2c1, 0x50,&chrTemp[0],1);	
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

int test(void)
{  
  unsigned char chrTemp[18];
	unsigned char str[100];
	
	
	while (1)
	{
    JY61_TxAndRx();
		
		a[0] = (float)CharToShort(&chrTemp[0])/32768*16;
		a[1] = (float)CharToShort(&chrTemp[2])/32768*16;
		a[2] = (float)CharToShort(&chrTemp[4])/32768*16;
		w[0] = (float)CharToShort(&chrTemp[6])/32768*2000;
		w[1] = (float)CharToShort(&chrTemp[8])/32768*2000;
		w[2] = (float)CharToShort(&chrTemp[10])/32768*2000;
		Angle[0] = (float)CharToShort(&chrTemp[12])/32768*180;
		Angle[1] = (float)CharToShort(&chrTemp[14])/32768*180;
		Angle[2] = (float)CharToShort(&chrTemp[16])/32768*180;		
		sprintf((char*)str,"0x50:  a:%.3f %.3f %.3f w:%.3f %.3f %.3f  h:%.0f %.0f %.0f  Angle:%.3f %.3f %.3f \r\n",a[0],a[1],a[2],w[0],w[1],w[2],h[0],h[1],h[2],Angle[0],Angle[1],Angle[2]);	
	}
}
