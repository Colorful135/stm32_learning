#include "stm32f4xx.h"
#include <string.h> 
#include <usart.h>

static usart_func usart_INT_callback;
 
void USART_init(void)
{
	//配置GPIO
	GPIO_InitTypeDef  GPIO_Struct;
	GPIO_StructInit(&GPIO_Struct);
		
	GPIO_Struct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Struct.GPIO_Speed = GPIO_High_Speed;
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Struct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 ;
		
	GPIO_Init(GPIOA, &GPIO_Struct);	
	 
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10,GPIO_AF_USART1);
 

	//配置USART
    USART_InitTypeDef USART_InitStructure;
    USART_StructInit(&USART_InitStructure);
	  
    USART_InitStructure.USART_BaudRate = 115200u; //结尾加个u，因为USART_BaudRate是无符号整数类型，115200是int类型，其实是不兼容的
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	  
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

void usart_INT_init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_InitTypeDef NVIC_Struct;
	memset(&NVIC_Struct,0,sizeof(NVIC_Struct));
	
	NVIC_Struct.NVIC_IRQChannel = USART1_IRQn ;
	NVIC_Struct.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_Struct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Struct.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_Struct);
}

//发单个字符
void usart_write_char(uint16_t ch)
{
	  USART_ClearFlag(USART1, USART_FLAG_TC);
	  USART_SendData(USART1, ch);
	  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

//发字符串
void usart_write(const char str[])
{
  int len = strlen(str);
  for(int i=0;i<len;i++)
	{
	  usart_write_char(str[i]);
    }
}


void usart_callback(usart_func f)
{
	usart_INT_callback = f;	
}

void USART1_IRQHandler(void)
{ 
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
		if(usart_INT_callback != NULL)
		{
			uint16_t data = USART_ReceiveData(USART1);
			usart_INT_callback(data);
		}
    }   
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}
