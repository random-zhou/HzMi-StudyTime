/**
  ****************************(C) COPYRIGHT 2024 HzMI****************************
  * @file       lowpass_filters.c/h
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
#ifndef LOWPASS_FILTER_H
#define LOWPASS_FILTER_H
#include "zf_common_headfile.h"


/******************************************************************************/
typedef struct
{
    float Tf; //!< Low pass filter time constant
    float y_prev; //!< filtered value in previous execution step
} LowPassFilter;

extern LowPassFilter  lpf_current_gyro;
/******************************************************************************/


void lpf_init(void);
float lpf_operator(LowPassFilter* LPF,float x ,float dt);
float angle_calc(float angle_m, float gyro_m);
/******************************************************************************/

#endif
