
//              GND   ��Դ��
//              VCC   ��5V��3.3v��Դ
//              SCL   ��PB13��SCL��
//              SDA   ��PB15��SDA��
//              RES   ��PB11 �������4��iic�ӿ�����ſ��Բ���

#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include "usart.h"
#include "string.h"

extern u8 RX_buffer[tbuf];
extern u8 RX_num; //���ռ�������
int iii = 0, i = 0;
u8 wendu[5];
u8 shishiwendu[5];
u8 shishishidu[5];
u8 aa[5];
u8 month[5];
u8 day[5];
int main(void)
{
    //���ڳ�ʼ��Ϊ9600
    delay_init();         //��ʱ������ʼ��
    NVIC_Configuration(); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 	LED_Init();			     //LED�˿ڳ�ʼ��
                          //		delay_ms(8000);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    OLED_Init(); //��ʼ��OLED
    OLED_Clear();

    myuart(115200);
    delay_ms(400);

    //aa[]���� 0�������� 12�¶�  34ʵʱ�¶� 56 ʵʱʪ��
    while (1)
    {
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == 0)
        {

            OLED_DrawBMP(0, 0, 128, 8, qing);
            delay_ms(10000);
            OLED_Clear();
        }
        for (i = 0; i < 1500; i++)
        {
            if (RX_buffer[i] == 'o' && RX_buffer[i + 1] == 'w')
            {
                aa[0] = RX_buffer[i + 13]; //�õ���������
            }
            if (RX_buffer[i] == 'r' && RX_buffer[i + 1] == 'e')
            {
                wendu[0] = RX_buffer[i + 4];
                wendu[1] = RX_buffer[i + 5];
            }
            if (RX_buffer[i] == 'T' && RX_buffer[i + 1] == 'T')
            {
                shishiwendu[0] = RX_buffer[i + 3];
                shishiwendu[1] = RX_buffer[i + 4];
            }
            if (RX_buffer[i] == 'H' && RX_buffer[i + 1] == 'H')
            {
                shishishidu[0] = RX_buffer[i + 3];
                shishishidu[1] = RX_buffer[i + 4];
            }
            if (RX_buffer[i] == 't' && RX_buffer[i + 1] == 'e' && RX_buffer[i + 4] == '2')
            {
                month[0] = RX_buffer[i + 9];
                month[1] = RX_buffer[i + 10];
                day[0] = RX_buffer[i + 12];
                day[1] = RX_buffer[i + 13];
            }
        }
				memset(RX_buffer, 0, 1500);
        OLED_ShowString(0, 0, "2021", 16); // 2021
        OLED_ShowCHinese(32, 0, 0);        //��
        OLED_ShowString(48, 0, month, 16); // 05
        OLED_ShowCHinese(64, 0, 1);        //��
        OLED_ShowString(80, 0, day, 16);   // 13
        OLED_ShowCHinese(96, 0, 2);        //��

        OLED_ShowCHinese(0, 2, 3); /*������ͨ*/
        OLED_ShowCHinese(16, 2, 4);
        OLED_ShowCHinese(32, 2, 5);
        OLED_ShowCHinese(48, 2, 6);
        OLED_ShowString(80, 2, wendu, 16);
        OLED_ShowString(96, 2, "`C", 16);

        OLED_ShowCHinese(0, 4, 7); /*�����¶�*/
        OLED_ShowCHinese(16, 4, 8);
        OLED_ShowCHinese(32, 4, 9);
        OLED_ShowCHinese(48, 4, 10);
        OLED_ShowString(80, 4, shishiwendu, 16);
        OLED_ShowString(96, 4, "`C", 16);

        OLED_ShowCHinese(0, 6, 7); /*����ʪ��*/
        OLED_ShowCHinese(16, 6, 8);
        OLED_ShowCHinese(32, 6, 13);
        OLED_ShowCHinese(48, 6, 14);
        OLED_ShowString(80, 6, shishishidu, 16);
        OLED_ShowString(96, 6, "%", 16);
    }
}
