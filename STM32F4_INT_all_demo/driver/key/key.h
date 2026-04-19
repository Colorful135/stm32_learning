#ifndef __KEY_H_
#define __KEY_H_

#include <stdint.h>
#include <stdbool.h>

struct key_desc;
typedef struct key_desc* key_desc;

typedef void(*key_func)(key_desc key);
	
void key_init(key_desc key);
bool key_read(key_desc key);
void key_INT_init(key_desc key);
void key_pressed_callback(key_desc key,key_func f);

#endif 


