#include "stm32f0xx.h"
#ifndef __RS_485_H
#define __RS_485_H

#define TX_485 GPIO_SetBits(GPIOA,GPIO_Pin_8) ¡¡¡¡//high level, transmitter input
#define RX_485 GPIO_ResetBits(GPIOA,GPIO_Pin_8)	


void USART_Config(void);
void GPIOA_Config(void);
void RS_485_send(void);
void RS_485_send_test(void);
void UART_send_byte(uint8_t byte);
#endif /*__RS_485_H*/
