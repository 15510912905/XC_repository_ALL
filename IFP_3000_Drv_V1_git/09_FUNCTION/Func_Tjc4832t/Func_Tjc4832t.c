#include "Func_Tjc4832t.h"

uint8_t uOrderAnalysis( uint8_t uOrder,uint8_t *puOrdArr,uint8_t uSize )
{
	switch( uOrder ){	
		/* 以下是错误回应 */		
		case TJC_INVALID_ORDER:
			uTjcErrorInvalidOrderEvent( TJC_INVALID_ORDER );
			break;
		
		case TJC_ORDER_SUCCEED:
			uTjcErrorEvent( TJC_ORDER_SUCCEED );
			break;
		
		case TJC_ORDERID_INVALID:
			uTjcErrorEvent( TJC_ORDERID_INVALID );
			break;
		
		case TJC_ORDERPAGE_INVALID:
			uTjcErrorEvent( TJC_ORDERPAGE_INVALID );
			break;
		
		case TJC_ORDERPIC_INVALID:
			uTjcErrorEvent( TJC_ORDERPIC_INVALID );
			break;		
		
		case TJC_ORDERWORD_INVALID:
			uTjcErrorEvent( TJC_ORDERWORD_INVALID );
			break;
		
		case TJC_BAUDS_INVALID:
			uTjcErrorEvent( TJC_BAUDS_INVALID );
			break;
		
		case TJC_CURVE_INVALID:
			uTjcErrorEvent( TJC_CURVE_INVALID );
			break;
		
		case TJC_VARIABLE_INVALID:
			uTjcErrorEvent( TJC_VARIABLE_INVALID );
			break;	
		
		case TJC_OPERATOR_INVALID:
			uTjcErrorEvent( TJC_OPERATOR_INVALID );
			break;
		
		case TJC_ASSIGN_INVALID:
			uTjcErrorEvent( TJC_ASSIGN_INVALID );
			break;
		
		case TJC_EEPROM_INVALID:
			uTjcErrorEvent( TJC_EEPROM_INVALID );
			break;
		
		case TJC_PARAM_INVALID:
			uTjcErrorEvent( TJC_PARAM_INVALID );
			break;		
		
		case TJC_IO_INVALID:
			uTjcErrorEvent( TJC_IO_INVALID );
			break;
		
		case TJC_TRANMEAN_INVALID:
			uTjcErrorEvent( TJC_TRANMEAN_INVALID );
			break;
		
		case TJC_VARLONG_INVALID:
			uTjcErrorEvent( TJC_VARLONG_INVALID );
			break;
		/* 以上是错误回应 */
		/* 以下是事件响应 */
		case TJC_TOUCH_EVENT:
			if( uSize>=3 ){
				return uPageButton( puOrdArr[1],puOrdArr[2] );
			}
			break;		
		
		case TJC_PAGE_ID:
			if( uSize==2 ){
				return uPageIdNumber( puOrdArr[1] );//
			}
			break;
		
		case TJC_TOUCH_DIT_EVENT:
			break;
		
		case TJC_SLEEP_EVENT:
			break;
		   			
		case TJC_STR_RE_EVENT:
			if( uSize>=2 ){
				return uReplyStr( gp_stuTjcCtrlMsg.page_id,gp_stuTjcCtrlMsg.control_id,puOrdArr+1,uSize-1 );
			}
			break;		
		
		case TJC_NUM_RE_EVENT:
			if( uSize>=2 ){
				return uReplyNum( gp_stuTjcCtrlMsg.page_id,gp_stuTjcCtrlMsg.control_id,puOrdArr+1,uSize-1 );
			}
			break;
		
		case TJC_AUTO_SLEEP_EVENT:
			break;
		
		case TJC_AUTO_WAKUP_EVENT:
			break;  
		
		case TJC_START_EVENT:
			return BUTTON_VALUE_TJC_START;
		
		case TJC_SD_UPDATA_EVENT:
			break;
		
		case TJC_DATA_SUCCEED_EVENT:
			break;
		
		case TJC_DATA_READY_EVENT:
			break;  
		/* 以上是事件响应 */
		default:			
			break;
	}
	
	return EXE_SUCCEED;
}

/* 按钮响应 */
uint8_t uPageButton( uint8_t uPage,uint8_t pButton )
{
	gp_stuTjcCtrlMsg.page_id = uPage;
	gp_stuTjcCtrlMsg.control_id = pButton;
	
	switch( uPage ){
		case TJC_NULL_PAGE:
			return uInitButton( pButton );
		case TJC_LOGIN_PAGE:
			return uLoginButton( pButton );
		case TJC_TEST_PAGE:
			return uTestButton( pButton );
		case TJC_MAIN_PAGE:
			return uMainButton( pButton );
		case TJC_SET_PAGE:
			return uSetButton( pButton );
		case TJC_HISTORY1_PAGE:
			return uHistoryButton( pButton );
		case TJC_SET_TIME_PAGE:
			return uSetTimeButton( pButton );
		case TJC_CONFIG_PAGE:
			return uConfigButton( pButton );
		case TJC_WARN_PAGE:
			return uWarnButton( pButton );
		case TJC_WARNING_PAGE:
			return uWarningButton( pButton );
		case TJC_ID_PAGE:
			return uIdButton( pButton );
		case TJC_QUICK_RESULT_PAGE:
			return uQuickResultButton( pButton );		
		case TJC_PROMPTER_PAGE:
			return uPrompterButton( pButton );
		case TJC_FORCE_EXIT_PAGE:
			return uForceExitButton( pButton );
		case TJC_PASSWORD_PAGE:
			return uPasswordButton( pButton );
		case TJC_MORE_PAGE:
			return uMorePageButton( pButton );
		case TJC_REFERENCE_PAGE:
			return uReferencePageButton( pButton );
		case TJC_AUTOTEST_PAGE:
			return uAutoTestPageButton( pButton );
		case TJC_WIFI_SSID_PAGE:
			return uWifiSsidPageButton( pButton );
		case TJC_WIFI_PAS_PAGE:
			return uWifiPasswordPageButton( pButton );
		case TJC_SET_SELECT_PAGE:
			return uSelSelectPageButton( pButton );
		case TJC_INSTRUMENT_PAGE:
			return uInstrumentAPageButton( pButton );
		case TJC_SYSTEM_PAR_PAGE:
			return uSystemPageButton( pButton );
		case TJC_SERVER_CONF_PAGE:
			return uServerPageButton( pButton );
		case TJC_BLUETOOTH_PAGE:
			return uBluetoothPageButton( pButton );
		
//		case TJC_REGISTER_PAGE:
//			return uLoginButton( pButton );
//		case TJC_DIS_TIME_PAGE:
//			return uDisTimeButton( pButton );
		
		default:			
			break;
	}
	
	return EXE_SUCCEED;
}

uint8_t	uPageIdNumber( uint8_t uPage )
{
	OS_ERR err = OS_ERR_NONE;
	
	g_RecPageID = uPage;

	OSSemPost( (OS_SEM *)&g_GetPageId,OS_OPT_POST_NO_SCHED,&err );   /* 发送页面ID信号量 */
	
	if( OS_ERR_NONE==err ){
		return EXE_SUCCEED;
	}else{
		return BUTTON_VALUE_POST_PAGE;
	}
}

/* 0x70 */
uint8_t uReplyStr( uint8_t uPage,uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{	
	switch( uPage ){
		case TJC_LOGIN_PAGE:
			return uReplyStrLoginButton( pButton,puOrdArr,uSize );
		case TJC_SET_TIME_PAGE:
			return uReplyStrButton( pButton,puOrdArr,uSize );
		case TJC_CONFIG_PAGE:
			return uReplyStrConfigButton( pButton,puOrdArr,uSize );			
		case TJC_PASSWORD_PAGE:
			return uReplyStrPassword( pButton,puOrdArr,uSize );	
		case TJC_MORE_PAGE:
			return uReplyStrMoreButton( pButton,puOrdArr,uSize );	
		case TJC_REFERENCE_PAGE:
			return uReplyStrReferenceButton( pButton,puOrdArr,uSize );	
		case TJC_PROMPTER_PAGE:			
			return uReplyStrPrompter( pButton,puOrdArr,uSize );	
		case TJC_WIFI_SSID_PAGE:
			return uReplyStrWifiSsidName( pButton,puOrdArr,uSize );
		case TJC_WIFI_PAS_PAGE:
			return uReplyStrWifiPassword( pButton,puOrdArr,uSize );
		case TJC_SYSTEM_PAR_PAGE:
			return uReplyStrSystemButton( pButton,puOrdArr,uSize );	
		case TJC_WARN_PAGE:
			return uReplyStrWarn( pButton,puOrdArr,uSize );			
		case TJC_SERVER_CONF_PAGE:
			return uReplyStrServerConfig( pButton,puOrdArr,uSize );
			
//		case TJC_REGISTER_PAGE:			
//			return uReplyStrRegisterButton( pButton,puOrdArr,uSize );
		
		default:
			break;
	}		
	
	return 0;
}

/* 0x71 */
uint8_t uReplyNum( uint8_t uPage,uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{	
	switch( uPage ){		
		case TJC_LOGIN_PAGE:
			return uReplyNumLoginButton( pButton,puOrdArr,uSize );
		
		case TJC_SET_PAGE:
			return uReplyNumInstrumentButton( pButton,puOrdArr,uSize );
		
		case TJC_SET_TIME_PAGE:
			return uReplyNumTimeButton( pButton,puOrdArr,uSize );

		case TJC_CONFIG_PAGE:
			return uReplyNumConfigButton( pButton,puOrdArr,uSize );	
		
		case TJC_REFERENCE_PAGE:
			return uReplyNumReferenceButton( pButton,puOrdArr,uSize );

		case TJC_AUTOTEST_PAGE:
			return uReplyNumAutoTestButton( pButton,puOrdArr,uSize );
		
		case TJC_INSTRUMENT_PAGE:
			return uReplyNumParameterButton( pButton,puOrdArr,uSize );
		
		case TJC_SYSTEM_PAR_PAGE:			
			return uReplyNumSystemButton( pButton,puOrdArr,uSize );
		
//		case TJC_REGISTER_PAGE:
//			return uReplyNumLoginButton( pButton,puOrdArr,uSize );
				
		default:
			break;
	}	
	
	return 0;
}

uint8_t uInitButton( uint8_t pButton )
{
	switch( pButton ){
		case 0:
			
			break;
		case 1:
			
			break;
		
		default:
			break;
	}
	
	return 0;
}

uint8_t uLoginButton( uint8_t pButton )
{
	switch( pButton ){

//		case 9:
//			return ID_PAGE;
		
		default:			
			break;
	}
	
	return 0;
}

/* 0x06 */
uint8_t uTestButton( uint8_t pButton )
{
	switch( pButton ){
		case 3:
			return STANDARD_RESULT_PAGE;
		case 6:
			return BUTTON_VALUE_WHOLE;   /* 选择全血 */
		case 7:	
			return BUTTON_VALUE_SERUM;   /* 选择末梢血 */		
		case 8:
			return QUICK_RESULT_PAGE;
		case 9:
			return ID_PAGE;
		//case 10:
		//	return KEY_PAGE;
		case 0x14:			
			return BUTTON_VALUE_USER_INFO_DIS;
		case 22:	
			return BUTTON_VALUE_S_MORE;   /* MORE */
		
		default:
			//OSTimeDlyHMSM(0, 0, 0, 120,OS_OPT_TIME_HMSM_STRICT,&err);                   /* 等待切换页面内容稳定下来 */ 
			break;
	}
	
	return 0;
}

/* 0x06 */
uint8_t uMainButton( uint8_t pButton )
{
	switch( pButton ){
		case 2:
			return SET2_PAGE;
		case 3:			
			return HISTORY1_PAGE;
		case 4:
			return TEST2_PAGE;
		case 5:
			return BUTTON_VALUE_RELOGIN;
		
		default:			
			break;
	}
	
	return 0;
}

uint8_t uHistoryButton( uint8_t pButton )
{
	switch( pButton ){
		case 2:
			return BUTTON_VALUE_HISTORY_PRINT;
		case 17:			
			return BUTTON_VALUE_HISTORY_DOWN;
		case 20:			
			return BUTTON_VALUE_HISTORY_UP;
		case 21:			
			return BUTTON_VALUE_LIS_UPLOAD;		
		
		default:			
			break;
	}
	
	return 0;
}

/* 0x07 */
uint8_t uSetButton( uint8_t pButton )
{
	switch( pButton ){

		case 2:			
			return SET4_PAGE;//SET3_PAGE;
		case 5:	
			return BUTTON_VALUE_REFERENCE_DIS;  
		case 6:
			return BUTTON_VALUE_WIFI_SCAN_AP;
		
		case 11:
			return BUTTON_VALUE_SYSTEM_INIT;
//			return BUTTON_VALUE_SLEEP;
		case 14:
			return BUTTON_VALUE_IDCARD_INFO;
		case 15:
			return BUTTON_VALUE_BLUE_SCAN_AP;
		
		default:			
			break;
	}
	
	return EXE_SUCCEED;
}

/* 10 */
uint8_t uDisTimeButton( uint8_t pButton )
{
	switch( pButton ){

//		case 3:			
//			return SET2_PAGE;
//		case 9:
//			return ID_PAGE;
		
		default:			
			break;
	}
	
	return 0;
}

uint8_t uSetTimeButton( uint8_t pButton )
{
	switch( pButton ){

		case 2:
			return BUTTON_VALUE_TIME_CLEAR;
//		case 9:
//			return ID_PAGE;
		
		default:			
			break;
	}
	
	return 0;
}

/* 0x12 */
uint8_t uConfigButton( uint8_t pButton )
{
	switch( pButton ){
		case 2:
			return BUTTON_VALUE_PARAMET_INIT;
		
		default:			
			break;
	}
	
	return 0;
}

uint8_t uWarnButton( uint8_t pButton )
{
	switch( pButton ){

//		case 2:			
//			return ;

		
		default:			
			break;
	}
	
	return 0;
}

uint8_t uWarningButton( uint8_t pButton )
{
	switch( pButton ){

//		case 2:			
//			return BUTTON_VALUE_HISTORY_UP;

		
		default:			
			break;
	}
	
	return 0;
}

/* 0x0f */
uint8_t uIdButton( uint8_t pButton )
{
	switch( pButton ){

//		case 3:
//			return TEST2_PAGE;   	
		case 13:
			return BUTTON_VALUE_IDCARD_UP;
		case 14:
			return BUTTON_VALUE_IDCARD_DOWN;
		case 0xf:
			return ID_PAGE;
		
		default:			
			break;
	}
	
	return 0;
}

/* 17 */
uint8_t uPrompterButton( uint8_t pButton )
{
	switch( pButton ){
		
		default:			
			break;
	}
	
	return 0;
}

/* 16 */
uint8_t uForceExitButton( uint8_t pButton )
{
	OS_ERR err;
	
	switch( pButton ){

		case 3:		
			OSSemPost( (OS_SEM *)&g_ForceExit,OS_OPT_POST_NO_SCHED,&err );                                       /* 发送强制退出信号量  特殊处理  */	
			break;//return BUTTON_VALUE_TEST_FEXIT;

		
		default:			
			break;
	}
	
	return EXE_SUCCEED;
}

/* 19 */
uint8_t uPasswordButton( uint8_t pButton )
{
	switch( pButton ){

//		case 3:					
//			return ;

		
		default:			
			break;
	}
	
	return 0;
}

/* 18 */
uint8_t uMorePageButton( uint8_t pButton )
{
	switch( pButton ){
//		case 6:
//			return BUTTON_VALUE_MALE;     /* 男 */
//		case 7:	
//			return BUTTON_VALUE_FAMALE;   /* 女 */
		case 2:
			return BUTTON_VALUE_MORE_CLEAR;
		
		default:			
			break;
	}
	
	return 0;
}

/* 0x16=22 */
uint8_t uAutoTestPageButton( uint8_t pButton )
{
	OS_ERR err;
	
	switch( pButton ){

		case 3:		
			OSSemPost( (OS_SEM *)&g_ForceExit,OS_OPT_POST_NO_SCHED,&err );                                       /* 发送强制退出信号量  特殊处理  */				
			break;//return BUTTON_VALUE_AUTO_FEXIT;
		case 9:
			return BUTTON_VALUE_ADBAR_DIS;
		
		default:			
			break;
	}
	
	return EXE_SUCCEED;
}

/* 0x17=23 */
uint8_t uSelSelectPageButton( uint8_t pButton )
{
	switch( pButton ){		
		case 2:
			return BUTTON_VALUE_SIDO_ROOT;	
		case 5:	
			return BUTTON_VALUE_INSTR_INIT;
		case 6:
			return BUTTON_VALUE_DIS_VER;
		case 22:

			break;
		
		default:			
			break;
	}
	
	return 0;
}

/* 0x18=24 */
uint8_t uInstrumentAPageButton( uint8_t pButton )
{
	switch( pButton ){
		case 2:
			return CONFIG_PAGE;
		case 3:			
			return BUTTON_VALUE_SIDO_ROOT;	
		case 10:
			return BUTTON_VALUE_MOTOR_UP;
		case 11:
			return BUTTON_VALUE_MOTOR_DOWN;	
		case 12:			
			return BUTTON_VALUE_RESET_MOTOR;
		case 14:			
			return BUTTON_VALUE_PROM_FACTORY;	
		case 15: /* 21 */
			return BUTTON_VALUE_PROM_CLEHIS;	
		case 16:
#if DOWN_TJC_BIN
			g_uTjcFileDownload = TJC_FILE_DOWNLOAD_ON;    /* 进入下载程序线 */
#endif
			break;
		
		default:			
			break;
	}
	
	return 0;
}

/* 25 */
uint8_t uSystemPageButton( uint8_t pButton )
{
	switch( pButton ){
		
		case 2:
			return BUTTON_VALUE_SYSTEM_CLEAR;
		case 9:
			break;
		
		case 22:

			break;
		
		default:			
			break;
	}
	
	return 0;
}

/* 26 */
uint8_t uServerPageButton( uint8_t pButton )
{
	switch( pButton ){
		
		case 4:
			return BUTTON_VALUE_SERVER_CLEAR;
		case 9:
			break;
		
		case 22:

			break;
		
		default:			
			break;
	}
	
	return 0;
}

/* 27 */
uint8_t uBluetoothPageButton( uint8_t pButton )
{
	switch( pButton ){
		case 2:
			return BUTTON_VALUE_INSTR_INIT;
		case 4:
			return BUTTON_VALUE_BLUE_A_MAC;
		case 5:
			return BUTTON_VALUE_BLUE_B_MAC;
		case 6:
			return BUTTON_VALUE_BLUE_C_MAC;
		case 7:
			return BUTTON_VALUE_BLUE_D_MAC;
		case 8:
			return BUTTON_VALUE_BLUE_E_MAC;
		case 9:
			return BUTTON_VALUE_BLUE_F_MAC;
		case 11:
			return BUTTON_VALUE_BLUE_G_MAC;
		case 12:
			return BUTTON_VALUE_BLUE_H_MAC;		
		case 10:
			return BUTTON_VALUE_BLUE_SCAN_AP;		
		case 22:

			break;
		
		default:			
			break;
	}
	
	return 0;
}

/* TJC_WIFI_SSID_PAGE */
uint8_t uWifiSsidPageButton( uint8_t pButton )
{
	switch( pButton ){

		case 2:
			return BUTTON_VALUE_INSTR_INIT;
		
		case 10:					
			return BUTTON_VALUE_WIFI_SCAN_AP;

		
		default:			
			break;
	}
	
	return 0;
}

/* TJC_WIFI_PAS_PAGE */
uint8_t uWifiPasswordPageButton( uint8_t pButton )
{
	switch( pButton ){

//		case 3:					
//			return ;
		case 5:
			return BUTTON_VALUE_WIFI_SCAN_AP;

		
		default:			
			break;
	}
	
	return 0;
}

/* 21 */
uint8_t uReferencePageButton( uint8_t pButton )
{
	switch( pButton ){
		case 2:
			return BUTTON_VALUE_REF_CLEAR;
//		case 3:					
//			return ;
		case 21:
			return BUTTON_VALUE_REFERENCE_UP;
		case 22:
			return BUTTON_VALUE_REFERENCE_DOWN;

		
		default:			
			break;
	}
	
	return 0;
}

/* 16 0x10 */
uint8_t uQuickResultButton( uint8_t pButton )
{
	switch( pButton ){
		
		case 3:			
			return TEST2_PAGE;
		case 18:
			return QUICK_RESULT_PAGE;

		
		default:			
			break;
	}
	
	return 0;
}

/*0x04 TJC_REGISTER_PAGE */
uint8_t uReplyStrRegisterButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{
#if LOGIN_CODE
	#if OS_CRITICAL_METHOD == 3			/* Allocate storage for CPU status register */
		//OS_CPU_SR  cpu_sr;
	#endif
#else
	
#endif
	
#if LOGIN_CODE
	uint8_t uRecLenTemp = 0;
	uint8_t *puTempArr = NULL;
	uint8_t i = 0;
#endif
	
	switch( pButton ){
		
		case 4:	
#if LOGIN_CODE		
			puTempArr = (uint8_t *)strtok( (char *)puOrdArr,":" );
			while(puTempArr)
			{  
				uRecLenTemp = strlen( (const char *)puTempArr );	
				
				//OS_ENTER_CRITICAL();  		                    /* 临界区 */				
				switch( i ){
					case 0:
						/* 需要考虑临界资源 */
						memset( g_userRegistName,0,USER_NAME_SIZE+1 );      //  
						if( uRecLenTemp<sizeof(g_userRegistName) ){
							memcpy( (char *)g_userRegistName,(const char *)puTempArr,uRecLenTemp );
						}
						break;
					case 1:
						/* 需要考虑临界资源 */
						memset( g_userRegistNamePas,0,USER_NAME_SIZE+1 );      // 
						if( uRecLenTemp<sizeof(g_userRegistNamePas) ){
							memcpy( (char *)g_userRegistNamePas,(const char *)puTempArr,uRecLenTemp );
						}
						break;
					case 2:
						/* 需要考虑临界资源 */
						memset( g_userRegistNamePas1,0,USER_NAME_SIZE+1 );      //
						if( uRecLenTemp<sizeof(g_userRegistNamePas1) ){
							memcpy( (char *)g_userRegistNamePas1,(const char *)puTempArr,uRecLenTemp );
						}
						break;
					
					default:
						break;
				}
				//OS_EXIT_CRITICAL();                                                    /* 临界区 */
				
				i++;
				puTempArr = (uint8_t *)strtok(NULL, ":");  
			}	
			return BUTTON_VALUE_REGISTER;
#else
			break;
#endif
			
			
			case 9:			
				break;		
		
		default:			
			break;
	}
	
	return EXE_SUCCEED;
}

/* 20 0x14 TJC_MORE_PAGE */
uint8_t uReplyStrMoreButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{	
	CPU_SR_ALLOC();                                             /*申请临界区变量*/	
	uint8_t uRecLenTemp = 0;
	uint8_t *puTempArr = NULL;
	int32_t uRecNumTemp = 0;
	uint8_t i = 0;
	
	switch( pButton ){		
		case 5:			
			puTempArr = (uint8_t *)strtok( (char *)puOrdArr,":" );
			while( (puTempArr)&&(i<STOCK_TIMES) )
			{  
				uRecLenTemp = strlen( (const char *)puTempArr );	
				
				OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */				
				switch( i ){
					case 0:
						/* 需要考虑临界资源 */
						memset( g_stuUserMoreInfo.user_name,0,sizeof(g_stuUserMoreInfo.user_name) );      //  
						if( uRecLenTemp<sizeof(g_stuUserMoreInfo.user_name) ){
							memcpy( (char *)g_stuUserMoreInfo.user_name,(const char *)puTempArr,uRecLenTemp );
						}
						break;
					case 1:
						/* 需要考虑临界资源 */
						memset( g_stuUserMoreInfo.user_sex,0,sizeof(g_stuUserMoreInfo.user_sex) );      //
						if( uRecLenTemp<sizeof(g_stuUserMoreInfo.user_sex) ){
							memcpy( (char *)g_stuUserMoreInfo.user_sex,(const char *)puTempArr,uRecLenTemp );
						}
						break;
					case 2:
						/* 需要考虑临界资源 */
						g_stuUserMoreInfo.user_age = 0;     //  
						uTjcAsciiToInt( puTempArr,&uRecNumTemp,uRecLenTemp ); 
						if( (0<uRecNumTemp)&&(uRecNumTemp<255) ){
							g_stuUserMoreInfo.user_age = uRecNumTemp;
						}
						break;
					
					default:
						break;
				}
				OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */
				
				i++;
				puTempArr = (uint8_t *)strtok(NULL, ":");  
			}	
#if DEBUH_UART1	
	#if PRIVATE_UART1			
			myprintf( "UserReference :%s %s %d\r\n",g_stuUserMoreInfo.user_name,g_stuUserMoreInfo.user_sex,g_stuUserMoreInfo.user_age );
	#endif
#endif	
			return BUTTON_VALUE_MORE_INFO;
			
			case 9:			
				break;		
		
		default:			
			break;
	}
	
	return 0;
}

/*0x05 TJC_LOGIN_PAGE */
uint8_t uReplyStrLoginButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{
	CPU_SR_ALLOC();                                             /*申请临界区变量*/	
	uint8_t uRecLenTemp = 0;
	uint8_t *puTempArr = NULL;
	uint8_t i = 0;
	
	switch( pButton ){		
		case 4:		
			puTempArr = (uint8_t *)strtok( (char *)puOrdArr,":" );
			while( (puTempArr)&&(i<STOCK_TIMES) )
			{  
				uRecLenTemp = strlen( (const char *)puTempArr );				

				OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */					
				switch( i ){
					case 0:
						/* 需要考虑临界资源 */
						memset( g_userName,0,USER_NAME_SIZE+1 );      //  
						if( uRecLenTemp<sizeof(g_userName) ){
							memcpy( (char *)g_userName,(const char *)puTempArr,uRecLenTemp );
						}
						break;
					case 1:	
						/* 需要考虑临界资源 */
						memset( g_userNamePas,0,USER_NAME_SIZE+1 );   //
						if( uRecLenTemp<sizeof(g_userNamePas) ){
							memcpy( (char *)g_userNamePas,(const char *)puTempArr,uRecLenTemp );
						}
						break;		
					
					default:
						break;
				}
				OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */
				
				i++;
				puTempArr = (uint8_t *)strtok(NULL, ":");  
			}				
			return BUTTON_VALUE_LOGIN;
			
			case 9:			
				break;		
		
		default:			
			break;
	}
	
	return 0;
}

/*26 TJC_SERVER_CONF_PAGE */
uint8_t uReplyStrServerConfig( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{
	CPU_SR_ALLOC();                                             /*申请临界区变量*/	
	uint8_t uRecLenTemp = 0;
	uint8_t *puTempArr = NULL;
	uint8_t i = 0;
	
	switch( pButton ){
		
		case 3:		
			puTempArr = (uint8_t *)strtok( (char *)puOrdArr,":" );
			while((puTempArr)&&(i<STOCK_TIMES) )			{  
				uRecLenTemp = strlen( (const char *)puTempArr );				

				OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */					
				switch( i ){
					case 0:
						/* 需要考虑临界资源 */
						memset( g_ServerIPAddr,0,sizeof(g_ServerIPAddr) );      //  
						if( uRecLenTemp<sizeof(g_ServerIPAddr) ){
							memcpy( (char *)g_ServerIPAddr,(const char *)puTempArr,uRecLenTemp );
						}
						break;
					case 1:	
						/* 需要考虑临界资源 */
						memset( g_ServerPort,0,sizeof(g_ServerPort) );   //
						if( uRecLenTemp<sizeof(g_ServerPort) ){
							memcpy( (char *)g_ServerPort,(const char *)puTempArr,uRecLenTemp );
						}
						break;		
					
					default:
						break;
				}
				OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */
				
				i++;
				puTempArr = (uint8_t *)strtok(NULL, ":");  
			}				
			return BUTTON_VALUE_SERVER_CONF;
			
			case 9:			
				break;		
		
		default:			
			break;
	}
	
	return 0;
}

/*0x0b*/
uint8_t uReplyStrButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{
	CPU_SR_ALLOC();                                             /*申请临界区变量*/
	uint8_t uRecLenTemp = 0;
	int32_t uRecNumTemp = 0;
	uint8_t *puTempArr = NULL;
	uint8_t i = 0;
	
	switch( pButton ){
		
		case 3:		
			puTempArr = (uint8_t *)strtok( (char *)puOrdArr,":" );
			while((puTempArr)&&(i<STOCK_TIMES)){  
				uRecLenTemp = strlen( (const char *)puTempArr );
				uTjcAsciiToInt( puTempArr,&uRecNumTemp,uRecLenTemp ); 	

				OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */		
				switch( i ){
					case 0:
						gp_stuEditTime->ustuTimeYears = uRecNumTemp;
						break;
					case 1:
						gp_stuEditTime->ustuTimeMonth = uRecNumTemp;
						break;
					case 2:
						gp_stuEditTime->ustuTimeDay = uRecNumTemp;
						break;
					case 3:
						gp_stuEditTime->ustuTimeHours = uRecNumTemp;
						break;
					case 4:
						gp_stuEditTime->ustuTimeMinuts = uRecNumTemp;
						break;
					
					default:
						break;
				}
				OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */
				
				i++;
				puTempArr = (uint8_t *)strtok(NULL, ":");  
			}			
			return BUTTON_VALUE_TIME;
		
		default:			
			break;
	}
	
	return 0;
}

/*0x0C TJC_CONFIG_PAGE */
uint8_t uReplyStrConfigButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{
	CPU_SR_ALLOC();                                             /*申请临界区变量*/
	uint8_t uRecLenTemp = 0;
	int32_t uRecNumTemp = 0;
	uint8_t *puTempArr = NULL;
	uint8_t i = 0;
	
	switch( pButton ){
		
		case 3:	
			puTempArr = (uint8_t *)strtok( (char *)puOrdArr,":" );
			while((puTempArr)&&(i<STOCK_TIMES)){  
				uRecLenTemp = strlen( (const char *)puTempArr );
				uTjcAsciiToInt( puTempArr,&uRecNumTemp,uRecLenTemp ); 
				
				OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */	
				switch( i ){
					case 0:
						gp_stuEditInputConfig->ustuOffset = uRecNumTemp;
						break;
					case 1:
						gp_stuEditInputConfig->ustuGain = uRecNumTemp;
						break;
					case 2:
						gp_stuEditInputConfig->ustuBarOffset = uRecNumTemp;
						break;
					case 3:
						gp_stuEditInputConfig->fstuCoeff = (float)((float)uRecNumTemp/(float)REF_MULTIPLE_RANGE);
						break;
					case 4:
						gp_stuEditInputConfig->ustuInputLanRef = uRecNumTemp;
						break;
					
					default:
						break;
				}
				OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */
				
				i++;
				puTempArr = (uint8_t *)strtok(NULL, ":");  
			}	
			return BUTTON_VALUE_ALL_CIG;
		case 9:		
			break;
		case 0x0a:
			break;
		case 0x0b:
			break;	
		case 17:
			OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */	

			memset( gp_stuEditInputConfig->ustuSNStrNum,0,SN_NUM );      //  
			memcpy( (char *)gp_stuEditInputConfig->ustuSNStrNum,(const char *)puOrdArr,uSize );
	
			OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */
			return BUTTON_VALUE_SN_STR;	
		
		default:			
			break;
	}
	
	return 0;
}

uint8_t uReplyStrSystemButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{
	CPU_SR_ALLOC();                                             /*申请临界区变量*/
	uint8_t uRecLenTemp = 0;
	int32_t uRecNumTemp = 0;
	uint8_t *puTempArr = NULL;
	uint8_t i = 0;
	
	switch( pButton ){		
		case 3:	
			puTempArr = (uint8_t *)strtok( (char *)puOrdArr,":" );
			while((puTempArr)&&(i<STOCK_TIMES)){  
				uRecLenTemp = strlen( (const char *)puTempArr );
				uTjcAsciiToInt( puTempArr,&uRecNumTemp,uRecLenTemp ); 
				
				OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */	
				switch( i ){
					case 0:
						gp_stuEditInputConfig->ustuAutoTime = uRecNumTemp;
						break;
					case 1:
						memset( g_uInputPrintTitles,0,sizeof(g_uInputPrintTitles) );   //
						if( uRecLenTemp<sizeof(g_uInputPrintTitles) ){
							memcpy( (char *)g_uInputPrintTitles,(const char *)puTempArr,uRecLenTemp );
						}
						break;
					
					default:
						break;
				}
				OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */
				
				i++;
				puTempArr = (uint8_t *)strtok(NULL, ":");  
			}	
			return BUTTON_VALUE_SYSTEM_CIG;
		case 9:
			OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */	
			memset( g_uInputPrintTitles,0,sizeof(g_uInputPrintTitles) );   //
			if( uSize<sizeof(g_uInputPrintTitles) ){
				memcpy( (char *)g_uInputPrintTitles,(const char *)puOrdArr,uSize );				
			}			
			OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */
			return BUTTON_VALUE_P_TITLES;
			
		case 0x0a:
			break;
		case 0x0b:
			break;						
		
		default:			
			break;
	}
	
	return 0;
}

/* 21 0x15 TJC_REFERENCE_PAGE */
uint8_t uReplyStrReferenceButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{
	CPU_SR_ALLOC();                                             /*申请临界区变量*/
	uint8_t uRecLenTemp = 0;
	int32_t uRecNumTemp = 0;
	uint8_t *puTempArr = NULL;
	uint8_t i = 0;
	
	memset( &g_stuUserReference,0,sizeof(g_stuUserReference) );
	
	switch( pButton ){		
		case 3:	
			puTempArr = (uint8_t *)strtok( (char *)puOrdArr,":" );
			while((puTempArr)&&(i<STOCK_TIMES)){  
				uRecLenTemp = strlen( (const char *)puTempArr );
				if( i>0 ){
					uTjcAsciiToInt( puTempArr,&uRecNumTemp,uRecLenTemp ); 
				}				
				OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */	
				switch( i ){
					case 0:
						if(uRecLenTemp>1){
							memcpy( g_stuUserReference.ureference_name,(const uint8_t*)(puTempArr+1),(uRecLenTemp-1)); 
						}
						break;
					case 1:
						g_stuUserReference.fuser_00_limits_min = (float)((float)uRecNumTemp/(float)REF_MULTIPLE_RANGE);
						break;
					case 2:
						g_stuUserReference.fuser_00_limits_max = (float)((float)uRecNumTemp/(float)REF_MULTIPLE_RANGE);
						break;		
					case 3:
						g_stuUserReference.fuser_01_limits_min = (float)((float)uRecNumTemp/(float)REF_MULTIPLE_RANGE);
						break;
					case 4:
						g_stuUserReference.fuser_01_limits_max = (float)((float)uRecNumTemp/(float)REF_MULTIPLE_RANGE);
						break;	
					case 5:
						g_stuUserReference.fuser_02_limits_min = (float)((float)uRecNumTemp/(float)REF_MULTIPLE_RANGE);
						break;
					case 6:
						g_stuUserReference.fuser_02_limits_max = (float)((float)uRecNumTemp/(float)REF_MULTIPLE_RANGE);
						break;	
					
					default:
						break;
				}
				OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */
				
				i++;
				puTempArr = (uint8_t *)strtok(NULL, ":");  
			}
			
#if DEBUH_UART1	
	#if PRIVATE_UART1	
			myprintf( "ReferenceName:%s\r\n",g_stuUserReference.ureference_name );
			myprintf( "UserReference0 :%.2f %.2f\r\n",g_stuUserReference.fuser_00_limits_min,g_stuUserReference.fuser_00_limits_max );
			myprintf( "UserReference1 :%.2f %.2f\r\n",g_stuUserReference.fuser_01_limits_min,g_stuUserReference.fuser_01_limits_max );
			myprintf( "UserReference2 :%.2f %.2f\r\n",g_stuUserReference.fuser_02_limits_min,g_stuUserReference.fuser_02_limits_max );
	#endif
#endif	
			return BUTTON_VALUE_REFERENCE;
		case 9:
		
			break;
		case 0x0a:
			break;
		case 0x0b:
			break;						
		
		default:			
			break;
	}
	
	return 0;
}

/* 17 0x12 TJC_PROMPTER_PAGE */
uint8_t uReplyStrPrompter( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{	
	uint8_t uRecTemp = 0;
	CPU_SR_ALLOC();                                             /*申请临界区变量*/
	
	switch( pButton ){		
		
		case 2:
			OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */	
		
			if( uSize<128 ){
				if( EN_ON==gp_stuConfigFile->uCutEnCu ){
					if(  NULL==strncmp( (const char *)"Associated?",(const char *)puOrdArr,uSize ) ){
						uRecTemp = BUTTON_VALUE_BAR_ERR;
					}else if( NULL==strncmp( (const char *)"Uploaded?",(const char *)puOrdArr,uSize ) ){
						uRecTemp = BUTTON_VALUE_LIS_CANCLE;
					}else if( NULL==strncmp( (const char *)"Cover ID?",(const char *)puOrdArr,uSize ) ){
						uRecTemp = BUTTON_VALUE_NO_OVER_ID;
					}else if( NULL==strncmp( (const char *)"Clear History?",(const char *)puOrdArr,uSize) ){
						//uRecTemp = BUTTON_VALUE_PARAMET_INIT;
					}
				}else{
					if(  NULL==strncmp( (const char *)"匹配?",(const char *)puOrdArr,uSize ) ){
						uRecTemp = BUTTON_VALUE_BAR_ERR;
					}else if( NULL==strncmp( (const char *)"上传?",(const char *)puOrdArr,uSize ) ){
						uRecTemp = BUTTON_VALUE_LIS_CANCLE;
					}else if( NULL==strncmp( (const char *)"覆盖?",(const char *)puOrdArr,uSize ) ){
						uRecTemp = BUTTON_VALUE_NO_OVER_ID;
					}else if( NULL==strncmp( (const char *)"清除?",(const char *)puOrdArr,uSize) ){
						//uRecTemp = BUTTON_VALUE_PARAMET_INIT;
					}
				}				
			}	

			OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */	
			return uRecTemp;	
		
		case 5:	
			OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */	
		
			if( uSize<128 ){
				if( EN_ON==gp_stuConfigFile->uCutEnCu ){
					if( NULL==strncmp( (const char *)"Shutdown?",(const char *)puOrdArr,uSize) ){
						uRecTemp = SPC_BUTTON_VALUE_SHUTDOWN;
					}else if( NULL==strncmp( (const char *)"Reset?",(const char *)puOrdArr,uSize) ){
						uRecTemp = BUTTON_VALUE_FACTORY;	
					}else if( NULL==strncmp( (const char *)"Clear History?",(const char *)puOrdArr,uSize) ){
						uRecTemp = BUTTON_VALUE_HISTORY_CLEAR;
					}else if( NULL==strncmp( (const char *)"Overwrite?",(const char *)puOrdArr,uSize) ){
						uRecTemp = BUTTON_VALUE_REF_COVER;
					}else if( NULL==strncmp( (const char *)"Associated?",(const char *)puOrdArr,uSize) ){
						uRecTemp = BUTTON_VALUE_FORCE_ASS;
					}else if( NULL==strncmp( (const char *)"Uploaded?",(const char *)puOrdArr,uSize) ){
						uRecTemp = BUTTON_VALUE_LIS_AFFIRM;
					}else if( NULL==strncmp( (const char *)"Cover ID?",(const char *)puOrdArr,uSize) ){
						uRecTemp = BUTTON_VALUE_OVER_ID;
					}
				}else{
					if( NULL==strncmp( (const char *)"关机?",(const char *)puOrdArr,uSize) ){
						uRecTemp = SPC_BUTTON_VALUE_SHUTDOWN;
					}else if( NULL==strncmp( (const char *)"复位?",(const char *)puOrdArr,uSize) ){
						uRecTemp = BUTTON_VALUE_FACTORY;	
					}else if( NULL==strncmp( (const char *)"清除?",(const char *)puOrdArr,uSize) ){
						uRecTemp = BUTTON_VALUE_HISTORY_CLEAR;
					}else if( NULL==strncmp( (const char *)"重写?",(const char *)puOrdArr,uSize) ){
						uRecTemp = BUTTON_VALUE_REF_COVER;
					}else if( NULL==strncmp( (const char *)"匹配?",(const char *)puOrdArr,uSize) ){
						uRecTemp = BUTTON_VALUE_FORCE_ASS;
					}else if( NULL==strncmp( (const char *)"上传?",(const char *)puOrdArr,uSize ) ){
						uRecTemp = BUTTON_VALUE_LIS_AFFIRM;
					}else if( NULL==strncmp( (const char *)"覆盖?",(const char *)puOrdArr,uSize) ){
						uRecTemp = BUTTON_VALUE_OVER_ID;
					}
				}
//				else if( NULL==strncmp( (const char *)"ID Success",(const char *)puOrdArr,uSize) ){
//					uRecTemp = TEST2_PAGE;
//				}
			}	

			OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */	
			return uRecTemp;					
		
		default:			
			break;
	}
	
	return 0;
}

/*  TJC_WARN_PAGE */
uint8_t uReplyStrWarn( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{	
	uint8_t uRecTemp = 0;
	CPU_SR_ALLOC();                                             /*申请临界区变量*/
	
	switch( pButton ){		
		case 2:	
			OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */	
		
			if( uSize<128 ){
				if( EN_ON==gp_stuConfigFile->uCutEnCu ){
					if( NULL!=strstr((const char *)puOrdArr,(const char *)"second") ){
						uRecTemp = BUTTON_VALUE_WARN_CANCEL;
					}else if( NULL==strncmp( (const char *)"Network Disconnect",(const char *)puOrdArr,uSize ) ){
						uRecTemp = BUTTON_VALUE_LIS_CANCLE;
					}else if(  NULL==strncmp( (const char *)ERROR_BLUR_INVALID,(const char *)puOrdArr,uSize) ){
						uRecTemp = BUTTON_VALUE_BLUE_SCAN_AP;
					}else if(  NULL==strncmp( (const char *)"Abnormal test",(const char *)puOrdArr,uSize) ){
						uRecTemp = BUTTON_VALUE_BAR_ERR;
					}else if( NULL==strncmp( (const char *)"Read ID Successful",(const char *)puOrdArr,uSize) ){
						uRecTemp = TEST2_PAGE;
					}
				}else{
					if( NULL!=strstr((const char *)puOrdArr,(const char *)"second") ){
						uRecTemp = BUTTON_VALUE_WARN_CANCEL;
					}else if( NULL==strncmp( (const char *)"Network Disconnect",(const char *)puOrdArr,uSize) ){
						uRecTemp = BUTTON_VALUE_LIS_CANCLE;
					}else if(  NULL==strncmp( (const char *)ERROR_BLUR_INVALID,(const char *)puOrdArr,uSize) ){
						uRecTemp = BUTTON_VALUE_BLUE_SCAN_AP;
					}else if(  NULL==strncmp( (const char *)"异常测试",(const char *)puOrdArr,uSize) ){
						uRecTemp = BUTTON_VALUE_BAR_ERR;
					}else if( NULL==strncmp( (const char *)"Read ID Successful",(const char *)puOrdArr,uSize) ){
						uRecTemp = TEST2_PAGE;
					}
				}				
			}	

			OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */	
			return uRecTemp;					
		
		default:			
			break;
	}
	
	return 0;
}

/* 24 TJC_WIFI_SSID_PAGE */
uint8_t uReplyStrWifiSsidName( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{	
	CPU_SR_ALLOC();                                             /*申请临界区变量*/
	
	switch( pButton ){			
//		case 3:			
//			return ;						
		
		default:	
			memset( g_uWifiSsidName,0,WIFI_SSID_NAME_MAX );                  // 
			OS_CRITICAL_ENTER();  		                                     /* 以下必须考虑临界资源的问题 */	

			memcpy( (char *)g_uWifiSsidName,(const char *)puOrdArr,uSize );	

			OS_CRITICAL_EXIT();                                              /* 以上必须考虑临界资源的问题 */		
			break;
	}
	
	return 0;
}

/* 25 TJC_WIFI_PAS_PAGE */
uint8_t uReplyStrWifiPassword( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{	 
	CPU_SR_ALLOC();                                                          /*申请临界区变量*/
	switch( pButton ){			                                             
		case 3:	                                                             
			memset( g_uWifiNamePas,0,WIFI_SSID_NAME_MAX );                   // 
			OS_CRITICAL_ENTER();  		                                     /* 以下必须考虑临界资源的问题 */	

			memcpy( (char *)g_uWifiNamePas,(const char *)puOrdArr,uSize );

			OS_CRITICAL_EXIT();                                              /* 以上必须考虑临界资源的问题 */
			return BUTTON_VALUE_WIFI_PAS;						
		
		default:				
			break;
	}
	
	return 0;
}

/*0x13 TJC_PASSWORD_PAGE */
uint8_t uReplyStrPassword( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{	
	CPU_SR_ALLOC();                                             /*申请临界区变量*/
	
	switch( pButton ){			
		case 3:
			OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */	

			memset( g_uSpecialNamePas,0,USER_PASSWORD_SIZE+1 );      //  
			memcpy( (char *)g_uSpecialNamePas,(const char *)puOrdArr,uSize );
	
			OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */
			return BUTTON_VALUE_SPECIAL_PAS;
		case 0x0a:
			break;
		case 0x0b:
			break;						
		
		default:			
			break;
	}
	
	return 0;
}

/*0x04 TJC_REGISTER_PAGE */
uint8_t uReplyNumRegisterButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{
#if LOGIN_CODE
	uint32_t uRecNumTemp = 0;
#endif
	
	switch( pButton ){
#if LOGIN_CODE
		case 9:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);
			g_stuAutoRemenber.uremember = (uint8_t)uRecNumTemp;
			return INIT_PAGE;
		case 11:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);
			g_stuAutoRemenber.uauto = (uint8_t)uRecNumTemp;
			return INIT_PAGE;
#endif
		default:			
			break;
	}
	
	return EXE_SUCCEED;
}

/*0x05 TJC_LOGIN_PAGE */
uint8_t uReplyNumLoginButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{
	CPU_SR_ALLOC();                                             /*申请临界区变量*/
	
	uint32_t uRecNumTemp = 0;
	
	switch( pButton ){
		case 8:
			OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */	

			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);
			g_stuAutoRemenber.uremember = (uint8_t)uRecNumTemp;
	
			OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */
			return INIT_PAGE;
		
		default:			
			break;
	}
	
	return 0;
}

/*0x0C TJC_CONFIG_PAGE */
uint8_t uReplyNumTimeButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{
	CPU_SR_ALLOC();                                             /*申请临界区变量*/
	
	uint8_t uRecTemp = 0;
	uint32_t uRecNumTemp = 0;
	
	OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */	
	switch( pButton ){
		case 2:							
			break;
		case 6:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);
			gp_stuEditTime->ustuTimeYears = uRecNumTemp;
			uRecTemp = BUTTON_VALUE_YEARS;
			break;
		case 8:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);
			gp_stuEditTime->ustuTimeMonth = uRecNumTemp;
			uRecTemp = BUTTON_VALUE_MONTH;
			break;
		case 9:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);
			gp_stuEditTime->ustuTimeDay = uRecNumTemp;
			uRecTemp = BUTTON_VALUE_DAY;
			break;
		case 11:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);
			gp_stuEditTime->ustuTimeHours = uRecNumTemp;
			uRecTemp = BUTTON_VALUE_HOURS;
			break;
		case 13:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);
			gp_stuEditTime->ustuTimeMinuts = uRecNumTemp;
			uRecTemp = BUTTON_VALUE_MINUTES;
			break;		
		
		default:			
			break;
	}
	OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */
	
	return uRecTemp;
}

/*0x0C TJC_CONFIG_PAGE */
uint8_t uReplyNumConfigButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{
	CPU_SR_ALLOC();                                             /*申请临界区变量*/
	uint8_t uRecTemp = 0;
	uint32_t uRecNumTemp = 0;
	
	OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */
	switch( pButton ){	
		case 2:							
			break;
		case 6:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);
			gp_stuEditInputConfig->ustuOffset = uRecNumTemp;
			uRecTemp = BUTTON_VALUE_OFFSET;
			break;
		case 7:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);
			gp_stuEditInputConfig->ustuGain = uRecNumTemp;
			uRecTemp = BUTTON_VALUE_GAIN;
			break;
		case 9:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);
			gp_stuEditInputConfig->ustuBarOffset = uRecNumTemp;
			uRecTemp = BUTTON_VALUE_BAROFFSET;
			break;
		case 13:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);			
			gp_stuEditInputConfig->fstuCoeff = (float)((float)uRecNumTemp/(float)REF_MULTIPLE_RANGE);
			uRecTemp = BUTTON_VALUE_COEFF;
			break;
		case 15:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);
			gp_stuEditInputConfig->ustuInputLanRef = uRecNumTemp;
			uRecTemp = BUTTON_VALUE_LANBO_BASE;
			break;		
		
		default:			
			break;
	}		
	OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */
	
	return uRecTemp;
}

/* 21 0x15 TJC_REFERENCE_PAGE */
uint8_t uReplyNumReferenceButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{
	CPU_SR_ALLOC();                                             /*申请临界区变量*/
	uint32_t uRecNumTemp = 0;
	uint8_t uRecTemp = 0;
	
	OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */
	switch( pButton ){	

		case 2:							
			break;
		case 5:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);			
			g_stuUserReference.fuser_00_limits_min = (float)((float)uRecNumTemp/(float)REF_MULTIPLE_RANGE);
#if DEBUH_UART1	
	#if PRIVATE_UART1			
			myprintf( "UserReference1 :%.2f\r\n",g_stuUserReference.fuser_00_limits_min );
	#endif
#endif	
			uRecTemp = BUTTON_VALUE_B1REFERENCE;
			break;
		case 6:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);			
			g_stuUserReference.fuser_00_limits_max = (float)((float)uRecNumTemp/(float)REF_MULTIPLE_RANGE);
#if DEBUH_UART1	
	#if PRIVATE_UART1			
			myprintf( "UserReference2 :%.2f\r\n",g_stuUserReference.fuser_00_limits_max );
	#endif
#endif	
			uRecTemp = BUTTON_VALUE_B2REFERENCE;	
			break;
		case 0x0b:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);			
			g_stuUserReference.fuser_01_limits_min = (float)((float)uRecNumTemp/(float)REF_MULTIPLE_RANGE);
#if DEBUH_UART1	
	#if PRIVATE_UART1			
			myprintf( "UserReference3 :%.2f\r\n",g_stuUserReference.fuser_01_limits_min );
	#endif
#endif	
			uRecTemp = BUTTON_VALUE_B3REFERENCE;
			break;
		case 0x0D:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);			
			g_stuUserReference.fuser_01_limits_max = (float)((float)uRecNumTemp/(float)REF_MULTIPLE_RANGE);
#if DEBUH_UART1	
	#if PRIVATE_UART1			
			myprintf( "UserReference4 :%.2f\r\n",g_stuUserReference.fuser_01_limits_max );
	#endif
#endif	
			uRecTemp = BUTTON_VALUE_B4REFERENCE;
			break;
		case 0x0F:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);			
			g_stuUserReference.fuser_02_limits_min = (float)((float)uRecNumTemp/(float)REF_MULTIPLE_RANGE);
#if DEBUH_UART1	
	#if PRIVATE_UART1			
			myprintf( "UserReference5 :%.2f\r\n",g_stuUserReference.fuser_02_limits_min );
	#endif
#endif	
			uRecTemp = BUTTON_VALUE_B5REFERENCE;
			break;
		case 0x11:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);			
			g_stuUserReference.fuser_02_limits_max = (float)((float)uRecNumTemp/(float)REF_MULTIPLE_RANGE);
#if DEBUH_UART1	
	#if PRIVATE_UART1			
			myprintf( "UserReference6 :%.2f\r\n",g_stuUserReference.fuser_02_limits_max );
	#endif
#endif	
			uRecTemp = BUTTON_VALUE_B6REFERENCE;
			break;
		
		default:			
			break;

	}
	OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */
	
	return uRecTemp;
}

/* 22 0x16 TJC_AUTOTEST_PAGE */
uint8_t uReplyNumAutoTestButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{
	CPU_SR_ALLOC();                                             /*申请临界区变量*/
	uint32_t uRecNumTemp = 0;
	uint8_t uRecTemp = 0;
	
	OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */	
	switch( pButton ){
		case 2:			
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);			
			g_uAutoTestTimes = uRecNumTemp;
		
#if DEBUH_UART1	
	#if PRIVATE_UART1			
			myprintf( "g_uAutoTestTimes :%d \r\n",g_uAutoTestTimes );
	#endif
#endif	
			uRecTemp = BUTTON_VALUE_AUTO_TEST;
			break;

		
		default:			
			break;
	}
	OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */
	
	return uRecTemp;
}

/* 23 0x17 TJC_INSTRUMENT_PAGE */
uint8_t uReplyNumInstrumentButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{
	CPU_SR_ALLOC();                                             /*申请临界区变量*/
	uint32_t uRecNumTemp = 0;
	uint8_t uRecTemp = 0;
	
	OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */
	switch( pButton ){		
		case 7:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);			
			gp_stuConfigFile->uBuzzerOnOff = uRecNumTemp;
#if DEBUH_UART1	
	#if PRIVATE_UART1			
			myprintf( "uBuzzerOnOff :%d \r\n",gp_stuConfigFile->uBuzzerOnOff );
	#endif
#endif	
			uRecTemp = BUTTON_VALUE_BUZZER;
			break;
		
		case 10:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);			
			gp_stuConfigFile->uPrintfOnOff = uRecNumTemp;
#if DEBUH_UART1	
	#if PRIVATE_UART1			
			myprintf( "uPrintfOnOff :%d \r\n",gp_stuConfigFile->uPrintfOnOff );
	#endif
#endif	
			uRecTemp = BUTTON_VALUE_PRINTF;		
			break;

		case 9: //18
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);			
			gp_stuConfigFile->uScanBar = uRecNumTemp;
#if DEBUH_UART1	
	#if PRIVATE_UART1			
			myprintf( "uScanBar :%d \r\n",gp_stuConfigFile->uScanBar );
	#endif
#endif	
			uRecTemp = BUTTON_VALUE_SCAN_BAR;	
			break;
		
		case 12:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);			
			gp_stuConfigFile->uWifiOnOff = uRecNumTemp;
#if DEBUH_UART1	
	#if PRIVATE_UART1			
			myprintf( "uWifiOnOff :%d \r\n",gp_stuConfigFile->uWifiOnOff );
	#endif
#endif	
			uRecTemp = BUTTON_VALUE_WIFI_ONOFF;
			break;
		
		default:			
			break;
	}
	OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */
	
	return uRecTemp;
}

/* 24 0x17 TJC_SYSTEM_PAR_PAGE */
uint8_t uReplyNumParameterButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{
	CPU_SR_ALLOC();                                             /*申请临界区变量*/
	uint32_t uRecNumTemp = 0;
	uint8_t uRecTemp = 0;
	
	OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */
	switch( pButton ){		
		case 6:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);			
			gp_stuConfigFile->uLedOnOff = uRecNumTemp;
#if DEBUH_UART1	
	#if PRIVATE_UART1			
			myprintf( "uLedOnOff :%d \r\n",gp_stuConfigFile->uLedOnOff );
	#endif
#endif	
			uRecTemp = BUTTON_VALUE_LED_CTRL;	
			break;
		
		case 7:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);			
			gp_stuConfigFile->uPrintAD = uRecNumTemp;
#if DEBUH_UART1	
	#if PRIVATE_UART1			
			myprintf( "uPrintAD :%d \r\n",gp_stuConfigFile->uPrintAD );
	#endif
#endif	
			uRecTemp = BUTTON_VALUE_PRINT_AD;
			break;
		
		case 8:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);			
			gp_stuConfigFile->uPrintBar = uRecNumTemp;
#if DEBUH_UART1	
	#if PRIVATE_UART1			
			myprintf( "uPrintBar :%d \r\n",gp_stuConfigFile->uPrintBar );
	#endif
#endif	
			uRecTemp = BUTTON_VALUE_PRINT_BAR;	
			break;
		
		case 9:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);			
			gp_stuConfigFile->uCutEnCu = uRecNumTemp;
#if DEBUH_UART1	
	#if PRIVATE_UART1			
			myprintf( "uCutEnCu :%d \r\n",gp_stuConfigFile->uCutEnCu );
	#endif
#endif	
			uRecTemp = BUTTON_VALUE_PRINT_1BAR;
			break;
		
		case 18:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);			
			gp_stuConfigFile->uSwitchOnOff = uRecNumTemp;
#if DEBUH_UART1	
	#if PRIVATE_UART1			
			myprintf( "uSwitchOnOff :%d \r\n",gp_stuConfigFile->uSwitchOnOff );
	#endif
#endif	
			uRecTemp = BUTTON_VALUE_SWITCH_ONOFF;
			break;
		
		case 19:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);			
			gp_stuConfigFile->uReserveChar[0] = uRecNumTemp;
#if DEBUH_UART1	
	#if PRIVATE_UART1			
			myprintf( "uPrintCurve :%d \r\n",gp_stuConfigFile->uReserveChar[0] );
	#endif
#endif	
			uRecTemp = BUTTON_VALUE_CURVE;
			break;
		
		default:			
			break;
	}
	OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */
	
	return uRecTemp;
}

uint8_t uReplyNumSystemButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize )
{
	CPU_SR_ALLOC();                                             /*申请临界区变量*/	
	uint32_t uRecNumTemp = 0;
	uint8_t uRecTemp = 0;
	
	OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */	
	switch( pButton ){
		case 7:
			uRecNumTemp = puOrdArr[0]+((uint32_t)puOrdArr[1]<<8)+((uint32_t)puOrdArr[2]<<16)+((uint32_t)puOrdArr[3]<<24);
			gp_stuEditInputConfig->ustuAutoTime = uRecNumTemp;
			uRecTemp = BUTTON_VALUE_AUTO_TIME;
			break;
		
		default:			
			break;
	}
	OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */
	
	return uRecTemp;
}

uint8_t uTjc4832tTouchEnable( uint8_t uenable )
{
	if( uenable ) {
		uTjc4832tTouchSwitch( 255,1 ); 
	}else{
		uTjc4832tTouchSwitch( 255,0 ); 
	}	

	return EXE_SUCCEED;
}

uint8_t uTjcAsciiToInt( uint8_t* msgTemp,int32_t * pu32RecTemp,uint8_t strSize )
{
	uint8_t uArrTemp[5] = {0};
	
	if( (strSize<11)&&(strSize>3) ){
		*pu32RecTemp = atoi( (const char *)msgTemp );
	}else{
		switch( strSize ){
			case 1:
				sprintf( (char *)uArrTemp,"%s%c","000",msgTemp[0] );
				*pu32RecTemp = atoi( (const char *)uArrTemp );
				break;
			case 2:
				sprintf( (char *)uArrTemp,"%s%c%c","00",msgTemp[0],msgTemp[1] );
				*pu32RecTemp = atoi( (const char *)uArrTemp );
				break;
			case 3:
				sprintf( (char *)uArrTemp,"%s%c%c%c","0",msgTemp[0],msgTemp[1],msgTemp[2] );
				*pu32RecTemp = atoi( (const char *)uArrTemp );
				break;
			default:
				break;
		}
	}
	
	return EXE_SUCCEED;
}

uint8_t uTjcErrorInvalidOrderEvent( uint8_t uEvent )
{
#if TJC_REPORT_ERROR
	static int32_t l_iCountOrder = 0;
#endif	
	
	switch( uEvent ){
		case TJC_INVALID_ORDER:
#if DEBUH_UART1		
			myprintf( "TJC_INVALID_ORDER \r\n");                          /*  */
#endif
#if TJC_REPORT_ERROR
			if( l_iCountOrder>0 ){
				uTjc4832tSetPage( TJC_WARN_PAGE ); 
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"TJC_INVALID_ORDER \r\n" );
			}
			l_iCountOrder++;
#endif	
			break;
			
		default:
			break;
	}
	
	return EXE_SUCCEED;
}

uint8_t uTjcErrorEvent( uint8_t uEvent )
{
#if TJC_REPORT_ERROR
	uTjc4832tSetPage( TJC_WARN_PAGE ); 
#endif
	switch( uEvent ){		
		case TJC_ORDER_SUCCEED:
#if DEBUH_UART1		
			myprintf( "TJC_ORDER_SUCCEED \r\n");                          /*  */
#endif	
#if TJC_REPORT_ERROR
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"TJC_ORDER_SUCCEED \r\n" );
#endif
			break;
		
		case TJC_ORDERID_INVALID:
#if DEBUH_UART1		
			myprintf( "TJC_ORDERID_INVALID \r\n");                          /*  */
#endif	
#if TJC_REPORT_ERROR
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"TJC_ORDERID_INVALID \r\n" );
#endif
			break;
		
		case TJC_ORDERPAGE_INVALID:
#if DEBUH_UART1		
			myprintf( "TJC_ORDERPAGE_INVALID \r\n");                          /*  */
#endif
#if TJC_REPORT_ERROR		
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"TJC_ORDERPAGE_INVALID \r\n" );
#endif
			break;
		
		case TJC_ORDERPIC_INVALID:
#if DEBUH_UART1		
			myprintf( "TJC_ORDERPIC_INVALID \r\n");                          /*  */
#endif
#if TJC_REPORT_ERROR
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"TJC_ORDERPIC_INVALID \r\n" );
#endif
			break;		
		
		case TJC_ORDERWORD_INVALID:
#if DEBUH_UART1		
			myprintf( "TJC_ORDERWORD_INVALID \r\n");                          /*  */
#endif
#if TJC_REPORT_ERROR
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"TJC_ORDERWORD_INVALID \r\n" );
#endif
			break;
		
		case TJC_BAUDS_INVALID:
#if DEBUH_UART1		
			myprintf( "TJC_BAUDS_INVALID \r\n");                          /*  */
#endif
#if TJC_REPORT_ERROR
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"TJC_BAUDS_INVALID \r\n" );
#endif
			break;
		
		case TJC_CURVE_INVALID:
#if DEBUH_UART1		
			myprintf( "TJC_CURVE_INVALID \r\n");                          /*  */
#endif	
#if TJC_REPORT_ERROR
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"TJC_CURVE_INVALID \r\n" );
#endif
			break;
		
		case TJC_VARIABLE_INVALID:
#if DEBUH_UART1		
			myprintf( "TJC_VARIABLE_INVALID \r\n");                          /*  */
#endif
#if TJC_REPORT_ERROR
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"TJC_VARIABLE_INVALID \r\n" );
#endif
			break;	
		
		case TJC_OPERATOR_INVALID:
#if DEBUH_UART1		
			myprintf( "TJC_OPERATOR_INVALID \r\n");                          /*  */
#endif	
#if TJC_REPORT_ERROR
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"TJC_OPERATOR_INVALID \r\n" );
#endif
			break;
		
		case TJC_ASSIGN_INVALID:
#if DEBUH_UART1		
			myprintf( "TJC_ASSIGN_INVALID \r\n");                          /*  */
#endif
#if TJC_REPORT_ERROR
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"TJC_ASSIGN_INVALID \r\n" );
#endif
			break;
		
		case TJC_EEPROM_INVALID:
#if DEBUH_UART1		
			myprintf( "TJC_EEPROM_INVALID \r\n");                          /*  */
#endif
#if TJC_REPORT_ERROR
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"TJC_EEPROM_INVALID \r\n" );
#endif
			break;
		
		case TJC_PARAM_INVALID:
#if DEBUH_UART1		
			myprintf( "TJC_PARAM_INVALID \r\n");                          /*  */
#endif
#if TJC_REPORT_ERROR
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"TJC_PARAM_INVALID \r\n" );
#endif
			break;		
		
		case TJC_IO_INVALID:
#if DEBUH_UART1		
			myprintf( "TJC_IO_INVALID \r\n");                          /*  */
#endif
#if TJC_REPORT_ERROR
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"TJC_IO_INVALID \r\n" );
#endif
			break;
		
		case TJC_TRANMEAN_INVALID:
#if DEBUH_UART1		
			myprintf( "TJC_TRANMEAN_INVALID \r\n");                          /*  */
#endif
#if TJC_REPORT_ERROR
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"TJC_TRANMEAN_INVALID \r\n" );
#endif
			break;
		
		case TJC_VARLONG_INVALID:
#if DEBUH_UART1		
			myprintf( "TJC_VARLONG_INVALID \r\n");                          /*  */
#endif
#if TJC_REPORT_ERROR
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"TJC_VARLONG_INVALID \r\n" );
#endif		
			break;
		
		default:
			break;
	}
	
	uTjc4832tTouchEnable( TJC_TOUCH_ON );         /* 整页打开触摸 */   
	
	return EXE_SUCCEED;
}
