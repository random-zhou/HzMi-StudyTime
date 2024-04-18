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


//用于初始化位置式pid参数的函数
void POS_PID_Init(PID *PID,float p,float i,float d,float maxI,float maxOut)
{
    PID->Kp_pos=p;
    PID->ki_pos=i;
    PID->kd_pos=d;
    PID->maxIntegral=maxI;
    PID->maxOutput=maxOut;//MAX=10000（默认）
}

//用于初始化pid参数的函数
void PID_Init(PID *pid,float p,float i,float d,float maxOut)
{
    pid->kp=p;
    pid->ki=i;
    pid->kd=d;
    pid->maxOutput=maxOut;//MAX=10000（默认）
}

//增量式pid
//参数为(pid结构体,目标值,反馈值)，计算结果放在pid结构体的output成员中
void PID_Calc(PID *pid,float reference,float feedback)
{
//    float dout=0;
//    float pout=0;
    cfloat32 in;
    cfloat32 out;
    //更新数据
    pid->error=0;
    pid->error=reference-feedback;//计算新error
//    //计算微分
    dout=(pid->error-2*pid->lastError+pid->prev_error)*pid->kd;
//    //计算比例
    pout=(pid->error-pid->lastError)*pid->kp;
    //计算积分
   pid->integral=pid->error*pid->ki;

    //计算输出
   pid->output=pout+dout+pid->integral;

    pid->prev_error=pid->lastError;//将上上次的error作为预测值
    pid->lastError=pid->error;//将旧error存起来

    //输出限幅
    if(pid->output > pid->maxOutput) pid->output=pid->maxOutput;
    else if(pid->output < -pid->maxOutput) pid->output=-pid->maxOutput;
}
//位置式pid
void PID_POS(PID *PID)
{

    //当前偏差
    PID->ek=PID->SetValue-PID->ActualValue;
    //比例输出控制量
    PID->kpout=PID->Kp_pos*PID->ek;
    //积分输出控制量
    PID->kiout+=PID->ek;
    PID->kiout*=PID->ki_pos;
    //积分限幅
    if(PID->kiout > PID->maxIntegral)
        PID->kiout=0;
    else if(PID->kiout < -PID->maxIntegral) PID->kiout=0;
    //微分输出控制量
    PID->kdout=PID->kd_pos*(PID->ek-PID->ek1);
    //PID控制器的输出控制量
    PID->out=PID->kpout+PID->kiout+PID->kdout;
    //输出限幅
    if(PID->out > PID->maxOutput) PID->out=PID->maxOutput;
    else if(PID->out < -PID->maxOutput) PID->out=PID->maxOutput;
    //历史偏差量赋值
    PID->ek1=PID->ek;
}


