#include "STEPPERMOTOR.h"
#include "SYSTEM.h"
#include "LED.h"


#define HIGH GPIO_PIN_SET //高电平
#define LOW GPIO_PIN_RESET//低电平

#define ENABLE LOW//开
#define DISABLE HIGH//关

#define CW DISABLE//顺时针
#define CCW ENABLE//逆时针

#define DRV_ENA(x) HAL_GPIO_WritePin(ENA_GPIO_Port,ENA_Pin,x);//驱动使能
#define DRV_DIR(x) HAL_GPIO_WritePin(DIR_GPIO_Port,DIR_Pin,x);//驱动方向
#define DRV_PUL(x) HAL_GPIO_WritePin(PUL_GPIO_Port,PUL_Pin,x);//驱动反转电平



void STEPPER_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct = {0};
		__HAL_RCC_GPIOC_CLK_ENABLE();

		GPIO_InitStruct.Pin = ENA_Pin|DIR_Pin|PUL_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		DRV_ENA(DISABLE);
		HAL_Delay_us_init(180);
}



void STEPPER_ParaSet(STEPMotor *stepper,Dir direction,float stepangle,int setturns,int tim,double subdivide)
{
		stepper->direction=direction;
		stepper->stepangle=stepangle;
		stepper->setturns=setturns;
		stepper->subdivide=subdivide;
		stepper->tim=tim;
		
}

void STEPPER_ParaInit(STEPMotor *stepper)
{
		stepper->direction=(Dir)0;
		stepper->state=(State)0;
		stepper->stepangle=1.8;
		stepper->setturns=0;
	  stepper->realangle=0;
		stepper->subdivide=0;
		stepper->tim=0;
		stepper->realturns=0;
		
}

void STEPPER_MOVE(STEPMotor *stepper)
{
		uint32_t real_turns;
		if (stepper->direction==0)
		{
				DRV_DIR(CW); 
		}
		if(stepper->direction==1)
    {
        DRV_DIR(CCW);       
    }
		
		DRV_ENA(ENABLE);
		
		for(uint32_t i=0;i<=((stepper->setturns)*(stepper->subdivide));i++)  
    {      
	
				stepper->state=BUSY;
        PUL_GPIO_Port->ODR ^= PUL_Pin;                 
				HAL_Delay_us(stepper->tim); 
				
				if (i%(int)((stepper)->subdivide)==0)
				{
					
					if (stepper->direction==0)
					{
							stepper->realturns++;
						
					}
					if (stepper->direction==1)
					{
							stepper->realturns--;
					}
					real_turns=stepper->realturns;
					STEPPER_GetTurnsFeedBack(stepper);
				}
				stepper->realangle=(float)((real_turns)*360)+((i*(stepper->stepangle))/(stepper->subdivide));		
				
				STEPPER_GetAngleFeedBack(stepper);
				STEPPER_GetStateFeedBack(stepper);
    }
		DRV_ENA(DISABLE);
		stepper->state=FREE;
		STEPPER_GetStateFeedBack(stepper);
		
}


float STEPPER_GetAngleFeedBack(STEPMotor *stepper)
{
			return stepper->realangle;
}

uint16_t STEPPER_GetTurnsFeedBack(STEPMotor *stepper)
{
			return stepper->realturns;
}

State STEPPER_GetStateFeedBack(STEPMotor *stepper)
{
			return stepper->state;
}

















