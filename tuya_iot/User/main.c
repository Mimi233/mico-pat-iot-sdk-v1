#include "stm32f0xx.h"
#include "stdio.h"
#include "RS_485.h"
#include "timer.h"
#include "mcu_api.h"
#include "protocol.h"
#include "system.h"
#include "wifi.h"
#define countof(a) (sizeof(a) / sizeof(*(a)))//计算数组内的成员个数

//如果想串口中断接收，请不要注释以下宏定义
#define EN_USART2_RX 	1			//0,不接收;1,接收.

void Delay(uint32_t temp)
{
	for(; temp!= 0; temp--);
}
uint32_t  fac_us=0;	


void delay_init()
{

	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	fac_us=SystemCoreClock/8000000;				//为系统时钟的1/8  

}								    


void delay_us(uint32_t nus)
{		
	uint32_t temp;	    	 
	SysTick->LOAD=nus*fac_us; 					//时间加载	  		 
	SysTick->VAL=0x00;        					//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;      					 //清空计数器	 
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
//	RCC_GetClocksFreq(&get_rcc_clock);  //仿真的时候查看结构体get_rcc_clock中可以看见各个外设的时钟
    while(1)
    {
		wifi_uart_service();
    }
}
