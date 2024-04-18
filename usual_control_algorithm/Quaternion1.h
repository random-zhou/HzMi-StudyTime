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
//IMU.h
#ifndef _IMU_H
#define _IMU_H


#include "IFXPORT.h"
#include "zf_common_typedef.h"

extern float FilterPitch;
extern float FilterRoll;
extern float FilterYaw;
/*************************
*��������IMU_Update
*���룺ֱ�Ӵ�����е�λ������������
*************************/
void IMU_Update(float gyrox,float gyroy,float gyroz,float accx,float accy,float accz);

#endif
