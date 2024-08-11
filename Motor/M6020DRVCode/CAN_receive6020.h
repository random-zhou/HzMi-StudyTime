/*
*
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
    CAN_YAW_MOTOR_ID = 0x205,
    CAN_PIT_MOTOR_ID = 0x206,
    CAN_GIMBAL_ALL_ID = 0x1FF,

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
		int32_t		total_ecd;//Ŀǰ��������
    int32_t	offset_ecd;//��������
} motor_measure_t;


/**
 * @brief          send control current of motor (0x205, 0x206, 0x207, 0x208)
 * @param[in]      yaw: (0x205) 6020 motor control current, range [-30000,30000] 
 * @param[in]      pitch: (0x206) 6020 motor control current, range [-30000,30000]
 * @param[in]      shoot: (0x207) 2006 motor control current, range [-10000,10000]
 * @param[in]      rev: (0x208) reserve motor control current
 * @retval         none
 */
/**
 * @brief          ���͵�����Ƶ���(0x205,0x206,0x207,0x208)
 * @param[in]      yaw: (0x205) 6020������Ƶ���, ��Χ [-30000,30000]
 * @param[in]      pitch: (0x206) 6020������Ƶ���, ��Χ [-30000,30000]
 * @param[in]      shoot: (0x207) 2006������Ƶ���, ��Χ [-10000,10000]
 * @param[in]      rev: (0x208) ������������Ƶ���
 * @retval         none
 */
extern void CAN_cmd_gimbal(int16_t yaw, int16_t pitch, int16_t shoot, int16_t rev);

/**
  * @brief          send CAN packet of ID 0x700, it will set chassis motor 3508 to quick ID setting
  * @param[in]      none
  * @retval         none
  */
/**
  * @brief          ����IDΪ0x700��CAN��,��������3508��������������ID
  * @param[in]      none
  * @retval         none
  */
extern void CAN_cmd_chassis_reset_ID(void);

/**
 * @brief          return the yaw 6020 motor data point
 * @param[in]      none
 * @retval         motor data point
 */
/**
 * @brief          ����yaw 6020�������ָ��
 * @param[in]      none
 * @retval         �������ָ��
 */
extern const motor_measure_t *get_yaw_gimbal_motor_measure_point(void);

/**
 * @brief          return the pitch 6020 motor data point
 * @param[in]      none
 * @retval         motor data point
 */
/**
 * @brief          ����pitch 6020�������ָ��
 * @param[in]      none
 * @retval         �������ָ��
 */
extern const motor_measure_t *get_pitch_gimbal_motor_measure_point(void);

/**
 * @brief          return the trigger 2006 motor data point
 * @param[in]      none
 * @retval         motor data point
 */
/**
 * @brief          ���ز������ 2006�������ָ��
 * @param[in]      none
 * @retval         �������ָ��
 */
extern const motor_measure_t *get_trigger_motor_measure_point(void);



#endif
