#include "stm32f10x.h"  
#include "delay.h"
#include "usart.h" 

#include "oled.h"

#include "cJSON.h"

void ParseStrDemo(void)
{
    char strArr[] = "{\"name\":\"Andy\",\"age\":20}";
    cJSON *str_json, *str_name, *str_age;
    
    printf("strArr[]:%s \r\n",strArr);
    
    str_json = cJSON_Parse(strArr);   //����JSON�������󣬷���JSON��ʽ�Ƿ���ȷ
    if (!str_json)
    {
        printf("JSON��ʽ����:%s \r\n", cJSON_GetErrorPtr()); //���json��ʽ������Ϣ
    }
    else
    {
        printf("JSON��ʽ��ȷ:\n%s \r\n",cJSON_Print(str_json) );
        str_name = cJSON_GetObjectItem(str_json, "name"); //��ȡname����Ӧ��ֵ����Ϣ
        if (str_name->type == cJSON_String)
        {
            printf("����:%s \r\n", str_name->valuestring);
        }
        str_age = cJSON_GetObjectItem(str_json, "age");   //��ȡage����Ӧ��ֵ����Ϣ
        if(str_age->type==cJSON_Number)
        {
            printf("����:%d \r\n", str_age->valueint);
        }
        cJSON_Delete(str_json);    //�ͷ��ڴ�
    }
}

//�Ӷ���1�ṹ��--Location
typedef struct
{
	char id[32];
	char name[32];
	char country[32];
	char path[64];
	char timezone[32];
	char timezone_offset[32];
}Location;
 
//�Ӷ���2�ṹ��--Now
typedef struct
{
	char text[32];
	char code[32];
	char temperature[32];
}Now;
 
//���ڱ�����������ص���������
typedef struct
{
	Location location;		//�Ӷ���1
	Now now;				//�Ӷ���2
	char last_update[64];	//�Ӷ���3
}Results;


/*********************************************************************************
* Function Name    �� cJSON_WeatherParse,������������
* Parameter		   �� JSON���������ݰ�  results�����������õ������õ�����
* Return Value     �� 0���ɹ� ����:����
* Function Explain �� 
* Create Date      �� 2017.12.6 by lzn
**********************************************************************************/
int cJSON_WeatherParse(char *JSON, Results *results)
{
	cJSON *json,*arrayItem,*object,*subobject,*item;
	
	json = cJSON_Parse(JSON); //����JSON���ݰ�
	if(json == NULL)		  //���JSON���ݰ��Ƿ�����﷨�ϵĴ��󣬷���NULL��ʾ���ݰ���Ч
	{
		printf("Error before: [%s] \r\n",cJSON_GetErrorPtr()); //��ӡ���ݰ��﷨�����λ��
		return 1;
	}
	else
	{
		if((arrayItem = cJSON_GetObjectItem(json,"results")) != NULL); //ƥ���ַ���"results",��ȡ��������
		{
			int size = cJSON_GetArraySize(arrayItem);     //��ȡ�����ж������
			printf("cJSON_GetArraySize: size=%d \r\n",size); 
			
			if((object = cJSON_GetArrayItem(arrayItem,0)) != NULL)//��ȡ����������
			{
				/* ƥ���Ӷ���1 */
				if((subobject = cJSON_GetObjectItem(object,"location")) != NULL)
				{
					printf("---------------------------------subobject1-------------------------------\r\n");
					if((item = cJSON_GetObjectItem(subobject,"id")) != NULL)   //ƥ���Ӷ���1��Ա"id"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].location.id,item->valuestring,strlen(item->valuestring));
					}
					if((item = cJSON_GetObjectItem(subobject,"name")) != NULL) //ƥ���Ӷ���1��Ա"name"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].location.name,item->valuestring,strlen(item->valuestring));
					}
					if((item = cJSON_GetObjectItem(subobject,"country")) != NULL)//ƥ���Ӷ���1��Ա"country"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].location.country,item->valuestring,strlen(item->valuestring));
					}
					if((item = cJSON_GetObjectItem(subobject,"path")) != NULL)  //ƥ���Ӷ���1��Ա"path"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].location.path,item->valuestring,strlen(item->valuestring));
					}
					if((item = cJSON_GetObjectItem(subobject,"timezone")) != NULL)//ƥ���Ӷ���1��Ա"timezone"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].location.timezone,item->valuestring,strlen(item->valuestring));
					}
					if((item = cJSON_GetObjectItem(subobject,"timezone_offset")) != NULL)//ƥ���Ӷ���1��Ա"timezone_offset"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].location.timezone_offset,item->valuestring,strlen(item->valuestring));
					}
				}
				/* ƥ���Ӷ���2 */
				if((subobject = cJSON_GetObjectItem(object,"now")) != NULL)
				{
					printf("---------------------------------subobject2-------------------------------\r\n");
					if((item = cJSON_GetObjectItem(subobject,"text")) != NULL)//ƥ���Ӷ���2��Ա"text"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].now.text,item->valuestring,strlen(item->valuestring));
					}
					if((item = cJSON_GetObjectItem(subobject,"code")) != NULL)//ƥ���Ӷ���2��Ա"code"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].now.code,item->valuestring,strlen(item->valuestring));
					}
					if((item = cJSON_GetObjectItem(subobject,"temperature")) != NULL) //ƥ���Ӷ���2��Ա"temperature"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].now.temperature,item->valuestring,strlen(item->valuestring));
					}
				}
				/* ƥ���Ӷ���3 */
				if((subobject = cJSON_GetObjectItem(object,"last_update")) != NULL)
				{
					printf("---------------------------------subobject3-------------------------------\r\n");
					printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",subobject->type,subobject->string,subobject->valuestring);
					memcpy(results[0].last_update,item->valuestring,strlen(subobject->valuestring));
				}
			} 
		}
	}
	
	cJSON_Delete(json); //�ͷ�cJSON_Parse()����������ڴ�ռ�
	
	return 0;
}


int main(void)  
{ 
	u16 uart1Len;
	Results results[] = {{0}};
	u8 dtOLEDBuf[16];   			//OLED������
	//��ʼ��
	//��ʱ������ʼ�� 	 
	delay_init();
				  
	uart_init(115200);	 			//����1:Debug,��ʼ��Ϊ115200 
	
	OLED_Init();
	
	OLED_ShowString(0,4,(u8 *)" 0.96 OLED Demo ");   
     
	
	while(1) 
	{
		//����1�յ�����Ϣ
		if(USART_RX_STA&0x8000)
		{ 
			uart1Len=USART_RX_STA&0x3f;            			//�õ��˴ν��յ������ݳ���   
			
			cJSON_WeatherParse(USART_RX_BUF, results);		//������������
			
			//��ӡ�ṹ��������
			printf("��ӡ�ṹ�����������£� \r\n");
			printf("%s \r\n",results[0].now.text);
			printf("%s \r\n",results[0].now.temperature);
			
			//������������ʾ��Ļ����
			OLED_Clear();
			memset(dtOLEDBuf, 0, sizeof(dtOLEDBuf));
			sprintf((char *)dtOLEDBuf,"Weather:%s",results[0].now.text);
			//OLED_ShowString(0,0,(u8 *)dtOLEDBuf);	
			OLED_ShowStr(0,2,(u8 *)dtOLEDBuf, 2);
			memset(dtOLEDBuf, 0, sizeof(dtOLEDBuf));
			sprintf((char *)dtOLEDBuf,"Temperature:%s",results[0].now.temperature);
			//OLED_ShowString(0,4,(u8 *)dtOLEDBuf);	
			OLED_ShowStr(0,6,(u8 *)dtOLEDBuf, 2);
			
			
			USART_RX_STA=0;   
			memset(USART_RX_BUF, 0, sizeof(USART_RX_BUF));                          //�������  
		}
        
        delay_ms(10); 
	}  
}
