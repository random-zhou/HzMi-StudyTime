#ifndef __VALIDATION_H__
#define __VALIDATION_H__
unsigned char Check(const unsigned char *buf, int len)  ;
unsigned char CheckXor(const char *strData,int len)  ;
unsigned short int CRC(const unsigned char *buf, int leng) ; 
unsigned short crc16(const unsigned char *data, int length) ;
unsigned char LRC(const unsigned char *auchMsg, unsigned short usDataLen) ; 
unsigned short sumCheck(const unsigned char *data, int length) ;
unsigned char iSumCheck(const unsigned char *buf, int len);



#endif