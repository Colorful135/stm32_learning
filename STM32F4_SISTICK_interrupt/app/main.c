#include <stdint.h>
#include "stm32f4xx.h"

uint32_t ticks_value(uint32_t ms)
{
	uint32_t ticks;
	ticks=ms*SystemCoreClock/1000;
	return ticks;
}

static volatile int times=10;
//__STATIC_INLINE uint32_t SysTick_Config(uint32_t ticks)
//{
//  if ((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk) { return (1UL); }    /* Reload value impossible */

//  SysTick->LOAD  = (uint32_t)(ticks - 1UL);                         /* set reload register */
//  NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); /* set Priority for Systick Interrupt */
//  SysTick->VAL   = 0UL;                                             /* Load the SysTick Counter Value */
//  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
//                   SysTick_CTRL_TICKINT_Msk   |
//                   SysTick_CTRL_ENABLE_Msk;                         /* Enable SysTick IRQ and SysTick Timer */
//  return (0UL);                                                     /* Function successful */
//}
void GPIO_init()
{
	GPIO_InitTypeDef GPIO_structure;
	GPIO_StructInit(&GPIO_structure);
	GPIO_structure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_structure.GPIO_OType = GPIO_OType_PP;
	GPIO_structure.GPIO_Pin=GPIO_Pin_2;
	GPIO_structure.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOA,&GPIO_structure);
	
}

int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	GPIO_init();
	
	uint32_t value = ticks_value(50);
	SysTick_Config(value);
	  while(1)
		{;}
}

void SysTick_Handler(void)
{
	times--;
	if(times<=0)
	{
	  times=10;
	  GPIO_ToggleBits(GPIOA,GPIO_Pin_2);
	}		
}
