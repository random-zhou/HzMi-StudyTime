/**
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  * @file       sort_search_deal.c/h
  * @brief      常用排序&搜索算法
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

//插入排序
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        // 选取未排序部分的第一个元素
        key = arr[i];
        // 将该元素与它前面的元素依次比较，找到合适的位置插入
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key; // 将元素插入到找到的位置
    }
}

// 冒泡排序
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    // 外层循环控制遍数
    for (i = 0; i < n - 1; i++) {
        // 内层循环负责进行相邻元素的比较和交换
        for (j = 0; j < n - i - 1; j++) {
            // 如果当前元素大于后一个元素，则交换它们的位置
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 线性查找函数实现
int linearSearch(int arr[], int size, int target) {
	int i; 
    for (i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i; // 找到目标元素，返回其在数组中的索引
        }
    }
    return -1; // 遍历完整个数组未找到目标元素，返回-1
}

// 二分查找函数，用于在已排序的数组中查找特定元素的位置
int binarySearch(int arr[], int left, int right, int target) {
    // 确保左边界小于右边界
    if (left > right) {
        return -1; // 如果左边界大于右边界，说明目标不存在于数组中
    }
    // 计算中间位置的索引
    int mid = left + (right - left) / 2;
    // 检查中间元素是否是我们要找的目标
    if (arr[mid] == target) {
        return mid; // 如果找到目标，返回其索引
    } else if (arr[mid] > target) {
        // 如果中间元素大于目标，说明目标在左边的子数组中
        return binarySearch(arr, left, mid - 1, target);
    } else {
        // 如果中间元素小于目标，说明目标在右边的子数组中
        return binarySearch(arr, mid + 1, right, target);
    }
}