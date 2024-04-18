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

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
#include "stdio.h"
#include "string.h"

uint8_t RxBuff[8]={0};
uint8_t RxState=0,length=0,RxData=0;
uint8_t RxFlag=0;
uint8_t ErrFlag=0;
RxDataStruct RxDataStructure;


/* USER CODE END 0 */

UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;

/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}
/* USART6 init function */

void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();

    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**USART3 GPIO Configuration
    PD9     ------> USART3_RX
    PD8     ------> USART3_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
  else if(uartHandle->Instance==USART6)
  {
  /* USER CODE BEGIN USART6_MspInit 0 */

  /* USER CODE END USART6_MspInit 0 */
    /* USART6 clock enable */
    __HAL_RCC_USART6_CLK_ENABLE();

    __HAL_RCC_GPIOG_CLK_ENABLE();
    /**USART6 GPIO Configuration
    PG14     ------> USART6_TX
    PG9     ------> USART6_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    /* USART6 interrupt Init */
    HAL_NVIC_SetPriority(USART6_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART6_IRQn);
  /* USER CODE BEGIN USART6_MspInit 1 */

  /* USER CODE END USART6_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    /**USART3 GPIO Configuration
    PD9     ------> USART3_RX
    PD8     ------> USART3_TX
    */
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_9|GPIO_PIN_8);

    /* USART3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART6)
  {
  /* USER CODE BEGIN USART6_MspDeInit 0 */

  /* USER CODE END USART6_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART6_CLK_DISABLE();

    /**USART6 GPIO Configuration
    PG14     ------> USART6_TX
    PG9     ------> USART6_RX
    */
    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_14|GPIO_PIN_9);

    /* USART6 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART6_IRQn);
  /* USER CODE BEGIN USART6_MspDeInit 1 */

  /* USER CODE END USART6_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
int fputc(int ch,FILE *f)
{
	
	HAL_UART_Transmit(&huart3,(uint8_t *)&ch,1,HAL_MAX_DELAY);
	return ch;

}

int fgetc(FILE *f)
{
	uint8_t ch;
	HAL_UART_Receive(&huart3,(uint8_t *)&ch,1,HAL_MAX_DELAY);
	return ch;

}

///默认8字节打包发送模式（包帧头帧尾）有效数据6位
//scale:0-255
void SendPacketDate(UART_HandleTypeDef *huart,uint8_t beginwith,uint8_t endwith,uint8_t value[])
{
		int length=8;
		uint8_t temp[length];
    uint8_t i=0,j=0;  
	 
	  temp[0]=beginwith;//数据包头
	 
		for(i=0;i<length;i++)  
		{  
		 temp[i+1] = *value++;//float转BYTE
		}  
		 temp[length-1]=endwith;//数据包尾
		
//		for( j=0;j<length;j++)
//	  {
	   HAL_UART_Transmit(huart,&temp[j],8,HAL_MAX_DELAY);
//	  }

}


//默认接受8字节数据包
uint8_t RxHandle(UART_HandleTypeDef *huart,uint8_t beginwith,uint8_t endwith,uint8_t datalength)
{
		
		if (RxData==beginwith&&RxState==0)
		{
				RxBuff[length++]=RxData;
				RxState=1;
		}
		else if (RxState==1)
		{
				RxBuff[length++]=RxData;
				if (RxData==endwith&&RxState==1)
				{
						if (length==datalength)
						{
								if(RxFlag==0)
								{
										
										RxDataStructure.x1=RxBuff[1];
										RxDataStructure.x2=RxBuff[2];
										RxDataStructure.x3=RxBuff[3];
										RxDataStructure.x4=RxBuff[4];
										RxDataStructure.x5=RxBuff[5];
										RxDataStructure.x6=RxBuff[6];
									
										SendPacketDate(huart,0x00,0x11,RxBuff);
										RxFlag=1;
									
//										printf("%d",RxDataStructure.x1);
//										printf("%d",RxDataStructure.x2);
//										printf("%d",RxDataStructure.x3);
//										printf("%d",RxDataStructure.x4);
//										printf("%d",RxDataStructure.x5);
//										printf("%d",RxDataStructure.x6);
									
										memset(RxBuff,0,length);
										length=0;
										RxState=0;
										RxData=0;
										ErrFlag=0;
										UART_Start_Receive_IT(huart,&RxData,1);
										
										return 1;
								}
								else{//未处理完，不接受数据，丢包
										memset(RxBuff,0,length);
                    RxState=0;
                    RxData=0;
                    length=0; 
										ErrFlag=1;
								}

						}
						else//数据不对，丢包
						{
								memset(RxBuff,0,length);
								RxState=0;
                RxData=0;
                length=0;
								ErrFlag=1;
								
						}
				}
		}
		ErrFlag=0;
		UART_Start_Receive_IT(huart,&RxData,1);
		return 0;

}

//中断回调函数
void	HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
		
		if (huart->Instance==USART3)
		{
				RxHandle(&huart3,0x2C,0x5B,8);
		}			
//		if (huart->Instance==USART6)
//		{
//				RxHandle(&huart6,0x2C,0x5B,8);
//		}	
		
//		if (huart->Instance==USART7)
//		{
//				RxHandle(&huart7,0x2C,0x5B);
//		}	
//				if (huart->Instance==USART8)
//		{
//				RxHandle(&huart8,0x2C,0x5B);
//		}	

	
		HAL_UART_Transmit_IT(&huart3,RxBuff,4);
	
	
	


}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
