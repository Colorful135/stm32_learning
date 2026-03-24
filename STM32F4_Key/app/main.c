#include <stdint.h>
#include "stm32f4xx.h"
#include "led.h"
//KEY0 连接到 PD10
//KEY1 连接到 PD9
//KEY2 连接到 PD8

int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	
	GPIO_InitTypeDef GPIO_structure;
	GPIO_StructInit(&GPIO_structure);
	
	GPIO_structure.GPIO_Mode = GPIO_Mode_IN; 
	GPIO_structure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10; 
	GPIO_structure.GPIO_PuPd = GPIO_PuPd_UP;  //由按键硬件电路可以看出按下为地电平，所以配置上拉输入
	GPIO_structure.GPIO_Speed = GPIO_High_Speed;
	
	GPIO_Init(GPIOD, &GPIO_structure);
	led_init();
	  while(1)
		{
		led_offall();
		if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_8)==Bit_RESET)
		{ 
			//按键被按下
            led_on(1);
		
		}
		if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_9)==Bit_RESET)
		{ 
			//按键被按下
            led_on(2);
		
		}
		if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10)==Bit_RESET)
		{ 
			//按键被按下
            led_on(3);
		
		}
		
		}
}
