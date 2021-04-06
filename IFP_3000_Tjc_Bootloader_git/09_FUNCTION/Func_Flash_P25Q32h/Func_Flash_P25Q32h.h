/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

			嵌入式开发平台——AD7685模数转换模块

  -------------------------------------------------------
   文 件 名   : Func_Flash_P25Q32h.h
   版 本 号   : V1.0.0.0
   作    者   : 
   生成日期   : 
   功能描述   : 
   使用方法   ：
   依赖于     : 
   注         ：该模块不依赖于硬件电路。 
 ********************************************************/
 
#ifndef _FUNC_FLASH_P25Q32H_H_
#define _FUNC_FLASH_P25Q32H_H_

#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"
#include "Drv_SimulateSpi.h"
#include "Drv_Flash_P25Q32h.h"

uint8_t* ReadSPIFlashTou8Arr( uint8_t* u8Arr,uint16_t u16Addr,uint8_t size );




#endif
