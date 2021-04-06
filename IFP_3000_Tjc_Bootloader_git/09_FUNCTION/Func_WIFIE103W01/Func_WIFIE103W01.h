#ifndef _Func_WIFIE103W01_H_
#define _Func_WIFIE103W01_H_ 

#include "Func_IFP_300_Drv.h"
#include "Func_Common.h"
#include "Drv_WIFIE103W01.h"

#define STR_NAME_MAX    (20)

#define WIFI_W01_E103_ON     (1)
#define WIFI_W01_E103_OFF    (0)

#define WIFI_SERVER_ADDR     "192.168.1.101"  //"192.168.1.104"//

//开始
uint8_t uWifiInit( void );
uint8_t uWifiConfig( void );
uint8_t uWifiConfigSSID( void );
uint8_t uWifiConfigServer( void );
uint8_t uWifiConfigServerIPPort( uint8_t* puServerAddr, uint8_t* puPort );
uint8_t uWifiScanAll( void );
uint8_t uWifiOpenClose( uint8_t uOnOff );
uint8_t uTjcDiaplaySsidName( uint8_t (*upSsidName)[STR_NAME_MAX] );
uint8_t uTjcDiaplayWifiPrompt( uint8_t *upStr );
uint8_t uWifiAPSsid( uint8_t* upStr );
uint8_t uWifiTransparentReceive( uint8_t uEnterExit );
uint8_t uWifiTransparentMode( uint8_t uEnterExit );
uint8_t uWifiUploaTheHistoryData( void );
uint8_t uWifiConnentEnv( void );
uint8_t uWifiTransfer( uint8_t uEnterExit );
uint8_t uWifiPowerInit( uint8_t uSecond );
bool isVaildIp(const char *ip);

#endif
