//
// Created by fangjiajun on 24-11-12.
//

#include "shuma.h"

void a() { HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); } // 测试用例

int time[4] = {1, 1, 1, 1};

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
        shownum(leddate[time[i]]);
        mydelay(10);
    }
}

void do_work_redus(void) {
    if (time[0] > 0) {
        time[0]--; // 每秒递减 time[0]（秒）
    } else {
        if (time[1] > 0) {
            time[1]--; // 秒归零时递减 time[1]（分钟）
            time[0] = 9; // 重置秒数
        } else if (time[2] > 0) {
            time[2]--; // 分钟归零时递减 time[2]（小时）
            time[1] = 9; // 重置分钟数
        } else if (time[3] > 0) {
            time[3]--; // 小时归零时递减 time[3]（天数）
            time[2] = 9; // 重置小时数
        } else {
            // 所有时间单位都为 0，倒计时结束
            // 在这里可以执行倒计时结束后的操作，比如停止定时器、触发某个事件等
            HAL_TIM_Base_Stop_IT(&htim3); // 停止定时器
        }
    }
}

void do_work_add(void) {
    // 增加秒数
    if (time[0] < 9) {
        time[0]++; // 每秒递增 time[0]（秒）
    } else {
        time[0] = 0; // 重置秒数
        // 增加分钟数
        if (time[1] < 9) {
            time[1]++; // 分钟递增
        } else {
            time[1] = 0; // 重置分钟数
            // 增加小时数
            if (time[2] < 9) {
                time[2]++; // 小时递增
            } else {
                time[2] = 0; // 重置小时数
                // 增加天数
                if (time[3] < 9) {
                    time[3]++; // 天数递增
                } else {
                    time[3] = 0; // 重置天数
                    // 你可以在这里做一些特殊的处理，例如触发某个事件
                    // 例如，如果天数到了 10 天，可以停止计时等
                    HAL_TIM_Base_Stop_IT(&htim3); // 停止定时器
                }
            }
        }
    }
}


