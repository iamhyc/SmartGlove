#ifndef _GY52_H_
#define _GY52_H_

#include "stm32f1xx_hal.h"

typedef struct
{
	uint16_t x, y, z;
}DIM3_t;
typedef struct
{
	DIM3_t Acc, Gryo;
}GY52_Data_t;

extern uint8_t GY52_pData[14];
extern GY52_Data_t GY52_Data;

#define GY52_ADDRESS_AD0_LOW     0x68 // address pin low (GND), default for InvenSense evaluation board
#define GY52_ADDRESS_AD0_HIGH    0x69 // address pin high (VCC)
#define GY52_DEFAULT_ADDRESS     GY52_ADDRESS_AD0_LOW

#define GY52_RA_XG_OFFS_TC       0x00 //[7] PWR_MODE, [6:1] XG_OFFS_TC, [0] OTP_BNK_VLD
#define GY52_RA_YG_OFFS_TC       0x01 //[7] PWR_MODE, [6:1] YG_OFFS_TC, [0] OTP_BNK_VLD
#define GY52_RA_ZG_OFFS_TC       0x02 //[7] PWR_MODE, [6:1] ZG_OFFS_TC, [0] OTP_BNK_VLD
#define GY52_RA_X_FINE_GAIN      0x03 //[7:0] X_FINE_GAIN
#define GY52_RA_Y_FINE_GAIN      0x04 //[7:0] Y_FINE_GAIN
#define GY52_RA_Z_FINE_GAIN      0x05 //[7:0] Z_FINE_GAIN
#define GY52_RA_XA_OFFS_H        0x06 //[15:0] XA_OFFS
#define GY52_RA_XA_OFFS_L_TC     0x07
#define GY52_RA_YA_OFFS_H        0x08 //[15:0] YA_OFFS
#define GY52_RA_YA_OFFS_L_TC     0x09
#define GY52_RA_ZA_OFFS_H        0x0A //[15:0] ZA_OFFS
#define GY52_RA_ZA_OFFS_L_TC     0x0B
#define GY52_RA_XG_OFFS_USRH     0x13 //[15:0] XG_OFFS_USR
#define GY52_RA_XG_OFFS_USRL     0x14
#define GY52_RA_YG_OFFS_USRH     0x15 //[15:0] YG_OFFS_USR
#define GY52_RA_YG_OFFS_USRL     0x16
#define GY52_RA_ZG_OFFS_USRH     0x17 //[15:0] ZG_OFFS_USR
#define GY52_RA_ZG_OFFS_USRL     0x18
#define GY52_RA_SMPLRT_DIV       0x19
#define GY52_RA_CONFIG           0x1A
#define GY52_RA_GYRO_CONFIG      0x1B
#define GY52_RA_ACCEL_CONFIG     0x1C
#define GY52_RA_FF_THR           0x1D
#define GY52_RA_FF_DUR           0x1E
#define GY52_RA_MOT_THR          0x1F
#define GY52_RA_MOT_DUR          0x20
#define GY52_RA_ZRMOT_THR        0x21
#define GY52_RA_ZRMOT_DUR        0x22
#define GY52_RA_FIFO_EN          0x23
#define GY52_RA_I2C_MST_CTRL     0x24
#define GY52_RA_I2C_SLV0_ADDR    0x25
#define GY52_RA_I2C_SLV0_REG     0x26
#define GY52_RA_I2C_SLV0_CTRL    0x27
#define GY52_RA_I2C_SLV1_ADDR    0x28
#define GY52_RA_I2C_SLV1_REG     0x29
#define GY52_RA_I2C_SLV1_CTRL    0x2A
#define GY52_RA_I2C_SLV2_ADDR    0x2B
#define GY52_RA_I2C_SLV2_REG     0x2C
#define GY52_RA_I2C_SLV2_CTRL    0x2D
#define GY52_RA_I2C_SLV3_ADDR    0x2E
#define GY52_RA_I2C_SLV3_REG     0x2F
#define GY52_RA_I2C_SLV3_CTRL    0x30
#define GY52_RA_I2C_SLV4_ADDR    0x31
#define GY52_RA_I2C_SLV4_REG     0x32
#define GY52_RA_I2C_SLV4_DO      0x33
#define GY52_RA_I2C_SLV4_CTRL    0x34
#define GY52_RA_I2C_SLV4_DI      0x35
#define GY52_RA_I2C_MST_STATUS   0x36
#define GY52_RA_INT_PIN_CFG      0x37
#define GY52_RA_INT_ENABLE       0x38
#define GY52_RA_DMP_INT_STATUS   0x39
#define GY52_RA_INT_STATUS       0x3A
#define GY52_RA_ACCEL_XOUT_H     0x3B
#define GY52_RA_ACCEL_XOUT_L     0x3C
#define GY52_RA_ACCEL_YOUT_H     0x3D
#define GY52_RA_ACCEL_YOUT_L     0x3E
#define GY52_RA_ACCEL_ZOUT_H     0x3F
#define GY52_RA_ACCEL_ZOUT_L     0x40
#define GY52_RA_TEMP_OUT_H       0x41
#define GY52_RA_TEMP_OUT_L       0x42
#define GY52_RA_GYRO_XOUT_H      0x43
#define GY52_RA_GYRO_XOUT_L      0x44
#define GY52_RA_GYRO_YOUT_H      0x45
#define GY52_RA_GYRO_YOUT_L      0x46
#define GY52_RA_GYRO_ZOUT_H      0x47
#define GY52_RA_GYRO_ZOUT_L      0x48
#define GY52_RA_EXT_SENS_DATA_00 0x49
#define GY52_RA_EXT_SENS_DATA_01 0x4A
#define GY52_RA_EXT_SENS_DATA_02 0x4B
#define GY52_RA_EXT_SENS_DATA_03 0x4C
#define GY52_RA_EXT_SENS_DATA_04 0x4D
#define GY52_RA_EXT_SENS_DATA_05 0x4E
#define GY52_RA_EXT_SENS_DATA_06 0x4F
#define GY52_RA_EXT_SENS_DATA_07 0x50
#define GY52_RA_EXT_SENS_DATA_08 0x51
#define GY52_RA_EXT_SENS_DATA_09 0x52
#define GY52_RA_EXT_SENS_DATA_10 0x53
#define GY52_RA_EXT_SENS_DATA_11 0x54
#define GY52_RA_EXT_SENS_DATA_12 0x55
#define GY52_RA_EXT_SENS_DATA_13 0x56
#define GY52_RA_EXT_SENS_DATA_14 0x57
#define GY52_RA_EXT_SENS_DATA_15 0x58
#define GY52_RA_EXT_SENS_DATA_16 0x59
#define GY52_RA_EXT_SENS_DATA_17 0x5A
#define GY52_RA_EXT_SENS_DATA_18 0x5B
#define GY52_RA_EXT_SENS_DATA_19 0x5C
#define GY52_RA_EXT_SENS_DATA_20 0x5D
#define GY52_RA_EXT_SENS_DATA_21 0x5E
#define GY52_RA_EXT_SENS_DATA_22 0x5F
#define GY52_RA_EXT_SENS_DATA_23 0x60
#define GY52_RA_MOT_DETECT_STATUS    0x61
#define GY52_RA_I2C_SLV0_DO      0x63
#define GY52_RA_I2C_SLV1_DO      0x64
#define GY52_RA_I2C_SLV2_DO      0x65
#define GY52_RA_I2C_SLV3_DO      0x66
#define GY52_RA_I2C_MST_DELAY_CTRL   0x67
#define GY52_RA_SIGNAL_PATH_RESET    0x68
#define GY52_RA_MOT_DETECT_CTRL      0x69
#define GY52_RA_USER_CTRL        0x6A
#define GY52_RA_PWR_MGMT_1       0x6B
#define GY52_RA_PWR_MGMT_2       0x6C
#define GY52_RA_BANK_SEL         0x6D
#define GY52_RA_MEM_START_ADDR   0x6E
#define GY52_RA_MEM_R_W          0x6F
#define GY52_RA_DMP_CFG_1        0x70
#define GY52_RA_DMP_CFG_2        0x71
#define GY52_RA_FIFO_COUNTH      0x72
#define GY52_RA_FIFO_COUNTL      0x73
#define GY52_RA_FIFO_R_W         0x74
#define GY52_RA_WHO_AM_I         0x75

#define GY52_TC_PWR_MODE_BIT     7
#define GY52_TC_OFFSET_BIT       6
#define GY52_TC_OFFSET_LENGTH    6
#define GY52_TC_OTP_BNK_VLD_BIT  0

#define GY52_VDDIO_LEVEL_VLOGIC  0
#define GY52_VDDIO_LEVEL_VDD     1

#define GY52_CFG_EXT_SYNC_SET_BIT    5
#define GY52_CFG_EXT_SYNC_SET_LENGTH 3
#define GY52_CFG_DLPF_CFG_BIT    2
#define GY52_CFG_DLPF_CFG_LENGTH 3

#define GY52_EXT_SYNC_DISABLED       0x0
#define GY52_EXT_SYNC_TEMP_OUT_L     0x1
#define GY52_EXT_SYNC_GYRO_XOUT_L    0x2
#define GY52_EXT_SYNC_GYRO_YOUT_L    0x3
#define GY52_EXT_SYNC_GYRO_ZOUT_L    0x4
#define GY52_EXT_SYNC_ACCEL_XOUT_L   0x5
#define GY52_EXT_SYNC_ACCEL_YOUT_L   0x6
#define GY52_EXT_SYNC_ACCEL_ZOUT_L   0x7

#define GY52_DLPF_BW_256         0x00
#define GY52_DLPF_BW_188         0x01
#define GY52_DLPF_BW_98          0x02
#define GY52_DLPF_BW_42          0x03
#define GY52_DLPF_BW_20          0x04
#define GY52_DLPF_BW_10          0x05
#define GY52_DLPF_BW_5           0x06

#define GY52_GCONFIG_FS_SEL_BIT      4
#define GY52_GCONFIG_FS_SEL_LENGTH   2

#define GY52_GYRO_FS_250         0x00
#define GY52_GYRO_FS_500         0x01
#define GY52_GYRO_FS_1000        0x02
#define GY52_GYRO_FS_2000        0x03

#define GY52_ACONFIG_XA_ST_BIT           7
#define GY52_ACONFIG_YA_ST_BIT           6
#define GY52_ACONFIG_ZA_ST_BIT           5
#define GY52_ACONFIG_AFS_SEL_BIT         4
#define GY52_ACONFIG_AFS_SEL_LENGTH      2
#define GY52_ACONFIG_ACCEL_HPF_BIT       2
#define GY52_ACONFIG_ACCEL_HPF_LENGTH    3

#define GY52_ACCEL_FS_2          0x00
#define GY52_ACCEL_FS_4          0x01
#define GY52_ACCEL_FS_8          0x02
#define GY52_ACCEL_FS_16         0x03

#define GY52_DHPF_RESET          0x00
#define GY52_DHPF_5              0x01
#define GY52_DHPF_2P5            0x02
#define GY52_DHPF_1P25           0x03
#define GY52_DHPF_0P63           0x04
#define GY52_DHPF_HOLD           0x07

#define GY52_TEMP_FIFO_EN_BIT    7
#define GY52_XG_FIFO_EN_BIT      6
#define GY52_YG_FIFO_EN_BIT      5
#define GY52_ZG_FIFO_EN_BIT      4
#define GY52_ACCEL_FIFO_EN_BIT   3
#define GY52_SLV2_FIFO_EN_BIT    2
#define GY52_SLV1_FIFO_EN_BIT    1
#define GY52_SLV0_FIFO_EN_BIT    0

#define GY52_MULT_MST_EN_BIT     7
#define GY52_WAIT_FOR_ES_BIT     6
#define GY52_SLV_3_FIFO_EN_BIT   5
#define GY52_I2C_MST_P_NSR_BIT   4
#define GY52_I2C_MST_CLK_BIT     3
#define GY52_I2C_MST_CLK_LENGTH  4

#define GY52_CLOCK_DIV_348       0x0
#define GY52_CLOCK_DIV_333       0x1
#define GY52_CLOCK_DIV_320       0x2
#define GY52_CLOCK_DIV_308       0x3
#define GY52_CLOCK_DIV_296       0x4
#define GY52_CLOCK_DIV_286       0x5
#define GY52_CLOCK_DIV_276       0x6
#define GY52_CLOCK_DIV_267       0x7
#define GY52_CLOCK_DIV_258       0x8
#define GY52_CLOCK_DIV_500       0x9
#define GY52_CLOCK_DIV_471       0xA
#define GY52_CLOCK_DIV_444       0xB
#define GY52_CLOCK_DIV_421       0xC
#define GY52_CLOCK_DIV_400       0xD
#define GY52_CLOCK_DIV_381       0xE
#define GY52_CLOCK_DIV_364       0xF

#define GY52_I2C_SLV_RW_BIT      7
#define GY52_I2C_SLV_ADDR_BIT    6
#define GY52_I2C_SLV_ADDR_LENGTH 7
#define GY52_I2C_SLV_EN_BIT      7
#define GY52_I2C_SLV_BYTE_SW_BIT 6
#define GY52_I2C_SLV_REG_DIS_BIT 5
#define GY52_I2C_SLV_GRP_BIT     4
#define GY52_I2C_SLV_LEN_BIT     3
#define GY52_I2C_SLV_LEN_LENGTH  4

#define GY52_I2C_SLV4_RW_BIT         7
#define GY52_I2C_SLV4_ADDR_BIT       6
#define GY52_I2C_SLV4_ADDR_LENGTH    7
#define GY52_I2C_SLV4_EN_BIT         7
#define GY52_I2C_SLV4_INT_EN_BIT     6
#define GY52_I2C_SLV4_REG_DIS_BIT    5
#define GY52_I2C_SLV4_MST_DLY_BIT    4
#define GY52_I2C_SLV4_MST_DLY_LENGTH 5

#define GY52_MST_PASS_THROUGH_BIT    7
#define GY52_MST_I2C_SLV4_DONE_BIT   6
#define GY52_MST_I2C_LOST_ARB_BIT    5
#define GY52_MST_I2C_SLV4_NACK_BIT   4
#define GY52_MST_I2C_SLV3_NACK_BIT   3
#define GY52_MST_I2C_SLV2_NACK_BIT   2
#define GY52_MST_I2C_SLV1_NACK_BIT   1
#define GY52_MST_I2C_SLV0_NACK_BIT   0

#define GY52_INTCFG_INT_LEVEL_BIT        7
#define GY52_INTCFG_INT_OPEN_BIT         6
#define GY52_INTCFG_LATCH_INT_EN_BIT     5
#define GY52_INTCFG_INT_RD_CLEAR_BIT     4
#define GY52_INTCFG_FSYNC_INT_LEVEL_BIT  3
#define GY52_INTCFG_FSYNC_INT_EN_BIT     2
#define GY52_INTCFG_I2C_BYPASS_EN_BIT    1
#define GY52_INTCFG_CLKOUT_EN_BIT        0

#define GY52_INTMODE_ACTIVEHIGH  0x00
#define GY52_INTMODE_ACTIVELOW   0x01

#define GY52_INTDRV_PUSHPULL     0x00
#define GY52_INTDRV_OPENDRAIN    0x01

#define GY52_INTLATCH_50USPULSE  0x00
#define GY52_INTLATCH_WAITCLEAR  0x01

#define GY52_INTCLEAR_STATUSREAD 0x00
#define GY52_INTCLEAR_ANYREAD    0x01

#define GY52_INTERRUPT_FF_BIT            7
#define GY52_INTERRUPT_MOT_BIT           6
#define GY52_INTERRUPT_ZMOT_BIT          5
#define GY52_INTERRUPT_FIFO_OFLOW_BIT    4
#define GY52_INTERRUPT_I2C_MST_INT_BIT   3
#define GY52_INTERRUPT_PLL_RDY_INT_BIT   2
#define GY52_INTERRUPT_DMP_INT_BIT       1
#define GY52_INTERRUPT_DATA_RDY_BIT      0

// TODO: figure out what these actually do
// UMPL source code is not very obivous
#define GY52_DMPINT_5_BIT            5
#define GY52_DMPINT_4_BIT            4
#define GY52_DMPINT_3_BIT            3
#define GY52_DMPINT_2_BIT            2
#define GY52_DMPINT_1_BIT            1
#define GY52_DMPINT_0_BIT            0

#define GY52_MOTION_MOT_XNEG_BIT     7
#define GY52_MOTION_MOT_XPOS_BIT     6
#define GY52_MOTION_MOT_YNEG_BIT     5
#define GY52_MOTION_MOT_YPOS_BIT     4
#define GY52_MOTION_MOT_ZNEG_BIT     3
#define GY52_MOTION_MOT_ZPOS_BIT     2
#define GY52_MOTION_MOT_ZRMOT_BIT    0

#define GY52_DELAYCTRL_DELAY_ES_SHADOW_BIT   7
#define GY52_DELAYCTRL_I2C_SLV4_DLY_EN_BIT   4
#define GY52_DELAYCTRL_I2C_SLV3_DLY_EN_BIT   3
#define GY52_DELAYCTRL_I2C_SLV2_DLY_EN_BIT   2
#define GY52_DELAYCTRL_I2C_SLV1_DLY_EN_BIT   1
#define GY52_DELAYCTRL_I2C_SLV0_DLY_EN_BIT   0

#define GY52_PATHRESET_GYRO_RESET_BIT    2
#define GY52_PATHRESET_ACCEL_RESET_BIT   1
#define GY52_PATHRESET_TEMP_RESET_BIT    0

#define GY52_DETECT_ACCEL_ON_DELAY_BIT       5
#define GY52_DETECT_ACCEL_ON_DELAY_LENGTH    2
#define GY52_DETECT_FF_COUNT_BIT             3
#define GY52_DETECT_FF_COUNT_LENGTH          2
#define GY52_DETECT_MOT_COUNT_BIT            1
#define GY52_DETECT_MOT_COUNT_LENGTH         2

#define GY52_DETECT_DECREMENT_RESET  0x0
#define GY52_DETECT_DECREMENT_1      0x1
#define GY52_DETECT_DECREMENT_2      0x2
#define GY52_DETECT_DECREMENT_4      0x3

#define GY52_USERCTRL_DMP_EN_BIT             7
#define GY52_USERCTRL_FIFO_EN_BIT            6
#define GY52_USERCTRL_I2C_MST_EN_BIT         5
#define GY52_USERCTRL_I2C_IF_DIS_BIT         4
#define GY52_USERCTRL_DMP_RESET_BIT          3
#define GY52_USERCTRL_FIFO_RESET_BIT         2
#define GY52_USERCTRL_I2C_MST_RESET_BIT      1
#define GY52_USERCTRL_SIG_COND_RESET_BIT     0

#define GY52_PWR1_DEVICE_RESET_BIT   7
#define GY52_PWR1_SLEEP_BIT          6
#define GY52_PWR1_CYCLE_BIT          5
#define GY52_PWR1_TEMP_DIS_BIT       3
#define GY52_PWR1_CLKSEL_BIT         2
#define GY52_PWR1_CLKSEL_LENGTH      3

#define GY52_CLOCK_INTERNAL          0x00
#define GY52_CLOCK_PLL_XGYRO         0x01
#define GY52_CLOCK_PLL_YGYRO         0x02
#define GY52_CLOCK_PLL_ZGYRO         0x03
#define GY52_CLOCK_PLL_EXT32K        0x04
#define GY52_CLOCK_PLL_EXT19M        0x05
#define GY52_CLOCK_KEEP_RESET        0x07

#define GY52_PWR2_LP_WAKE_CTRL_BIT       7
#define GY52_PWR2_LP_WAKE_CTRL_LENGTH    2
#define GY52_PWR2_STBY_XA_BIT            5
#define GY52_PWR2_STBY_YA_BIT            4
#define GY52_PWR2_STBY_ZA_BIT            3
#define GY52_PWR2_STBY_XG_BIT            2
#define GY52_PWR2_STBY_YG_BIT            1
#define GY52_PWR2_STBY_ZG_BIT            0

#define GY52_WAKE_FREQ_1P25      0x0
#define GY52_WAKE_FREQ_2P5       0x1
#define GY52_WAKE_FREQ_5         0x2
#define GY52_WAKE_FREQ_10        0x3

#define GY52_BANKSEL_PRFTCH_EN_BIT       6
#define GY52_BANKSEL_CFG_USER_BANK_BIT   5
#define GY52_BANKSEL_MEM_SEL_BIT         4
#define GY52_BANKSEL_MEM_SEL_LENGTH      5

#define GY52_WHO_AM_I_BIT        6
#define GY52_WHO_AM_I_LENGTH     6

#define GY52_DMP_MEMORY_BANKS        8
#define GY52_DMP_MEMORY_BANK_SIZE    256
#define GY52_DMP_MEMORY_CHUNK_SIZE   16

void GY52_Init(void);
void GY52_fetchData(void);
void GY52_print(void);
void GY52_getAcc(float * ax, float* ay, float* az);
void GY52_getGryo(float* gx, float* gy, float* gz);
void GY52_getMotion6(uint16_t* ax, uint16_t* ay, uint16_t* az, uint16_t* gx, uint16_t* gy, uint16_t* gz);

#endif
