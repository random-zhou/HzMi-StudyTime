/**
  ****************************(C) COPYRIGHT 2024 HzMI****************************
  * @file       filters.c/h
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
/**
	*******************************************************************************
  * @brief   ³£ÓÃÂË²¨Æ÷:
	*					 »¬¶¯Æ½¾ùÖµÂË²¨
	*					 µÍÍ¨ÂË²¨
	*					 	
	*******************************************************************************
**/
#include "filters.h"

int Slide_Average_Filter ( Slide_Average_Filter_Struct_Pointer Slide_Ave_P )				//»¬¶¯Æ½¾ùÖµÂË²¨
{
	Slide_Ave_P->Sum -= Slide_Ave_P->Array[ Slide_Ave_P->Pointer ];
	Slide_Ave_P->Sum += Slide_Ave_P->New_Data;
	Slide_Ave_P->Array[ Slide_Ave_P->Pointer ] = Slide_Ave_P->New_Data;
	Slide_Ave_P->Result = Slide_Ave_P->Sum / Slide_Average_Filter_Sample_Capacity;
	Slide_Ave_P->Pointer++;
	Slide_Ave_P->Pointer %= Slide_Average_Filter_Sample_Capacity;
	
	return 1;
}


int Low_Pass_Filter ( Low_Pass_Filter_Struct_Pointer Low_Pass_Filter_Pass_P )				//µÍÍ¨ÂË²¨
{
	Low_Pass_Filter_Pass_P->Result = Low_Pass_Filter_Pass_P->History_Data * ( 1 - Low_Pass_Filter_Pass_P->K ) + Low_Pass_Filter_Pass_P->New_Data * Low_Pass_Filter_Pass_P->K;
	Low_Pass_Filter_Pass_P->History_Data = Low_Pass_Filter_Pass_P->Result;
	return Low_Pass_Filter_Pass_P->Result;
}

void Ramp_Func_Init( Ramp_Struct_Pointer Ramp_P, float step, float current )
{
	Ramp_P->step = step;
	Ramp_P->current = current;
	Ramp_P->out = current;	
}

void Ramp_Func_Cal( Ramp_Struct_Pointer Ramp_P, float target, float current )
{
	
	Ramp_P->target = target;
	Ramp_P->current = current;
	Ramp_P->e = Ramp_P->target - Ramp_P->current;
	if( Ramp_P->e > 0 )
	{
		Ramp_P->out = Ramp_P->out + Ramp_P->step;
		Ramp_P->out = Ramp_P->out > Ramp_P->target ? Ramp_P->target : Ramp_P->out;
	}
	else if( Ramp_P->e < 0 )
	{
		Ramp_P->out = Ramp_P->out - Ramp_P->step;
		Ramp_P->out = Ramp_P->out < Ramp_P->target ? Ramp_P->target : Ramp_P->out;
	}
}





