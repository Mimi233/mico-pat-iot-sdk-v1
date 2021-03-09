#ifndef __TIMER_H
#define __TIMER_H

#include "core_cm0.h"
#include "stm32f0xx.h"

void Systick_Init(void);
void Delay_ms(__IO uint32_t nTime);
void TimingDelay_Decrement(void);
#endif /*__TIMER_H*/


