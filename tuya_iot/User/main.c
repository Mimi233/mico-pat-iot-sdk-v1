#include "stm32f0xx.h"
#include "stdio.h"
#include "RS_485.h"
#include "timer.h"
#include "mcu_api.h"
#include "protocol.h"
#include "system.h"
#include "wifi.h"
#define countof(a) (sizeof(a) / sizeof(*(a)))//���������ڵĳ�Ա����

//����봮���жϽ��գ��벻Ҫע�����º궨��
#define EN_USART2_RX 	1			//0,������;1,����.

void Delay(uint32_t temp)
{
	for(; temp!= 0; temp--);
}
uint32_t  fac_us=0;	


void delay_init()
{

	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
	fac_us=SystemCoreClock/8000000;				//Ϊϵͳʱ�ӵ�1/8  

}								    


void delay_us(uint32_t nus)
{		
	uint32_t temp;	    	 
	SysTick->LOAD=nus*fac_us; 					//ʱ�����	  		 
	SysTick->VAL=0x00;        					//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL =0X00;      					 //��ռ�����	 
}


int main(void)
{
//	RCC_ClocksTypeDef get_rcc_clock; 
	GPIOA_Config();
	USART_Config();
	delay_init();
	SystemInit();
	wifi_protocol_init();
//	Systick_Init();
//	RCC_GetClocksFreq(&get_rcc_clock);  //�����ʱ��鿴�ṹ��get_rcc_clock�п��Կ������������ʱ��
    while(1)
    {
		wifi_uart_service();
    }
}
