#ifndef __SYSTEM_H__
#define __SYSTEM_H__
#include "main.h"
#include "stm32f4xx.h"
#include "gpio.h"
#include "stm32f4xx_hal_def.h"
#include "core_cm4.h"
void HAL_Delay_us_init(uint8_t SYSCLK);
void HAL_Delay_us(uint32_t nus);






















#endif
