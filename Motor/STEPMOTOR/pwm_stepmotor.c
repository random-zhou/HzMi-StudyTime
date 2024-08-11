/**
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  * @file       pwm_stepmotor.c/h
  * @brief      步进电机驱动方法
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Aug-11-2024     ZLK              1. done
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  */

//在使用之前初始化TIM8的通道一,PWM模式
// ENA_PIN和DIR_PIN是电机控制引脚，分别用于控制电机的方向和使能。
// 需要自己根据自己的板子自己在gpio那里初始化使能，拉高即可，频率给高即可
//定义在pwm_stepmotor.h的文件当中，自己去翻看



#include "tim.h" // 包含定时器相关的头文件
#include "gpio.h" // 包含GPIO相关的头文件
#include "pwm_stepmotor.h" // 包含步进电机相关的头文件

#define HIGH GPIO_PIN_SET //高电平
#define LOW GPIO_PIN_RESET//低电平

#define ENABLE LOW//开
#define DISABLE HIGH//关

#define CW DISABLE//顺时针
#define CCW ENABLE//逆时针

#define DRV_ENA(x) HAL_GPIO_WritePin(ENA_GPIO_Port,ENA_Pin,x);//驱动使能
#define DRV_DIR(x) HAL_GPIO_WritePin(DIR_GPIO_Port,DIR_Pin,x);//驱动方向


// 定义脉冲计数器变量
int Pulse = 0;
int target_pulse = 0;

// 定义设置电机方向的函数
void DIR(int Dir_flag) {
    if (Dir_flag == 1) {
        // 如果Dir_flag为1，设置电机方向为正转
        HAL_GPIO_WritePin(DIR_GPIO_Port, DIR_Pin, GPIO_PIN_SET); // 将控制正转的GPIO引脚置高电平
    }
    if (Dir_flag == 0) {
        // 如果Dir_flag为0，设置电机方向为反转
        HAL_GPIO_WritePin(DIR_GPIO_Port,DIR_Pin, GPIO_PIN_RESET); // 将控制反转的GPIO引脚置低电平
    }
}

// 定义电机顺时针转动的函数
void Stepmotor_motor_Clockwise(int target_Pulse) {
    DIR(1); // 设置电机方向为正转
    target_pulse = target_Pulse; // 将目标脉冲数赋值给全局变量
    HAL_TIM_PWM_Start_IT(&htim8, TIM_CHANNEL_1); // 启动定时器8的PWM中断，用于产生脉冲
}

// 定义电机逆时针转动的函数
void Stepmotor_motor_Anti_Clockwise(int target_Pulse) {
    DIR(0); // 设置电机方向为反转
    target_pulse = target_Pulse; // 将目标脉冲数赋值给全局变量
    HAL_TIM_PWM_Start_IT(&htim8, TIM_CHANNEL_1); // 启动定时器8的PWM中断，用于产生脉冲
}

// 定义脉冲计数器变量
int pul = 0;

// 定义PWM脉冲结束的回调函数
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {
    if (htim == &htim8) {
        pul += 1; // 每次PWM脉冲结束，计数器增加1
        if (Pulse > target_pulse) {
            // 如果当前脉冲数超过目标脉冲数，停止PWM
            HAL_TIM_PWM_Stop_IT(&htim8, TIM_CHANNEL_1);
            Pulse = 0; // 重置脉冲计数器
        } else {
            Pulse++; // 如果没有达到目标脉冲数，脉冲计数器增加
        }
    }
}