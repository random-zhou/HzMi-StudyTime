#ifndef _KALMAN_H_
#define _KALMAN_H_

#include "IFXPORT.h"
#include "zf_common_typedef.h"

//过程噪声协方差,Q增大，动态响应变快，收敛稳定性变坏
//测量噪声协方差,R增大，动态响应变慢，收敛稳定性变好


typedef struct
{
    float LastP;//上次估算协方差 初始化值为0.02
    float Now_P;//当前估算协方差 初始化值为0
    float out;//卡尔曼滤波器输出 初始化值为0
    float Kg;//卡尔曼增益 初始化值为0
    float Q;//过程噪声协方差 初始化值为0.001
    float R;//观测噪声协方差 初始化值为0.543
}KFP;//Kalman Filter parameter

extern KFP gyro_z_str;
extern KFP Motor;
//卡尔曼滤波初始化参数
void Kalman_Init(void);
//获取卡尔曼融合后的数据
float Kalman_getAngle(float dt,float Gyro_rate,float Acc_Angle);
//一维卡尔曼滤波
float kalmanFilter(KFP *kfp,float input);


#endif
