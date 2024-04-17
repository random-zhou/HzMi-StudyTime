/*
 * bsp_usart.c
 *
 *  Created on: 2021年10月24日
 *      Author: LBQ
 */
#include "bsp_usart.h"

extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart3_rx;

/**
  * @brief          遥控器串口初始化
  * @retval         none
  */
void RC_init(uint8_t *rx1_buf, uint8_t *rx2_buf, uint16_t dma_buf_num)
{
	if (rx1_buf == 0 || rx2_buf == 0 || dma_buf_num == 0) {
		return;
	}

    //使能DMA串口接收
    SET_BIT(huart3.Instance->CR3, USART_CR3_DMAR);

    //使能空闲中断
    __HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);

    //失效DMA
    __HAL_DMA_DISABLE(&hdma_usart3_rx);
    while (hdma_usart3_rx.Instance->CR & DMA_SxCR_EN)
    {
        __HAL_DMA_DISABLE(&hdma_usart3_rx);
    }

    hdma_usart3_rx.Instance->PAR = (uint32_t) & (USART3->DR);

    //内存缓冲区1
    hdma_usart3_rx.Instance->M0AR = (uint32_t)(rx1_buf);

    //内存缓冲区2
    hdma_usart3_rx.Instance->M1AR = (uint32_t)(rx2_buf);

    //数据长度
    hdma_usart3_rx.Instance->NDTR = dma_buf_num;

    //使能双缓冲区
    SET_BIT(hdma_usart3_rx.Instance->CR, DMA_SxCR_DBM);

    //使能DMA
    __HAL_DMA_ENABLE(&hdma_usart3_rx);
}

/**
  * @brief          串口中断处理函数
  * @retval         none
  */
void USART3_IRQHandler(void)
{
    if (huart3.Instance->SR & UART_FLAG_RXNE)	//接收中断
    {
        __HAL_UART_CLEAR_PEFLAG(&huart3);
    }
    else if (USART3->SR & UART_FLAG_IDLE)		//空闲中断
    {
        static uint16_t this_time_rx_len = 0;

        __HAL_UART_CLEAR_PEFLAG(&huart3);

        if ((hdma_usart3_rx.Instance->CR & DMA_SxCR_CT) == RESET) {
            /* Current memory buffer used is Memory 0 */

            //失效DMA
            __HAL_DMA_DISABLE(&hdma_usart3_rx);

            //获取接收数据长度,长度 = 设定长度 - 剩余长度
			this_time_rx_len = SBUS_RX_BUF_NUM - hdma_usart3_rx.Instance->NDTR;

            //重新设定数据长度
            hdma_usart3_rx.Instance->NDTR = SBUS_RX_BUF_NUM;

            //设定缓冲区1
            hdma_usart3_rx.Instance->CR |= DMA_SxCR_CT;
            
            //使能DMA
            __HAL_DMA_ENABLE(&hdma_usart3_rx);

            if (this_time_rx_len == RC_FRAME_LENGTH) {
                sbus_to_rc(sbus_rx_buf[0], &rc_ctrl);
            }
        } else {
            /* Current memory buffer used is Memory 1 */

            //失效DMA
            __HAL_DMA_DISABLE(&hdma_usart3_rx);

            //获取接收数据长度,长度 = 设定长度 - 剩余长度
            this_time_rx_len = SBUS_RX_BUF_NUM - hdma_usart3_rx.Instance->NDTR;

            //重新设定数据长度
//            __HAL_DMA_GET_COUNTER(&hdma_usart3_rx) = SBUS_RX_BUF_NUM;
            hdma_usart3_rx.Instance->NDTR = SBUS_RX_BUF_NUM;

            //设定缓冲区0
            DMA1_Stream1->CR &= ~(DMA_SxCR_CT);
            
            //使能DMA
            __HAL_DMA_ENABLE(&hdma_usart3_rx);

            if (this_time_rx_len == RC_FRAME_LENGTH) {
                //处理遥控器数据
                sbus_to_rc(sbus_rx_buf[1], &rc_ctrl);
            }
        }
    }
}
