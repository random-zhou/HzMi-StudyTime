/*
*
****************************(C) COPYRIGHT 2024 HZMI****************************
  * @file       can_receive.c/h
  * @brief      there is CAN interrupt function  to receive motor data,
  *             and CAN send function to send motor current to control motor.
  *             这里是CAN中断接收函数，接收电机数据,CAN发送函数发送电机电流控制电机.
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

#include "CAN_receive6020.h"
#include "main.h"



extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

//#define get_motor_measure(ptr, data)                                    \
//    {                                                                   \
//        (ptr)->last_ecd = (ptr)->ecd;                                   \
//        (ptr)->ecd = (uint16_t)((data)[0] << 8 | (data)[1]);            \
//        (ptr)->speed_rpm = (uint16_t)((data)[2] << 8 | (data)[3]);      \
//        (ptr)->given_current = (uint16_t)((data)[4] << 8 | (data)[5]);  \
//        (ptr)->temperate = (data)[6];                                   \
//    }

//motor data read
#define get_motor_measure(ptr, data)                                    \
    {                                                                   \
        uint8_t i = 0; \
        int32_t temp_sum = 0; \
        (ptr)->last_raw_ecd = (ptr)->raw_ecd; \
				(ptr)->raw_ecd=(uint16_t)((data)[0] << 8 | (data)[1]); \
        (ptr)->speed_rpm = (uint16_t)((data)[2] << 8 | (data)[3]); \
        (ptr)->given_current = (uint16_t)((data)[4] << 8 | (data)[5]); \
        (ptr)->ecd_diff = (ptr)->raw_ecd - (ptr)->last_raw_ecd; \
        if ((ptr)->ecd_diff < -4096) \
        { \
            (ptr)->round_cnt++; \
            (ptr)->ecd_raw_rate = (ptr)->ecd_diff + 8191; \
        } \
        else if ((ptr)->ecd_diff > 4096) \
        { \
            (ptr)->round_cnt--; \
            (ptr)->ecd_raw_rate = (ptr)->ecd_diff - 8191; \
        } \
        else \
        { \
            (ptr)->ecd_raw_rate = (ptr)->ecd_diff; \
        } \
        (ptr)->deal_ecd = (ptr)->raw_ecd + (ptr)->round_cnt * 8191; \
        (ptr)->ecd_angle = ((float)(((ptr)->raw_ecd - (ptr)->ecd_bias) * 360 / 8191) + (ptr)->round_cnt * 360) ; \
        (ptr)->rate_buf[(ptr)->buf_count++] = (ptr)->ecd_raw_rate; \
        if ((ptr)->buf_count == RATE_BUF_SIZE) \
        { \
            (ptr)->buf_count = 0; \
        } \
        for (i = 0; i < RATE_BUF_SIZE; i++) \
        { \
            temp_sum += (ptr)->rate_buf[i]; \
        } \
        (ptr)->avg_rate = (int32_t)(temp_sum / RATE_BUF_SIZE); \
    }
/*
motor data, 4:yaw gimbal motor 6020;5:pitch gimbal motor 6020;
电机数据,4:yaw云台电机 6020电机; 5:pitch云台电机 6020电机*/
motor_measure_t motor_chassis[4];

static CAN_TxHeaderTypeDef  gimbal_tx_message;
static uint8_t              gimbal_can_send_data[8];
// static CAN_TxHeaderTypeDef  chassis_tx_message;
// static uint8_t              chassis_can_send_data[8];

/**
  * @brief          hal CAN fifo call back, receive motor data
  * @param[in]      hcan, the point to CAN handle
  * @retval         none
  */
/**
  * @brief          hal库CAN回调函数,接收电机数据
  * @param[in]      hcan:CAN句柄指针
  * @retval         none
  */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[8];

    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data);

    switch (rx_header.StdId)
    {
//         case CAN_3508_M1_ID:
// //							get_motor_measure(&motor_chassis[0], rx_data);
// //							break;
//         case CAN_3508_M2_ID:
// //							get_motor_measure(&motor_chassis[1], rx_data);
// //							break;
//         case CAN_3508_M3_ID:
//         case CAN_3508_M4_ID:
        case CAN_YAW_MOTOR_ID:
        case CAN_PIT_MOTOR_ID:
        case CAN_TRIGGER_MOTOR_ID:
        {
            static uint8_t i = 0;
            //get motor id
            i = rx_header.StdId - CAN_YAW_MOTOR_ID;
						get_motor_measure(&motor_chassis[i], rx_data);
//            get_motor_measure(&motor_chassis[0], rx_data);
//						get_motor_measure(&motor_chassis[1], rx_data);
            break;
        }

        default:
        {
            break;
        }
    }
}



/**
  * @brief          send control current of motor (0x205, 0x206, 0x207, 0x208)
  * @param[in]      yaw: (0x205) 6020 motor control current, range [-30000,30000] 
  * @param[in]      pitch: (0x206) 6020 motor control current, range [-30000,30000]
  * @param[in]      shoot: (0x207) 2006 motor control current, range [-10000,10000]
  * @param[in]      rev: (0x208) reserve motor control current
  * @retval         none
  */
/**
  * @brief          发送电机控制电流(0x205,0x206,0x207,0x208)
  * @param[in]      yaw: (0x205) 6020电机控制电流, 范围 [-30000,30000]
  * @param[in]      pitch: (0x206) 6020电机控制电流, 范围 [-30000,30000]
  * @param[in]      shoot: (0x207) 2006电机控制电流, 范围 [-10000,10000]
  * @param[in]      rev: (0x208) 保留，电机控制电流
  * @retval         none
  */
void CAN_cmd_gimbal(int16_t yaw, int16_t pitch, int16_t shoot, int16_t rev)
{
   uint32_t send_mail_box;
   gimbal_tx_message.StdId = CAN_GIMBAL_ALL_ID;
   gimbal_tx_message.IDE = CAN_ID_STD;
   gimbal_tx_message.RTR = CAN_RTR_DATA;
   gimbal_tx_message.DLC = 0x08;
   gimbal_can_send_data[0] = (yaw >> 8);
   gimbal_can_send_data[1] = yaw;
   gimbal_can_send_data[2] = (pitch >> 8);
   gimbal_can_send_data[3] = pitch;
   gimbal_can_send_data[4] = (shoot >> 8);
   gimbal_can_send_data[5] = shoot;
   gimbal_can_send_data[6] = (rev >> 8);
   gimbal_can_send_data[7] = rev;
   HAL_CAN_AddTxMessage(&GIMBAL_CAN, &gimbal_tx_message, gimbal_can_send_data, &send_mail_box);
}

/**
  * @brief          send CAN packet of ID 0x700, it will set chassis motor 3508 to quick ID setting
  * @param[in]      none
  * @retval         none
  */
/**
  * @brief          发送ID为0x700的CAN包,它会设置3508电机进入快速设置ID
  * @param[in]      none
  * @retval         none
  */
void CAN_cmd_chassis_reset_ID(void)
{
    uint32_t send_mail_box;
    chassis_tx_message.StdId = 0x700;
    chassis_tx_message.IDE = CAN_ID_STD;
    chassis_tx_message.RTR = CAN_RTR_DATA;
    chassis_tx_message.DLC = 0x08;
    chassis_can_send_data[0] = 0;
    chassis_can_send_data[1] = 0;
    chassis_can_send_data[2] = 0;
    chassis_can_send_data[3] = 0;
    chassis_can_send_data[4] = 0;
    chassis_can_send_data[5] = 0;
    chassis_can_send_data[6] = 0;
    chassis_can_send_data[7] = 0;

    HAL_CAN_AddTxMessage(&CHASSIS_CAN, &chassis_tx_message, chassis_can_send_data, &send_mail_box);
}




/**
 * @brief          return the yaw 6020 motor data point
 * @param[in]      none
 * @retval         motor data point
 */
/**
 * @brief          返回yaw 6020电机数据指针
 * @param[in]      none
 * @retval         电机数据指针
 */
const motor_measure_t *get_yaw_gimbal_motor_measure_point(void)
{
   return &motor_chassis[4];
}

/**
 * @brief          return the pitch 6020 motor data point
 * @param[in]      none
 * @retval         motor data point
 */
/**
 * @brief          返回pitch 6020电机数据指针
 * @param[in]      none
 * @retval         电机数据指针
 */
const motor_measure_t *get_pitch_gimbal_motor_measure_point(void)
{
   return &motor_chassis[5];
}


/**
 * @brief          return the trigger 2006 motor data point
 * @param[in]      none
 * @retval         motor data point
 */
/**
 * @brief          返回拨弹电机 2006电机数据指针
 * @param[in]      none
 * @retval         电机数据指针
 */
const motor_measure_t *get_trigger_motor_measure_point(void)
{
   return &motor_chassis[6];
}

