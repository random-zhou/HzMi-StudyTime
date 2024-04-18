/**
  ****************************(C) COPYRIGHT 2024 HzMI****************************
  * @file       usart.c/h
  * @brief      
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Apr-18-2024      Rz              1. done
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */



extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;

/* USER CODE BEGIN Private defines */
typedef struct RxDataStruct
{
    uint8_t x1;
		uint8_t x2;
		uint8_t x3;
		uint8_t x4;
		uint8_t x5;
		uint8_t x6;

}RxDataStruct;
/* USER CODE END Private defines */

void MX_USART3_UART_Init(void);
void MX_USART6_UART_Init(void);

/* USER CODE BEGIN Prototypes */
int fputc(int ch,FILE *f);//串口发送重定向
int fgetc(FILE *f);//串口接收重定向
void SendPacketDate(UART_HandleTypeDef *huart,uint8_t beginwith,uint8_t endwith,uint8_t value[]);
uint8_t RxHandle(UART_HandleTypeDef *huart,uint8_t beginwith,uint8_t endwith,uint8_t datalength);



/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
