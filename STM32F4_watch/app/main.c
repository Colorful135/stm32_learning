#include <stdint.h>
#include "stm32f4xx.h"
#include <stdio.h>
//USART1_TX PA9
//USART1_RX PA10

volatile static int times=20;
volatile static int usart_flag=0;

static int hour = 0;
static int min = 0;
static int second = 0;
	
void time_count(int* hour,int* min,int* second)
{
	(*second)++;
	if((*second)>=60)
	{
		(*second)=0;
		(*min)++;
		if((*min) >= 60)
		{
		  (*min)=0;
		  (*hour)++;
		  if((*hour)>=24)
		  {
			  (*hour)=0;
		  }
		  
		}
	}
}


int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	GPIO_InitTypeDef GPIO_Struct;
	GPIO_StructInit(&GPIO_Struct);
	
	GPIO_Struct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Struct.GPIO_OType =  GPIO_OType_PP;
	GPIO_Struct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_Struct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Struct.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOA,&GPIO_Struct);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9 ,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10 ,GPIO_AF_USART1);
	
	USART_InitTypeDef USART_Struct;
	USART_StructInit(&USART_Struct);
	
	USART_Struct.USART_Mode =USART_Mode_Rx | USART_Mode_Tx;
	USART_Struct.USART_BaudRate = 115200;
	USART_Struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None ;
	USART_Struct.USART_Parity = USART_Parity_No;
	USART_Struct.USART_StopBits = USART_StopBits_1 ;
	USART_Struct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART_Struct);
	USART_Cmd(USART1, ENABLE); //打开串口（别忘记！！！）
	
//	__STATIC_INLINE uint32_t SysTick_Config(uint32_t ticks)
//	{
//	  if ((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk) { return (1UL); }    /* Reload value impossible */

//	  SysTick->LOAD  = (uint32_t)(ticks - 1UL);                         /* set reload register */
//	  NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); /* set Priority for Systick Interrupt */
//	  SysTick->VAL   = 0UL;                                             /* Load the SysTick Counter Value */
//	  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
//					   SysTick_CTRL_TICKINT_Msk   |
//					   SysTick_CTRL_ENABLE_Msk;                         /* Enable SysTick IRQ and SysTick Timer */
//	  return (0UL);                                                     /* Function successful */
//	}
	SysTick_Config(SystemCoreClock/1000*50);
	  while(1)
		{
		if(usart_flag)
			{
			 time_count(&hour,&min,&second);	
			 printf("%02d:%02d:%02d\r\n",hour,min,second);	
			 usart_flag = 0;
			}
		}
}
void SysTick_Handler (void)
{
	times--;
	if(times<=0)
	{
	  times=20;
	  usart_flag =1;   
	}		
	
}

int fputc(int c , FILE *stream)
{
 (void)stream; //代表没有使用到stream这个参数，不让编译器报warning
	
  USART_ClearFlag(USART1, USART_FLAG_TC);
  USART_SendData(USART1, (uint16_t)c); //发送一个字符
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); //等待发送完成
//阻塞式发送
  return c;
}
