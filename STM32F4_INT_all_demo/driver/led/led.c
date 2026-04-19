#include "stm32f4xx.h"
#include <stdbool.h>
#include "led.h"
//LED1=PA1
//LED2=PA2
//LED3=PA3

//led初始化
void led_init(led_desc led)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);  //赋初值，以防赋随机值出错
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  //gpio配置为输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  //High speed
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  //并不需要上下拉
	
  GPIO_InitStructure.GPIO_Pin = led->Pin;

  GPIO_Init(led->Port, &GPIO_InitStructure);
  
}
		

//led亮灭状态设置
void led_set(led_desc led, bool onoff)
{
	GPIO_WriteBit(led->Port,led->Pin,onoff?Bit_RESET:Bit_SET);
}

//led亮
void led_on(led_desc led)
{
	GPIO_WriteBit(led->Port,led->Pin,Bit_RESET);
}

//led灭	
void led_off(led_desc led)
{
	GPIO_WriteBit(led->Port,led->Pin,Bit_SET);
}

//led翻转
void led_Toggle(led_desc led)
{
	GPIO_ToggleBits(led->Port,led->Pin);
}

