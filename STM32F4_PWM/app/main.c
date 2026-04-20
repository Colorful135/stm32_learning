#include <stdint.h>
#include "stm32f4xx.h"
#include "delay_us.h"

//LED1=PA1 TIM2_CH2
//LED2=PA2 TIM2_CH3
//LED3=PA3 TIM2_CH4


int main(void)
{
	//开时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA ,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 ,ENABLE);
	
	//配置TIM pins
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
      
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2); 
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM2);
	
	
	//配置TIMX
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
	
	RCC_ClocksTypeDef  RCC_ClocksStruct;
	RCC_GetClocksFreq(&RCC_ClocksStruct);
	uint32_t tim2_clock = RCC_ClocksStruct.PCLK1_Frequency /1000000 *2; //返回的是HZ，要先改为MHZ
	
	TIM_TimeBaseInitStruct.TIM_Prescaler = tim2_clock -1;  //频率变为1MHZ
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInitStruct.TIM_Period = 1000-1;  //计数时长为1ms
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV4 ;
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	/* Output Compare Toggle Mode configuration: Channelx */
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //CNT < CCR → 内部输出高,CNT ≥ CCR → 内部输出低
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //内部输出到引脚时，反转后输出；PWM1 + Low占空比越大，低电平越多，适用于低电平亮的 LED
    
	TIM_OCInitStructure.TIM_Pulse = 200;
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_Pulse = 400;
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_Pulse = 600;
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
    
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable); 
	//开启预装载后，CCR 的修改会 “等一个周期”，保证波形平滑过渡（比如呼吸灯从暗到亮，不会突然闪一下）。
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable); 
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable); 
	
	TIM_Cmd(TIM2,ENABLE);
	
	static int pwm1_duty_cycle =200,pwm2_duty_cycle =400,pwm3_duty_cycle =600;
	static int pwm1_inc =1,pwm2_inc =1,pwm3_inc =1;
	
	  while(1)
		{
			delay_us(1000);
			
			pwm1_duty_cycle += pwm1_inc;
			pwm2_duty_cycle += pwm2_inc;
			pwm3_duty_cycle += pwm3_inc;
			
			if(pwm1_duty_cycle>=999 || pwm1_duty_cycle<=0)
			{
				pwm1_inc = -pwm1_inc;
			}
			if(pwm2_duty_cycle>=999 || pwm2_duty_cycle<=0)
			{
				pwm2_inc = -pwm2_inc;
			}
			if(pwm3_duty_cycle>=999 || pwm3_duty_cycle<=0)
			{
				pwm3_inc = -pwm3_inc;
			}
			
			TIM_SetCompare2(TIM2,pwm1_duty_cycle);
			TIM_SetCompare3(TIM2,pwm2_duty_cycle);
			TIM_SetCompare4(TIM2,pwm3_duty_cycle);
		}

}



