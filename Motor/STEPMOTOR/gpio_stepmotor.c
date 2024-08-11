/**
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  * @file       stepmotor.c/h
  * @brief      步进电机驱动方法
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Apr-18-2024     HZMI              1. done
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2024 HZMI****************************
  */
#include "GPIO_STEPPERMOTOR.h"
// #include "SYSTEM.h"//delayus的函数在里面
// #include "LED.h"
/*使用方法：
1.电机初始化 STEPPER_Init
2、电机参数初始化 STEPPER_ParaInit
3.电机参数设置 STEPPER_ParaSet
4.电机驱动 STEPPER_MOVE(&stepper)
*/

#define HIGH GPIO_PIN_SET //高电平
#define LOW GPIO_PIN_RESET//低电平

#define ENABLE LOW//开
#define DISABLE HIGH//关

#define CW DISABLE//顺时针
#define CCW ENABLE//逆时针

#define DRV_ENA(x) HAL_GPIO_WritePin(ENA_GPIO_Port,ENA_Pin,x);//驱动使能
#define DRV_DIR(x) HAL_GPIO_WritePin(DIR_GPIO_Port,DIR_Pin,x);//驱动方向
#define DRV_PUL(x) HAL_GPIO_WritePin(PUL_GPIO_Port,PUL_Pin,x);//驱动反转电平



// 电机初始化引脚口函数
void STEPPER_Init(void){
    GPIO_InitTypeDef GPIO_InitStruct = {0}; // 初始化GPIO结构体
    __HAL_RCC_GPIOC_CLK_ENABLE(); // 使能GPIOC的时钟

    GPIO_InitStruct.Pin = ENA_Pin|DIR_Pin|PUL_Pin; // 设置引脚，ENA, DIR, PUL
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // 设置为推挽输出模式
    GPIO_InitStruct.Pull = GPIO_NOPULL; // 不设置上拉或下拉电阻
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // 设置为高速
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct); // 初始化GPIO

    DRV_ENA(DISABLE); // 禁用驱动
    HAL_Delay_us_init(180); // 初始化微秒级延时
}

// 电机参数设置函数
void STEPPER_ParaSet(STEPMotor *stepper, Dir direction, float stepangle, int setturns, int tim, double subdivide){
    stepper->direction = direction; // 设置电机转向
    stepper->stepangle = stepangle; // 设置步角
    stepper->setturns = setturns; // 设置电机转动的圈数
    stepper->subdivide = subdivide; // 设置细分
    stepper->tim = tim; // 设置延时时间
}

// 电机参数初始化函数
void STEPPER_ParaInit(STEPMotor *stepper){
    stepper->direction = (Dir)0; // 初始化电机转向
    stepper->state = (State)0; // 初始化电机状态
    stepper->stepangle = 1.8; // 初始化步角
    stepper->setturns = 0; // 初始化设置的圈数
    stepper->realangle = 0; // 初始化实际角度
    stepper->subdivide = 0; // 初始化细分
    stepper->tim = 0; // 初始化延时时间
    stepper->realturns = 0; // 初始化实际转动的圈数
}

// 电机驱动函数
void STEPPER_MOVE(STEPMotor *stepper){
    uint32_t real_turns;
    if (stepper->direction == 0){ // 如果方向为0，设置为顺时针
        DRV_DIR(CW);
    }
    if(stepper->direction == 1){ // 如果方向为1，设置为逆时针
        DRV_DIR(CCW);
    }
    
    DRV_ENA(ENABLE); // 使能驱动

    for(uint32_t i = 0; i <= ((stepper->setturns) * (stepper->subdivide)); i++){ // 根据设置的圈数和细分进行循环
        stepper->state = BUSY; // 设置电机状态为忙碌
        PUL_GPIO_Port->ODR ^= PUL_Pin; // 切换脉冲引脚状态
        HAL_Delay_us(stepper->tim); // 延时

        if (i % (int)(stepper->subdivide) == 0){ // 每完成一次细分，更新实际转动圈数
            if (stepper->direction == 0){
                stepper->realturns++; // 顺时针增加圈数
            }
            if (stepper->direction == 1){
                stepper->realturns--; // 逆时针减少圈数
            }
            real_turns = stepper->realturns; // 获取实际转动圈数
            STEPPER_GetTurnsFeedBack(stepper); // 获取圈数反馈
        }
        stepper->realangle = (float)(real_turns * 360) + ((i * stepper->stepangle) / stepper->subdivide); // 计算实际角度
        STEPPER_GetAngleFeedBack(stepper); // 获取角度反馈
        STEPPER_GetStateFeedBack(stepper); // 获取状态反馈
    }
    DRV_ENA(DISABLE); // 禁用驱动
    stepper->state = FREE; // 设置电机状态为空闲
    STEPPER_GetStateFeedBack(stepper); // 获取状态反馈
}

// 电机反馈实时角度函数
float STEPPER_GetAngleFeedBack(STEPMotor *stepper){
    return stepper->realangle; // 返回实际角度
}

// 电机反馈实时圈数函数
uint16_t STEPPER_GetTurnsFeedBack(STEPMotor *stepper){
    return stepper->realturns; // 返回实际转动的圈数
}

// 电机反馈运行状态函数
State STEPPER_GetStateFeedBack(STEPMotor *stepper){
    return stepper->state; // 返回电机运行状态
}

















