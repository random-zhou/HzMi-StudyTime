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
#include <PID.h>


//���ڳ�ʼ��λ��ʽpid�����ĺ���
void POS_PID_Init(PID *PID,float p,float i,float d,float maxI,float maxOut)
{
    PID->Kp_pos=p;
    PID->ki_pos=i;
    PID->kd_pos=d;
    PID->maxIntegral=maxI;
    PID->maxOutput=maxOut;//MAX=10000��Ĭ�ϣ�
}

//���ڳ�ʼ��pid�����ĺ���
void PID_Init(PID *pid,float p,float i,float d,float maxOut)
{
    pid->kp=p;
    pid->ki=i;
    pid->kd=d;
    pid->maxOutput=maxOut;//MAX=10000��Ĭ�ϣ�
}

//����ʽpid
//����Ϊ(pid�ṹ��,Ŀ��ֵ,����ֵ)������������pid�ṹ���output��Ա��
void PID_Calc(PID *pid,float reference,float feedback)
{
//    float dout=0;
//    float pout=0;
    cfloat32 in;
    cfloat32 out;
    //��������
    pid->error=0;
    pid->error=reference-feedback;//������error
//    //����΢��
    dout=(pid->error-2*pid->lastError+pid->prev_error)*pid->kd;
//    //�������
    pout=(pid->error-pid->lastError)*pid->kp;
    //�������
   pid->integral=pid->error*pid->ki;

    //�������
   pid->output=pout+dout+pid->integral;

    pid->prev_error=pid->lastError;//�����ϴε�error��ΪԤ��ֵ
    pid->lastError=pid->error;//����error������

    //����޷�
    if(pid->output > pid->maxOutput) pid->output=pid->maxOutput;
    else if(pid->output < -pid->maxOutput) pid->output=-pid->maxOutput;
}
//λ��ʽpid
void PID_POS(PID *PID)
{

    //��ǰƫ��
    PID->ek=PID->SetValue-PID->ActualValue;
    //�������������
    PID->kpout=PID->Kp_pos*PID->ek;
    //�������������
    PID->kiout+=PID->ek;
    PID->kiout*=PID->ki_pos;
    //�����޷�
    if(PID->kiout > PID->maxIntegral)
        PID->kiout=0;
    else if(PID->kiout < -PID->maxIntegral) PID->kiout=0;
    //΢�����������
    PID->kdout=PID->kd_pos*(PID->ek-PID->ek1);
    //PID�����������������
    PID->out=PID->kpout+PID->kiout+PID->kdout;
    //����޷�
    if(PID->out > PID->maxOutput) PID->out=PID->maxOutput;
    else if(PID->out < -PID->maxOutput) PID->out=PID->maxOutput;
    //��ʷƫ������ֵ
    PID->ek1=PID->ek;
}


