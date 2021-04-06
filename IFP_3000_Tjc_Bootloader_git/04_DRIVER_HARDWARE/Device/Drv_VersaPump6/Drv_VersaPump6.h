/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

			嵌入式开发平台——VersaPump6微量泵模块

  -------------------------------------------------------
   文 件 名   : Drv_VersaPump6.c
   版 本 号   : V1.0.0.0
   作    者   : ryc
   生成日期   : 2020年03月18日
   功能描述   : 定义VersaPump6微量泵模块的控制。
   使用方法   ：上层模块通过调用VersaPump6_Init获得一个
				VersaPump6模块的指针，通过调用VersaPump6_Sample
				进行吸样，通过调用VersaPump6_BlowOff排样，
				通过调用VersaPump6_Reset复位。
   依赖于     : BSP.h
   注         ：该模块不依赖于硬件电路。 
 ********************************************************/
 
#ifndef _DRV_VERSAPUMP6_H_
#define _DRV_VERSAPUMP6_H_

#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"
#include "BSP_Uart.h"

#define USART_RX_MAX_NUMBER	100
#define USART_TX_MAX_NUMBER	100

/*微量泵模块枚举*/
typedef enum{
	VERSAPUMP6_1 = 0,
	VERSAPUMP6_BUTT
} DRV_VERSAPUMP6_ENUM;

/*微量泵模块状态枚举*/
typedef enum{
	VERSAPUMP6_UNDEFINED = 0,		/*未初始化*/
	VERSAPUMP6_READY,				/*准备好*/
	VERSAPUMP6_BUSY					/*繁忙*/
} DRV_VERSAPUMP6_STATUS_ENUM;

/*微量泵阀状态枚举*/
typedef enum{
	VERSAPUMP6_VALUE_AB = 0,		/*旁通*/
	VERSAPUMP6_VALUE_AS,			/*A通*/
	VERSAPUMP6_VALUE_BS,			/*B通*/
} DRV_VERSAPUMP6_VALUE_STATUS_ENUM;

/*微量泵模块结构体*/
typedef struct{
	/*------------------------------变量*/
	DRV_VERSAPUMP6_STATUS_ENUM status;		/*该模块的状态*/
	uint8_t rx_buffer[USART_RX_MAX_NUMBER];	/*接收缓存*/
	uint8_t rx_push;						/*接收下标*/
	DRV_VERSAPUMP6_VALUE_STATUS_ENUM value_status;	/*阀状态*/
	uint16_t distance_now;					/*当前位置*/
	/*------------------------------变常*/
	
	/*------------------------------常量*/
	DRV_VERSAPUMP6_ENUM id;					/*模块编号*/
	uint16_t max_step;						/*总步数*/
	uint16_t max_distance;					/*总行程*/
	BSP_USART_ENUM usart_number;			/*串口模块编号*/
	uint32_t baud_rate;						/*波特率*/
	BSP_PORT_ENUM tx_port_number; 			/*TX引脚端口号*/
	BSP_PIN_ENUM  tx_pin_number;			/*TX引脚编号*/
	BSP_PORT_ENUM rx_port_number; 			/*RX引脚端口号*/
	BSP_PIN_ENUM  rx_pin_number;			/*RX引脚编号*/
	OS_EVENT* work_done_sem;				/*动作完成信号量*/
} DRV_VERSAPUMP6_TYPE;

/* 接口函数
 ********************************************************/

/* 初始化微量泵模块
  -----------------------------
  入口：微量泵模块的ID号，波特率，TX、RX端口
  返回值：初始化好的微量泵模块结构体
*/
extern DRV_VERSAPUMP6_TYPE* Drv_VersaPump6_Init(DRV_VERSAPUMP6_ENUM id, \
										uint16_t max_step, uint16_t max_distance, \
										BSP_USART_ENUM usart_number, uint32_t baud_rate, \
										BSP_PORT_ENUM tx_port_number, BSP_PIN_ENUM tx_pin_number, \
										BSP_PORT_ENUM rx_port_number, BSP_PIN_ENUM rx_pin_number);

/* 微量泵吸样
  -----------------------------
  入口：微量泵模块结构体
  返回值：true 成功，false 失败
*/
extern bool Drv_VersaPump6_Sample(DRV_VERSAPUMP6_TYPE* p_unit, double distance);

/* 微量泵排样
  -----------------------------
  入口：微量泵模块结构体
  返回值：true 成功，false 失败
*/
extern bool Drv_VersaPump6_BlowOff(DRV_VERSAPUMP6_TYPE* p_unit, double distance);

/* 微量泵复位
  -----------------------------
  入口：微量泵模块结构体
  返回值：true 成功，false 失败
*/
extern bool Drv_VersaPump6_Reset(DRV_VERSAPUMP6_TYPE* p_unit);

/* 微量泵阀状态切换
  -----------------------------
  入口：微量泵模块结构体，阀的状态
  返回值：true 成功，false 失败
*/
extern bool Drv_VersaPump6_ValueToggle(DRV_VERSAPUMP6_TYPE* p_unit, DRV_VERSAPUMP6_VALUE_STATUS_ENUM status);

/* 发送命令
  -----------------------------
  入口：微量泵模块结构体，命令字符串
  返回值：true 成功，false 失败
*/
static bool _Drv_VersaPump6_SendCmd(DRV_VERSAPUMP6_TYPE* p_unit, uint8_t* datas);

/* 判断整形数和字符串数是否相等
  -----------------------------
  入口：微量泵模块结构体，数据，字符串
  返回值：true 相等，false 不相等
*/
static bool _Drv_VersaPump6_Check(DRV_VERSAPUMP6_TYPE* p_unit, uint16_t data_int, uint8_t* data_str);

/* 提取字符串中的数值
  -----------------------------
  入口：微量泵模块结构体，字符串
  返回值：数值地址
*/
static uint8_t* _Drv_VersaPump6_GetDataStr(DRV_VERSAPUMP6_TYPE* p_unit, uint8_t* data_str);

#endif
