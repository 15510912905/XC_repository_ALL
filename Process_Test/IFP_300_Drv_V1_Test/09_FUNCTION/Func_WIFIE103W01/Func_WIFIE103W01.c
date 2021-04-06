#include "Func_WIFIE103W01.h"
#include "Global_Variable.h"

uint8_t uWifiInit( void )
{
	uint8_t uTempErr = 0;
	
	uTempErr += uWifiTransfer( WIFI_TRANSFER_EXIT );			                                                    /* 退出透彻收数据 退出透彻模式并进入普通模式 */
	uWifiCloseReDis( WAIT_BLUE_ATE_OFF );                                                                           /* 回显 */
//	if( EXE_FAILED==uWifiPing( (uint8_t *)WIFI_SERVER_ADDR ) ){
//		g_uWifiConnect = WIFI_CONNEST_DISLINE;
//		uTempErr += uWifiReset();                                                                                   /* 复位 */
//	}else{
//		uTempErr += uWifiTransfer( WIFI_TRANSFER_ENTER );          		                                            /* 进入透传模式 */
//		if( EXE_SUCCEED==uTempErr ){
//			g_uWifiConnect = WIFI_CONNEST_ONLINE;
//		}
//	}
	
#if DEBUH_UART1	
	if( EXE_SUCCEED!=uTempErr ){
		myprintf( "WifiInit:%d \r\n",uTempErr );
	}
#endif
	
	return uTempErr;
}

/* 配置WIFI */  
uint8_t uWifiConfig( void )
{
//	OS_ERR err;
	uint8_t uRecError = 0;
	
	uTjc4832tSetPage( TJC_WARN_PAGE );                                                                     /* 设置为强制警告页 */
	uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Waiting" );	                           /* 等待效验WIFI数据 */
	uTjc4832tTouchEnable( TJC_TOUCH_OFF );                                                                 /* 整页关闭触摸 */ 
																					                       
//	uWifiResetInit();                                                                                      /* 恢复出厂设置 */
//	OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);                                                /* 等待Wifi启动 */
																					                       
	/* 作为station模式 */                                                                                  
	uRecError = uWifiGetVersion();                                                                         /* 获取版本 */	
	uRecError += uWifiEnterMode( WIFI_STATION_MODE );                                                      /* 进入sta模式 */
	
	uRecError += uWifiConnectRoute( (uint8_t *)g_uWifiSsidName,(uint8_t *)g_uWifiNamePas );                /* 设置Wifi路由 */
//	uWifiConnectRoute( (uint8_t *)"TP-LINK_799608",(uint8_t *)"12345678" );                                /* 设置Wifi路由 */
	
	uRecError += uWifiReadIP();                                                                            /* 读IP地址 */

	uRecError += uWifiConnectSavetRanStart( TCP_TYPE,(uint8_t *)WIFI_SERVER_ADDR,(uint8_t *)"5150" );      /* 开机透传服务器IP地址和端口号 */
//	uRecError += uWifiConnectSavetRanStart( TCP_TYPE,(uint8_t *)"192.168.124.6",(uint8_t *)"6000" );       /* 开机透传服务器IP地址和端口号 */	
//	uWifiConnectStart( TCP_TYPE,(uint8_t *)"192.168.1.101",(uint8_t *)"6000" );                            /* 服务器IP地址和端口号 */
	uRecError += uWifiPing( (uint8_t *)WIFI_SERVER_ADDR );                                                 /* 测试IP */	
																		                                           
//	uWifiAskMode();                                                                                        /* 模式查询 */
		
	uTjc4832tSetLableValue( TJC_WIFI_PAS_PAGE,WIFI_BUTTER_PAS_ID_0NUM,(uint8_t *)"" );		
	if( EXE_SUCCEED==uRecError ){
//		uRecError += uWifiTransfer( WIFI_TRANSFER_ENTER );          		                               /* 进入透传模式 */
		if( EXE_SUCCEED==uRecError ){
			g_uWifiConnect = WIFI_CONNEST_ONLINE;
		}
		uTjc4832tSetPage( TJC_SET_PAGE );                                                                  /* 设置为 */
	}else{    
		g_uWifiConnect = WIFI_CONNEST_DISLINE;
		uRecError += uWifiReset();                                                                         /* 复位 */
		
		uTjc4832tSetPage( TJC_WARN_PAGE );                                                                 /* 设置为强制警告页 */
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"WIFI Invalid" );	                   /* 无效的WIFI数据 */
	}
	uTjc4832tTouchEnable( TJC_TOUCH_ON );                                                                  /* 整页打开触摸 */
		
	return uRecError;
}

/* 配置WIFI */  
uint8_t uWifiConfigSSID( void )
{
//	OS_ERR err;
	uint8_t uRecError = 0;
	
	uTjc4832tSetPage( TJC_WARN_PAGE );                                                                     /* 设置为强制警告页 */
	uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Waiting" );	                           /* 等待效验WIFI数据 */
	uTjc4832tTouchEnable( TJC_TOUCH_OFF );                                                                 /* 整页关闭触摸 */ 
																					                       
//	uWifiResetInit();                                                                                      /* 恢复出厂设置 */
//	OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);                                                /* 等待Wifi启动 */
																					                       
	/* 作为station模式 */                                                                                  
	uRecError = uWifiGetVersion();                                                                         /* 获取版本 */	
	uRecError += uWifiEnterMode( WIFI_STATION_MODE );                                                      /* 进入sta模式 */
	
	uRecError += uWifiConnectRoute( (uint8_t *)g_uWifiSsidName,(uint8_t *)g_uWifiNamePas );                /* 设置Wifi路由 */
//	uWifiConnectRoute( (uint8_t *)"TP-LINK_799608",(uint8_t *)"12345678" );                                /* 设置Wifi路由 */
	
	uRecError += uWifiReadIP();                                                                            /* 读IP地址 */	
																		                                           
//	uWifiAskMode();                                                                                        /* 模式查询 */
		
	uTjc4832tSetLableValue( TJC_WIFI_PAS_PAGE,WIFI_BUTTER_PAS_ID_0NUM,(uint8_t *)"" );		
	if( EXE_SUCCEED==uRecError ){
		uTjc4832tSetPage( TJC_SET_PAGE );                                                                  /* 设置为 */
	}else{    
		g_uWifiConnect = WIFI_CONNEST_DISLINE;
		uRecError += uWifiReset();                                                                         /* 复位 */
		
		uTjc4832tSetPage( TJC_WARN_PAGE );                                                                 /* 设置为强制警告页 */
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"WIFI Invalid" );	                   /* 无效的WIFI数据 */
	}
	uTjc4832tTouchEnable( TJC_TOUCH_ON );                                                                  /* 整页打开触摸 */
		
	return uRecError;
}

uint8_t uWifiConfigServer( void )
{
	uWifiConfigServerIPPort( g_ServerIPAddr,g_ServerPort );                                                          /* 配置服务器 */
	
	uTjc4832tSetLableValue( TJC_SERVER_CONF_PAGE,SERVER_IP_ID_NUM,(uint8_t *)"" );	                                 /* 无效的WIFI数据 */
	uTjc4832tSetLableValue( TJC_SERVER_CONF_PAGE,SERVER_PORT_ID_NUM,(uint8_t *)"" );	                                 /* 无效的WIFI数据 */
	
	return EXE_SUCCEED;
}

/* 配置WIFI */  
uint8_t uWifiConfigServerIPPort( uint8_t* puServerAddr, uint8_t* puPort  )
{
//	OS_ERR err;
	uint8_t uRecError = 0;
	
	uTjc4832tSetPage( TJC_WARN_PAGE );                                                                     /* 设置为强制警告页 */
	uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Waiting" );	                           /* 等待效验WIFI数据 */
	uTjc4832tTouchEnable( TJC_TOUCH_OFF );                                                                 /* 整页关闭触摸 */ 
																					                       
//	uWifiResetInit();                                                                                      /* 恢复出厂设置 */
//	OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);                                                /* 等待Wifi启动 */

	uRecError += uWifiConnectStart( TCP_TYPE,(uint8_t *)puServerAddr,(uint8_t *)puPort );          /* 开机透传服务器IP地址和端口号 */
//	uRecError += uWifiConnectStart( TCP_TYPE,(uint8_t *)"192.168.124.6",(uint8_t *)"6000" );       /* 开机透传服务器IP地址和端口号 */	
//	uWifiConnectStart( TCP_TYPE,(uint8_t *)"192.168.1.101",(uint8_t *)"6000" );                            /* 服务器IP地址和端口号 */
	uRecError += uWifiPing( (uint8_t *)puServerAddr );                                                     /* 测试IP */	
																		                                           
//	uWifiAskMode();                                                                                        /* 模式查询 */
		
	uTjc4832tSetLableValue( TJC_WIFI_PAS_PAGE,WIFI_BUTTER_PAS_ID_0NUM,(uint8_t *)"" );		
	if( EXE_SUCCEED==uRecError ){
//		uRecError += uWifiTransfer( WIFI_TRANSFER_ENTER );          		                               /* 进入透传模式 */
		if( EXE_SUCCEED==uRecError ){
			g_uWifiConnect = WIFI_CONNEST_ONLINE;
		}	
//		uWifiPowerInit( 1 );                                                                               /* 重启一下电源 */
		uTjc4832tSetPage( TJC_SET_PAGE );                                                                  /* 设置为 */
	}else{    
		g_uWifiConnect = WIFI_CONNEST_DISLINE;
		uRecError += uWifiReset();                                                                         /* 复位 */
		
		uTjc4832tSetPage( TJC_WARN_PAGE );                                                                 /* 设置为强制警告页 */
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"WIFI Invalid" );	                   /* 无效的WIFI数据 */
	}
	uTjc4832tTouchEnable( TJC_TOUCH_ON );                                                                  /* 整页打开触摸 */
		
	return uRecError;
}

/* 扫描WIFI */
uint8_t uWifiScanAll( void )
{
	OS_ERR err = OS_ERR_NONE;
	uint8_t uErr = 0;
	
	
	OSTimeDlyHMSM(0, 0, 0, 120,OS_OPT_TIME_HMSM_STRICT,&err);	
	uTjc4832tTouchEnable( TJC_TOUCH_OFF );                                       /* 整页关闭触摸 */ 
	
	uTjc4832tSetLableValue( TJC_SPITEST_PAGE,SPI_TEST_DIS_CON_ID,(uint8_t *)"Wifi Scanning" );     
	
	if( WIFI_OFF==gp_stuConfigFile->uWifiOnOff ){
		gp_stuConfigFile->uWifiOnOff = WIFI_ON;
		uWifiOpenClose( WIFI_W01_E103_ON );                                      /* 打开WIFI */
		OSTimeDlyHMSM(0, 0, 3, 0,OS_OPT_TIME_HMSM_STRICT,&err);                  /* 等待Wifi启动 */	
	}
	
	uWifiTransfer( WIFI_TRANSFER_EXIT );                                         /* 退出透彻模式并进入普通模式 CIPMODE */
	uWifiEnterMode( WIFI_STATION_MODE );                                         /* 进入sta模式 CWMODE */
	
	uErr += uWifiCloseReDis( WAIT_BLUE_ATE_OFF );                                /* 回显 */
	uErr += uWifiACwlaPort( WIFI_RSSI,WIFI_MASK );                               /* 热点名按信号强度排列 */
																               
	uErr += uWifiScanAP();                                                       /* 扫描WIFI热点 */  
	if( EXE_SUCCEED!=uErr ){   
		uWifiResetInit();                                                        /* 恢复出厂设置 */		
		uErr = uWifiReset();                                                     /* 复位 */
		uTjc4832tSetLableValue( TJC_SPITEST_PAGE,SPI_TEST_DIS_CON_ID,(uint8_t *)"Null" );  
	}
	
	uTjc4832tTouchEnable( TJC_TOUCH_ON );                                        /* 整页打开触摸 */
	
	return uErr;
}

/* 打开WIFI */
uint8_t uWifiOpenClose( uint8_t uOnOff )
{
	uint8_t uTempErr = 0;
	
	if( uOnOff==WIFI_W01_E103_ON ){	
		WIFI_RST_OUT = WIFI_RST_TRUE;                                                /* 默认配置 WIFI开启	*/
		
	}else{
		uTempErr += uWifiTransparentReceive( TRANSFER_EXIT_STATION );			     /* 退出透彻收数据 */
		
		WIFI_RST_OUT = WIFI_RST_FALSE;                                               /* 默认配置 WIFI关闭	*/
	}
	
#if DEBUH_UART1	
	if( EXE_SUCCEED!=uTempErr ){
		myprintf( "WifiOpenClose:%d \r\n",uTempErr );
	}
#endif
	
	return uTempErr;
}

uint8_t uTjcDiaplaySsidName( uint8_t (*upSsidName)[STR_NAME_MAX] )
{
	uint8_t i = 0;
	uint8_t (*puTempSsidName)[STR_NAME_MAX] = upSsidName;
	
	uint8_t uArrTest[128] = {0};
	
	uTjc4832tSetLableValue( TJC_SPITEST_PAGE,SPI_TEST_DIS_CON_ID,(uint8_t *)"" );	
	
//	uConfirmPage( TJC_WIFI_SSID_PAGE );
	
	sprintf( (char *)uArrTest,"%s%s","Wifi:",*(puTempSsidName) );
	uTjc4832tSetLableValue( TJC_SPITEST_PAGE,SPI_TEST_DIS_CON_ID,uArrTest );

	
#if DEBUH_UART1	
	puTempSsidName = upSsidName;
	myprintf( "ScanAP:\r\n" );
	for( i=0;i<WIFI_AP_MAX;i++ ){
		myprintf( " %s\r\n",*(puTempSsidName++) );
	}
#endif
	
	return EXE_SUCCEED;	
}

uint8_t uTjcDiaplayWifiPrompt( uint8_t *upStr )
{
	uint8_t i = 0;
	
	for( i=0;i<WIFI_AP_MAX;i++ ){
		uTjc4832tSetButterValue( TJC_WIFI_SSID_PAGE,WIFI_BUTTER_ID_1NUM*i,(uint8_t *)upStr );
	}
	
	return EXE_SUCCEED;	
}

/* WIFI SSID账号不能超过20位最多显示八个账号 */
uint8_t uWifiAPSsid( uint8_t* upStr )
{
	uint8_t uRecLenTemp = 0;
	uint8_t *puTempArr = NULL;
	uint8_t i = 0;
	uint8_t uSsidName[WIFI_AP_MAX][WIFI_SSID_NAME_MAX] = { 0 };
	uint8_t uTempBuf[WIFI_SSID_NAME_MAX] = {0};
	uint8_t uErr = EXE_SUCCEED;

	puTempArr = calloc( WIFI_SSID_NAME_MAX,sizeof(uint8_t) );             /* 申请内存 */
	if( NULL==puTempArr ){
		return EXE_FAILED;
	}	
	
	puTempArr = (uint8_t *)strtok( (char *)upStr,(const char *)"\r\n" );

	while(puTempArr){  
		memset( (char *)uTempBuf,0,sizeof(uTempBuf) );
		sscanf( (const char *)puTempArr, "%*[^(](%[^)]",uTempBuf );       /* 只要括号直接的数据 */
		uRecLenTemp = strlen( (const char *)uTempBuf );
		
		if( (uRecLenTemp>=1)&&(uRecLenTemp<WIFI_SSID_NAME_MAX)&&(i<WIFI_AP_MAX) ){
			memcpy( (char *)(&uSsidName[i][0]),(const char *)(uTempBuf+1),(uRecLenTemp-2) );
			i++;
		}	
		
		puTempArr = (uint8_t *)strtok(NULL, (const char *)"\r\n"); 
	}	
	
	if( i>=1 ){
		uErr = uTjcDiaplaySsidName( uSsidName );/* 显示ssid用户名 */
	}
	
	if( NULL!=puTempArr ){        /* 释放内存 */
		free( puTempArr );
	}	
	
	return uErr;
}	

uint8_t uWifiTransparentReceive( uint8_t uEnterExit )
{
//	OS_ERR err;
	
	if( TRANSFER_AP_STATION==uEnterExit ){
		g_uTransparentStatus = TRANSFER_AP_STATION;
		vClearWifiBuffer();                                                        /* 清空缓存 */
	}else{
		g_uTransparentStatus = TRANSFER_EXIT_STATION;	
//		OSTimeDlyHMSM(0, 0, 0, 600,OS_OPT_TIME_HMSM_STRICT,&err);			
	}
	
	return EXE_SUCCEED;
}

uint8_t uWifiTransparentMode( uint8_t uEnterExit )
{	
	OS_ERR err;
	uint8_t uRecError = 0;
	
	if( TRANSFER_AP_STATION==uEnterExit ){
		uRecError += uWifiStationTransfer( TRANSFER_AP_STATION,ENTER_TRANSPARENT );         /* 设置为透彻模式 */
		uRecError += uEnterTransparent();	                                                /* 进入透彻模式 */   
	}else{        
		OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_STRICT,&err);                              /* 这个延时最好保留 */	
		uRecError += uWifiStationTransfer( TRANSFER_EXIT_STATION,EXIT_TRANSPARENT );        /* 间隔100ms没有数据发送时 退出指令才能生效 退出透传模式 */ 
		OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_STRICT,&err);                              /* 这个延时最好保留 */	
		uWifiStationNullOrder();
		uRecError += uWifiStationTransfer( TRANSFER_AP_STATION,EXIT_TRANSPARENT );          /* 设置为普通模式 AT+CIPMODE=0 退出透传模式 */
		if( EXE_SUCCEED!=uRecError ){
			WIFI_RST_OUT = WIFI_RST_FALSE;                                                  /* 默认配置 WIFI关闭	*/
			OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err);                            /* 这个延时最好保留 */	
			WIFI_RST_OUT = WIFI_RST_TRUE;                                                   /* 默认配置 WIFI开启	*/
			OSTimeDlyHMSM(0,0,3,0,OS_OPT_TIME_HMSM_STRICT,&err);                            /* 这个延时最好保留 */
			uRecError = uWifiStationTransfer( TRANSFER_EXIT_STATION,EXIT_TRANSPARENT );     /* 间隔100ms没有数据发送时 退出指令才能生效 退出透传模式 */ 
			uWifiStationNullOrder();
			OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err);                            /* 这个延时最好保留 */	
			uRecError += uWifiStationTransfer( TRANSFER_AP_STATION,EXIT_TRANSPARENT );      /* 设置为普通模式 AT+CIPMODE=0 退出透传模式 */
		}
	}
	
	return uRecError;
}

uint8_t uWifiUploaTheHistoryData( void )
{	
	static int16_t l_iRecUploaData = 0;	
	GYK950E* pHistoryMyForm = NULL;

	if( WIFI_CONNEST_ONLINE==g_uWifiConnect ){
		if( l_iRecUploaData<(g_projectSerial.history_count-1) ){
			pHistoryMyForm = calloc( 1,sizeof(GYK950E) );
			if( NULL==pHistoryMyForm ){
				return EXE_FAILED;
			}	
			
			if( (0==l_iRecUploaData) ){ 
				SPI_Flash_Read( (uint8_t *)pHistoryMyForm,(SPIFLASH_DENSITY_BASE_ADDR+((g_projectSerial.history_count-1)*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );
				l_iRecUploaData = (g_projectSerial.history_count-1);
			}else{	
				l_iRecUploaData++;
				SPI_Flash_Read( (uint8_t *)pHistoryMyForm,(SPIFLASH_DENSITY_BASE_ADDR+(l_iRecUploaData*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );
			}			
			uWifiTransparentSendData( (uint8_t *)"WIFIHistoryData:" );                          /* 发送数据 */			
			uWifiTransparentSendData( (uint8_t *)pHistoryMyForm->uGyk_printname );              /* 发送数据 */
			uWifiTransparentSendData( (uint8_t *)pHistoryMyForm->uGyk_serialnumber );           /* 发送数据 */
			uWifiTransparentSendData( (uint8_t *)pHistoryMyForm->uGyk_report );			
			uWifiTransparentSendData( (uint8_t *)pHistoryMyForm->uGyk_densityresult );          /* 发送数据 */
			uWifiTransparentSendData( (uint8_t *)pHistoryMyForm->uGyk_barcode );
			uWifiTransparentSendData( (uint8_t *)pHistoryMyForm->uGyk_reference );              /* 发送数据 */
			uWifiTransparentSendData( (uint8_t *)pHistoryMyForm->uGyk_testtime );
			uWifiTransparentSendData( (uint8_t *)pHistoryMyForm->uGyk_printtime );              /* 发送数据 */
			uWifiTransparentSendData( (uint8_t *)pHistoryMyForm->uGyk_printunit );		
			uWifiTransparentSendData( (uint8_t *)pHistoryMyForm->uGyk_usersex );
			uWifiTransparentSendData( (uint8_t *)pHistoryMyForm->uGyk_userage );
			
			uWifiTransparentSendData( (uint8_t *)pHistoryMyForm->uGyk_username );               /* 发送数据 */
			uWifiTransparentSendData( (uint8_t *)pHistoryMyForm->uGyk_samplenumber );
			
			if( NULL!=pHistoryMyForm ){
				free( pHistoryMyForm );
			}
			
			return EXE_SUCCEED;
		}
	}
	
	return EXE_FAILED;
}

uint8_t uWifiConnentEnv( void )
{
	uint8_t uTempErr = 0;
	
	if( WIFI_ON==gp_stuConfigFile->uWifiOnOff ){		
		uTempErr += uWifiInit();                                                                    /* 初始化 */
	}
	
	return uTempErr;
}

uint8_t uWifiTransfer( uint8_t uEnterExit )
{
	uint8_t uTempErr = 0;

	if( uEnterExit ){
		uTempErr += uWifiTransparentReceive( TRANSFER_EXIT_STATION );			     /* 退出透彻收数据 */
		uTempErr += uWifiTransparentMode( TRANSFER_EXIT_STATION );                   /* 退出透彻模式并进入普通模式 */
#if DEBUH_UART1	
	#if	PRIVATE_WIFIDUG_UART1
		myprintf( "WifiExit:%d \r\n",uTempErr );	
	#endif
#endif
	}else{
		uTempErr += uWifiTransparentMode( TRANSFER_AP_STATION );		             /* 进入透传模式 */
		uTempErr += uWifiTransparentReceive( TRANSFER_AP_STATION );			         /* 进入透彻收数据 */
#if DEBUH_UART1	
	#if PRIVATE_WIFIDUG_UART1
		myprintf( "WifiEnter:%d \r\n",uTempErr );	
	#endif
#endif
	}
	return uTempErr;
}

uint8_t uWifiPowerInit( uint8_t uSecond )
{
	OS_ERR err;
	
	uWifiOpenClose( WIFI_W01_E103_OFF );                /* 关闭WIFI */
	OSTimeDlyHMSM(0, 0, uSecond, 0,OS_OPT_TIME_HMSM_STRICT,&err);  
	uWifiOpenClose( WIFI_W01_E103_ON );                 /* 打开WIFI */
	gp_stuConfigFile->uWifiOnOff = WIFI_ON;
	
	return EXE_SUCCEED;
}
