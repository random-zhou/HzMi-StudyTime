/**
  ****************************(C) COPYRIGHT 2024 HzMI****************************
  * @file       kalman.c/h
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
#include "kalman.h"

/*****************  一阶卡尔曼  *****************/

typedef struct {
    float x;		// state
    float A;		// x(n)=A*x(n-1)+u(n),u(n)~N(0,q)
    float H;		// z(n)=H*x(n)+w(n),w(n)~N(0,r)
    float q;		// process(predict) noise convariance
    float r;		// measure noise(error) convariance
    float p;		// estimated error convariance
    float gain;		// kalman gain
} kalman1_filter_t;

kalman1_filter_t KF1;

/**
 * @brief			一阶卡尔曼滤波初始化
 * @param[out]		state : 滤波结构数据指针
 * @param[in]		q & r
 */
void kalman1_init(kalman1_filter_t *state, float q, float r)
{
    state->x = 0.0f;
    state->p = 0.0f;
    state->A = 1.0f;
    state->H = 1.0f;
    state->q = q;
    state->r = r;
}

/**
 * @brief			一阶卡尔曼滤波
 * @param[out]		state : 滤波结构数据指针
 * @param[in]		z_measure : 原始数据
 */
float kalman1_filter(kalman1_filter_t *state, float z_measure)
{
    /* Predict */
	// 时间更新(预测): X(k|k-1) = A(k,k-1)*X(k-1|k-1) + B(k)*u(k)
    state->x = state->A * state->x;
    // 更新先验协方差: P(k|k-1) = A(k,k-1)*A(k,k-1)^T*P(k-1|k-1)+Q(k)
    state->p = state->A * state->A * state->p + state->q;

    /* Measurement */
    // 计算卡尔曼增益: K(k) = P(k|k-1)*H(k)^T/(P(k|k-1)*H(k)*H(k)^T + R(k))
    state->gain = state->p * state->H / (state->p * state->H * state->H + state->r);
    // 测量更新(校正): X(k|k) = X(k|k-1)+K(k)*(Z(k)-H(k)*X(k|k-1))
    state->x = state->x + state->gain * (z_measure - state->H * state->x);
    // 更新后验协方差: P(k|k) =（I-K(k)*H(k))*P(k|k-1)
    state->p = (1 - state->gain * state->H) * state->p;

    return state->x;
}

/*****************  二阶卡尔曼  *****************/

#define mat         arm_matrix_instance_f32	// ARM矩阵类型
#define mat_init    arm_mat_init_f32		// 矩阵初始化 将数组地址赋予给ARM矩阵
#define mat_add     arm_mat_add_f32			// 矩阵加法
#define mat_sub     arm_mat_sub_f32			// 矩阵减法
#define mat_mult    arm_mat_mult_f32		// 矩阵乘法
#define mat_trans   arm_mat_trans_f32		// 转置矩阵
#define mat_inv     arm_mat_inverse_f32		// 逆矩阵

typedef struct {
  float raw_value;
  float filtered_value[2];
  mat xhat, xhatminus, z, A, H, AT, HT, Q, R, P, Pminus, K;
} kalman_filter_t;

typedef struct {
  float raw_value;
  float filtered_value[2];
  float xhat_data[2], xhatminus_data[2], z_data[2],Pminus_data[4], K_data[4];
  float P_data[4];
  float AT_data[4], HT_data[4];
  float A_data[4];
  float H_data[4];
  float Q_data[4];
  float R_data[4];
} kalman_filter_init_t;

/*
	测量噪声大 R需要设置的较大
	模型不准确 Q需要增大
	R固定，Q越大，代表越信任侧量值，Q无穷代表只用测量值(Q/R取0无意义)
	Q/R决定了滤波器的稳态频率响应。Q增大和R减小都会导致卡尔曼增益K变大
	卡尔曼增益的值越大，意味着越相信测量值的输出，从而使得估计值倾向于测量值，，收敛速度越快，最优估计值震荡越明显
	A B H 根据模型来确定
	P变大也会导致卡尔曼增益变大，但是很快会迭代至稳定值，因此P的初始值只会对前几个周期的估计值有影响。
 */

kalman_filter_t KF;
kalman_filter_init_t KF_init;
float KFtest = 0;

void kalman_filter_mat_init(kalman_filter_t *F, kalman_filter_init_t *I)
{
	I->Q_data[0] = I->Q_data[3] = 200;
	I->R_data[0] = I->R_data[3] = 300;
	I->A_data[0] = I->A_data[3] = 2;
	I->H_data[0] = I->H_data[3] = 2;
	// 将一维数组地址赋予给ARM矩阵指针 row行, col列
	mat_init(&F->xhat, 2, 1, (float *)I->xhat_data);
	mat_init(&F->xhatminus, 2, 1, (float *)I->xhatminus_data);
	mat_init(&F->z, 2, 1, (float *)I->z_data);
	mat_init(&F->Pminus, 2, 2, (float *)I->Pminus_data);
	mat_init(&F->K, 2, 2, (float *)I->K_data);
	mat_init(&F->P, 2, 2, (float *)I->P_data);
	mat_init(&F->AT, 2, 2, (float *)I->AT_data);
	mat_init(&F->HT, 2, 2, (float *)I->HT_data);
	mat_init(&F->A, 2, 2, (float *)I->A_data);
	mat_init(&F->H, 2, 2, (float *)I->H_data);
	mat_init(&F->Q, 2, 2, (float *)I->Q_data);
	mat_init(&F->R, 2, 2, (float *)I->R_data);
	mat_trans(&F->A, &F->AT);
	mat_trans(&F->H, &F->HT);
}

float *kalman_filter_calc(kalman_filter_t *F, float signal1, float signal2)
{
  float TEMP221_data[4] = {0, 0, 0, 0};
  float TEMP222_data[4] = {0, 0, 0, 0};
  float Num1_data[4] = {1, 1, 1, 1};
  float TEMP211_data[2] = {0, 0};
  float TEMP212_data[2] = {0, 0};
  mat Num1,TEMP221,TEMP222,TEMP211,TEMP212;

  mat_init(&Num1, 2, 2, (float *)Num1_data);
  mat_init(&TEMP221, 2, 2, (float *)TEMP221_data);
  mat_init(&TEMP222, 2, 2, (float *)TEMP222_data);
  mat_init(&TEMP211, 2, 1, (float *)TEMP211_data);
  mat_init(&TEMP211, 2, 1, (float *)TEMP212_data);

  F->z.pData[0] = signal1;
  F->z.pData[1] = signal2;

  //1. xhat'(k)= A xhat(k-1)
  mat_mult(&F->A, &F->xhat, &F->xhatminus);

  //2. P'(k) = A P(k-1) AT + Q
  mat_mult(&F->A, &F->P, &F->Pminus);
  mat_mult(&F->Pminus, &F->AT, &TEMP221);
  mat_add(&TEMP221, &F->Q, &F->Pminus);

  //3. K(k) = P'(k) HT / (H P'(k) HT + R)
  mat_mult(&F->H, &F->Pminus, &F->K);
  mat_mult(&F->K, &F->HT, &TEMP221);
  mat_add(&TEMP221, &F->R, &F->K);

  mat_inv(&F->K, &TEMP222);
  mat_mult(&F->Pminus, &F->HT, &TEMP221);
  mat_mult(&TEMP221, &TEMP222, &F->K);

  //4. xhat(k) = xhat'(k) + K(k) (z(k) - H xhat'(k))
  mat_mult(&F->H, &F->xhatminus, &TEMP211);
  mat_sub(&F->z, &TEMP211, &TEMP212);
  mat_mult(&F->K, &TEMP212, &TEMP211);
  mat_add(&F->xhatminus, &TEMP211, &F->xhat);

  //5. P(k) = (1-K(k)H)P'(k)
  mat_mult(&F->K, &F->H, &TEMP221);
  mat_sub(&Num1, &TEMP221, &TEMP222);
  mat_mult(&TEMP222, &F->Pminus, &F->P);

  F->filtered_value[0] = F->xhat.pData[0];
  F->filtered_value[1] = F->xhat.pData[1];

  return F->filtered_value;
}

void kalman_filter_init(void)
{
	kalman1_init(&KF1, 200, 300);
	kalman_filter_mat_init(&KF, &KF_init);
}

void kalman_filter_test(void)
{
	KFtest = kalman1_filter(&KF1, 5);
//	kalman_filter_calc(&KF, 5, 5);
}
