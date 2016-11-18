#ADC Sampling

##Configure

<cite>**注意：先查看cube生成的配置文件做了什么！**
	
因为使用ADC2的缘故，需要使用借用ADC1上的DMA传输数据；

数据在调用HAL\_ADC\_Start_DMA中会要求填充长度为5的u32数组

参数已配置完毕，非·连续模式规则组，每个channel 18us采样，可自行查看cubeMX配置

**数组定义在头文件中，extern标识**

	注：cubeMX只能查看，不能保存！任何修改需联系管理员！
</cite>

##Export

+ **void ADC\_Init(void)**

	<font size=2>
	(1) ADC calibration for both
	</font>

+ **void ADC\_fetchData(void)**

	<font size=2>软件触发一轮转换，DMA传输；
	
	在DMA中断中对数据处理（滤波），并填充数组/结构体
	
	注：这部分内容需参考DACEx文档部分（DAC Extension）</font>


+ **uint16\_t ADC\_getChannel(int channel)**

	<font size=2>注意ADC2数据在32位数据的高16位</font>

+ **(float *) ADC\_getAll(void)**
	
	<font size=2>返回数据按照channel顺序排列，从IN0到IN9</font>

##Debug

+ void ADC_print(void)
	
	打印10个changnnel解读出的u16数据