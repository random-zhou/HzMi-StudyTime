/**
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  * @file       struct_typedef.h
  * @brief      常用运算函数
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
#ifndef USER_LIB_H
#define USER_LIB_H

// Includes
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "struct_typedef.h"
#include "main.h"


//#define DEBUGMODE 1

// Data Define
#define M_PI_F		(3.14159265358979f)
//#define PI			(3.14159265358979f)
#define ONE_PI		(3.14159265358979f)
#define EPS			(1e-6)

// Function Define
#define USER_ABS(x)		(((x) > 0) ? (x) : (-(x)))                                          // 宏定义实现返回绝对值(x里不能有自加自减的语句，否则变量出错)
#define LIMIT_MIN_MAX(x, min, max) ((x) = (((x)<=(min))?(min):(((x)>=(max))?(max):(x))))	// 限幅
#define USER_LIMIT_MINMAX(x, min, max)	\
{										\
        if ((x) > (max)) {				\
            (x) = (max);				\
        } else if ((x) < (min)) {		\
            (x) = (min);				\
        }								\
    }
#define USER_MIN(x, y)	(((x) < (y)) ? (x) : (y))                                           // 取最小值
#define USER_MAX(x, y)	(((x) > (y)) ? (x) : (y))                                           // 取最大值
#define USER_MINF(x, y)	(((x) + (y) - fabs((x) - (y))) / 2)
#define USER_MF(x, y)	(((x) + (y) + fabs((x) - (y))) / 2)
#define USER_SIGN(x)	(((x) > 0) ? 1 :-1) //((int32)(((x) > 0 ? 1 : -1) * ceil(ABS((x)))))// 取符号
#define USER_SWAP(x, y)	do{(x) ^= (y); (y) ^= (x); (x) ^= (y);} while(0)                    // 交换 x, y 的值
#define USER_ARR_SIZE(a)	( sizeof( (a) ) / sizeof( ((a)[0]) ) )                          // 返回数组元素的个数
#define USER_OFFSET(type, member)	((uint32_t)(&(((type *)0)->member)))					// 获取结构体某成员偏移



#endif

