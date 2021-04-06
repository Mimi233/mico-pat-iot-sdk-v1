#include "stm32f10x.h"
#ifndef __CONCROL_H
#define __CONCROL_H

#define PWM_PORT GPIOA
#define LED_PORT GPIOA

#define LED_GPIO  GPIO_Pin_0
#define PWM1_GPIO GPIO_Pin_2
#define PWM2_GPIO GPIO_Pin_3

#define PWM1_L GPIO_SetBits(PWM_PORT,PWM1_GPIO) ����
#define PWM1_H GPIO_ResetBits(PWM_PORT,PWM1_GPIO)	//high level, transmitter input
#define PWM2_L GPIO_SetBits(PWM_PORT,PWM2_GPIO) ��
#define PWM2_H GPIO_ResetBits(PWM_PORT,PWM2_GPIO)	��//high level, transmitter input
#define LED_0N GPIO_ResetBits(LED_PORT,LED_GPIO)//LED��
#define LED_0FF GPIO_SetBits(LED_PORT,LED_GPIO)//LED��

void GPIO_CONFIG(void);
void motor_concrol_right(uint8_t tim);//�����ת��ʱ��ֹͣ
void Delay(__IO uint32_t nCount);	 //�򵥵���ʱ����
#endif /*__CONCROL_H*/
