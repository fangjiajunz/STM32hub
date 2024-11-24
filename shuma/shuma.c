//
// Created by fangjiajun on 24-11-12.
//
#include <sys/stat.h>


#include "gpio.h"
#include "main.h"
void Led_init() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __GPIOC_CLK_ENABLE();
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIOA->ODR = 0xffff;
    GPIOC->ODR = 0xffff;
    GPIOB->ODR = 0xffff;
}

void key_init() {
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}
void led_light() {
    static uint8_t i = 0x01;
    GPIOA->ODR = (GPIOA->ODR & 0xFF00) | i;
    GPIOB->ODR = (GPIOB->ODR & 0xff00) | i;
    i = i << 1;
    if (i == 0x80) {
        i = 0x01;
    }
    HAL_Delay(1000);
}

void led2init() {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1, GPIO_PIN_SET);
}


void read_key() {
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2)) {
        HAL_Delay(10);
        if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2)) {
            while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2)) {
                HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
            }
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
        }
    } else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5)) {
        HAL_Delay(10);
        if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5)) {
            while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5)) {
                HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
            }
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
        }
    }
}


void a() { HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); } // 测试用例

int my_time[4] = {1, 1, 1, 1};

extern TIM_HandleTypeDef htim3;

uint8_t leddate[] = {
        /***************************/
        0xbf, 0x86, 0xdb, 0xcf, 0xe6, 0xed, 0xfd, 0x87, 0xff, 0xef, 0xf1}; // 0到9最后一位为F

void GPIO_Write_Port_Low8(GPIO_TypeDef *GPIOx, uint8_t port_value) {
    // 先清零低8位，再写入port_value
    GPIOx->ODR = (GPIOx->ODR & 0xFF00) | port_value;
}

void shownum(uint8_t num) {
    /*********/
    GPIO_Write_Port_Low8(GPIOA, num);
}

void Chose_Pin(uint8_t pin) {
    // 先将 GPIO_PIN_0、GPIO_PIN_1、GPIO_PIN_10 全部复位
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);

    // 根据传入的 pin 参数设置对应引脚
    if (pin & 0x01)
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET); // 如果 pin 的第0位为1，设置 GPIO_PIN_0
    if (pin & 0x02)
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET); // 如果 pin 的第1位为1，设置 GPIO_PIN_1
    if (pin & 0x04)
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET); // 如果 pin 的第2位为1，设置 GPIO_PIN_10
}

void mydelay(uint32_t delay_time) {
    for (volatile uint32_t i = 0; i < delay_time * 1000; i++)
        ;
}

void led_show() {
    for (uint8_t i = 0; i < 4; i++) {
        Chose_Pin(i);
        shownum(leddate[my_time[i]]);
        mydelay(10);
    }
}

void do_work_redus(void) {
    if (my_time[0] > 0) {
        my_time[0]--; // 每秒递减 time[0]（秒）
    } else {
        if (my_time[1] > 0) {
            my_time[1]--; // 秒归零时递减 time[1]（分钟）
            my_time[0] = 9; // 重置秒数
        } else if (my_time[2] > 0) {
            my_time[2]--; // 分钟归零时递减 time[2]（小时）
            my_time[1] = 9; // 重置分钟数
        } else if (my_time[3] > 0) {
            my_time[3]--; // 小时归零时递减 time[3]（天数）
            my_time[2] = 9; // 重置小时数
        } else {
            // 所有时间单位都为 0，倒计时结束
            // 在这里可以执行倒计时结束后的操作，比如停止定时器、触发某个事件等
            HAL_TIM_Base_Stop_IT(&htim3); // 停止定时器
        }
    }
}

void do_work_add(void) {
    // 增加秒数
    if (my_time[0] < 9) {
        my_time[0]++; // 每秒递增 time[0]（秒）
    } else {
        my_time[0] = 0; // 重置秒数
        // 增加分钟数
        if (my_time[1] < 9) {
            my_time[1]++; // 分钟递增
        } else {
            my_time[1] = 0; // 重置分钟数
            // 增加小时数
            if (my_time[2] < 9) {
                my_time[2]++; // 小时递增
            } else {
                my_time[2] = 0; // 重置小时数
                // 增加天数
                if (my_time[3] < 9) {
                    my_time[3]++; // 天数递增
                } else {
                    my_time[3] = 0; // 重置天数
                    // 你可以在这里做一些特殊的处理，例如触发某个事件
                    // 例如，如果天数到了 10 天，可以停止计时等
                    HAL_TIM_Base_Stop_IT(&htim3); // 停止定时器
                }
            }
        }
    }
}


