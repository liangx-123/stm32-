//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : 
//  ��������   : 2014-0101
//  ����޸�   : 
//  ��������   : 0.69��OLED �ӿ���ʾ����(STM32F103ZEϵ��IIC)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND   ��Դ��
//              VCC   ��5V��3.3v��Դ
//              SCL   ��PB13��SCL��
//              SDA   ��PB15��SDA�� 
//              RES   ��PB11 �������4��iic�ӿ�����ſ��Բ���
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
extern u8 RX_num;				 //���ռ�������
int iii=0,i=0;
char aa[150];
 int main(void)
  {	u8 t;
			 //���ڳ�ʼ��Ϊ9600  
		delay_init();	    	 //��ʱ������ʼ��	  
		NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 	LED_Init();			     //LED�˿ڳ�ʼ��
	//		delay_ms(8000);
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		
	OLED_Init();			//��ʼ��OLED  
OLED_Clear()  	; 
			
		delay_ms(400);
		myuart(115200);
		t=' ';

//		OLED_ShowCHinese(54,0,3);//��
//		OLED_ShowCHinese(72,0,4);//��
//		OLED_ShowCHinese(90,0,5);//��
//		OLED_ShowCHinese(108,0,6);//��		

	while(1) 
	{		
		
				for(i=0;i<1500;i++){
					if(RX_buffer[i]=='o'&&RX_buffer[i+1]=='w'){
aa[0]=RX_buffer[i+13];//�õ���������
				
				
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

//	OLED_ShowCHinese(54,0,1);//��
//		OLED_ShowCHinese(72,0,2);//��
//		OLED_ShowCHinese(90,0,3);//��
//		OLED_ShowCHinese(108,0,4);//��
//			OLED_ShowCHinese(38,0,0);//��
//		

//		
	
//		//OLED_ShowString(8,2,"ZHONGJINGYUAN");  
//	 //	OLED_ShowString(20,4,"2014/05/01");  
//		OLED_ShowString(0,6,"ASCII:",16);  
//		OLED_ShowString(63,6,"CODE:",16);  
//		OLED_ShowChar(48,6,t,16);//��ʾASCII�ַ�	   
//		t++;
//		if(t>'~')t=' ';
//		OLED_ShowNum(103,6,t,3,16);//��ʾASCII�ַ�����ֵ 	
//			delay_ms(8000);
//		delay_ms(8000);

//					delay_ms(8000);
//		delay_ms(8000);
////		delay_ms(8000);
//		OLED_DrawBMP(0,0,128,8,BMP2);  //ͼƬ��ʾ(ͼƬ��ʾ���ã����ɵ��ֱ�ϴ󣬻�ռ�ý϶�ռ䣬FLASH�ռ�8K��������)
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
	