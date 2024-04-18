/**
  ****************************(C) COPYRIGHT 2024 HzMI****************************
  * @file       HAL_Delay_us.c/h
  * @brief      
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Apr-18-2024      Rz              1. done
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  */
#ifndef __HAL_DELAY_US_H__
#define __HAL_DELAY_US_H__
#include "main.h"
#include "stm32f4xx.h"
#include "gpio.h"
#include "stm32f4xx_hal_def.h"
#include "core_cm4.h"
void HAL_Delay_us_init(uint8_t SYSCLK);
void HAL_Delay_us(uint32_t nus);






















#endif
