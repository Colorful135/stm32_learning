#ifndef LED_DESC_H_
#define LED_DESC_H_

#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx.h"

struct led_desc
{
  	GPIO_TypeDef* Port;
	uint32_t Pin;
};

#endif
