#include "Drv_WIFIE103W01.h"
#include "Global_Variable.h"

//void vClearWifiBlueBuffer( void )
//{
//	CPU_SR_ALLOC();                                               /*申请临界区变量*/
//	
//	OS_CRITICAL_ENTER();   		  				                  /* 以下必须考虑临界资源的问题 */
//	memset( g_Usart2_Rx_Buf,0,sizeof(g_Usart2_Rx_Buf) ); 
//	g_Usart2_Rx_Sta = 0;
//	OS_CRITICAL_EXIT();   			                              /* 以上必须考虑临界资源的问题 */	

//	CPU_SR_ALLOC();                                               /*申请临界区变量*/
//	
//	OS_CRITICAL_ENTER();   		  				                  /* 以下必须考虑临界资源的问题 */
//	memset( g_WifiBluetooth,0,sizeof(g_WifiBluetooth) ); 
//	OS_CRITICAL_EXIT();   			                              /* 以上必须考虑临界资源的问题 */	
//}

//void vCopyWifiBlueBuffer( uint8_t* uTempWifiBuffer )
//{
//	uint16_t uUsart2RxStaTemp = 0;
//	CPU_SR_ALLOC();                                               /*申请临界区变量*/
//	
//	OS_CRITICAL_ENTER();   		  				                                                            /* 以下必须考虑临界资源的问题 */
//	uUsart2RxStaTemp = (g_Usart2_Rx_Sta&0X3FFF)+1;		
//	memcpy( (char *)uTempWifiBuffer,(const char *)g_Usart2_Rx_Buf,uUsart2RxStaTemp );                          /* 复制 */				
//	OS_CRITICAL_EXIT();   			                                                                        /* 以上必须考虑临界资源的问题 */

//	uint16_t uUsart2RxStaTemp = 0;
//	CPU_SR_ALLOC();                                               /*申请临界区变量*/
//	
//	OS_CRITICAL_ENTER();   		  				                                                            /* 以下必须考虑临界资源的问题 */		
//	if( strlen((const char *)g_WifiBluetooth)<sizeof(g_WifiBluetooth) ){
//		memcpy( (char *)uTempWifiBuffer,(const char *)g_WifiBluetooth,uUsart2RxStaTemp );                          /* 复制 */		
//	}
//	OS_CRITICAL_EXIT();                                                                                     /* 以上必须考虑临界资源的问题 */	
//}

void vClearWifiBuffer( void )
{
	CPU_SR_ALLOC();                                               /*申请临界区变量*/
	
	OS_CRITICAL_ENTER();   		  				                  /* 以下必须考虑临界资源的问题 */
	memset( g_Usart2_Rx_Buf,0,sizeof(g_Usart2_Rx_Buf) ); 
	g_Usart2_Rx_Sta = 0;
	OS_CRITICAL_EXIT(); 	
}

void vCopyWifiBuffer( uint8_t* uTempWifiBuffer )
{
	uint16_t uUsart2RxStaTemp = 0;
	CPU_SR_ALLOC();                                               /*申请临界区变量*/
	
	OS_CRITICAL_ENTER();   		  				                                                            /* 以下必须考虑临界资源的问题 */
	uUsart2RxStaTemp = (g_Usart2_Rx_Sta&0X3FFF)+1;		
	memcpy( (char *)uTempWifiBuffer,(const char *)g_Usart2_Rx_Buf,uUsart2RxStaTemp );                          /* 复制 */				
	OS_CRITICAL_EXIT();     			                                                                        /* 以上必须考虑临界资源的问题 */
}

uint8_t uReportWifiSemErr( uint16_t uTime,uint8_t *uErrStr )
{
//	return uReportSemErr( (OS_SEM *)&g_WifiBlueOrder, uTime,uErrStr );
//	return uReportSemErr( (OS_SEM *)&g_WifiReceive, uTime,uErrStr );
	return EXE_SUCCEED;
}

uint8_t uReportWifiSem( uint16_t uTime )
{
//	return uReportSemErr( (OS_SEM *)&g_WifiBlueOrder, uTime,uErrStr );
//	return uReportSem( (OS_SEM *)&g_WifiReceive, uTime );
	return EXE_SUCCEED;
}

uint8_t uWifiUartSet( uint8_t uBauds,uint8_t uDatabit,uint8_t uStop )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	
	
	myprintf( "AT+UART=%d,%d,%d%s\r\n",uBauds,uDatabit,uStop,",0,0" );                             /* */
	
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */	
#endif
	
	return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"WIFI UART Err" );
}

/* 1=sta */
uint8_t uWifiEnterMode( uint8_t uMode )
{	
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                                        /* 清空缓存 */
														                       
	uRecUsart = uGetUsartPrintf();	                                           
	vEnableUsartPrintf( WIFI_USART_NUM );                                      /* 使能串口2printf */  	
														                       
	myprintf( "AT+CWMODE=%d\r\n",uMode );                                      /* */
														                       
	vEnableUsartPrintf( uRecUsart );                                           /* 使能串口1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"WIFI CWMODE Err" );
}

uint8_t uWifiNetInfo( void )
{	
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	
	
	myprintf( "AT+CIPSTATUS\r\n" );                             /* */
	
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"WIFI CIPSTATUS Err" );
}

uint8_t uWifiReadIP( void )
{	
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	
	
	myprintf( "AT+CIPSTA?\r\n" );                       /* */
	
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"WIFI CWMODE? Err" );
}

uint8_t uWifiAskMode( void )
{	
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	
	
	myprintf( "AT+CIPMODE?\r\n" );                             /* */
	
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"WIFI CIPMODE? Err" );
}

uint8_t uWifiCloseReDis( uint8_t uOnOff )
{	
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	
	
	myprintf( "ATE%d\r\n",uOnOff );                             /* */
	
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"WIFI ATE0 Err" );
}

uint8_t uWifiReset( void )
{	
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	
	
	myprintf( "AT+RST\r\n" );                             /* */
	
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_5_TIME,(uint8_t *)"WIFI RST Err" );
}

uint8_t uWifiResetInit( void )
{	
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	
	
	myprintf( "AT+RESTORE\r\n" );                       /* */
	
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"WIFI RESTORE Err" );
}

uint8_t uWifiGetVersion( void )
{	
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	
	
	myprintf( "AT+GMR\r\n" );                             /* */
	
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"WIFI GMR Err" );
}

uint8_t uWifiSleep( uint8_t uCheck,uint8_t uMode )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  
	
	if( 0==uCheck ){
		myprintf( "AT+SLEEP?\r\n" );                             /*清除打印缓存各参数恢复为默认值*/
	}else{
		myprintf( "AT+SLEEP=%d\r\n",uMode ); 
	}
	
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"WIFI SLEEP Err" );
}

/*  */
uint8_t uWifiConnectRoute( uint8_t* upName,uint8_t* upPassword )
{	
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	
	
	if( (NULL!=upName)&&(NULL!=upPassword) ){
//		myprintf( "AT+CWJAP_DEF=\"%s\",\"%s\"\r\n",upName,upPassword ); 	
		myprintf( "AT+CWJAP=\"%s\",\"%s\"\r\n",upName,upPassword ); 
	}
	
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_1_TIME,(uint8_t *)"WIFI CWJAP Err" );
}

/* 建立TCP/UDP连接 */
uint8_t uWifiConnectStart( uint8_t uType,uint8_t* upIP,uint8_t* upPort )
{	
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	
	
	if( (NULL!=upIP)&&(NULL!=upPort) ){
		if( TCP_TYPE==uType ){
			myprintf( "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n",upIP,upPort ); 	
		}else{
			myprintf( "AT+CIPSTART=\"UDP\",\"%s\",%s\r\n",upIP,upPort ); 
		}
	}
	
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_1_TIME,(uint8_t *)"WIFI CIPSTART Err" );
}

/* 开机透传 */
uint8_t uWifiConnectSavetRanStart( uint8_t uType,uint8_t* upIP,uint8_t* upPort )
{	
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	
	
	if( (NULL!=upIP)&&(NULL!=upPort) ){
		if( TCP_TYPE==uType ){
			myprintf( "AT+SAVETRANSLINK=1,\"%s\",%s,\"TCP\",10\r\n",upIP,upPort ); 	
		}else{
			myprintf( "AT+SAVETRANSLINK=1,\"%s\",%s,\"UDP\",1005\r\n",upIP,upPort ); 
		}
	}
	
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_6_TIME,(uint8_t *)"WIFI SAVETRANSLINK Err" );
}

uint8_t uWifiScanAP( void )
{
	CPU_SR_ALLOC();                                                   /*申请临界区变量*/
	uint8_t uTempArr[256] = {0};
	uint8_t uErr = 0;
	
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                               /* 清空缓存 */
													                  
	uRecUsart = uGetUsartPrintf();	                                  
	vEnableUsartPrintf( WIFI_USART_NUM );                             /* 使能串口2printf */  	
													                  
	myprintf( "AT+CWLAP\r\n" ); 	                                  
													                  
	vEnableUsartPrintf( uRecUsart );                                  /* 使能串口1printf */
#endif
	
	if( EXE_SUCCEED==uReportWifiSemErr( WAIT_SEM_1_TIME,(uint8_t *)"WIFI CWLAP Err" ) ){
		OS_CRITICAL_ENTER();   		  				                  /* 以下必须考虑临界资源的问题 */
		memcpy( uTempArr,g_Usart2_Rx_Buf,sizeof(uTempArr) );
		OS_CRITICAL_EXIT();   			                              /* 以上必须考虑临界资源的问题 */
		
		uErr = uWifiAPSsid( uTempArr );                                      /* 分离ssid用户名 */
		
		return uErr;
	}else{
		return EXE_FAILED;
	}
}

uint8_t uWifiCwApQuit( void )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	

	myprintf( "AT+CWQAP\r\n" ); 	
	
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_1_TIME,(uint8_t *)"WIFI CWQAP Err" );
}

/* uValue 1-82 */
uint8_t uWifiRFTxPower( uint8_t uCheck,uint8_t uValue )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	

	if( uCheck ){
		myprintf( "AT+RFPOWER=%d\r\n",uValue ); 	
	}else{
		myprintf( "AT+RFPOWER?\r\n" ); 
	}
	
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"WIFI RFPOWER Err" );
}

/* uValue 1900-3300 */
uint8_t uWifiRFTxVdd( uint8_t uCheck,uint16_t uValue )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	

	if( 1==uCheck ){
		myprintf( "AT+RFVDD=%d\r\n",uValue ); 	
	}else if( 2==uCheck ){
		myprintf( "AT+RFVDD\r\n" ); 
	}else{
		myprintf( "AT+RFVDD?\r\n" ); 
	}
	
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"WIFI RFVDD Err" );
}

uint8_t uWifiACwlaPort( uint8_t uRssi,uint8_t uMask )
{	
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	

	myprintf( "AT+CWLAPOPT=%d,%d\r\n",uRssi,uMask ); 	
	
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"WIFI CWLAPOPT Err" );
}

/* 发送数据 */
uint8_t uWifiStationSendData( uint8_t* upData,uint8_t uLen )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	
	
	if( (NULL!=upData)&&(uLen>0) ){	
		myprintf( "AT+CIPSEND=%d\r\n",uLen ); 
		uReportWifiSem( WAIT_SEM_TIME );/* 等待接收 > */
//		OSTimeDlyHMSM(0, 0, 0, 5,OS_OPT_TIME_HMSM_STRICT,&err); 	
		myprintf( "%s\r\n",upData ); 		
	}
	
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"WIFI CIPSENDS Err" );//

}

/* 发送字符数据 */
uint8_t uWifiStationSendDataChar( uint8_t upData )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	
		
	myprintf( "AT+CIPSEND=%d\r\n",1 ); 
	uReportWifiSem( WAIT_SEM_TIME );/* 等待接收 > */
//	OSTimeDlyHMSM(0, 0, 0, 5,OS_OPT_TIME_HMSM_STRICT,&err); 
	vClearWifiBuffer();                                 /* 清空缓存 */
	myprintf( "%c",upData ); 		
		
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"WIFI CIPSENDChar Err" );//
}

/* 发送数据 */
uint8_t uWifiStationSendOriginalData( uint8_t* upData,uint8_t uLen )
{	
	uint8_t uErr = 0;
	
	uErr = uWifiStationSendLen( uLen );
	if( EXE_SUCCEED==uErr ){
		uErr = uWifiStationSendDatas( upData,uLen );
	}
	
	return uErr;
}

uint8_t uWifiStationSendLen( uint32_t uLen )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                                        /* 清空缓存 */
														                       
	uRecUsart = uGetUsartPrintf();	                                           
	vEnableUsartPrintf( WIFI_USART_NUM );                                      /* 使能串口2printf */  	
			
	if( (uLen>0) ){              /* <sizeof()  */
		myprintf( "AT+CIPSEND=%d\r\n",uLen );                                     /* */
	}
	
	vEnableUsartPrintf( uRecUsart );                                           /* 使能串口1printf */
#endif
	
	uReportWifiSem( WAIT_SEM_TIME );        /* 等待接收 > */
	return EXE_SUCCEED;	
}

uint8_t uWifiStationSendDatas( uint8_t* upData,uint32_t uLen )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                                        /* 清空缓存 */
														                       
	uRecUsart = uGetUsartPrintf();	                                           
	vEnableUsartPrintf( WIFI_USART_NUM );                                      /* 使能串口2printf */  	
			
	if( (NULL!=upData)&&(uLen>0) ){              /* <sizeof()  */		
		myprintf( "%s",upData );
	}
	
	vEnableUsartPrintf( uRecUsart );                                           /* 使能串口1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"WifiStation Datas Err" );
}


/* 发送数据 */
uint8_t uWifiTransparentSendData( uint8_t* upData )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	
	
	if( (NULL!=upData) ){		
		myprintf( "%s\r\n",upData ); 		
	}
	
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
	
	return EXE_SUCCEED;
}

/* 发送字符数据 */
uint8_t uWifiTransparentSendDataChar( uint8_t upData )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	
				
	myprintf( "%c",upData ); 		
		
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
	
	return EXE_SUCCEED;
}

/* 发送字符串数据 */
uint8_t uWifiTransparentSendOriginalData( uint8_t* upData,uint32_t uLen )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	
	
	if( (NULL!=upData) ){		
		myprintf( "%s",upData ); 		
	}
	
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
	
	return EXE_SUCCEED;
}

/* 在AT指令模式下连接到服务器后才能再进入透明传输 */
uint8_t uWifiStationTransfer( uint8_t uOpenClose,uint8_t uTransparent )
{	
#if	DEBUH_UART2
//	OS_ERR err;
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	
	
	if( TRANSFER_AP_STATION==uOpenClose){
		myprintf( "AT+CIPMODE=%d\r\n",uTransparent ); 
	}else{
		myprintf( "+++" );
//		OSTimeDlyHMSM(0, 0, 0, 200,OS_OPT_TIME_HMSM_STRICT,&err);	       /* 不会响应OK 发送下一条指令需要等待200ms */
//		myprintf( "\r\n" );
//		OSTimeDlyHMSM(0, 0, 0, 200,OS_OPT_TIME_HMSM_STRICT,&err);	       /* 不会响应OK 发送下一条指令需要等待200ms */
	}
		
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
	
	if( TRANSFER_AP_STATION==uOpenClose){
		return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"WIFI CIPMODE Err" );
	}else{
		uReportWifiSemErr( WAIT_SEM_4_TIME,(uint8_t *)"WIFI +++" );     /* 不会响应OK 发送下一条指令需要等待200ms */
		return EXE_SUCCEED;
	}
}

uint8_t uWifiStationNullOrder( void )
{	
#if	DEBUH_UART2
//	OS_ERR err;
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  
	
	myprintf( "+++\r\n" );
		
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif	

	uReportWifiSem( WAIT_SEM_4_TIME );     /* 不会响应OK 发送下一条指令需要等待200ms */
	return EXE_SUCCEED;
}

uint8_t uWifiPing( uint8_t* pIpAddr )
{	
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	
	
	myprintf( "AT+PING=\"%s\"\r\n",pIpAddr );           /* AT+PING="192.168.1.202" */
		
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
		
	return uReportWifiSemErr( WAIT_SEM_5_TIME,(uint8_t *)"WIFI Ping Err" );
}

uint8_t uEnterTransparent( void )
{	
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	
	
	myprintf( "AT+CIPSEND\r\n" ); 
		
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
		
	return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"WIFI CIPSEND" );
}

/* 设置为开机进入透明传输或关闭透明传输 */
uint8_t uWifiStationDeafulTransfer( uint8_t uOpenClose )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* 清空缓存 */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* 使能串口2printf */  	
	
	if( TRANSFER_AP_STATION==uOpenClose){
		myprintf( "AT+CIPMODE=1\r\n" ); 
		/* 等待接收 ok */
		myprintf( "AT+CIPSEND\r\n" ); 
	}else{
		myprintf( "+++\r\n" ); 
		/* 等待接收 ok */
		myprintf( "AT+SAVETRANSLINK=0\r\n" );           /* 关闭开机透传模式 */
	}
		
	vEnableUsartPrintf( uRecUsart );                    /* 使能串口1printf */
#endif
	
	return EXE_SUCCEED;
}
