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
void STEPPER_ParaSet(STEPMotor *stepper,Dir direction,float stepangle,int setturns,int tim,double subdivide);
void STEPPER_ParaInit(STEPMotor *stepper);
void STEPPER_Init(void);
void STEPPER_MOVE(STEPMotor *stepper);

float STEPPER_GetAngleFeedBack(STEPMotor *stepper);
uint16_t STEPPER_GetTurnsFeedBack(STEPMotor *stepper);
State STEPPER_GetStateFeedBack(STEPMotor *stepper);














#endif
