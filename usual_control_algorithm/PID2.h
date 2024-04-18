/**
  ****************************(C) COPYRIGHT 2024 HzMI****************************
  * @file       PID.c/h
  * @brief      
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Apr-18-2024      Rz              1. done
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  */
#ifndef __PID_H__
#define __PID_H__

#include "main.h"
#include "user_lib.h"


//typedef __packed struct
//typedef struct __attribute__((packed))	// PID结构体不涉及位运算可以不用字节对齐
typedef struct
{
    float   Now_Val;            // 当前值
	float   Last_Val;			// 上次值
	float   EX_Last;			// 上次期望值
    float   EX_Val;             // 期望值

    float   Err_Now;            // 当前误差
    float   Err_ABS;            // 当前误差绝对值
    float   Err_Last;           // 上次误差
    float   Err_LastLast;       // 上上次误差
    float   Err_Sum;            // 误差累积

    float   Kp;                 // 比例系数
    float   Ki;                 // 积分系数
    float   Kd;                 // 微分系数

	float   p_Max;              // 比例项输出限幅
    float   i_Max;              // 积分项限幅
	float   d_Max;              // 微分项输出限幅
	float   sum_Max;			// 累积误差限幅
	float   out_Max;            // 输出限幅
	
    float   Output_p;           // 比例项输出
    float   Output_i;           // 积分项输出
    float   Output_d;           // 微分项输出
    float   Output_dd;          // 上次微分项输出
    float   Output_Last;        // 上次输出值
	float   Output;             // 输出
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
	PIDTypeDef_t *BaseStructInstance;	// 定义PID基类指针
	float ILErr;				// 积分项误差死区范围上限
	float ISErr;				// 积分项误差死区范围下限
	float outPutLimit;			// 输出项死区
	float onlineK;				// 强作用比率
} PIDProfessTypeDef_t;			// 专家PID规则设置

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

