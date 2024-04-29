#include <stdio.h>
#include <stdlib.h>
#include "filters.h"



//�޷��˲�����
float limit_filter(float new_value,int DEVIATION)
{
    static int num = 0;  // ����һ����̬���� num�����ڼ�¼�������õĴ���
    static float value = 0;  // ����һ����̬���� value�����ڴ洢��һ�ε�ֵ����ʼ��Ϊ0

    num++;  // ÿ�κ������� num ��ֵ��1

    if(num == 1)  // ������Ǻ����ĵ�һ�ε���
        value = new_value;  // �� new_value ��ֵ�� value
    else
    {
        // ������ǵ�һ�ε��ã���� new_value �� value �Ĳ�ֵ�Ƿ񳬹� DEVIATION
        if ( ( new_value - value > DEVIATION ) || ( value - new_value > DEVIATION ) )
            return value;  // ���������ֵ��������һ�ε� value
    }
    // ��� new_value �� value �Ĳ�ֵû�г��� DEVIATION�������µ� new_value
    return new_value;
}


// ���ڻ���ƽ��ֵ�˲�����
double averageFilter(double *data, int size, int windowSize) {
    int i, j, halfWindowSize;
    double sum = 0.0, filteredValue;
    // ��鴰�ڴ�С�Ƿ�Ϊ�����������ż������Ҫ����
    if (windowSize % 2 == 0) {
        windowSize++;
    }
    halfWindowSize = windowSize / 2;
    
    // ��ÿ�����ݵ�����˲�
    for (i = 0; i < size; i++) {
        sum = 0.0; // ���ô�����Ԫ�صĺ�
        // ���㵱ǰ���ݵ�Ĵ��ڷ�Χ
        int start = i - halfWindowSize;
        int end = start + windowSize;
        // ȷ�����ڲ��������ݵı߽�
        if (start < 0) start = 0;
        if (end > size) end = size;
        
        // ���㴰�����������ݵĺ�
        for (j = start; j < end; j++) {
            sum += data[j];
        }
        // ����ƽ��ֵ����ֵ����ǰ���ݵ�
        filteredValue = sum / windowSize;
        data[i] = filteredValue;
    }
    // ���ش�������������
    return data[0]; // ���ص�һ��Ԫ����Ϊʾ��
}

// һ�׿������˲�����
void kalmanFilter(double *measurements, double *estimates, int numMeasurements, double processNoise, double measurementNoise) {
    int i;
    double estimate, priorEstimate, priorError, errorCovariance;
    double kalmanGain, temp;
    
    // ��ʼ��״̬���ƺ�Э����
    estimate = 0.0;
    priorEstimate = 0.0;
    priorError = 1.0; // ��ʼ���������Ϊ1.0
    errorCovariance = priorError * priorError;
    
    for (i = 0; i < numMeasurements; i++) {
        // ���㿨��������
        kalmanGain = errorCovariance / (errorCovariance + measurementNoise);
        // ����״̬����
        estimate = priorEstimate + kalmanGain * (measurements[i] - priorEstimate);
        // ����Э����
        errorCovariance = (1 - kalmanGain) * errorCovariance;
        // ����������ƺ����
        priorEstimate = estimate;
        priorError = errorCovariance;
    }
    // �����չ��ƴ洢��estimates������
    estimates[0] = estimate;
}


// �������ڸ��������һ����
void copyArray(double *source, double *destination, int start, int end) {
    for (int i = start; i < end; i++) {
        destination[i - start] = source[i];
    }
}

// ��λֵ�����˲�����
double medianFilter(double *data, int size, int windowSize) {
    int i, j, k, halfWindowSize;
    double *tempArray, filteredValue;
    // ��鴰�ڴ�С�Ƿ�Ϊ�����������ż������Ҫ����
    if (windowSize % 2 == 0) {
        windowSize++;
    }
    halfWindowSize = windowSize / 2;
    
    // ��ÿ�����ݵ�����˲�
    for (i = 0; i < size; i++) {
        // ������ʱ�������ڴ洢�����ڵ�����
        tempArray = (double *)malloc(windowSize * sizeof(double));
        // ���㵱ǰ���ݵ�Ĵ��ڷ�Χ
        int start = i - halfWindowSize;
        int end = start + windowSize;
        // ȷ�����ڲ��������ݵı߽�
        if (start < 0) {
            start = 0;
            end = windowSize;
        } else if (end > size) {
            end = size;
        }
        
        // ���ƴ����ڵ����ݵ���ʱ����
        copyArray(data + start, tempArray, 0, end - start);
        // ����ʱ�����������
        for (j = 0; j < windowSize - 1; j++) {
            for (k = 0; k < windowSize - j - 1; k++) {
                if (tempArray[k] > tempArray[k + 1]) {
                    double temp = tempArray[k];
                    tempArray[k] = tempArray[k + 1];
                    tempArray[k + 1] = temp;
                }
            }
        }
        // ������λֵ����ֵ����ǰ���ݵ�
        filteredValue = tempArray[halfWindowSize];
        data[i] = filteredValue;
        // �ͷ���ʱ������ڴ�
        free(tempArray);
    }
    // ���ش�������������ĵ�һ��Ԫ����Ϊʾ��
    return data[0];
}



//һ���ͺ��˲�
float first_order_lag_filter(float new_value,double FIRST_LAG_PROPORTION)
{
    // ����������̬���������ڴ洢�˲����ĵ�ǰֵ����һ��ֵ
    static float first_order_value, first_order_last_value;

    // ����һ�ε��˲�ֵ������ǰֵ���Ա�����һ�ε�����ʹ��
    first_order_value = first_order_last_value;

    // ���� last_value Ϊ��ǰ����ֵ��Ϊ��һ�κ���������׼��
    first_order_last_value = new_value;

    // ���㲢�����µ��˲�ֵ
    // ����ʹ���� FIRST_LAG_PROPORTION ��Ϊ�˲�����������һ������0��1֮��ĳ���
    // (1 - FIRST_LAG_PROPORTION) * first_order_value ��ʾ��һ���˲�ֵ������Ĺ���
    // FIRST_LAG_PROPORTION * new_value ��ʾ��ǰ��ֵ������Ĺ���
    // ������ӵõ����յ��˲����
    return (1 - FIRST_LAG_PROPORTION) * first_order_value + FIRST_LAG_PROPORTION * new_value;
}

//��Ȩ����ƽ���˲�

//��Ҫ��ǰ����WEIGHT_AVERAGE_N
#define WEIGHT_AVERAGE_N 12
// uint8_t  coe[WEIGHT_AVERAGE_N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
// uint8_t  sum_coe = 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10 + 11 + 12;
float weighted_filter(float new_value,uint8_t *coe,uint8_t sum_coe)
{
    // ����һ����̬���飬���ڴ洢�˲����Ļ����������СΪ WEIGHT_AVERAGE_N
    static float weight_average_buf[WEIGHT_AVERAGE_N];

    uint8_t count;  // ����һ���޷���8λ��������������ѭ������
    float sum = 0;  // ����һ������������ sum�����ڴ洢��Ȩ��͵Ľ��

    // ѭ���� weight_average_buf �����е�Ԫ�������ƶ�һ��λ��
    // ����������ĵ�һ��Ԫ�ؽ����Ƴ��������һ��Ԫ�ؽ�����ֵ�滻
    for (count = 0; count < WEIGHT_AVERAGE_N - 1; count++)
    {
        weight_average_buf[count] = weight_average_buf[count + 1];
    }

    // ����ֵ new_value ������������һ��λ��
    weight_average_buf[WEIGHT_AVERAGE_N - 1] = new_value;

    // ��ʼ�� sum Ϊ 0
    sum = 0;

    // ѭ���������飬�������е�ÿ��Ԫ�������Ӧ��Ȩ����ˣ�Ȼ���ۼӵ� sum
    for (count = 0; count < WEIGHT_AVERAGE_N; count++)
    {
        sum += weight_average_buf[count] * coe[count];
    }

    // ���ؼ�Ȩ��͵Ľ������Ȩ��ϵ��֮�ͣ��Եõ���Ȩƽ��ֵ
    // ������� coe ��һ���ⲿ��������飬��������ÿ��Ԫ�ص�Ȩ��
    // sum_coe �� coe ����������Ȩ�ص��ܺ�
    return (sum / (sum_coe * 1.0));
}

//�����˲���
float shake_filter(float new_value, float now_value,int SHAKE_N)
{
    // ����һ����̬���� count�����ڼ�¼�����仯�Ĵ���
    static uint8_t count = 0;

    // �����ǰֵ now_value ����ֵ new_value ��ͬ
    if (now_value != new_value)
    {
        // �����仯�Ĵ��� count ��һ
        count++;

        // ��������仯�Ĵ����ﵽԤ�����ֵ SHAKE_N
        if (count >= SHAKE_N)
        {
            // ���� count Ϊ 0
            count = 0;

            // ������ֵ new_value����Ϊ���Ѿ�ͨ���𶯼��
            return new_value;
        }
    }

    // �����ֵ�͵�ǰֵ��ͬ�����������仯����δ�ﵽ��ֵ���򷵻ص�ǰֵ now_value
    return now_value;
}
