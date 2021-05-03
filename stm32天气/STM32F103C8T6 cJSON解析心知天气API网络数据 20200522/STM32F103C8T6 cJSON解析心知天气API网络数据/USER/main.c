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
    
    str_json = cJSON_Parse(strArr);   //创建JSON解析对象，返回JSON格式是否正确
    if (!str_json)
    {
        printf("JSON格式错误:%s \r\n", cJSON_GetErrorPtr()); //输出json格式错误信息
    }
    else
    {
        printf("JSON格式正确:\n%s \r\n",cJSON_Print(str_json) );
        str_name = cJSON_GetObjectItem(str_json, "name"); //获取name键对应的值的信息
        if (str_name->type == cJSON_String)
        {
            printf("姓名:%s \r\n", str_name->valuestring);
        }
        str_age = cJSON_GetObjectItem(str_json, "age");   //获取age键对应的值的信息
        if(str_age->type==cJSON_Number)
        {
            printf("年龄:%d \r\n", str_age->valueint);
        }
        cJSON_Delete(str_json);    //释放内存
    }
}

//子对象1结构体--Location
typedef struct
{
	char id[32];
	char name[32];
	char country[32];
	char path[64];
	char timezone[32];
	char timezone_offset[32];
}Location;
 
//子对象2结构体--Now
typedef struct
{
	char text[32];
	char code[32];
	char temperature[32];
}Now;
 
//用于保存服务器返回的天气数据
typedef struct
{
	Location location;		//子对象1
	Now now;				//子对象2
	char last_update[64];	//子对象3
}Results;


/*********************************************************************************
* Function Name    ： cJSON_WeatherParse,解析天气数据
* Parameter		   ： JSON：天气数据包  results：保存解析后得到的有用的数据
* Return Value     ： 0：成功 其他:错误
* Function Explain ： 
* Create Date      ： 2017.12.6 by lzn
**********************************************************************************/
int cJSON_WeatherParse(char *JSON, Results *results)
{
	cJSON *json,*arrayItem,*object,*subobject,*item;
	
	json = cJSON_Parse(JSON); //解析JSON数据包
	if(json == NULL)		  //检测JSON数据包是否存在语法上的错误，返回NULL表示数据包无效
	{
		printf("Error before: [%s] \r\n",cJSON_GetErrorPtr()); //打印数据包语法错误的位置
		return 1;
	}
	else
	{
		if((arrayItem = cJSON_GetObjectItem(json,"results")) != NULL); //匹配字符串"results",获取数组内容
		{
			int size = cJSON_GetArraySize(arrayItem);     //获取数组中对象个数
			printf("cJSON_GetArraySize: size=%d \r\n",size); 
			
			if((object = cJSON_GetArrayItem(arrayItem,0)) != NULL)//获取父对象内容
			{
				/* 匹配子对象1 */
				if((subobject = cJSON_GetObjectItem(object,"location")) != NULL)
				{
					printf("---------------------------------subobject1-------------------------------\r\n");
					if((item = cJSON_GetObjectItem(subobject,"id")) != NULL)   //匹配子对象1成员"id"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].location.id,item->valuestring,strlen(item->valuestring));
					}
					if((item = cJSON_GetObjectItem(subobject,"name")) != NULL) //匹配子对象1成员"name"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].location.name,item->valuestring,strlen(item->valuestring));
					}
					if((item = cJSON_GetObjectItem(subobject,"country")) != NULL)//匹配子对象1成员"country"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].location.country,item->valuestring,strlen(item->valuestring));
					}
					if((item = cJSON_GetObjectItem(subobject,"path")) != NULL)  //匹配子对象1成员"path"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].location.path,item->valuestring,strlen(item->valuestring));
					}
					if((item = cJSON_GetObjectItem(subobject,"timezone")) != NULL)//匹配子对象1成员"timezone"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].location.timezone,item->valuestring,strlen(item->valuestring));
					}
					if((item = cJSON_GetObjectItem(subobject,"timezone_offset")) != NULL)//匹配子对象1成员"timezone_offset"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].location.timezone_offset,item->valuestring,strlen(item->valuestring));
					}
				}
				/* 匹配子对象2 */
				if((subobject = cJSON_GetObjectItem(object,"now")) != NULL)
				{
					printf("---------------------------------subobject2-------------------------------\r\n");
					if((item = cJSON_GetObjectItem(subobject,"text")) != NULL)//匹配子对象2成员"text"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].now.text,item->valuestring,strlen(item->valuestring));
					}
					if((item = cJSON_GetObjectItem(subobject,"code")) != NULL)//匹配子对象2成员"code"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].now.code,item->valuestring,strlen(item->valuestring));
					}
					if((item = cJSON_GetObjectItem(subobject,"temperature")) != NULL) //匹配子对象2成员"temperature"
					{
						printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",item->type,item->string,item->valuestring);
						memcpy(results[0].now.temperature,item->valuestring,strlen(item->valuestring));
					}
				}
				/* 匹配子对象3 */
				if((subobject = cJSON_GetObjectItem(object,"last_update")) != NULL)
				{
					printf("---------------------------------subobject3-------------------------------\r\n");
					printf("cJSON_GetObjectItem: type=%d, string is %s,valuestring=%s \r\n",subobject->type,subobject->string,subobject->valuestring);
					memcpy(results[0].last_update,item->valuestring,strlen(subobject->valuestring));
				}
			} 
		}
	}
	
	cJSON_Delete(json); //释放cJSON_Parse()分配出来的内存空间
	
	return 0;
}


int main(void)  
{ 
	u16 uart1Len;
	Results results[] = {{0}};
	u8 dtOLEDBuf[16];   			//OLED缓存器
	//初始化
	//延时函数初始化 	 
	delay_init();
				  
	uart_init(115200);	 			//串口1:Debug,初始化为115200 
	
	OLED_Init();
	
	OLED_ShowString(0,4,(u8 *)" 0.96 OLED Demo ");   
     
	
	while(1) 
	{
		//串口1收到的信息
		if(USART_RX_STA&0x8000)
		{ 
			uart1Len=USART_RX_STA&0x3f;            			//得到此次接收到的数据长度   
			
			cJSON_WeatherParse(USART_RX_BUF, results);		//解析天气数据
			
			//打印结构体内内容
			printf("打印结构体内内容如下： \r\n");
			printf("%s \r\n",results[0].now.text);
			printf("%s \r\n",results[0].now.temperature);
			
			//清屏，重新显示屏幕内容
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
			memset(USART_RX_BUF, 0, sizeof(USART_RX_BUF));                          //清空数组  
		}
        
        delay_ms(10); 
	}  
}
