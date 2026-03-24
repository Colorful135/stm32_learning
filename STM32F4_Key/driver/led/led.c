#include "stm32f4xx.h"
#include <stdbool.h>
#include "led.h"
//LED1=PA1
//LED2=PA2
//LED3=PA3

#define LED1_PORT GPIOA
#define LED1_Pin GPIO_Pin_1
#define LED2_PORT GPIOA
#define LED2_Pin GPIO_Pin_2
#define LED3_PORT GPIOA
#define LED3_Pin GPIO_Pin_3


void led_set(uint16_t id, bool onoff)
{
switch(id)
{
	case 1:
		GPIO_WriteBit(LED1_PORT,LED1_Pin,onoff?Bit_RESET:Bit_SET);
		break;
	case 2:
		GPIO_WriteBit(LED2_PORT,LED2_Pin,onoff?Bit_RESET:Bit_SET);
		break;
	case 3:
		GPIO_WriteBit(LED3_PORT,LED3_Pin,onoff?Bit_RESET:Bit_SET);
		break;	
    default:
		break;
}
}



void led_init(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
  GPIO_InitTypeDef  GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);  //赋初值，以防赋随机值出错
	
  GPIO_InitStructure.GPIO_Pin = LED1_Pin | LED2_Pin | LED3_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  //gpio配置为输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  //High speed
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  //并不需要上下拉

  GPIO_Init(LED1_PORT, &GPIO_InitStructure);
  GPIO_Init(LED2_PORT, &GPIO_InitStructure);
  GPIO_Init(LED3_PORT, &GPIO_InitStructure);
}
		
void led_on(uint16_t id)
{
	led_set(id, 1);
}

	
void led_off(uint16_t id)
{
	led_set(id, 0);
}	
void led_offall(void)
{
	led_set(1, 0);
	led_set(2, 0);
	led_set(3, 0);
}	


