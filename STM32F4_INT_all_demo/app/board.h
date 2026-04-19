#ifndef __BOARD_H__
#define __BOARD_H__

#include "led.h"
#include "key_desc.h"

extern led_desc  led1;
extern led_desc  led2;
extern led_desc  led3;
extern key_desc  key0;
extern key_desc  key1;
extern key_desc  key2;

void board_lowlevel_init(void);


#endif /* __BOARD_H__ */
