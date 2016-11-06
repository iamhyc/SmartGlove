#ADC Sampling

##Configure

	因为使用ADC2的缘故，需要使用借用ADC1上的DMA传输数据；
	数据在调用HAL_ADC_Start_DMA中会要求填充长度为5的u32数组
	参数已配置完毕，连续模式规则组，每个channel 6us采样，可自行查看cubeMX配置

	注：cubeMX只能查看，不能保存！任何修改需联系管理员！

##Export

+ void ADC\_Start\_DMA(uint32\_t * pData)

	传入数组handler，并开始DMA传输；
	
	注：这部分内容需参考DACEx文档部分（DAC Extension）

+ void ADC\_Stop\_DMA(void)

+ uint16 ADC\_getChannel(int channel)

	注意ADC2数据在32位数据的高16位

+ (uint16 *) ADC\_getAll(void)
	
	返回数据按照channel顺序排列，从IN0到IN9

##Debug

+ void ADC_print(void)
	
	打印10个changnnel解读出的u16数据