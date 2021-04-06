#ifndef _FUNC_BLUETOOTH_H_
#define _FUNC_BLUETOOTH_H_

#include "Func_IFP_300_Drv.h"

#define ERROR_BLUR_INVALID  "Bluetooth Invalid"

uint8_t uClassicBluetoothInit( void );
uint8_t uClassicBluetoothScan( void );
uint8_t uTjcDiaplayBluePrompt( uint8_t *upStr );
uint8_t uBlueAPSsid( uint8_t* upStr );
uint8_t uTjcDiaplayBlueName( uint8_t (*upSsidName)[20] );
uint8_t uBluetoothMacAddrConnet( uint8_t* upMacaddr );
uint8_t uSearchBlueName( uint8_t* uBlueName,uint8_t (*upSsidName)[20] );
uint8_t uTjcDiaplayBluetoothPrompt( uint8_t *upStr );
uint8_t uBluetoothError( uint8_t* pArrErr );

#endif
	
