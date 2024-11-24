//
// Created by fangjiajun on 24-11-12.
//

#ifndef SHUMA_H
#define SHUMA_H
#include "main.h"
void a();
void shownum(uint8_t num);
void GPIO_Write_Port_Low8(GPIO_TypeDef *GPIOx, uint8_t port_value);
void Chose_Pin(uint8_t pin);
void mydelay(uint32_t delay_time);
void led_show();
void do_work_redus(void);
void do_work_add(void);
#endif // SHUMA_H
