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
