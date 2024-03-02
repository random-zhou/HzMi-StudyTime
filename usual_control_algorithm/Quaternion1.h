//IMU.h
#ifndef _IMU_H
#define _IMU_H


#include "IFXPORT.h"
#include "zf_common_typedef.h"

extern float FilterPitch;
extern float FilterRoll;
extern float FilterYaw;
/*************************
*函数名：IMU_Update
*输入：直接传入带有单位的陀螺仪数据
*************************/
void IMU_Update(float gyrox,float gyroy,float gyroz,float accx,float accy,float accz);

#endif
