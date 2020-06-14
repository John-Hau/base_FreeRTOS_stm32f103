 /**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ���� 8M����flash���ԣ�����������Ϣͨ������1�ڵ��Եĳ����ն��д�ӡ����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-MINI STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./led/bsp_led.h"
#include "./i2c/bsp_i2c_ee.h"

#include "./systick/bsp_SysTick.h"
#include "./dht11/bsp_dht11.h"
#include "./rtc/bsp_rtc.h"

#include "./flash/bsp_spi_flash.h"


typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;

/* ��ȡ�������ĳ��� */
#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define RxBufferSize1   (countof(TxBuffer1) - 1)
#define countof(a)      (sizeof(a) / sizeof(*(a)))
#define  BufferSize (countof(Tx_Buffer)-1)

#define  FLASH_WriteAddress     0x00000
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress

     

/* ���ͻ�������ʼ�� */
uint8_t Tx_Buffer[] = "��л��ѡ��Ұ��stm32������\r\n";
uint8_t Rx_Buffer[BufferSize];

__IO uint32_t DeviceID = 0;
__IO uint32_t FlashID = 0;
__IO TestStatus TransferStatus1 = FAILED;

// ����ԭ������
void Delay(__IO uint32_t nCount);
TestStatus Buffercmp(uint8_t* pBuffer1,uint8_t* pBuffer2, uint16_t BufferLength);

/*
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����
 */
 
 
 int8_t tstr[]="hello";	
 
 
 uint32_t rt_cnt=0;
 
 
 
 
 
 // N = 2^32/365/24/60/60 = 136 ��

/*ʱ��ṹ�壬Ĭ��ʱ��2000-01-01 00:00:00*/
struct rtc_time systmtime=
{
0,0,0,1,1,2000,0
};

extern __IO uint32_t TimeDisplay ;

 
 
 
 
 
 
 
int main(void)
{ 	
	
		DHT11_Data_TypeDef DHT11_Data;
	LED_GPIO_Config();
	
	/* ���ô���Ϊ��115200 8-N-1 */
	USART_Config();
	//printf("\r\n ����һ��8Mbyte����flash(W25Q64)ʵ�� \r\n");
	printf("\r\nOLED DHT11 USART W25Q64\r\n");
	//=================================================================
#if  1
	i2c_CfgGpio();
	
	
		Initial_LY096BG30();
	
	
	
	fill_picture(0x00);
	oled_096_print(0, 0, tstr);
	oled_096_print(1, 1, tstr);
	oled_096_print(2, 2, tstr);
	
	oled_096_print(3, 3, tstr);
	oled_096_print(4, 4, tstr);
	oled_096_print(5, 5, tstr);
	
	oled_096_print(6, 6, tstr);
	oled_096_print(6, 7, tstr);
	
	
	/* ����SysTick Ϊ1us�ж�һ�� */
	SysTick_Init();
	
		/*��ʼ��DTT11������*/
	DHT11_Init();
	
	
	

	
	
#endif
//===================================================================================	
	
	
	
			/* ����RTC���ж����ȼ� */
	  RTC_NVIC_Config();
	  RTC_CheckAndConfig(&systmtime);
	
	

	
	
	/* 8M����flash W25Q64��ʼ�� */
	SPI_FLASH_Init();
	
	/* ��ȡ Flash Device ID */
	DeviceID = SPI_FLASH_ReadDeviceID();	
	Delay( 200 );
	
	/* ��ȡ SPI Flash ID */
	FlashID = SPI_FLASH_ReadID();	
	printf("\r\n FlashID is 0x%X,\
	Manufacturer Device ID is 0x%X\r\n", FlashID, DeviceID);
	
	/* ���� SPI Flash ID */
	if (FlashID == sFLASH_ID)
	{	
		printf("\r\n get W25Q64\r\n");
		
		/* ������Ҫд��� SPI FLASH ������FLASHд��ǰҪ�Ȳ��� */
		// �������4K����һ����������������С��λ������
		SPI_FLASH_SectorErase(FLASH_SectorToErase);	 	 
		
		/* �����ͻ�����������д��flash�� */
		// ����дһҳ��һҳ�Ĵ�СΪ256���ֽ�
		SPI_FLASH_BufferWrite(Tx_Buffer, FLASH_WriteAddress, BufferSize);		
		printf("\r\n write data %s \r\t", Tx_Buffer);
		
		/* ���ո�д������ݶ������ŵ����ջ������� */
		SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);
		printf("\r\n read data %s \r\n", Rx_Buffer);
		
		/* ���д�������������������Ƿ���� */
		TransferStatus1 = Buffercmp(Tx_Buffer, Rx_Buffer, BufferSize);
		
		if( PASSED == TransferStatus1 )
		{ 
			//LED2_ON;
			printf("\r\n test W25Q64 ok\n\r");
		}
		else
		{        
			//LED1_ON;
			printf("\r\n test W25Q64 error\n\r");
		}
	}// if (FlashID == sFLASH_ID)
	else// if (FlashID == sFLASH_ID)
	{ 
		LED1_ON;
		printf("\r\ncan not get W25Q64 ID!\n\r");
	}
	
	while(1)
	{	
		
		  /* ÿ��1s ����һ��ʱ��*/
	    if (TimeDisplay == 1)
			//if(1)
	    {
				/* ��ǰʱ�� */
	      Time_Display( RTC_GetCounter(),&systmtime); 		  
	      TimeDisplay = 0;
				
				
				
				
				
				rt_cnt++;
				
				if(rt_cnt%5 ==0)
				{
				
							/*����DHT11_Read_TempAndHumidity��ȡ��ʪ�ȣ����ɹ����������Ϣ*/
							if( DHT11_Read_TempAndHumidity ( & DHT11_Data ) == SUCCESS)
							{
								printf("\r\nread dht11 ok \r\n\r\nRH is %d.%d ��RH, T is %d.%d�� \r\n",\
								DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
							}			
							else
							{
								printf("Read DHT11 ERROR!\r\n");
							}
				
				
				}
				

				
	    }
			
			

			
			
			
			
			
			
			
			
			
			//���°�����ͨ�������޸�ʱ��
			//if( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON  )
			if(0)
			{
				struct rtc_time set_time;

				/*ʹ�ô��ڽ������õ�ʱ�䣬��������ʱע��ĩβҪ�ӻس�*/
				Time_Regulate_Get(&set_time);
				/*�ý��յ���ʱ������RTC*/
				Time_Adjust(&set_time);
				
				//�򱸷ݼĴ���д���־
				BKP_WriteBackupRegister(RTC_BKP_DRX, RTC_BKP_DATA);

			} 
		
		
			
			
#if 0
			
	/*����DHT11_Read_TempAndHumidity��ȡ��ʪ�ȣ����ɹ����������Ϣ*/
			if( DHT11_Read_TempAndHumidity ( & DHT11_Data ) == SUCCESS)
			{
				printf("\r\nread dht11 ok \r\n\r\nRH is %d.%d ��RH, T is %d.%d�� \r\n",\
				DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
			}			
			else
			{
				printf("Read DHT11 ERROR!\r\n");
			}

		 Delay_ms(5000);
			
#endif
			
			
			
	}
}

/*
 * ��������Buffercmp
 * ����  ���Ƚ������������е������Ƿ����
 * ����  ��-pBuffer1     src������ָ��
 *         -pBuffer2     dst������ָ��
 *         -BufferLength ����������
 * ���  ����
 * ����  ��-PASSED pBuffer1 ����   pBuffer2
 *         -FAILED pBuffer1 ��ͬ�� pBuffer2
 */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }

    pBuffer1++;
    pBuffer2++;
  }
  return PASSED;
}

void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/
