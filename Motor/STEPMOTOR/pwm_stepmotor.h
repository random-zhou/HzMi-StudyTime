/**
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  * @file       pwm_stepmotor.c/h
  * @brief      ���������������
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

//���µ�������Ҫ�Լ������Լ������Ž����޸�
//����gpio.c���н��г�ʼ��������ֻ�Ǻ궨��
#define ENA_Pin GPIO_PIN_2
#define ENA_GPIO_Port GPIOC
#define DIR_Pin GPIO_PIN_3
#define DIR_GPIO_Port GPIOC


// ����ȫ�ֱ���Pulse��target_pulseΪ�ⲿ���ӣ�����ζ�������������ļ��ж���
extern int Pulse;
extern int target_pulse;

// ����DIR����ԭ�ͣ��ú����������õ������ת����
// Dir_flag����Ϊ1ʱ��ʾ��ת��Ϊ0ʱ��ʾ��ת
void DIR(int Dir_flag);

// ����Stepmotor_motor_Clockwise����ԭ�ͣ��ú������ڿ��Ƶ��˳ʱ����ת
// target_Pulse����ָ�������Ҫ��ת��������
void Stepmotor_motor_Clockwise(int target_Pulse);

// ����Stepmotor_motor_Anti_Clockwise����ԭ�ͣ��ú������ڿ��Ƶ����ʱ����ת
// target_Pulse����ָ�������Ҫ��ת��������
void Stepmotor_motor_Anti_Clockwise(int target_Pulse);

#endif // ����ͷ�ļ��ĺ궨����