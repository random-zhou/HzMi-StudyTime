#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "vaildation_deal.h"

//У���  ����һ���ֽ�
unsigned char Check(const unsigned char *buf, int len)  
{  
    int iSum = 0; 
    for (int i = 0;i < len;i++)  
    {  
        iSum += buf[i];  
    }  
    iSum %= 0x100;   //Ҳ����&0xff
    return (unsigned char)iSum;  
} 

//���У�� ����һ���ֽ�
unsigned char CheckXor(const char *strData,int len)  
{  
    char checksum = 0;  
    for (int i = 0;i < len;i++)  
    {  
        checksum = checksum ^ strData[i];  
    }  
    return (unsigned char)checksum;  
} 

//CRCУ�� �����������ֽ� ���ֽ���ǰ�����ֽ��ں�  ѭ������У��
unsigned short int CRC(const unsigned char *buf, int leng)  
{  
    unsigned short int  Reg,temp,Crccode,i,j;  
    Reg = 0xFFFF;  					//����crc��ֵ    FF FF
    Crccode = 0xA001;     			//�����һ������ʽ�룬���ն�������������
    for ( i=0;i<leng;i++ )  
    {     
        Reg ^= *(buf+i);  			//�������  ��crc�ĵ�8λ
        	// ==��ע�������ѭ�� ��ʵ���ǹ̶���ֵ������ֱ�Ӽ�������һ������ֱ�ӻ�ȡ
        for ( j=0;j<8;j++ )  
        {     
            temp=Reg&0x0001;      	//��ȡ��ǰ���λ������
            Reg=Reg>>1;  			//������һλ
            if( temp==0x0001 )   	//�ж��Ƴ������λ��ֵ�����Ϊ1���������Ķ���Ķ���ʽ��������Ϊ0���򲻴���
                Reg^=Crccode;   
        }   
    }  								//�ظ����������е�����
    return (Reg<<8 | Reg>>8);   //(Reg^ 0xffff)   ==>������ʵ���˷�ת
}

// CRC16���㺯��
unsigned short crc16(const unsigned char *data, int length) {
    unsigned short crc = 0xFFFF; // ��ʼ��CRCֵΪ0xFFFF
    int i, j;
    for (i = 0; i < length; i++) { // ��������
        crc ^= (unsigned short)data[i]; // �������
        for (j = 0; j < 8; j++) { // ����8��ѭ��
            if (crc & 0x0001) { // ������λΪ1
                crc = (crc >> 1) ^ 0xA001; // ����һλ��������ɶ���ʽ
            } else {
                crc >>= 1; // ����ֻ����һλ
            }
        }
    }
    return crc; // ���ؼ�����
}

// ��������У�� ���У��� ���ɿ�
//LRCУ�� ���  ȡ��  +1
unsigned char LRC(const unsigned char *auchMsg, unsigned short usDataLen)  
{  
    unsigned char uchLRC=0;  
    while(usDataLen--)  
    {  
        uchLRC+=*auchMsg++;  
    }  
    return ((unsigned char)(-((char)uchLRC)));  
} 

// �ܺ�У����㺯��
unsigned short sumCheck(const unsigned char *data, int length) {
    unsigned short sum = 0; // ��ʼ���ܺ�Ϊ0
    int i;
    for (i = 0; i < length; i++) { // ��������
        sum += data[i]; // �ۼ�����
    }
    return sum; // ���ؼ�����
}

//�������
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