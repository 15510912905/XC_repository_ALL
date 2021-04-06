/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

				嵌入式开发平台——PID模块

  -------------------------------------------------------
   文 件 名   : Drv_Pid.c
   版 本 号   : V1.0.0.0
   作    者   : ryc
   生成日期   : 2020年2月14日
   功能描述   : 定义一种PID模块。
   使用方法   ：
   依赖于     : 
   注         ：该模块不依赖于硬件电路。 
 ********************************************************/
 
#ifndef _DRV_PID_H_
#define _DRV_PID_H_ 

#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"
#include "float.h"
#include "BSP_Gpio.h"

#define DEFAULTPERIOD	1
#define	FULLDUTY		200
#define	ARRAY_DUTY		100.0	/*积分限幅百分比*/
#define	ARRAY_ERR		3.0  	/*积分舍弃偏差*/

/*PID模块枚举*/
typedef enum{
	PID_1 = 0,
	PID_2,
	PID_3,
	PID_4,
	PID_BUTT
} DRV_PID_ENUM;

/*PID模块状态枚举*/
typedef enum{
	PID_TUNING = 0,		/*整定*/
	PID_WORKING = 1,	/*运行*/
} DRV_PID_STATUS_ENUM;

/*PID模块结构体*/
typedef struct{
	/*------------------------------变量*/
	DRV_PID_STATUS_ENUM status;				/*该PID模块的状态*/
    float lasterr; 			/*Error[-1]*/
    float preverr; 			/*Error[-2]*/
    float sumerr; 			/*Sums of Errors*/
	/*------------------------------变常*/
	/*------------------------------常量*/
	DRV_PID_ENUM id;		/*PID模块id*/
    float setpoint; 		/*设定目标*/
    float kp; 				/*比例常数*/
    float ki; 				/*积分常数*/
    float kd; 				/*微分常数*/
} DRV_PID_TYPE;

/* 接口函数
 ********************************************************/

/* 初始化PID模块
  -----------------------------
  入口：PID模块的ID号，目标值，P、I、D参数
  返回值：初始化好的PID模块结构体
*/
extern DRV_PID_TYPE* Drv_PidInit(DRV_PID_ENUM id, float setpoint, float kp, float ki, float kd);

/* PID模块输出计算
  -----------------------------
  入口：PID模块指针，当前值
  返回值：输出值
*/					  
extern float Drv_PidCalculate(DRV_PID_TYPE* p_unit, float current);

#endif
