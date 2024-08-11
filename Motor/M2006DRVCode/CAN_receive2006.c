/**
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  * @file       can_receive.c/h
  * @brief      there is CAN interrupt function  to receive motor data,
  *             and CAN send function to send motor current to control motor.
  *             ������CAN�жϽ��պ��������յ������,CAN���ͺ������͵���������Ƶ��.
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
#include "CAN_receive2006.h"
#include "main.h"
/*
  * @param[in]      motor1: (0x201) 2006������Ƶ���, ��Χ [-16384,16384]
  * @param[in]      motor2: (0x202) 2006������Ƶ���, ��Χ [-16384,16384]
  * @param[in]      motor3: (0x203) 2006������Ƶ���, ��Χ [-16384,16384]
  * @param[in]      motor4: (0x204) 2006������Ƶ���, ��Χ [-16384,16384]
*/


extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;
//motor data read
#define get_motor_measure(ptr, data)                                    \
    {                                                                   \
        uint8_t i = 0; /*ѭ��������*/    \ 
        int32_t temp_sum = 0; /*��ʱ�ۻ���*/ \
        (ptr)->last_raw_ecd = (ptr)->raw_ecd; /*��¼�˿̱���ֵΪ��һ�̱���ֵ*/ \
				(ptr)->raw_ecd=(uint16_t)((data)[0] << 8 | (data)[1]); /*��¼�˿̱���ֵ*/\
        (ptr)->speed_rpm = (uint16_t)((data)[2] << 8 | (data)[3]); /*��¼�˿�ת���ٶ�(RPM)*/\
        (ptr)->given_current = (uint16_t)((data)[4] << 8 | (data)[5]); /*��¼�˿�ͨ������ֵ*/\
        (ptr)->ecd_diff = (ptr)->raw_ecd - (ptr)->last_raw_ecd; /*��¼�˿̱���ֵ����һ�̱���ֵ�Ĳ�*/\
        if ((ptr)->ecd_diff < -4096) \
        { /*�жϵ���ֵС��-4096ʱ*/ \
            (ptr)->round_cnt++; /*��¼�˿�Ȧ��+1*/ \
            (ptr)->ecd_raw_rate = (ptr)->ecd_diff + 8191; /*��¼�˿̱���ֵ+8191*/ \
        } \
        else if ((ptr)->ecd_diff > 4096) \
        {  /*�жϵ���ֵ����4096ʱ*/ \
            (ptr)->round_cnt--;/*��¼�˿�Ȧ��-1*/ \
            (ptr)->ecd_raw_rate = (ptr)->ecd_diff - 8191;/*��¼�˿̱���ֵ-8191*/ \
        } \
        else \
        { \
            (ptr)->ecd_raw_rate = (ptr)->ecd_diff; /*��¼�˿̱�������*/ \
        } \
        (ptr)->deal_ecd = (ptr)->raw_ecd + (ptr)->round_cnt * 8191; /*ת���ۻ�����*/ \
        (ptr)->ecd_angle = ((float)(((ptr)->raw_ecd - (ptr)->ecd_bias) * 360 / 8191) + (ptr)->round_cnt * 360) / 36; /*��ת�ۻ��Ƕ�*/ \
        (ptr)->rate_buf[(ptr)->buf_count++] = (ptr)->ecd_raw_rate;/*��ֵ�˲�*/ \
        if ((ptr)->buf_count == RATE_BUF_SIZE) \
        { \
            (ptr)->buf_count = 0; \
        } \
        for (i = 0; i < RATE_BUF_SIZE; i++) \
        { \
            temp_sum += (ptr)->rate_buf[i]; \
        } \
        (ptr)->avg_rate = (int32_t)(temp_sum / RATE_BUF_SIZE); /*��¼�˿�ƽ���ٶ�*/\
    }
/*
motor data,  0:chassis motor1 2006;1:chassis motor3 2006;2:chassis motor3 2006;3:chassis motor4 2006;
�������, 0:���̵��1 2006���,  1:���̵��2 2006���,2:���̵��3 2006���,3:���̵��4 2006���;
*/
Motor_Measure_T motor_chassis[4];


static CAN_TxHeaderTypeDef  chassis_tx_message;
static uint8_t              chassis_can_send_data[8];

		

		
/**
  * @brief          hal CAN fifo call back, receive motor data
  * @param[in]      hcan, the point to CAN handle
  * @retval         none
  */
/**
  * @brief          hal��CAN�ص�����,���յ������
  * @param[in]      hcan:CAN���ָ��
  * @retval         none
  */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef rx_header; // ����CAN��Ϣͷ�ṹ�����
    uint8_t rx_data[8]; // ����һ��8�ֽڴ�С�����飬���ڴ洢���յ�������

    // ��CAN���߻�ȡFIFO0�е���Ϣ��������Ϣͷ������
    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data);

    // ���ݽ��յ�����ϢID�����жϣ�������Ӧ�Ĵ�����
    switch (rx_header.StdId) // ��׼ID�ֶ�
    {
        case CAN_2006_M1_ID: // ����CAN_2006_M1_ID�ǵ��1��ID
        {
            // ����get_motor_measure����������1������
            get_motor_measure(&motor_chassis[0], rx_data);
            break;
        }
        case CAN_2006_M2_ID: // ����CAN_2006_M2_ID�ǵ��2��ID
        {
            // ����get_motor_measure����������2������
            get_motor_measure(&motor_chassis[1], rx_data);
            break;
        }
        case CAN_2006_M3_ID: // ����CAN_2006_M3_ID�ǵ��3��ID
        {
            // ����get_motor_measure����������3������
            get_motor_measure(&motor_chassis[2], rx_data);
            break;
        }
        case CAN_2006_M4_ID: // ����CAN_2006_M4_ID�ǵ��4��ID
        {
            // ����get_motor_measure����������4������
            get_motor_measure(&motor_chassis[3], rx_data);
            break;
        }
        default:
        {
            // ������յ�����ϢID����Ԥ�ڵĵ��ID����ִ���κβ���
            break;
        }
    }
}




/**
  * @brief          send CAN packet of ID 0x700, it will set chassis motor 3508 to quick ID setting
  * @param[in]      none
  * @retval         none
  */
/**
  * @brief          ����IDΪ0x700��CAN��,��������2006��������������ID
  * @param[in]      none
  * @retval         none
  */
void CAN_cmd_chassis_reset_ID(void)
{
    void CAN_cmd_chassis_reset_ID(void)
{
    uint32_t send_mail_box; // ���ڴ洢��������ı���

    // ����Ҫ���͵�CAN��Ϣ
    chassis_tx_message.StdId = 0x700; // ���ñ�׼IDΪ0x700
    chassis_tx_message.IDE = CAN_ID_STD; // ����Ϊ��׼ID��ʶ��չ
    chassis_tx_message.RTR = CAN_RTR_DATA; // ����Ϊ����֡����Զ�̴�������
    chassis_tx_message.DLC = 0x08; // �������ݳ���Ϊ8�ֽ�

    // ��ʼ�����͵��������飬���8��0ֵ
    chassis_can_send_data[0] = 0;
    chassis_can_send_data[1] = 0;
    chassis_can_send_data[2] = 0;
    chassis_can_send_data[3] = 0;
    chassis_can_send_data[4] = 0;
    chassis_can_send_data[5] = 0;
    chassis_can_send_data[6] = 0;
    chassis_can_send_data[7] = 0;

    // ��CAN��Ϣ��ӵ�������У�����ȡ����������
    HAL_CAN_AddTxMessage(&CHASSIS_CAN, &chassis_tx_message, chassis_can_send_data, &send_mail_box);
}
}


/**
  * @brief          send control current of motor (0x201, 0x202, 0x203, 0x204)
  * @param[in]      motor1: (0x201) 2006 motor control current, range [-16384,16384] 
  * @param[in]      motor2: (0x202) 2006 motor control current, range [-16384,16384] 
  * @param[in]      motor3: (0x203) 2006 motor control current, range [-16384,16384] 
  * @param[in]      motor4: (0x204) 2006 motor control current, range [-16384,16384] 
  * @retval         none
  */
/**
  * @brief          ���͵�����Ƶ���(0x201,0x202,0x203,0x204)
  * @param[in]      motor1: (0x201) 2006������Ƶ���, ��Χ [-16384,16384]
  * @param[in]      motor2: (0x202) 2006������Ƶ���, ��Χ [-16384,16384]
  * @param[in]      motor3: (0x203) 2006������Ƶ���, ��Χ [-16384,16384]
  * @param[in]      motor4: (0x204) 2006������Ƶ���, ��Χ [-16384,16384]
  * @retval         none
  */
void CAN_cmd_chassis(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4)
{
    uint32_t send_mail_box; // ���ڴ洢��������ı���

    // ����Ҫ���͵�CAN��Ϣ
    chassis_tx_message.StdId = CAN_CHASSIS_ALL_ID; // ���ñ�׼ID�����ڵ������е��
    chassis_tx_message.IDE = CAN_ID_STD; // ����Ϊ��׼ID������չID
    chassis_tx_message.RTR = CAN_RTR_DATA; // ����Ϊ����֡����Զ�̴�������
    chassis_tx_message.DLC = 0x08; // �������ݳ���Ϊ8�ֽ�

    // ������Ŀ���ֵ��Ϊ��8λ�͵�8λ���洢����������������
    chassis_can_send_data[0] = motor1 >> 8; // ���1�ĸ�8λ
    chassis_can_send_data[1] = motor1;       // ���1�ĵ�8λ
    chassis_can_send_data[2] = motor2 >> 8; // ���2�ĸ�8λ
    chassis_can_send_data[3] = motor2;       // ���2�ĵ�8λ
    chassis_can_send_data[4] = motor3 >> 8; // ���3�ĸ�8λ
    chassis_can_send_data[5] = motor3;       // ���3�ĵ�8λ
    chassis_can_send_data[6] = motor4 >> 8; // ���4�ĸ�8λ
    chassis_can_send_data[7] = motor4;       // ���4�ĵ�8λ

    // ��CAN��Ϣ��ӵ�������У�����ȡ����������
    HAL_CAN_AddTxMessage(&CHASSIS_CAN, &chassis_tx_message, chassis_can_send_data, &send_mail_box);
}

/**
  * @brief          return the chassis 2006 motor data point
  * @param[in]      i: motor number,range [0,3]
  * @retval         motor data point
  */
/**
  * @brief          ���ص��̵�� 2006�������ָ��
  * @param[in]      i: ������,��Χ[0,3]
  * @retval         �������ָ��
  */
const Motor_Measure_T *get_chassis_motor_measure_point(uint8_t i)
{
    return &motor_chassis[(i & 0x03)];
}
