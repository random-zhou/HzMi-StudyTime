/**
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  * @file       bsp_can.c/h
  * @brief      can�˲������ú���
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Aug-11-2024     ZSB            1. done
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  */
#include "bsp_can.h"
#include "main.h"


extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

void CAN_Filter_Init(void)
{
    // ����CAN�������ṹ�����
    CAN_FilterTypeDef can_filter_st;
    
    // ���ù�����
    can_filter_st.FilterActivation = ENABLE;
    
    // ���ù�����ģʽΪID����ģʽ
    can_filter_st.FilterMode = CAN_FILTERMODE_IDMASK;
    
    // ���ù�����Ϊ32λ��ģ
    can_filter_st.FilterScale = CAN_FILTERSCALE_32BIT;
    
    // ���ù�������ID��16λ�͵�16λ
    can_filter_st.FilterIdHigh = 0x0000;
    can_filter_st.FilterIdLow = 0x0000;
    
    // ���ù������������16λ�͵�16λ
    can_filter_st.FilterMaskIdHigh = 0x0000;
    can_filter_st.FilterMaskIdLow = 0x0000;
    
    // ���ù��������ڵĿ���
    can_filter_st.FilterBank = 0;
    
    // ָ������FIFOΪ0
    can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;
    
    // ����hcan1�Ĺ�����
    HAL_CAN_ConfigFilter(&hcan1, &can_filter_st);
    
    // ����hcan1
    HAL_CAN_Start(&hcan1);
    
    // ����hcan1�Ľ���FIFO0��Ϣ�������ж�֪ͨ
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
    
    // ����hcan2�����ôӿ���14��ʼ�Ĺ�����
    can_filter_st.SlaveStartFilterBank = 14;
    can_filter_st.FilterBank = 14;
    
    // ����hcan2�Ĺ�����
    HAL_CAN_ConfigFilter(&hcan2, &can_filter_st);
    
    // ����hcan2
    HAL_CAN_Start(&hcan2);
    
    // ����hcan2�Ľ���FIFO0��Ϣ�������ж�֪ͨ
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
}
