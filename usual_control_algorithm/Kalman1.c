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
#include "Kalman.h"





//��ά�������˲�
float Q_angle;
float Q_bias;
float R_measure;

static float angle;   //�Ƕ�
static float bias;    //������Ư��
static float rate;    //���ٶ�
static float P[2][2]; //���Э�������

void Kalman_Init(void)
{
    Q_angle = 9.99999977E-3;//�Ƕ�����Э����
    Q_bias = 5.49999997E-2; //������Ư������Э����
    R_measure = 0.03f;  //�ǶȲ�������

    angle = 0.0f; //��λ�Ƕ�
    bias  = 0.0f; //��λ������Ư��

    P[0][0] = 0.0f; //Э�������
    P[0][1] = 0.0f;
    P[1][0] = 0.0f;
    P[1][1] = 0.0f;

}

//dt������
//Gyro:�����ǽ��ٶ�ֵ
//Accel�����ٶȼ�������ĽǶ�
float  Kalman_getAngle(float dt,float Gyro_rate,float Acc_Angle)
{

    float K[2];     //����������
    float S;        //���㿨��������ʱ��ķ�ĸ
    float angle_err;        //�������Ź���ֵʱ�ĽǶ����

    /* Step 1 */
    //����ϵͳ����һ״̬��Ԥ��ֵ
    rate = Gyro_rate - bias;//�����ǣ����ٶ� - ���ٶ�Ư��
    angle = angle + rate*dt;//�����ǽ��ٶȻ��ֳɵĽǶ�=

    /* Step 2 */
    //��Ӧ��X(k|k-1)��Э�������
    P[0][0] += dt * (dt*P[1][1] - P[0][1] - P[1][0] + Q_angle);
    P[0][1] -= dt * P[1][1];
    P[1][0] -= dt * P[1][1];
    P[1][1] += Q_bias * dt;

    /* Step 3 */
    //���㿨��������
    S = P[0][0] + R_measure; //��ĸ

    K[0] = P[0][0] / S;
    K[1] = P[1][0] / S;

    /* Step 4 */
    //�������Ź���ֵ
    angle_err = Acc_Angle - angle; //�Ƕ����

    angle += K[0] * angle_err;
    bias  += K[1] * angle_err;

    /* Step 5 */
    //����k״̬��X(k|k)��Э����
    P[0][0] -= K[0] * P[0][0];
    P[0][1] -= K[0] * P[0][1];
    P[1][0] -= K[1] * P[0][0];
    P[1][1] -= K[1] * P[0][1];
    return angle;

}





//һά�������˲�
//1. �ṹ�����Ͷ���


//2. �Ը߶�Ϊ�� ���忨�����ṹ�岢��ʼ������
//KFP KFP_height={0.02,0,0,0,0.001,0.543};
KFP gyro_z_str={0.02,0,0,0,0.001f,0.856f};

/**
 *�������˲���
 *@param KFP *kfp �������ṹ�����
 *   float input ��Ҫ�˲��Ĳ����Ĳ���ֵ�����������Ĳɼ�ֵ��
 *@return �˲���Ĳ���������ֵ��
 */
 float kalmanFilter(KFP *kfp,float input)
 {
     //Ԥ��Э����̣�kʱ��ϵͳ����Э���� = k-1ʱ�̵�ϵͳЭ���� + ��������Э����
     kfp->Now_P = kfp->LastP + kfp->Q;
     //���������淽�̣����������� = kʱ��ϵͳ����Э���� / ��kʱ��ϵͳ����Э���� + �۲�����Э���
     kfp->Kg = kfp->Now_P / (kfp->Now_P + kfp->R);
     //��������ֵ���̣�kʱ��״̬����������ֵ = ״̬������Ԥ��ֵ + ���������� * ������ֵ - ״̬������Ԥ��ֵ��
     kfp->out = kfp->out + kfp->Kg * (input -kfp->out);//��Ϊ��һ�ε�Ԥ��ֵ������һ�ε����ֵ
     //����Э�����: ���ε�ϵͳЭ����� kfp->LastP ����һ������׼����
     kfp->LastP = (1-kfp->Kg) * kfp->Now_P;
     return kfp->out;
 }

/**
 *���ÿ������˲��� ʵ��
 */
//int height;
//int kalman_height=0;
//kalman_height = kalmanFilter(&KFP_height,(float)height);

