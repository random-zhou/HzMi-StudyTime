/*
 * @Author: “random-zhou” 2501601106@qq.com
 * @Date: 2024-04-17 22:13:05
 * @LastEditors: “random-zhou” 2501601106@qq.com
 * @LastEditTime: 2024-04-17 22:14:08
 * @FilePath: \HzMi-StudyTime\usual_control_algorithm\bsp_spi.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*
 * bsp_spi.h
 *
 *  Created on: 2021年10月24日
 *      Author: LBQ
 */
#ifndef BSP_SPI_H
#define BSP_SPI_H

#include "main.h"
#include "struct_typedef.h"
#include "spi.h"

extern void SPI1_DMA_init(uint32_t tx_buf, uint32_t rx_buf, uint16_t num);
extern void SPI1_DMA_enable(uint32_t tx_buf, uint32_t rx_buf, uint16_t ndtr);

#endif
