#ifndef __KEY_DESC_H_
#define __KEY_DESC_H_

#include <stdint.h>
#include "stm32f4xx.h"
#include "key.h"

struct key_desc
{
	GPIO_TypeDef* port;
	uint32_t pin;
	uint8_t EXTI_PortSource;
	uint8_t EXTI_PinSource;
	uint32_t EXTI_Line;
	uint8_t EXTI_IRQn;
	key_func func;
};

#endif 
