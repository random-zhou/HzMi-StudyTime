#ifndef __PID_H__
#define __PID_H__
#include "stm32f4xx.h"


enum PID_MODE
{
  PID_POSITION = 0,//λ�û�
  PID_DELTA  //λ�û�
};
 
typedef struct
{
  uint8_t mode;
  //PID ������
  float Kp;
  float Ki;
  float Kd;
 
  float max_out;  //������
  float max_iout; //���������
 
  float set;
  float fdb;
 
  float out;
  float Pout;
  float Iout;
  float Dout;
  float Dbuf[3];  //΢���� 0���� 1��һ�� 2���ϴ�
  float error[3]; //����� 0���� 1��һ�� 2���ϴ�
 
} pid_type_def;
 
void LimitMax(float input, float max);
void PID_Init(pid_type_def *pid, uint8_t mode, const float PID[3], float max_out, float max_iout);
float PID_Calc(pid_type_def *pid, float ref, float set);
void PID_Clear(pid_type_def *pid);
 


#endif

