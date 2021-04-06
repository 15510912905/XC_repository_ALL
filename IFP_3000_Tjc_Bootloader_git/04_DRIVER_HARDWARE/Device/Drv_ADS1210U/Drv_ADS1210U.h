/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

			嵌入式开发平台——ADS1210U 24位模数转换模块

  -------------------------------------------------------
   文 件 名   : Drv_ADS1210U.c
   版 本 号   : V1.0.0.0
   作    者   : ryc
   生成日期   : 2020年2月14日
   功能描述   : 定义ADS1210U模数转换器的驱动。
   使用方法   ：上层模块通过调用Ads1210uInit获得一个ADS1210U
				的指针。
   依赖于     : Drv_SimulateSpi V1.0.0.0
   注         ：该模块不依赖于硬件电路。 
 ********************************************************/

#ifndef _DRV_ADS1210U_H_
#define _DRV_ADS1210U_H_ 

#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"
#include "Drv_SimulateSpi.h"

/*ADS1210U模块枚举*/
typedef enum{
	ADS1210U_1 = 0,
	ADS1210U_BUTT
} DRV_ADS1210U_ENUM;

/*ADS1210U模块状态枚举*/
typedef enum{
	ADS1210U_UNDEFINED = 0,				/*未初始化*/
	ADS1210U_READY  = 1					/*可用*/
} DRV_ADS1210U_STATUS_ENUM;

/*ADS1210U模块结构体*/
typedef struct{
	/*------------------------------变量*/
	DRV_ADS1210U_STATUS_ENUM status;		/*该ADS1210U模块的状态*/
	uint32_t rx_buffer;						/*接收缓存*/
	uint8_t drdy_buffer;					/*DRDY脚状态缓存*/
	/*------------------------------变常*/
	/*------------------------------常量*/
	DRV_ADS1210U_ENUM id;					/*ADS1210U模块id*/
	DRV_SOFTWARE_SPI_TYPE* spi_port;			/*SPI接口*/
	BSP_PORT_ENUM drdy_port_number; 		/*DRDY引脚*/
	BSP_PIN_ENUM drdy_pin_number;
	
} DRV_ADS1210U_TYPE;

/* 接口函数
 ********************************************************/

/* 初始化ADS1210U模块
  -----------------------------
  入口：ADS1210U模块的ID号，SPI端口编号，引脚端口号
  返回值：初始化好的ADS1210U模块结构体
*/
extern DRV_ADS1210U_TYPE* Drv_Ads1210uInit(DRV_ADS1210U_ENUM id, \
										BSP_PORT_ENUM sclk_port_number, BSP_PIN_ENUM sclk_pin_number, \
										BSP_PORT_ENUM sdout_port_number, BSP_PIN_ENUM sdout_pin_number, \
										BSP_PORT_ENUM sdio_port_number, BSP_PIN_ENUM sdio_pin_number, \
										BSP_PORT_ENUM drdy_port_number, BSP_PIN_ENUM drdy_pin_number);

/* ADS1210U启动
  -----------------------------
  入口：ADS1210U模块结构体指针
  返回值：true 成功，false 失败
*/
extern bool Ads1210uStart(DRV_ADS1210U_TYPE* p_unit);

/*  ADS1210U模块完成一次采样
  -----------------------------
  入口：ADS1210U模块结构体指针
  返回值：true 成功，false 失败
*/
extern uint32_t Ads1210uOneAcq(DRV_ADS1210U_TYPE* p_unit);

/* 内部函数
 ********************************************************/

/* ADS1210U等待转换
  -----------------------------
  入口：ADS1210U模块结构体指针
  返回值：true 成功，false 失败
*/
static bool _Ads1210uWait(DRV_ADS1210U_TYPE* p_unit);

/*  ADS1210U模块延时n微秒
  -----------------------------
  入口：延时时间
  返回值：true 成功，false 失败
*/
static bool _Ads1210uDelayUs(DRV_ADS1210U_TYPE* p_unit, uint32_t time);

/*  ADS1210U模块读取AD值
  -----------------------------
  入口：命令
  返回值：true 成功，false 失败
*/
static uint32_t _Ads1210uReadData(DRV_ADS1210U_TYPE* p_unit);

#endif
