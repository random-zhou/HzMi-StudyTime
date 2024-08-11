/**
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  * @file       bsp_can.c/h
  * @brief      can滤波器配置函数
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
    // 定义CAN过滤器结构体变量
    CAN_FilterTypeDef can_filter_st;
    
    // 启用过滤器
    can_filter_st.FilterActivation = ENABLE;
    
    // 设置过滤器模式为ID掩码模式
    can_filter_st.FilterMode = CAN_FILTERMODE_IDMASK;
    
    // 设置过滤器为32位规模
    can_filter_st.FilterScale = CAN_FILTERSCALE_32BIT;
    
    // 设置过滤器的ID高16位和低16位
    can_filter_st.FilterIdHigh = 0x0000;
    can_filter_st.FilterIdLow = 0x0000;
    
    // 设置过滤器的掩码高16位和低16位
    can_filter_st.FilterMaskIdHigh = 0x0000;
    can_filter_st.FilterMaskIdLow = 0x0000;
    
    // 设置过滤器所在的库编号
    can_filter_st.FilterBank = 0;
    
    // 指定接收FIFO为0
    can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;
    
    // 配置hcan1的过滤器
    HAL_CAN_ConfigFilter(&hcan1, &can_filter_st);
    
    // 启动hcan1
    HAL_CAN_Start(&hcan1);
    
    // 激活hcan1的接收FIFO0消息待处理中断通知
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
    
    // 对于hcan2，设置从库编号14开始的过滤器
    can_filter_st.SlaveStartFilterBank = 14;
    can_filter_st.FilterBank = 14;
    
    // 配置hcan2的过滤器
    HAL_CAN_ConfigFilter(&hcan2, &can_filter_st);
    
    // 启动hcan2
    HAL_CAN_Start(&hcan2);
    
    // 激活hcan2的接收FIFO0消息待处理中断通知
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
}
