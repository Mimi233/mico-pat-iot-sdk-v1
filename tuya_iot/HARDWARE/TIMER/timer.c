#include "timer.h"
#include "core_cm0.h"
#include "stm32f0xx_misc.h"

static __IO uint32_t TimingDelay;

void Delay_ms(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

void Systick_Init(void)
{
  if (SysTick_Config(SystemCoreClock / 1000))//1����
  { 
    /* Capture error */ 
    while (1);
  }
}
