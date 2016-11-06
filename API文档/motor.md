#Motor

##Configure

	PB2为输出端；TIM2的Channel1已开启（中断），可用作计时

	注：cubeMX只能查看，不能保存！任何修改需联系管理员！

##Export

+ void Motor_Start(void)
	
	高电平

+ void Motor_Stop(void)
	
	低电平

+ void Motor_Flip(void)
	
	翻转

+ void Motor_On(int micro)

	开启持续micro毫秒后关闭

##Debug

### void Motor_Note(int n, int * micros)

	弹奏一首~

