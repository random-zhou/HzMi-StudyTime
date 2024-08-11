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
    CAN_2006_M1_ID = 0x201,
    CAN_2006_M2_ID = 0x202,
    CAN_2006_M3_ID = 0x203,
    CAN_2006_M4_ID = 0x204,

//    CAN_YAW_MOTOR_ID = 0x205,
//    CAN_PIT_MOTOR_ID = 0x206,
//    CAN_TRIGGER_MOTOR_ID = 0x207,
//    CAN_GIMBAL_ALL_ID = 0x1FF,

} can_msg_id_e;

//rm motor data
typedef struct
{
  int32_t	 	speed_rpm;//���ת��ת��
		int32_t   avg_rate;	//�������ת��ƽ���ٶ�
		int32_t  	given_current;//��������
		int32_t  	temperate;//�¶�
		int32_t 	raw_ecd;				//δ����ʵʱ����abs angle range:[0,8191]
		int32_t 	last_raw_ecd;	//δ�����ϴα���abs angle range:[0,8191]
		int32_t  deal_ecd;//��������������
		int32_t  ecd_diff;//���α���֮���ֵ
	  int32_t  ecd_raw_rate;	//ͨ������������õ��ı����ٶ�ԭʼֵ
    float 	ecd_angle;		//�����ۻ��Ƕ�
		int32_t ecd_bias;						   //��ʼ������ֵ
		int32_t buf_count;						 //�˲�����buf��
	  int32_t rate_buf[RATE_BUF_SIZE];	     //buf��for filter
		int32_t		round_cnt;//ĿǰȦ��
} Motor_Measure_T;



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
  * @brief          ���͵�����Ƶ���(0x201,0x202,0x203,0x204)
  * @param[in]      motor1: (0x201) 3508������Ƶ���, ��Χ [-16384,16384]
  * @param[in]      motor2: (0x202) 3508������Ƶ���, ��Χ [-16384,16384]
  * @param[in]      motor3: (0x203) 3508������Ƶ���, ��Χ [-16384,16384]
  * @param[in]      motor4: (0x204) 3508������Ƶ���, ��Χ [-16384,16384]
  * @retval         none
  */
extern void CAN_cmd_chassis(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4);

/**
  * @brief          return the chassis 3508 motor data point
  * @param[in]      i: motor number,range [0,3]
  * @retval         motor data point
  */
/**
  * @brief          ���ص��̵�� 3508�������ָ��
  * @param[in]      i: ������,��Χ[0,3]
  * @retval         �������ָ��
  */
extern const Motor_Measure_T *get_chassis_motor_measure_point(uint8_t i);


#endif
