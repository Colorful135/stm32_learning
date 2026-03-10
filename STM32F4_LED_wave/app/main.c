#include "led.h"
#include "stm32f4xx.h"
#include <stdbool.h>
//LED1=PA1
//LED2=PA2
//LED3=PA3

/*
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
*/

int main(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  led_init();
  led_offall();
	
  int led1_init=10,led1_inc=1;
  int led2_init=30,led2_inc=1;
  int led3_init=50,led3_inc=1;
  while (1)
  {
	int period=100;
	for(int duty=0;duty<period;duty++)//决定呼吸快慢
	 {
	  for(int i=0;i<100;i++)//决定了初始亮度
	    {
		  led_set(1,i < led1_init ? 1 : 0);
		  led_set(2,i < led2_init ? 1 : 0);
		  led_set(3,i < led3_init ? 1 : 0);
	    }
     }
	 led1_init += led1_inc; if(led1_init>=100||led1_init<=10) led1_inc = -led1_inc;
	 led2_init += led2_inc; if(led2_init>=100||led2_init<=10) led2_inc = -led2_inc;
	 led3_init += led3_inc; if(led3_init>=100||led3_init<=10) led3_inc = -led3_inc;
  }
}
