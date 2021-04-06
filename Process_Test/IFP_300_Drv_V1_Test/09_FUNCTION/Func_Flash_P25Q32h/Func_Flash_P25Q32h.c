/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

			嵌入式开发平台——AD7685模数转换模块

  -------------------------------------------------------
   文 件 名   : Func_Flash_P25Q32h.c
   版 本 号   : V1.0.0.0
   作    者   : 
   生成日期   : 2020年06月12日
   功能描述   : 
   使用方法   ：
   依赖于     : 
   注         ：该模块不依赖于硬件电路,使用了硬件SPI。 
 ********************************************************/

#include "Func_Flash_P25Q32h.h"

uint8_t* ReadSPIFlashTou8Arr( uint8_t* u8Arr,uint16_t u16Addr,uint8_t size )
{
	uint8_t i=0;

	//SPI_Flash_Init();  		//SPI FLASH 初始化 ;   /* 后续可能不需要再初始化 */
	
	if( SPI_Flash_ReadID()==P25Q32H ){							//检测不到W25Q64		
		for( i=0;i<size;i++ ){
			//u8Arr[i] = SPI_Flash_Read( g_SpiFlashBuf,u16Addr+i,4096 );  
			//At24c32ReadByte( _gp_EEP,u16Addr+i );
		}
		return u8Arr;
	}else{
		return 0;
	}

}
