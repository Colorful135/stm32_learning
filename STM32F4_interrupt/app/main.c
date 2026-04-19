#include "led.h"
#include "stm32f4xx.h"
#include <stdbool.h>
#include <string.h>
//LED1=PA1
//LED2=PA2
//LED3=PA3
//KEY2连接到 PD8


void delay_us(uint32_t us)
{
	while(us >=1000)
	{
    SysTick->VAL = 0;
	SysTick->LOAD = SystemCoreClock /1000;
	SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;	
	while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) ==0);
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	us -= 1000;	
	}
	while(us>0)
	{
	SysTick->VAL = 0;
	SysTick->LOAD = us*SystemCoreClock /1000/1000;
	SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;	
	while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) ==0);
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;			
	}	
}

/**
  * @brief  Configures EXTI Line8 (connected to PD8 pin) in interrupt mode
  * @param  None
  * @retval None
  */
static void EXTILine8_Config(void)
{
  /* Enable GPIOA clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  EXTI_InitTypeDef   EXTI_InitStructure;
  EXTI_StructInit(&EXTI_InitStructure);
	
  GPIO_InitTypeDef   GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);
	
  NVIC_InitTypeDef   NVIC_InitStructure;	
  memset(&NVIC_InitStructure,0,sizeof(NVIC_InitStructure));
  
  /* Configure PD8 pin as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Medium_Speed ;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* Connect EXTI Line8 to PD8 pin */
  //将按键设置为中断模式
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource8);

  /* Configure EXTI Line8 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line8;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


int main(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	
  EXTILine8_Config();
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  led_init();
  led_offall();
  while (1)
  {
//	led_on(1);
//	delay_us(200*1000);
//	led_off(1);
//	delay_us(200*1000);
	    
  }
}


void EXTI9_5_IRQHandler(void)
{
  delay_us(20*1000);
  while(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_8)==Bit_RESET);
  delay_us(20*1000);
  GPIO_ToggleBits(GPIOA,GPIO_Pin_2);
  EXTI_ClearITPendingBit(EXTI_Line8);
}
