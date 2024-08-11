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

#ifndef __PWM_STEPMOTOR_H 
#define __PWM_STEPMOTOR_H 

//以下的引脚需要自己根据自己的引脚进行修改
//需在gpio.c当中进行初始化，这里只是宏定义
#define ENA_Pin GPIO_PIN_2
#define ENA_GPIO_Port GPIOC
#define DIR_Pin GPIO_PIN_3
#define DIR_GPIO_Port GPIOC


// 声明全局变量Pulse和target_pulse为外部链接，这意味着它们在其他文件中定义
extern int Pulse;
extern int target_pulse;

// 声明DIR函数原型，该函数用于设置电机的旋转方向
// Dir_flag参数为1时表示正转，为0时表示反转
void DIR(int Dir_flag);

// 声明Stepmotor_motor_Clockwise函数原型，该函数用于控制电机顺时针旋转
// target_Pulse参数指定电机需要旋转的脉冲数
void Stepmotor_motor_Clockwise(int target_Pulse);

// 声明Stepmotor_motor_Anti_Clockwise函数原型，该函数用于控制电机逆时针旋转
// target_Pulse参数指定电机需要旋转的脉冲数
void Stepmotor_motor_Anti_Clockwise(int target_Pulse);

#endif // 结束头文件的宏定义检查