#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "delay_us.h"
#include "usart.h"

//LED1=PA1 TIM2_CH2
//LED2=PA2 TIM2_CH3
//LED3=PA3 TIM2_CH4

static uint16_t IC2Value = 0;
static uint16_t DutyCycle = 0;
static uint32_t Frequency = 0;
  
int main(void)
{
	//开时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 ,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	USART_init();
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	//配置TIM pins
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
      
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.TIM_Period = 0xFFFF;        // 计数最大值
    TIM_TimeBaseStructure.TIM_Prescaler = 0;    
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	// TIM2 configuration: PWM Input mode
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
		
	//配置通道2直连，抓上升沿		
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0x0;
    
	//这个函数会自动配置通道1非直连，抓下降沿
    TIM_PWMIConfig(TIM2, &TIM_ICInitStructure);
	   
    /* Select the TIM2 Input Trigger: TI2FP2 */
    TIM_SelectInputTrigger(TIM2, TIM_TS_TI2FP2);
    
    /* Select the slave Mode: Reset Mode */
    TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);
    TIM_SelectMasterSlaveMode(TIM2,TIM_MasterSlaveMode_Enable);
  
	TIM_Cmd(TIM2,ENABLE);
	
	//输入模式：引脚上抓到边沿（捕获成功）产生中断
	TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);
	 
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Enable the TIM2 global Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    char str[100];
	  while(1)
		{
			delay_us(500*1000);//500ms打一次
			snprintf(str,sizeof(str),"DutyCycle = %d,Frequency = %d",DutyCycle,Frequency);
			usart_write(str);
		}

}

void TIM2_IRQHandler(void)
{
	
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);

  /* Clear TIM4 Capture compare interrupt pending bit */
  TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);

  /* Get the Input Capture value */
  IC2Value = TIM_GetCapture2(TIM2);

  if (IC2Value != 0)
  {
    /* Duty cycle computation */
    DutyCycle = (TIM_GetCapture1(TIM2) * 100) / IC2Value;

    /* Frequency computation 
       TIM2 counter clock = (RCC_Clocks.HCLK_Frequency)/2 */
    //外部PWM频率 = 定时器每秒能数的总数 ÷ 一个周期用掉的个数(输出单位是 Hz)
    Frequency = RCC_Clocks.PCLK1_Frequency * 2 / IC2Value;
  }
  else
  {
    DutyCycle = 0;
    Frequency = 0;
  }
}

