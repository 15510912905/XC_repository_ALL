#ifndef _FUNC_TJC_BOOTLOADER_H_
#define _FUNC_TJC_BOOTLOADER_H_ 

#include "Func_IFP_300_Drv.h"

#define UPGARDE_WAIT_TIME          (800)

typedef struct Loader{	
	uint32_t uSectorSize;
	uint32_t uFileSize;
}LOADER;

uint8_t uUart1Parsing( uint16_t* puSize );
uint8_t uUart1DataCopy( uint8_t* puTarget,uint8_t* puSource,uint16_t* puSize );
uint8_t uUart4DataCopy( uint8_t* puTarget,uint8_t* puSource,uint16_t* puSize );
uint8_t uUart1DmaSend( uint8_t* puTarget,uint16_t uSize );
uint8_t uUart4DmaSend( uint8_t* puTarget,uint16_t uSize );
uint8_t uDeclarationspData( uint8_t* puTarget,uint16_t uSize );
uint8_t uUart4UpgardeEngineering( uint32_t uSetor,uint32_t uSize );
uint8_t uUart4UpgardeFile( uint32_t uSetor,uint32_t uSize );

#endif
