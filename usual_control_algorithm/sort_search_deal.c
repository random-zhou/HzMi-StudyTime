/**
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  * @file       sort_search_deal.c/h
  * @brief      ��������&�����㷨
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
#include <stdint.h>
#include <string.h>
#include "sort_search_deal.h"

//��������
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        // ѡȡδ���򲿷ֵĵ�һ��Ԫ��
        key = arr[i];
        // ����Ԫ������ǰ���Ԫ�����αȽϣ��ҵ����ʵ�λ�ò���
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key; // ��Ԫ�ز��뵽�ҵ���λ��
    }
}

// ð������
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    // ���ѭ�����Ʊ���
    for (i = 0; i < n - 1; i++) {
        // �ڲ�ѭ�������������Ԫ�صıȽϺͽ���
        for (j = 0; j < n - i - 1; j++) {
            // �����ǰԪ�ش��ں�һ��Ԫ�أ��򽻻����ǵ�λ��
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// ���Բ��Һ���ʵ��
int linearSearch(int arr[], int size, int target) {
	int i; 
    for (i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i; // �ҵ�Ŀ��Ԫ�أ��������������е�����
        }
    }
    return -1; // ��������������δ�ҵ�Ŀ��Ԫ�أ�����-1
}

// ���ֲ��Һ�����������������������в����ض�Ԫ�ص�λ��
int binarySearch(int arr[], int left, int right, int target) {
    // ȷ����߽�С���ұ߽�
    if (left > right) {
        return -1; // �����߽�����ұ߽磬˵��Ŀ�겻������������
    }
    // �����м�λ�õ�����
    int mid = left + (right - left) / 2;
    // ����м�Ԫ���Ƿ�������Ҫ�ҵ�Ŀ��
    if (arr[mid] == target) {
        return mid; // ����ҵ�Ŀ�꣬����������
    } else if (arr[mid] > target) {
        // ����м�Ԫ�ش���Ŀ�꣬˵��Ŀ������ߵ���������
        return binarySearch(arr, left, mid - 1, target);
    } else {
        // ����м�Ԫ��С��Ŀ�꣬˵��Ŀ�����ұߵ���������
        return binarySearch(arr, mid + 1, right, target);
    }
}