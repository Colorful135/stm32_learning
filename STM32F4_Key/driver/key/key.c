#include "stm32f4xx.h"
#include <stdbool.h>
#include "led.h"
//key0=PD10
//key1=PD9
//key2=PD8


#define key0_PORT GPIOD
#define key0_Pin GPIO_Pin_10
#define key1_PORT GPIOD
#define key1_Pin GPIO_Pin_9
#define key2_PORT GPIOD
#define key2_Pin GPIO_Pin_8


void key_init(void)
{
    GPIO_InitTypeDef GPIO_structure;
	GPIO_StructInit(&GPIO_structure);
	
	GPIO_structure.GPIO_Mode = GPIO_Mode_IN; 
	GPIO_structure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10; 
	GPIO_structure.GPIO_PuPd = GPIO_PuPd_UP;  //由按键硬件电路可以看出按下为地电平，所以配置上拉输入
	GPIO_structure.GPIO_Speed = GPIO_High_Speed;
	
	GPIO_Init(GPIOD, &GPIO_structure);
}

bool key_read(uint16_t id)
{
	switch(id)
	{
		case 0:return GPIO_ReadInputDataBit(key0_PORT, key0_Pin)==Bit_RESET;
		case 1:return GPIO_ReadInputDataBit(key1_PORT, key1_Pin)==Bit_RESET;
		case 2:return GPIO_ReadInputDataBit(key2_PORT, key2_Pin)==Bit_RESET;
		default:return false;
	}
}


		


