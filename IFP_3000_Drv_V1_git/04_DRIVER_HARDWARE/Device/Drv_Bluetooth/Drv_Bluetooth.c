#include "Drv_Bluetooth.h"
#include "Global_Variable.h"

uint8_t uWifiBuleOrder( uint8_t* pOrder )
{
//	uint8_t uLen = 0;
	
	if( NULL!=strstr((const char *)pOrder,(const char *)"+BTINIT:") ){
//		uLen = strlen((const char *)"+BTINIT:");
	
	}
	switch( 1 ){
		case 1:
			break;
		
		default:
			break;
	}
	
	return EXE_SUCCEED;
}

void vClearBluetoothBuffer( void )
{
	vClearWifiBuffer();                                 /* ��ջ��� */
}

void vCopyBluetoothBuffer( uint8_t* uTempWifiBuffer,uint16_t uSize )
{
	vCopyWifiBuffer( uTempWifiBuffer,uSize ); 			                                    
}

uint8_t uReportBluetoothSemErr( uint16_t uTime,uint8_t *uErrStr )
{
	return uReportWifiSemErr( uTime, uErrStr );
}

/*
AT+BTINIT?                                    // ��ѯ 
AT+BTINIT=1                                   // ��ʼ�� 
AT+BTSCANMODE=2                               //������������ģʽ �ɷ���Ҳ������
AT+BTSPPINIT=2                                //����Ϊ�ͷ��� ��ӡ��Ϊ�����
AT+BTSTARTDISC=0,10,8                         //ɨ��ģ�� 0 ��ͨģʽ 10 ����ʱ�� 8���ض��ٸ������豸
AT+BTSPPCONN=0,0,"dc:1d:30:61:f8:fb"          //���Ӷ�Ӧ��MAC��ַ
AT+BTSPPSEND=0,10                             //��������
AT+BTNAME?
AT+BTNAME="XC"
*/

/*
AT+BTINIT=1                                   // ��ʼ��  
*/
uint8_t uBluetoothSetInitMode( uint8_t uMode )
{	
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                                        /* ��ջ��� */
														                       
	uRecUsart = uGetUsartPrintf();	                                           
	vEnableUsartPrintf( WIFI_USART_NUM );                                      /* ʹ�ܴ���2printf */  	
														                       
	myprintf( "AT+BTINIT=%d\r\n",uMode );                                      /* */
														                       
	vEnableUsartPrintf( uRecUsart );                                           /* ʹ�ܴ���1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"Bluetooth BTINIT Err" );
}

/*
AT+BLEINIT=1                                   // ��ʼ��  
*/
uint8_t uBluetoothSetBleInitMode( uint8_t uMode )
{	
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                                        /* ��ջ��� */
														                       
	uRecUsart = uGetUsartPrintf();	                                           
	vEnableUsartPrintf( WIFI_USART_NUM );                                      /* ʹ�ܴ���2printf */  	
														                       
	myprintf( "AT+BLEINIT=%d\r\n",uMode );                                      /* */
														                       
	vEnableUsartPrintf( uRecUsart );                                           /* ʹ�ܴ���1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"Bluetooth BLEINIT Err" );
}

/*
AT+BTINIT?                                    // ��ѯ 
*/
int8_t uBluetoothGetMode( void )
{	
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                                        /* ��ջ��� */
														                       
	uRecUsart = uGetUsartPrintf();	                                           
	vEnableUsartPrintf( WIFI_USART_NUM );                                      /* ʹ�ܴ���2printf */  	
														                       
	myprintf( "AT+BTINIT?\r\n" );                                              /* */
														                       
	vEnableUsartPrintf( uRecUsart );                                           /* ʹ�ܴ���1printf */
#endif
	
	if( EXE_SUCCEED==uReportWifiSemErr(WAIT_SEM_TIME,(uint8_t *)"Bluetooth BTINIT? Err") ){
		return 1;
	}else{
		return EXE_SPECIAL_FAILED;
	}
}

/*
AT+BLEINIT?                                    // ��ѯ 
*/
int8_t uBluetoothGetBleMode( void )
{	
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                                        /* ��ջ��� */
														                       
	uRecUsart = uGetUsartPrintf();	                                           
	vEnableUsartPrintf( WIFI_USART_NUM );                                      /* ʹ�ܴ���2printf */  	
														                       
	myprintf( "AT+BLEINIT?\r\n" );                                              /* */
														                       
	vEnableUsartPrintf( uRecUsart );                                           /* ʹ�ܴ���1printf */
#endif
	
	if( EXE_SUCCEED==uReportWifiSemErr(WAIT_SEM_TIME,(uint8_t *)"Bluetooth BLEINIT? Err") ){
		return 1;
	}else{
		return EXE_SPECIAL_FAILED;
	}
}

/*
AT+BTSCANMODE=2                               //������������ģʽ �ɷ���Ҳ������
*/
uint8_t uBluetoothSetScanMode( uint8_t uMode )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                                        /* ��ջ��� */
														                       
	uRecUsart = uGetUsartPrintf();	                                           
	vEnableUsartPrintf( WIFI_USART_NUM );                                      /* ʹ�ܴ���2printf */  	
														                       
	myprintf( "AT+BTSCANMODE=%d\r\n",uMode );                                      /* */
														                       
	vEnableUsartPrintf( uRecUsart );                                           /* ʹ�ܴ���1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"Bluetooth BTSCANMODE Err" );
}

/*
AT+BTSTARTDISC=0,10,8                         //ɨ��ģ�� 0 ��ͨģʽ 10 ����ʱ�� 8���ض��ٸ������豸
*/
uint8_t uBluetoothScanDis( uint8_t uDuration,uint8_t uResponses )
{
//	CPU_SR_ALLOC();                                                   /*�����ٽ�������*/
#if	DEBUH_UART2	
	uint8_t uRecUsart = 0;
	uint8_t* puTempArr = NULL;
	uint8_t uErr = 0;
	
	vClearWifiBuffer();                                                        /* ��ջ��� */
														                       
	uRecUsart = uGetUsartPrintf();	                                           
	vEnableUsartPrintf( WIFI_USART_NUM );                                      /* ʹ�ܴ���2printf */  	
														                       
	myprintf( "AT+BTSTARTDISC=0,%d,%d\r\n",uDuration,uResponses );                                      /* */
														                       
	vEnableUsartPrintf( uRecUsart );                                           /* ʹ�ܴ���1printf */
#endif
	
	if( EXE_SUCCEED==uReportWifiSemErr( WAIT_SEM_1_TIME,(uint8_t *)"Bluetooth BTSTARTDISC Err" ) ){
		puTempArr = calloc( 1,USART2_REC_LEN );
		if( NULL==puTempArr ){
			return EXE_FAILED;
		}
		
//		OS_CRITICAL_ENTER();   		  				                  /* ���±��뿼���ٽ���Դ������ */
//		memcpy( puTempArr,g_Usart2_Rx_Buf,sizeof(g_Usart2_Rx_Buf) );
//		OS_CRITICAL_EXIT();   			                              /* ���ϱ��뿼���ٽ���Դ������ */
		vCopyBluetoothBuffer( puTempArr,USART2_REC_LEN );
		
		uErr = uBlueAPSsid( puTempArr );                                      /* ����ssid�û��� */
		
		if( NULL!=puTempArr ){
			free( puTempArr );
		}
		
		return uErr;
	}else{
		return EXE_FAILED;
	}
}

/*
AT+BTSPPINIT=2                                //����Ϊ�ͷ��� ��ӡ��Ϊ�����
*/
uint8_t uBluetoothSetSppInit( uint8_t uMasterSlave )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                                        /* ��ջ��� */
														                       
	uRecUsart = uGetUsartPrintf();	                                           
	vEnableUsartPrintf( WIFI_USART_NUM );                                      /* ʹ�ܴ���2printf */  	
														                       
	myprintf( "AT+BTSPPINIT=%d\r\n",uMasterSlave );                                      /* */
														                       
	vEnableUsartPrintf( uRecUsart );                                           /* ʹ�ܴ���1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"Bluetooth BTSPPINIT Err" );
}

/*
AT+BTSPPCONN=0,0,"dc:1d:30:61:f8:fb"          //���Ӷ�Ӧ��MAC��ַ
*/
uint8_t uBluetoothConnet( uint8_t* uRemoteAddress,uint32_t uLen )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
//	uint8_t uTemp[128] = {0};
//	sprintf( (char *)uTemp,"%s%s%s","AT+BTSPPCONN=0,0,\"",uRemoteAddress,"\"\r\n" );
//	myprintf( "%s",uTemp ); 
//	uReportWifiSemErr( WAIT_SEM_2_TIME,(uint8_t *)"Bluetooth BTSPPCONN Err" );
	
	vClearWifiBuffer();                                                        /* ��ջ��� */
														                       
	uRecUsart = uGetUsartPrintf();	                                           
	vEnableUsartPrintf( WIFI_USART_NUM );                                      /* ʹ�ܴ���2printf */  	
			
	if( uLen ){              /* <sizeof()  */
		myprintf( "AT+BTSPPCONN=0,0,\"%s\"\r\n",uRemoteAddress );                                      /* */
	}
	
	vEnableUsartPrintf( uRecUsart );                                           /* ʹ�ܴ���1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_1_TIME,(uint8_t *)"Bluetooth BTSPPCONN Err" );
}

uint8_t uBluetoothEncdev( void )
{	
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
		
	vClearWifiBuffer();                                                        /* ��ջ��� */
														                       
	uRecUsart = uGetUsartPrintf();	                                           
	vEnableUsartPrintf( WIFI_USART_NUM );                                      /* ʹ�ܴ���2printf */  			

	myprintf( "AT+BTENCDEV?\r\n" );                                   /* */
	
	vEnableUsartPrintf( uRecUsart );                                           /* ʹ�ܴ���1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_8_TIME,(uint8_t *)"Bluetooth BTENCDEV Err" );
	
}

/*
AT+BTSPPSEND=0,10                             //��������
*/
uint8_t uBluetoothSendData( uint8_t* upData,uint32_t uLen )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                                        /* ��ջ��� */
														                       
	uRecUsart = uGetUsartPrintf();	                                           
	vEnableUsartPrintf( WIFI_USART_NUM );                                      /* ʹ�ܴ���2printf */  	
			
	if( (NULL!=upData)&&(uLen>0) ){              /* <sizeof()  */
		myprintf( "AT+BTSPPSEND=0,%d\r\n",uLen );                                      /* */
		uReportWifiSem( WAIT_SEM_TIME );       /* �ȴ����� > */
		
		myprintf( "%s\r\n",upData );
	}
	
	vEnableUsartPrintf( uRecUsart );                                           /* ʹ�ܴ���1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"Bluetooth BTSPPSEND Err" );
}

uint8_t uBluetoothSendCharData( uint8_t uData )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                                        /* ��ջ��� */
														                       
	uRecUsart = uGetUsartPrintf();	                                           
	vEnableUsartPrintf( WIFI_USART_NUM );                                      /* ʹ�ܴ���2printf */  	
	
	myprintf( "AT+BTSPPSEND=0,%d\r\n",1 );                                      /* */
	uReportWifiSem( WAIT_SEM_TIME );       /* �ȴ����� > */
	
	myprintf( "%c",uData );	
	
	vEnableUsartPrintf( uRecUsart );                                           /* ʹ�ܴ���1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_TIME,(uint8_t *)"Bluetooth BTSPPSEND Err" );
}

uint8_t uBluetoothSendOriginalData( uint8_t* upData,uint32_t uLen )
{
	uint8_t uErr = 0;
	
	uErr = uBluetoothSendLen( uLen );
	if( EXE_SUCCEED==uErr ){
		uErr = uBluetoothSendDatas( upData,uLen );
	}
	
	if( EXE_SUCCEED!=uErr ){
		gp_stuConfigFile->uWifiOnOff = WIFI_OFF;
		g_uWifiConnect = WIFI_CONNEST_DISLINE;
		uWifiOpenClose( WIFI_W01_E103_OFF );                /* �ر�WIFI */
	}
	
	return uErr;
}

uint8_t uBluetoothSendDatas( uint8_t* upData,uint32_t uLen )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	uint32_t i = 0;
	
	vClearWifiBuffer();                                                        /* ��ջ��� */
														                       
	uRecUsart = uGetUsartPrintf();	                                           
	vEnableUsartPrintf( WIFI_USART_NUM );                                      /* ʹ�ܴ���2printf */  	
			
	if( (NULL!=upData)&&(uLen>0) ){              /* <sizeof()  */		
		for( i=0;i<uLen;i++ ){
			myprintf( "%c",*(upData+i) );
		}
	}
	
	vEnableUsartPrintf( uRecUsart );                                           /* ʹ�ܴ���1printf */
#endif
	
	return uReportWifiSemErr( WAIT_SEM_8_TIME,(uint8_t *)"Bluetooth Datas Err" );
}

uint8_t uBluetoothSendLen( uint32_t uLen )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                                        /* ��ջ��� */
														                       
	uRecUsart = uGetUsartPrintf();	                                           
	vEnableUsartPrintf( WIFI_USART_NUM );                                      /* ʹ�ܴ���2printf */  	
			
	if( (uLen>0) ){              /* <sizeof()  */
		myprintf( "AT+BTSPPSEND=0,%d\r\n",uLen );                                      /* */
	}
	
	vEnableUsartPrintf( uRecUsart );                                           /* ʹ�ܴ���1printf */
#endif
	
	uReportWifiSem( WAIT_SEM_TIME );        /* �ȴ����� > */
	return EXE_SUCCEED;
}

/* �������� */
uint8_t uBluetoothTransparentSendData( uint8_t* upData )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* ��ջ��� */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* ʹ�ܴ���2printf */  	
	
	if( (NULL!=upData) ){		
		myprintf( "%s\r\n",upData ); 		
	}
	
	vEnableUsartPrintf( uRecUsart );                    /* ʹ�ܴ���1printf */
#endif
	
	return EXE_SUCCEED;
}

/* �����ַ����� */
uint8_t uBluetoothTransparentSendDataChar( uint8_t upData )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* ��ջ��� */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* ʹ�ܴ���2printf */  	
				
	myprintf( "%c",upData ); 		
		
	vEnableUsartPrintf( uRecUsart );                    /* ʹ�ܴ���1printf */
#endif
	
	return EXE_SUCCEED;
}

/* �����ַ������� */
uint8_t uBluetoothTransparentSendOriginalData( uint8_t* upData,uint32_t uLen )
{
#if	DEBUH_UART2
	uint8_t uRecUsart = 0;
	
	vClearWifiBuffer();                                 /* ��ջ��� */
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( WIFI_USART_NUM );               /* ʹ�ܴ���2printf */  	
	
	if( (NULL!=upData) ){		
		myprintf( "%s",upData ); 		
	}
	
	vEnableUsartPrintf( uRecUsart );                    /* ʹ�ܴ���1printf */
#endif
	
	return EXE_SUCCEED;
}
