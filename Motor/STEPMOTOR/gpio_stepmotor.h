/**
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  * @file       stepmotor.c/h
  * @brief      ���������������
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
		Dir direction;//ת������
		State state;//����״̬
		float stepangle;//����ǣ�һ��1.8��
		int setturns;//�趨ת��Ȧ��
		double realangle;//ʵ��ת���Ƕ�
		uint16_t realturns;//ʵ��Ȧ��
		int tim;//����ߵ͵�ƽʱ��
	  double subdivide;//��������ϸ��
}STEPMotor;

//void Motor_Run(uint32_t dir,uint32_t num,uint32_t speed);
// ���ò�����������ĺ�������
// stepper: ָ�򲽽�����ṹ���ָ��
// direction: �������ת����ͨ��Ϊö������
// stepangle: ���ÿ������ת�Ƕȣ���λΪ��
// setturns: �����Ҫ��ת��Ȧ��
// tim: ������ʱ�䣬��λΪ΢��
// subdivide: ϸ�ֵȼ������ڸ���ϸ�ؿ��Ƶ������
void STEPPER_ParaSet(STEPMotor *stepper, Dir direction, float stepangle, int setturns, int tim, double subdivide);

// ��ʼ��������������ĺ�������
// stepper: ָ�򲽽�����ṹ���ָ��
void STEPPER_ParaInit(STEPMotor *stepper);

// ��ʼ�����������Ӳ�����ź�������õĺ�������
void STEPPER_Init(void);

// ���Ʋ������ת���ĺ�������
// stepper: ָ�򲽽�����ṹ���ָ��
void STEPPER_MOVE(STEPMotor *stepper);

// ��ȡ�������ʵʱ�Ƕȷ����ĺ�������
// stepper: ָ�򲽽�����ṹ���ָ��
// ����ֵ: �����ǰ��ת�ĽǶȣ���λΪ��
float STEPPER_GetAngleFeedBack(STEPMotor *stepper);

// ��ȡ�������ʵʱȦ�������ĺ�������
// stepper: ָ�򲽽�����ṹ���ָ��
// ����ֵ: �����ǰ��ת��Ȧ��
uint16_t STEPPER_GetTurnsFeedBack(STEPMotor *stepper);

// ��ȡ�����������״̬�����ĺ�������
// stepper: ָ�򲽽�����ṹ���ָ��
// ����ֵ: �����ǰ������״̬��ͨ��Ϊö������
State STEPPER_GetStateFeedBack(STEPMotor *stepper);














#endif