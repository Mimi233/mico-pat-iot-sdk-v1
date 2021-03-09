#include "RS_485.h"
#include "stm32f0xx.h"
#include "stdio.h"
#include "mcu_api.h"
#include "protocol.h"
#include "system.h"
#include "wifi.h"

uint8_t USART2_TX_BUF[11] = {0x1A,0x00,0x00,0x00,0x00,0x11,0x00,0x00,0x00,0x00,0x0B}; //�������ݻ��壬���ΪUSART2_MAX_SEND_LEN���ֽ�

/*���ڳ�ʼ������ */
void USART_Config(void)
{
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	/*��ʼ��USART1ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_InitStructure.USART_BaudRate = 2500000;//���ô��ڲ�����
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//����������
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;//���ù���ģʽ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����Ч��λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//����ֹͣλ
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//��������λ
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);//ʹ�ܴ��� 1	

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
  
	NVIC_Init(&NVIC_InitStructure);	//��ʼ��VIC�Ĵ���
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  //�����ж�
	
}


uint8_t UART_Recive(void)
{
	while(!(USART1->ISR & (1<<5)));
	return(USART1->RDR);
}

/*���� 1 �ֽ�����*/
void UART_send_byte(uint8_t byte)
{
	while(!((USART1->ISR)&(1<<7)));//�ȴ�������
	USART1->TDR=byte; //����һ���ֽ�
}

/*
	RS485����
*/
void RS_485_send(void){
		uint8_t i;
		GPIO_SetBits(GPIOA, GPIO_Pin_8);//����Ϊ����ģʽ
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
		for(i=0;i<11;i++)
	{
		UART_send_byte( USART2_TX_BUF[i]);//���ڽ��ջ���
	}		
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);

		GPIO_ResetBits(GPIOA, GPIO_Pin_8);			//����ģʽ	
}
/*
	RS485����
*/
void RS_485_send_test(){
		uint8_t i;
		GPIO_SetBits(GPIOA, GPIO_Pin_8);//����Ϊ����ģʽ
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
		for(i=0;i<1;i++)
	{
//		UART_send_byte( USART2_TX_BUF[i]);//���ڽ��ջ���
		UART_send_byte(0x02);//���ڽ��ջ���
	}		
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);

		GPIO_ResetBits(GPIOA, GPIO_Pin_8);			//����ģʽ	
}

//����1�жϷ�����
void USART1_IRQHandler(void)  
{
	uint8_t Res;
	//������յ�������

	if(USART_GetITStatus(USART1, USART_IT_RXNE))

	{
		Res =UART_Recive();//��ȡ���ڽ��յ�������
		uart_receive_input(Res);	
	}	
	/* ������ڽ��ձ�־λ */
	USART_ClearFlag(USART1,USART_FLAG_RXNE);
//	GPIO_ResetBits(GPIOA, GPIO_Pin_8);			//485����ģʽ
	}


/*GPIOA��ʼ������ */
void GPIOA_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*��ʼ��GPIOAʱ��*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_1);
	/* ����PA9 ,PA10*/
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //���ö˿ڸ���
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
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);//��ʼ��GPIOA8Ϊ�͵�ƽ

}

