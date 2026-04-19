#include "stm32f4xx.h"
#include <stdbool.h>
#include <string.h>
#include <key.h>
#include <key_desc.h>
#include <board.h>

//key0=PD10
//key1=PD9
//key2=PD8
	
	
//按键初始化	
void key_init(key_desc key)
{
    GPIO_InitTypeDef GPIO_structure;
	GPIO_StructInit(&GPIO_structure);
	
	GPIO_structure.GPIO_Mode = GPIO_Mode_IN; 
	GPIO_structure.GPIO_PuPd = GPIO_PuPd_UP;  //由按键硬件电路可以看出按下为低电平，所以配置上拉输入
	GPIO_structure.GPIO_Speed = GPIO_High_Speed;
	
	GPIO_structure.GPIO_Pin = key->pin; 
	GPIO_Init(key->port, &GPIO_structure);
}


void key_INT_init(key_desc key)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	EXTI_InitTypeDef   EXTI_InitStructure;
    EXTI_StructInit(&EXTI_InitStructure);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	memset(&NVIC_InitStructure,0,sizeof(NVIC_InitStructure));
	
  //将按键设置为中断模式,选择用作 EXTI 线路的 GPIO 引脚。
	//即：把 GPIO 引脚 与 EXTI 中断线 连接起来
	SYSCFG_EXTILineConfig(key->EXTI_PortSource, key->EXTI_PinSource);
	

	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	
	EXTI_InitStructure.EXTI_Line =key->EXTI_Line;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI Linex Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_InitStructure.NVIC_IRQChannel = key->EXTI_IRQn;
	NVIC_Init(&NVIC_InitStructure);
}

//按键状态读取
bool key_read(key_desc key)
{
	return GPIO_ReadInputDataBit(key->port, key->pin)==Bit_RESET;
}


//按键对应中断函数配置
/*主函数可通过调用此函数实现：在主函数里写f，f是什么，对应按键按下时执行的中断函数就是什么
因为中断函数里面是执行了回调函数，回调到key0_pressed,key1_pressed,key2_pressed;*/
void key_pressed_callback(key_desc key,key_func f)
{
	key->func = f ;
}
