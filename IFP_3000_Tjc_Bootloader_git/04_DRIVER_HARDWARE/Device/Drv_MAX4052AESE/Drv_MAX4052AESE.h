/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

			嵌入式开发平台——MAX4052AESE多路开关模块

  -------------------------------------------------------
   文 件 名   : Drv_MAX4052AESE.c
   版 本 号   : V1.0.0.0
   作    者   : ryc
   生成日期   : 2020年2月14日
   功能描述   : 定义MAX4052AESE多路开关的驱动。
   使用方法   ：上层模块通过调用Max4052aeseInit获得一个Max4052aese
				的指针，通过调用Max4052aeseSet设置选通哪一路。
   依赖于     : BSP_Gpio V1.0.0.0
   注         ：该模块不依赖于硬件电路。 
 ********************************************************/

#ifndef _DRV_MAX4052AESE_H_
#define _DRV_MAX4052AESE_H_ 

#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"
#include "BSP_Gpio.h"

/*MAX4052AESE模块枚举*/
typedef enum{
	MAX4052AESE_1 = 0,
	MAX4052AESE_BUTT
} DRV_MAX4052AESE_ENUM;

/*MAX4052AESE模块状态枚举*/
typedef enum{
	MAX4052AESE_UNDEFINED = 0,				/*未初始化*/
	MAX4052AESE_READY  = 1					/*可用*/
} DRV_MAX4052AESE_STATUS_ENUM;

/*MAX4052AESE模块结构体*/
typedef struct{
	/*------------------------------变量*/
	DRV_MAX4052AESE_STATUS_ENUM status;		/*该MAX4052AESE模块的状态*/
	bool adda_pin_buffer;					/*adda输出引脚缓存*/
	bool addb_pin_buffer;					/*addb输出引脚缓存*/
	uint8_t choose;							/*通道选择*/
	/*------------------------------变常*/
	/*------------------------------常量*/
	DRV_MAX4052AESE_ENUM id;				/*MAX4052AESE模块id*/
	BSP_PORT_ENUM adda_port_number; 		/*adda引脚端口号*/
	BSP_PIN_ENUM adda_pin_number;			/*adda引脚编号*/
	BSP_PORT_ENUM addb_port_number; 		/*addb引脚端口号*/
	BSP_PIN_ENUM addb_pin_number;			/*addb引脚编号*/
	
} DRV_MAX4052AESE_TYPE;

/* 接口函数
 ********************************************************/

/* 初始化MAX4052AESE模块
  -----------------------------
  入口：MAX4052AESE模块的ID号，引脚端口
  返回值：初始化好的MAX4052AESE模块结构体
*/
extern DRV_MAX4052AESE_TYPE* Max4052aeseInit(DRV_MAX4052AESE_ENUM id, \
											BSP_PORT_ENUM adda_port_number, BSP_PIN_ENUM adda_pin_number, \
											BSP_PORT_ENUM addb_port_number, BSP_PIN_ENUM addb_pin_number);

/* MAX4052AESE模块选择通道
  -----------------------------
  入口：MAX4052AESE模块的ID号，通道号
  返回值：true 成功，flase 失败
*/
extern bool Max4052aeseChoose(DRV_MAX4052AESE_TYPE* p_unit, uint8_t choose);

#endif
