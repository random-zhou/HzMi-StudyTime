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
#include "PID.h"

PIDTypeDef_t PID_Mortor_Speed[SpeedPID_NUM], PID_Mortor_Angle[AnglePID_NUM];
PIDTypeDef_t PID_IMU_Temp;

//PIDTypeDef_t PIDProfessBaseStruct;
//PIDProfessTypeDef_t PIDProfess;

/*********** PIDϵ�� ***********/
// ����ٶȻ�PIDϵ��
static const float PID_Speed_Param[SpeedPID_NUM][5] =	{
	{0.65f	, 0.10f	, 0	, 10240	, 5120},
	{0.65f	, 0.10f	, 0	, 10240	, 5120},
	{0.65f	, 0.10f	, 0	, 10240	, 8000},
	{120.0f	, 0.015f, 0	, 4000	, 300},
	{0.65f	, 0.10f	, 0	, 10240	, 8000}
};
// ���λ�û�PIDϵ��
static const float PID_Angle_Param[AnglePID_NUM][5] =	{
	{5		, 0.10f	, 0		, 25	, 5},
	{1.2f	, 0		, 0.20f	, 20	, 5},
	{1000	, 2.10f	, 600	, 10240 , 8000}
};
// �������¶�PIDϵ��
static const float PID_IMUTemp_Param[5] =	{200, 10, 0, 1000, 500};

/**
  * @brief          PIDϵ����ʼ������ά���飩
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
	PID_Clear(pid);					// �����ֵ
}

/**
  * @brief          PID��ʼ��
  */
void PID_Init(void)
{
	uint8_t i = 0;
	
	// �ٶȻ�
	for (i = 0; i < SpeedPID_NUM; i ++ ) {
		PID_Param2_Init(&PID_Mortor_Speed[i], i, PID_Speed_Param);
	}
	
	// λ�û�
	for (i = 0; i < AnglePID_NUM; i ++ ) {
		PID_Param2_Init(&PID_Mortor_Angle[i], i, PID_Angle_Param);
	}
	
	// �������¶Ȼ�
	PID_IMU_Temp.Kp = PID_IMUTemp_Param[0];
	PID_IMU_Temp.Ki = PID_IMUTemp_Param[1];
	PID_IMU_Temp.Kd = PID_IMUTemp_Param[2];
	PID_IMU_Temp.out_Max = PID_IMUTemp_Param[3];
	PID_IMU_Temp.i_Max = PID_IMUTemp_Param[4];
	if (PID_IMU_Temp.Ki != 0.0f) {
		PID_IMU_Temp.sum_Max = 1.15f * PID_IMU_Temp.i_Max / PID_IMU_Temp.Ki;
	}
	PID_Clear(&PID_IMU_Temp);

	// ��ʼ��ר��PID�Ļ���ָ��
//	PIDProfess.BaseStructInstance = &PIDProfessBaseStruct;
//	PID_Clear(PIDProfess.BaseStructInstance);
}

/**
  * @brief          ԭʼλ��ʽ PID ����
  * @param[out]		pid : PID�ṹ����ָ��
  * @param[in]		ref : ��ǰֵ
  * @param[in]		set : ����ֵ
  */
void PID_Calc_Original(PIDTypeDef_t *pid, float ref, float set)
{
    if (pid == NULL) {
        return;
    }
	// �����ϴ����
	pid->Err_Last = pid->Err_Now;
	// �������
	pid->Now_Val = ref;
	pid->EX_Val = set;
	pid->Err_Now = pid->EX_Val - pid->Now_Val;
	pid->Err_Sum += pid->Err_Now;
	// λ��ʽ PID ����
	pid->Output_p = pid->Kp * pid->Err_Now;
	pid->Output_i = pid->Ki * pid->Err_Sum;
	pid->Output_d = pid->Kd * (pid->Err_Now - pid->Err_Last);
//	// ����ʽ PID ����
//	pid->Output_p = pid->Kp * (pid->Err_Now - pid->Err_Last);
//	pid->Output_i = pid->Ki * pid->Err_Now;
//	pid->Output_d = pid->Kd * (pid->Err_Now - 2 * pid->Err_Last + pid->Err_LastLast);
	// �������޷�
	USER_LIMIT_MINMAX(pid->Output_i, -pid->i_Max, pid->i_Max);
	USER_LIMIT_MINMAX(pid->Err_Sum, -pid->sum_Max, pid->sum_Max);
	pid->Output = pid->Output_p + pid->Output_i + pid->Output_d;
//	pid->Output += pid->Output_p + pid->Output_i + pid->Output_d;
	// ����޷�
	USER_LIMIT_MINMAX(pid->Output, -pid->out_Max, pid->out_Max);
}

/**
  * @brief          λ��ʽ PID ����
  * @param[out]		pid : PID�ṹ����ָ��
  * @param[in]		ref : ��ǰֵ
  * @param[in]		set : ����ֵ
  */
void PID_Calc(PIDTypeDef_t *pid, float ref, float set)
{
    if (pid == NULL) {
        return;
    }
	// ���ƾ�ֵ
	pid->Err_LastLast = pid->Err_Last;
	pid->Err_Last = pid->Err_Now;
	pid->Last_Val = pid->Now_Val;
	pid->EX_Last = pid->EX_Val;
	pid->Output_Last = pid->Output;
	pid->Output_dd = pid->Output_d;
	
	pid->Now_Val = ref;
	// ���΢������
	pid->Now_Val = pid->Now_Val * 0.950f + pid->Last_Val * (1.000f - 0.950f);
	pid->EX_Val = set;
	pid->Err_Now = pid->EX_Val - pid->Now_Val;
	// ƫ��΢������
	pid->Err_Now = pid->Err_Now * 0.850f + pid->Err_Last * (1.000f - 0.850f);
	pid->Err_Sum += pid->Err_Now;

	// λ��ʽ PID ����
	pid->Output_p = pid->Kp * pid->Err_Now;
	pid->Output_i = pid->Ki * pid->Err_Sum;
	pid->Output_d = pid->Kd * (pid->Err_Now - pid->Err_Last);
	// ΢�����ȫ΢��
	pid->Output_d = pid->Output_d * 0.850f + pid->Output_dd * (1.000f - 0.850f);
	USER_LIMIT_MINMAX(pid->Err_Sum, -pid->sum_Max, pid->sum_Max);
	USER_LIMIT_MINMAX(pid->Output_i, -pid->i_Max, pid->i_Max);
	// λ��ʽ PID ����
	pid->Output = pid->Output_p + pid->Output_i + pid->Output_d;
	// �������ȫ΢��
	pid->Output = pid->Output * 0.850f + pid->Output_Last * (1.000f - 0.850f);
	USER_LIMIT_MINMAX(pid->Output, -pid->out_Max, pid->out_Max);
}

/**
  * @brief          ����ʽ PID ����
  * @param[out]		pid : PID�ṹ����ָ��
  * @param[in]		ref : ��ǰֵ
  * @param[in]		set : ����ֵ
  */
void PID_Calc_Incremental(PIDTypeDef_t *pid, float ref, float set)
{
    if (pid == NULL) {
        return;
    }
	// ���ƾ�ֵ
	pid->Err_LastLast = pid->Err_Last;
	pid->Err_Last = pid->Err_Now;
	pid->Last_Val = pid->Now_Val;
	pid->EX_Last = pid->EX_Val;
	pid->Output_Last = pid->Output;
	pid->Output_dd = pid->Output_d;

	pid->Now_Val = ref;
	// ���΢������
	pid->Now_Val = pid->Now_Val * 0.950f + pid->Last_Val * (1.000f - 0.950f);
	pid->EX_Val = set;
	pid->Err_Now = pid->EX_Val - pid->Now_Val;
	// ƫ��΢������
	pid->Err_Now = pid->Err_Now * 0.850f + pid->Err_Last * (1.000f - 0.850f);
	pid->Err_Sum += pid->Err_Now;

	// ����ʽ PID ����
	pid->Output_p = pid->Kp * (pid->Err_Now - pid->Err_Last);
	pid->Output_i = pid->Ki * pid->Err_Now;
	pid->Output_d = pid->Kd * (pid->Err_Now - 2 * pid->Err_Last + pid->Err_LastLast);
	// ΢�����ȫ΢��
	pid->Output_d = pid->Output_d * 0.850f + pid->Output_dd * (1.000f - 0.850f);
	USER_LIMIT_MINMAX(pid->Err_Sum, -pid->sum_Max, pid->sum_Max);
	USER_LIMIT_MINMAX(pid->Output_i, -pid->i_Max, pid->i_Max);
	// ����ʽ PID ����
	pid->Output += pid->Output_p + pid->Output_i + pid->Output_d;
	// �������ȫ΢��
	pid->Output = pid->Output * 0.850f + pid->Output_Last * (1.000f - 0.850f);
	USER_LIMIT_MINMAX(pid->Output, -pid->out_Max, pid->out_Max);
}

/**
  * @brief          PID �Ľ�
  * @param[out]		pid : PID�ṹ����ָ��
  * @param[in]		ref : ��ǰֵ
  * @param[in]		set : ����ֵ
  */
void PID_Profess(PIDTypeDef_t *pid, PIDProfessTypeDef_t *pp, float ref, float set)
{
    if (pid == NULL || pp == NULL) {
        return;
    }

	float kiIndex = 1.000f;

	// ���ƾ�ֵ
	pid->Err_LastLast = pid->Err_Last;
	pid->Err_Last = pid->Err_Now;
	pid->Err_ABS = (fabsf)(pid->Err_Now);
	pid->Last_Val = pid->Now_Val;
	pid->EX_Last = pid->EX_Val;
	pid->Output_Last = pid->Output;
	pid->Output_dd = pid->Output_d;

	pid->Now_Val = ref;
	// ���΢������
	pid->Now_Val = pid->Now_Val * 0.950f + pid->Last_Val * (1.000f - 0.950f);
	pid->EX_Val = set;
	pid->Err_Now = pid->EX_Val - pid->Now_Val;
	// ƫ��΢������
	pid->Err_Now = pid->Err_Now * 0.850f + pid->Err_Last * (1.000f - 0.850f);
	pid->Err_Sum += pid->Err_Now;
	// λ��ʽ PID ����
	pid->Output_p = pid->Kp * pid->Err_Now;
	pid->Output_i = kiIndex * (pid->Ki * pid->Err_Sum);
	pid->Output_d = pid->Kd * (pid->Err_Now - pid->Err_Last);
	// ΢�����ȫ΢��
	pid->Output_d = pid->Output_d * 0.850f + pid->Output_dd * (1.000f - 0.850f);
	USER_LIMIT_MINMAX(pid->Err_Sum, -pid->sum_Max, pid->sum_Max);
	USER_LIMIT_MINMAX(pid->Output_i, -pid->i_Max, pid->i_Max);
	// ������������
	if (fabsf(pid->Output_Last) > pp->outPutLimit) {
		if ((pid->Err_Sum > 0.0f && pid->Err_Now < 0.0f) || (pid->Err_Sum < 0.0f && pid->Err_Now > 0.0f)) {
			pid->Err_Sum += pid->Err_Now;
		}
	} else {
		pid->Err_Sum += pid->Err_Now;
	}
	// ���ٻ��֣����Ի��ַ���
	if (pid->Err_ABS > pp->ILErr) {
		kiIndex = 0.000f;
	} else if (pid->Err_ABS < pp->ISErr) {
		kiIndex = 1.000f;
	} else {
		kiIndex = (pp->ILErr - pid->Err_ABS) / (pp->ILErr - pp->ISErr);
	}
	// λ��ʽ PID ����
	pid->Output = pid->Output_p + pid->Output_i + pid->Output_d;
	// ��Чƫ��
	// ר��PID����
	if (pid->Err_ABS > pp->ISErr && pid->Err_ABS < pp->ILErr) {
		// ����С ��������Χ��
		if ((pid->Err_Now * (pid->Err_Now - pid->Err_Last) > 0 && pid->Err_Last * (pid->Err_Last - pid->Err_LastLast) > 0) || (pid->Err_Now - pid->Err_Last) == 0) {
			// ƫ���ڳ���ƫ�����ֵ����ķ���仯(ƫ��Խ��Խ��), ����ƫ��һֱΪĳһ�̶�ֵ
			if (pid->Err_ABS > (pp->ILErr + pp->ISErr) / 2.0f) {
				// ������ʵʩ��ǿ�Ŀ�������
				pid->Output = pp->onlineK * pid->Output;
			} else {
				// ����ƫ�����ֵ�������Ǻܴ�
				pid->Output = pid->Output + 0.0f;
			}
//		} else if ((pid->Err_Now * (pid->Err_Now - pid->Err_Last) < 0 && (pid->Err_Now - pid->Err_Last) * (pid->Err_Last - pid->Err_LastLast) > 0) || (pid->Err_Now == 0 && pid->Err_Last == 0)) {
			// ƫ��ľ���ֵ���С�ķ���仯�������Ѿ��ﵽƽ��״̬
			// ��ʱ���Ա��ֿ������������
		} else if (pid->Err_Now * (pid->Err_Now - pid->Err_Last) < 0 && ((pid->Err_Now - pid->Err_Last) * (pid->Err_Last - pid->Err_LastLast) < 0)) {
			// ƫ��ڼ�ֵ����״̬
			if (pid->Err_ABS > (pp->ILErr + pp->ISErr) / 2.0f) {
				pid->Output = pp->onlineK * pid->Output;
			} else {
				// ����ƫ�����ֵ�������Ǻܴ�
				pid->Output = pid->Output + 0;
			}
		}
	}
	// �������ȫ΢��
	pid->Output = pid->Output * 0.850f + pid->Output_Last * (1.000f - 0.850f);
	USER_LIMIT_MINMAX(pid->Output, -pid->out_Max, pid->out_Max);
}

/**
  * @brief          PID �����ֵ
  * @param[out]		pid : PID�ṹ����ָ��
  * @notice			�����л�ģʽʱ����򱣴�״̬
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
