/*
 * @Author: ��random-zhou�� 2501601106@qq.com
 * @Date: 2024-04-18 00:23:06
 * @LastEditors: ��random-zhou�� 2501601106@qq.com
 * @LastEditTime: 2024-04-29 16:34:11
 * @FilePath: \HzMi-StudyTime\usual_control_algorithm\filters.h
 * @Description: ����Ĭ������,������`customMade`, ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __FILTERS_H__
#define __FILTERS_H__


typedef unsigned char uint8_t;

float limit_filter(float new_value,int DEVIATION);
double averageFilter(double *data, int size, int windowSize) ;
void kalmanFilter(double *measurements, double *estimates, int numMeasurements, double processNoise, double measurementNoise) ;
void copyArray(double *source, double *destination, int start, int end) ;
double medianFilter(double *data, int size, int windowSize) ;
float first_order_lag_filter(float new_value,double FIRST_LAG_PROPORTION);
float weighted_filter(float new_value,uint8_t *coe,uint8_t sum_coe);
float shake_filter(float new_value, float now_value,int SHAKE_N);







//����
// // ����������ʾƽ��ֵ�˲�
// int main() {
//     double data[] = {1, 2, 3, 2.5, 3.5, 2, 3, 4, 5};
//     int size = sizeof(data) / sizeof(data[0]);
//     int windowSize = 3; // ���ô��ڴ�СΪ3
//     averageFilter(data, size, windowSize);
//     printf("Filtered data: \n");
//     for (int i = 0; i < size; i++) {
//         printf("%f ", data[i]);
//     }
//     printf("\n");
//     return 0;
// }

// // ����������ʾ�������˲�
// int main() {
//     double measurements[] = {1.0, 2.0, 3.0, 2.5, 3.5, 2.0, 3.0, 4.0, 5.0};
//     double estimates[1]; // ���ڴ洢���չ��Ƶ�����
//     int numMeasurements = sizeof(measurements) / sizeof(measurements[0]);
//     double processNoise = 0.1; // ��������
//     double measurementNoise = 0.2; // ��������
//     kalmanFilter(measurements, estimates, numMeasurements, processNoise, measurementNoise);
//     printf("Estimated value: %f\n", estimates[0]);
//     return 0;
// }

// // ����������ʾ��λֵ�˲�
// int main() {
//     double data[] = {1, 2, 3, 2.5, 3.5, 2, 3, 4, 5};
//     int size = sizeof(data) / sizeof(data[0]);
//     int windowSize = 3; // ���ô��ڴ�СΪ3
//     medianFilter(data, size, windowSize);
//     printf("Filtered data: \n");
//     for (int i = 0; i < size; i++) {
//         printf("%f ", data[i]);
//     }
//     printf("\n");
//     return 0;
// }




#endif