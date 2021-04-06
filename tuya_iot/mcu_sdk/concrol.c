#include "concrol.h"
#include "./lcd/bsp_ili9341_lcd.h"
#include <string.h>
#include "wifi.h"
uint32_t delay_time = 0;
extern unsigned char feed_plan[5];
extern uint16_t TIM_NUM;
extern uint8_t MANUAL_FEED_FLAG;
extern char dispBuff[100];
int MANUAL_FEED_NUM = 0;
int MANUAL_FEED_SUM = 0;//总喂食量
void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}

void GPIO_CONFIG(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// 打开串口GPIO的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void motor_concrol_right(uint8_t tim)//电机正转延时后停止
{
	MANUAL_FEED_NUM = tim;
	LCD_SetFont(&Font8x16);	
	LCD_SetColors(RED,BLACK);
	sprintf(dispBuff,"手动投喂量： %d ",MANUAL_FEED_NUM);
	ILI9341_DispString_EN_CH(2*48,2*48,dispBuff);
	
	GPIO_SetBits(PWM_PORT,PWM2_GPIO);
	GPIO_ResetBits(PWM_PORT,PWM1_GPIO);
	Delay(10000000*tim);

	GPIO_ResetBits(PWM_PORT,PWM1_GPIO);
	GPIO_ResetBits(PWM_PORT,PWM2_GPIO);
	MANUAL_FEED_SUM = MANUAL_FEED_SUM+MANUAL_FEED_NUM;
	
}
void MEAL_PLAN(unsigned char value[])
{
//	for(int t;t<5;t++)//提取value值
//	{
//		feed_plan[t] = value[t];
//	}
	
}
