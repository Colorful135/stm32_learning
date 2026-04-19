#include <stdint.h>
#include "stm32f4xx.h"
#include <stdio.h>

volatile static int rxflag;

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
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //启用指定的 USART 中断
	
	NVIC_InitTypeDef NVIC_Struct;
	NVIC_Struct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_Struct.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_Struct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Struct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Struct); 

	while(1)
	{
	   if(rxflag != 0)
	   {
		 char msg[64]; //用来存放拼接好的字符串
		   int len = snprintf(msg,sizeof(msg),"received:%c\r\n",(char)rxflag);
		 for(int i=0;i<len;i++)
		 {
		   while(!USART_GetFlagStatus(USART1,USART_FLAG_TXE));
			 //等待 串口发送数据寄存器（DR）变空 → 确保可以安全写下一个字节
		   USART_SendData(USART1,msg[i]);
			 //内部执行USART1->DR = msg[i];把字符 msg[i] → 写入 USART 发送数据寄存器 DR
		 }
		 rxflag = 0;
	   }
	}
}

void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE)!= RESET)
    {
        // 处理接收
        rxflag = USART_ReceiveData(USART1);
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
    }
}
