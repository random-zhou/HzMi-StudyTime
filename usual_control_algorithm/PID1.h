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
#ifndef _PID_H_
#define _PID_H_


//���ȶ���PID�ṹ�����ڴ��һ��PID������
typedef struct
{
    //����������ʽpid�Ĳ���
    float kp,ki,kd;//����ϵ��
    float error,lastError;//���ϴ����
    float integral,maxIntegral;//���֡������޷�
    float output,maxOutput;//���������޷�
    float reference,feedback;//Ŀ��ֵ��ʵ��ֵ
    float prev_error;
    //������λ��ʽpid�Ĳ���
    float SetValue;       //�趨ֵ
    float ActualValue;  //ʵ��ֵ
    float Kp_pos;       //����ϵ��
    float ki_pos;      //����ϵ��
    float kd_pos;      //΢��ϵ��
    float T;       //��������
    float kpout;   //�������������
    float kiout;   //�������������
    float kdout;   //΢�����������
    float ek;     //��ǰƫ��
    float ek1;     //��һ��ƫ��
    float ek2;     //���ϴ�ƫ��
    float out;    //���������
}PID;





//����ʽPID������ʼ��
void PID_Init(PID *pid,float p,float i,float d,float maxOut);
//λ��ʽpid��ʼ��
void POS_PID_Init(PID *PID,float p,float i,float d,float maxI,float maxOut);
//����ʽPID���㺯��
void PID_Calc(PID *pid,float reference,float feedback);
//λ��ʽpid
void PID_POS(PID *pid);





#endif
