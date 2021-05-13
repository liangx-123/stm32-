
stm32天气
===================
 stm32天气为原版本;
 
 V_1测试显示文字,成功;
 V_2为最终成品;
 
 接线:
		DHT11: GND---->GND (ESP8266)
			   VCC---->3.3 
			   DATA--->D4
			   
		ESP8266: RX---->J6左1 (STM32)
				 TX---->J6右4
				 GND--->J1 GND
				 3.3--->J1 3.3
				 
				 VH---->J1 5V
				 GND--->J6 左4
				 
		OLED: GND---->GND (STM32)
			  VCC---->3.3
			  SCL---->B13
			  SDA---->B15
