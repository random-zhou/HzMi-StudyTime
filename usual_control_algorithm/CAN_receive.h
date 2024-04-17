/**
  ****************************(C) COPYRIGHT 2019 DJI****************************
  * @file       can_receive.c/h
  * @brief      there is CAN interrupt function  to receive motor data,
  *             and CAN send function to send motor current to control motor.
  *             这里是CAN中断接收函数，接收电机数据,CAN发送函数发送电机电流控制电机.
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Dec-26-2018     RM              1. done
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2019 DJI****************************
  */

#ifndef CAN_RECEIVE_H
#define CAN_RECEIVE_H
#define RATE_BUF_SIZE 6
#include "struct_typedef.h"

#define CHASSIS_CAN hcan1
#define GIMBAL_CAN hcan2

/* CAN send and receive ID */
typedef enum
{
    CAN_CHASSIS_ALL_ID = 0x200,
    CAN_3508_M1_ID = 0x201,
    CAN_3508_M2_ID = 0x202,
    CAN_3508_M3_ID = 0x203,
    CAN_3508_M4_ID = 0x204,

    CAN_YAW_MOTOR_ID = 0x205,
    CAN_PIT_MOTOR_ID = 0x206,
    CAN_TRIGGER_MOTOR_ID = 0x207,
    CAN_GIMBAL_ALL_ID = 0x1FF,

} can_msg_id_e;

//rm motor data
typedef struct
{
    int32_t	 	speed_rpm;//电机转子转速
		int32_t   avg_rate;	//处理后电机转子平均速度
		int32_t  	given_current;//给定电流
		int32_t  	temperate;//温度
		int32_t 	raw_ecd;				//未处理实时编码abs angle range:[0,8191]
		int32_t 	last_raw_ecd;	//未处理上次编码abs angle range:[0,8191]
		int32_t  deal_ecd;//处理后的连续编码
		int32_t  ecd_diff;//两次编码之间差值
	  int32_t  ecd_raw_rate;	//通过编码器计算得到的编码速度原始值
    float 	ecd_angle;		//编码累积角度
		int32_t ecd_bias;						   //初始编码器值
		int32_t buf_count;						 //滤波更新buf用
	  int32_t rate_buf[RATE_BUF_SIZE];	     //buf，for filter
		int32_t		round_cnt;//目前圈数
		int32_t		total_ecd;//目前编码总数
    int32_t	offset_ecd;//补偿编码
} motor_measure_t;


///**
//  * @brief          send control current of motor (0x205, 0x206, 0x207, 0x208)
//  * @param[in]      yaw: (0x205) 6020 motor control current, range [-30000,30000] 
//  * @param[in]      pitch: (0x206) 6020 motor control current, range [-30000,30000]
//  * @param[in]      shoot: (0x207) 2006 motor control current, range [-10000,10000]
//  * @param[in]      rev: (0x208) reserve motor control current
//  * @retval         none
//  */
///**
//  * @brief          发送电机控制电流(0x205,0x206,0x207,0x208)
//  * @param[in]      yaw: (0x205) 6020电机控制电流, 范围 [-30000,30000]
//  * @param[in]      pitch: (0x206) 6020电机控制电流, 范围 [-30000,30000]
//  * @param[in]      shoot: (0x207) 2006电机控制电流, 范围 [-10000,10000]
//  * @param[in]      rev: (0x208) 保留，电机控制电流
//  * @retval         none
//  */
//extern void CAN_cmd_gimbal(int16_t yaw, int16_t pitch, int16_t shoot, int16_t rev);

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
extern void CAN_cmd_chassis_reset_ID(void);

/**
  * @brief          send control current of motor (0x201, 0x202, 0x203, 0x204)
  * @param[in]      motor1: (0x201) 3508 motor control current, range [-16384,16384] 
  * @param[in]      motor2: (0x202) 3508 motor control current, range [-16384,16384] 
  * @param[in]      motor3: (0x203) 3508 motor control current, range [-16384,16384] 
  * @param[in]      motor4: (0x204) 3508 motor control current, range [-16384,16384] 
  * @retval         none
  */
/**
  * @brief          发送电机控制电流(0x201,0x202,0x203,0x204)
  * @param[in]      motor1: (0x201) 3508电机控制电流, 范围 [-16384,16384]
  * @param[in]      motor2: (0x202) 3508电机控制电流, 范围 [-16384,16384]
  * @param[in]      motor3: (0x203) 3508电机控制电流, 范围 [-16384,16384]
  * @param[in]      motor4: (0x204) 3508电机控制电流, 范围 [-16384,16384]
  * @retval         none
  */
extern void CAN_cmd_chassis(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4);

///**
//  * @brief          return the yaw 6020 motor data point
//  * @param[in]      none
//  * @retval         motor data point
//  */
///**
//  * @brief          返回yaw 6020电机数据指针
//  * @param[in]      none
//  * @retval         电机数据指针
//  */
//extern const motor_measure_t *get_yaw_gimbal_motor_measure_point(void);

///**
//  * @brief          return the pitch 6020 motor data point
//  * @param[in]      none
//  * @retval         motor data point
//  */
///**
//  * @brief          返回pitch 6020电机数据指针
//  * @param[in]      none
//  * @retval         电机数据指针
//  */
//extern const motor_measure_t *get_pitch_gimbal_motor_measure_point(void);

///**
//  * @brief          return the trigger 2006 motor data point
//  * @param[in]      none
//  * @retval         motor data point
//  */
///**
//  * @brief          返回拨弹电机 2006电机数据指针
//  * @param[in]      none
//  * @retval         电机数据指针
//  */
//extern const motor_measure_t *get_trigger_motor_measure_point(void);

/**
  * @brief          return the chassis 3508 motor data point
  * @param[in]      i: motor number,range [0,3]
  * @retval         motor data point
  */
/**
  * @brief          返回底盘电机 3508电机数据指针
  * @param[in]      i: 电机编号,范围[0,3]
  * @retval         电机数据指针
  */
extern const motor_measure_t *get_chassis_motor_measure_point(uint8_t i);


#endif
