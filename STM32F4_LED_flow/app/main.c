#include "led.h"
#include "stm32f4xx.h"
#include <stdbool.h>
//LED1=PA1
//LED2=PA2
//LED3=PA3


void delay_ms(uint32_t ms)
{
  // volatile让t不被优化，循环必须完整执行
  volatile uint32_t t;
  // 168MHz主频下，这个数值≈1毫秒延时（可根据实际微调）
  for(; ms > 0; ms--)
    for(t = 0; t < 18000; t++);
}


int main(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  led_init();
  led_offall();
  while (1)
  {
	for(uint16_t id=1;id<=3;id++)
	{
		led_on(id);
		delay_ms(500);
		led_off(id);
	}
  }
}

