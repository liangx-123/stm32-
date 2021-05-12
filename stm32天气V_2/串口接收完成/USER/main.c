//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : 
//  生成日期   : 2014-0101
//  最近修改   : 
//  功能描述   : 0.69寸OLED 接口演示例程(STM32F103ZE系列IIC)
//              说明: 
//              ----------------------------------------------------------------
//              GND   电源地
//              VCC   接5V或3.3v电源
//              SCL   接PB13（SCL）
//              SDA   接PB15（SDA） 
//              RES   接PB11 如果是用4针iic接口这个脚可以不接
//              ----------------------------------------------------------------
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include  "usart.h"
#include  "string.h"


extern u8 RX_buffer[tbuf];
extern u8 RX_num;				 //接收计数变量
int iii=0,i=0;
char aa[150];
 int main(void)
  {	u8 t;
			 //串口初始化为9600  
		delay_init();	    	 //延时函数初始化	  
		NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 	LED_Init();			     //LED端口初始化
	//		delay_ms(8000);
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		
	OLED_Init();			//初始化OLED  
OLED_Clear()  	; 
			
		delay_ms(400);
		myuart(115200);
		t=' ';

//		OLED_ShowCHinese(54,0,3);//电
//		OLED_ShowCHinese(72,0,4);//子
//		OLED_ShowCHinese(90,0,5);//科
//		OLED_ShowCHinese(108,0,6);//技		

	while(1) 
	{		
		
				for(i=0;i<1500;i++){
					if(RX_buffer[i]=='o'&&RX_buffer[i+1]=='w'){
aa[0]=RX_buffer[i+13];//拿到天气代码
				
				
					}
					if(RX_buffer[i]=='r'&&RX_buffer[i+1]=='e'){
aa[1]=RX_buffer[i+4];
						aa[2]=RX_buffer[i+5];
  

		}
						if(RX_buffer[i]=='T'&&RX_buffer[i+1]=='T'){
aa[3]=RX_buffer[i+3];
						aa[4]=RX_buffer[i+4];
  

		}
							if(RX_buffer[i]=='H'&&RX_buffer[i+1]=='H'){
aa[5]=RX_buffer[i+3];
						aa[6]=RX_buffer[i+4];
  

		}
				Uart1SendStr(aa) ;
		OLED_ShowString(8,2,aa,7);}
//		
//		for(i=0;i<50;i++){
//aa[i]=RX_buffer[i];

//		}
	//	Uart1SendStr(RX_buffer) ;	
		
//		OLED_Clear();

//	OLED_ShowCHinese(54,0,1);//电
//		OLED_ShowCHinese(72,0,2);//子
//		OLED_ShowCHinese(90,0,3);//科
//		OLED_ShowCHinese(108,0,4);//技
//			OLED_ShowCHinese(38,0,0);//技
//		

//		
	
//		//OLED_ShowString(8,2,"ZHONGJINGYUAN");  
//	 //	OLED_ShowString(20,4,"2014/05/01");  
//		OLED_ShowString(0,6,"ASCII:",16);  
//		OLED_ShowString(63,6,"CODE:",16);  
//		OLED_ShowChar(48,6,t,16);//显示ASCII字符	   
//		t++;
//		if(t>'~')t=' ';
//		OLED_ShowNum(103,6,t,3,16);//显示ASCII字符的码值 	
//			delay_ms(8000);
//		delay_ms(8000);

//					delay_ms(8000);
//		delay_ms(8000);
////		delay_ms(8000);
//		OLED_DrawBMP(0,0,128,8,BMP2);  //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
//		delay_ms(8000);
//					delay_ms(8000);
//		delay_ms(8000);
//		delay_ms(8000);
//		OLED_DrawBMP(0,0,128,8,BMP2);
//		delay_ms(8000);
//					delay_ms(8000);
//		delay_ms(8000);
//		delay_ms(8000);
	}	  
	
}
	