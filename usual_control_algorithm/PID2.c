/*
 * PID.c
 *
 *  Created on: 2021年10月24日
 *      Author: LBQ
 */
#include "PID.h"

PIDTypeDef_t PID_Mortor_Speed[SpeedPID_NUM], PID_Mortor_Angle[AnglePID_NUM];
PIDTypeDef_t PID_IMU_Temp;

//PIDTypeDef_t PIDProfessBaseStruct;
//PIDProfessTypeDef_t PIDProfess;

/*********** PID系数 ***********/
// 电机速度环PID系数
static const float PID_Speed_Param[SpeedPID_NUM][5] =	{
	{0.65f	, 0.10f	, 0	, 10240	, 5120},
	{0.65f	, 0.10f	, 0	, 10240	, 5120},
	{0.65f	, 0.10f	, 0	, 10240	, 8000},
	{120.0f	, 0.015f, 0	, 4000	, 300},
	{0.65f	, 0.10f	, 0	, 10240	, 8000}
};
// 电机位置环PID系数
static const float PID_Angle_Param[AnglePID_NUM][5] =	{
	{5		, 0.10f	, 0		, 25	, 5},
	{1.2f	, 0		, 0.20f	, 20	, 5},
	{1000	, 2.10f	, 600	, 10240 , 8000}
};
// 陀螺仪温度PID系数
static const float PID_IMUTemp_Param[5] =	{200, 10, 0, 1000, 500};

/**
  * @brief          PID系数初始化（二维数组）
  */
void PID_Param2_Init(PIDTypeDef_t *pid, uint8_t num, const float param[][5])
{
    if (pid == NULL) {
        return;
    }
	pid->Kp = param[num][0];
	pid->Ki = param[num][1];
	pid->Kd = param[num][2];
	pid->out_Max = param[num][3];
	pid->i_Max = param[num][4];
	if (pid->Ki != 0.0f) {
		pid->sum_Max = 1.15f * pid->i_Max / pid->Ki;
	}
	PID_Clear(pid);					// 清除数值
}

/**
  * @brief          PID初始化
  */
void PID_Init(void)
{
	uint8_t i = 0;
	
	// 速度环
	for (i = 0; i < SpeedPID_NUM; i ++ ) {
		PID_Param2_Init(&PID_Mortor_Speed[i], i, PID_Speed_Param);
	}
	
	// 位置环
	for (i = 0; i < AnglePID_NUM; i ++ ) {
		PID_Param2_Init(&PID_Mortor_Angle[i], i, PID_Angle_Param);
	}
	
	// 陀螺仪温度环
	PID_IMU_Temp.Kp = PID_IMUTemp_Param[0];
	PID_IMU_Temp.Ki = PID_IMUTemp_Param[1];
	PID_IMU_Temp.Kd = PID_IMUTemp_Param[2];
	PID_IMU_Temp.out_Max = PID_IMUTemp_Param[3];
	PID_IMU_Temp.i_Max = PID_IMUTemp_Param[4];
	if (PID_IMU_Temp.Ki != 0.0f) {
		PID_IMU_Temp.sum_Max = 1.15f * PID_IMU_Temp.i_Max / PID_IMU_Temp.Ki;
	}
	PID_Clear(&PID_IMU_Temp);

	// 初始化专家PID的基类指针
//	PIDProfess.BaseStructInstance = &PIDProfessBaseStruct;
//	PID_Clear(PIDProfess.BaseStructInstance);
}

/**
  * @brief          原始位置式 PID 计算
  * @param[out]		pid : PID结构数据指针
  * @param[in]		ref : 当前值
  * @param[in]		set : 期望值
  */
void PID_Calc_Original(PIDTypeDef_t *pid, float ref, float set)
{
    if (pid == NULL) {
        return;
    }
	// 更新上次误差
	pid->Err_Last = pid->Err_Now;
	// 计算误差
	pid->Now_Val = ref;
	pid->EX_Val = set;
	pid->Err_Now = pid->EX_Val - pid->Now_Val;
	pid->Err_Sum += pid->Err_Now;
	// 位置式 PID 计算
	pid->Output_p = pid->Kp * pid->Err_Now;
	pid->Output_i = pid->Ki * pid->Err_Sum;
	pid->Output_d = pid->Kd * (pid->Err_Now - pid->Err_Last);
//	// 增量式 PID 计算
//	pid->Output_p = pid->Kp * (pid->Err_Now - pid->Err_Last);
//	pid->Output_i = pid->Ki * pid->Err_Now;
//	pid->Output_d = pid->Kd * (pid->Err_Now - 2 * pid->Err_Last + pid->Err_LastLast);
	// 积分项限幅
	USER_LIMIT_MINMAX(pid->Output_i, -pid->i_Max, pid->i_Max);
	USER_LIMIT_MINMAX(pid->Err_Sum, -pid->sum_Max, pid->sum_Max);
	pid->Output = pid->Output_p + pid->Output_i + pid->Output_d;
//	pid->Output += pid->Output_p + pid->Output_i + pid->Output_d;
	// 输出限幅
	USER_LIMIT_MINMAX(pid->Output, -pid->out_Max, pid->out_Max);
}

/**
  * @brief          位置式 PID 计算
  * @param[out]		pid : PID结构数据指针
  * @param[in]		ref : 当前值
  * @param[in]		set : 期望值
  */
void PID_Calc(PIDTypeDef_t *pid, float ref, float set)
{
    if (pid == NULL) {
        return;
    }
	// 递推旧值
	pid->Err_LastLast = pid->Err_Last;
	pid->Err_Last = pid->Err_Now;
	pid->Last_Val = pid->Now_Val;
	pid->EX_Last = pid->EX_Val;
	pid->Output_Last = pid->Output;
	pid->Output_dd = pid->Output_d;
	
	pid->Now_Val = ref;
	// 输出微分先行
	pid->Now_Val = pid->Now_Val * 0.950f + pid->Last_Val * (1.000f - 0.950f);
	pid->EX_Val = set;
	pid->Err_Now = pid->EX_Val - pid->Now_Val;
	// 偏差微分先行
	pid->Err_Now = pid->Err_Now * 0.850f + pid->Err_Last * (1.000f - 0.850f);
	pid->Err_Sum += pid->Err_Now;

	// 位置式 PID 计算
	pid->Output_p = pid->Kp * pid->Err_Now;
	pid->Output_i = pid->Ki * pid->Err_Sum;
	pid->Output_d = pid->Kd * (pid->Err_Now - pid->Err_Last);
	// 微分项不完全微分
	pid->Output_d = pid->Output_d * 0.850f + pid->Output_dd * (1.000f - 0.850f);
	USER_LIMIT_MINMAX(pid->Err_Sum, -pid->sum_Max, pid->sum_Max);
	USER_LIMIT_MINMAX(pid->Output_i, -pid->i_Max, pid->i_Max);
	// 位置式 PID 计算
	pid->Output = pid->Output_p + pid->Output_i + pid->Output_d;
	// 输出不完全微分
	pid->Output = pid->Output * 0.850f + pid->Output_Last * (1.000f - 0.850f);
	USER_LIMIT_MINMAX(pid->Output, -pid->out_Max, pid->out_Max);
}

/**
  * @brief          增量式 PID 计算
  * @param[out]		pid : PID结构数据指针
  * @param[in]		ref : 当前值
  * @param[in]		set : 期望值
  */
void PID_Calc_Incremental(PIDTypeDef_t *pid, float ref, float set)
{
    if (pid == NULL) {
        return;
    }
	// 递推旧值
	pid->Err_LastLast = pid->Err_Last;
	pid->Err_Last = pid->Err_Now;
	pid->Last_Val = pid->Now_Val;
	pid->EX_Last = pid->EX_Val;
	pid->Output_Last = pid->Output;
	pid->Output_dd = pid->Output_d;

	pid->Now_Val = ref;
	// 输出微分先行
	pid->Now_Val = pid->Now_Val * 0.950f + pid->Last_Val * (1.000f - 0.950f);
	pid->EX_Val = set;
	pid->Err_Now = pid->EX_Val - pid->Now_Val;
	// 偏差微分先行
	pid->Err_Now = pid->Err_Now * 0.850f + pid->Err_Last * (1.000f - 0.850f);
	pid->Err_Sum += pid->Err_Now;

	// 增量式 PID 计算
	pid->Output_p = pid->Kp * (pid->Err_Now - pid->Err_Last);
	pid->Output_i = pid->Ki * pid->Err_Now;
	pid->Output_d = pid->Kd * (pid->Err_Now - 2 * pid->Err_Last + pid->Err_LastLast);
	// 微分项不完全微分
	pid->Output_d = pid->Output_d * 0.850f + pid->Output_dd * (1.000f - 0.850f);
	USER_LIMIT_MINMAX(pid->Err_Sum, -pid->sum_Max, pid->sum_Max);
	USER_LIMIT_MINMAX(pid->Output_i, -pid->i_Max, pid->i_Max);
	// 增量式 PID 计算
	pid->Output += pid->Output_p + pid->Output_i + pid->Output_d;
	// 输出不完全微分
	pid->Output = pid->Output * 0.850f + pid->Output_Last * (1.000f - 0.850f);
	USER_LIMIT_MINMAX(pid->Output, -pid->out_Max, pid->out_Max);
}

/**
  * @brief          PID 改进
  * @param[out]		pid : PID结构数据指针
  * @param[in]		ref : 当前值
  * @param[in]		set : 期望值
  */
void PID_Profess(PIDTypeDef_t *pid, PIDProfessTypeDef_t *pp, float ref, float set)
{
    if (pid == NULL || pp == NULL) {
        return;
    }

	float kiIndex = 1.000f;

	// 递推旧值
	pid->Err_LastLast = pid->Err_Last;
	pid->Err_Last = pid->Err_Now;
	pid->Err_ABS = (fabsf)(pid->Err_Now);
	pid->Last_Val = pid->Now_Val;
	pid->EX_Last = pid->EX_Val;
	pid->Output_Last = pid->Output;
	pid->Output_dd = pid->Output_d;

	pid->Now_Val = ref;
	// 输出微分先行
	pid->Now_Val = pid->Now_Val * 0.950f + pid->Last_Val * (1.000f - 0.950f);
	pid->EX_Val = set;
	pid->Err_Now = pid->EX_Val - pid->Now_Val;
	// 偏差微分先行
	pid->Err_Now = pid->Err_Now * 0.850f + pid->Err_Last * (1.000f - 0.850f);
	pid->Err_Sum += pid->Err_Now;
	// 位置式 PID 计算
	pid->Output_p = pid->Kp * pid->Err_Now;
	pid->Output_i = kiIndex * (pid->Ki * pid->Err_Sum);
	pid->Output_d = pid->Kd * (pid->Err_Now - pid->Err_Last);
	// 微分项不完全微分
	pid->Output_d = pid->Output_d * 0.850f + pid->Output_dd * (1.000f - 0.850f);
	USER_LIMIT_MINMAX(pid->Err_Sum, -pid->sum_Max, pid->sum_Max);
	USER_LIMIT_MINMAX(pid->Output_i, -pid->i_Max, pid->i_Max);
	// 遇限削弱积分
	if (fabsf(pid->Output_Last) > pp->outPutLimit) {
		if ((pid->Err_Sum > 0.0f && pid->Err_Now < 0.0f) || (pid->Err_Sum < 0.0f && pid->Err_Now > 0.0f)) {
			pid->Err_Sum += pid->Err_Now;
		}
	} else {
		pid->Err_Sum += pid->Err_Now;
	}
	// 变速积分（线性积分分离
	if (pid->Err_ABS > pp->ILErr) {
		kiIndex = 0.000f;
	} else if (pid->Err_ABS < pp->ISErr) {
		kiIndex = 1.000f;
	} else {
		kiIndex = (pp->ILErr - pid->Err_ABS) / (pp->ILErr - pp->ISErr);
	}
	// 位置式 PID 计算
	pid->Output = pid->Output_p + pid->Output_i + pid->Output_d;
	// 有效偏差
	// 专家PID规则
	if (pid->Err_ABS > pp->ISErr && pid->Err_ABS < pp->ILErr) {
		// 误差不大不小 在正常范围内
		if ((pid->Err_Now * (pid->Err_Now - pid->Err_Last) > 0 && pid->Err_Last * (pid->Err_Last - pid->Err_LastLast) > 0) || (pid->Err_Now - pid->Err_Last) == 0) {
			// 偏差在朝向偏差绝对值增大的方向变化(偏差越来越大), 或者偏差一直为某一固定值
			if (pid->Err_ABS > (pp->ILErr + pp->ISErr) / 2.0f) {
				// 控制器实施较强的控制作用
				pid->Output = pp->onlineK * pid->Output;
			} else {
				// 但是偏差绝对值本身并不是很大
				pid->Output = pid->Output + 0.0f;
			}
//		} else if ((pid->Err_Now * (pid->Err_Now - pid->Err_Last) < 0 && (pid->Err_Now - pid->Err_Last) * (pid->Err_Last - pid->Err_LastLast) > 0) || (pid->Err_Now == 0 && pid->Err_Last == 0)) {
			// 偏差的绝对值向减小的方向变化，或者已经达到平衡状态
			// 此时可以保持控制器输出不变
		} else if (pid->Err_Now * (pid->Err_Now - pid->Err_Last) < 0 && ((pid->Err_Now - pid->Err_Last) * (pid->Err_Last - pid->Err_LastLast) < 0)) {
			// 偏差处于极值极限状态
			if (pid->Err_ABS > (pp->ILErr + pp->ISErr) / 2.0f) {
				pid->Output = pp->onlineK * pid->Output;
			} else {
				// 但是偏差绝对值本身并不是很大
				pid->Output = pid->Output + 0;
			}
		}
	}
	// 输出不完全微分
	pid->Output = pid->Output * 0.850f + pid->Output_Last * (1.000f - 0.850f);
	USER_LIMIT_MINMAX(pid->Output, -pid->out_Max, pid->out_Max);
}

/**
  * @brief          PID 清除数值
  * @param[out]		pid : PID结构数据指针
  * @notice			用于切换模式时清除或保存状态
  */
void PID_Clear(PIDTypeDef_t *pid)
{
    if (pid == NULL) {
        return;
    }
	pid->Last_Val = pid->Now_Val = 0;
	pid->EX_Last = pid->EX_Val = 0;
	
	pid->Err_Now = pid->Err_ABS = pid->Err_Last = pid->Err_LastLast = 0;
	pid->Err_Sum = 0;
	pid->Output_p = pid->Output_i = pid->Output_d = pid->Output_dd = 0;
	pid->Output = pid->Output_Last = 0;
}
