/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

			嵌入式开发平台——MAX5402EUA数字电位器模块

  -------------------------------------------------------
   文 件 名   : Drv_MAX5402EUA.c
   版 本 号   : V1.0.0.0
   作    者   : ryc
   生成日期   : 2019年10月14日
   功能描述   : 定义MAX5402EUA数字电位器的驱动。
   使用方法   ：上层模块通过调用MAX5402EUA_Init获得一个MAX5402EUA
				的指针，通过调用MAX5402EUASet设置增益值。
   依赖于     : Drv_Software_Spi V1.0.0.0
   注         ：该模块不依赖于硬件电路。 
 ********************************************************/
 
#ifndef _DRV_HARDMAX5402EUA_H_
#define _DRV_HARDMAX5402EUA_H_ 

#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"
#include "BSP_Spi.h"
#include "Drv_MAX5402EUA.h"
#include "Drv_SimulateSpi.h"

/*MAX5402EUA模块枚举*/
typedef enum{
	MAX5402EUA_HARD_1 = 0,
	MAX5402EUA_HARD_2,
	MAX5402EUA_HARD_3,
	MAX5402EUA_HARD_4,
	MAX5402EUA_HARD_5,
	MAX5402EUA_HARD_6,
	MAX5402EUA_HARD_7,
	MAX5402EUA_HARD_8,
	MAX5402EUA_HARD_9,
	MAX5402EUA_HARD_10,
	MAX5402EUA_HARD_11,
	MAX5402EUA_HARD_12,
	MAX5402EUA_HARD_13,
	MAX5402EUA_HARD_14,
	MAX5402EUA_HARD_15,
	MAX5402EUA_HARD_16,
	MAX5402EUA_HARD_17,
	MAX5402EUA_HARD_18,
	MAX5402EUA_HARD_19,
	MAX5402EUA_HARD_20,
	MAX5402EUA_HARD_21,
	MAX5402EUA_HARD_22,
	MAX5402EUA_HARD_23,
	MAX5402EUA_HARD_24,
	MAX5402EUA_HARD_25,
	MAX5402EUA_HARD_26,
	MAX5402EUA_HARD_27,
	MAX5402EUA_HARD_28,
	MAX5402EUA_HARD_BUTT
} DRV_MAX5402EUA_HARD_ENUM;

/*MAX5402EUA模块状态枚举*/
typedef enum{
	MAX5402EUA_HARD_UNDEFINED = 0,				/*未初始化*/
	MAX5402EUA_HARD_READY     = 1				/*设置好*/
} DRV_MAX5402EUA_HARD_STATUS_ENUM;

/*MAX5402EUA模块结构体*/
typedef struct{
	/*------------------------------变量*/
	DRV_MAX5402EUA_HARD_STATUS_ENUM status;		/*该MAX5402EUA模块的状态*/
	uint8_t gain;							    /*电阻档数，每档39.0625欧姆，共255档*/
	/*------------------------------变常*/
	/*------------------------------常量*/
	DRV_MAX5402EUA_HARD_ENUM id;			    /*MAX5402EUA模块id*/	
	BSP_SPI_ENUM hardspi;
	uint32_t theta;							    /*时钟速度参数*/
	
	BSP_PORT_ENUM nss_port_number; 
	BSP_PIN_ENUM nss_pin_number;
} DRV_MAX5402EUA_HARD_TYPE;

/* 接口函数
 ********************************************************/

/* 初始化MAX5402EUA模块
  -----------------------------
  入口：MAX5402EUA模块的ID号，电阻值，引脚端口
  返回值：初始化好的MAX5402EUA模块结构体
*/
extern DRV_MAX5402EUA_HARD_TYPE* Max5402euaHardInit(DRV_MAX5402EUA_HARD_ENUM id, \
									                uint8_t gain, BSP_SPI_ENUM spi_number,uint32_t theta, \
									                BSP_PORT_ENUM miso_port_number, BSP_PIN_ENUM miso_pin_number, \
									                BSP_PORT_ENUM mosi_port_number, BSP_PIN_ENUM mosi_pin_number, \
									                BSP_PORT_ENUM sck_port_number, BSP_PIN_ENUM sck_pin_number, \
									                BSP_PORT_ENUM nss_port_number, BSP_PIN_ENUM nss_pin_number);
/* 设置MAX5402EUA阻值
  -----------------------------
  入口：MAX5402EUA模块的ID号，电阻档数
  返回值：true 成功，false 失败
*/
extern bool Max5402euaHardSet(DRV_MAX5402EUA_HARD_TYPE* p_unit, uint8_t gain);

static bool _Max5402euaHardStart(DRV_MAX5402EUA_HARD_TYPE* p_unit);
static bool _Max5402euaHardEnd(DRV_MAX5402EUA_HARD_TYPE* p_unit);
static bool _Max5402euaHardDelayUs(DRV_MAX5402EUA_HARD_TYPE* p_unit, uint32_t time);
//static bool _Max5402euaHardWait(DRV_MAX5402EUA_HARD_TYPE* p_unit);
											
#endif
