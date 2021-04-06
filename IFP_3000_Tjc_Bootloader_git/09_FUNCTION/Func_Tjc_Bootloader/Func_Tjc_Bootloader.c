#include "Func_TjcBootloader.h"

uint8_t uUart1Parsing( uint16_t* puSize )
{
	uint8_t* pUartTemp = NULL;
	uint16_t uSize = *puSize;
	
	pUartTemp = (uint8_t *)calloc( USART_REC_LEN,sizeof(uint8_t) );
	if( NULL==pUartTemp ){
		return EXE_FAILED;
	}
	
	if( *puSize ){		
		uUart1DataCopy( (uint8_t *)pUartTemp,(uint8_t *)g_Usart_Rx_Buf,(uint16_t *)puSize );		
		
		uDeclarationspData( (uint8_t *)pUartTemp,uSize );                                                      /*  */
	}
	
	if( NULL!=pUartTemp ){
		free( pUartTemp );
	}
	
	return EXE_SUCCEED;
}

uint8_t uUart1DataCopy( uint8_t* puTarget,uint8_t* puSource,uint16_t* puSize )
{
	/* 处理数据，这里用于演示，将收到的数据使用DMA发送出去 */
	memcpy((uint8_t *)puTarget,(uint8_t *)puSource,*puSize );
//	memset((uint8_t *)puSource,0,*puSize);
	*puSize = 0;
	
	/* DMA接收复位 */
	DMA_Cmd(DMA1_Channel5,DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel5,USART_REC_LEN);
	DMA_Cmd(DMA1_Channel5,ENABLE);
	
	return EXE_SUCCEED;
}

uint8_t uUart1DmaSend( uint8_t* puTarget,uint16_t uSize )
{
	/* 处理数据，这里用于演示，将收到的数据使用DMA发送出去 */
	memcpy((uint8_t *)g_Usart_Tx_Buf,(uint8_t *)puTarget,uSize );
	
	/* 先关闭DMA发送通道 */
	DMA_Cmd(DMA1_Channel4,DISABLE);
	/* 清除标志 */
	DMA_ClearFlag(DMA1_FLAG_TC4);
	/* 设置DMA发送长度 */
	DMA_SetCurrDataCounter( DMA1_Channel4,uSize );
	/* 使能DMA发送通道 */
	DMA_Cmd(DMA1_Channel4,ENABLE);
	/* 等待发送完成，这里没有使用DMA发送完成中断 */
	while( !DMA_GetFlagStatus(DMA1_FLAG_TC4) );
	
	return EXE_SUCCEED;
}

uint8_t uUart4DmaSend( uint8_t* puTarget,uint16_t uSize )
{
	/* 处理数据，这里用于演示，将收到的数据使用DMA发送出去 */
	memcpy((uint8_t *)g_Usart4_Tx_Buf,(uint8_t *)puTarget,uSize );
	
	/* 先关闭DMA发送通道 */
	DMA_Cmd(DMA2_Channel5,DISABLE);
	/* 清除标志 */
	DMA_ClearFlag(DMA2_FLAG_TC5);
	
	/* 设置DMA发送长度 */
	DMA_SetCurrDataCounter( DMA2_Channel5,uSize );
	/* 使能DMA发送通道 */
	DMA_Cmd(DMA2_Channel5,ENABLE);
	/* 等待发送完成，这里没有使用DMA发送完成中断 */
	while( !DMA_GetFlagStatus(DMA2_FLAG_TC5) );
	
	return EXE_SUCCEED;
}

uint8_t uUart4DataCopy( uint8_t* puTarget,uint8_t* puSource,uint16_t* puSize )
{
	/* 处理数据，这里用于演示，将收到的数据使用DMA发送出去 */
	memcpy((uint8_t *)puTarget,(uint8_t *)puSource,*puSize );
//	memset((uint8_t *)puSource,0,*puSize);
	*puSize = 0;
	
	/* DMA接收复位 */
	DMA_Cmd(DMA2_Channel3,DISABLE);
	DMA_SetCurrDataCounter(DMA2_Channel3,USART4_REC_LEN);
	DMA_Cmd(DMA2_Channel3,ENABLE);
	
	return EXE_SUCCEED;
}

uint8_t uDeclarationspData( uint8_t* puTarget,uint16_t uSize )
{
	static uint8_t l_uReceiveFile = 0;
	static uint32_t l_uTftFileLength = 0;
	static uint32_t l_uTftFileLengthCount = 0;
	static uint32_t l_uPageCounti = 0;
	OS_ERR err = OS_ERR_NONE;
	uint8_t uReplyData[128] = {0};
	uint16_t uLength = 0;
	LOADER sBootLoader = {0};
	uint8_t* puTempArr = NULL;
	uint8_t uRecLenTemp = 0;
	
	if( NULL!=strstr((const char *)puTarget,(const char *)"connect") ){	
		sprintf( (char *)(uReplyData),"%c",0x1A );
		uLength =  strlen((const char *)uReplyData);
		sprintf( (char *)(uReplyData+uLength),"%c%c%c",0xFF,0xFF,0xFF );
		uLength =  strlen((const char *)uReplyData);
//		OSTimeDlyHMSM(0, 0, 0, 50,OS_OPT_TIME_HMSM_STRICT,&err);	                            /* 延时10ms   */	
		
		sprintf( (char *)(uReplyData+uLength),"%s%d%c%s%c%s%c%s%c%s%c%s%c%s","comok ",2,',',"30614-0",',',"TJC4832T135_011C",',',"30",',',"61744",',',"313E3401D97FD655",',',"8388608" );
		uLength =  strlen((const char *)uReplyData);
		sprintf( (char *)(uReplyData+uLength),"%c%c%c",0xFF,0xFF,0xFF );
		uLength =  strlen((const char *)uReplyData);
		
		uUart1DmaSend( (uint8_t *)uReplyData,uLength );	
		l_uReceiveFile = 0;	
		l_uTftFileLengthCount = 0;	
		l_uPageCounti = 0;
	}else if( NULL!=strstr((const char *)puTarget,(const char *)"wri") ){
		sprintf( (char *)(uReplyData),"%s%d%c%s%c%s%c%s%c%s%c%s%c%s","comok ",2,',',"30614-0",',',"TJC4832T135_011C",',',"30",',',"61744",',',"313E3401D97FD655",',',"8388608" );
		uLength =  strlen((const char *)uReplyData);		
		sprintf( (char *)(uReplyData+uLength),"%c%c%c",0xFF,0xFF,0xFF );
		uLength =  strlen((const char *)uReplyData);	
		
		uUart1DmaSend( (uint8_t *)uReplyData,uLength );	
		
		uLength = 0;
		memset( uReplyData,0,sizeof(uReplyData) );
		
		OSTimeDlyHMSM(0, 0, 1, 500,OS_OPT_TIME_HMSM_STRICT,&err);	                            /* 延时10ms   */	
		
		sprintf( (char *)(uReplyData),"%c",0x05 );
		uLength =  strlen((const char *)uReplyData);
		
		uUart1DmaSend( (uint8_t *)uReplyData,uLength );	
		
		puTempArr = (uint8_t *)strtok( (char *)(puTarget)," " );
		puTempArr = (uint8_t *)strtok( NULL,"," );
		if( (NULL!=puTempArr) ){  
			uRecLenTemp = strlen( (const char *)puTempArr );
			uTjcAsciiToInt( puTempArr,&l_uTftFileLength,uRecLenTemp ); 			
		}
		
		l_uReceiveFile = 1;		
	}else if( NULL!=strstr((const char *)puTarget,(const char *)"666666") ){
		SPI_Flash_Read( (uint8_t *)&sBootLoader,(SPIFLASH_TJC_LOADER),sizeof(LOADER) );
		uUart4UpgardeEngineering( sBootLoader.uSectorSize,sBootLoader.uFileSize );	
	}else{	
		if( 1==l_uReceiveFile ){
			
			/* 存TJC */
//			SPI_Flash_Write_Page( (uint8_t *)"ABC",SPIFLASH_TJC_TFT,uSize );
//			SPI_Flash_Erase_Sector( (((SPIFLASH_TJC_TFT)/SPIFLASH_PAGE_BASE_ADDR)+l_uPageCounti) );
			
			SPI_Flash_Write_NoCheck( (uint8_t *)puTarget,(SPIFLASH_TJC_TFT+(SPIFLASH_PAGE_BASE_ADDR*l_uPageCounti)),uSize );
			l_uPageCounti++;
			
			sprintf( (char *)(uReplyData),"%c",0x05 );
			uLength =  strlen((const char *)uReplyData);
			
			uUart1DmaSend( (uint8_t *)uReplyData,uLength );	
			
			l_uTftFileLengthCount += uSize;			
			if( l_uTftFileLengthCount==l_uTftFileLength ){
				
//				/* 写TJC */
				uUart4UpgardeEngineering( l_uPageCounti,l_uTftFileLength );	
				sBootLoader.uFileSize = l_uTftFileLength;
				sBootLoader.uSectorSize = l_uPageCounti;
				SPI_Flash_Write_NoCheck( (uint8_t *)&sBootLoader,(SPIFLASH_TJC_LOADER),sizeof(LOADER) );
				
				l_uReceiveFile = 0;
				l_uTftFileLengthCount = 0;
				l_uPageCounti = 0;
			}
		}else{

		}

	}
	
	return EXE_SUCCEED;
}

uint8_t uUart4UpgardeEngineering( uint32_t uSetor,uint32_t uSize )
{
	OS_ERR err = OS_ERR_NONE;
	uint8_t uReplyData[128] = {0};
	uint8_t uReceiveData[256] = {0};
	uint16_t uLength = 0;
	uint8_t uRecUpgaedeErr = 0;
//	uint32_t i = 0;
//	uint32_t uSizeCount = 0;
	
	uSemclear( &g_TjcUpgarde );
	
	sprintf( (char *)(uReplyData),"%c",0x01 );
	uLength =  uMyStrlength((const char *)uReplyData);
	sprintf( (char *)(uReplyData+uLength),"%c%c%c",0xFF,0xFF,0xFF );
	uLength =  uMyStrlength((const char *)uReplyData);
	uUart4DmaSend( (uint8_t *)uReplyData,uLength );	
	
	uLength = 0;
	memset( uReplyData,0,sizeof(uReplyData) );
	
	sprintf( (char *)(uReplyData),"%c%c",0xFF,0xFF );
	uLength =  uMyStrlength((const char *)uReplyData);
	uUart4DmaSend( (uint8_t *)uReplyData,uLength );	
	
	uLength = 0;
	memset( uReplyData,0,sizeof(uReplyData) );
	
	sprintf( (char *)(uReplyData),"%s","DRAKJHSUYDGBNCJHGJKSHBDN" );
	uLength =  uMyStrlength((const char *)uReplyData);
	sprintf( (char *)(uReplyData+uLength),"%c%c%c",0xFF,0xFF,0xFF );
	uLength =  uMyStrlength((const char *)uReplyData);
	uUart4DmaSend( (uint8_t *)uReplyData,uLength );	
	OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	
		
	uLength = 0;
	memset( uReplyData,0,sizeof(uReplyData) );
	
	sprintf( (char *)(uReplyData),"%s","connect" );
	uLength =  uMyStrlength((const char *)uReplyData);
	sprintf( (char *)(uReplyData+uLength),"%c%c%c",0xFF,0xFF,0xFF );
	uLength =  uMyStrlength((const char *)uReplyData);
	uUart4DmaSend( (uint8_t *)uReplyData,uLength );
	OSTimeDlyHMSM(0, 0, 0, 60,OS_OPT_TIME_HMSM_STRICT,&err);	
	
	uLength = 0;
	memset( uReplyData,0,sizeof(uReplyData) );

	sprintf( (char *)(uReplyData),"%c%c",0xFF,0xFF );
	uLength =  uMyStrlength((const char *)uReplyData);
	uUart4DmaSend( (uint8_t *)uReplyData,uLength );
	
	uLength = 0;
	memset( uReplyData,0,sizeof(uReplyData) );
	
	sprintf( (char *)(uReplyData),"%s","connect" );
	uLength =  uMyStrlength((const char *)uReplyData);
	sprintf( (char *)(uReplyData+uLength),"%c%c%c",0xFF,0xFF,0xFF );
	uLength =  uMyStrlength((const char *)uReplyData);
	uUart4DmaSend( (uint8_t *)uReplyData,uLength );	
	OSTimeDlyHMSM(0, 0, 0, 60,OS_OPT_TIME_HMSM_STRICT,&err);
	
	uLength = 0;
	memset( uReplyData,0,sizeof(uReplyData) );
	
	OSSemPend( (OS_SEM *)&g_TjcUpgarde, UPGARDE_WAIT_TIME,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	           /*  */
	if( OS_ERR_NONE==err ){
		uUart4DataCopy( uReceiveData,g_Usart4_Rx_Buf,&g_Usart4_Rx_Sta );
		OSTimeDlyHMSM(0, 0, 0, 100,OS_OPT_TIME_HMSM_STRICT,&err);
		
		sprintf( (char *)(uReplyData),"%s","delay=2500" );
		uLength =  uMyStrlength((const char *)uReplyData);
		sprintf( (char *)(uReplyData+uLength),"%c%c%c",0xFF,0xFF,0xFF );
		uLength =  uMyStrlength((const char *)uReplyData);
		uUart4DmaSend( (uint8_t *)uReplyData,uLength );	
		OSTimeDlyHMSM(0, 0, 1, 500,OS_OPT_TIME_HMSM_STRICT,&err);
		
		uLength = 0;
		memset( uReplyData,0,sizeof(uReplyData) );
		
		sprintf( (char *)(uReplyData),"%c",0x00 );
		uLength =  1;//uMyStrlength((const char *)uReplyData);
		sprintf( (char *)(uReplyData+uLength),"%c%c%c",0xFF,0xFF,0xFF );
		uLength =  uMyStrlength((const char *)uReplyData);
		uUart4DmaSend( (uint8_t *)uReplyData,uLength );	
		OSTimeDlyHMSM(0, 0, 0, 100,OS_OPT_TIME_HMSM_STRICT,&err);
		
		uLength = 0;
		memset( uReplyData,0,sizeof(uReplyData) );
		
		sprintf( (char *)(uReplyData),"%s%d%c%d%c%d","whmi-wri ",uSize,',',115200,',',0 );
		uLength =  uMyStrlength((const char *)uReplyData);
		sprintf( (char *)(uReplyData+uLength),"%c%c%c",0xFF,0xFF,0xFF );
		uLength =  uMyStrlength((const char *)uReplyData);
		uUart4DmaSend( (uint8_t *)uReplyData,uLength );
		uLength = 0;
		memset( uReplyData,0,sizeof(uReplyData) );
		
		OSTimeDlyHMSM(0, 0, 0, 100,OS_OPT_TIME_HMSM_STRICT,&err);
		OSSemPend( (OS_SEM *)&g_TjcUpgarde, UPGARDE_WAIT_TIME,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	           /*  */
		if( OS_ERR_NONE==err ){
			uUart4DataCopy( uReceiveData,g_Usart4_Rx_Buf,&g_Usart4_Rx_Sta );
		}
			
		OSTimeDlyHMSM(0, 0, 2, 50,OS_OPT_TIME_HMSM_STRICT,&err);	/* 延时不能修改 */	
		
		OSSemPend( (OS_SEM *)&g_TjcUpgarde, UPGARDE_WAIT_TIME,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	           /*  */
		if( OS_ERR_NONE==err ){
			uUart4DataCopy( uReceiveData,g_Usart4_Rx_Buf,&g_Usart4_Rx_Sta );
			if( 5!=uReceiveData[0] ){
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Upgrade failed" );	//
				return EXE_FAILED;
			}
//			OSTimeDlyHMSM(0, 0, 0, 50,OS_OPT_TIME_HMSM_STRICT,&err);			
//			OSSemPend( (OS_SEM *)&g_TjcUpgarde, UPGARDE_WAIT_TIME,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	           /*  */
//			if( OS_ERR_NONE==err ){
//				uUart4DataCopy( uReceiveData,g_Usart4_Rx_Buf,&g_Usart4_Rx_Sta );
//				if( 5!=uReceiveData[0] ){
//					uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Upgrade failed" );	//
//					return EXE_FAILED;
//				}
//			}else{
//				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Upgrade failed" );	//
//				return EXE_FAILED;
//			}
//			uSemclear( &g_TjcUpgarde );
//			OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);
			
			uRecUpgaedeErr = uUart4UpgardeFile( uSetor,uSize );
			if( EXE_FAILED==uRecUpgaedeErr){
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Upgrade failed" );	//
				return EXE_FAILED;
			}			
		}else{
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Upgrade failed" );	//
			return EXE_FAILED;
		}		
	}else{
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Upgrade failed" );	//
		return EXE_FAILED;
	}
	
	uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Upgrade successful" );	//
	return EXE_SUCCEED;
}

uint8_t uUart4UpgardeFile( uint32_t uSetor,uint32_t uSize )
{
	OS_ERR err = OS_ERR_NONE;
	uint8_t uReceiveData[256] = {0};
	uint32_t i = 0;
	uint32_t uSizeCount = 0;
	
	/* 写TJC */
	if( uSetor>=2 ){
		for( i=0;i<uSetor;i++ ){
			if( (uSize-uSizeCount)>USART4_REC_LEN ){
				SPI_Flash_Read( (uint8_t *)g_Usart4_Tx_Buf,(SPIFLASH_TJC_TFT+(SPIFLASH_PAGE_BASE_ADDR*i)),USART4_REC_LEN );/* */				
				uUart4DmaSend( (uint8_t *)g_Usart4_Tx_Buf,USART4_REC_LEN );	
				uSizeCount += USART4_REC_LEN;
			}else{
				SPI_Flash_Read( (uint8_t *)g_Usart4_Tx_Buf,(SPIFLASH_TJC_TFT+(SPIFLASH_PAGE_BASE_ADDR*i)),(uSize-uSizeCount) );/* */					
				uUart4DmaSend( (uint8_t *)g_Usart4_Tx_Buf,(uSize-uSizeCount) );	
			}
			
			OSTimeDlyHMSM(0, 0, 0, 280,OS_OPT_TIME_HMSM_STRICT,&err);
			
			OSSemPend( (OS_SEM *)&g_TjcUpgarde, UPGARDE_WAIT_TIME,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	           /*  */
			if( OS_ERR_NONE==err ){
				uUart4DataCopy( uReceiveData,g_Usart4_Rx_Buf,&g_Usart4_Rx_Sta );
				if( 5==uReceiveData[0] ){
					
				}else{
					OSTimeDlyHMSM(0, 0, 0, 300,OS_OPT_TIME_HMSM_STRICT,&err);
				}
			}else{
				return EXE_FAILED;
			}
//			OSTimeDlyHMSM(0, 0, 0, 300,OS_OPT_TIME_HMSM_STRICT,&err);	
		}
	}else{
		SPI_Flash_Read( (uint8_t *)g_Usart4_Tx_Buf,(SPIFLASH_TJC_TFT+(SPIFLASH_PAGE_BASE_ADDR*i)),uSize );/* */				
		uUart4DmaSend( (uint8_t *)g_Usart4_Tx_Buf,uSize );	
		
		OSSemPend( (OS_SEM *)&g_TjcUpgarde, UPGARDE_WAIT_TIME,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	           /*  */
		if( OS_ERR_NONE==err ){
			uUart4DataCopy( uReceiveData,g_Usart4_Rx_Buf,&g_Usart4_Rx_Sta );
		}else{
			return EXE_FAILED;
		}
//		OSTimeDlyHMSM(0, 0, 0, 300,OS_OPT_TIME_HMSM_STRICT,&err);
	}
	
	return EXE_SUCCEED;
}

//if( NULL!=strstr((const char *)puTarget,(const char *)"connect") ){	
//	sprintf( (char *)(uReplyData),"%c",0x1A );
//	uLength =  strlen((const char *)uReplyData);
//	sprintf( (char *)(uReplyData+uLength),"%c%c%c",0xFF,0xFF,0xFF );
//	uLength =  strlen((const char *)uReplyData);
//	
//	sprintf( (char *)(uReplyData+uLength),"%s%d%c%s%c%s%c%s%c%s%c%s%c%s","comok ",2,',',"30314-0",',',"TJC4832T135_011C",',',"30",',',"61744",',',"313E3401D97FD655",',',"8388608" );
//	uLength =  strlen((const char *)uReplyData);
//	sprintf( (char *)(uReplyData+uLength),"%c%c%c",0xFF,0xFF,0xFF );
//	uLength =  strlen((const char *)uReplyData);
//	
//	uUart1DmaSend( (uint8_t *)uReplyData,uLength );	
//}else if( NULL!=strstr((const char *)puTarget,(const char *)"whmi-wri") ){
//	sprintf( (char *)(uReplyData),"%s%d%c%s%c%s%c%s%c%s%c%s%c%s","comok ",2,',',"30314-0",',',"TJC4832T135_011C",',',"30",',',"61744",',',"313E3401D97FD655",',',"8388608" );
//	uLength =  strlen((const char *)uReplyData);		
//	sprintf( (char *)(uReplyData+uLength),"%c%c%c",0xFF,0xFF,0xFF );
//	uLength =  strlen((const char *)uReplyData);
//	
//	sprintf( (char *)(uReplyData+uLength),"%c",0x05 );
//	uLength =  strlen((const char *)uReplyData);
//	
//	uUart1DmaSend( (uint8_t *)uReplyData,uLength );	
//}else{
////		sprintf( (char *)uReplyData,"%c%c%c%c",0x1A,0xFF,0xFF,0xFF );
////		uLength =  strlen((const char *)uReplyData);
////		uUart1DmaSend( (uint8_t *)uReplyData,uLength );	
//	
//	sprintf( (char *)(uReplyData),"%c",0x05 );
//	uLength =  strlen((const char *)uReplyData);
//	
//	uUart1DmaSend( (uint8_t *)uReplyData,uLength );	
//}
