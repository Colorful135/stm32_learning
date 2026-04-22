#ifndef __USART_H_
#define __USART_H_

#include <stdint.h>

typedef void(*usart_func)(uint16_t data);

void USART_init(void);
void usart_write(const char str[]);
void usart_INT_init(void);
void usart_callback(usart_func f);
void usart_write_char(uint16_t ch);

#endif 


