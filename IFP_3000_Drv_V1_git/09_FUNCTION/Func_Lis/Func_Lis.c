#include "Func_Lis.h"

uint8_t uLisSendTest( void )
{
	
	return EXE_SUCCEED;
}

uint8_t uLisFrameHeardLoad( uint8_t *uLisTemp,const GYK950E *pHistoryTemp )
{
	uint8_t uTemp1[128] = "H|\\^&|||IFP-3000|||||LIS||SRLT|E1394-97|";
	uint8_t uLen = 0;
	
	memcpy( uLisTemp,(const char *)uTemp1,strlen((const char *)uTemp1) );
	uLen = strlen( (const char *)uLisTemp );
	if( strlen((const char *)pHistoryTemp->uGyk_testtime)<sizeof(pHistoryTemp->uGyk_testtime) ){
		memcpy( uLisTemp+uLen,pHistoryTemp->uGyk_testtime,4 );
		uLen += 4;
		memcpy( uLisTemp+uLen,pHistoryTemp->uGyk_testtime+5,2 );
		uLen += 2;
		memcpy( uLisTemp+uLen,pHistoryTemp->uGyk_testtime+8,2 );
		uLen += 2;
		memcpy( uLisTemp+uLen,pHistoryTemp->uGyk_testtime+11,2 );
		uLen += 2;
		memcpy( uLisTemp+uLen,pHistoryTemp->uGyk_testtime+14,2 );
		uLen += 2;
		memcpy( uLisTemp+uLen,pHistoryTemp->uGyk_testtime+17,2 );
		return EXE_SUCCEED;
	}
	
	return EXE_FAILED;
}

uint8_t uLisFrameDensityResultdLoad( uint8_t *uLisTemp,const GYK950E *pHistoryTemp )
{
	uint8_t uTemp1[128] = "R|";
	uint8_t uLen = 0;
	uint8_t uDensityLen = 0;
	char* uRecIndex = NULL;
	uint8_t uTempArr[32] = {0}; 
	
	memcpy( uLisTemp,(const char *)uTemp1,strlen((const char *)uTemp1) );
	uLen = strlen( (const char *)uLisTemp );
	if( strlen((const char *)pHistoryTemp->uGyk_serialnumber)<sizeof(pHistoryTemp->uGyk_serialnumber) ){
		memcpy( uLisTemp+uLen,pHistoryTemp->uGyk_serialnumber+9,3 );   
//		sprintf( (char *)(uLisTemp+uLen),"%s%c",pHistoryTemp->uGyk_serialnumber,'|' );  /* ��󳤶�3 */
	}else{
		return EXE_FAILED;
	}
	uLen = strlen( (const char *)uLisTemp );
	if( strlen((const char *)pHistoryTemp->uGyk_report)<sizeof(pHistoryTemp->uGyk_report) ){
		sprintf( (char *)(uLisTemp+uLen),"%c%s%c",'|',pHistoryTemp->uGyk_report,'|' );
	}else{
		return EXE_FAILED;
	}
	uLen = strlen( (const char *)uLisTemp );
	if( strlen((const char *)pHistoryTemp->uGyk_densityresult)<sizeof(pHistoryTemp->uGyk_densityresult) ){
		uDensityLen = strlen((const char *)pHistoryTemp->uGyk_densityresult);
		if( 0xA1==pHistoryTemp->uGyk_densityresult[uDensityLen-2] ){
			memcpy( (char *)(uLisTemp+uLen),(const char *)pHistoryTemp->uGyk_densityresult,uDensityLen-2);
			uDensityLen = strlen((const char *)uLisTemp);
			sprintf( (char *)(uLisTemp+uDensityLen),"%c",'|' );
		}else{
			sprintf( (char *)(uLisTemp+uLen),"%s%c",pHistoryTemp->uGyk_densityresult,'|' );
		}
		
	}else{
		return EXE_FAILED;
	}	
	uLen = strlen( (const char *)uLisTemp );
	if( strlen((const char *)pHistoryTemp->uGyk_printunit)<sizeof(pHistoryTemp->uGyk_printunit) ){
		sprintf( (char *)(uLisTemp+uLen),"%s%c",pHistoryTemp->uGyk_printunit,'|' );
	}else{
		return EXE_FAILED;
	}
	uLen = strlen( (const char *)uLisTemp );
	if( strlen((const char *)pHistoryTemp->uGyk_reference)<sizeof(pHistoryTemp->uGyk_reference) ){
		memcpy( uTempArr,pHistoryTemp->uGyk_reference,sizeof(pHistoryTemp->uGyk_reference) );
		uRecIndex = strstr( (const char *)uTempArr,"~" );
		if( NULL!=uRecIndex ){
			*uRecIndex = '^';
		}
		sprintf( (char *)(uLisTemp+uLen),"%s%c",uTempArr,'|' );
		
	}else{
		return EXE_FAILED;
	}	
	
	uLen = strlen( (const char *)uLisTemp );
	sprintf( (char *)(uLisTemp+uLen),"%s","|N|F||||" );
	
	uLen = strlen( (const char *)uLisTemp );
	if( strlen((const char *)pHistoryTemp->uGyk_testtime)<sizeof(pHistoryTemp->uGyk_testtime) ){
		memcpy( uLisTemp+uLen,pHistoryTemp->uGyk_testtime,4 );
		uLen += 4;
		memcpy( uLisTemp+uLen,pHistoryTemp->uGyk_testtime+5,2 );
		uLen += 2;
		memcpy( uLisTemp+uLen,pHistoryTemp->uGyk_testtime+8,2 );
		uLen += 2;
		memcpy( uLisTemp+uLen,pHistoryTemp->uGyk_testtime+11,2 );
		uLen += 2;
		memcpy( uLisTemp+uLen,pHistoryTemp->uGyk_testtime+14,2 );
		uLen += 2;
		memcpy( uLisTemp+uLen,pHistoryTemp->uGyk_testtime+17,2 ); 
	}else{
		return EXE_FAILED;
	}
	
	uLen = strlen( (const char *)uLisTemp );	
	sprintf( (char *)(uLisTemp+uLen),"%c%s",'|',"IFP-3000" );
	
	return EXE_SUCCEED;
}

uint8_t uLisFrameTailLoad( uint8_t *uLisTemp,const GYK950E *pHistoryTemp )
{
	uint8_t uTemp1[128] = "L|1|N";
//	uint8_t uLen = 0;
	
	memcpy( uLisTemp,(const char *)uTemp1,strlen((const char *)uTemp1) );
//	uLen = strlen( (const char *)uLisTemp );
	
	return EXE_SUCCEED;
}

//uint8_t uLisFramePatientLoad( uint8_t *uLisTemp,const GYK950E *pHistoryTemp,USER_MORE_INFO* pUserMore )
uint8_t uLisFramePatientLoad( uint8_t *uLisTemp,const GYK950E *pHistoryTemp )
{
	uint8_t uTemp1[128] = "P|1||||";//"P|1||||������|||��||||||100^��";
//	uint8_t uTemp1[128] = "P|1||||������|||��||||||100^��";
	
	uint8_t uLen = 0;
	
	memcpy( uLisTemp,(const char *)uTemp1,strlen((const char *)uTemp1) );
	uLen = strlen( (const char *)uLisTemp );
	if( strlen((const char *)pHistoryTemp->uGyk_username)<sizeof(pHistoryTemp->uGyk_username) ){
		sprintf( (char *)(uLisTemp+uLen),"%s%s",pHistoryTemp->uGyk_username,"|||" );
	}else{
		sprintf( (char *)(uLisTemp),"%s","P|1||||δ֪|||U||||||0^��" );
		return EXE_SUCCEED;
	}	
	
	uLen = strlen( (const char *)uLisTemp );
	if( strlen((const char *)pHistoryTemp->uGyk_usersex)<sizeof(pHistoryTemp->uGyk_usersex) ){
		if( 'F'==pHistoryTemp->uGyk_usersex[0] ){
			sprintf( (char *)(uLisTemp+uLen),"%s%s","F","||||||" );
		}else{
			sprintf( (char *)(uLisTemp+uLen),"%s%s","M","||||||" );
		}		
	}else{
		sprintf( (char *)(uLisTemp),"%s","P|1||||δ֪|||U||||||0^��" );
		return EXE_SUCCEED;
	}
	
	uLen = strlen( (const char *)uLisTemp );
	if( 0!=pHistoryTemp->uGyk_userage[0] ){	
		sprintf( (char *)(uLisTemp+uLen),"%s%s",pHistoryTemp->uGyk_userage,"^��" );			
	}else{
		sprintf( (char *)(uLisTemp),"%s","P|1||||δ֪|||U||||||0^��" );
		return EXE_SUCCEED;
	}	
	
	return EXE_SUCCEED;
}

uint8_t uLisFrameOUnitLoad( uint8_t *uLisTemp,const GYK950E *pHistoryTemp )
{
	uint8_t uTemp1[128] = "O|1|";//"O|1|20201229001^28^1^1^N||CRP\\SAA|R|2020-12-29|||||||||0||||||||||F";
	uint8_t uLen = 0;
	
	memcpy( uLisTemp,(const char *)uTemp1,strlen((const char *)uTemp1) );
	uLen = strlen( (const char *)uLisTemp );
	if( strlen((const char *)pHistoryTemp->uGyk_serialnumber)<sizeof(pHistoryTemp->uGyk_serialnumber) ){
		sprintf( (char *)(uLisTemp+uLen),"%s%s",pHistoryTemp->uGyk_serialnumber,"||" );
	}else{
		return EXE_FAILED;
	}	
	
	uLen = strlen( (const char *)uLisTemp );
	if( strlen((const char *)pHistoryTemp->uGyk_report)<sizeof(pHistoryTemp->uGyk_report) ){
		sprintf( (char *)(uLisTemp+uLen),"%s%s",pHistoryTemp->uGyk_report,"|R|" );
	}else{
		return EXE_FAILED;
	}
	
	uLen = strlen( (const char *)uLisTemp );
	if( strlen((const char *)pHistoryTemp->uGyk_testtime)<sizeof(pHistoryTemp->uGyk_testtime) ){
		memcpy( uLisTemp+uLen,pHistoryTemp->uGyk_testtime,10 );
	}else{
		return EXE_FAILED;
	}
	
	uLen = strlen( (const char *)uLisTemp );
	if( EN_ON==gp_stuConfigFile->uCutEnCu ){
		if( 0==strncmp((const char *)"Whole  blood",(const char *)pHistoryTemp->uGyk_sampletype,sizeof(pHistoryTemp->uGyk_sampletype)) ){
			//sprintf( (char *)(uLisTemp+uLen),"%s","|||||||||0|1|2|3|4|5|6|7|8|9|F|1|2|3|4|5" );
			sprintf( (char *)(uLisTemp+uLen),"%s","|||||||||6|1|2|3|4|5|6|7|8|9|F|1|2|3|4|5" );
		}else if( 0==strncmp((const char *)"Serum/Plasma",(const char *)pHistoryTemp->uGyk_sampletype,sizeof(pHistoryTemp->uGyk_sampletype)) ){				
			sprintf( (char *)(uLisTemp+uLen),"%s","|||||||||2|1|2|3|4|5|6|7|8|9|F|1|2|3|4|5" );
		}else{
			sprintf( (char *)(uLisTemp+uLen),"%s","|||||||||6|1|2|3|4|5|6|7|8|9|F|1|2|3|4|5" );
		}
	}else{
		if( 0==strncmp((const char *)"ȫѪ",(const char *)pHistoryTemp->uGyk_sampletype,sizeof(pHistoryTemp->uGyk_sampletype)) ){
			//sprintf( (char *)(uLisTemp+uLen),"%s","|||||||||0|1|2|3|4|5|6|7|8|9|F|1|2|3|4|5" );
			sprintf( (char *)(uLisTemp+uLen),"%s","|||||||||6|1|2|3|4|5|6|7|8|9|F|1|2|3|4|5" );
		}else if( 0==strncmp((const char *)"Ѫ��/Ѫ��",(const char *)pHistoryTemp->uGyk_sampletype,sizeof(pHistoryTemp->uGyk_sampletype)) ){				
			sprintf( (char *)(uLisTemp+uLen),"%s","|||||||||2|1|2|3|4|5|6|7|8|9|F|1|2|3|4|5" );
		}else{
			sprintf( (char *)(uLisTemp+uLen),"%s","|||||||||6|1|2|3|4|5|6|7|8|9|F|1|2|3|4|5" );
		}
	}	

	return EXE_SUCCEED;
}

uint8_t uLisSendHistorySingleton( int16_t iUploaData )
{
	
	return EXE_SUCCEED;
}

uint8_t uLisSendHistoryPage( const int16_t iPage,uint8_t uOverLoad )
{

	uint8_t i = 0;
//	uint8_t j = 0;
	int16_t iRecUploaData = 0;	
	GYK950E* pHistoryMyForm[3] = { 0,0,0 };
	uint8_t uRecErrorTemp = 0;
	static char uRecSerial[20] = {0};
	
	iRecUploaData = iPage;
	
	if( WIFI_CONNEST_DISLINE==g_uWifiConnect ){
//		if( EXE_FAILED==uWifiConnentEnv() ){                                                                       /* ���ȼ��������WIFI���ܺ��� */
			uTjc4832tSetPage( TJC_WARN_PAGE );        /*����Ϊ*/
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Network Disconnect" );			
			return EXE_FAILED;
//		}
	}
	
	if( WIFI_CONNEST_ONLINE==g_uWifiConnect ){
		for( i=0;i<(sizeof(pHistoryMyForm)/sizeof(GYK950E*));i++ ){
			pHistoryMyForm[i] = calloc( 1,sizeof(GYK950E) );
			if( NULL==pHistoryMyForm[i] ){
				uRecErrorTemp = EXE_FAILED;
			}	
		}
		
		if( EXE_FAILED==uRecErrorTemp ){
			for( i=0;i<(sizeof(pHistoryMyForm)/sizeof(GYK950E*));i++ ){
				if( NULL!=pHistoryMyForm[i] ){
					free( pHistoryMyForm[i] );
				}	
			}
			return uRecErrorTemp;
		}		
	
		SPI_Flash_Read( (uint8_t *)pHistoryMyForm[0],(SPIFLASH_DENSITY_BASE_ADDR+(iRecUploaData*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );
		
		if( uOverLoad ){              /* Ϊ0ʱ �����ϴ� */
			if( 0==strncmp((const char *)pHistoryMyForm[0]->uGyk_serialnumber,(const char *)uRecSerial,sizeof(uRecSerial)) ){
				uTjc4832tSetPage( TJC_PROMPTER_PAGE );        /*����Ϊ*/
				if( EN_ON==gp_stuConfigFile->uCutEnCu ){
					uTjc4832tSetLableValue( TJC_PROMPTER_PAGE,PROMPTER_ID_TXT,(uint8_t *)"Uploaded?" );	
				}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
					uTjc4832tSetLableValue( TJC_PROMPTER_PAGE,PROMPTER_ID_TXT,(uint8_t *)"�ϴ�?" );                                           
				}else{
					uTjc4832tSetLableValue( TJC_PROMPTER_PAGE,PROMPTER_ID_TXT,(uint8_t *)"Invalid" ); 
				}	
				
				for( i=0;i<(sizeof(pHistoryMyForm)/sizeof(GYK950E*));i++ ){
					if( NULL!=pHistoryMyForm[i] ){
						free( pHistoryMyForm[i] );
					}	
				}
				return EXE_FAILED;
			}
		}
		
		switch( pHistoryMyForm[0]->uGyk_children_num ){
			case 1:
				uLisFrameDataPackSend( pHistoryMyForm,pHistoryMyForm[0]->uGyk_children_num );
				break;
			case 2:
				if( 1==pHistoryMyForm[0]->uGyk_children_index ){
					iRecUploaData++;
					SPI_Flash_Read( (uint8_t *)pHistoryMyForm[1],(SPIFLASH_DENSITY_BASE_ADDR+(iRecUploaData*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );
				}else if( 2==pHistoryMyForm[0]->uGyk_children_index ){
					iRecUploaData--;
					SPI_Flash_Read( (uint8_t *)pHistoryMyForm[1],(SPIFLASH_DENSITY_BASE_ADDR+(iRecUploaData*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );
				}else{
					uLisFrameDataPackSend( pHistoryMyForm,1 );
				}
				if( 0==strncmp((const char *)pHistoryMyForm[0]->uGyk_serialnumber,(const char *)pHistoryMyForm[1]->uGyk_serialnumber,sizeof(pHistoryMyForm[0]->uGyk_serialnumber)) ){
					uLisFrameDataPackSend( pHistoryMyForm,pHistoryMyForm[0]->uGyk_children_num );
				}else{
#if DEBUH_UART1		
//	#if PRIVATE_UART1
					myprintf( "uLisSendHistoryError \r\n" );
//	#endif
#endif
				}
				break;
			case 3:
				if( 1==pHistoryMyForm[0]->uGyk_children_index ){
					iRecUploaData++;
					SPI_Flash_Read( (uint8_t *)pHistoryMyForm[1],(SPIFLASH_DENSITY_BASE_ADDR+(iRecUploaData*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );
					iRecUploaData++;
					SPI_Flash_Read( (uint8_t *)pHistoryMyForm[2],(SPIFLASH_DENSITY_BASE_ADDR+(iRecUploaData*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );
				}else if( 2==pHistoryMyForm[0]->uGyk_children_index ){
					iRecUploaData--;
					SPI_Flash_Read( (uint8_t *)pHistoryMyForm[1],(SPIFLASH_DENSITY_BASE_ADDR+(iRecUploaData*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );
					iRecUploaData = iRecUploaData+2;
					SPI_Flash_Read( (uint8_t *)pHistoryMyForm[2],(SPIFLASH_DENSITY_BASE_ADDR+(iRecUploaData*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );
				}else if( 3==pHistoryMyForm[0]->uGyk_children_index ){
					iRecUploaData = iRecUploaData-2;
					SPI_Flash_Read( (uint8_t *)pHistoryMyForm[2],(SPIFLASH_DENSITY_BASE_ADDR+(iRecUploaData*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );
					iRecUploaData++;
					SPI_Flash_Read( (uint8_t *)pHistoryMyForm[1],(SPIFLASH_DENSITY_BASE_ADDR+(iRecUploaData*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );
	
				}else{
					uLisFrameDataPackSend( pHistoryMyForm,1 );
				}
				if( (0==strncmp((const char *)pHistoryMyForm[0]->uGyk_serialnumber,(const char *)pHistoryMyForm[1]->uGyk_serialnumber,sizeof(pHistoryMyForm[0]->uGyk_serialnumber)))&&
					(0==strncmp((const char *)pHistoryMyForm[1]->uGyk_serialnumber,(const char *)pHistoryMyForm[2]->uGyk_serialnumber,sizeof(pHistoryMyForm[0]->uGyk_serialnumber))) ){
					uLisFrameDataPackSend( pHistoryMyForm,pHistoryMyForm[0]->uGyk_children_num );
				}else{
#if DEBUH_UART1		
//	#if PRIVATE_UART1
					myprintf( "uLisSendHistoryError \r\n" );
//	#endif
#endif				
				}
				break;
			
			default:
				break;
		}
		
		strncpy( uRecSerial,(const char *)pHistoryMyForm[0]->uGyk_serialnumber,sizeof(pHistoryMyForm[0]->uGyk_serialnumber) );
		
		if( 0==uOverLoad ){                                               /* �ر���ʾ�� */
			uDisplayHistoryDataSpecifiedPage( g_uRecordHistoryPage );	                      
		}
		
		for( i=0;i<(sizeof(pHistoryMyForm)/sizeof(GYK950E*));i++ ){
			if( NULL!=pHistoryMyForm[i] ){
				free( pHistoryMyForm[i] );
			}	
		}			
		return EXE_SUCCEED;
		
	}
	
	return EXE_FAILED;
}


uint8_t uLisSendHistory( void )
{
	uint8_t i = 0;
//	uint8_t j = 0;
	static int16_t l_iRecUploaData = 0;	
	GYK950E* pHistoryMyForm[3] = { 0,0,0 };
	uint8_t uRecErrorTemp = 0;

	if( WIFI_CONNEST_ONLINE==g_uWifiConnect ){
		if( l_iRecUploaData<(g_projectSerial.history_count-1) ){
			for( i=0;i<(sizeof(pHistoryMyForm)/sizeof(GYK950E*));i++ ){
				pHistoryMyForm[i] = calloc( 1,sizeof(GYK950E) );
				if( NULL==pHistoryMyForm[i] ){
					uRecErrorTemp = EXE_FAILED;
				}	
			}
			
			if( EXE_FAILED==uRecErrorTemp ){
				for( i=0;i<(sizeof(pHistoryMyForm)/sizeof(GYK950E*));i++ ){
					if( NULL!=pHistoryMyForm[i] ){
						free( pHistoryMyForm[i] );
					}	
				}
				return uRecErrorTemp;
			}
			
			if( (0==l_iRecUploaData) ){ 
				SPI_Flash_Read( (uint8_t *)pHistoryMyForm[0],(SPIFLASH_DENSITY_BASE_ADDR+((g_projectSerial.history_count-1)*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );
				l_iRecUploaData = (g_projectSerial.history_count-1);
			}else{	
				l_iRecUploaData++;
				SPI_Flash_Read( (uint8_t *)pHistoryMyForm[0],(SPIFLASH_DENSITY_BASE_ADDR+(l_iRecUploaData*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );
			}	
			
			switch( pHistoryMyForm[0]->uGyk_children_num ){
				case 1:
					uLisFrameDataPackSend( pHistoryMyForm,pHistoryMyForm[0]->uGyk_children_num );
					break;
				case 2:
					if( 1==pHistoryMyForm[0]->uGyk_children_index ){
						l_iRecUploaData++;
						SPI_Flash_Read( (uint8_t *)pHistoryMyForm[1],(SPIFLASH_DENSITY_BASE_ADDR+(l_iRecUploaData*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );
					}else if( 2==pHistoryMyForm[0]->uGyk_children_index ){
						l_iRecUploaData--;
						SPI_Flash_Read( (uint8_t *)pHistoryMyForm[1],(SPIFLASH_DENSITY_BASE_ADDR+(l_iRecUploaData*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );
						l_iRecUploaData++;
					}else{
						uLisFrameDataPackSend( pHistoryMyForm,1 );
					}
					if( 0==strncmp((const char *)pHistoryMyForm[0]->uGyk_serialnumber,(const char *)pHistoryMyForm[1]->uGyk_serialnumber,sizeof(pHistoryMyForm[0]->uGyk_serialnumber)) ){
						uLisFrameDataPackSend( pHistoryMyForm,pHistoryMyForm[0]->uGyk_children_num );
					}else{
#if DEBUH_UART1		
//	#if PRIVATE_UART1
						myprintf( "uLisSendHistoryError \r\n" );
//	#endif
#endif
					}
					break;
				case 3:
					if( 1==pHistoryMyForm[0]->uGyk_children_index ){
						l_iRecUploaData++;
						SPI_Flash_Read( (uint8_t *)pHistoryMyForm[1],(SPIFLASH_DENSITY_BASE_ADDR+(l_iRecUploaData*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );
						l_iRecUploaData++;
						SPI_Flash_Read( (uint8_t *)pHistoryMyForm[2],(SPIFLASH_DENSITY_BASE_ADDR+(l_iRecUploaData*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );
					}else if( 2==pHistoryMyForm[0]->uGyk_children_index ){
						l_iRecUploaData--;
						SPI_Flash_Read( (uint8_t *)pHistoryMyForm[1],(SPIFLASH_DENSITY_BASE_ADDR+(l_iRecUploaData*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );
						l_iRecUploaData = l_iRecUploaData+2;
						SPI_Flash_Read( (uint8_t *)pHistoryMyForm[2],(SPIFLASH_DENSITY_BASE_ADDR+(l_iRecUploaData*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );
					}else if( 3==pHistoryMyForm[0]->uGyk_children_index ){
						l_iRecUploaData = l_iRecUploaData-2;
						SPI_Flash_Read( (uint8_t *)pHistoryMyForm[2],(SPIFLASH_DENSITY_BASE_ADDR+(l_iRecUploaData*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );
						l_iRecUploaData++;
						SPI_Flash_Read( (uint8_t *)pHistoryMyForm[1],(SPIFLASH_DENSITY_BASE_ADDR+(l_iRecUploaData*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );
						l_iRecUploaData++;
					}else{
						uLisFrameDataPackSend( pHistoryMyForm,1 );
					}
					if( (0==strncmp((const char *)pHistoryMyForm[0]->uGyk_serialnumber,(const char *)pHistoryMyForm[1]->uGyk_serialnumber,sizeof(pHistoryMyForm[0]->uGyk_serialnumber)))&&
						(0==strncmp((const char *)pHistoryMyForm[1]->uGyk_serialnumber,(const char *)pHistoryMyForm[2]->uGyk_serialnumber,sizeof(pHistoryMyForm[0]->uGyk_serialnumber))) ){
						uLisFrameDataPackSend( pHistoryMyForm,pHistoryMyForm[0]->uGyk_children_num );
					}else{
#if DEBUH_UART1		
//	#if PRIVATE_UART1
						myprintf( "uLisSendHistoryError \r\n" );
//	#endif
#endif				
					}
					break;
				
				default:
					break;
			}
			
			
			for( i=0;i<(sizeof(pHistoryMyForm)/sizeof(GYK950E*));i++ ){
				if( NULL!=pHistoryMyForm[i] ){
					free( pHistoryMyForm[i] );
				}	
			}			
			return EXE_SUCCEED;
		}
	}
	
	return EXE_FAILED;
}

uint8_t uLisFrameDataPackSend( GYK950E* pHistoryMyFormTemp[3],uint8_t uChildrenNumTemp )
{
	uint8_t i = 0;
	uint8_t j = 0;
	uint8_t uRecErr = 0;
	uint8_t uLIsArrTemp[USART2_REC_LEN] = {0};
	
	vClearWifiBuffer();                                               /* ���WIFI���� */

	sprintf( (char *)uLIsArrTemp,"%c",LIS_ENQ );
	if( strlen((const char *)uLIsArrTemp)<sizeof(uLIsArrTemp) ){
		uWifiStationSendOriginalData( uLIsArrTemp,strlen((const char *)uLIsArrTemp) );
	}
	memset( uLIsArrTemp,0,sizeof(uLIsArrTemp) );
	
	if( EXE_SUCCEED!=uLisFrameAck() ){
		return EXE_FAILED;
	}
	
	for( i=0;i<8;i++ ){			
		switch( i ){
			case 0:
				break;
			case 1:
				uRecErr = uLisFrameHeardLoad( uLIsArrTemp,pHistoryMyFormTemp[0] );
				if( EXE_SUCCEED!=uRecErr ){
					return uRecErr;
				}
				uLisFrameDataPack( i,(uint8_t *)uLIsArrTemp,strlen((const char *)uLIsArrTemp) );
				if( EXE_SUCCEED!=uLisFrameAck() ){
					return EXE_FAILED;
				}
				memset( uLIsArrTemp,0,sizeof(uLIsArrTemp) );
				break;
			case 2:
				uRecErr = uLisFramePatientLoad( uLIsArrTemp,pHistoryMyFormTemp[0] );
				if( EXE_SUCCEED!=uRecErr ){
					return uRecErr;
				}
				uLisFrameDataPack( i,(uint8_t *)uLIsArrTemp,strlen((const char *)uLIsArrTemp) );
				if( EXE_SUCCEED!=uLisFrameAck() ){
					return EXE_FAILED;
				}
				memset( uLIsArrTemp,0,sizeof(uLIsArrTemp) );
				break;		
			case 3:
				uRecErr = uLisFrameOUnitLoad( uLIsArrTemp,pHistoryMyFormTemp[0] );
				if( EXE_SUCCEED!=uRecErr ){
					return uRecErr;
				}
				uLisFrameDataPack( i,(uint8_t *)uLIsArrTemp,strlen((const char *)uLIsArrTemp) );
				if( EXE_SUCCEED!=uLisFrameAck() ){
					return EXE_FAILED;
				}
				memset( uLIsArrTemp,0,sizeof(uLIsArrTemp) );
				break;	
			case 4:
				for( j=0;j<uChildrenNumTemp;j++ ){
					uRecErr = uLisFrameDensityResultdLoad( uLIsArrTemp,pHistoryMyFormTemp[j] );
					if( EXE_SUCCEED!=uRecErr ){
						return uRecErr;
					}
					uLisFrameDataPack( i+j,(uint8_t *)uLIsArrTemp,strlen((const char *)uLIsArrTemp) );
					if( EXE_SUCCEED!=uLisFrameAck() ){
						return EXE_FAILED;
					}
					memset( uLIsArrTemp,0,sizeof(uLIsArrTemp) );
				}			
				break;
			case 5:
				uRecErr = uLisFrameTailLoad( uLIsArrTemp,pHistoryMyFormTemp[0] );
				if( EXE_SUCCEED!=uRecErr ){
					return uRecErr;
				}
				uLisFrameDataPack( i+j,(uint8_t *)uLIsArrTemp,strlen((const char *)uLIsArrTemp) );
				if( EXE_SUCCEED!=uLisFrameAck() ){
					return EXE_FAILED;
				}
				memset( uLIsArrTemp,0,sizeof(uLIsArrTemp) );
				break;
			case 6:
				break;
			case 7:
				break;
			default:
				
				break;
		}

	}
	
	sprintf( (char *)uLIsArrTemp,"%c",LIS_EOT );
	if( strlen((const char *)uLIsArrTemp)<sizeof(uLIsArrTemp) ){
		uWifiStationSendOriginalData( uLIsArrTemp,strlen((const char *)uLIsArrTemp) );
	}
	
	return EXE_SUCCEED;
}

//uint8_t uLisFrameDataPackSend( GYK950E* pHistoryMyFormTemp[3],uint8_t uChildrenNumTemp )
//{
//	uint8_t i = 0;
//	uint8_t j = 0;
//	uint8_t uRecErr = 0;
//	uint8_t uLIsArrTemp[USART2_REC_LEN] = {0};
//	
//	vClearWifiBuffer();                                               /* ���WIFI���� */

//	uWifiTransparentSendDataChar( LIS_ENQ );                          /* �������� */	
//	if( EXE_SUCCEED!=uLisFrameAck() ){
//		return EXE_FAILED;
//	}
//	
//	for( i=0;i<8;i++ ){			
//		switch( i ){
//			case 0:
//				break;
//			case 1:
//				uRecErr = uLisFrameHeardLoad( uLIsArrTemp,pHistoryMyFormTemp[0] );
//				if( EXE_SUCCEED!=uRecErr ){
//					return uRecErr;
//				}
//				uLisFrameDataPack( i,(uint8_t *)uLIsArrTemp,strlen((const char *)uLIsArrTemp) );
//				if( EXE_SUCCEED!=uLisFrameAck() ){
//					return EXE_FAILED;
//				}
//				memset( uLIsArrTemp,0,sizeof(uLIsArrTemp) );
//				break;
//			case 2:
//				uRecErr = uLisFramePatientLoad( uLIsArrTemp,pHistoryMyFormTemp[0],&g_stuUserMoreInfo );
//				if( EXE_SUCCEED!=uRecErr ){
//					return uRecErr;
//				}
//				uLisFrameDataPack( i,(uint8_t *)uLIsArrTemp,strlen((const char *)uLIsArrTemp) );
//				if( EXE_SUCCEED!=uLisFrameAck() ){
//					return EXE_FAILED;
//				}
//				memset( uLIsArrTemp,0,sizeof(uLIsArrTemp) );
//				break;		
//			case 3:
//				uRecErr = uLisFrameOUnitLoad( uLIsArrTemp,pHistoryMyFormTemp[0] );
//				if( EXE_SUCCEED!=uRecErr ){
//					return uRecErr;
//				}
//				uLisFrameDataPack( i,(uint8_t *)uLIsArrTemp,strlen((const char *)uLIsArrTemp) );
//				if( EXE_SUCCEED!=uLisFrameAck() ){
//					return EXE_FAILED;
//				}
//				memset( uLIsArrTemp,0,sizeof(uLIsArrTemp) );
//				break;	
//			case 4:
//				for( j=0;j<uChildrenNumTemp;j++ ){
//					uRecErr = uLisFrameDensityResultdLoad( uLIsArrTemp,pHistoryMyFormTemp[j] );
//					if( EXE_SUCCEED!=uRecErr ){
//						return uRecErr;
//					}
//					uLisFrameDataPack( i+j,(uint8_t *)uLIsArrTemp,strlen((const char *)uLIsArrTemp) );
//					if( EXE_SUCCEED!=uLisFrameAck() ){
//						return EXE_FAILED;
//					}
//					memset( uLIsArrTemp,0,sizeof(uLIsArrTemp) );
//				}			
//				break;
//			case 5:
//				uRecErr = uLisFrameTailLoad( uLIsArrTemp,pHistoryMyFormTemp[0] );
//				if( EXE_SUCCEED!=uRecErr ){
//					return uRecErr;
//				}
//				uLisFrameDataPack( i+j,(uint8_t *)uLIsArrTemp,strlen((const char *)uLIsArrTemp) );
//				if( EXE_SUCCEED!=uLisFrameAck() ){
//					return EXE_FAILED;
//				}
//				memset( uLIsArrTemp,0,sizeof(uLIsArrTemp) );
//				break;
//			case 6:
//				break;
//			case 7:
//				break;
//			default:
//				
//				break;
//		}

//	}
//	
//	uWifiTransparentSendDataChar( LIS_EOT );                          /* �������� */
//	
//	return EXE_SUCCEED;
//}

uint8_t uLisFrameDataPack( uint8_t uFnData,uint8_t* uFrameData,uint32_t uFrameLen )
{
	uint32_t i = 0;
	uint32_t uCrNum = LIS_CR+LIS_ETX;
	uint8_t uCrNumOne = 0;
	uint8_t uCrNumTwo = 0;
	uint8_t uLIsArrTemp[1024] = {0};
	uint32_t uRec = 0;
	
	/* ����STX ������ʼλ */
	sprintf( (char *)uLIsArrTemp,"%c",LIS_STX );
	uRec = strlen( (const char *)uLIsArrTemp );
	
	/* FN ���͵����� */
	sprintf( (char *)(uLIsArrTemp+uRec),"%c",ASCII_ZERO+uFnData );
	uRec = strlen( (const char *)uLIsArrTemp );		
	uFnData += uFnData;
	
	/* Frame ���͵����� */
	for( i=0;i<uFrameLen;i++ ){
		uCrNum += *(uFrameData+i);
	}		
	sprintf( (char *)(uLIsArrTemp+uRec),"%s",uFrameData );
	uRec = strlen( (const char *)uLIsArrTemp );	
	
	/* ����CR ֡���ݽ���λ */
	sprintf( (char *)(uLIsArrTemp+uRec),"%c",LIS_CR );
	uRec = strlen( (const char *)uLIsArrTemp );
	
	/* ����EXT ���ݽ���λ */
	sprintf( (char *)(uLIsArrTemp+uRec),"%c",LIS_ETX );
	uRec = strlen( (const char *)uLIsArrTemp );
	
	uCrNum %= LIS_MODULUS;
	
	uCrNumTwo = (uCrNum&0xF0)>>4;   /* �ȷ���λ */
	uCrNumOne = (uCrNum&0x0F);	    /* �󷢵�λ */
	
	/* ����Ч��Ͷ�256ȡģ �ȷ���λ �󷢵�λ */	
	if( uCrNumTwo>9 ){
		sprintf( (char *)(uLIsArrTemp+uRec),"%c",ASCII_A1+uCrNumTwo );
		uRec = strlen( (const char *)uLIsArrTemp );
	}else{
		sprintf( (char *)(uLIsArrTemp+uRec),"%c",ASCII_ZERO+uCrNumTwo );
		uRec = strlen( (const char *)uLIsArrTemp );
	}	
	if( uCrNumOne>9 ){
		sprintf( (char *)(uLIsArrTemp+uRec),"%c",ASCII_A1+uCrNumOne );
		uRec = strlen( (const char *)uLIsArrTemp );
	}else{
		sprintf( (char *)(uLIsArrTemp+uRec),"%c", ASCII_ZERO+uCrNumOne );
		uRec = strlen( (const char *)uLIsArrTemp );
	}
	
	/* �������ݽ����س����� */	
	sprintf( (char *)(uLIsArrTemp+uRec),"%c%c", LIS_CR,LIS_LF );
	uRec = strlen( (const char *)uLIsArrTemp );
	
	
	if( strlen((const char *)uLIsArrTemp)<sizeof(uLIsArrTemp) ){
		uWifiStationSendOriginalData( uLIsArrTemp,strlen((const char *)uLIsArrTemp) );
	}
	return EXE_SUCCEED;
}

//uint8_t uLisFrameDataPack( uint8_t uFnData,uint8_t* uFrameData,uint32_t uFrameLen )
//{
//	uint32_t i = 0;
//	uint32_t uCrNum = LIS_CR+LIS_ETX;
//	uint8_t uCrNumOne = 0;
//	uint8_t uCrNumTwo = 0;
//	
//	/* ����STX ������ʼλ */
//	uWifiTransparentSendDataChar( LIS_STX );                          /* �������� */		
//	
//	/* FN ���͵����� */
//	uWifiTransparentSendDataChar( ASCII_ZERO+uFnData );                          /* �������� */		
//	uFnData += uFnData;
//	
//	/* Frame ���͵����� */
//	for( i=0;i<uFrameLen;i++ ){
//		uCrNum += *(uFrameData+i);
//	}		
//	uWifiTransparentSendOriginalData( uFrameData,uFrameLen );
//	
//	/* ����CR ֡���ݽ���λ */
//	uWifiTransparentSendDataChar( LIS_CR );                          /* �������� 0D */	
//	
//	/* ����EXT ���ݽ���λ */
//	uWifiTransparentSendDataChar( LIS_ETX );  
//	
//	uCrNum %= LIS_MODULUS;
//	
//	uCrNumTwo = (uCrNum&0xF0)>>4;   /* �ȷ���λ */
//	uCrNumOne = (uCrNum&0x0F);	    /* �󷢵�λ */
//	
//	/* ����Ч��Ͷ�256ȡģ �ȷ���λ �󷢵�λ */	
//	if( uCrNumTwo>9 ){
//		uWifiTransparentSendDataChar( ASCII_A1+uCrNumTwo );                          /* �������� */
//	}else{
//		uWifiTransparentSendDataChar( ASCII_ZERO+uCrNumTwo );                          /* �������� */
//	}	
//	if( uCrNumOne>9 ){
//		uWifiTransparentSendDataChar( ASCII_A1+uCrNumOne );                          /* �������� */
//	}else{
//		uWifiTransparentSendDataChar( ASCII_ZERO+uCrNumOne );                          /* �������� */
//	}
//	
//	/* �������ݽ����س����� */	
//	uWifiTransparentSendDataChar( LIS_CR );                          /* �������� */
//	uWifiTransparentSendDataChar( LIS_LF );                          /* �������� */
//	
//	return EXE_SUCCEED;
//}

uint8_t uLisFrameAck( void )
{	
	OS_ERR err = OS_ERR_NONE;
	uint8_t i = 0;
	uint8_t uWifiArrTemp[USART2_REC_LEN] = {0};
	
	while( i<3 ){
		OSTimeDlyHMSM(0, 0, 0, 50,OS_OPT_TIME_HMSM_STRICT,&err);                                                /* ����30ms */
		vCopyWifiBuffer( uWifiArrTemp,USART2_REC_LEN );                                                                        /* COPY���� */
		if( 0!=uWifiArrTemp[0] ){
			break;
		}
		i++;		
	}	
	vClearWifiBuffer();                                                                                         /* ���WIFI���� */
	
	if( NULL!=strstr((const char *)uWifiArrTemp,(const char *)"\6") ){
		return EXE_SUCCEED;
	}else{
//		return EXE_FAILED;
		return EXE_SUCCEED;
	}		
}
