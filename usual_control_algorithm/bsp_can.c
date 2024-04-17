#include "bsp_can.h"

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

/**
  * @brief          CANɸѡ��
  */
HAL_StatusTypeDef Can_Filter_Init(void)
{
	/***	CAN1	***/
    CAN_FilterTypeDef sFilterConfig;
	sFilterConfig.FilterActivation = ENABLE;			// ���������
	sFilterConfig.FilterBank = 0;						// ������CANɸѡ������
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;	// ���ù���ģʽΪ�б�ģʽ
	sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;	// ����ɸѡ���ĳ߶�Ϊ16λ��
	sFilterConfig.FilterIdHigh = 0x0000;				// CAN_FxR1�Ĵ���
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;			// CAN_FxR2�Ĵ���
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;	// ɸѡ����ɸѡ���Ĺ�����FIFO0
	
	if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK) {						// ����CAN1����ɸѡ������
		Error_Handler();
	}
	if (HAL_CAN_Start(&hcan1) != HAL_OK) {												// ����CAN1
		Error_Handler();
	}
	if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {	// ����CAN1��FIFO0�����ж�
		Error_Handler();
	}
	if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_MSG_PENDING) != HAL_OK) {	// ����CAN1��FIFO1�����ж�
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
	sFilterConfig2.FilterBank = 14;						// ���ô�CAN����������
	sFilterConfig2.SlaveStartFilterBank = 14;			// ����CAN2����ʼ��������

	if (HAL_CAN_ConfigFilter(&hcan2, &sFilterConfig2) != HAL_OK) {
		Error_Handler();
	}
	if (HAL_CAN_Start(&hcan2) != HAL_OK) {												// ����CAN2
		Error_Handler();
	}
	if (HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {	// ����CAN2��FIFO0�����ж�
		Error_Handler();
	}

	return HAL_OK;
}

