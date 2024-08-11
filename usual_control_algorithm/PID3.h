#ifndef __PID_H__
#define __PID_H__
#include "stm32f4xx.h"


enum PID_MODE
{
  PID_POSITION = 0,//位置环
  PID_DELTA  //位置环
};
 
typedef struct
{
  uint8_t mode;
  //PID 三参数
  float Kp;
  float Ki;
  float Kd;
 
  float max_out;  //最大输出
  float max_iout; //最大积分输出
 
  float set;
  float fdb;
 
  float out;
  float Pout;
  float Iout;
  float Dout;
  float Dbuf[3];  //微分项 0最新 1上一次 2上上次
  float error[3]; //误差项 0最新 1上一次 2上上次
 
} pid_type_def;
 
void LimitMax(float input, float max);
void PID_Init(pid_type_def *pid, uint8_t mode, const float PID[3], float max_out, float max_iout);
float PID_Calc(pid_type_def *pid, float ref, float set);
void PID_Clear(pid_type_def *pid);
 


#endif

