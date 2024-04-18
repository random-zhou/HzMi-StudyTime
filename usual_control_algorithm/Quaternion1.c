/**
  ****************************(C) COPYRIGHT 2024 HzMI****************************
  * @file       Quaternion.c/h
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
//IMU.c
#include "Quaternion.h"

#define RtA         57.295779f  //弧度->角度
#define AtR         0.0174533f  //角度->弧度
//#define Acc_G       0.0011963f
//#define Gyro_G      0.0610351f
//#define Gyro_Gr     0.0010653f

#define Kp 18.0f        //越大更相信加速度计，越小更相信陀螺仪
#define Ki 0.008f
#define halfT 0.001f

float q0 = 1, q1 = 0, q2 = 0, q3 = 0;
float exInt = 0, eyInt = 0, ezInt = 0;
//最终角度
float FilterPitch=0,FilterRoll=0,FilterYaw=0;

float imuyaw,imuyawlast,iyaw,imux;
//直接传入带有单位的陀螺仪数据

void IMU_Update(float gyrox,float gyroy,float gyroz,float accx,float accy,float accz)
{
    float ax=accx,ay=accy,az=accz;
    float gx=gyrox,gy=gyroy,gz=gyroz;
    float norm;
    float vx, vy, vz;
    float ex, ey, ez;
    float q0q0 = q0*q0;
    float q0q1 = q0*q1;
    float q0q2 = q0*q2;
    float q1q1 = q1*q1;
    float q1q3 = q1*q3;
    float q2q2 = q2*q2;
    float q2q3 = q2*q3;
    float q3q3 = q3*q3;
    if(ax*ay*az==0)//此时任意方向角加速度为0
        return;
//    gx *= Gyro_Gr;
//    gy *= Gyro_Gr;
//    gz *= Gyro_Gr;
    //归一化处理，将角加速度单位转为弧度
        gx *= AtR;
        gy *= AtR;
        gz *= AtR;

    norm = sqrt(ax*ax + ay*ay + az*az);
    ax = ax /norm;
    ay = ay / norm;
    az = az / norm;

     // estimated direction of gravity and flux (v and w)
    vx = 2*(q1q3 - q0q2);
    vy = 2*(q0q1 + q2q3);
    vz = q0q0 - q1q1 - q2q2 + q3q3 ;

    // error is sum of cross product between reference direction of fields and direction        measured by sensors
    ex = (ay*vz - az*vy) ;
    ey = (az*vx - ax*vz) ;
    ez = (ax*vy - ay*vx) ;

    exInt = exInt + ex * Ki;
    eyInt = eyInt + ey * Ki;
    ezInt = ezInt + ez * Ki;

  // adjusted gyroscope measurements
    gx = gx + Kp*ex + exInt;
    gy = gy + Kp*ey + eyInt;
    gz = gz + Kp*ez + ezInt;

    // integrate quaternion rate and normalise
    q0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
    q1 = q1 + (q0*gx + q2*gz - q3*gy)*halfT;
    q2 = q2 + (q0*gy - q1*gz + q3*gx)*halfT;
    q3 = q3 + (q0*gz + q1*gy - q2*gx)*halfT;

    // normalise quaternion
    norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);

    q0 = q0 / norm;
    q1 = q1 / norm;
    q2 = q2 / norm;
    q3 = q3 / norm;

//    FilterYaw  = atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2*q2 - 2 * q3* q3 + 1)* RtA;           // yaw
//    FilterPitch    = asin(-2 * q1 * q3 + 2 * q0* q2)* RtA ; //pitch
    FilterRoll    = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* RtA;     //roll


    //取消注释后航向角会变为0
//    // 计算偏航角的增量变化
//        iyaw = imuyaw - imuyawlast;
//        // 当穿越360-0度边界时，纠正偏航的突然跳变
//        if (iyaw < -300) {
//            // 如果偏航角变化的增量小于 -300 度，说明发生了向负方向超过 300 度的突变
//            imux += 360;
//        } else if (iyaw > 300) {
//            // 如果偏航角变化的增量大于 300 度，说明发生了向正方向超过 300 度的突变
//            imux -= 360;
//        }
//        // 更新上一次的偏航测量值
//        imuyawlast = imuyaw;
//        // 将修正值加到偏航上
//        imuyaw += imux;
//        // 用新的偏航值更新imu结构
//        FilterYaw = imuyaw;
//        // 将偏航角度规范化到0到360度范围内
//        if (imuyaw > 360) {
//            // 如果偏航角大于 360 度，则减去一个完整的圈数，使其处于 0 到 360 度之间
//            imuyaw -= 360;
//            FilterYaw = imuyaw;
//        } else if (imuyaw < 0) {
//            // 如果偏航角小于 0 度，则加上一个完整的圈数，使其处于 0 到 360 度之间
//            imuyaw += 360;
//            FilterYaw = imuyaw;
//        }
//        // 计算连续测量之间的偏航角差异
//        float i = imuyaw - imuyawlast;
//        // 标识特定方向，初始化为0
//        int imuflag = 0;
//        // 若偏航角超过-170度，则可能设置一个标志位以进行特殊处理
//        if (FilterYaw < -170) {
//            imuflag = 1;
//        }
//        // 确保偏航角变化`i`在-180到180度范围内，以适应环绕连续性
//        if (i > 180) {
//            i -= 360;
//        } else if (i < -180) {
//            i += 360;
//        }
//        // 累积偏航角变化并更新偏航角
//        imuyaw += i;
//        // 将更新后的偏航角重新存储到imu结构中
//        FilterYaw = imuyaw;



}

