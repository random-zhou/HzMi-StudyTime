/*
 * PID.h
 *
 *  Created on: 2021��10��24��
 *      Author: LBQ
 */
#ifndef __PID_H__
#define __PID_H__

#include "main.h"
#include "user_lib.h"


//typedef __packed struct
//typedef struct __attribute__((packed))	// PID�ṹ�岻�漰λ������Բ����ֽڶ���
typedef struct
{
    float   Now_Val;            // ��ǰֵ
	float   Last_Val;			// �ϴ�ֵ
	float   EX_Last;			// �ϴ�����ֵ
    float   EX_Val;             // ����ֵ

    float   Err_Now;            // ��ǰ���
    float   Err_ABS;            // ��ǰ������ֵ
    float   Err_Last;           // �ϴ����
    float   Err_LastLast;       // ���ϴ����
    float   Err_Sum;            // ����ۻ�

    float   Kp;                 // ����ϵ��
    float   Ki;                 // ����ϵ��
    float   Kd;                 // ΢��ϵ��

	float   p_Max;              // ����������޷�
    float   i_Max;              // �������޷�
	float   d_Max;              // ΢��������޷�
	float   sum_Max;			// �ۻ�����޷�
	float   out_Max;            // ����޷�
	
    float   Output_p;           // ���������
    float   Output_i;           // ���������
    float   Output_d;           // ΢�������
    float   Output_dd;          // �ϴ�΢�������
    float   Output_Last;        // �ϴ����ֵ
	float   Output;             // ���
} PIDTypeDef_t;

enum SpeedPID_ID_e {
	SpeedPID_ChassisM1 = 0,
	SpeedPID_ShootM,
	SpeedPID_GimbalPitch,
	SpeedPID_GimbalYaw,
	SpeedPID_GimbalPitch_Relative,
	SpeedPID_NUM
};

enum AnglePID_ID_e {
	AnglePID_GimbalPitch = 0,
	AnglePID_GimbalYaw,
	AnglePID_GimbalPitch_Relative,
	AnglePID_NUM
};

typedef struct {
	PIDTypeDef_t *BaseStructInstance;	// ����PID����ָ��
	float ILErr;				// ���������������Χ����
	float ISErr;				// ���������������Χ����
	float outPutLimit;			// ���������
	float onlineK;				// ǿ���ñ���
} PIDProfessTypeDef_t;			// ר��PID��������

extern	PIDTypeDef_t PID_Mortor_Speed[SpeedPID_NUM];
extern	PIDTypeDef_t PID_Mortor_Angle[AnglePID_NUM];
extern	PIDTypeDef_t PID_IMU_Temp;

extern	void PID_Param2_Init(PIDTypeDef_t *pid, uint8_t num, const float param[][5]);
extern	void PID_Init(void);
extern	void PID_Calc_Original(PIDTypeDef_t *pid, float ref, float set);
extern	void PID_Calc(PIDTypeDef_t *pid, float ref, float set);
extern	void PID_Calc_Incremental(PIDTypeDef_t *pid, float ref, float set);
extern	void PID_Profess(PIDTypeDef_t *pid, PIDProfessTypeDef_t *pp, float ref, float set);
extern	void PID_Clear(PIDTypeDef_t *pid);

#endif

