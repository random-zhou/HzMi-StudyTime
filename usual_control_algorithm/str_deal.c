/**
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  * @file       str_deal.c/h
  * @brief      字符串处理算法
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
#include <string.h>
#include "str_deal.h"

//数据定义采用char *或者char arr[]

// 字符串比较函数，返回0表示两个字符串相等
int stringCompare(const char *str1, const char *str2) {
    return strcmp(str1, str2);
}

// 字符串替换函数，将所有找到的old子字符串替换为new子字符串
void stringReplace(char *str, const char *old, const char *new) {
    char *pos = strstr(str, old); // 查找old子字符串的位置
    while (pos != NULL) { // 只要找到old子字符串就替换
        strcpy(pos, new); // 用new替换old
        pos = strstr(pos + strlen(new), old); // 继续查找下一个old
    }
}

// 字符串查找函数，返回找到的子字符串的索引，未找到则返回-1
int stringFind(const char *haystack, const char *needle) {
    return strstr(haystack, needle) - haystack; // 使用标准库中的strstr函数
}

// 字符串复制函数，将src字符串复制到dest字符串中
void stringCopy(char *dest, const char *src) {
    strcpy(dest, src); // 使用标准库中的strcpy函数
}

// 字符串连接函数，将src字符串连接到dest字符串的末尾
void stringConcatenate(char *dest, const char *src) {
    strcat(dest, src); // 使用标准库中的strcat函数
}