#include <stdint.h>
#include <stdio.h>
#include <string.h> 
#include "stm32f4xx.h"
//#include "usart.h"
//#include "delay_us.h"
#include "key.h"
#include "led.h"
#include "board.h"

//KEY0 连接到 PD10
//KEY1 连接到 PD9
//KEY2 连接到 PD8

//通过面向对象的方式实现按键控制灯的亮灭

static void key_callback(key_desc key)
{
  if (key == key0)
    {
       led_Toggle(led1);
    }
    else if (key == key1)
    {
       led_Toggle(led2);
    }
    else if (key == key2)
    {
        led_Toggle(led3);
    }

}

//static void usart_rx_callback(uint16_t data)
//{
//	//按下按键回显并控制对应led亮灭
//	usart_write_char(data);
//	switch(data)
//	{
//		//这里注意别忘记加引号
//		case '1':led1_Toggle();break;			
//		case '2':led2_Toggle();break;		
//		case '3':led3_Toggle();break;
//	    default:break;
//	}
//}

int main(void)
{	
	 board_lowlevel_init();
	
	 led_init(led1);
	 led_init(led2);
	 led_init(led3);
	
	 led_off(led1);
	 led_off(led2);
	 led_off(led3);
	
	 key_init(key0);
	 key_init(key1);
	 key_init(key2);
	 
	 key_INT_init(key0);
	 key_INT_init(key1);
	 key_INT_init(key2);
	
	 key_pressed_callback(key0,key_callback);
	 key_pressed_callback(key1,key_callback);
	 key_pressed_callback(key2,key_callback);
	
//	 USART_init();
//	 usart_INT_init();
//	 usart_callback(usart_rx_callback);
	 while(1)
		{	
		;		
		}
}
	

