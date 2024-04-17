#include "bsp_can.h"

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

/**
  * @brief          CAN筛选器
  */
HAL_StatusTypeDef Can_Filter_Init(void)
{
	/***	CAN1	***/
    CAN_FilterTypeDef sFilterConfig;
	sFilterConfig.FilterActivation = ENABLE;			// 激活过滤器
	sFilterConfig.FilterBank = 0;						// 配置主CAN筛选器组编号
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;	// 配置工作模式为列表模式
	sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;	// 配置筛选器的尺度为16位长
	sFilterConfig.FilterIdHigh = 0x0000;				// CAN_FxR1寄存器
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;			// CAN_FxR2寄存器
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;	// 筛选器接筛选报文关联到FIFO0
	
	if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK) {						// 配置CAN1接收筛选过滤器
		Error_Handler();
	}
	if (HAL_CAN_Start(&hcan1) != HAL_OK) {												// 开启CAN1
		Error_Handler();
	}
	if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {	// 开启CAN1的FIFO0接收中断
		Error_Handler();
	}
	if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_MSG_PENDING) != HAL_OK) {	// 开启CAN1的FIFO1接收中断
		Error_Handler();
	}

	/***	CAN2	***/
	CAN_FilterTypeDef sFilterConfig2;
	sFilterConfig2.FilterActivation = ENABLE;
	sFilterConfig2.FilterBank = 0;
	sFilterConfig2.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig2.FilterScale = CAN_FILTERSCALE_16BIT;
	sFilterConfig2.FilterIdHigh = 0x0000;
	sFilterConfig2.FilterIdLow = 0x0000;
	sFilterConfig2.FilterMaskIdHigh = 0x0000;
	sFilterConfig2.FilterMaskIdLow = 0x0000;
	sFilterConfig2.FilterFIFOAssignment = CAN_RX_FIFO0;
	sFilterConfig2.FilterBank = 14;						// 设置从CAN过滤器组编号
	sFilterConfig2.SlaveStartFilterBank = 14;			// 设置CAN2的起始过滤器组

	if (HAL_CAN_ConfigFilter(&hcan2, &sFilterConfig2) != HAL_OK) {
		Error_Handler();
	}
	if (HAL_CAN_Start(&hcan2) != HAL_OK) {												// 开启CAN2
		Error_Handler();
	}
	if (HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {	// 开启CAN2的FIFO0接收中断
		Error_Handler();
	}

	return HAL_OK;
}

