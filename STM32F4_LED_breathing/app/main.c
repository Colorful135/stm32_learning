#include "led.h"
#include "stm32f4xx.h"
#include <stdbool.h>
//LED1=PA1
//LED2=PA2
//LED3=PA3

void led_breath(int duty,int time)
{
	for(int t=0;t<time;t++)//调整time来调整这个百分比的亮度的时长
	{
	led_on(1);
	for(int i=0;i<duty;i++);
	led_off(1);
	for(int i=duty;i<100;i++); //这里的100就意味着每次亮度改变是1%->2%...->100%的
	}
}

int main(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  led_init();
  led_offall();
  while (1)
  {
	int period=100;
	for(int d=0;d<period;d++)
	{
		led_breath(d,2000);
	}
	for(int d=period;d>0;d--)
	{
		led_breath(d,2000);	
	}
  }
}