/**
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  * @file       stepmotor.c/h
  * @brief      步进电机驱动方法
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Apr-18-2024     HZMI              1. done
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  */
#ifndef __STEPPERMOTOR_H__
#define __STEPPERMOTOR_H__

#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal_def.h"
#include "core_cm4.h"



//PC2->L1->ENA
//PC3->M1->DIR
//PC4->N1->PUL
#define ENA_Pin GPIO_PIN_2
#define ENA_GPIO_Port GPIOC
#define DIR_Pin GPIO_PIN_3
#define DIR_GPIO_Port GPIOC
#define PUL_Pin GPIO_PIN_4
#define PUL_GPIO_Port GPIOC

typedef enum Dir {CW=0,CCW=1} Dir ;
typedef enum State {FREE=0,BUSY=1} State;


typedef struct STEPMotor
{
		Dir direction;//转动方向
		State state;//运行状态
		float stepangle;//步距角，一般1.8度
		int setturns;//设定转动圈数
		double realangle;//实际转动角度
		uint16_t realturns;//实际圈数
		int tim;//脉冲高低电平时间
	  double subdivide;//步进驱动细分
}STEPMotor;

//void Motor_Run(uint32_t dir,uint32_t num,uint32_t speed);
// 设置步进电机参数的函数声明
// stepper: 指向步进电机结构体的指针
// direction: 电机的旋转方向，通常为枚举类型
// stepangle: 电机每步的旋转角度，单位为度
// setturns: 电机需要旋转的圈数
// tim: 脉冲间隔时间，单位为微秒
// subdivide: 细分等级，用于更精细地控制电机步进
void STEPPER_ParaSet(STEPMotor *stepper, Dir direction, float stepangle, int setturns, int tim, double subdivide);

// 初始化步进电机参数的函数声明
// stepper: 指向步进电机结构体的指针
void STEPPER_ParaInit(STEPMotor *stepper);

// 初始化步进电机的硬件引脚和相关配置的函数声明
void STEPPER_Init(void);

// 控制步进电机转动的函数声明
// stepper: 指向步进电机结构体的指针
void STEPPER_MOVE(STEPMotor *stepper);

// 获取步进电机实时角度反馈的函数声明
// stepper: 指向步进电机结构体的指针
// 返回值: 电机当前旋转的角度，单位为度
float STEPPER_GetAngleFeedBack(STEPMotor *stepper);

// 获取步进电机实时圈数反馈的函数声明
// stepper: 指向步进电机结构体的指针
// 返回值: 电机当前旋转的圈数
uint16_t STEPPER_GetTurnsFeedBack(STEPMotor *stepper);

// 获取步进电机运行状态反馈的函数声明
// stepper: 指向步进电机结构体的指针
// 返回值: 电机当前的运行状态，通常为枚举类型
State STEPPER_GetStateFeedBack(STEPMotor *stepper);














#endif
