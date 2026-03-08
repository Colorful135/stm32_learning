#ifndef __LED_H_
#define __LED_H_

#include <stdint.h>
#include <stdbool.h>

void led_set(uint16_t id, bool onoff);
void led_init();
void led_on(uint16_t id);
void led_off(uint16_t id);
void led_offall();

#endif 


