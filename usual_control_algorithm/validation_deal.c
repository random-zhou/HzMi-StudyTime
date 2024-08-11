/**
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  * @file       vaildation_deal.c/h
  * @brief      校验算法
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
#include <string.h>
#include <stdint.h>
#include "vaildation_deal.h"

//校验和  返回一个字节
unsigned char Check(const unsigned char *buf, int len)  
{  
    int iSum = 0; 
    for (int i = 0;i < len;i++)  
    {  
        iSum += buf[i];  
    }  
    iSum %= 0x100;   //也可以&0xff
    return (unsigned char)iSum;  
} 

//异或校验 返回一个字节
unsigned char CheckXor(const char *strData,int len)  
{  
    char checksum = 0;  
    for (int i = 0;i < len;i++)  
    {  
        checksum = checksum ^ strData[i];  
    }  
    return (unsigned char)checksum;  
} 

//CRC校验 （返回两个字节 高字节在前，低字节在后）  循环冗余校验
unsigned short int CRC(const unsigned char *buf, int leng)  
{  
    unsigned short int  Reg,temp,Crccode,i,j;  
    Reg = 0xFFFF;  					//设置crc的值    FF FF
    Crccode = 0xA001;     			//定义的一个多项式码，最终都会与这个码异或
    for ( i=0;i<leng;i++ )  
    {     
        Reg ^= *(buf+i);  			//进行异或  与crc的低8位
        	// ==》注意这里的循环 其实都是固定的值，可以直接计算生成一个表来直接获取
        for ( j=0;j<8;j++ )  
        {     
            temp=Reg&0x0001;      	//获取当前最低位的数字
            Reg=Reg>>1;  			//向右移一位
            if( temp==0x0001 )   	//判断移出的最低位的值，如果为1，则与上文定义的多项式码进行异或，为0，则不处理
                Reg^=Crccode;   
        }   
    }  								//重复处理完所有的数据
    return (Reg<<8 | Reg>>8);   //(Reg^ 0xffff)   ==>这里其实做了反转
}

// CRC16计算函数
unsigned short crc16(const unsigned char *data, int length) {
    unsigned short crc = 0xFFFF; // 初始化CRC值为0xFFFF
    int i, j;
    for (i = 0; i < length; i++) { // 遍历数据
        crc ^= (unsigned short)data[i]; // 异或数据
        for (j = 0; j < 8; j++) { // 进行8次循环
            if (crc & 0x0001) { // 如果最低位为1
                crc = (crc >> 1) ^ 0xA001; // 右移一位并异或生成多项式
            } else {
                crc >>= 1; // 否则只右移一位
            }
        }
    }
    return crc; // 返回计算结果
}

// 纵向冗余校验 异或校验和 不可靠
//LRC校验 求和  取反  +1
unsigned char LRC(const unsigned char *auchMsg, unsigned short usDataLen)  
{  
    unsigned char uchLRC=0;  
    while(usDataLen--)  
    {  
        uchLRC+=*auchMsg++;  
    }  
    return ((unsigned char)(-((char)uchLRC)));  
} 

// 总和校验计算函数
unsigned short sumCheck(const unsigned char *data, int length) {
    unsigned short sum = 0; // 初始化总和为0
    int i;
    for (i = 0; i < length; i++) { // 遍历数据
        sum += data[i]; // 累加数据
    }
    return sum; // 返回计算结果
}

//补码求和
unsigned char iSumCheck(const unsigned char *buf, int len)
{
    int iSum = 0;
    for (int i = 0;i < len;i++)
    {
      iSum += buf[i];
    }
    iSum = 256 - iSum;
   	return (unsigned char)iSum;
}