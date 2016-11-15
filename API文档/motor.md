#Motor

##Configure

<cite>PB2为输出端；TIM2的Channel1已开启（中断），可用作计时, 参数调整请告知管理员

	注：cubeMX只能查看，不能保存！任何修改需联系管理员！
</cite>

##Export

+ **void Motor_Start(void)**
	
	<font size = 2>
	高电平
	</font>

+ **void Motor_Stop(void)**

	<font size = 2>
	低电平
	</font>
	

+ **void Motor_Flip(void)**
	
	<font size = 2>
	翻转
	</font>

+ **void Motor_On(int micro)**

	<font size = 2>
	开启持续micro毫秒后关闭
	</font>

##Debug

+ **void Motor_Note(int n, int * micros)**

	<font size = 2>
		弹奏一首~
	</font>

