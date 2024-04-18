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

#define RtA         57.295779f  //����->�Ƕ�
#define AtR         0.0174533f  //�Ƕ�->����
//#define Acc_G       0.0011963f
//#define Gyro_G      0.0610351f
//#define Gyro_Gr     0.0010653f

#define Kp 18.0f        //Խ������ż��ٶȼƣ�ԽС������������
#define Ki 0.008f
#define halfT 0.001f

float q0 = 1, q1 = 0, q2 = 0, q3 = 0;
float exInt = 0, eyInt = 0, ezInt = 0;
//���սǶ�
float FilterPitch=0,FilterRoll=0,FilterYaw=0;

float imuyaw,imuyawlast,iyaw,imux;
//ֱ�Ӵ�����е�λ������������

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
    if(ax*ay*az==0)//��ʱ���ⷽ��Ǽ��ٶ�Ϊ0
        return;
//    gx *= Gyro_Gr;
//    gy *= Gyro_Gr;
//    gz *= Gyro_Gr;
    //��һ���������Ǽ��ٶȵ�λתΪ����
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


    //ȡ��ע�ͺ���ǻ��Ϊ0
//    // ����ƫ���ǵ������仯
//        iyaw = imuyaw - imuyawlast;
//        // ����Խ360-0�ȱ߽�ʱ������ƫ����ͻȻ����
//        if (iyaw < -300) {
//            // ���ƫ���Ǳ仯������С�� -300 �ȣ�˵���������򸺷��򳬹� 300 �ȵ�ͻ��
//            imux += 360;
//        } else if (iyaw > 300) {
//            // ���ƫ���Ǳ仯���������� 300 �ȣ�˵���������������򳬹� 300 �ȵ�ͻ��
//            imux -= 360;
//        }
//        // ������һ�ε�ƫ������ֵ
//        imuyawlast = imuyaw;
//        // ������ֵ�ӵ�ƫ����
//        imuyaw += imux;
//        // ���µ�ƫ��ֵ����imu�ṹ
//        FilterYaw = imuyaw;
//        // ��ƫ���Ƕȹ淶����0��360�ȷ�Χ��
//        if (imuyaw > 360) {
//            // ���ƫ���Ǵ��� 360 �ȣ����ȥһ��������Ȧ����ʹ�䴦�� 0 �� 360 ��֮��
//            imuyaw -= 360;
//            FilterYaw = imuyaw;
//        } else if (imuyaw < 0) {
//            // ���ƫ����С�� 0 �ȣ������һ��������Ȧ����ʹ�䴦�� 0 �� 360 ��֮��
//            imuyaw += 360;
//            FilterYaw = imuyaw;
//        }
//        // ������������֮���ƫ���ǲ���
//        float i = imuyaw - imuyawlast;
//        // ��ʶ�ض����򣬳�ʼ��Ϊ0
//        int imuflag = 0;
//        // ��ƫ���ǳ���-170�ȣ����������һ����־λ�Խ������⴦��
//        if (FilterYaw < -170) {
//            imuflag = 1;
//        }
//        // ȷ��ƫ���Ǳ仯`i`��-180��180�ȷ�Χ�ڣ�����Ӧ����������
//        if (i > 180) {
//            i -= 360;
//        } else if (i < -180) {
//            i += 360;
//        }
//        // �ۻ�ƫ���Ǳ仯������ƫ����
//        imuyaw += i;
//        // �����º��ƫ�������´洢��imu�ṹ��
//        FilterYaw = imuyaw;



}

