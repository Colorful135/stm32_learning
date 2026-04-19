#include <stdint.h>
#include <stdio.h>
#include <string.h> 
#include "stm32f4xx.h"
#include "usart.h"
#include "delay_us.h"
#include "key.h"
#include "key_desc.h"
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



//高级的宏定义key
#define key_define(n,PORT,PIN,IRQn)\
static struct key_desc key_desc##n = \
{\
	.port =  GPIO##PORT,\
	.pin = GPIO_Pin_##PIN,\
	.EXTI_PortSource = EXTI_PortSourceGPIO##PORT,\
	.EXTI_PinSource = EXTI_PinSource##PIN,\
	.EXTI_Line = EXTI_Line##PIN,\
	.EXTI_IRQn = IRQn,\
};\
key_desc key##n = &key_desc##n   //宏定义最后不加分号

key_define(0,D,10,EXTI15_10_IRQn);
key_define(1,D,9,EXTI9_5_IRQn);
key_define(2,D,8, EXTI9_5_IRQn);


void EXTI9_5_IRQHandler(void)
{
	 if (key2->func != NULL) {
        key2->func(key2);
    }
	EXTI_ClearITPendingBit(EXTI_Line8);
}

void EXTI15_10_IRQHandler(void)
{
	 if (key0->func != NULL) {
        key0->func(key0);
    }
	EXTI_ClearITPendingBit(EXTI_Line10);
}


