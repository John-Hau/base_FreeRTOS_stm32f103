#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "bsp_led.h"   

void LED_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_APB2PeriphClockCmd( LED1_GPIO_CLK | LED2_GPIO_CLK , ENABLE);
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;	

		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);	
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);		

		/* �ر�����led��	*/
		GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);
		
		/* �ر�����led��	*/
		GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);
}


void LED1_Task(void *para)
{

	while(1)
	{
		LED1(0);//LED1_ON();
		vTaskDelay(500);
		LED1(1);//LED1_OFF();
		vTaskDelay(500);
	}
	
	
}



#if 1
void LED2_Task(void *para)
{

	while(1)
	{
		LED2(0);//LED2_ON();
		vTaskDelay(500);
		LED2(1);//LED2_OFF();
		vTaskDelay(500);
	}
	
	
}

#endif

/*********************************************END OF FILE**********************/
