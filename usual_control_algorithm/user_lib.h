/**
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  * @file       struct_typedef.h
  * @brief      �������㺯��
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
#define USER_ABS(x)		(((x) > 0) ? (x) : (-(x)))                                          // �궨��ʵ�ַ��ؾ���ֵ(x�ﲻ�����Լ��Լ�����䣬�����������)
#define LIMIT_MIN_MAX(x, min, max) ((x) = (((x)<=(min))?(min):(((x)>=(max))?(max):(x))))	// �޷�
#define USER_LIMIT_MINMAX(x, min, max)	\
{										\
        if ((x) > (max)) {				\
            (x) = (max);				\
        } else if ((x) < (min)) {		\
            (x) = (min);				\
        }								\
    }
#define USER_MIN(x, y)	(((x) < (y)) ? (x) : (y))                                           // ȡ��Сֵ
#define USER_MAX(x, y)	(((x) > (y)) ? (x) : (y))                                           // ȡ���ֵ
#define USER_MINF(x, y)	(((x) + (y) - fabs((x) - (y))) / 2)
#define USER_MF(x, y)	(((x) + (y) + fabs((x) - (y))) / 2)
#define USER_SIGN(x)	(((x) > 0) ? 1 :-1) //((int32)(((x) > 0 ? 1 : -1) * ceil(ABS((x)))))// ȡ����
#define USER_SWAP(x, y)	do{(x) ^= (y); (y) ^= (x); (x) ^= (y);} while(0)                    // ���� x, y ��ֵ
#define USER_ARR_SIZE(a)	( sizeof( (a) ) / sizeof( ((a)[0]) ) )                          // ��������Ԫ�صĸ���
#define USER_OFFSET(type, member)	((uint32_t)(&(((type *)0)->member)))					// ��ȡ�ṹ��ĳ��Աƫ��



#endif

