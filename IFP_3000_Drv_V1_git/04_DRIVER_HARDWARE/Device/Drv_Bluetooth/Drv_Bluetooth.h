#ifndef _Drv_BLUETOOTH_H_
#define _Drv_BLUETOOTH_H_ 

#include "Func_IFP_300_Drv.h"

#define CLASSIC_BLUETOOTH                  (1)
#define BOTH_DISCOVER_CONNECT              (2)
#define CLASSIC_BLUETOOTH_MASTER           (1)
#define CLASSIC_BLUETOOTH_SLAVE            (1)


void vClearBluetoothBuffer( void );
void vCopyBluetoothBuffer( uint8_t* uTempWifiBuffer,uint16_t uSize );
uint8_t uReportBluetoothSemErr( uint16_t uTime,uint8_t *uErrStr );
uint8_t uBluetoothSetBleInitMode( uint8_t uMode );
int8_t uBluetoothGetBleMode( void );
uint8_t uWifiBuleOrder( uint8_t* pOrder );
uint8_t uBluetoothSetInitMode( uint8_t uMode );
int8_t uBluetoothGetMode( void );
uint8_t uBluetoothSetScanMode( uint8_t uMode );
uint8_t uBluetoothScanDis( uint8_t uDuration,uint8_t uResponses );
uint8_t uBluetoothSetSppInit( uint8_t uMasterSlave );
uint8_t uBluetoothConnet( uint8_t* uRemoteAddress,uint32_t uLen );
uint8_t uBluetoothSendData( uint8_t* upData,uint32_t uLen );
uint8_t uBluetoothSendCharData( uint8_t uData );
uint8_t uBluetoothSendOriginalData( uint8_t* upData,uint32_t uLen );
uint8_t uBluetoothTransparentSendData( uint8_t* upData );
uint8_t uBluetoothTransparentSendDataChar( uint8_t upData );
uint8_t uBluetoothTransparentSendOriginalData( uint8_t* upData,uint32_t uLen );
uint8_t uBluetoothSendLen( uint32_t uLen );
uint8_t uBluetoothSendDatas( uint8_t* upData,uint32_t uLen );
uint8_t uBluetoothEncdev( void );

#endif
