#include <stdint.h>
#include <stdio.h>
#include <string.h> 
#include "stm32f4xx.h"
#include "led.h"

//KEY0 连接到 PD10
//KEY1 连接到 PD9
//KEY2 连接到 PD8

//开时钟
void board_lowlevel_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
}

//高级的宏定义led
#define led_define(n,port,pin)\
static struct led_desc led_desc##n=\
{\
	.Port = GPIO##port,\
	.Pin = GPIO_Pin_##pin,\
};\
led_desc led##n = &led_desc##n

 led_define(1,A,1);
 led_define(2,A,2);
 led_define(3,A,3);






