/**
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  * @file       filters.c/h
  * @brief      常用滤波算法
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Aug-11-2024     ZSB              1. done
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  */
#include <stdio.h>
#include <stdlib.h>
#include "filters.h"



//限幅滤波函数
float limit_filter(float new_value,int DEVIATION)
{
    static int num = 0;  // 定义一个静态变量 num，用于记录函数调用的次数
    static float value = 0;  // 定义一个静态变量 value，用于存储上一次的值，初始化为0

    num++;  // 每次函数调用 num 的值加1

    if(num == 1)  // 如果这是函数的第一次调用
        value = new_value;  // 将 new_value 赋值给 value
    else
    {
        // 如果不是第一次调用，检查 new_value 与 value 的差值是否超过 DEVIATION
        if ( ( new_value - value > DEVIATION ) || ( value - new_value > DEVIATION ) )
            return value;  // 如果超过阈值，返回上一次的 value
    }
    // 如果 new_value 与 value 的差值没有超过 DEVIATION，返回新的 new_value
    return new_value;
}


// 窗口滑动平均值滤波函数
double averageFilter(double *data, int size, int windowSize) {
    int i, j, halfWindowSize;
    double sum = 0.0, filteredValue;
    // 检查窗口大小是否为奇数，如果是偶数，需要调整
    if (windowSize % 2 == 0) {
        windowSize++;
    }
    halfWindowSize = windowSize / 2;
    
    // 对每个数据点进行滤波
    for (i = 0; i < size; i++) {
        sum = 0.0; // 重置窗口内元素的和
        // 计算当前数据点的窗口范围
        int start = i - halfWindowSize;
        int end = start + windowSize;
        // 确保窗口不超出数据的边界
        if (start < 0) start = 0;
        if (end > size) end = size;
        
        // 计算窗口内所有数据的和
        for (j = start; j < end; j++) {
            sum += data[j];
        }
        // 计算平均值并赋值给当前数据点
        filteredValue = sum / windowSize;
        data[i] = filteredValue;
    }
    // 返回处理后的数据数组
    return data[0]; // 返回第一个元素作为示例
}

// 一阶卡尔曼滤波函数
void kalmanFilter(double *measurements, double *estimates, int numMeasurements, double processNoise, double measurementNoise) {
    int i;
    double estimate, priorEstimate, priorError, errorCovariance;
    double kalmanGain, temp;
    
    // 初始化状态估计和协方差
    estimate = 0.0;
    priorEstimate = 0.0;
    priorError = 1.0; // 初始估计误差设为1.0
    errorCovariance = priorError * priorError;
    
    for (i = 0; i < numMeasurements; i++) {
        // 计算卡尔曼增益
        kalmanGain = errorCovariance / (errorCovariance + measurementNoise);
        // 更新状态估计
        estimate = priorEstimate + kalmanGain * (measurements[i] - priorEstimate);
        // 更新协方差
        errorCovariance = (1 - kalmanGain) * errorCovariance;
        // 更新先验估计和误差
        priorEstimate = estimate;
        priorError = errorCovariance;
    }
    // 将最终估计存储在estimates数组中
    estimates[0] = estimate;
}


// 函数用于复制数组的一部分
void copyArray(double *source, double *destination, int start, int end) {
    for (int i = start; i < end; i++) {
        destination[i - start] = source[i];
    }
}

// 中位值窗口滤波函数
double medianFilter(double *data, int size, int windowSize) {
    int i, j, k, halfWindowSize;
    double *tempArray, filteredValue;
    // 检查窗口大小是否为奇数，如果是偶数，需要调整
    if (windowSize % 2 == 0) {
        windowSize++;
    }
    halfWindowSize = windowSize / 2;
    
    // 对每个数据点进行滤波
    for (i = 0; i < size; i++) {
        // 创建临时数组用于存储窗口内的数据
        tempArray = (double *)malloc(windowSize * sizeof(double));
        // 计算当前数据点的窗口范围
        int start = i - halfWindowSize;
        int end = start + windowSize;
        // 确保窗口不超出数据的边界
        if (start < 0) {
            start = 0;
            end = windowSize;
        } else if (end > size) {
            end = size;
        }
        
        // 复制窗口内的数据到临时数组
        copyArray(data + start, tempArray, 0, end - start);
        // 对临时数组进行排序
        for (j = 0; j < windowSize - 1; j++) {
            for (k = 0; k < windowSize - j - 1; k++) {
                if (tempArray[k] > tempArray[k + 1]) {
                    double temp = tempArray[k];
                    tempArray[k] = tempArray[k + 1];
                    tempArray[k + 1] = temp;
                }
            }
        }
        // 计算中位值并赋值给当前数据点
        filteredValue = tempArray[halfWindowSize];
        data[i] = filteredValue;
        // 释放临时数组的内存
        free(tempArray);
    }
    // 返回处理后的数据数组的第一个元素作为示例
    return data[0];
}



//一阶滞后滤波
float first_order_lag_filter(float new_value,double FIRST_LAG_PROPORTION)
{
    // 定义两个静态变量，用于存储滤波器的当前值和上一个值
    static float first_order_value, first_order_last_value;

    // 将上一次的滤波值赋给当前值，以便在下一次迭代中使用
    first_order_value = first_order_last_value;

    // 更新 last_value 为当前的新值，为下一次函数调用做准备
    first_order_last_value = new_value;

    // 计算并返回新的滤波值
    // 这里使用了 FIRST_LAG_PROPORTION 作为滤波比例，它是一个介于0和1之间的常数
    // (1 - FIRST_LAG_PROPORTION) * first_order_value 表示上一个滤波值对输出的贡献
    // FIRST_LAG_PROPORTION * new_value 表示当前新值对输出的贡献
    // 两者相加得到最终的滤波输出
    return (1 - FIRST_LAG_PROPORTION) * first_order_value + FIRST_LAG_PROPORTION * new_value;
}

//加权递推平均滤波

//需要提前定义WEIGHT_AVERAGE_N
#define WEIGHT_AVERAGE_N 12
// uint8_t  coe[WEIGHT_AVERAGE_N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
// uint8_t  sum_coe = 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10 + 11 + 12;
float weighted_filter(float new_value,uint8_t *coe,uint8_t sum_coe)
{
    // 定义一个静态数组，用于存储滤波器的缓冲区，其大小为 WEIGHT_AVERAGE_N
    static float weight_average_buf[WEIGHT_AVERAGE_N];

    uint8_t count;  // 定义一个无符号8位整数变量，用于循环计数
    float sum = 0;  // 定义一个浮点数变量 sum，用于存储加权求和的结果

    // 循环将 weight_average_buf 数组中的元素向左移动一个位置
    // 这样，数组的第一个元素将被移除，而最后一个元素将被新值替换
    for (count = 0; count < WEIGHT_AVERAGE_N - 1; count++)
    {
        weight_average_buf[count] = weight_average_buf[count + 1];
    }

    // 将新值 new_value 放入数组的最后一个位置
    weight_average_buf[WEIGHT_AVERAGE_N - 1] = new_value;

    // 初始化 sum 为 0
    sum = 0;

    // 循环遍历数组，将数组中的每个元素与其对应的权重相乘，然后累加到 sum
    for (count = 0; count < WEIGHT_AVERAGE_N; count++)
    {
        sum += weight_average_buf[count] * coe[count];
    }

    // 返回加权求和的结果除以权重系数之和，以得到加权平均值
    // 这里假设 coe 是一个外部定义的数组，它包含了每个元素的权重
    // sum_coe 是 coe 数组中所有权重的总和
    return (sum / (sum_coe * 1.0));
}

//消抖滤波法
float shake_filter(float new_value, float now_value,int SHAKE_N)
{
    // 定义一个静态变量 count，用于记录连续变化的次数
    static uint8_t count = 0;

    // 如果当前值 now_value 与新值 new_value 不同
    if (now_value != new_value)
    {
        // 连续变化的次数 count 加一
        count++;

        // 如果连续变化的次数达到预设的阈值 SHAKE_N
        if (count >= SHAKE_N)
        {
            // 重置 count 为 0
            count = 0;

            // 返回新值 new_value，因为它已经通过震动检测
            return new_value;
        }
    }

    // 如果新值和当前值相同，或者连续变化次数未达到阈值，则返回当前值 now_value
    return now_value;
}
