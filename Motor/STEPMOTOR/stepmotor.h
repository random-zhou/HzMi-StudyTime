/*
 * @Author: ��random-zhou�� 2501601106@qq.com
 * @Date: 2024-04-18 20:27:30
 * @LastEditors: ��random-zhou�� 2501601106@qq.com
 * @LastEditTime: 2024-04-18 20:27:59
 * @FilePath: \HzMi-StudyTime\Motor\STEPMOTOR\stepmotor.h
 * @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
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
void STEPPER_ParaSet(STEPMotor *stepper,Dir direction,float stepangle,int setturns,int tim,double subdivide);
void STEPPER_ParaInit(STEPMotor *stepper);
void STEPPER_Init(void);
void STEPPER_MOVE(STEPMotor *stepper);

float STEPPER_GetAngleFeedBack(STEPMotor *stepper);
uint16_t STEPPER_GetTurnsFeedBack(STEPMotor *stepper);
State STEPPER_GetStateFeedBack(STEPMotor *stepper);














#endif
