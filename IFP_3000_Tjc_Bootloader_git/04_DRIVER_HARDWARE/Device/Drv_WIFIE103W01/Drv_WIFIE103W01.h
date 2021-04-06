#ifndef _Drv_WIFIE103W01_H_
#define _Drv_WIFIE103W01_H_ 

#include "Func_IFP_300_Drv.h"

#define WIFI_USART_NUM  (_USART2_)

#define TCP_TYPE                 (1)

#define TRANSFER_AP_STATION	     (1)
#define TRANSFER_EXIT_STATION	 (0)

#define WIFI_TRANSFER_ENTER	     (0)
#define WIFI_TRANSFER_EXIT       (1)

#define ENTER_TRANSPARENT        (1)
#define EXIT_TRANSPARENT         (0)

#define WIFI_RSSI        (1)
#define WIFI_MASK        (2)

#define WIFI_STATION_MODE        (1) 

#define WIFI_SLEEP_CHECK       (1) 
#define WIFI_SLEEP_LIGHT       (1)

#define WIFI_CONNEST_DISLINE       (0)
#define WIFI_CONNEST_ONLINE        (1)

#define TJC_FILE_DOWNLOAD_OFF       (0)
#define TJC_FILE_DOWNLOAD_ON        (1)

#define WIFI_W01_E03_OFF       (0)
#define WIFI_W01_E03_ON        (1)

#define WIFI_AP_MAX              (8)
#define WIFI_SSID_NAME_MAX       (20)

#define WAIT_SEM_TIME           (250)
#define WAIT_SEM_1_TIME         (3000)//(2500)
#define WAIT_SEM_2_TIME         (5000)
#define WAIT_SEM_3_TIME         (5000)
#define WAIT_SEM_4_TIME         (100)
#define WAIT_SEM_5_TIME         (300)
#define WAIT_SEM_6_TIME         (1000)
#define WAIT_SEM_7_TIME         (0)

#define WAIT_BLUE_ATE_ON        (1)
#define WAIT_BLUE_ATE_OFF       (0)

//void vClearWifiBlueBuffer( void );
//void vCopyWifiBlueBuffer( uint8_t* uTempWifiBuffer );
void vClearWifiBuffer( void );
void vCopyWifiBuffer( uint8_t* uTempWifiBuffer );
uint8_t uReportWifiSemErr( uint16_t uTime,uint8_t *uErrStr );
uint8_t uWifiUartSet( uint8_t uBauds,uint8_t uDatabit,uint8_t uStop );
uint8_t uWifiEnterMode( uint8_t uMode );
uint8_t uWifiNetInfo( void );
uint8_t uWifiReadIP( void );
uint8_t uWifiAskMode( void );
uint8_t uWifiCloseReDis( uint8_t uOnOff );
uint8_t uWifiReset( void );
uint8_t uWifiResetInit( void );
uint8_t uWifiGetVersion( void );
uint8_t uWifiSleep( uint8_t uCheck,uint8_t uMode );
uint8_t uWifiConnectRoute( uint8_t* upName,uint8_t* upPassword );
uint8_t uWifiConnectStart( uint8_t uType,uint8_t* upIP,uint8_t* upPort );
uint8_t uWifiConnectSavetRanStart( uint8_t uType,uint8_t* upIP,uint8_t* upPort );
uint8_t uWifiScanAP( void );
uint8_t uWifiCwApQuit( void );
uint8_t uWifiRFTxPower( uint8_t uCheck,uint8_t uValue );
uint8_t uWifiRFTxVdd( uint8_t uCheck,uint16_t uValue );
uint8_t uWifiACwlaPort( uint8_t uRssi,uint8_t uMask );
uint8_t uWifiStationSendData( uint8_t* upData,uint8_t uLen );
uint8_t uWifiTransparentSendData( uint8_t* upData );
uint8_t uWifiStationTransfer( uint8_t uOpenClose,uint8_t uTransparent );
uint8_t uWifiPing( uint8_t* pIpAddr );
uint8_t uEnterTransparent( void );
uint8_t uWifiStationDeafulTransfer( uint8_t uOpenClose );  /* 设置为开机进入透明传输或关闭透明传输 */
uint8_t uWifiTransparentSendDataChar( uint8_t upData );
uint8_t uWifiTransparentSendOriginalData( uint8_t* upData,uint32_t uLen );
uint8_t uWifiStationSendDataChar( uint8_t upData );
uint8_t uWifiStationSendOriginalData( uint8_t* upData,uint8_t uLen );
uint8_t uWifiStationNullOrder( void );
uint8_t uReportWifiSem( uint16_t uTime );
uint8_t uWifiStationSendLen( uint32_t uLen );
uint8_t uWifiStationSendDatas( uint8_t* upData,uint32_t uLen );

#endif
