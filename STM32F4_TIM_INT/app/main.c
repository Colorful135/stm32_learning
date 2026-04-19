#include <stdint.h>
#include <string.h>
#include "stm32f4xx.h"
#include "board.h"
#include "led.h"

int main(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //这行代码必须最前面调用
	
	//配置TIM6
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
	
	TIM_TimeBaseInitStruct.TIM_Prescaler = 84-1;  //频率变为1MHZ
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInitStruct.TIM_Period = 1000-1;  //计数时长为1ms
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV4 ;
	
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM6,ENABLE);
	
	
	//配置中断
	NVIC_InitTypeDef NVIC_InitStruct;
	memset(&NVIC_InitStruct,0,sizeof(NVIC_InitStruct));
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM6_DAC_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStruct);
	
	board_lowlevel_init();
	led_init(led2);	
	
	  while(1)
		{
			;
		}
}

void  TIM6_DAC_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update) == SET)  //这个判断必须要有
	{
		static int count;
		if(++count >=500)
		{
		//让led2每500ms改变一下电平状态
		 led_Toggle(led2);
		 count = 0;
		}
    }    
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update); 
}


