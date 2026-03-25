#include <stdint.h>
#include <string.h> 
#include "stm32f4xx.h"
#include <usart.h>
#include <delay_us.h>
#include <key.h>
//KEY0 连接到 PD10
//KEY1 连接到 PD9
//KEY2 连接到 PD8


int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);	
	
	 key_init();
	 USART_init();
	
	  while(1)
		{
		
		if(key_read(0))
		{ 
			//KEY0按键被按下
			delay_us(20*1000);
		while(key_read(0));
			delay_us(20*1000);
           usart_write("KEY0 is been pressed\n");
		
		}
		if(key_read(1))
		{ 
			//KEY1按键被按下
			delay_us(20*1000);
		while(key_read(1));
			delay_us(20*1000);
			usart_write("KEY1 is been pressed\n");
		
		}
		if(key_read(2))
		{ 
			//KEY2按键被按下
			delay_us(20*1000);
		   while(key_read(2));
			delay_us(20*1000);
			usart_write("KEY2 is been pressed\n");
		
		}
		
		}
}
