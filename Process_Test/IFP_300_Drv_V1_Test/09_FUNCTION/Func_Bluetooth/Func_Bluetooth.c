#include "Func_Bluetooth.h"

uint8_t uClassicBluetoothInit( void )
{
	uBluetoothGetMode();
	uBluetoothGetBleMode();
	uBluetoothGetMode();		
	uBluetoothSetInitMode( CLASSIC_BLUETOOTH );	
	uBluetoothSetScanMode( BOTH_DISCOVER_CONNECT );
	uBluetoothSetSppInit( CLASSIC_BLUETOOTH_SLAVE );
	
	return EXE_SUCCEED;
}

uint8_t uClassicBluetoothScan( void )
{
	OS_ERR err = OS_ERR_NONE;
	uint8_t uErr = 0;
	
	OSTimeDlyHMSM(0, 0, 0, 120,OS_OPT_TIME_HMSM_STRICT,&err);	
	uTjc4832tTouchEnable( TJC_TOUCH_OFF );                                       /* 整页关闭触摸 */ 
	
	uTjc4832tSetLableValue( TJC_SPITEST_PAGE,SPI_TEST_DIS_CON_ID,(uint8_t *)"Bluetooth Scanning" );
	
	uErr = uBluetoothScanDis( 4,4 );
	if( uErr!=EXE_SUCCEED ){	
		uErr = uWifiReset();                                                     /* 复位 */
		uTjc4832tSetLableValue( TJC_SPITEST_PAGE,SPI_TEST_DIS_CON_ID,(uint8_t *)"Null" );  
	}
	
	uTjc4832tTouchEnable( TJC_TOUCH_ON );                                        /* 整页打开触摸 */
	
	return uErr;
}

uint8_t uTjcDiaplayBluePrompt( uint8_t *upStr )
{
	uint8_t i = 0;
	
	for( i=0;i<WIFI_AP_MAX;i++ ){
		uTjc4832tSetButterValue( TJC_BLUETOOTH_PAGE,WIFI_BUTTER_ID_1NUM*i,(uint8_t *)upStr );
	}
	
	return EXE_SUCCEED;	
}

/* WIFI SSID账号不能超过20位最多显示八个账号 */
uint8_t uBlueAPSsid( uint8_t* upStr )
{
	uint8_t *puTempArr = NULL;
	uint8_t i = 0;
	uint8_t uSsidName[WIFI_AP_MAX][WIFI_SSID_NAME_MAX] = { 0 };
	uint8_t uTempBuf[256] = {0};
	char* puIndex = 0;
	uint32_t uRecNameLen = 0;
	uint8_t uErr = EXE_SUCCEED;
	
	memset( g_MacAddr,0,WIFI_AP_MAX*WIFI_SSID_NAME_MAX );
	
	puTempArr = calloc( 256,sizeof(uint8_t) );             /* 申请内存 */
	if( NULL==puTempArr ){
		return EXE_FAILED;
	}	
	
	puTempArr = (uint8_t *)strtok( (char *)upStr,(const char *)"\r\n" );

	while(puTempArr){  
		memset( (char *)uTempBuf,0,sizeof(uTempBuf) );
		if( i<WIFI_AP_MAX ){			
			if( ('+'==*(const char *)(puTempArr+0))&&(','==*(const char *)(puTempArr+30))&& 		\
				(','!=*(const char *)(puTempArr+31)) ){
				if( strlen((const char *)(puTempArr+31))<sizeof(uTempBuf) ){
					
					memcpy( uTempBuf,(const char *)(puTempArr+31),strlen((const char *)(puTempArr+31)) );
					puIndex = strchr( (const char *)uTempBuf,',' );
					uRecNameLen = puIndex -(const char *)(uTempBuf);					

					if( EXE_SUCCEED==uSearchBlueName( uTempBuf,uSsidName ) ){
						if( (uRecNameLen>=1)&&(uRecNameLen<WIFI_SSID_NAME_MAX) ){
							memcpy( (char *)(&uSsidName[i][0]),(const char *)(uTempBuf),uRecNameLen );
							memcpy( (char *)(&g_MacAddr[i][0]),(const char *)(puTempArr+13),17 );
							i++;
						}					
					}
				}				
			}	
		}	
		
		puTempArr = (uint8_t *)strtok(NULL, (const char *)"\r\n"); 
	}	
	
	if( i>=1 ){
		uTjcDiaplayBlueName( uSsidName );/* 显示ssid用户名 */
	}else{
		uErr = EXE_FAILED;
	}
	
	if( NULL!=puTempArr ){        /* 释放内存 */
		free( puTempArr );
	}	
	
	return uErr;
}	

uint8_t uTjcDiaplayBlueName( uint8_t (*upSsidName)[STR_NAME_MAX] )
{
	uint8_t i = 0;
	uint8_t (*puTempSsidName)[STR_NAME_MAX] = upSsidName;
	
	uint8_t uArrTest[128] = {0};	

	uTjc4832tSetLableValue( TJC_SPITEST_PAGE,SPI_TEST_DIS_CON_ID,(uint8_t *)"" );	
	
//	uConfirmPage( TJC_WIFI_SSID_PAGE );	
	sprintf( (char *)uArrTest,"%s%s","Buletooth:",*(puTempSsidName) );

	uTjc4832tSetLableValue( TJC_SPITEST_PAGE,SPI_TEST_DIS_CON_ID,uArrTest );

	
#if DEBUH_UART1	
	puTempSsidName = upSsidName;
	myprintf( "BlueScanAP:\r\n" );
	for( i=0;i<WIFI_AP_MAX;i++ ){
		myprintf( " %s\r\n",*(puTempSsidName++) );
	}
#endif
	
	return EXE_SUCCEED;	
}

uint8_t uSearchBlueName( uint8_t* uBlueName,uint8_t (*upSsidName)[STR_NAME_MAX] )
{
	uint8_t i = 0;
	
	while( 0!=(**(upSsidName+i)) ){
		if( NULL==strstr((const char *)uBlueName,(const char *)(*(upSsidName+i))) ){

		}else{
			return  EXE_FAILED;
		}
		i++;
	};	
	
	return EXE_SUCCEED;
}

uint8_t uBluetoothMacAddrConnet(  uint8_t* upMacaddr )
{
	uint8_t uErr = 0;
	
	if( strlen((const char *)upMacaddr)<18 ){        /* mac==17 */
		uErr = uBluetoothConnet( (uint8_t *)upMacaddr,strlen((const char *)upMacaddr) );
		if( EXE_SUCCEED==uErr ){
			uTjc4832tSetPage( TJC_SET_PAGE );                                                                  /* 设置为 */
			return uErr;
		}else{
			return uErr;
		}
	}	
	
#if DEBUH_UART1	
	myprintf( "BlueMac:%s\r\n",upMacaddr );
#endif
	
	return EXE_FAILED;
}

///* 扫描WIFI */
//uint8_t uWifiScanAll( void )
//{
//	OS_ERR err = OS_ERR_NONE;
//	uint8_t uErr = 0;
//	
//	
//	OSTimeDlyHMSM(0, 0, 0, 120,OS_OPT_TIME_HMSM_STRICT,&err);	
//	uTjc4832tTouchEnable( TJC_TOUCH_OFF );                                       /* 整页关闭触摸 */ 
//	
//	uTjcDiaplayWifiPrompt( (uint8_t *)"Scanning" );     
//	
//	if( WIFI_OFF==gp_stuConfigFile->uWifiOnOff ){
//		gp_stuConfigFile->uWifiOnOff = WIFI_ON;
//		uWifiOpenClose( WIFI_W01_E103_ON );                                      /* 打开WIFI */
//		OSTimeDlyHMSM(0, 0, 3, 0,OS_OPT_TIME_HMSM_STRICT,&err);                  /* 等待Wifi启动 */	
//	}
//	
//	uWifiTransfer( WIFI_TRANSFER_EXIT );                                         /* 退出透彻模式并进入普通模式 CIPMODE */
//	uWifiEnterMode( WIFI_STATION_MODE );                                         /* 进入sta模式 CWMODE */
//	
//	uErr += uWifiCloseReDis( WAIT_BLUE_ATE_OFF );                                /* 回显 */
//	uErr += uWifiACwlaPort( WIFI_RSSI,WIFI_MASK );                               /* 热点名按信号强度排列 */
//																               
//	uErr += uWifiScanAP();                                                       /* 扫描WIFI热点 */  
//	if( EXE_SUCCEED!=uErr ){   
//		uWifiResetInit();                                                        /* 恢复出厂设置 */		
//		uErr = uWifiReset();                                                     /* 复位 */
//		uTjcDiaplayWifiPrompt( (uint8_t *)"Null" );  
//	}
//	
//	uTjc4832tTouchEnable( TJC_TOUCH_ON );                                        /* 整页打开触摸 */
//	
//	return uErr;
//}

uint8_t uClassicBluetoothConnet( void )
{
	uBluetoothConnet( (uint8_t *)"dc:1d:30:61:f8:fb",strlen( (const char *)"dc:1d:30:61:f8:fb" ) );
	
	return EXE_SUCCEED;
}

uint8_t uTjcDiaplayBluetoothPrompt( uint8_t *upStr )
{
	uint8_t i = 0;
	
	for( i=0;i<WIFI_AP_MAX;i++ ){
		uTjc4832tSetButterValue( TJC_BLUETOOTH_PAGE,WIFI_BUTTER_ID_1NUM*i,(uint8_t *)upStr );
	}
	
	return EXE_SUCCEED;	
}
