/**
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  * @file       vaildation_deal.c/h
  * @brief      –£—ÈÀ„∑®
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
#ifndef __VALIDATION_H__
#define __VALIDATION_H__
unsigned char Check(const unsigned char *buf, int len)  ;
unsigned char CheckXor(const char *strData,int len)  ;
unsigned short int CRC(const unsigned char *buf, int leng) ; 
unsigned short crc16(const unsigned char *data, int length) ;
unsigned char LRC(const unsigned char *auchMsg, unsigned short usDataLen) ; 
unsigned short sumCheck(const unsigned char *data, int length) ;s
unsigned char iSumCheck(const unsigned char *buf, int len);



#endif