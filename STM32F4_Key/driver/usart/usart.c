#include "stm32f4xx.h"
#include <string.h> 

 
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


void usart_write(const char str[])
{
  int len = strlen(str);
  for(int i=0;i<len;i++)
	{
	  USART_ClearFlag(USART1, USART_FLAG_TC);
	  USART_SendData(USART1, (uint16_t)str[i]);
	  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    }
}

