#include "Kalman.h"





//二维卡尔曼滤波
float Q_angle;
float Q_bias;
float R_measure;

static float angle;   //角度
static float bias;    //陀螺仪漂移
static float rate;    //角速度
static float P[2][2]; //误差协方差矩阵

void Kalman_Init(void)
{
    Q_angle = 9.99999977E-3;//角度噪声协方差
    Q_bias = 5.49999997E-2; //陀螺仪漂移噪声协方差
    R_measure = 0.03f;  //角度测量噪声

    angle = 0.0f; //复位角度
    bias  = 0.0f; //复位陀螺仪漂移

    P[0][0] = 0.0f; //协方差矩阵
    P[0][1] = 0.0f;
    P[1][0] = 0.0f;
    P[1][1] = 0.0f;

}

//dt：周期
//Gyro:陀螺仪角速度值
//Accel：加速度计算出来的角度
float  Kalman_getAngle(float dt,float Gyro_rate,float Acc_Angle)
{

    float K[2];     //卡尔曼增益
    float S;        //计算卡尔曼增益时候的分母
    float angle_err;        //计算最优估计值时的角度误差

    /* Step 1 */
    //基于系统的上一状态的预测值
    rate = Gyro_rate - bias;//陀螺仪：角速度 - 角速度漂移
    angle = angle + rate*dt;//陀螺仪角速度积分成的角度=

    /* Step 2 */
    //对应于X(k|k-1)的协方差更新
    P[0][0] += dt * (dt*P[1][1] - P[0][1] - P[1][0] + Q_angle);
    P[0][1] -= dt * P[1][1];
    P[1][0] -= dt * P[1][1];
    P[1][1] += Q_bias * dt;

    /* Step 3 */
    //计算卡尔曼增益
    S = P[0][0] + R_measure; //分母

    K[0] = P[0][0] / S;
    K[1] = P[1][0] / S;

    /* Step 4 */
    //计算最优估计值
    angle_err = Acc_Angle - angle; //角度误差

    angle += K[0] * angle_err;
    bias  += K[1] * angle_err;

    /* Step 5 */
    //更新k状态下X(k|k)的协方差
    P[0][0] -= K[0] * P[0][0];
    P[0][1] -= K[0] * P[0][1];
    P[1][0] -= K[1] * P[0][0];
    P[1][1] -= K[1] * P[0][1];
    return angle;

}





//一维卡尔曼滤波
//1. 结构体类型定义


//2. 以高度为例 定义卡尔曼结构体并初始化参数
//KFP KFP_height={0.02,0,0,0,0.001,0.543};
KFP gyro_z_str={0.02,0,0,0,0.001f,0.856f};

/**
 *卡尔曼滤波器
 *@param KFP *kfp 卡尔曼结构体参数
 *   float input 需要滤波的参数的测量值（即传感器的采集值）
 *@return 滤波后的参数（最优值）
 */
 float kalmanFilter(KFP *kfp,float input)
 {
     //预测协方差方程：k时刻系统估算协方差 = k-1时刻的系统协方差 + 过程噪声协方差
     kfp->Now_P = kfp->LastP + kfp->Q;
     //卡尔曼增益方程：卡尔曼增益 = k时刻系统估算协方差 / （k时刻系统估算协方差 + 观测噪声协方差）
     kfp->Kg = kfp->Now_P / (kfp->Now_P + kfp->R);
     //更新最优值方程：k时刻状态变量的最优值 = 状态变量的预测值 + 卡尔曼增益 * （测量值 - 状态变量的预测值）
     kfp->out = kfp->out + kfp->Kg * (input -kfp->out);//因为这一次的预测值就是上一次的输出值
     //更新协方差方程: 本次的系统协方差付给 kfp->LastP 威下一次运算准备。
     kfp->LastP = (1-kfp->Kg) * kfp->Now_P;
     return kfp->out;
 }

/**
 *调用卡尔曼滤波器 实践
 */
//int height;
//int kalman_height=0;
//kalman_height = kalmanFilter(&KFP_height,(float)height);

