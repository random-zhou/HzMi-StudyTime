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


//首先定义PID结构体用于存放一个PID的数据
typedef struct
{
    //以下是增量式pid的参数
    float kp,ki,kd;//三个系数
    float error,lastError;//误差、上次误差
    float integral,maxIntegral;//积分、积分限幅
    float output,maxOutput;//输出、输出限幅
    float reference,feedback;//目标值、实际值
    float prev_error;
    //以下是位置式pid的参数
    float SetValue;       //设定值
    float ActualValue;  //实际值
    float Kp_pos;       //比例系数
    float ki_pos;      //积分系数
    float kd_pos;      //微分系数
    float T;       //采样周期
    float kpout;   //比例输出控制量
    float kiout;   //积分输出控制量
    float kdout;   //微分输出控制量
    float ek;     //当前偏差
    float ek1;     //上一次偏差
    float ek2;     //上上次偏差
    float out;    //输出控制量
}PID;





//增量式PID参数初始化
void PID_Init(PID *pid,float p,float i,float d,float maxOut);
//位置式pid初始化
void POS_PID_Init(PID *PID,float p,float i,float d,float maxI,float maxOut);
//增量式PID计算函数
void PID_Calc(PID *pid,float reference,float feedback);
//位置式pid
void PID_POS(PID *pid);





#endif
