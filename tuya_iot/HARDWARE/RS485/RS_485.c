#include "RS_485.h"
#include "stm32f0xx.h"
#include "stdio.h"
#include "mcu_api.h"
#include "protocol.h"
#include "system.h"
#include "wifi.h"

uint8_t USART2_TX_BUF[11] = {0x1A,0x00,0x00,0x00,0x00,0x11,0x00,0x00,0x00,0x00,0x0B}; //发送数据缓冲，最大为USART2_MAX_SEND_LEN个字节

/*串口初始化配置 */
void USART_Config(void)
{
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	/*初始化USART1时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_InitStructure.USART_BaudRate = 2500000;//设置串口波特率
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//设置流控制
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;//设置工作模式
	USART_InitStructure.USART_Parity = USART_Parity_No;//设置效验位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//设置停止位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//设置数据位
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);//使能串口 1	

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
  
	NVIC_Init(&NVIC_InitStructure);	//初始化VIC寄存器
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  //开启中断
	
}


uint8_t UART_Recive(void)
{
	while(!(USART1->ISR & (1<<5)));
	return(USART1->RDR);
}

/*发送 1 字节数据*/
void UART_send_byte(uint8_t byte)
{
	while(!((USART1->ISR)&(1<<7)));//等待发送完
	USART1->TDR=byte; //发送一个字节
}

/*
	RS485发送
*/
void RS_485_send(void){
		uint8_t i;
		GPIO_SetBits(GPIOA, GPIO_Pin_8);//设置为发送模式
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
		for(i=0;i<11;i++)
	{
		UART_send_byte( USART2_TX_BUF[i]);//串口接收回显
	}		
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);

		GPIO_ResetBits(GPIOA, GPIO_Pin_8);			//接收模式	
}
/*
	RS485发送
*/
void RS_485_send_test(){
		uint8_t i;
		GPIO_SetBits(GPIOA, GPIO_Pin_8);//设置为发送模式
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
		for(i=0;i<1;i++)
	{
//		UART_send_byte( USART2_TX_BUF[i]);//串口接收回显
		UART_send_byte(0x02);//串口接收回显
	}		
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);

		GPIO_ResetBits(GPIOA, GPIO_Pin_8);			//接收模式	
}

//串口1中断服务函数
void USART1_IRQHandler(void)  
{
	uint8_t Res;
	//处理接收到的数据

	if(USART_GetITStatus(USART1, USART_IT_RXNE))

	{
		Res =UART_Recive();//读取串口接收到的数据
		uart_receive_input(Res);	
	}	
	/* 清除串口接收标志位 */
	USART_ClearFlag(USART1,USART_FLAG_RXNE);
//	GPIO_ResetBits(GPIOA, GPIO_Pin_8);			//485接收模式
	}


/*GPIOA初始化配置 */
void GPIOA_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*初始化GPIOA时钟*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_1);
	/* 配置PA9 ,PA10*/
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //设置端口复用
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);//初始化GPIOA8为低电平

}

