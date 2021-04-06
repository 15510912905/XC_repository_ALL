/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

				嵌入式开发平台——钻石ISE模块

  -------------------------------------------------------
   文 件 名   : Drv_DiamondIseModule.h
   版 本 号   : V1.0.0.0
   作    者   : ryc
   生成日期   : 2020年03月25日
   功能描述   : 定义钻石ISE模块的控制。
   使用方法   ：上层模块通过调用DiamondIseModule_Init获得一个
				ISE模块的指针。
   依赖于     : BSP.h
   注         ：该模块不依赖于硬件电路。 
 ********************************************************/
 
#ifndef _DRV_DIAMONDISEMODULE_H_
#define _DRV_DIAMONDISEMODULE_H_

#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"
#include "BSP_Uart.h"

#define USART_RX_MAX_NUMBER	100
#define USART_TX_MAX_NUMBER	100

/*DIAMOND_ISE模块枚举*/
typedef enum{
	DIAMOND_ISE_1 = 0,
	DIAMOND_ISE_BUTT
} DRV_DIAMOND_ISE_ENUM;

/*DIAMOND_ISE模块状态枚举*/
typedef enum{
	DIAMOND_ISE_UNDEFINED	= 0,				/*未初始化*/
	DIAMOND_ISE_READY		= 1,				/*准备好*/
	DIAMOND_ISE_BUSY		= 2,				/*繁忙*/
} DRV_DIAMOND_ISE_STATUS_ENUM;

/*DIAMOND_ISE模块结构体*/
typedef struct{
	/*------------------------------变量*/
	DRV_DIAMOND_ISE_STATUS_ENUM status;			/*该DIAMOND_ISE模块的状态*/
	uint8_t rx_buffer[USART_RX_MAX_NUMBER];		/*接收缓存*/
	uint8_t rx_push;							/*写入下标*/
	/*------------------------------变常*/
	
	/*------------------------------常量*/
	DRV_DIAMOND_ISE_ENUM id;					/*DIAMOND_ISE模块编号*/
	BSP_USART_ENUM usart_number;				/*串口模块编号*/
	uint32_t baud_rate;							/*波特率*/
	BSP_PORT_ENUM tx_port_number; 				/*TX引脚端口号*/
	BSP_PIN_ENUM  tx_pin_number;				/*TX引脚编号*/
	BSP_PORT_ENUM rx_port_number; 				/*RX引脚端口号*/
	BSP_PIN_ENUM  rx_pin_number;				/*RX引脚编号*/
	OS_EVENT* work_done_sem;					/*动作完成信号量*/
} DRV_DIAMOND_ISE_TYPE;

/* 接口函数
 ********************************************************/

/* 初始化DIAMOND_ISE模块
  -----------------------------
  入口：扫码模块的ID号，波特率，TX、RX端口
  返回值：初始化好的扫码模块结构体
*/
extern DRV_CR100M2_TYPE* Drv_CR100M2_Init(DRV_CR100M2_ENUM id, \
										BSP_USART_ENUM usart_number, uint32_t baud_rate, \
										BSP_PORT_ENUM tx_port_number, BSP_PIN_ENUM tx_pin_number, \
										BSP_PORT_ENUM rx_port_number, BSP_PIN_ENUM rx_pin_number);

/* 扫码头扫描一次
  -----------------------------
  入口：扫码模块结构体
  返回值：true 扫描成功，false 扫码失败
*/
extern bool Drv_CR100M2_Scan(DRV_CR100M2_TYPE* p_unit);

/* 获取扫码数据
  -----------------------------
  入口：扫码模块结构体，数据缓存区地址，数据缓存区大小
  返回值：true 获取成功，false 获取失败
*/
extern bool Drv_CR100M2_Get(DRV_CR100M2_TYPE* p_unit, uint8_t* datas, uint16_t datas_number);

#endif
