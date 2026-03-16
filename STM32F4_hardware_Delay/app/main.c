
#include "stm32f4xx.h"
//LED1=PA1

#define LED1_PORT GPIOA
#define LED1_Pin GPIO_Pin_1


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



int main(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
  GPIO_InitTypeDef  GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);  //赋初值，以防赋随机值出错
	
  GPIO_InitStructure.GPIO_Pin = LED1_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  //gpio配置为输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  //High speed
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  //并不需要上下拉
  GPIO_Init(LED1_PORT, &GPIO_InitStructure);

	GPIO_SetBits(LED1_PORT,LED1_Pin);
		
  while (1)
  {
   
        for (int i = 0; i < 3; i++)
        {
            GPIO_ResetBits(LED1_PORT, LED1_Pin);
            delay_us(200 * 1000);
            GPIO_SetBits(LED1_PORT, LED1_Pin);
            delay_us(200 * 1000);
        }
        for (int i = 0; i < 3; i++)
        {
            GPIO_ResetBits(LED1_PORT, LED1_Pin);
            delay_us(500 * 1000);
            GPIO_SetBits(LED1_PORT, LED1_Pin);
            delay_us(500 * 1000);
        }
        for (int i = 0; i < 3; i++)
        {
            GPIO_ResetBits(LED1_PORT, LED1_Pin);
            delay_us(200 * 1000);
            GPIO_SetBits(LED1_PORT, LED1_Pin);
            delay_us(200 * 1000);
        }
		delay_us(600 * 1000);
  }
}

