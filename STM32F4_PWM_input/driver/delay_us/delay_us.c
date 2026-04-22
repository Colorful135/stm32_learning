#include "stm32f4xx.h"

void delay_us(uint32_t us)
{
	while(us >= 1000)
	{
		SysTick->VAL=0; //不置0的话定时器会从 VAL 残留值开始倒数
	  SysTick->LOAD=SystemCoreClock /1000;
	  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | 
					  SysTick_CTRL_ENABLE_Msk;
	  while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk )==0);            	
	  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; //「先读→改→写」仅清0 bit0，其他位保持原样
		us -= 1000;  //减去刚刚走过的1ms
	}
	while(us > 0)
	{
	  SysTick->VAL=0;
	  SysTick->LOAD=us * SystemCoreClock /1000 /1000;
	  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | 
					  SysTick_CTRL_ENABLE_Msk;
	  while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk )==0);            	
	  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	}
	
}

