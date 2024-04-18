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
#ifndef __FILTERS_BY_RFS_H
#define __FILTERS_BY_RFS_H




/*****************************滑动平均值滤波*****************************/
typedef int Data_Type_Slide_Average_Filter;
typedef struct 																								//滑动平均值滤波的结构体
{
	#define			 												Slide_Average_Filter_Sample_Capacity 						6							
	Data_Type_Slide_Average_Filter			Sum;																										
	Data_Type_Slide_Average_Filter			Array[ Slide_Average_Filter_Sample_Capacity ];								
	Data_Type_Slide_Average_Filter 	 		New_Data;																							
	Data_Type_Slide_Average_Filter			Result;																										
	int																	Pointer;										
}										
Slide_Average_Filter_Struct,
*Slide_Average_Filter_Struct_Pointer;

int Slide_Average_Filter ( Slide_Average_Filter_Struct_Pointer Slide_Ave_P );


/*****************************低通滤波*****************************/
typedef float Data_Type_Low_Pass_Filter;
typedef struct																						//低通滤波结构体
{
	double 												K; 												//K越大越相信新数据
	Data_Type_Low_Pass_Filter			History_Data;
	Data_Type_Low_Pass_Filter			New_Data;
	Data_Type_Low_Pass_Filter			Result;
}
Low_Pass_Filter_Struct,
*Low_Pass_Filter_Struct_Pointer;

int Low_Pass_Filter ( Low_Pass_Filter_Struct_Pointer Low_Pass_Filter_Pass_P );

typedef struct
{
	float target;
	float current;
	float step;
	float out;
	float e;
}
Ramp_Struct,
*Ramp_Struct_Pointer;

void Ramp_Func_Init( Ramp_Struct_Pointer Ramp_P, float step, float current );
void Ramp_Func_Cal( Ramp_Struct_Pointer Ramp_P, float target, float current );

#endif

