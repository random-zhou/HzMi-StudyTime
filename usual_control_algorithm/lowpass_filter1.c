//    gyro_lpf = lpf_operator(&lpf_current_gyro,imu660ra_gyro_x,0.001);
#include "lowpass_filter.h"

/******************************************************************************/
LowPassFilter  lpf_current_gyro;
/******************************************************************************/

void lpf_init(void)
{

    lpf_current_gyro.Tf = 0.08f;
    lpf_current_gyro.y_prev = 0;

}


/******************************************************************************/
float lpf_operator(LowPassFilter* LPF,float x ,float dt)
{

    float alpha = 0, y = 0;

    alpha = LPF->Tf / (LPF->Tf + dt);
    y = alpha * LPF->y_prev + (1.0f - alpha) * x;
    LPF->y_prev = y;

    return y;
}
/******************************************************************************/
float angle;                //数据融合后的角度



//float acc_ratio = 0.6;      //加速度计比例
//
//float gyro_ratio = 0.38;    //陀螺仪比例

float acc_ratio = 0.000244;      //加速度计比例

float gyro_ratio = 0.06;    //陀螺仪比例


float dt = 0.01;           //采样周期



//----------------------------------------------------------------

//  @brief      一阶互补滤波

//  @param      angle_m     加速度计数据

//  @param      gyro_m      陀螺仪数据

//  @return     float       数据融合后的角度

//----------------------------------------------------------------

float angle_calc(float angle_m, float gyro_m)

{

    float temp_angle;

    float gyro_now;

    float error_angle;



    static float last_angle;

    static uint8 first_angle;



    if(!first_angle)//判断是否为第一次运行本函数

    {

        //如果是第一次运行，则将上次角度值设置为与加速度值一致

        first_angle = 1;

        last_angle = angle_m;

    }



    gyro_now = gyro_m * gyro_ratio;



    //根据测量到的加速度值转换为角度之后与上次的角度值求偏差

    error_angle = (angle_m - last_angle)*acc_ratio;



    //根据偏差与陀螺仪测量得到的角度值计算当前角度值

    temp_angle = last_angle + (error_angle + gyro_now)*dt;



    //保存当前角度值

    last_angle = temp_angle;



    return temp_angle;

}

