#include "Func_GY_K950E.h"

uint8_t GyK950eTestForm( void )
{
	OS_ERR err;
	GYK950E* ptestMyForm = NULL;

	ptestMyForm = calloc( 1,sizeof(GYK950E) );
	if( NULL==ptestMyForm ){
		return EXE_FAILED;
	}
	
	/*����Ĳ�������Ҫ���*/
	sprintf( (char *)ptestMyForm->uGyk_testtime,"%4d-%2d-%2d %2d:%2d:%2d",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec );	
	sprintf( (char *)ptestMyForm->uGyk_printname,"%s",(const char *)"Sichuan Xincheng Biological Co., LTD" );
	sprintf( (char *)ptestMyForm->uGyk_report,"%s",(const char *)"Contrlo" );
	sprintf( (char *)ptestMyForm->uGyk_serialnumber,"%s",(const char *)"66666666" );
	sprintf( (char *)ptestMyForm->uGyk_samplenumber,"%s",(const char *)"88888888" );
	sprintf( (char *)ptestMyForm->uGyk_sampletype,"%s",(const char *)"A-A-B-B" );
	sprintf( (char *)ptestMyForm->uGyk_densityresult,"%s",(const char *)"2.6666" );	
	OSTimeDlyHMSM(0, 0, 2, 10,OS_OPT_TIME_HMSM_STRICT,&err);	
	sprintf( (char *)ptestMyForm->uGyk_printtime,"%4d-%2d-%2d %2d:%2d:%2d",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec );
	
	GyK950ePrintForm( ptestMyForm );
	
	if( NULL!=ptestMyForm ){
		free( ptestMyForm );
	}		
	return 0;
}

/* �洢��ʷ�ʹ�ӡ��Ϣ */
uint8_t uStorageData( GYK950E* pPrintForm,ID_Info* pIDData,UINTE_DATA_TYPE* pstuIdInfo,uint8_t *pfDensity,uint8_t uChildrenNum )
{	

	if( EN_ON==gp_stuConfigFile->uCutEnCu ){
		return uStorageDataEn( pPrintForm,pIDData,pstuIdInfo,pfDensity,uChildrenNum );
	}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
		return uStorageDataCh( pPrintForm,pIDData,pstuIdInfo,pfDensity,uChildrenNum );
	}else{
	
	}
	
	return EXE_SUCCEED;
}

/* �洢��ʷ�ʹ�ӡ��Ϣ */
uint8_t uStorageDataEn( GYK950E* pPrintForm,ID_Info* pIDData,UINTE_DATA_TYPE* pstuIdInfo,uint8_t *pfDensity,uint8_t uChildrenNum )
{			
	sprintf( (char *)pPrintForm->uGyk_printname,"%s",(const char *)g_uPrintTitles );
	if( pIDData->children_num>1 ){
		sprintf( (char *)pPrintForm->uGyk_report,"%s",(const char *)pstuIdInfo->children_name );
	}else{
		sprintf( (char *)pPrintForm->uGyk_report,"%s",(const char *)pIDData->project_name );
	}
		
	sprintf( (char *)pPrintForm->uGyk_serialnumber,"%s",(const char *)g_projectSerial.serial_id );   /* ��ˮ�ŵı���������ڼ���ˮ�� */
	
	sprintf( (char *)pPrintForm->uGyk_printunit,"%s",(const char *)pstuIdInfo->children_unit_name );
	sprintf( (char *)pPrintForm->uGyk_sampletype,"%s",(const char *)g_uSampleType );			
	sprintf( (char *)pPrintForm->uGyk_samplenumber,"%s",(const char *)pIDData->lot_num );
	sprintf( (char *)pPrintForm->uGyk_barcode,"%s",(const char *)pIDData->barcode );
		
//	sprintf( (char *)pPrintForm->reference,"%.1f%c%.1f",pstuIdInfo->children_limits_min,'~',pstuIdInfo->children_limits_max ); /* ���Է�Χ �ο�ֵ */
	/* ��Ҫ�������� */
	switch( uChildrenNum ){
		case 0:
			sprintf( (char *)pPrintForm->uGyk_reference,"%.2f%c%.2f",g_stuUserReference.fuser_00_limits_min,'~',g_stuUserReference.fuser_00_limits_max );
			break;
		case 1:
			sprintf( (char *)pPrintForm->uGyk_reference,"%.2f%c%.2f",g_stuUserReference.fuser_01_limits_min,'~',g_stuUserReference.fuser_01_limits_max );
			break;
		case 2:
			sprintf( (char *)pPrintForm->uGyk_reference,"%.2f%c%.2f",g_stuUserReference.fuser_02_limits_min,'~',g_stuUserReference.fuser_02_limits_max );
			break;
		default:
			break;
		
	}
	
	pPrintForm->uGyk_children_num = pIDData->children_num;
	pPrintForm->uGyk_children_index = (uChildrenNum+1);
	
	sprintf( (char *)pPrintForm->uGyk_username,"%s",g_stuUserMoreInfo.user_name );
	//sprintf( (char *)pPrintForm->usersex,"%s",g_stuUserMoreInfo.user_sex );
	if( 0x31==g_stuUserMoreInfo.user_sex[0] ){
		sprintf( (char *)pPrintForm->uGyk_usersex,"%s","Famale" );
	}else{
		sprintf( (char *)pPrintForm->uGyk_usersex,"%s","Male" );
	}	
	sprintf( (char *)pPrintForm->uGyk_userage,"%d",g_stuUserMoreInfo.user_age );
	
	sprintf( (char *)pPrintForm->uGyk_densityresult,"%s",pfDensity );	
	sprintf( (char *)pPrintForm->uGyk_printtime,"%04d-%02d-%02d %02d:%02d:%02d",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec );
	sprintf( (char *)pPrintForm->uGyk_testtime,"%04d-%02d-%02d %02d:%02d:%02d",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec );
	
	return EXE_SUCCEED;
}

/* �洢��ʷ�ʹ�ӡ��Ϣ */
uint8_t uStorageDataCh( GYK950E* pPrintForm,ID_Info* pIDData,UINTE_DATA_TYPE* pstuIdInfo,uint8_t *pfDensity,uint8_t uChildrenNum )
{			
	sprintf( (char *)pPrintForm->uGyk_printname,"%s",(const char *)g_uPrintTitles );
	if( pIDData->children_num>1 ){
		sprintf( (char *)pPrintForm->uGyk_report,"%s",(const char *)pstuIdInfo->children_name );
	}else{
		sprintf( (char *)pPrintForm->uGyk_report,"%s",(const char *)pIDData->project_name );
	}
		
	sprintf( (char *)pPrintForm->uGyk_serialnumber,"%s",(const char *)g_projectSerial.serial_id );   /* ��ˮ�ŵı���������ڼ���ˮ�� */
	
	sprintf( (char *)pPrintForm->uGyk_printunit,"%s",(const char *)pstuIdInfo->children_unit_name );
	sprintf( (char *)pPrintForm->uGyk_sampletype,"%s",(const char *)g_uSampleType );			
	sprintf( (char *)pPrintForm->uGyk_samplenumber,"%s",(const char *)pIDData->lot_num );
	sprintf( (char *)pPrintForm->uGyk_barcode,"%s",(const char *)pIDData->barcode );
		
//	sprintf( (char *)pPrintForm->reference,"%.1f%c%.1f",pstuIdInfo->children_limits_min,'~',pstuIdInfo->children_limits_max ); /* ���Է�Χ �ο�ֵ */
	/* ��Ҫ�������� */
	switch( uChildrenNum ){
		case 0:
			sprintf( (char *)pPrintForm->uGyk_reference,"%.2f%c%.2f",g_stuUserReference.fuser_00_limits_min,'~',g_stuUserReference.fuser_00_limits_max );
			break;
		case 1:
			sprintf( (char *)pPrintForm->uGyk_reference,"%.2f%c%.2f",g_stuUserReference.fuser_01_limits_min,'~',g_stuUserReference.fuser_01_limits_max );
			break;
		case 2:
			sprintf( (char *)pPrintForm->uGyk_reference,"%.2f%c%.2f",g_stuUserReference.fuser_02_limits_min,'~',g_stuUserReference.fuser_02_limits_max );
			break;
		default:
			break;
		
	}
	
	pPrintForm->uGyk_children_num = pIDData->children_num;
	pPrintForm->uGyk_children_index = (uChildrenNum+1);
	
	sprintf( (char *)pPrintForm->uGyk_username,"%s",g_stuUserMoreInfo.user_name );
	//sprintf( (char *)pPrintForm->usersex,"%s",g_stuUserMoreInfo.user_sex );
	if( 0x31==g_stuUserMoreInfo.user_sex[0] ){
		sprintf( (char *)pPrintForm->uGyk_usersex,"%s","Ů" );
	}else{
		sprintf( (char *)pPrintForm->uGyk_usersex,"%s","��");
	}		
	sprintf( (char *)pPrintForm->uGyk_userage,"%d",g_stuUserMoreInfo.user_age );
	
	sprintf( (char *)pPrintForm->uGyk_densityresult,"%s",pfDensity );	
	sprintf( (char *)pPrintForm->uGyk_printtime,"%04d-%02d-%02d %02d:%02d:%02d",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec );
	sprintf( (char *)pPrintForm->uGyk_testtime,"%04d-%02d-%02d %02d:%02d:%02d",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec );
	
	return EXE_SUCCEED;
}

uint8_t GyK950ePrintForm( GYK950E* stuForm )
{
	uint8_t uErr = 0;
//	static uint8_t l_uBlueConnet = EXE_SUCCEED;
//			if( (EXE_SUCCEED==uBluetoothEncdev()) ){
//				l_uBlueConnet = EXE_SUCCEED;
//			}else{
//				l_uBlueConnet = EXE_FAILED;
//			}
	
	uErr = uGky950ECheckData( stuForm );             /* �����ݽ��кϷ����ж� */
	if( uErr!=EXE_SUCCEED ){
		return EXE_FAILED;
	}
	
	if( EN_ON==gp_stuConfigFile->uCutEnCu ){
		uErr = GyK950ePrintEnForm( stuForm );
		if( WIFI_ON==gp_stuConfigFile->uWifiOnOff ){
			uErr = GyK950ePrintEnBlueForm( stuForm );
		}
		return uErr;
	}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
		uErr = GyK950ePrintChForm( stuForm );
		if( WIFI_ON==gp_stuConfigFile->uWifiOnOff ){
			uErr = GyK950ePrintChBlueForm( stuForm );
		}
		return uErr;
	}else{
	
	}
	
	return EXE_SUCCEED;
}

uint8_t GyK950ePrintEnForm( GYK950E* stuForm )
{
#if DEBUH_UART3		
	uint8_t uRecUsart = 0;
	
	uRecUsart = uGetUsartPrintf();
	vEnableUsartPrintf( _USART3_ );               /* ʹ�ܴ���3printf */   
	
/* ��ʾ��˾���� */
#if PRINT_DIS_COMPANY
	myprintf( "\x1b@" );                         /* �����ӡ����������ָ�ΪĬ��ֵ */	
	myprintf( "\x1b%c%c",0x33,1 );               /* �����м�� */
	myprintf( "\r\n" );
	myprintf( "\r\n" ); 
	
	myprintf( "\x1b@" );                         /* �����ӡ����������ָ�ΪĬ��ֵ */
	myprintf( "\x1d!%c",0x00 );                  /* �����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );              /* ���ô�ӡ��ʼλ�� */
	myprintf( "%s",stuForm->uGyk_printname );	
	myprintf( "\r\n" ); 
	
	myprintf( "\x1b@" );                         /* �����ӡ����������ָ�ΪĬ��ֵ */
	myprintf( "\x1b%c%c",0x33,15 );              /* �����м�� */
	myprintf( " " );  
	myprintf( "\r\n" ); 
#endif
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x11 );               /* ������׶��ٿո� */    	
	myprintf( "\x1b\x24%c%c",20,0 );          /* ���ô�ӡ��ʼλ��*/
	myprintf( "\x1b%c%c",0x33,80 );           /* �����м�� */
	myprintf( "%s%s",stuForm->uGyk_report,(const char *)" Report" );	
	myprintf( "\r\n" ); 
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );            /*���ô�ӡ��ʼλ��*/
	myprintf( "Name:%s",stuForm->uGyk_username );	
	myprintf( "\r\n" );
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );            /*���ô�ӡ��ʼλ��*/
	myprintf( "Gender:%s %s Age:%s",stuForm->uGyk_usersex,"    ",stuForm->uGyk_userage );	
	myprintf( "\r\n" );
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );            /*���ô�ӡ��ʼλ��x��y���� 0-255 */
	myprintf( "%s%s",(const char *)"Serial number:",stuForm->uGyk_serialnumber );	
	myprintf( "\r\n" ); 
	
//	myprintf( "\x1b@" );
//	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
//	myprintf( "\x1b\x24%c%c",0,0 );            /*���ô�ӡ��ʼλ��*/
//	myprintf( "%s%s",(const char *)"Sample number:",stuForm->uGyk_samplenumber );	
//	myprintf( "\r\n" ); 
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );            /*���ô�ӡ��ʼλ��*/
	myprintf( "%s%s",(const char *)"Sample type:",stuForm->uGyk_sampletype );	
	myprintf( "\r\n" ); 
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );            /*���ô�ӡ��ʼλ��*/
	myprintf( "DateA:%s",stuForm->uGyk_testtime );	
	myprintf( "\r\n" );	
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );            /*���ô�ӡ��ʼλ��*/
	myprintf( "%s",(const char *)"-------------------------------" );	
	myprintf( "\r\n" );
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );            /*���ô�ӡ��ʼλ��*/
	myprintf( "%s",(const char *)"Item         Result       Unit" );	
	myprintf( "\r\n" ); 
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );            /*���ô�ӡ��ʼλ��*/
	myprintf( "%s%s%s%s%s",stuForm->uGyk_report,(const char *)"       ",stuForm->uGyk_densityresult,(const char *)"      ",stuForm->uGyk_printunit );	
	myprintf( "\r\n" );
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );            /*���ô�ӡ��ʼλ��*/
	myprintf( "Reference Range: %s",stuForm->uGyk_reference );	
	myprintf( "\r\n" );
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );            /*���ô�ӡ��ʼλ��*/
	myprintf( "%s",(const char *)"-------------------------------" );	
	myprintf( "\r\n" );
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );            /*���ô�ӡ��ʼλ��*/
	myprintf( "%s",(const char *)"This result is only responsible for this specimen." );
	myprintf( "\r\n" );
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                      /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );                  /*���ô�ӡ��ʼλ��*/
	myprintf( "DateB:%s",stuForm->uGyk_printtime );	
	myprintf( "\x1b%c%c",0x64,0x03 );                /* ��ӡ����ֽ3�� �����˵����������׽϶� */
	//myprintf( "\r\n" );

	vEnableUsartPrintf( uRecUsart );                 /* ʹ�ܴ���1printf */  
#endif	
	return EXE_SUCCEED;	
}

uint8_t GyK950ePrintChForm( GYK950E* stuForm )
{
#if DEBUH_UART3		
	uint8_t uRecUsart = 0;
	
	uRecUsart = uGetUsartPrintf();
	vEnableUsartPrintf( _USART3_ );               /* ʹ�ܴ���3printf */   
	
/* ��ʾ��˾���� */
#if PRINT_DIS_COMPANY
	myprintf( "\x1b@" );                         /* �����ӡ����������ָ�ΪĬ��ֵ */	
	myprintf( "\x1b%c%c",0x33,1 );               /* �����м�� */
	myprintf( "\r\n" );
	myprintf( "\r\n" ); 
	
	myprintf( "\x1b@" );                         /* �����ӡ����������ָ�ΪĬ��ֵ */
	myprintf( "\x1d!%c",0x00 );                  /* �����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );              /* ���ô�ӡ��ʼλ�� */
	myprintf( "%s",stuForm->uGyk_printname );	
	myprintf( "\r\n" ); 
	
	myprintf( "\x1b@" );                         /* �����ӡ����������ָ�ΪĬ��ֵ */
	myprintf( "\x1b%c%c",0x33,15 );              /* �����м�� */
	myprintf( " " );  
	myprintf( "\r\n" ); 
#endif
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x11 );               /* ������׶��ٿո� */    	
	myprintf( "\x1b\x24%c%c",20,0 );          /* ���ô�ӡ��ʼλ��*/
	myprintf( "\x1b%c%c",0x33,80 );           /* �����м�� */
	myprintf( "%s%s",stuForm->uGyk_report,(const char *)" ����" );	
	myprintf( "\r\n" ); 
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );               /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );           /*���ô�ӡ��ʼλ��*/
	myprintf( "����:%s",stuForm->uGyk_username );
	myprintf( "\r\n" );
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );               /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );           /*���ô�ӡ��ʼλ��*/
	myprintf( "�Ա�:%s %s ����:%s",stuForm->uGyk_usersex,"    ",stuForm->uGyk_userage );	
	myprintf( "\r\n" );
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );            /*���ô�ӡ��ʼλ��x��y���� 0-255 */
	myprintf( "%s%s",(const char *)"��ˮ��:",stuForm->uGyk_serialnumber );	
	myprintf( "\r\n" ); 
	
//	myprintf( "\x1b@" );
//	myprintf( "\x1d!%c",0x00 );              /*�����ֺŴ�С Ϊ0 */    	
//	myprintf( "\x1b\x24%c%c",0,0 );          /*���ô�ӡ��ʼλ��*/
//	myprintf( "%s%s",(const char *)"������:",stuForm->uGyk_samplenumber );	
//	myprintf( "\r\n" ); 
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );              /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );          /*���ô�ӡ��ʼλ��*/
	myprintf( "%s%s",(const char *)"��������:",stuForm->uGyk_sampletype );		
	myprintf( "\r\n" ); 
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );            /*���ô�ӡ��ʼλ��*/
	myprintf( "����ʱ��:%s",stuForm->uGyk_testtime );	
	myprintf( "\r\n" );	
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );               /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );           /*���ô�ӡ��ʼλ��*/
	myprintf( "%s",(const char *)"-------------------------------" );	
	myprintf( "\r\n" );
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );               /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );           /*���ô�ӡ��ʼλ��*/
	myprintf( "%s",(const char *)"��Ŀ         ���       ��λ" );	
	myprintf( "\r\n" ); 
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );            /*���ô�ӡ��ʼλ��*/
	myprintf( "%s%s%s%s%s",stuForm->uGyk_report,(const char *)"       ",stuForm->uGyk_densityresult,(const char *)"      ",stuForm->uGyk_printunit );	
	myprintf( "\r\n" );
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );            /*���ô�ӡ��ʼλ��*/
	myprintf( "�ο���Χ: %s",stuForm->uGyk_reference );	
	myprintf( "\r\n" );
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );            /*���ô�ӡ��ʼλ��*/
	myprintf( "%s",(const char *)"-------------------------------" );	
	myprintf( "\r\n" );
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );            /*���ô�ӡ��ʼλ��*/
	myprintf( "%s",(const char *)"��������Ա��ݱ걾����!" );
	myprintf( "\r\n" );
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );            /*���ô�ӡ��ʼλ��*/
	myprintf( "��ӡʱ��:%s",stuForm->uGyk_printtime );
	myprintf( "\x1b%c%c",0x64,0x03 );          /* ��ӡ����ֽ3�� �����˵����������׽϶� */
	//myprintf( "\r\n" );

	vEnableUsartPrintf( uRecUsart );               /* ʹ�ܴ���1printf */  
#endif	
	return EXE_SUCCEED;	
}

uint8_t GyK950ePrintEnBlueForm( GYK950E* stuForm )
{
	uint8_t uTempBluetooth[1000] = {0};
	uint16_t uLenData = 0;
	uint8_t uErrBluetooth = 0; 
	
	uErrBluetooth = uBluetoothEncdev();
	/*  */
	if( EXE_SUCCEED==uErrBluetooth ){
	/* ��ʾ��˾���� */
#if PRINT_DIS_COMPANY
		sprintf( (char *)uTempBluetooth,"\x1b@\x1b%c%c\r\n\r\n",0x33,0x30 );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);		
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s\r\n",0x00,0,0,stuForm->uGyk_printname );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1b\x33%c%s\r\n",0x30," " );
#endif	
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c\x1b\x33%c%s%s\r\n",0x11,20,0,80,stuForm->uGyk_report,(const char *)" Report" );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s%s\r\n",0x00,0,0,(const char *)"Name:",stuForm->uGyk_username );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s%s%s%s%s\r\n",0x00,0,0,(const char *)"Gender:",stuForm->uGyk_username,"    ",(const char *)"Age:",stuForm->uGyk_userage );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s%s\r\n",0x00,0,0,(const char *)"Serial number:",stuForm->uGyk_serialnumber );
		
//		uLenData = uMyStrlength((const char*)uTempBluetooth);
//		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s%s\r\n",0x00,0,0,(const char *)"Sample number:",stuForm->uGyk_samplenumber );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s%s\r\n",0x00,0,0,(const char *)"Sample type:",stuForm->uGyk_sampletype );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s%s\r\n",0x00,0,0,(const char *)"Test Time:",stuForm->uGyk_testtime );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s\r\n",0x00,0,0,(const char *)"-------------------------------" );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s\r\n",0x00,0,0,(const char *)"Item         Result       Unit" );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s%s%s%s%s\r\n",0x00,0,0,stuForm->uGyk_report,(const char *)"       ",     \
			                                       stuForm->uGyk_densityresult,(const char *)"      ",stuForm->uGyk_printunit );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s%s\r\n",0x00,0,0,(const char *)"Reference Range:",stuForm->uGyk_reference );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s\r\n",0x00,0,0,(const char *)"-------------------------------" );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s\r\n",0x00,0,0,(const char *)"This result is only for this    sample." );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1b\x33%c%s\r\n",0x30," " );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s%s\x1b\x64%c",0x00,0,0,(const char *)"Print Time:",stuForm->uGyk_printtime,3 );
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		
		if( uLenData<sizeof(uTempBluetooth) ){
			if( uLenData>CLASSIC_BLUETOOTH_PACK ){
				uBluetoothSendOriginalData( (uint8_t *)uTempBluetooth,CLASSIC_BLUETOOTH_PACK );
				uBluetoothSendOriginalData( (uint8_t *)(uTempBluetooth+CLASSIC_BLUETOOTH_PACK),(uLenData-CLASSIC_BLUETOOTH_PACK) );
			}else{
				uBluetoothSendOriginalData( (uint8_t *)uTempBluetooth,uLenData );
			}
		}
	}
	
	return EXE_SUCCEED;	
}

uint8_t GyK950ePrintChBlueForm( GYK950E* stuForm )
{
	uint8_t uTempBluetooth[1000] = {0};
	uint16_t uLenData = 0;
	
	/*  */
	if( (EXE_SUCCEED==uBluetoothEncdev()) ){
	/* ��ʾ��˾���� */
#if PRINT_DIS_COMPANY
		sprintf( (char *)uTempBluetooth,"\x1b@\x1b%c%c\r\n\r\n",0x33,0x30 );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);		
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s\r\n",0x00,0,0,stuForm->uGyk_printname );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1b\x33%c%s\r\n",0x30," " );
#endif	
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c\x1b\x33%c%s%s\r\n",0x11,20,0,80,stuForm->uGyk_report,(const char *)" ����" );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s%s\r\n",0x00,0,0,(const char *)"����:",stuForm->uGyk_username );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s%s%s%s%s\r\n",0x00,0,0,(const char *)"�Ա�:",stuForm->uGyk_username,"    ",(const char *)"����:",stuForm->uGyk_userage );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s%s\r\n",0x00,0,0,(const char *)"��ˮ��:",stuForm->uGyk_serialnumber );
		
//		uLenData = uMyStrlength((const char*)uTempBluetooth);
//		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s%s\r\n",0x00,0,0,(const char *)"������:",stuForm->uGyk_samplenumber );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s%s\r\n",0x00,0,0,(const char *)"��������:",stuForm->uGyk_sampletype );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s%s\r\n",0x00,0,0,(const char *)"����ʱ��:",stuForm->uGyk_testtime );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s\r\n",0x00,0,0,(const char *)"-------------------------------" );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s\r\n",0x00,0,0,(const char *)"��Ŀ         ���       ��λ" );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s%s%s%s%s\r\n",0x00,0,0,stuForm->uGyk_report,(const char *)"       ",     \
			                                       stuForm->uGyk_densityresult,(const char *)"      ",stuForm->uGyk_printunit );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s%s\r\n",0x00,0,0,(const char *)"�ο���Χ:",stuForm->uGyk_reference );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s\r\n",0x00,0,0,(const char *)"-------------------------------" );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s\r\n",0x00,0,0,(const char *)"��������Ա��ݱ걾����!" );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1b\x33%c%s\r\n",0x30," " );
		
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		sprintf( (char *)(uTempBluetooth+uLenData),"\x1b@\x1d!%c\x1b\x24%c%c%s%s\x1b\x64%c",0x00,0,0,(const char *)"��ӡʱ��:",stuForm->uGyk_printtime,3 );
		uLenData = uMyStrlength((const char*)uTempBluetooth);
		
		if( uLenData<sizeof(uTempBluetooth) ){
			if( uLenData>CLASSIC_BLUETOOTH_PACK ){
				uBluetoothSendOriginalData( (uint8_t *)uTempBluetooth,CLASSIC_BLUETOOTH_PACK );
				uBluetoothSendOriginalData( (uint8_t *)(uTempBluetooth+CLASSIC_BLUETOOTH_PACK),(uLenData-CLASSIC_BLUETOOTH_PACK) );
			}else{
				uBluetoothSendOriginalData( (uint8_t *)uTempBluetooth,uLenData );
			}
		}
	}
		
	return EXE_SUCCEED;	
}

uint8_t GyK950ePrintTest( void )
{
#if DEBUH_UART3	
	uint8_t uRecUsart = 0;
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( _USART3_ );               /* ʹ�ܴ���3printf */  
	
	myprintf( "\x1b@" );                    /*�����ӡ����������ָ�ΪĬ��ֵ*/	
	myprintf( "\x1b%c%c",0x33,1 );         /* �����м�� */
	myprintf( "\r\n" );
	myprintf( "\r\n" ); 
	
	myprintf( "\x1b@" );                    /*�����ӡ����������ָ�ΪĬ��ֵ*/
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );         /*���ô�ӡ��ʼλ�� */
	//myprintf( "\x1b%c%c",0x33,100 );         /* �����м�� */
	myprintf( "%s",(const char *)"Sichuan Xincheng Biological Co., LTD" );	
	myprintf( "\r\n" ); 
	
	myprintf( "\x1b@" );                    /*�����ӡ����������ָ�ΪĬ��ֵ*/
	myprintf( "\x1b%c%c",0x33,15 );         /* �����м�� */
	myprintf( " " );  
	myprintf( "\r\n" ); 
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x11 );                /*�����ֺŴ�С Ϊ1���� */  
	//myprintf( "\x1d!%c",0x22 );                /*�����ֺŴ�С Ϊ2���� */    	
	myprintf( "\x1b\x24%c%c",20,0 );         /*���ô�ӡ��ʼλ��*/
	myprintf( "\x1b%c%c",0x33,80 );           /* �����м�� */
	myprintf( "%s",(const char *)"Contrlo Report" );	
	myprintf( "\r\n" ); 
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );         /*���ô�ӡ��ʼλ��x��y���� 0-255 */
	
	myprintf( "%s%s",(const char *)"Serial number:",(const char *)"66666666" );	
	myprintf( "\r\n" ); 
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );         /*���ô�ӡ��ʼλ��*/
	//sprintf( (char *)cArrGy,"%s",(const char *)"88888888" );//
	myprintf( "%s%s",(const char *)"Sample number:",(const char *)"88888888" );	
	myprintf( "\r\n" ); 
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );         /*���ô�ӡ��ʼλ��*/
	myprintf( "%s%s",(const char *)"Sample type:",(const char *)"A-A-B-B" );	
	myprintf( "\r\n" ); 
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );         /*���ô�ӡ��ʼλ��*/
	myprintf( "%s",(const char *)"2020-06-08 09:07:55" );	
	myprintf( "\r\n" );
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );         /*���ô�ӡ��ʼλ��*/
	myprintf( "%s",(const char *)"-------------------------------" );	
	myprintf( "\r\n" );
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );         /*���ô�ӡ��ʼλ��*/
	myprintf( "%s",(const char *)"Item         Result       Unit" );	
	myprintf( "\r\n" ); 
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );         /*���ô�ӡ��ʼλ��*/
	myprintf( "%s",(const char *)"Control      2.1456       T/C" );	
	myprintf( "\r\n" );
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );         /*���ô�ӡ��ʼλ��*/
	myprintf( "%s",(const char *)"-------------------------------" );	
	myprintf( "\r\n" );
	
	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );         /*���ô�ӡ��ʼλ��*/
	//myprintf( "%s",(const char *)"This result is only responsible for this specimen!" );	
	myprintf( "%s",(const char *)"This result is only for this sample." );
	myprintf( "\r\n" );

	myprintf( "\x1b@" );
	myprintf( "\x1d!%c",0x00 );                /*�����ֺŴ�С Ϊ0 */    	
	myprintf( "\x1b\x24%c%c",0,0 );         /*���ô�ӡ��ʼλ��*/
	myprintf( "%s",(const char *)"2020-06-08 09:08:59" );	
	myprintf( "\x1b%c%c",0x64,0x03 );          /* */
	//myprintf( "\r\n" );
	
	vEnableUsartPrintf( uRecUsart );               /* ʹ�ܴ���1printf */  
#endif

	return 0;	
	
}

uint8_t DisplayHistoryDataTxt( GYK950E* pHistory )
{
	uint8_t strff[32]  = {0};
	
	uConfirmPage( TJC_HISTORY1_PAGE );      /* ȷ���Ƿ�����ʷ��ʾҳ */
	
	memset( strff,0,sizeof(strff) );		
	if( 0xff!=pHistory->uGyk_serialnumber[0] ){
		uTjc4832tSetLableValue( TJC_HISTORY1_PAGE,SERIAL_DIS_CON_ID,(uint8_t *)pHistory->uGyk_serialnumber );	
	}else{
		uTjc4832tSetLableValue( TJC_HISTORY1_PAGE,SERIAL_DIS_CON_ID,(uint8_t *)"" );	
	}
	
	memset( strff,0,sizeof(strff) );		
	if( 0xff!=pHistory->uGyk_report[0] ){
		uTjc4832tSetLableValue( TJC_HISTORY1_PAGE,NAME_DIS_CON_ID,(uint8_t *)pHistory->uGyk_report );	
	}else{
		uTjc4832tSetLableValue( TJC_HISTORY1_PAGE,NAME_DIS_CON_ID,(uint8_t *)"" );	
	}
	
	memset( strff,0,sizeof(strff) );
	if( 0xff!=pHistory->uGyk_densityresult[0] ){
		//sprintf( (char *)uArrTemp,"%f",pHistoryMyForm->densityresult );
		uTjc4832tSetLableValue( TJC_HISTORY1_PAGE,LOT_DIS_CON_ID,(uint8_t *)pHistory->uGyk_densityresult );
	}else{
		uTjc4832tSetLableValue( TJC_HISTORY1_PAGE,LOT_DIS_CON_ID,(uint8_t *)"" );
	}
	
	memset( strff,0,sizeof(strff) );
	if( 0xff!=pHistory->uGyk_testtime[0] ){
		uTjc4832tSetLableValue( TJC_HISTORY1_PAGE,SAMPLE_DIS_CON_ID,(uint8_t *)pHistory->uGyk_testtime );	
	}else{
		uTjc4832tSetLableValue( TJC_HISTORY1_PAGE,SAMPLE_DIS_CON_ID,(uint8_t *)"" );
	}
	
	memset( strff,0,sizeof(strff) );
	if( 0xff!=pHistory->uGyk_reference[0] ){
		uTjc4832tSetLableValue( TJC_HISTORY1_PAGE,ITEM_DIS_CON_ID,(uint8_t *)pHistory->uGyk_reference );	
	}else{
		uTjc4832tSetLableValue( TJC_HISTORY1_PAGE,ITEM_DIS_CON_ID,(uint8_t *)"" );	
	}
					
	memset( strff,0,sizeof(strff) );
	if( 0xff!=pHistory->uGyk_barcode[0] ){
		uTjc4832tSetLableValue( TJC_HISTORY1_PAGE,DENSITY_DIS_CON_ID,(uint8_t *)pHistory->uGyk_barcode );	
	}else{
		uTjc4832tSetLableValue( TJC_HISTORY1_PAGE,DENSITY_DIS_CON_ID,(uint8_t *)"" );	
	}
							
	memset( strff,0,sizeof(strff) );
	if( 0xff!=pHistory->uGyk_sampletype[0] ){								
		uTjc4832tSetLableValue( TJC_HISTORY1_PAGE,DATA_DIS_CON_ID,(uint8_t *)pHistory->uGyk_sampletype );
	}else{
		uTjc4832tSetLableValue( TJC_HISTORY1_PAGE,DATA_DIS_CON_ID,(uint8_t *)"" );
	}

	return EXE_SUCCEED;
}

uint8_t uGky950ECheckData(  GYK950E* stuForm )
{
	stuForm->uGyk_printname[47] = '\0';
	stuForm->uGyk_report[19] = '\0';
	stuForm->uGyk_serialnumber[19] = '\0';
	stuForm->uGyk_samplenumber[7] = '\0';
	stuForm->uGyk_sampletype[19] = '\0';
	stuForm->uGyk_densityresult[11] = '\0';
	stuForm->uGyk_barcode[7] = '\0';
	stuForm->uGyk_reference[25] = '\0';
	stuForm->uGyk_testtime[23] = '\0';
	stuForm->uGyk_printtime[23] = '\0';
	stuForm->uGyk_printunit[7] = '\0';
	stuForm->uGyk_username[19] = '\0';
	stuForm->uGyk_usersex[7] = '\0';
	stuForm->uGyk_userage[3] = '\0';
	
	if( (0==stuForm->uGyk_printname[0])||(0xff==stuForm->uGyk_printname[0]) ){
		return EXE_FAILED;
	}
	
	if( (0==stuForm->uGyk_report[0])||(0xff==stuForm->uGyk_report[0]) ){
		return EXE_FAILED;
	}
	
	if( (0==stuForm->uGyk_serialnumber[0])||(0xff==stuForm->uGyk_serialnumber[0]) ){
		return EXE_FAILED;
	}
	
//	if( (0==stuForm->uGyk_samplenumber[0])||(0xff==stuForm->uGyk_samplenumber[0]) ){
//		return EXE_FAILED;
//	}
	
	if( (0==stuForm->uGyk_sampletype[0])||(0xff==stuForm->uGyk_sampletype[0]) ){
		return EXE_FAILED;
	}
	
	if( (0==stuForm->uGyk_densityresult[0])||(0xff==stuForm->uGyk_densityresult[0]) ){
		return EXE_FAILED;
	}
	
	if( (0==stuForm->uGyk_barcode[0])||(0xff==stuForm->uGyk_barcode[0]) ){
		return EXE_FAILED;
	}
	
	if( (0==stuForm->uGyk_reference[0])||(0xff==stuForm->uGyk_reference[0]) ){
		return EXE_FAILED;
	}
	
	if( (0==stuForm->uGyk_testtime[0])||(0xff==stuForm->uGyk_testtime[0]) ){
		return EXE_FAILED;
	}
	
	if( (0==stuForm->uGyk_printtime[0])||(0xff==stuForm->uGyk_printtime[0]) ){
		return EXE_FAILED;
	}
	
	if( (0==stuForm->uGyk_printunit[0])||(0xff==stuForm->uGyk_printunit[0]) ){
		return EXE_FAILED;
	}
	
//	if( (0==stuForm->uGyk_username[0])||(0xff==stuForm->uGyk_username[0]) ){
//		return EXE_FAILED;
//	}
//	
//	if( (0==stuForm->uGyk_usersex[0])||(0xff==stuForm->uGyk_usersex[0]) ){
//		return EXE_FAILED;
//	}
//	
//	if( (0==stuForm->uGyk_userage[0])||(0xff==stuForm->uGyk_userage[0]) ){
//		return EXE_FAILED;
//	}
	
	if( (0==stuForm->uGyk_children_num)||(3<stuForm->uGyk_children_num) ){
		return EXE_FAILED;
	}
	
	return EXE_SUCCEED;	
}

unsigned int uMyStrlength(const char *str)
{
	const char *ptr=str;
	
	do{
		while( *(str++)!='\0' ){
			;
		}
	}while( !((*(str++)==0)&&(*(str++)==0)) );	

	return str-ptr-3;	
}


