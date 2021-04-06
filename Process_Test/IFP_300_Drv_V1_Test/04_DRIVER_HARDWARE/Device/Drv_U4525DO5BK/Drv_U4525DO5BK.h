/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

			嵌入式开发平台——U4525DO5BK压力检测模块

  -------------------------------------------------------
   文 件 名   : Drv_U4525DO5BK.h
   版 本 号   : V1.0.0.0
   作    者   : ryc
   生成日期   : 2020年04月22日
   功能描述   : 定义U4525DO5BK压力检测模块的驱动。
   使用方法   ：
   依赖于     : 
   注         ：该模块不依赖于硬件电路。 
 ********************************************************/

#ifndef _DRV_U4525DO5BK_H_
#define _DRV_U4525DO5BK_H_

#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"
#include "BSP_Gpio.h"
#include "Drv_SimulateIic.h"

typedef struct{
	unsigned short pressure;	/*压力值*/
} Data_Fetch_2;

typedef struct{
	unsigned short pressure;	/*压力值*/
	unsigned char  temperature;	/*温度值，8位精度*/
} Data_Fetch_3;

typedef struct{
	unsigned short pressure;	/*压力值*/
	unsigned short temperature;	/*温度值，11位精度*/
} Data_Fetch_4;

/*U4525DO5BK模块寄存器地址枚举*/
typedef enum{
	U4525DO5BK_WRITE = 0,		/*写*/
	U4525DO5BK_READ,				/*读*/
} DRV_U4525DO5BK_ADDR_ENUM;

/*U4525DO5BK模块枚举*/
typedef enum{
	U4525DO5BK_1 = 0,
	U4525DO5BK_2,
	U4525DO5BK_3,
	U4525DO5BK_4,
	U4525DO5BK_BUTT
} DRV_U4525DO5BK_ENUM;

/*U4525DO5BK模块状态枚举*/
typedef enum{
	U4525DO5BK_UNDEFINED = 0,				/*未初始化*/
	U4525DO5BK_STANDBY,						/*预备*/
	U4525DO5BK_BUSY,							/*繁忙*/
	U4525DO5BK_READY							/*准备好*/
} DRV_U4525DO5BK_STATUS_ENUM;

/*U4525DO5BK模块结构体*/
typedef struct{
	/*------------------------------变量*/
	DRV_U4525DO5BK_STATUS_ENUM status;		/*该4525DO5BK模块的状态*/
	double pressure;						/*压力值*/
	/*------------------------------变常*/
	/*------------------------------常量*/
	DRV_U4525DO5BK_ENUM id;					/*4525DO5BK模块id*/
	uint8_t addr;							/*器件地址*/
	uint8_t range;							/*量程*/
	DRV_SIMULATE_IIC_TYPE* iic_port;		/*IIC端口*/	
	BSP_PORT_ENUM int_port_number; 			/*int引脚端口号*/
	BSP_PIN_ENUM int_pin_number;			/*int引脚编号*/
} DRV_U4525DO5BK_TYPE;

/* 接口函数
 ********************************************************/

/* 初始化U4525DO5BK模块
  -----------------------------
  入口：U4525DO5BK模块的ID号，IO端口
  返回值：初始化好的U4525DO5BK模块结构体
*/
extern DRV_U4525DO5BK_TYPE* Drv_U4525DO5BKInit(DRV_U4525DO5BK_ENUM id, \
												uint8_t addr, \
												uint8_t range, \
												BSP_PORT_ENUM sda_port_number, BSP_PIN_ENUM sda_pin_number, \
												BSP_PORT_ENUM scl_port_number, BSP_PIN_ENUM scl_pin_number, \
												BSP_PORT_ENUM int_port_number, BSP_PIN_ENUM int_pin_number);

/*
  启动测量
  ----------------------------
*/
extern void Drv_U4525DO5BKReadMr(DRV_U4525DO5BK_TYPE* p_unit);

/*
  读压力值
  ----------------------------
*/
extern Data_Fetch_2 Drv_U4525DO5BKReadDF2(DRV_U4525DO5BK_TYPE* p_unit);

/*
  读压力值和8位温度值
  ----------------------------
*/
extern Data_Fetch_3 Drv_U4525DO5BKReadDF3(DRV_U4525DO5BK_TYPE* p_unit);

/*
  读压力值和11位温度值
  ----------------------------
*/
extern Data_Fetch_4 Drv_U4525DO5BKReadDF4(DRV_U4525DO5BK_TYPE* p_unit);

/*
  读转换状态
  ----------------------------
*/
extern bool Drv_U4525DO5BKGetState(DRV_U4525DO5BK_TYPE* p_unit);

#endif
