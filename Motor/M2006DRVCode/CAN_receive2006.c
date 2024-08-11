/**
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
#include "CAN_receive2006.h"
#include "main.h"
/*
  * @param[in]      motor1: (0x201) 2006电机控制电流, 范围 [-16384,16384]
  * @param[in]      motor2: (0x202) 2006电机控制电流, 范围 [-16384,16384]
  * @param[in]      motor3: (0x203) 2006电机控制电流, 范围 [-16384,16384]
  * @param[in]      motor4: (0x204) 2006电机控制电流, 范围 [-16384,16384]
*/


extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;
//motor data read
#define get_motor_measure(ptr, data)                                    \
    {                                                                   \
        uint8_t i = 0; /*循环计数用*/    \ 
        int32_t temp_sum = 0; /*暂时累积数*/ \
        (ptr)->last_raw_ecd = (ptr)->raw_ecd; /*记录此刻编码值为上一刻编码值*/ \
				(ptr)->raw_ecd=(uint16_t)((data)[0] << 8 | (data)[1]); /*记录此刻编码值*/\
        (ptr)->speed_rpm = (uint16_t)((data)[2] << 8 | (data)[3]); /*记录此刻转子速度(RPM)*/\
        (ptr)->given_current = (uint16_t)((data)[4] << 8 | (data)[5]); /*记录此刻通过电流值*/\
        (ptr)->ecd_diff = (ptr)->raw_ecd - (ptr)->last_raw_ecd; /*记录此刻编码值与上一刻编码值的差*/\
        if ((ptr)->ecd_diff < -4096) \
        { /*判断当差值小于-4096时*/ \
            (ptr)->round_cnt++; /*记录此刻圈数+1*/ \
            (ptr)->ecd_raw_rate = (ptr)->ecd_diff + 8191; /*记录此刻编码值+8191*/ \
        } \
        else if ((ptr)->ecd_diff > 4096) \
        {  /*判断当差值大于4096时*/ \
            (ptr)->round_cnt--;/*记录此刻圈数-1*/ \
            (ptr)->ecd_raw_rate = (ptr)->ecd_diff - 8191;/*记录此刻编码值-8191*/ \
        } \
        else \
        { \
            (ptr)->ecd_raw_rate = (ptr)->ecd_diff; /*记录此刻编码速率*/ \
        } \
        (ptr)->deal_ecd = (ptr)->raw_ecd + (ptr)->round_cnt * 8191; /*转子累积编码*/ \
        (ptr)->ecd_angle = ((float)(((ptr)->raw_ecd - (ptr)->ecd_bias) * 360 / 8191) + (ptr)->round_cnt * 360) / 36; /*轴转累积角度*/ \
        (ptr)->rate_buf[(ptr)->buf_count++] = (ptr)->ecd_raw_rate;/*均值滤波*/ \
        if ((ptr)->buf_count == RATE_BUF_SIZE) \
        { \
            (ptr)->buf_count = 0; \
        } \
        for (i = 0; i < RATE_BUF_SIZE; i++) \
        { \
            temp_sum += (ptr)->rate_buf[i]; \
        } \
        (ptr)->avg_rate = (int32_t)(temp_sum / RATE_BUF_SIZE); /*记录此刻平均速度*/\
    }
/*
motor data,  0:chassis motor1 2006;1:chassis motor3 2006;2:chassis motor3 2006;3:chassis motor4 2006;
电机数据, 0:底盘电机1 2006电机,  1:底盘电机2 2006电机,2:底盘电机3 2006电机,3:底盘电机4 2006电机;
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
  * @brief          hal库CAN回调函数,接收电机数据
  * @param[in]      hcan:CAN句柄指针
  * @retval         none
  */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef rx_header; // 定义CAN消息头结构体变量
    uint8_t rx_data[8]; // 定义一个8字节大小的数组，用于存储接收到的数据

    // 从CAN总线获取FIFO0中的消息，包括消息头和数据
    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data);

    // 根据接收到的消息ID进行判断，调用相应的处理函数
    switch (rx_header.StdId) // 标准ID字段
    {
        case CAN_2006_M1_ID: // 假设CAN_2006_M1_ID是电机1的ID
        {
            // 调用get_motor_measure函数处理电机1的数据
            get_motor_measure(&motor_chassis[0], rx_data);
            break;
        }
        case CAN_2006_M2_ID: // 假设CAN_2006_M2_ID是电机2的ID
        {
            // 调用get_motor_measure函数处理电机2的数据
            get_motor_measure(&motor_chassis[1], rx_data);
            break;
        }
        case CAN_2006_M3_ID: // 假设CAN_2006_M3_ID是电机3的ID
        {
            // 调用get_motor_measure函数处理电机3的数据
            get_motor_measure(&motor_chassis[2], rx_data);
            break;
        }
        case CAN_2006_M4_ID: // 假设CAN_2006_M4_ID是电机4的ID
        {
            // 调用get_motor_measure函数处理电机4的数据
            get_motor_measure(&motor_chassis[3], rx_data);
            break;
        }
        default:
        {
            // 如果接收到的消息ID不是预期的电机ID，则不执行任何操作
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
  * @brief          发送ID为0x700的CAN包,它会设置2006电机进入快速设置ID
  * @param[in]      none
  * @retval         none
  */
void CAN_cmd_chassis_reset_ID(void)
{
    void CAN_cmd_chassis_reset_ID(void)
{
    uint32_t send_mail_box; // 用于存储发送邮箱的变量

    // 配置要发送的CAN消息
    chassis_tx_message.StdId = 0x700; // 设置标准ID为0x700
    chassis_tx_message.IDE = CAN_ID_STD; // 设置为标准ID标识扩展
    chassis_tx_message.RTR = CAN_RTR_DATA; // 设置为数据帧，非远程传输请求
    chassis_tx_message.DLC = 0x08; // 设置数据长度为8字节

    // 初始化发送的数据数组，填充8个0值
    chassis_can_send_data[0] = 0;
    chassis_can_send_data[1] = 0;
    chassis_can_send_data[2] = 0;
    chassis_can_send_data[3] = 0;
    chassis_can_send_data[4] = 0;
    chassis_can_send_data[5] = 0;
    chassis_can_send_data[6] = 0;
    chassis_can_send_data[7] = 0;

    // 将CAN消息添加到传输队列，并获取发送邮箱编号
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
  * @brief          发送电机控制电流(0x201,0x202,0x203,0x204)
  * @param[in]      motor1: (0x201) 2006电机控制电流, 范围 [-16384,16384]
  * @param[in]      motor2: (0x202) 2006电机控制电流, 范围 [-16384,16384]
  * @param[in]      motor3: (0x203) 2006电机控制电流, 范围 [-16384,16384]
  * @param[in]      motor4: (0x204) 2006电机控制电流, 范围 [-16384,16384]
  * @retval         none
  */
void CAN_cmd_chassis(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4)
{
    uint32_t send_mail_box; // 用于存储发送邮箱的变量

    // 配置要发送的CAN消息
    chassis_tx_message.StdId = CAN_CHASSIS_ALL_ID; // 设置标准ID，用于底盘所有电机
    chassis_tx_message.IDE = CAN_ID_STD; // 设置为标准ID，非扩展ID
    chassis_tx_message.RTR = CAN_RTR_DATA; // 设置为数据帧，非远程传输请求
    chassis_tx_message.DLC = 0x08; // 设置数据长度为8字节

    // 将电机的控制值分为高8位和低8位，存储到发送数据数组中
    chassis_can_send_data[0] = motor1 >> 8; // 电机1的高8位
    chassis_can_send_data[1] = motor1;       // 电机1的低8位
    chassis_can_send_data[2] = motor2 >> 8; // 电机2的高8位
    chassis_can_send_data[3] = motor2;       // 电机2的低8位
    chassis_can_send_data[4] = motor3 >> 8; // 电机3的高8位
    chassis_can_send_data[5] = motor3;       // 电机3的低8位
    chassis_can_send_data[6] = motor4 >> 8; // 电机4的高8位
    chassis_can_send_data[7] = motor4;       // 电机4的低8位

    // 将CAN消息添加到传输队列，并获取发送邮箱编号
    HAL_CAN_AddTxMessage(&CHASSIS_CAN, &chassis_tx_message, chassis_can_send_data, &send_mail_box);
}

/**
  * @brief          return the chassis 2006 motor data point
  * @param[in]      i: motor number,range [0,3]
  * @retval         motor data point
  */
/**
  * @brief          返回底盘电机 2006电机数据指针
  * @param[in]      i: 电机编号,范围[0,3]
  * @retval         电机数据指针
  */
const Motor_Measure_T *get_chassis_motor_measure_point(uint8_t i)
{
    return &motor_chassis[(i & 0x03)];
}
