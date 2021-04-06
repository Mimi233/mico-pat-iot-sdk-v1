/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ��������ʵ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
#include "stm32f10x.h"
#include "./usart/bsp_usart.h"	
#include "./lcd/bsp_ili9341_lcd.h"
#include "./lcd/bsp_xpt2046_lcd.h"
#include "./flash/bsp_spi_flash.h"
#include "./led/bsp_led.h" 
#include "palette.h"
#include <string.h>
#include "mcu_api.h"
#include "protocol.h"
#include "system.h"
#include "wifi.h"
#include "concrol.h"
#include "dht11.h"
#include "delay.h"
#include "ws2812.h"
extern int MANUAL_FEED_NUM;
char dispBuff[100],tempbuff[20],humbuf[20];
extern int MANUAL_FEED_SUM;
	u8 temperature;  	    
	u8 humidity; 
int8_t i=0;	
const char s[5];
int main(void)
{		
	
	ILI9341_Init(); //LCD ��ʼ�� 
	XPT2046_Init();	//��������ʼ��
	Calibrate_or_Get_TouchParaWithFlash(3,0);//��FLASH���ȡУ����������FLASH�޲�������ʹ��ģʽ3����У��
	delay_init();	
	USART_Config();  /* USART config */
	LED_GPIO_Config();
	EXTIX_Init();      //�ⲿ�жϳ�ʼ��
	ILI9341_GramScan ( 3 );		
	Palette_Init(LCD_SCAN_MODE);//���ƴ����������
	wifi_protocol_init();
	GPIO_CONFIG();		
	LCD_SetFont(&Font8x16);	
	LCD_SetColors(RED,BLACK);
	sprintf(dispBuff,"�ֶ�Ͷι���� %d ",MANUAL_FEED_NUM);
	ILI9341_DispString_EN_CH(2*48,2*48,dispBuff);
	ILI9341_DisplayStringEx(2*48,0*48,16,16,(uint8_t *)"���������ߣ�����",0);	
	DHT11_Init();
//	ws281x_init();
	while ( 1 )
	{	
//		if(i == 0)
//		{
////			ws281x_rainbowCycle(0);
//			ws281x_colorWipe(ws281x_color(0, 255, 0), 50); // Green
//			ws281x_colorWipe(ws281x_color(0, 0, 255), 50); // Blue
//			i=1;
//		}	
 


		wifi_uart_service();//�������
		//������⺯��������������10ms����һ��
		XPT2046_TouchEvenHandler();
		DHT11_Read_Data(&temperature,&humidity);	//��ȡ��ʪ��ֵ	
		LCD_SetFont(&Font8x16);	
		LCD_SetColors(RED,BLACK);
		sprintf(dispBuff,"��ιʳ���� %d ",MANUAL_FEED_SUM);
		ILI9341_DispString_EN_CH(2*48,1*48,dispBuff);

		sprintf(humbuf,"ʪ�ȣ� %d ",humidity);
		ILI9341_DispString_EN_CH(4*48,4*48,humbuf);
		mcu_dp_value_update(DPID_HUMBUF,(long)humidity);

		sprintf(tempbuff,"�¶ȣ� %d ",temperature);
		ILI9341_DispString_EN_CH(2*48,4*48,tempbuff);  
		mcu_dp_value_update(DPID_TEMPERATURE,(long)temperature); 
		get_wifi_status(mcu_get_wifi_work_state());

	}
		
}





/* ------------------------------------------end of file---------------------------------------- */

