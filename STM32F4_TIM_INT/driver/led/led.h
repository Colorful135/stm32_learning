#ifndef __LED_H_
#define __LED_H_

#include <stdint.h>
#include <stdbool.h>
#include "led_desc.h"

struct led_desc;
typedef struct led_desc* led_desc;

void led_set(led_desc led, bool onoff);
void led_init(led_desc led);
void led_on(led_desc led);
void led_off(led_desc led);
void led_Toggle(led_desc led);

#endif 


