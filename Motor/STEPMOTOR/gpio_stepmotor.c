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
#include "GPIO_STEPPERMOTOR.h"
// #include "SYSTEM.h"//delayus�ĺ���������
// #include "LED.h"
/*ʹ�÷�����
1.�����ʼ�� STEPPER_Init
2�����������ʼ�� STEPPER_ParaInit
3.����������� STEPPER_ParaSet
4.������� STEPPER_MOVE(&stepper)
*/

#define HIGH GPIO_PIN_SET //�ߵ�ƽ
#define LOW GPIO_PIN_RESET//�͵�ƽ

#define ENABLE LOW//��
#define DISABLE HIGH//��

#define CW DISABLE//˳ʱ��
#define CCW ENABLE//��ʱ��

#define DRV_ENA(x) HAL_GPIO_WritePin(ENA_GPIO_Port,ENA_Pin,x);//����ʹ��
#define DRV_DIR(x) HAL_GPIO_WritePin(DIR_GPIO_Port,DIR_Pin,x);//��������
#define DRV_PUL(x) HAL_GPIO_WritePin(PUL_GPIO_Port,PUL_Pin,x);//������ת��ƽ



// �����ʼ�����ſں���
void STEPPER_Init(void){
    GPIO_InitTypeDef GPIO_InitStruct = {0}; // ��ʼ��GPIO�ṹ��
    __HAL_RCC_GPIOC_CLK_ENABLE(); // ʹ��GPIOC��ʱ��

    GPIO_InitStruct.Pin = ENA_Pin|DIR_Pin|PUL_Pin; // �������ţ�ENA, DIR, PUL
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // ����Ϊ�������ģʽ
    GPIO_InitStruct.Pull = GPIO_NOPULL; // ��������������������
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // ����Ϊ����
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct); // ��ʼ��GPIO

    DRV_ENA(DISABLE); // ��������
    HAL_Delay_us_init(180); // ��ʼ��΢�뼶��ʱ
}

// ����������ú���
void STEPPER_ParaSet(STEPMotor *stepper, Dir direction, float stepangle, int setturns, int tim, double subdivide){
    stepper->direction = direction; // ���õ��ת��
    stepper->stepangle = stepangle; // ���ò���
    stepper->setturns = setturns; // ���õ��ת����Ȧ��
    stepper->subdivide = subdivide; // ����ϸ��
    stepper->tim = tim; // ������ʱʱ��
}

// ���������ʼ������
void STEPPER_ParaInit(STEPMotor *stepper){
    stepper->direction = (Dir)0; // ��ʼ�����ת��
    stepper->state = (State)0; // ��ʼ�����״̬
    stepper->stepangle = 1.8; // ��ʼ������
    stepper->setturns = 0; // ��ʼ�����õ�Ȧ��
    stepper->realangle = 0; // ��ʼ��ʵ�ʽǶ�
    stepper->subdivide = 0; // ��ʼ��ϸ��
    stepper->tim = 0; // ��ʼ����ʱʱ��
    stepper->realturns = 0; // ��ʼ��ʵ��ת����Ȧ��
}

// �����������
void STEPPER_MOVE(STEPMotor *stepper){
    uint32_t real_turns;
    if (stepper->direction == 0){ // �������Ϊ0������Ϊ˳ʱ��
        DRV_DIR(CW);
    }
    if(stepper->direction == 1){ // �������Ϊ1������Ϊ��ʱ��
        DRV_DIR(CCW);
    }
    
    DRV_ENA(ENABLE); // ʹ������

    for(uint32_t i = 0; i <= ((stepper->setturns) * (stepper->subdivide)); i++){ // �������õ�Ȧ����ϸ�ֽ���ѭ��
        stepper->state = BUSY; // ���õ��״̬Ϊæµ
        PUL_GPIO_Port->ODR ^= PUL_Pin; // �л���������״̬
        HAL_Delay_us(stepper->tim); // ��ʱ

        if (i % (int)(stepper->subdivide) == 0){ // ÿ���һ��ϸ�֣�����ʵ��ת��Ȧ��
            if (stepper->direction == 0){
                stepper->realturns++; // ˳ʱ������Ȧ��
            }
            if (stepper->direction == 1){
                stepper->realturns--; // ��ʱ�����Ȧ��
            }
            real_turns = stepper->realturns; // ��ȡʵ��ת��Ȧ��
            STEPPER_GetTurnsFeedBack(stepper); // ��ȡȦ������
        }
        stepper->realangle = (float)(real_turns * 360) + ((i * stepper->stepangle) / stepper->subdivide); // ����ʵ�ʽǶ�
        STEPPER_GetAngleFeedBack(stepper); // ��ȡ�Ƕȷ���
        STEPPER_GetStateFeedBack(stepper); // ��ȡ״̬����
    }
    DRV_ENA(DISABLE); // ��������
    stepper->state = FREE; // ���õ��״̬Ϊ����
    STEPPER_GetStateFeedBack(stepper); // ��ȡ״̬����
}

// �������ʵʱ�ǶȺ���
float STEPPER_GetAngleFeedBack(STEPMotor *stepper){
    return stepper->realangle; // ����ʵ�ʽǶ�
}

// �������ʵʱȦ������
uint16_t STEPPER_GetTurnsFeedBack(STEPMotor *stepper){
    return stepper->realturns; // ����ʵ��ת����Ȧ��
}

// �����������״̬����
State STEPPER_GetStateFeedBack(STEPMotor *stepper){
    return stepper->state; // ���ص������״̬
}

















