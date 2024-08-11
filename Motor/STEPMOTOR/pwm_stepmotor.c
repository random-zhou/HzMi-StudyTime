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

//��ʹ��֮ǰ��ʼ��TIM8��ͨ��һ,PWMģʽ
// ENA_PIN��DIR_PIN�ǵ���������ţ��ֱ����ڿ��Ƶ���ķ����ʹ�ܡ�
// ��Ҫ�Լ������Լ��İ����Լ���gpio�����ʼ��ʹ�ܣ����߼��ɣ�Ƶ�ʸ��߼���
//������pwm_stepmotor.h���ļ����У��Լ�ȥ����



#include "tim.h" // ������ʱ����ص�ͷ�ļ�
#include "gpio.h" // ����GPIO��ص�ͷ�ļ�
#include "pwm_stepmotor.h" // �������������ص�ͷ�ļ�

#define HIGH GPIO_PIN_SET //�ߵ�ƽ
#define LOW GPIO_PIN_RESET//�͵�ƽ

#define ENABLE LOW//��
#define DISABLE HIGH//��

#define CW DISABLE//˳ʱ��
#define CCW ENABLE//��ʱ��

#define DRV_ENA(x) HAL_GPIO_WritePin(ENA_GPIO_Port,ENA_Pin,x);//����ʹ��
#define DRV_DIR(x) HAL_GPIO_WritePin(DIR_GPIO_Port,DIR_Pin,x);//��������


// �����������������
int Pulse = 0;
int target_pulse = 0;

// �������õ������ĺ���
void DIR(int Dir_flag) {
    if (Dir_flag == 1) {
        // ���Dir_flagΪ1�����õ������Ϊ��ת
        HAL_GPIO_WritePin(DIR_GPIO_Port, DIR_Pin, GPIO_PIN_SET); // ��������ת��GPIO�����øߵ�ƽ
    }
    if (Dir_flag == 0) {
        // ���Dir_flagΪ0�����õ������Ϊ��ת
        HAL_GPIO_WritePin(DIR_GPIO_Port,DIR_Pin, GPIO_PIN_RESET); // �����Ʒ�ת��GPIO�����õ͵�ƽ
    }
}

// ������˳ʱ��ת���ĺ���
void Stepmotor_motor_Clockwise(int target_Pulse) {
    DIR(1); // ���õ������Ϊ��ת
    target_pulse = target_Pulse; // ��Ŀ����������ֵ��ȫ�ֱ���
    HAL_TIM_PWM_Start_IT(&htim8, TIM_CHANNEL_1); // ������ʱ��8��PWM�жϣ����ڲ�������
}

// ��������ʱ��ת���ĺ���
void Stepmotor_motor_Anti_Clockwise(int target_Pulse) {
    DIR(0); // ���õ������Ϊ��ת
    target_pulse = target_Pulse; // ��Ŀ����������ֵ��ȫ�ֱ���
    HAL_TIM_PWM_Start_IT(&htim8, TIM_CHANNEL_1); // ������ʱ��8��PWM�жϣ����ڲ�������
}

// �����������������
int pul = 0;

// ����PWM��������Ļص�����
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {
    if (htim == &htim8) {
        pul += 1; // ÿ��PWM�������������������1
        if (Pulse > target_pulse) {
            // �����ǰ����������Ŀ����������ֹͣPWM
            HAL_TIM_PWM_Stop_IT(&htim8, TIM_CHANNEL_1);
            Pulse = 0; // �������������
        } else {
            Pulse++; // ���û�дﵽĿ�����������������������
        }
    }
}