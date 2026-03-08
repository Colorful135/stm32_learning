
#include "stm32f4xx.h"
//LED1=PA1
//LED2=PA2
//LED3=PA3

#define LED1_PORT GPIOA
#define LED1_Pin GPIO_Pin_1
#define LED2_PORT GPIOA
#define LED2_Pin GPIO_Pin_2
#define LED3_PORT GPIOA
#define LED3_Pin GPIO_Pin_3
void delay_ms(uint32_t ms)
{
  // volatile让t不被优化，循环必须完整执行
  volatile uint32_t t;
  // 168MHz主频下，这个数值≈1毫秒延时（可根据实际微调）
  for(; ms > 0; ms--)
    for(t = 0; t < 18000; t++);
}



int main(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
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
	
  while (1)
  {
	GPIO_ResetBits(LED1_PORT,LED1_Pin);
	GPIO_ResetBits(LED2_PORT,LED2_Pin);
	GPIO_ResetBits(LED3_PORT,LED3_Pin);
	delay_ms(500);
    GPIO_SetBits(LED1_PORT,LED1_Pin);
	GPIO_SetBits(LED2_PORT,LED2_Pin);
	GPIO_SetBits(LED3_PORT,LED3_Pin);
	delay_ms(500);  
  }
}

