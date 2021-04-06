/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

				嵌入式开发平台——通用功能

  -------------------------------------------------------
   文 件 名   : Func_Common.c
   版 本 号   : V1.0.0.0
   作    者   : ryc
   生成日期   : 2019年07月19日
   功能描述   : 通用功能定义
   依赖于     : 
 ********************************************************/
#include "Global_Variable.h"
#include "Func_Common.h"
#include "math.h"


/* 初始化函数
 ********************************************************/

/* 通用指令任务函数
 ********************************************************/

/* 步进电机引脚初始化 */
uint8_t uSteopMotorInit( void )
{
	/* 步进电机引脚初始化 */
	BSP_Init_PinInterrupt(MOTOR_RESET_PORT,MOTOR_RESET_PIN);               /* 用于电机复位开关量检测 外部中断 EXTI4 */	
//	BSP_Init_Pin(MOTOR_DECAYA_PORT,MOTOR_DECAYA_PIN,_OUT_PP_);             /* decay a */
//	BSP_Init_Pin(MOTOR_DECAYB_PORT,MOTOR_DECAYB_PIN,_OUT_PP_);             /* decay b */
//	BSP_WritePin(MOTOR_DECAYA_PORT,MOTOR_DECAYA_PIN,MOTOR_DECAYA_FALSE);   /* 默认输出低电平 */
//	BSP_WritePin(MOTOR_DECAYB_PORT,MOTOR_DECAYB_PIN,MOTOR_DECAYB_FALSE);   /* 默认输出高电平 */
	BSP_Init_Pin(MOTOR_SLEEP_PORT,MOTOR_SLEEP_PIN,_OUT_PP_);               /* Sleep 高电平使能  低电平休眠 */
	BSP_Init_Pin(MOTOR_EN_PORT,MOTOR_EN_PIN,_OUT_PP_);                     /* En */
	BSP_Init_Pin(MOTOR_DIR_PORT,MOTOR_DIR_PIN,_OUT_PP_);                   /* Dir */
//	_gp_PWM1 = PWM_Init(PWM_1, _T2_, MOTOR_STEP_PORT, MOTOR_STEP_PIN);     /*初始化PWM波*/
	
	return 0;
}

/* 初始化和设置 */
uint8_t uMax5402GainInitSet( uint16_t uGain,uint8_t uPrompter )
{
	if( UI_Y_PROMPT==uPrompter ){
		uTjc4832tSetPage( TJC_WARN_PAGE );        /*设置为*/
	}
	
	if( (1<=uGain)&&(uGain<=254) ){	
#if MAX5402_CHOISE		

#else
//		_gp_MAX5402 = Max5402euaInit(MAX5402EUA_2,uGain,  \
//									 _PORT_BUTT_,_PIN_BUTT_,MAX5402_SPI_SDO_PORT,MAX5402_SPI_SDO_PIN,  \
//									 MAX5402_SPI_CLK_PORT,MAX5402_SPI_CLK_PIN,MAX5402_SPI_CS_PORT,MAX5402_SPI_CS_PIN);     /* 调解接受光的放大倍数 */	
//		_gp_MAX5402 = Max5402euaInit(MAX5402EUA_2,MAX5402_INIT_VALUE,  \
//							 _PORT_BUTT_,_PIN_BUTT_,MAX5402_SPI_SDO_PORT,MAX5402_SPI_SDO_PIN,  \
//							 MAX5402_SPI_CLK_PORT,MAX5402_SPI_CLK_PIN,MAX5402_SPI_CS_PORT,MAX5402_SPI_CS_PIN);     /* 调解接受光的放大倍数 */	
		
//		Max5402euaSet( _gp_MAX5402,uGain );
#endif
		
		bFuncFlashP25Q32hInit();                                                                        /* 初始化FLASH */
		
		gp_stuConfigFile->uMax5402Gain = uGain;	
		if( EXE_SUCCEED==SPI_Flash_Write_Page( (u8 *)gp_stuConfigFile,SPIFLASH_CONFIG_FILE_BASE_ADDR,sizeof(CONFIG_FILE) ) ){  /* clear */		
			if( UI_Y_PROMPT==uPrompter ){
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Gain Ok" );
			}
#if DEBUH_UART1	
			#if PRIVATE_UART1
//			myprintf( "uGain:%d uMax5402Gain:%d \r\n",uGain,gp_stuConfigFile->uMax5402Gain );                                          /*  */
			#endif
#endif
			return EXE_SUCCEED;	
		}else{		
			if( UI_Y_PROMPT==uPrompter ){
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Gain Error" );
			}
			return EXE_FAILED;
		}
	}else{
		if( UI_Y_PROMPT==uPrompter ){
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"The Range Of 1-254" );
		}		
		return EXE_FAILED;
	}
}

/* 确认是否是IDCard页 */
uint8_t uConfirmIdCardPage( uint8_t uIdPage )
{	
	OS_ERR err = OS_ERR_NONE;
	int16_t iRecPageIDTemp = 0;
	
	iRecPageIDTemp = uTjc4832tGetPage();             /* 获取当前页面ID */
	if( EXE_SPECIAL_FAILED!=iRecPageIDTemp ){
		if( uIdPage!=iRecPageIDTemp ){		     
			uTjc4832tSetPage( uIdPage );       /* 设置为 */
		}else{
			OSTimeDlyHMSM(0, 0, 0, 70,OS_OPT_TIME_HMSM_STRICT,&err);	/* 最好不要小于70 */
			return EXE_SUCCEED;
		}
	}else{
#if DEBUH_UART1	
		myprintf( "iRecPageIDTemp Error  \r\n" );
#endif
	}
	
	iRecPageIDTemp = uTjc4832tGetPage();             /* 获取当前页面ID */
	if( EXE_SPECIAL_FAILED!=iRecPageIDTemp ){
		if( uIdPage==iRecPageIDTemp ){		     
			return EXE_SUCCEED;
		}else{
			return EXE_FAILED;
		}
	}else{
#if DEBUH_UART1	
		myprintf( "iRecPageIDTemp Error  \r\n" );
#endif
		return EXE_FAILED;
	}	
}

/* 确认是否是页 不是设置为页  */
uint8_t uConfirmPage( uint8_t uPage )
{
	int16_t iRecPageIDTemp = 0;
	uint8_t i = 0;
	
	iRecPageIDTemp = uTjc4832tGetPage();             /* 获取当前页面ID */	
	if( EXE_SPECIAL_FAILED!=iRecPageIDTemp ){
		return uConfirmSetPage( uPage,iRecPageIDTemp );
	}else{
		while(i<TJC_PAGE_ERROR_MAX){
			iRecPageIDTemp = uTjc4832tGetPage();             /* 获取当前页面ID */
			if( EXE_SPECIAL_FAILED!=iRecPageIDTemp ){
				return uConfirmSetPage( uPage,iRecPageIDTemp );
			}
			i++;
		}
#if DEBUH_UART1	
		myprintf( "iRecPageIDTemp Error  \r\n" );
#endif
		return EXE_FAILED;	
	}	
}

uint8_t uConfirmSetPage( uint8_t uPage,int16_t iGetPage )
{
	OS_ERR err = OS_ERR_NONE;
	
	if( uPage!=iGetPage ){
		uTjc4832tSetPage( uPage );               /*  */
		OSTimeDlyHMSM(0, 0, 0, 70,OS_OPT_TIME_HMSM_STRICT,&err);	             /* 最好不要小于70 */
		return EXE_SUCCEED;	
	}else{
		OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	             /* 最好不要小于70 */
		return EXE_SUCCEED;	
	}
}

/* 需要考虑出现连续错误的时候 不需要频繁切换页面 */
uint8_t uAllConfigSet( USER_INPUT_CONFIG_FILE* pstuConfig )
{
	if( EXE_FAILED==uSampleOffsetSet( pstuConfig->ustuOffset,UI_N_PROMPT ) ){		
		uConfirmPage( TJC_WARN_PAGE );        /* 设置为警告页 */
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"The Range Of 1-254 " );	
		uBuzzerTimes( BUZZER_ONE_TIME );
		return EXE_FAILED;
	}
	if( EXE_FAILED==uMax5402GainInitSet( pstuConfig->ustuGain,UI_N_PROMPT ) ){
		uConfirmPage( TJC_WARN_PAGE );        /* 设置为警告页 */
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"The Range Of 1-254" );
		uBuzzerTimes( BUZZER_ONE_TIME );
		return EXE_FAILED;
	}	
	if( EXE_FAILED==uSampleBarOffsetSet( pstuConfig->ustuBarOffset,UI_N_PROMPT ) ){
		uConfirmPage( TJC_WARN_PAGE );        /* 设置为警告页 */
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"The Range Of 1-254" );
		uBuzzerTimes( BUZZER_ONE_TIME );
		return EXE_FAILED;
	}
	if( EXE_FAILED==uSetCoeffValue( pstuConfig->fstuCoeff,UI_N_PROMPT ) ){
		uConfirmPage( TJC_WARN_PAGE );        /* 设置为警告页 */
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"The Range Of 1-254" );
		uBuzzerTimes( BUZZER_ONE_TIME );
		return EXE_FAILED;
	}
	if( EXE_FAILED==uSetLanboRefValue( pstuConfig->ustuInputLanRef,UI_N_PROMPT )){
		uConfirmPage( TJC_WARN_PAGE );        /* 设置为警告页 */
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"The Range Of 1-311" );
		uBuzzerTimes( BUZZER_ONE_TIME );
		return EXE_FAILED;
	}
	
	uTjc4832tSetPage( TJC_INSTRUMENT_PAGE );        /*设置为*/
	return EXE_SUCCEED;
}

/* 需要考虑出现连续错误的时候 不需要频繁切换页面 */
uint8_t uSystemAllConfigSet( USER_INPUT_CONFIG_FILE* pstuConfig )
{
	if( EXE_FAILED==uAutoShutdownSet( pstuConfig->ustuAutoTime,UI_N_PROMPT ) ){
		uConfirmPage( TJC_WARN_PAGE );        /* 设置为警告页 */
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"The Range Of 1-99" );
		uBuzzerTimes( BUZZER_ONE_TIME );
		return EXE_FAILED;
	}
	
	/* 保存打印抬头 */
	if( EXE_FAILED==uSetPrintTitles(g_uInputPrintTitles,strlen((const char *)g_uInputPrintTitles),UI_N_PROMPT)){
		uConfirmPage( TJC_WARN_PAGE );        /* 设置为警告页 */
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"The Range Of 1-48" );
		uBuzzerTimes( BUZZER_ONE_TIME );
		return EXE_FAILED;
	}
	
	uTjc4832tSetPage( TJC_SET_PAGE );        /*设置为*/
	return EXE_SUCCEED;
}

uint8_t uSampleOffsetSet( uint16_t uOffsetSet,uint8_t uPrompter )
{
	if( UI_Y_PROMPT==uPrompter ){
		uTjc4832tSetPage( TJC_WARN_PAGE );        /*设置为*/
	}
	if( (1<=uOffsetSet)&&(uOffsetSet<=254) ){	
		
		//SPI_Flash_Init();  		//SPI FLASH 初始化 ;   /* 后续可能不需要再初始化 */
		
		gp_stuConfigFile->uStartOffset = uOffsetSet;
		
		if( EXE_SUCCEED==SPI_Flash_Write_Page( (u8 *)gp_stuConfigFile,SPIFLASH_CONFIG_FILE_BASE_ADDR,sizeof(CONFIG_FILE) ) ){ /* clear */	
			if( UI_Y_PROMPT==uPrompter ){
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Offset Ok" );
			}
#if DEBUH_UART1		
			myprintf( "uOffsetSet:%d uStartOffset:%d \r\n",uOffsetSet,gp_stuConfigFile->uStartOffset );                                          /*  */
#endif	
			return EXE_SUCCEED;	
		}else{
			if( UI_Y_PROMPT==uPrompter ){
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Offset Error" );
			}
			return EXE_FAILED;
		}			
	}else{
		if( UI_Y_PROMPT==uPrompter ){
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"The Range Of 1-254 " );	
			uBuzzerTimes( BUZZER_ONE_TIME );
		}
		return EXE_FAILED;
	}	
}

uint8_t uSampleBarOffsetSet( uint16_t uOffsetSet,uint8_t uPrompter )
{
	if( UI_Y_PROMPT==uPrompter ){
		uTjc4832tSetPage( TJC_WARN_PAGE );        /*设置为*/
	}
	if( (1<=uOffsetSet)&&(uOffsetSet<=254) ){		
		
		gp_stuConfigFile->uBarOffset = uOffsetSet;
		
		if( EXE_SUCCEED==SPI_Flash_Write_Page( (u8 *)gp_stuConfigFile,SPIFLASH_CONFIG_FILE_BASE_ADDR,sizeof(CONFIG_FILE) ) ){  /* clear */	
			if( UI_Y_PROMPT==uPrompter ){
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"BarOffset Ok" );
			}
#if DEBUH_UART1		
			myprintf( "uBarSet:%d uBarOffset:%d \r\n",uOffsetSet,gp_stuConfigFile->uBarOffset );                                          /*  */
#endif		
			return EXE_SUCCEED;	
		}else{
			if( UI_Y_PROMPT==uPrompter ){
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"BarOffset Error" );
			}
			return EXE_FAILED;
		}	
	}else{
		if( UI_Y_PROMPT==uPrompter ){
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"The Range Of 1-254" );
			uBuzzerTimes( BUZZER_ONE_TIME );
		}
		return EXE_FAILED;
	}
}

uint8_t uAutoShutdownSet( uint8_t uTimes,uint8_t uPrompter )
{
	if( UI_Y_PROMPT==uPrompter ){
		uTjc4832tSetPage( TJC_WARN_PAGE );        /*设置为*/
	}
	if( (1<=uTimes)&&(uTimes<=99) ){	
		
		gp_stuConfigFile->uAutoShutDown = uTimes;
		
		if( EXE_SUCCEED==SPI_Flash_Write_Page( (u8 *)gp_stuConfigFile,SPIFLASH_CONFIG_FILE_BASE_ADDR,sizeof(CONFIG_FILE) ) ){ /* clear */		
			if( UI_Y_PROMPT==uPrompter ){
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"ShutDown Ok" );	
			}
		}else{
			if( UI_Y_PROMPT==uPrompter ){
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"ShutDown Error" );
			}		
		}
		
#if DEBUH_UART1		
		myprintf( "uTimes:%d uAutoShutDown:%d \r\n",uTimes,gp_stuConfigFile->uAutoShutDown );                                          /*  */
#endif		
		return EXE_SUCCEED;	
	}else{
		if( UI_Y_PROMPT==uPrompter ){
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"The Range Of 1-99" );
			uBuzzerTimes( BUZZER_ONE_TIME );
		}
		return EXE_FAILED;
	}
}

uint8_t uSetPrintTitles( uint8_t* puTempTitles,uint8_t uNum,uint8_t uPrompter )
{
	if( UI_Y_PROMPT==uPrompter ){
		uTjc4832tSetPage( TJC_WARN_PAGE );        /*设置为*/
	}
	if( (1<=uNum)&&(uNum<48) ){
		memset( g_uPrintTitles,0,sizeof(g_uPrintTitles) );
		memcpy( g_uPrintTitles,puTempTitles,uNum );
		if( EXE_SUCCEED==SPI_Flash_Write_Page( (u8 *)g_uPrintTitles,SPIFLASH_P_TITLES_BASE_ADDR,sizeof(g_uPrintTitles) ) ){ /* clear */		
			if( UI_Y_PROMPT==uPrompter ){
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Title Ok" );	
			}
		}else{
			if( UI_Y_PROMPT==uPrompter ){
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Title Error" );
			}		
		}
		
#if DEBUH_UART1		
		myprintf( "Titles:%s \r\n",puTempTitles );                                          /*  */
#endif		
		return EXE_SUCCEED;	
	}else{
		if( UI_Y_PROMPT==uPrompter ){
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"The Range Of 1-48" );
			uBuzzerTimes( BUZZER_ONE_TIME );
		}
		return EXE_FAILED;
	}
}
	
/* 打开/关闭 3V 电源*/
uint8_t uCtrl3VPower( uint8_t uOnOff )
{
	if( CTRL_POWER3_ON==uOnOff ){
		BSP_WritePin(POWER3_CONTROL_PORT,POWER3_CONTROL_PIN,POWER3_CONTROL_TRUE);          /*开启电源	*/
	}else if( CTRL_POWER3_OFF==uOnOff ){
//		BSP_WritePin(POWER3_CONTROL_PORT,POWER3_CONTROL_PIN,POWER3_CONTROL_FALSE);           /*关闭电源	*/
	}
		
	return 0;
}
	

/* 打开/关闭 5V 电源*/
uint8_t uCtrl5VPower( uint8_t uOnOff )
{
	if( CTRL_POWER5_ON==uOnOff ){
		BSP_WritePin(POWER5_CONTROL_PORT,POWER5_CONTROL_PIN,POWER5_CONTROL_TRUE );          /*开启电源	*/
	}else if( CTRL_POWER5_OFF==uOnOff ){
//		BSP_WritePin(POWER5_CONTROL_PORT,POWER5_CONTROL_PIN,POWER5_CONTROL_FALSE );           /*关闭电源	*/
	}
		
	return 0;
}

/* 自动控制 电源*/
uint8_t uCtrlPower( uint8_t uOnOff )
{
	if( CTRL_POWER_ON==uOnOff ){
		BSP_WritePin(POWER_CONTROL_PORT,POWER_CONTROL_PIN,POWER_CONTROL_TRUE);          /*开启电源	*/
	}else if( CTRL_POWER5_OFF==uOnOff ){
//		BSP_WritePin(POWER_CONTROL_PORT,POWER_CONTROL_PIN,POWER_CONTROL_FALSE);           /*关闭电源	*/
	}
		
	return 0;
}

/* 打开/关闭 Buzzer */
uint8_t uBuzzer( uint8_t uOnOff )
{
	if( BUZZER_ON==gp_stuConfigFile->uBuzzerOnOff ){
		if( BUZZER_ON==uOnOff ){
			BSP_WritePin(BUZZER_CONTORL_PORT,BUZZER_CONTORL_PIN,BUZZER_CONTORL_TRUE);          /*开启Buzzer	*/
		}else if( BUZZER_OFF==uOnOff ){
			BSP_WritePin(BUZZER_CONTORL_PORT,BUZZER_CONTORL_PIN,BUZZER_CONTORL_FALSE);          /*关闭Buzzer	*/
		}
	}
		
	return 0;
}

/* 打开/关闭 CTRL_LED灯 */
uint8_t uFluorescenceLight( uint8_t uOnOff )
{
	if( FLUORESCENCE_ON==uOnOff ){
		BSP_WritePin( LED_GLOW_CONTORL_PORT,LED_GLOW_CONTORL_PIN,LED_GLOW_CONTORL_TRUE );            /* 打开 CTRL_LED灯	 */
		gp_stuConfigFile->uLedOnOff = FLUORESCENCE_ON;
	}else if( FLUORESCENCE_OFF==uOnOff ){
		BSP_WritePin( LED_GLOW_CONTORL_PORT,LED_GLOW_CONTORL_PIN,LED_GLOW_CONTORL_FALSE );           /* 关闭CTRL_LED灯	*/
		gp_stuConfigFile->uLedOnOff = FLUORESCENCE_OFF;
	}
		
	return 0;
}

uint8_t uConfigAllFileInit( void )
{
	if( 0xff==gp_stuConfigFile->uPrintfOnOff )
	{
		gp_stuConfigFile->uPrintfOnOff = GY_K950E_ON;
	}
	if( 0xffff==gp_stuConfigFile->uStartOffset )
	{
		gp_stuConfigFile->uStartOffset = 1;
	}
	if( 0xffff==gp_stuConfigFile->uMax5402Gain )
	{
		gp_stuConfigFile->uMax5402Gain = MAX5402_INIT_VALUE;
	}	
	if( 0xffff==gp_stuConfigFile->uBarOffset )
	{
		gp_stuConfigFile->uBarOffset = 45;
	}
	if( 0xffff==gp_stuConfigFile->uLanReferValue){
		gp_stuConfigFile->uLanReferValue=120;
	}
	if( 0xff==gp_stuConfigFile->uBuzzerOnOff ){
		gp_stuConfigFile->uBuzzerOnOff = BUZZER_OFF;
	}
	if( 0xff==gp_stuConfigFile->uAutoShutDown ){
		gp_stuConfigFile->uAutoShutDown = 5;
	}
	if( 0xff==gp_stuConfigFile->uPrintAD ){
		gp_stuConfigFile->uPrintAD = PRINT_AD_ON;//PRINT_AD_OFF;
	}
	if( 0xff==gp_stuConfigFile->uPrintBar ){
		gp_stuConfigFile->uPrintBar = PRINT_BAR_ON;//PRINT_BAR_OFF;
	}
	if( 0xff==gp_stuConfigFile->uLedOnOff ){
		gp_stuConfigFile->uLedOnOff = FLUORESCENCE_OFF;
	}
	if( 0xff==gp_stuConfigFile->uScanBar ){
		gp_stuConfigFile->uScanBar = SCAN_BAR_ON;
	}
	if( 0xff==gp_stuConfigFile->uWifiOnOff ){
		gp_stuConfigFile->uWifiOnOff = WIFI_OFF;
	}
	if( 0xff==gp_stuConfigFile->uCutEnCu ){
		gp_stuConfigFile->uCutEnCu = EN_ON;//CH_ON;//EN_ON;
	}
	if( 0xff==gp_stuConfigFile->uSwitchOnOff ){
		gp_stuConfigFile->uSwitchOnOff = SWITCH_MIC_ON;
	}
	if( 1==isnan(gp_stuConfigFile->fCoeff) ){
		gp_stuConfigFile->fCoeff = CONCERSION_COFFICIENT;
	}
	if( (0xff==gp_stuConfigFile->uSNStrNum[0]) ){
		memcpy( gp_stuConfigFile->uSNStrNum,"",1 );
	}
	
	return 0;
}

/* 流水号初始化 */
uint8_t uSerialFileInit( void )
{		
	if( (0==g_projectSerial.serial_num)||(0xffff==g_projectSerial.serial_num)||(0xffff==g_projectSerial.history_count) ){	
		sprintf( (char *)g_projectSerial.serial_id,"%04d%02d%02d%04d",calendar.w_year,calendar.w_month,calendar.w_date,(g_projectSerial.serial_num+1) );    /* 流水号的编码规则日期加流水号 */
		g_projectSerial.history_count = 0;			
	}
	
	if( (0==g_projectSerial.uid_count)||(0xff==g_projectSerial.uid_count) ){
		g_projectSerial.uid_count = 0;
	}
	
	if( EXE_SUCCEED==SPI_Flash_Write_Page( (uint8_t *)&g_projectSerial,SPIFLASH_SERIAL_BASE_ADDR,sizeof(PRO_SERIAL) ) ){ /* clear */
		return EXE_SUCCEED;
	}else{
		return EXE_FAILED;
	}
}

uint8_t uClearIdData( void )
{
//	uTjc4832tSetLableValue( TJC_ID_PAGE,ID_NUM_DIS_CON_ID,(uint8_t *)"" );
//	uTjc4832tSetLableValue( TJC_ID_PAGE,ID_ITEM_DIS_CON_ID,(uint8_t *)"" );
//	uTjc4832tSetLableValue( TJC_ID_PAGE,ID_BAR_DIS_CON_ID,(uint8_t *)"" );
//	uTjc4832tSetLableValue( TJC_ID_PAGE,ID_WAVE_DIS_CON_ID,(uint8_t *)"" );	
//	uTjc4832tSetLableValue( TJC_ID_PAGE,ID_CURRENT_DIS_CON_ID,(uint8_t *)"" );
	
	return EXE_SUCCEED;
}

uint8_t uReadIdItem( void )
{
//	OS_ERR err;
//	uint8_t i = 0;
//	uint8_t uRecError = 0;
//	UINTE_DATA_TYPE* pTempUinteData = NULL;
//	
//	if( !BSP_ReadPin(ID_DETECT_PORT,ID_DETECT_PIN) ){ 
//		uIdCountCheck();                                                             /* 保证初始状态正确 */		
//		uRecError = uInitIdInfo( &g_IdMemory ); 			                         /* 初始化全读 */
//		if( EXE_FAILED==uRecError ){
//			return uRecError;
//		}
//		OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);                     /* 延时100ms */		
//		pTempUinteData = (UINTE_DATA_TYPE *)calloc( 1,sizeof(UINTE_DATA_TYPE) );     /* 当局部变量使用 */
//		if( NULL==pTempUinteData ){		
//			vForceWarn();                                                            /* 不可恢复警告 */
//		}
//		
//		if( g_IdMemory.children_num<=MAX_CHILDER ){                                            /* 子项最多3个 */
//			for( i=0;i<g_IdMemory.children_num;i++ ){									
//				uRecError = uInitIdChildren( pTempUinteData,i,COVER_ID_CHI_OFF );		                       /* 不覆盖存储 */
//				if( EXE_FAILED==uRecError ){
//					if( NULL!=pTempUinteData ){
//						free( pTempUinteData );
//					}
//					return uRecError;
//				}				
//				memset( (uint8_t *)pTempUinteData,0,sizeof(UINTE_DATA_TYPE) );				
//				OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);  /* 延时100ms */
//			}
//		}else{
//			uConfirmPage( TJC_WARN_PAGE );                                              /*设置为强制警告页*/
//			uTjc4832tSetLableValuePco( TJC_WARN_PAGE,WARN_ID_NUM,TJC_RED );
//			OSTimeDlyHMSM(0, 0, 0, 20,OS_OPT_TIME_HMSM_STRICT,&err);  
//			uTjc4832tSetLableValuePco( TJC_WARN_PAGE,WARN_ID_NUM,TJC_RED );
//			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Format error" );	
//			uBuzzerTimes( BUZZER_ONE_TIME );
//			uRecError = EXE_FAILED;
//		}	
//		
//		uSetIdCount();     /* 记录ID卡 */
//		
//		if( NULL!=pTempUinteData ){
//			free( pTempUinteData );
//		}
//		
//		//memset( (unsigned char *)&g_stuUserReference,0,sizeof(USER_REFERRENCE) );           /* 清除参考范围 */
//	}else{
//		uConfirmPage( TJC_WARN_PAGE );        /*设置为*/
//		
//		if( EN_ON==gp_stuConfigFile->uCutEnCu ){
//			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Please insert the ID card" );	
//		}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
//			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"请插入ID卡" );
//		}else{
//			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Invalid" );	             //ID数据错误
//		}
//		
//		uBuzzerTimes( BUZZER_ONE_TIME );
//	}

	return EXE_SUCCEED;
}

uint8_t uChangeIdCard( ID_Info *pIdCard )
{
	uint8_t i = 0;
	uint16_t uTemps = 0;
	uint16_t uTempe = 0;
	
	for( i=0;i<pIdCard->peak_num;i++){
		uTemps = pIdCard->interval_s[i];
		uTempe = pIdCard->interval_e[i];

#if	EN_REVERSE_INT_ARR	
		pIdCard->interval_s[i] = (uint16_t)(((float)uTemps)*(gp_stuConfigFile->fCoeff));
		pIdCard->interval_e[i] = (uint16_t)(((float)uTempe)*(gp_stuConfigFile->fCoeff));	
#else
//		pIdCard->interval_s[i] = (uint16_t)((float)MAPID_ADDRA-(((float)uTempe)*gp_stuConfigFile->fCoeff));
//		pIdCard->interval_e[i] = (uint16_t)((float)MAPID_ADDRA-(((float)uTemps)*gp_stuConfigFile->fCoeff));
		pIdCard->interval_s[i] = (uint16_t)((float)((uint16_t)MAPID_ADDRB-uTempe)*(gp_stuConfigFile->fCoeff));
		pIdCard->interval_e[i] = (uint16_t)((float)((uint16_t)MAPID_ADDRB-uTemps)*(gp_stuConfigFile->fCoeff));
#endif
		
#if DEBUH_UART1	
		myprintf( "ChangeIdCard S: %d E: %d \r\n",pIdCard->interval_s[i],pIdCard->interval_e[i] );
#endif
	}
	
	return EXE_SUCCEED;
}

ID_Info* uReadStoreIdItem( int8_t iIdNum )
{
//	if( (iIdNum<MAX_IDCARD_NUM)&&(iIdNum>=0) ){
//		SPI_Flash_Read( (uint8_t *)(&g_IdMemory),SPIFLASH_IDA_BASE_ADDR+(iIdNum*SPIFLASH_ID_NUM_BASE),sizeof(g_IdMemory) );
//		return &g_IdMemory;
//	}else{	
		return NULL;
//	}	
}

ID_Info* uReadStoreIdItemCope( int8_t iIdNum,ID_Info* pstuTempIDCard )
{
//	if( (iIdNum<MAX_IDCARD_NUM)&&(iIdNum>=0) ){
//		SPI_Flash_Read( (uint8_t *)pstuTempIDCard,SPIFLASH_IDA_BASE_ADDR+(iIdNum*SPIFLASH_ID_NUM_BASE),sizeof(g_IdMemory) );
//		return pstuTempIDCard;
//	}else{	
		return NULL;
//	}
}

uint8_t uIdDisplay( uint8_t uCurrent )
{
	OS_ERR err;	
//	char strff[64] = {0};
	
//	memset( strff,0,sizeof(strff) );
//	sprintf( strff,"%d",g_projectSerial.uid_max );
//	uTjc4832tSetLableValue( TJC_ID_PAGE,ID_NUM_DIS_CON_ID,(uint8_t *)strff );

//	memset( strff,0,sizeof(strff) );
//	memcpy( (char *)strff,(const char *)g_IdMemory.project_name,sizeof(strff) );
//	uTjc4832tSetLableValue( TJC_ID_PAGE,ID_ITEM_DIS_CON_ID,(uint8_t *)strff );

//	memset( strff,0,sizeof(strff) );
//	sprintf( strff,"%s",(const char *)g_IdMemory.barcode );
//	uTjc4832tSetLableValue( TJC_ID_PAGE,ID_BAR_DIS_CON_ID,(uint8_t *)strff );

//	memset( strff,0,sizeof(strff) );
//	sprintf( strff,"%d",g_IdMemory.children_num );
//	uTjc4832tSetLableValue( TJC_ID_PAGE,ID_WAVE_DIS_CON_ID,(uint8_t *)strff );
//	
//	memset( strff,0,sizeof(strff) );
//	sprintf( strff,"%d",uCurrent );
//	uTjc4832tSetLableValue( TJC_ID_PAGE,ID_CURRENT_DIS_CON_ID,(uint8_t *)strff );
	
	uTjc4832tSetLableValuePco( TJC_WARN_PAGE,WARN_ID_NUM,TJC_GREEN );             /* 设置为绿色字体 */
	OSTimeDlyHMSM(0, 0, 0, 20,OS_OPT_TIME_HMSM_STRICT,&err);
	uTjc4832tSetLableValuePco( TJC_WARN_PAGE,WARN_ID_NUM,TJC_GREEN );             /* 设置为绿色字体 */
	uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Read ID Successful" );	
//	uTjc4832tSetLableValuePco( TJC_PROMPTER_PAGE,PROMPTER_ID_TXT,TJC_RED );
	
	return EXE_SUCCEED;
}

uint8_t uIdPageDisplay( uint8_t uCurrent )
{
//	char strff[64] = {0};
//	
//	memset( strff,0,sizeof(strff) );
//	sprintf( strff,"%d",g_projectSerial.uid_max );
//	uTjc4832tSetLableValue( TJC_ID_PAGE,ID_NUM_DIS_CON_ID,(uint8_t *)strff );

//	memset( strff,0,sizeof(strff) );
//	memcpy( (char *)strff,(const char *)g_IdMemory.project_name,sizeof(strff) );
//	uTjc4832tSetLableValue( TJC_ID_PAGE,ID_ITEM_DIS_CON_ID,(uint8_t *)strff );

//	memset( strff,0,sizeof(strff) );
//	sprintf( strff,"%s",(const char *)g_IdMemory.barcode );
//	uTjc4832tSetLableValue( TJC_ID_PAGE,ID_BAR_DIS_CON_ID,(uint8_t *)strff );

//	memset( strff,0,sizeof(strff) );
//	sprintf( strff,"%d",g_IdMemory.children_num );
//	uTjc4832tSetLableValue( TJC_ID_PAGE,ID_WAVE_DIS_CON_ID,(uint8_t *)strff );
//	
//	memset( strff,0,sizeof(strff) );
//	sprintf( strff,"%d",uCurrent+1 );
//	uTjc4832tSetLableValue( TJC_ID_PAGE,ID_CURRENT_DIS_CON_ID,(uint8_t *)strff );
//	
//	uTjc4832tSetLableValuePco( TJC_WARN_PAGE,WARN_ID_NUM,TJC_GREEN );             /* 设置为绿色字体 */
//	uTjc4832tSetLableValuePco( TJC_WARN_PAGE,WARN_ID_NUM,TJC_GREEN );             /* 设置为绿色字体 */
//	uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Read ID Successful" );	
//	uTjc4832tSetLableValuePco( TJC_PROMPTER_PAGE,PROMPTER_ID_TXT,TJC_RED );
	
	return EXE_SUCCEED;
}

uint8_t uIdDisplayUpDown( uint8_t uUpDown )
{
	static uint8_t l_uRecPage = 0;
	static uint8_t l_uRecPageUpDown = 0;
	
	l_uRecPage = g_projectSerial.uid_max;
	
	uClearIdData();                 /* 清空上次数据  */
	if( l_uRecPage>0 ){
		if( BUTTON_VALUE_IDCARD_UP==uUpDown ){
			if( l_uRecPage>l_uRecPageUpDown ){  
				l_uRecPageUpDown++;
				if( l_uRecPage==l_uRecPageUpDown ){
					l_uRecPageUpDown = 0;
				}
			}else{
				l_uRecPageUpDown = 0;
			}		
		}else if( BUTTON_VALUE_IDCARD_DOWN==uUpDown ){
			if( l_uRecPageUpDown>0 ){
				l_uRecPageUpDown--;
			}else{	
				l_uRecPageUpDown = l_uRecPage-1;
				if( l_uRecPageUpDown<=0 ){
					l_uRecPageUpDown = 0;
				}
			}		
		}else{
			l_uRecPageUpDown = 0;
		}
		
		if( NULL!=uReadStoreIdItem( l_uRecPageUpDown ) ){  /* 从本地存储读取 */		
//			uIdDisplay( l_uRecPageUpDown );                /* 显示结果 */	
			uIdPageDisplay( l_uRecPageUpDown );
		}
	}else{
		uTjc4832tSetPage( TJC_WARN_PAGE );                                          /* 警告 */		
		if( EN_ON==gp_stuConfigFile->uCutEnCu ){
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"No ID data");	//
		}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"卡无数据");	//
		}else{
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"No ID data");	//
		}
		uBuzzerTimes( BUZZER_ONE_TIME );
	}

	return EXE_SUCCEED;
}

uint8_t uIdCountCheck( void )
{
	if( g_projectSerial.uid_count>=MAX_IDCARD_NUM ){
		g_projectSerial.uid_count = 0;
	}
	if( g_projectSerial.uid_max>MAX_IDCARD_NUM ){
		g_projectSerial.uid_max = MAX_IDCARD_NUM;
	}
	
	return EXE_SUCCEED;
}

int8_t uGetIdCountValue( void )
{
	if( (g_projectSerial.uid_count>0)&&(g_projectSerial.uid_count<=MAX_IDCARD_NUM) ){
		return g_projectSerial.uid_count-1;
	}else{
		g_projectSerial.uid_count = 0;
		return g_projectSerial.uid_count;
//		return EXE_SPECIAL_FAILED;
	}	
}

uint8_t uSetIdCount( void )
{	
	if( g_projectSerial.uid_count<MAX_IDCARD_NUM ){
		g_projectSerial.uid_count++;		
		if( MAX_IDCARD_NUM!=g_projectSerial.uid_max ){
			g_projectSerial.uid_max = g_projectSerial.uid_count;
		}		
	}else{
		g_projectSerial.uid_count = 0;
		if( g_projectSerial.uid_max>MAX_IDCARD_NUM ){
			g_projectSerial.uid_max = MAX_IDCARD_NUM;
		}
	}
	
	if( EXE_SUCCEED==SPI_Flash_Write_Page( (uint8_t *)&g_projectSerial,SPIFLASH_SERIAL_BASE_ADDR,sizeof(PRO_SERIAL) ) ){  /* clear */	
		return EXE_SUCCEED;
	}else{
		return EXE_FAILED;
	}
}

uint8_t uConfigPrintfFile( void )
{	
	if( GY_K950E_ON==gp_stuConfigFile->uPrintfOnOff ){
		gp_stuConfigFile->uPrintfOnOff = GY_K950E_ON;
		
		uPromptInformation( (uint8_t *)"Print On" ); 
	}else if( GY_K950E_OFF==gp_stuConfigFile->uPrintfOnOff ){
		gp_stuConfigFile->uPrintfOnOff = GY_K950E_OFF;	
		
		uPromptInformation( (uint8_t *)"Print Off" );			
	}else{
		gp_stuConfigFile->uPrintfOnOff = GY_K950E_OFF;
		
		uPromptInformation( (uint8_t *)"Print Off" );
	}
	
	if( EXE_SUCCEED==SPI_Flash_Write_Page( (u8 *)gp_stuConfigFile,SPIFLASH_CONFIG_FILE_BASE_ADDR,sizeof(CONFIG_FILE) ) ){  /* clear */	
		return EXE_SUCCEED;
	}else{
		uPromptInformation( (uint8_t *)"Print Error" );
		return EXE_FAILED;
	}
}

uint8_t uConfigBuzzerFile( void )
{	
	if( BUZZER_ON==gp_stuConfigFile->uBuzzerOnOff ){
		gp_stuConfigFile->uBuzzerOnOff = BUZZER_ON;
		
		uPromptInformation( (uint8_t *)"Buzzer On" );		
	}else if( BUZZER_OFF==gp_stuConfigFile->uBuzzerOnOff ){
		gp_stuConfigFile->uBuzzerOnOff = BUZZER_OFF;	
		
		uPromptInformation( (uint8_t *)"Buzzer Off" );	
	}else{
		gp_stuConfigFile->uBuzzerOnOff = BUZZER_OFF;
		
		uPromptInformation( (uint8_t *)"Buzzer Off" );
	}
	
	if( EXE_SUCCEED==SPI_Flash_Write_Page( (u8 *)gp_stuConfigFile,SPIFLASH_CONFIG_FILE_BASE_ADDR,sizeof(CONFIG_FILE) ) ){  /* clear */	
		return EXE_SUCCEED;
	}else{
		uPromptInformation( (uint8_t *)"Buzzer Error" );
		return EXE_FAILED;
	}
}

uint8_t uConfigScanBarFile( void )
{	
	if( SCAN_BAR_ON==gp_stuConfigFile->uScanBar ){
		gp_stuConfigFile->uScanBar = SCAN_BAR_ON;
			
		uPromptInformation( (uint8_t *)"ScanBar on" );
	}else if( SCAN_BAR_OFF==gp_stuConfigFile->uScanBar ){
		gp_stuConfigFile->uScanBar = SCAN_BAR_OFF;	
		
		uPromptInformation( (uint8_t *)"ScanBar Off" );
	}else{
		gp_stuConfigFile->uScanBar = SCAN_BAR_OFF;
		
		uPromptInformation( (uint8_t *)"ScanBar Off" );
	}
	
	if( EXE_SUCCEED==SPI_Flash_Write_Page( (u8 *)gp_stuConfigFile,SPIFLASH_CONFIG_FILE_BASE_ADDR,sizeof(CONFIG_FILE) ) ){  /* clear */	
		return EXE_SUCCEED;
	}else{
		uPromptInformation( (uint8_t *)"ScanBar Error" );
		return EXE_FAILED;
	}
}

uint8_t uConfigPrintADFile( void )
{	
	if( PRINT_AD_ON==gp_stuConfigFile->uPrintAD ){
		gp_stuConfigFile->uPrintAD = PRINT_AD_ON;
			
		uPromptParameter( (uint8_t *)"AD on" );
	}else if( PRINT_AD_OFF==gp_stuConfigFile->uPrintAD ){
		gp_stuConfigFile->uPrintAD = PRINT_AD_OFF;	
		
		uPromptParameter( (uint8_t *)"AD Off" );
	}else{
		gp_stuConfigFile->uPrintAD = PRINT_AD_OFF;
		
		uPromptParameter( (uint8_t *)"AD Off" );
	}
	
	if( EXE_SUCCEED==SPI_Flash_Write_Page( (u8 *)gp_stuConfigFile,SPIFLASH_CONFIG_FILE_BASE_ADDR,sizeof(CONFIG_FILE) ) ){  /* clear */	
		return EXE_SUCCEED;
	}else{
		uPromptParameter( (uint8_t *)"AD Error" );
		return EXE_FAILED;
	}
}

uint8_t uConfigWifiBluetoothFile( void )
{ 
//	OS_ERR err;
	
	if( WIFI_ON==gp_stuConfigFile->uWifiOnOff ){
//		uTjc4832tTouchEnable( TJC_TOUCH_OFF );                                                                 /* 整页关闭触摸 */ 
		
		gp_stuConfigFile->uWifiOnOff = WIFI_ON;		
		uWifiOpenClose( WIFI_W01_E103_ON );                 /* 打开WIFI */
//		OSTimeDlyHMSM(0, 0, 0, 500,OS_OPT_TIME_HMSM_STRICT,&err);                                              /* 等待Wifi启动 */	
//		uWifiInit();                                        /* 初始化 */ 	
//		uClassicBluetoothInit();                            /* 经典蓝牙初始化 */		
		uPromptInformation( (uint8_t *)"WIFI on" );
		
//		uTjc4832tTouchEnable( TJC_TOUCH_ON );                                                                  /* 整页打开触摸 */
	}else if( WIFI_OFF==gp_stuConfigFile->uWifiOnOff ){
		gp_stuConfigFile->uWifiOnOff = WIFI_OFF;
		g_uWifiConnect = WIFI_CONNEST_DISLINE;
		uWifiOpenClose( WIFI_W01_E103_OFF );                /* 关闭WIFI */
		
		uPromptInformation( (uint8_t *)"WIFI Off" );
	}else{
		gp_stuConfigFile->uWifiOnOff = WIFI_OFF;
		g_uWifiConnect = WIFI_CONNEST_DISLINE;
		uWifiOpenClose( WIFI_W01_E103_OFF );               /* 关闭WIFI */
		
		uPromptInformation( (uint8_t *)"WIFI Off" );
	}
	
	if( EXE_SUCCEED==SPI_Flash_Write_Page( (u8 *)gp_stuConfigFile,SPIFLASH_CONFIG_FILE_BASE_ADDR,sizeof(CONFIG_FILE) ) ){  /* clear */	
		return EXE_SUCCEED;
	}else{
		uPromptInformation( (uint8_t *)"WIFI Error" );
		return EXE_FAILED;
	}
}

uint8_t uConfigPrintBarFile( void )
{	
	if( PRINT_BAR_ON==gp_stuConfigFile->uPrintBar ){
		gp_stuConfigFile->uPrintBar = PRINT_BAR_ON;
			
		uPromptParameter( (uint8_t *)"Bar on" );
	}else if( PRINT_BAR_OFF==gp_stuConfigFile->uPrintBar ){
		gp_stuConfigFile->uPrintBar = PRINT_BAR_OFF;	
			
		uPromptParameter( (uint8_t *)"Bar off" );
	}else{
		gp_stuConfigFile->uPrintBar = PRINT_BAR_OFF;
		
		uPromptParameter( (uint8_t *)"Bar off" );
	}
	
	if( EXE_SUCCEED==SPI_Flash_Write_Page( (u8 *)gp_stuConfigFile,SPIFLASH_CONFIG_FILE_BASE_ADDR,sizeof(CONFIG_FILE) ) ){  /* clear */	
		return EXE_SUCCEED;
	}else{
		uPromptParameter( (uint8_t *)"Bar Error" );
		return EXE_FAILED;
	}
}

uint8_t uConfigPrint1BarFile( void )
{	
	if( EN_ON==gp_stuConfigFile->uCutEnCu ){
		gp_stuConfigFile->uCutEnCu = EN_ON;
			
		uPromptParameter( (uint8_t *)"En on" );
	}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
		gp_stuConfigFile->uCutEnCu = CH_ON;	
			
		uPromptParameter( (uint8_t *)"Ch on" );
	}else{
		gp_stuConfigFile->uCutEnCu = CH_ON;
		
		uPromptParameter( (uint8_t *)"Ch on" );
	}
	
	if( EXE_SUCCEED==SPI_Flash_Write_Page( (u8 *)gp_stuConfigFile,SPIFLASH_CONFIG_FILE_BASE_ADDR,sizeof(CONFIG_FILE) ) ){  /* clear */	
		return EXE_SUCCEED;
	}else{
		uPromptParameter( (uint8_t *)"EnCh Error" );
		return EXE_FAILED;
	}
}

uint8_t uConfigMicSwitch( void )
{	
	if( SWITCH_MIC_ON==gp_stuConfigFile->uSwitchOnOff ){
		gp_stuConfigFile->uSwitchOnOff = SWITCH_MIC_ON;
			
		uPromptParameter( (uint8_t *)"Switch on" );
	}else if( SWITCH_MIC_OFF==gp_stuConfigFile->uSwitchOnOff ){
		gp_stuConfigFile->uSwitchOnOff = SWITCH_MIC_OFF;	
			
		uPromptParameter( (uint8_t *)"Switch on" );
	}else{
		gp_stuConfigFile->uSwitchOnOff = SWITCH_MIC_ON;
		
		uPromptParameter( (uint8_t *)"Switch on" );
	}
	
	if( EXE_SUCCEED==SPI_Flash_Write_Page( (u8 *)gp_stuConfigFile,SPIFLASH_CONFIG_FILE_BASE_ADDR,sizeof(CONFIG_FILE) ) ){  /* clear */	
		return EXE_SUCCEED;
	}else{
		uPromptParameter( (uint8_t *)"Switch Error" );
		return EXE_FAILED;
	}
}

uint8_t uOpenCloseLed( void )
{		
	if( FLUORESCENCE_ON==gp_stuConfigFile->uLedOnOff ){	
		uFluorescenceLight( FLUORESCENCE_ON );            /* 开启LED	 */
		
		uPromptParameter( (uint8_t *)"Led Open" );		
	}else if( FLUORESCENCE_OFF==gp_stuConfigFile->uLedOnOff ){		
		uFluorescenceLight( FLUORESCENCE_OFF );           /* 关闭LED	 */
		
		uPromptParameter( (uint8_t *)"Led Close" );					
	}else{
		uFluorescenceLight( FLUORESCENCE_OFF );           /* 关闭LED	 */
		
		uPromptParameter( (uint8_t *)"Led Close" );	
	}
	
	return EXE_SUCCEED;
}

uint8_t uInitSidoRoot( void )
{
	uTjc4832tSetLableValue( TJC_PASSWORD_PAGE,PASSWORD_PAGE_TEST_ID,(uint8_t *)"" );	/* 清空特殊用户密码值 */
	
	return EXE_SUCCEED;
}

uint8_t uWarnCancel( void )
{
//	OS_ERR err = OS_ERR_NONE;
//	
//	OSSemPost( (OS_SEM *)&g_WarnCencle,OS_OPT_POST_NO_SCHED,&err  );   /* 发送取消警告信号量 */
	
	return EXE_SUCCEED;
}

uint8_t uPromptInformation( uint8_t* uArrInfo )
{
	uTjc4832tSetLableValue( TJC_SET_PAGE,INSTRUMENT_DIS_CON_ID,(uint8_t *)uArrInfo );
	
	return EXE_SUCCEED;
}

uint8_t uPromptParameter( uint8_t* uArrInfo )
{
	uTjc4832tSetLableValue( TJC_INSTRUMENT_PAGE,INSTRUMENT_DIS_CON_ID,(uint8_t *)uArrInfo );
	
	return EXE_SUCCEED;
}

//void vInquireScreen( void )
//{
//	OS_ERR err;
//	
//	/* 显示屏握手 */
//	if( PAGE_ONLINE==g_ReadPageIDStatus ){

//	}else{
//		uCtrl3VPower( CTRL_POWER3_OFF );
//		OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);
//		uCtrl3VPower( CTRL_POWER3_ON );
//		OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);
//		//SetPage( MAIN_PAGE );        /*设置为*/
//	}
//}

uint8_t uConfig1Add( void )
{

	
	return 0;
}

uint8_t uConfig1Sub( void )
{

	
	return 0;
}

uint8_t uConfig2Add( void )
{

	return 0;
}

uint8_t uConfig2Sub( void )
{

	return 0;
}

uint8_t uDensityAffirmPage( void )
{	
#if DEBUH_UART1
	//myprintf( "g_RecordReturn2Page: %d %x\r\n",g_RecordReturn2Page ,g_RecordReturn2Page );
#endif
	
	return 0;
}

uint8_t uConfigCalendar( void )
{
	return 0;
}

uint8_t uSetTimeEditInit( void )
{
	uint8_t strff[64] = {0}; 
	
	memset( strff,0,sizeof(strff) );
	sprintf( (char *)strff,"%04d",calendar.w_year );
	uTjc4832tSetNumValue( TJC_SET_TIME_PAGE,TIME_PAGE_1CONTROL_ID,(uint8_t *)strff);	//
	
	memset( strff,0,sizeof(strff) );
	sprintf( (char *)strff,"%02d",calendar.w_month );
	uTjc4832tSetNumValue( TJC_SET_TIME_PAGE,TIME_PAGE_2CONTROL_ID,(uint8_t *)strff );	//
	
	memset( strff,0,sizeof(strff) );
	sprintf( (char *)strff,"%02d",calendar.w_date );
	uTjc4832tSetNumValue( TJC_SET_TIME_PAGE,TIME_PAGE_3CONTROL_ID,(uint8_t *)strff );	//
	
	memset( strff,0,sizeof(strff) );
	sprintf( (char *)strff,"%02d",calendar.hour );
	uTjc4832tSetNumValue( TJC_SET_TIME_PAGE,TIME_PAGE_4CONTROL_ID,(uint8_t *)strff );	//
	
	memset( strff,0,sizeof(strff) );
	sprintf( (char *)strff,"%02d",calendar.min );
	uTjc4832tSetNumValue( TJC_SET_TIME_PAGE,TIME_PAGE_5CONTROL_ID,(uint8_t *)strff );	//
	/* 暂时不显示秒 */
//	sprintf( (char *)strff,"%02d",calendar.sec );
//	uTjc4832tSetNumValue( TJC_SET_TIME_PAGE,TIME_PAGE_6CONTROL_ID,(uint8_t *)strff );	//
	
	return EXE_SUCCEED;
}

uint8_t uSetInputConfigEditInit( CONFIG_FILE* pstuConfig )
{
	uint8_t strff[64] = {0}; 

	memset( strff,0,sizeof(strff) );
	sprintf( (char *)strff,"%03d",pstuConfig->uStartOffset );
	uTjc4832tSetNumValue( TJC_CONFIG_PAGE,CONFIG_PAGE_OFFSET_ID,strff );	  //
																		    
	memset( strff,0,sizeof(strff) );                                        
	sprintf( (char *)strff,"%03d",pstuConfig->uMax5402Gain );               
	uTjc4832tSetNumValue( TJC_CONFIG_PAGE,CONFIG_PAGE_GAIN_ID,strff );	      //
	
	memset( strff,0,sizeof(strff) );
	sprintf( (char *)strff,"%03d",pstuConfig->uBarOffset );
	uTjc4832tSetNumValue( TJC_CONFIG_PAGE,CONFIG_PAGE_BAROFFSET_ID,strff );	  //
	
	memset( strff,0,sizeof(strff) );
	sprintf( (char *)strff,"%d",(int )(pstuConfig->fCoeff*REF_MULTIPLE_RANGE) );
	uTjc4832tSetFloatNumValue( TJC_CONFIG_PAGE,CONFIG_PAGE_COEFF_ID,strff );
	
	memset( strff,0,sizeof(strff) );
	sprintf( (char *)strff,"%03d",gp_stuConfigFile->uLanReferValue );
	uTjc4832tSetNumValue( TJC_CONFIG_PAGE,CONFIG_PAGE_LANBO_ID,strff );
	
	memset( strff,0,sizeof(strff) );
	if( strlen( (const char *)gp_stuConfigFile->uSNStrNum )<sizeof(gp_stuConfigFile->uSNStrNum) ){
		memcpy( (char *)strff,(const char *)gp_stuConfigFile->uSNStrNum,SN_NUM );
		uTjc4832tSetLableValue( TJC_CONFIG_PAGE,CONFIG_PAGE_SN_ID,strff );
	}else{
		uTjc4832tSetLableValue( TJC_CONFIG_PAGE,CONFIG_PAGE_SN_ID,strff );
	}
	
	return EXE_SUCCEED;
}

uint8_t uSetSystemEditInit( CONFIG_FILE* pstuConfig )
{
	uint8_t strff[64] = {0}; 
	
	memset( strff,0,sizeof(strff) );
	sprintf( (char *)strff,"%03d",pstuConfig->uAutoShutDown );
	uTjc4832tSetNumValue( TJC_SYSTEM_PAR_PAGE,CONFIG_PAGE_SHUT_ID,strff );        //
	
	memset( strff,0,sizeof(strff) );
	memcpy( (char *)strff,(const char *)g_uPrintTitles,strlen((const char *)g_uPrintTitles) );
	uTjc4832tSetLableValue( TJC_SYSTEM_PAR_PAGE,CONFIG_PAGE_TITLE_ID,strff );        //
	
	uConfirmPage( TJC_SYSTEM_PAR_PAGE );  
	
	return EXE_SUCCEED;
}

uint8_t uSetPageInit( void )
{
	uDisplayVersion();
	
	return EXE_SUCCEED;
}

uint8_t uDisplayVersion( void )
{	
	uTjc4832tSetLableValue( TJC_SET_SELECT_PAGE,DIS_VER_ID,(uint8_t *)MCU_FIRMWARE_VERSION );    /* 登录页面显示版本号 */
	
	uConfirmPage( TJC_SET_SELECT_PAGE ); 
	
	return EXE_SUCCEED;
}

uint8_t uDisInputUserInfoInit( USER_MORE_INFO* pstuConfig )
{
	uint8_t strff[64] = {0}; 
	
//	uConfirmPage( TJC_MORE_PAGE );         /* */
	uSpecialMoreInformationInit();                                             /* 初始化用户信息 */

	memset( strff,0,sizeof(strff) );
	if( 0xff!=pstuConfig->user_name[0] ){
		memcpy( (char *)strff,pstuConfig->user_name,sizeof(strff) );
	}else{
		sprintf( (char *)strff,"%s","" );
	}
	uTjc4832tSetLableValue( TJC_MORE_PAGE,MORE_PAGE_USER_ID,strff );	//
	
	memset( strff,0,sizeof(strff) );
	if( 0==pstuConfig->user_age ){
		sprintf( (char *)strff,"%s","" );
	}else{
		sprintf( (char *)strff,"%03d",pstuConfig->user_age );
	}
	uTjc4832tSetLableValue( TJC_MORE_PAGE,MORE_PAGE_AGE_ID,strff );	//
	
	uConfirmPage( TJC_MORE_PAGE );         /* */
	
	/* 设置单选框的值 */
	//uTjc4832tSetVariableValue( TJC_MORE_PAGE,MORE_PAGE_SEX_ID,pstuConfig->user_sex );     /* 设置变量值与单选框同步 */
	if( 0x31==pstuConfig->user_sex[0] ){                                                    /* 女性  */
		uTjc4832tClickEvent( MORE_TRADIO_0_BUTTON,TJC_PRESS_DOWN );                         /* 按下 */
		uTjc4832tClickEvent( MORE_TRADIO_0_BUTTON,TJC_PUT_UP );                             /* 弹起 */		
	}else{                                                                                  /* 男性  */
		uTjc4832tClickEvent( MORE_TRADIO_1_BUTTON,TJC_PRESS_DOWN );                         /* 按下 */
		uTjc4832tClickEvent( MORE_TRADIO_1_BUTTON,TJC_PUT_UP );                             /* 弹起 */
	}
	
	return EXE_SUCCEED;
}

uint8_t uClearInputUserInfo( void )
{	
//	uConfirmPage( TJC_MORE_PAGE );         /* */

	uTjc4832tSetLableValue( TJC_MORE_PAGE,MORE_PAGE_USER_ID,(uint8_t *)"" );	//	
	uTjc4832tSetLableValue( TJC_MORE_PAGE,MORE_PAGE_AGE_ID,(uint8_t *)"" );	//
	
	return EXE_SUCCEED;
}

uint8_t uClearInputReference( void )
{	
//	uConfirmPage( TJC_MORE_PAGE );         /* */
		
	uTjc4832tSetLableValue( TJC_REFERENCE_PAGE,REFERENCE_PAGE_00_TXT_ID,(uint8_t *)""  );	//

	uTjc4832tSetFloatNumValue( TJC_REFERENCE_PAGE,REFERENCE_PAGE_00_MIN_ID,(uint8_t *)"" );	//	

	uTjc4832tSetFloatNumValue( TJC_REFERENCE_PAGE,REFERENCE_PAGE_00_MAX_ID,(uint8_t *)""  );	//	

	uTjc4832tSetFloatNumValue( TJC_REFERENCE_PAGE,REFERENCE_PAGE_01_MIN_ID,(uint8_t *)""  );	//	

	uTjc4832tSetFloatNumValue( TJC_REFERENCE_PAGE,REFERENCE_PAGE_01_MAX_ID,(uint8_t *)""  );	//	

	uTjc4832tSetFloatNumValue( TJC_REFERENCE_PAGE,REFERENCE_PAGE_02_MIN_ID,(uint8_t *)""  );	//	

	uTjc4832tSetFloatNumValue( TJC_REFERENCE_PAGE,REFERENCE_PAGE_02_MAX_ID,(uint8_t *)""  );	//
	
	return EXE_SUCCEED;
}

uint8_t uClearInputSystem( void )
{	
//	uConfirmPage( TJC_MORE_PAGE );         /* */

	uTjc4832tSetNumValue( TJC_SYSTEM_PAR_PAGE,CONFIG_PAGE_SHUT_ID,(uint8_t *)"" );        //
	
	uTjc4832tSetLableValue( TJC_SYSTEM_PAR_PAGE,CONFIG_PAGE_TITLE_ID,(uint8_t *)"" );        //
	
	return EXE_SUCCEED;
}

uint8_t uClearInputTimeValue( void )
{	
//	uConfirmPage( TJC_MORE_PAGE );         /* */

	uTjc4832tSetNumValue( TJC_SET_TIME_PAGE,TIME_PAGE_1CONTROL_ID,(uint8_t *)"");	//
	
	uTjc4832tSetNumValue( TJC_SET_TIME_PAGE,TIME_PAGE_2CONTROL_ID,(uint8_t *)"" );	//
	
	uTjc4832tSetNumValue( TJC_SET_TIME_PAGE,TIME_PAGE_3CONTROL_ID,(uint8_t *)"" );	//
	
	uTjc4832tSetNumValue( TJC_SET_TIME_PAGE,TIME_PAGE_4CONTROL_ID,(uint8_t *)"" );	//
	
	uTjc4832tSetNumValue( TJC_SET_TIME_PAGE,TIME_PAGE_5CONTROL_ID,(uint8_t *)"" );	//
	
	return EXE_SUCCEED;
}

uint8_t uClearInputServer( void )
{	
//	uConfirmPage( TJC_MORE_PAGE );         /* */

	uTjc4832tSetLableValue( TJC_SERVER_CONF_PAGE,SERVER_PAGE_IP_ID,(uint8_t *)"" );	//	
	
	uTjc4832tSetLableValue( TJC_SERVER_CONF_PAGE,SERVER_PAGE_PORT_ID,(uint8_t *)"" );	//
	
	return EXE_SUCCEED;
}

/* 显示参考页面数据 刷新参考页面 */
uint8_t uDisInputReferenceInit( USER_REFERRENCE* pstuConfig,uint8_t uRefNumber )
{
	uint8_t strff[64] = {0}; 
	
	if( 0xff!=pstuConfig->ureference_name[0] ){
		
		uTjc4832tSetLableValue( TJC_REFERENCE_PAGE,REFERENCE_PAGE_00_TXT_ID,pstuConfig->ureference_name );	//

		memset( strff,0,sizeof(strff) );
		sprintf( (char *)strff,"%d",(int )(pstuConfig->fuser_00_limits_min*REF_MULTIPLE_RANGE) );
		uTjc4832tSetFloatNumValue( TJC_REFERENCE_PAGE,REFERENCE_PAGE_00_MIN_ID,strff );	//
		
		memset( strff,0,sizeof(strff) );
		sprintf( (char *)strff,"%d",(int )(pstuConfig->fuser_00_limits_max*REF_MULTIPLE_RANGE) );
		uTjc4832tSetFloatNumValue( TJC_REFERENCE_PAGE,REFERENCE_PAGE_00_MAX_ID,strff );	//
		
		memset( strff,0,sizeof(strff) );
		sprintf( (char *)strff,"%d",(int )(pstuConfig->fuser_01_limits_min*REF_MULTIPLE_RANGE) );
		uTjc4832tSetFloatNumValue( TJC_REFERENCE_PAGE,REFERENCE_PAGE_01_MIN_ID,strff );	//
		
		memset( strff,0,sizeof(strff) );
		sprintf( (char *)strff,"%d",(int )(pstuConfig->fuser_01_limits_max*REF_MULTIPLE_RANGE) );
		uTjc4832tSetFloatNumValue( TJC_REFERENCE_PAGE,REFERENCE_PAGE_01_MAX_ID,strff );	//
		
		memset( strff,0,sizeof(strff) );
		sprintf( (char *)strff,"%d",(int )(pstuConfig->fuser_02_limits_min*REF_MULTIPLE_RANGE) );
		uTjc4832tSetFloatNumValue( TJC_REFERENCE_PAGE,REFERENCE_PAGE_02_MIN_ID,strff );	//
		
		memset( strff,0,sizeof(strff) );
		sprintf( (char *)strff,"%d",(int )(pstuConfig->fuser_02_limits_max*REF_MULTIPLE_RANGE) );
		uTjc4832tSetFloatNumValue( TJC_REFERENCE_PAGE,REFERENCE_PAGE_02_MAX_ID,strff );	//
		
		uConfirmPage( TJC_REFERENCE_PAGE );
		
		memset( strff,0,sizeof(strff) );
		sprintf( (char *)strff,"%d",uRefNumber );
		uTjc4832tSetLableValue( TJC_REFERENCE_PAGE,REFERENCE_PAGE_00_TXT_NUM_ID,strff );	//
	}
	
	return 0;
}

uint8_t uDisInstrumentInit( void )
{
	uint8_t strff[64] = {0}; 
	
	uConfirmPage( TJC_SET_PAGE );
	
	memset( strff,0,sizeof(strff) );
	sprintf( (char *)strff,"%d",(int )gp_stuConfigFile->uBuzzerOnOff );
	uTjc4832tSetSwitchValue( TJC_SET_PAGE,INSTR_BT0_ID,strff );
	
	memset( strff,0,sizeof(strff) );
	sprintf( (char *)strff,"%d",(int )gp_stuConfigFile->uPrintfOnOff );
	uTjc4832tSetSwitchValue( TJC_SET_PAGE,INSTR_BT2_ID,strff );
	
	memset( strff,0,sizeof(strff) );
	sprintf( (char *)strff,"%d",(int )gp_stuConfigFile->uScanBar );
	uTjc4832tSetSwitchValue( TJC_SET_PAGE,INSTR_BT5_ID,strff );
	
	memset( strff,0,sizeof(strff) );
	sprintf( (char *)strff,"%d",(int )gp_stuConfigFile->uWifiOnOff );
	uTjc4832tSetSwitchValue( TJC_SET_PAGE,INSTR_BT6_ID,strff );
	
	return EXE_SUCCEED;
}

uint8_t uDisParameterInit( void )
{
	uint8_t strff[64] = {0}; 
	
	uConfirmPage( TJC_INSTRUMENT_PAGE );
	
	memset( strff,0,sizeof(strff) );
	sprintf( (char *)strff,"%d",(int )gp_stuConfigFile->uLedOnOff );
	uTjc4832tSetSwitchValue( TJC_INSTRUMENT_PAGE,INSTR_BT1_ID,strff );
	
	memset( strff,0,sizeof(strff) );
	sprintf( (char *)strff,"%d",(int )gp_stuConfigFile->uPrintBar );
	uTjc4832tSetSwitchValue( TJC_INSTRUMENT_PAGE,INSTR_BT3_ID,strff );
	
	memset( strff,0,sizeof(strff) );
	sprintf( (char *)strff,"%d",(int )gp_stuConfigFile->uPrintAD );
	uTjc4832tSetSwitchValue( TJC_INSTRUMENT_PAGE,INSTR_BT4_ID,strff );
	
	memset( strff,0,sizeof(strff) );
	sprintf( (char *)strff,"%d",(int )gp_stuConfigFile->uCutEnCu );
	uTjc4832tSetSwitchValue( TJC_INSTRUMENT_PAGE,INSTR_BT7_ID,strff );
	
	memset( strff,0,sizeof(strff) );
	sprintf( (char *)strff,"%d",(int )gp_stuConfigFile->uSwitchOnOff );
	uTjc4832tSetSwitchValue( TJC_INSTRUMENT_PAGE,INSTR_BT0_ID,strff );
	
	return EXE_SUCCEED;
}

uint8_t uSpecialMoreInformationInit( void )
{
	SPI_Flash_Read( (uint8_t *)&g_stuUserMoreInfo,SPIFLASH_USER_MORE_ADDR,sizeof(USER_MORE_INFO) );
	if( (0xff==g_stuUserMoreInfo.user_name[0])||(0xff==g_stuUserMoreInfo.user_sex[0])||(0xff==g_stuUserMoreInfo.user_age) ){     /* 如何判断 */
		/* 默认为空  */
		memcpy( (char *)g_stuUserMoreInfo.user_name,"",sizeof(g_stuUserMoreInfo.user_name) );  /*Allen*/
		memcpy( (char *)g_stuUserMoreInfo.user_sex,"",sizeof(g_stuUserMoreInfo.user_sex) );    /*Man*/
		g_stuUserMoreInfo.user_age = 0;
	}
		
	return EXE_SUCCEED;
}

uint8_t uSetRerferenceInit( void )
{	
	OS_ERR err;
	uint8_t i = 0;
	USER_REFERRENCE stuTempRerf[9] = { {"CRP",0,10,0,1,0,0},
									   {"SAA",0,10,0,0,0,0},
									   {"PCT",0,0.5,0,0,0,0},
									   {"IL-6",0,7,0,0,0,0},
									   {"cTnI",0,0.3,0,0.04,0,0},
									   {"NT-proBNP",0,300,0,0,0,0},
									   {"D-Dimer",0,0.5,0,0,0,0},
									   {"心肌三项",0,58,0,5,0,0.3},
									   {"SARS-Cov-2 IgG/M",0,0,0,0,0,0}};
	
	for( i=0;i<9;i++ ){
		memcpy( &g_stuUserReference,&stuTempRerf[i],sizeof(USER_REFERRENCE));
		uSetMassRerference( &g_stuUserReference,&g_projectSerial );                            /* 设置全部参考值 */
		OSTimeDlyHMSM(0, 0, 0, 20,OS_OPT_TIME_HMSM_STRICT,&err);	                            /* 延时10ms   */
	}
										  								  
//	for( i=0;i<9;i++ ){
//		memcpy( &g_stuUserReference,&stuTempRerf[i],sizeof(USER_REFERRENCE));
//		uSetMassRerference( &g_stuUserReference,&g_projectSerial );                            /* 设置全部参考值 */
//	}
	
#if DEBUH_UART1	
	#if PRIVATE_UART1	
//	SPI_Flash_Read( (uint8_t *)&g_stuUserReference,SPIFLASH_USER_REFER_ADDR,sizeof(USER_REFERRENCE) );
//	if( (0xff==(*(uint8_t *)(&g_stuUserReference.fuser_00_limits_min)))||(0xff==(*(uint8_t *)(&g_stuUserReference.fuser_00_limits_max))) ){     /* 如何判断 */
//		g_stuUserReference.fuser_00_limits_min = 0;
//		g_stuUserReference.fuser_00_limits_max = 0;	
//	}
//	if( (0xff==(*(uint8_t *)(&g_stuUserReference.fuser_01_limits_min)))||(0xff==(*(uint8_t *)(&g_stuUserReference.fuser_01_limits_max))) ){     /* 如何判断 */
//		g_stuUserReference.fuser_01_limits_min = 0;
//		g_stuUserReference.fuser_01_limits_max = 0;	
//	}
//	if( (0xff==(*(uint8_t *)(&g_stuUserReference.fuser_02_limits_min)))||(0xff==(*(uint8_t *)(&g_stuUserReference.fuser_02_limits_max))) ){     /* 如何判断 */
//		g_stuUserReference.fuser_02_limits_min = 0;
//		g_stuUserReference.fuser_02_limits_max = 0;	
//	}
	
//		myprintf( "UserReference0 :%.2f %.2f\r\n",g_stuUserReference.fuser_00_limits_min,g_stuUserReference.fuser_00_limits_max );
//		myprintf( "UserReference1 :%.2f %.2f\r\n",g_stuUserReference.fuser_01_limits_min,g_stuUserReference.fuser_01_limits_max );
//		myprintf( "UserReference2 :%.2f %.2f\r\n",g_stuUserReference.fuser_02_limits_min,g_stuUserReference.fuser_02_limits_max );
	#endif
#endif
	
	return EXE_SUCCEED;
}

uint8_t uSetPrintTitlesInit( void )
{	
#if TITLES_PRINT_NULL
	char cTempTitle[] = " ";	
#else
//	char cTempTitle[] = "Sichuan Xincheng Biological Co., LTD ";
	char cTempTitle[48] = {0};//"Fluorescent Immunoanalyzer ";
#endif
	
	if( EN_ON==gp_stuConfigFile->uCutEnCu ){
		sprintf( cTempTitle,"%s","Fluorescent Immunoanalyzer " );
	}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
		sprintf( cTempTitle,"%s","干式荧光免疫分析仪 " );
	}
	
	SPI_Flash_Read( (uint8_t *)&g_uPrintTitles,SPIFLASH_P_TITLES_BASE_ADDR,sizeof(g_uPrintTitles) );
	if( (0xff==(g_uPrintTitles[0])) ){     /* 如何判断 */	
		memset( g_uPrintTitles,0,sizeof(cTempTitle) );
		memcpy( g_uPrintTitles,(const char *)cTempTitle,strlen(cTempTitle) );		
	}
	
	if( strlen((const char *)g_uPrintTitles)>=sizeof(g_uPrintTitles) ){
		memset( g_uPrintTitles,0,sizeof(cTempTitle) );
		memcpy( g_uPrintTitles,(const char *)cTempTitle,strlen(cTempTitle) );	
	}
	
#if DEBUH_UART1	
	#if PRIVATE_UART1			
//		myprintf( "cTempTitle :%s \r\n",g_uPrintTitles,g_uPrintTitles );
	#endif
#endif
	
	return EXE_SUCCEED;
}

uint8_t uSpecialMoreInformation( void )
{
	/* 姓名为空 */
	if( (strlen((const char *)g_stuUserMoreInfo.user_name)>0)&&(strlen((const char *)g_stuUserMoreInfo.user_name)<sizeof(g_stuUserMoreInfo.user_name))&&
		(0x30!=g_stuUserMoreInfo.user_name[0])&&(0x31!=g_stuUserMoreInfo.user_name[0]) ){
	
	}else{
		uTjc4832tSetPage( TJC_WARN_PAGE );        /*设置为*/			
		if( EN_ON==gp_stuConfigFile->uCutEnCu ){
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Name Null " );
		}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"无姓名" );	             //ID数据错误
		}else{
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Name Null " );
		}
		uBuzzerTimes( BUZZER_ONE_TIME );
		return EXE_FAILED;
	}
	
	if( (1<=g_stuUserMoreInfo.user_age)&&(g_stuUserMoreInfo.user_age<=200) ){
	
	}else{
		uTjc4832tSetPage( TJC_WARN_PAGE );        /*设置为*/				
		if( EN_ON==gp_stuConfigFile->uCutEnCu ){
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"The Range Of 1-200 " );
		}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"范围是 1-200 " );
		}else{
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"The Range Of 1-200 " );
		}
		uBuzzerTimes( BUZZER_ONE_TIME );
		return EXE_FAILED;
	}
	
	if( EXE_SUCCEED==SPI_Flash_Write_Page( (uint8_t *)&g_stuUserMoreInfo,SPIFLASH_USER_MORE_ADDR,sizeof(USER_MORE_INFO) ) ){
		uTjc4832tSetPage( TJC_TEST_PAGE ); 
	}else{
		uTjc4832tSetPage( TJC_WARN_PAGE );         /*  */
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"information error" ); 
	}
	
	return EXE_SUCCEED;
}

uint8_t uSetCoeffValue( float fTempCoeff,uint8_t uPrompter )
{
	if( UI_Y_PROMPT==uPrompter ){
		uTjc4832tSetPage( TJC_WARN_PAGE );        /*设置为*/
	}
	
	if( (0<=fTempCoeff)&&(fTempCoeff<=LINEAR_RANGE_MAX) ){
		gp_stuConfigFile->fCoeff = fTempCoeff;//gp_stuEditInputConfig->fstuCoeff;
		
		if( EXE_SUCCEED==SPI_Flash_Write_Page( (u8 *)gp_stuConfigFile,SPIFLASH_CONFIG_FILE_BASE_ADDR,sizeof(CONFIG_FILE) ) ){  /* clear */	
			if( UI_Y_PROMPT==uPrompter ){
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Coeff Ok" );		
			}	
#if DEBUH_UART1		
			myprintf( "fTempCoeff:%f fCoeff:%f \r\n",fTempCoeff,gp_stuConfigFile->fCoeff );                                          /*  */
#endif	
			return EXE_SUCCEED;			
		}else{
			if( UI_Y_PROMPT==uPrompter ){
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Coeff Error" );	
			}	
			return EXE_FAILED;
		}
	}else{
		if( UI_Y_PROMPT==uPrompter ){
			uLinearRangeWarn( 0 );           /* 警告 提示范围 */
		}		
		return EXE_FAILED;
	}
}

/*  */
uint8_t uSetLanboRefValue( uint16_t uTempLanboRef,uint8_t uPrompter )
{	
	if( UI_Y_PROMPT==uPrompter ){
		uTjc4832tSetPage( TJC_WARN_PAGE );        /*设置为*/
	}
	
	if( (0<uTempLanboRef)&&(uTempLanboRef<SCAN_LENGTH) ){
		gp_stuConfigFile->uLanReferValue = uTempLanboRef;//gp_stuEditInputConfig->fstuCoeff;
		
		if( EXE_SUCCEED==SPI_Flash_Write_Page( (u8 *)gp_stuConfigFile,SPIFLASH_CONFIG_FILE_BASE_ADDR,sizeof(CONFIG_FILE) ) ){  /* clear */	
			if( UI_Y_PROMPT==uPrompter ){
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"LanRef Ok" );		
			}	
#if DEBUH_UART1		
			myprintf( "LanRef:%d uLanReferValue:%d \r\n",uTempLanboRef,gp_stuConfigFile->uLanReferValue );                                          /*  */
#endif	
			return EXE_SUCCEED;			
		}else{
			if( UI_Y_PROMPT==uPrompter ){
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"LanRef Error" );	
			}	
			return EXE_FAILED;
		}
	}else{
		if( UI_Y_PROMPT==uPrompter ){
			uTjc4832tSetPage( TJC_WARN_PAGE );        /*设置为*/		
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"The Range Of 1-311 " );
			uBuzzerTimes( BUZZER_ONE_TIME );
		}
		return EXE_FAILED;
	}
}

/*  */
uint8_t uSetSNStr( uint8_t* puSnStr,uint8_t uStrNum,uint8_t uPrompter )
{	
	if( UI_Y_PROMPT==uPrompter ){
		uTjc4832tSetPage( TJC_WARN_PAGE );        /*设置为*/
	}
	
	if( (0<uStrNum) ){
		memset( gp_stuConfigFile->uSNStrNum,0,sizeof( gp_stuConfigFile->uSNStrNum ) );
		memcpy( gp_stuConfigFile->uSNStrNum,puSnStr,uStrNum );		
		
		if( EXE_SUCCEED==SPI_Flash_Write_Page( (u8 *)gp_stuConfigFile,SPIFLASH_CONFIG_FILE_BASE_ADDR,sizeof(CONFIG_FILE) ) ){  /* clear */	
			if( UI_Y_PROMPT==uPrompter ){
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"SN Ok" );		
			}	
#if DEBUH_UART1		
			myprintf( "SN:%s uSNstr:%s \r\n",puSnStr,gp_stuConfigFile->uSNStrNum );                                          /*  */
#endif	
			return EXE_SUCCEED;			
		}else{
			if( UI_Y_PROMPT==uPrompter ){
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"SN Error" );	
			}	
			return EXE_FAILED;
		}
	}else{
		if( UI_Y_PROMPT==uPrompter ){
			uTjc4832tSetPage( TJC_WARN_PAGE );        /*设置为*/		
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"SN NULL" );
			uBuzzerTimes( BUZZER_ONE_TIME );
		}
		return EXE_FAILED;
	}
}

/* 后台设置参考范围 */
uint8_t uSetMassRerference( USER_REFERRENCE* pstuUserRerf,PRO_SERIAL* pstuRecRerf  )
{
	int8_t iTempCoverPage = 0;
	
	if( 0==strlen((const char *)pstuUserRerf->ureference_name) ){
		uLinearRangeWarn( 2 );            /* 警告  */
		return EXE_FAILED;
	}else{
		iTempCoverPage = uFindReferenceName( (uint8_t *)pstuUserRerf->ureference_name );   /* 没有找到返回0 */
		if( REF_SEEK_FAILE!=iTempCoverPage ){                                              /* 找到了相同项目直接返回 */                                             
//				uLinearRangeWarn( 3 );            /* 警告  */
			return EXE_FAILED;
		}
	}
	
	if( (0<=pstuUserRerf->fuser_00_limits_min)&&(pstuUserRerf->fuser_00_limits_min<=LINEAR_RANGE_MAX)&&     \
		(pstuUserRerf->fuser_00_limits_max<=LINEAR_RANGE_MAX)	){
		if( !(pstuUserRerf->fuser_00_limits_min<=pstuUserRerf->fuser_00_limits_max) ){
			uLinearRangeWarn( 1 );       /* 警告 提示Min<Max */
			return EXE_FAILED;
		}		
	}else{
		uLinearRangeWarn( 0 );           /* 警告 提示范围 */
		return EXE_FAILED;
	}
	
	if( (0<=pstuUserRerf->fuser_01_limits_min)&&(pstuUserRerf->fuser_01_limits_min<=LINEAR_RANGE_MAX)&&     \
		(pstuUserRerf->fuser_01_limits_max<=LINEAR_RANGE_MAX) ){
		if( !(pstuUserRerf->fuser_01_limits_min<=pstuUserRerf->fuser_01_limits_max) ){
			uLinearRangeWarn( 1 );       /* 警告 提示Min<Max */
			return EXE_FAILED;
		}		
	}else{
		uLinearRangeWarn( 0 );       /* 警告 提示范围 */
		return EXE_FAILED;
	}
	
	if( (0<=pstuUserRerf->fuser_02_limits_min)&&(pstuUserRerf->fuser_02_limits_min<=LINEAR_RANGE_MAX)&&     \
		(pstuUserRerf->fuser_02_limits_max<=LINEAR_RANGE_MAX) ){
		if( !(pstuUserRerf->fuser_02_limits_min<=pstuUserRerf->fuser_02_limits_max) ){
			uLinearRangeWarn( 1 );       /* 警告 提示Min<Max */
			return EXE_FAILED;
		}		
	}else{
		uLinearRangeWarn( 0 );       /* 警告 提示范围 */
		return EXE_FAILED;
	}
		       
	return uStoreMassReferencedata( pstuUserRerf,pstuRecRerf );
}

/* 需要考虑出现连续错误的时候 不需要频繁切换页面 */
uint8_t uSetRerference( uint8_t uDisInfo )
{
	uint8_t uRecVerify = 0;
	
	if( BUTTON_VALUE_REFERENCE==uDisInfo ){
		if( 0==strlen((const char *)g_stuUserReference.ureference_name) ){
			uLinearRangeWarn( 2 );            /* 警告  */
			return EXE_FAILED;
		}else{
			g_uRecordCoverPage = uFindReferenceName( (uint8_t *)g_stuUserReference.ureference_name );    /* 没有找到返回0 */
			if( REF_SEEK_FAILE!=g_uRecordCoverPage ){                                                    /* 找到了相同的项目询问是否需要覆盖 */
				g_uRecordCoverPage = g_uRecordCoverPage-1;
				if( EN_ON==gp_stuConfigFile->uCutEnCu ){
					uPrompterWarn( (uint8_t *)"Overwrite?" );
				}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
					uPrompterWarn( (uint8_t *)"重写?" );                                           
				}else{
					uPrompterWarn( (uint8_t *)"Invalid" ); 
				}	
				
//				uLinearRangeWarn( 3 );            /* 警告  */
				return EXE_FAILED;
			}
		}	
	
		uRecVerify = uReferenceVerify( &g_stuUserReference );
		if( uRecVerify!=EXE_SUCCEED ){
			return uRecVerify;
		}
	}else if( (BUTTON_VALUE_B1REFERENCE==uDisInfo)||(BUTTON_VALUE_B2REFERENCE==uDisInfo) ){
		if( (0<=g_stuUserReference.fuser_00_limits_min)&&(g_stuUserReference.fuser_00_limits_min<=LINEAR_RANGE_MAX)&&     \
			(g_stuUserReference.fuser_00_limits_max<=LINEAR_RANGE_MAX)	){
			if( (BUTTON_VALUE_B1REFERENCE!=uDisInfo) ){
				if( !(g_stuUserReference.fuser_00_limits_min<g_stuUserReference.fuser_00_limits_max) ){
					uLinearRangeWarn( 1 );       /* 警告 提示Min<Max */
					return EXE_FAILED;
				}	
			}			
		}else{
			uLinearRangeWarn( 0 );               /* 警告 提示范围 */
			return EXE_FAILED;
		}
	}else if( (BUTTON_VALUE_B3REFERENCE==uDisInfo)||(BUTTON_VALUE_B4REFERENCE==uDisInfo) ){
		if( (0<=g_stuUserReference.fuser_01_limits_min)&&(g_stuUserReference.fuser_01_limits_min<=LINEAR_RANGE_MAX)&&     \
			(g_stuUserReference.fuser_01_limits_max<=LINEAR_RANGE_MAX) ){
			if( (BUTTON_VALUE_B3REFERENCE!=uDisInfo) ){
				if( !(g_stuUserReference.fuser_01_limits_min<g_stuUserReference.fuser_01_limits_max) ){
					uLinearRangeWarn( 1 );       /* 警告 提示Min<Max */
					return EXE_FAILED;
				}	
			}			
		}else{
			uLinearRangeWarn( 0 );       /* 警告 提示范围 */
			return EXE_FAILED;
		}
	}else if( (BUTTON_VALUE_B5REFERENCE==uDisInfo)||(BUTTON_VALUE_B6REFERENCE==uDisInfo) ){
		if( (0<=g_stuUserReference.fuser_02_limits_min)&&(g_stuUserReference.fuser_02_limits_min<=LINEAR_RANGE_MAX)&&     \
			(g_stuUserReference.fuser_02_limits_max<=LINEAR_RANGE_MAX) ){
			if( (BUTTON_VALUE_B5REFERENCE!=uDisInfo) ){
				if( !(g_stuUserReference.fuser_02_limits_min<g_stuUserReference.fuser_02_limits_max) ){
					uLinearRangeWarn( 1 );       /* 警告 提示Min<Max */
					return EXE_FAILED;
				}	
			}			
		}else{
			uLinearRangeWarn( 0 );       /* 警告 提示范围 */
			return EXE_FAILED;
		}
	}else{
		uTjc4832tSetPage( TJC_SET_PAGE );
		return EXE_FAILED;
	}
	       
	return uStoreReferencedata( DEF_COVER_OFF,uDisInfo );
}

uint8_t uReferenceVerify( USER_REFERRENCE *pTempReference )
{
	if( (0<=pTempReference->fuser_00_limits_min)&&(pTempReference->fuser_00_limits_min<=LINEAR_RANGE_MAX)&&     \
		(pTempReference->fuser_00_limits_max<=LINEAR_RANGE_MAX)	){
		if( 0!=pTempReference->fuser_00_limits_max ){
			if( !(pTempReference->fuser_00_limits_min<=pTempReference->fuser_00_limits_max) ){
				uLinearRangeWarn( 1 );       /* 警告 提示Min<Max */
				return EXE_FAILED;
			}	
		}		
	}else{
		uLinearRangeWarn( 0 );           /* 警告 提示范围 */
		return EXE_FAILED;
	}
	
	if( (0<=pTempReference->fuser_01_limits_min)&&(pTempReference->fuser_01_limits_min<=LINEAR_RANGE_MAX)&&     \
		(pTempReference->fuser_01_limits_max<=LINEAR_RANGE_MAX) ){
		if( 0!=pTempReference->fuser_01_limits_max ){
			if( !(pTempReference->fuser_01_limits_min<=pTempReference->fuser_01_limits_max) ){
				uLinearRangeWarn( 1 );       /* 警告 提示Min<Max */
				return EXE_FAILED;
			}	
		}	
	}else{
		uLinearRangeWarn( 0 );       /* 警告 提示范围 */
		return EXE_FAILED;
	}
	
	if( (0<=pTempReference->fuser_02_limits_min)&&(pTempReference->fuser_02_limits_min<=LINEAR_RANGE_MAX)&&     \
		(pTempReference->fuser_02_limits_max<=LINEAR_RANGE_MAX) ){
		if( 0!=pTempReference->fuser_02_limits_max ){
			if( !(pTempReference->fuser_02_limits_min<=pTempReference->fuser_02_limits_max) ){
				uLinearRangeWarn( 1 );       /* 警告 提示Min<Max */
				return EXE_FAILED;
			}	
		}		
	}else{
		uLinearRangeWarn( 0 );       /* 警告 提示范围 */
		return EXE_FAILED;
	}
	
	return EXE_SUCCEED;
}

//uint8_t uReferenceVerify( USER_REFERRENCE *pTempReference )
//{
//	if( (0<=pTempReference->fuser_00_limits_min)&&(pTempReference->fuser_00_limits_min<=LINEAR_RANGE_MAX)&&     \
//		(pTempReference->fuser_00_limits_max<=LINEAR_RANGE_MAX)	){
//		if( !(pTempReference->fuser_00_limits_min<=pTempReference->fuser_00_limits_max) ){
//			uLinearRangeWarn( 1 );       /* 警告 提示Min<Max */
//			return EXE_FAILED;
//		}		
//	}else{
//		uLinearRangeWarn( 0 );           /* 警告 提示范围 */
//		return EXE_FAILED;
//	}
//	
//	if( (0<=pTempReference->fuser_01_limits_min)&&(pTempReference->fuser_01_limits_min<=LINEAR_RANGE_MAX)&&     \
//		(pTempReference->fuser_01_limits_max<=LINEAR_RANGE_MAX) ){
//		if( !(pTempReference->fuser_01_limits_min<=pTempReference->fuser_01_limits_max) ){
//			uLinearRangeWarn( 1 );       /* 警告 提示Min<Max */
//			return EXE_FAILED;
//		}		
//	}else{
//		uLinearRangeWarn( 0 );       /* 警告 提示范围 */
//		return EXE_FAILED;
//	}
//	
//	if( (0<=pTempReference->fuser_02_limits_min)&&(pTempReference->fuser_02_limits_min<=LINEAR_RANGE_MAX)&&     \
//		(pTempReference->fuser_02_limits_max<=LINEAR_RANGE_MAX) ){
//		if( !(pTempReference->fuser_02_limits_min<=pTempReference->fuser_02_limits_max) ){
//			uLinearRangeWarn( 1 );       /* 警告 提示Min<Max */
//			return EXE_FAILED;
//		}		
//	}else{
//		uLinearRangeWarn( 0 );       /* 警告 提示范围 */
//		return EXE_FAILED;
//	}
//	
//	return EXE_SUCCEED;
//}

uint8_t uStoreReferenceCover( void )
{
	uint8_t uRecVerify = 0;
	
	uRecVerify = uReferenceVerify( &g_stuUserReference );
	if( uRecVerify!=EXE_SUCCEED ){
		return uRecVerify;
	}		
	
	uStoreReferencedata( DEF_COVER_ON,BUTTON_VALUE_REFERENCE );     /* 全部参考值覆盖存储 */
	
	return EXE_SUCCEED;
}

uint8_t uStoreIDCardCover( void )
{	
//	uint8_t i = 0;
//	OS_ERR err;	
//	uint8_t uRecError = 0;
//	UINTE_DATA_TYPE* pTempUinteData = NULL;
//	
//	pTempUinteData = (UINTE_DATA_TYPE *)calloc( 1,sizeof(UINTE_DATA_TYPE) );
//	if( NULL==pTempUinteData ){
//		return EXE_FAILED;
//	}
//	
//	if( EXE_SUCCEED==SPI_Flash_Write_Page( (uint8_t *)&g_IdMemory,SPIFLASH_IDA_BASE_ADDR+(g_uRecordIdCardCover*SPIFLASH_ID_NUM_BASE),sizeof(ID_Info) ) ){	
//	}else{
//#if DEBUH_UART1		
//		myprintf( "FlashWriteError \r\n" );
//#endif
//	}
//	
//	if( g_IdMemory.children_num<=MAX_CHILDER ){                                            /* 子项最多3个 */
//		for( i=0;i<g_IdMemory.children_num;i++ ){									
//			uRecError = uInitIdChildren( pTempUinteData,i,COVER_ID_CHI_ON );		       /* 覆盖存储 */
//			if( EXE_FAILED==uRecError ){
//				if( NULL!=pTempUinteData ){
//					free( pTempUinteData );
//				}
//				return uRecError;
//			}				
//			memset( (uint8_t *)pTempUinteData,0,sizeof(UINTE_DATA_TYPE) );				
//			OSTimeDlyHMSM(0, 0, 0, 20,OS_OPT_TIME_HMSM_STRICT,&err);  /* 延时100ms */
//		}
//	}		
//	if( NULL!=pTempUinteData ){
//		free( pTempUinteData );
//	}

//	uTestInformation();                                                       /* 显示测试信息 */
	
	return EXE_SUCCEED;
}

/* 
uCover   :覆盖写入
uDisInfo :写入单独值选项
*/
uint8_t uStoreReferencedata( uint8_t uCover,uint8_t uDisInfo )
{	
	if( DEF_COVER_OFF==uCover ){		
		if( (0<(g_projectSerial.ureference_count))&&((g_projectSerial.ureference_count)<STORAGE_REFERENCE_MAX) ){	
			if( EXE_SUCCEED==SPI_Flash_Write_Page( (uint8_t *)&g_stuUserReference,(SPIFLASH_USER_REFER_ADDR+((g_projectSerial.ureference_count)*SPIFLASH_PAGE_BASE_ADDR)),sizeof(USER_REFERRENCE) ) ){
				g_projectSerial.ureference_count++;	
				if( STORAGE_REFERENCE_MAX!=g_projectSerial.ureference_max ){
					g_projectSerial.ureference_max = g_projectSerial.ureference_count;
				}		
			}else{
				uTjc4832tSetPage( TJC_WARN_PAGE );         /*  */
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Rerference error" ); 
				return EXE_FAILED;
			}		
		}else{			
			if( EXE_SUCCEED==SPI_Flash_Write_Page( (uint8_t *)&g_stuUserReference,(SPIFLASH_USER_REFER_ADDR),sizeof(USER_REFERRENCE) ) ){		
				g_projectSerial.ureference_count = 1;		
			}else{
				uTjc4832tSetPage( TJC_WARN_PAGE );         /*  */
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Rerference error" ); 
				return EXE_FAILED;
			}		
		}
		/* 记录参考数据有多少种 */
		if( EXE_SUCCEED==SPI_Flash_Write_Page( (uint8_t *)&g_projectSerial,SPIFLASH_SERIAL_BASE_ADDR,sizeof(g_projectSerial) ) ){ /* clear */
			return uStoreReferenceResult( uDisInfo );
		}else{
			uTjc4832tSetPage( TJC_WARN_PAGE );         /*  */
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Rerference error" ); 
#if DEBUH_UART1		
			myprintf( "FlashWriteError \r\n" );
#endif
			return EXE_FAILED;
		}
	}else{
		if( EXE_SUCCEED==SPI_Flash_Write_Page( (uint8_t *)&g_stuUserReference,(SPIFLASH_USER_REFER_ADDR+((g_uRecordCoverPage)*SPIFLASH_PAGE_BASE_ADDR)),sizeof(USER_REFERRENCE) ) ){
			return uStoreReferenceResult( uDisInfo );
		}else{
			uTjc4832tSetPage( TJC_WARN_PAGE );         /*  */
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Rerference error" ); 
			return EXE_FAILED;
		}
	}
}

/* 参考范围存储成功不做任何处理 */
uint8_t uStoreMassReferencedata( USER_REFERRENCE* pstuUserRerfence,PRO_SERIAL* pstuRecRerference )
{			
	if( (0<(pstuRecRerference->ureference_count))&&((pstuRecRerference->ureference_count)<STORAGE_REFERENCE_MAX) ){	
		if( EXE_SUCCEED==SPI_Flash_Write_Page( (uint8_t *)pstuUserRerfence,(SPIFLASH_USER_REFER_ADDR+((pstuRecRerference->ureference_count)*SPIFLASH_PAGE_BASE_ADDR)),sizeof(USER_REFERRENCE) ) ){
			pstuRecRerference->ureference_count++;	
			if( STORAGE_REFERENCE_MAX!=pstuRecRerference->ureference_max ){
				pstuRecRerference->ureference_max = pstuRecRerference->ureference_count;
			}		
		}else{
			uTjc4832tSetPage( TJC_WARN_PAGE );         /*  */
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Rerference error" ); 
			return EXE_FAILED;
		}		
	}else{			
		if( EXE_SUCCEED==SPI_Flash_Write_Page( (uint8_t *)pstuUserRerfence,(SPIFLASH_USER_REFER_ADDR),sizeof(USER_REFERRENCE) ) ){		
			pstuRecRerference->ureference_count = 1;		
		}else{
			uTjc4832tSetPage( TJC_WARN_PAGE );         /*  */
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Rerference error" ); 
			return EXE_FAILED;
		}		
	}
	/* 记录参考数据有多少种 */
	if( EXE_SUCCEED==SPI_Flash_Write_Page( (uint8_t *)pstuRecRerference,SPIFLASH_SERIAL_BASE_ADDR,sizeof(PRO_SERIAL) ) ){ /* clear */
		return EXE_SUCCEED;
	}else{
		uTjc4832tSetPage( TJC_WARN_PAGE );         /*  */
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Rerference error" ); 
#if DEBUH_UART1		
		myprintf( "FlashWriteError \r\n" );
#endif
		return EXE_FAILED;
	}	
}

uint8_t uStoreReferenceResult( uint8_t uDisInfo )
{
	if( BUTTON_VALUE_REFERENCE==uDisInfo ){
		uTjc4832tSetPage( TJC_SET_PAGE );
	}else if( (BUTTON_VALUE_B1REFERENCE==uDisInfo)||(BUTTON_VALUE_B3REFERENCE==uDisInfo)||(BUTTON_VALUE_B5REFERENCE==uDisInfo) ){
		uTjc4832tSetPage( TJC_WARN_PAGE );        /*设置为*/		
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Minimum set ok" );
	}else if( (BUTTON_VALUE_B2REFERENCE==uDisInfo)||(BUTTON_VALUE_B4REFERENCE==uDisInfo)||(BUTTON_VALUE_B6REFERENCE==uDisInfo) ){
		uTjc4832tSetPage( TJC_WARN_PAGE );        /*设置为*/		
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Maximum set ok" );
	}else{
		uTjc4832tSetPage( TJC_WARN_PAGE );        /*设置为*/		
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Err parameter" );
	}
	
	return EXE_SUCCEED;
}
	
uint8_t uLinearRangeWarn( uint8_t uWarn )
{
	uConfirmPage( TJC_WARN_PAGE );        /* 设置为警告页 */
	switch( uWarn ){
		case 0:
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Range: 0-1000000 " );
			break;
		case 1:
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Min<Max " );
			break;
		case 2:
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Name Null " );
			break;
		case 3:
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Already exists, do you want to cover it " );
			break;
	}
	uBuzzerTimes( BUZZER_ONE_TIME );
	
	return EXE_SUCCEED;
}

uint8_t uSpecialPasswordInit( void )
{
	uint8_t uTempArr[7] = "666666";
	
	if( 0==strncmp((const char*)uTempArr,(const char*)g_uSpecialNamePas,sizeof(uTempArr)) ){
		uTjc4832tSetPage( TJC_INSTRUMENT_PAGE ); 
		uDisParameterInit();
	}else{
		uTjc4832tSetPage( TJC_WARN_PAGE );         /*  */
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Password error" ); 
	}
	
	return EXE_SUCCEED;
}

uint8_t uBarErrorProcess( void )
{
//	OS_ERR err;
//	
//	OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_STRICT,&err);   //延时1s
	
	uConfirmPage( TJC_TEST_PAGE );                           /* 退回到测试页 */
	uTestInformation();                                      /* 显示测试信息 */
	
	return EXE_SUCCEED;
}

uint8_t uConfigTime( void )
{	
	//uTjc4832tSetPage( TJC_WARN_PAGE );         /*设置为*/
	
	if( !((1970<=gp_stuEditTime->ustuTimeYears)&&(gp_stuEditTime->ustuTimeYears<=2099)) ){
		uTjc4832tSetPage( TJC_WARN_PAGE );         /*设置为*/
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Years Error");	//
		return EXE_FAILED;
	}
	if( !((0<gp_stuEditTime->ustuTimeMonth)&&(gp_stuEditTime->ustuTimeMonth<=12)) ){
		uTjc4832tSetPage( TJC_WARN_PAGE );         /*设置为*/
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Month Error");	//
		return EXE_FAILED;
	}  
	
	if( Is_Leap_Year(gp_stuEditTime->ustuTimeYears)&&(2==gp_stuEditTime->ustuTimeMonth) ){
		if( !((0<gp_stuEditTime->ustuTimeDay)&&(gp_stuEditTime->ustuTimeDay<=29)) ){
			uTjc4832tSetPage( TJC_WARN_PAGE );         /*设置为*/
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Day Error");	//
			return EXE_FAILED;
		}
	}else if( !((0<gp_stuEditTime->ustuTimeDay)&&(gp_stuEditTime->ustuTimeDay<=mon_table[gp_stuEditTime->ustuTimeMonth-1])) ){
		uTjc4832tSetPage( TJC_WARN_PAGE );         /*设置为*/
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Day Error");	//
		return EXE_FAILED;
	}  
	
	if( (gp_stuEditTime->ustuTimeHours<=23) ){
	
	}else{
		uTjc4832tSetPage( TJC_WARN_PAGE );         /*设置为*/
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Hours Error");	//
		return EXE_FAILED;
	}   
	
	if( (gp_stuEditTime->ustuTimeMinuts<=59) ){
	  
	}else{
		uTjc4832tSetPage( TJC_WARN_PAGE );         /*设置为*/
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Minuts Error");	//
		return EXE_FAILED;
	} 
	gp_stuEditTime->ustuTimeSeconds = 0;
//	if( !((0<gp_stuEditTime->ustuTimeSeconds)&&(gp_stuEditTime->ustuTimeSeconds<=60)) ){
//		uTjc4832tSetPage( TJC_WARN_PAGE );         /*设置为*/
//		return EXE_FAILED;
//	}	
	
	RTC_Set( gp_stuEditTime->ustuTimeYears,gp_stuEditTime->ustuTimeMonth,gp_stuEditTime->ustuTimeDay,    \
			 gp_stuEditTime->ustuTimeHours,gp_stuEditTime->ustuTimeMinuts,gp_stuEditTime->ustuTimeSeconds );
	     
	//uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Time OK");	//
	uTjc4832tSetPage( TJC_SET_PAGE );        /*设置为*/
	
	return EXE_SUCCEED;
}

uint8_t uConfigTimeYears( void )
{		
	uTjc4832tSetPage( TJC_WARN_PAGE );         /*设置为*/ 
	if( !((1970<=gp_stuEditTime->ustuTimeYears)&&(gp_stuEditTime->ustuTimeYears<=2099)) ){
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Years Error");	//
		return EXE_FAILED;
	}

	RTC_Set( gp_stuEditTime->ustuTimeYears,calendar.w_month,calendar.w_date,    \
			 calendar.hour,calendar.min,calendar.sec );
	      
	uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Years OK");	//
	
	return EXE_SUCCEED;
}

uint8_t uConfigTimeMonth( void )
{		
	uTjc4832tSetPage( TJC_WARN_PAGE );         /*设置为*/ 
	if( !((0<gp_stuEditTime->ustuTimeMonth)&&(gp_stuEditTime->ustuTimeMonth<=12)) ){
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Month Error");	//
		return EXE_FAILED;
	} 

	RTC_Set( calendar.w_year,gp_stuEditTime->ustuTimeMonth,calendar.w_date,    \
		     calendar.hour,calendar.min,calendar.sec );
	       
	uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Month OK");	//
	
	return EXE_SUCCEED;
}

uint8_t uConfigTimeData( void )
{	
	uTjc4832tSetPage( TJC_WARN_PAGE );         /*设置为*/ 
	
	if( Is_Leap_Year(gp_stuEditTime->ustuTimeYears)&&(2==gp_stuEditTime->ustuTimeMonth) ){
		if( !((0<gp_stuEditTime->ustuTimeDay)&&(gp_stuEditTime->ustuTimeDay<=29)) ){
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Day Error");	//
			return EXE_FAILED;
		}
	}else if( !((0<gp_stuEditTime->ustuTimeDay)&&(gp_stuEditTime->ustuTimeDay<=mon_table[gp_stuEditTime->ustuTimeMonth-1])) ){
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Day Error");	//
		return EXE_FAILED;
	}  

	RTC_Set( calendar.w_year,calendar.w_month,gp_stuEditTime->ustuTimeDay,    \
		     calendar.hour,calendar.min,calendar.sec );
	
	uTjc4832tSetPage( TJC_WARN_PAGE );         /*设置为*/       
	uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Day OK");	//
	
	return EXE_SUCCEED;
}

uint8_t uConfigTimeHour( void )
{		
	uTjc4832tSetPage( TJC_WARN_PAGE );         /*设置为*/ 
	
	if( (gp_stuEditTime->ustuTimeHours<=23) ){
	
	}else{
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Hours Error");	//
		return EXE_FAILED;
	}   

	RTC_Set( calendar.w_year,calendar.w_month,calendar.w_date,    \
		     gp_stuEditTime->ustuTimeHours,calendar.min,calendar.sec );

	uTjc4832tSetPage( TJC_WARN_PAGE );         /*设置为*/       
	uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Hours OK");	//
	
	return EXE_SUCCEED;
}

uint8_t uConfigTimeMinutes( void )
{		
	uTjc4832tSetPage( TJC_WARN_PAGE );         /*设置为*/ 
	
	if( (gp_stuEditTime->ustuTimeMinuts<=59) ){
	  
	}else{
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Minuts Error");	//
		return EXE_FAILED;
	} 

	RTC_Set( calendar.w_year,calendar.w_month,calendar.w_date,    \
		     calendar.hour,gp_stuEditTime->ustuTimeMinuts,calendar.sec );
	
	uTjc4832tSetPage( TJC_WARN_PAGE );         /*设置为*/       
	uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Minuts OK");	//
	
	return EXE_SUCCEED;
}

uint8_t uPrompterWarn( uint8_t *pStr )
{
	uConfirmPage( TJC_PROMPTER_PAGE );         /*设置为*/       
	uTjc4832tSetLableValue( TJC_PROMPTER_PAGE,PROMPTER_ID_TXT,(uint8_t *)pStr );	//
	
	return EXE_SUCCEED;
}

uint8_t uTemperatrueDisplay( void )
{
//	uint8_t pTemperaBuf[24] = {0};
//	float fTempTempera = 0;
//	
//	fTempTempera = SMBus_ReadTemp();

//	sprintf( (char *)pTemperaBuf,"%s%.2f%s","Temperature:",fTempTempera,"℃" );
////	sprintf( (char *)pTemperaBuf,"%s%.2f%s","Temperature:",fTempTempera,"度" );
//	
//	uTjc4832tSetPage( TJC_WARN_PAGE );         /*设置为*/       
//	uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)pTemperaBuf );	//
	
	return EXE_SUCCEED;
}

/* 需要完善 */
uint8_t uFactoryReset( void )
{
//	OS_ERR err = OS_ERR_NONE;
//	
//	uTjc4832tSetPage( TJC_PROMPT_PAGE );        /*设置为*/
//	OSTimeDlyHMSM(0, 0, 0, 150,OS_OPT_TIME_HMSM_STRICT,&err);
//	uTjc4832tSetLableValue( TJC_PROMPT_PAGE,SET1_TEXT_DIS_CON_ID,(uint8_t *)"Factory Reset ..." );
//	
//	/* 第一页永远不擦除 保存配置信息 */
//	uEraseSectorFromStartToEnd( (SPIFLASH_USER_NUMBER_ADRR/SPIFLASH_PAGE_BASE_ADDR),P25Q32H_CLEAR_SECTOR );
//	memset( &g_IdMemory,0,sizeof(ID_Info) );	               /* 清除ID卡 */
//	memset( &g_stuMyAlgorithm,0,sizeof(ALGORITHM_DATA_TYPE) ); /* 清楚测试数据 */
//	memset( &g_stuUserMoreInfo,0,sizeof(USER_MORE_INFO) );     /* 清除用户信息 */
//	uReferenceClear();                                         /* 清除参考区间 */
//	uHistoryClear( UI_N_PROMPT );                              /* 清除流水号 */
//	
//	uTjc4832tSetLableValue( TJC_PROMPT_PAGE,SET1_TEXT_DIS_CON_ID,(uint8_t *)"Please turn on later." );
//	/* 是否需要蜂鸣器提示 */
//	OSTimeDlyHMSM(0, 0, 2, 500,OS_OPT_TIME_HMSM_STRICT,&err);	
//	
//	//vPromptShutDown( POWER_FORCE,POWER_FORCE_05_SECOND );       /* 关机 不可取消 */
//	vShutDown();                  /* 直接强制关机 不可取消 */
	
	return EXE_SUCCEED;
}

uint8_t uEraseSectorFromStartToEnd( uint16_t uStart,uint16_t uEnd )
{
	uint16_t i = 0;	
	
	for( i=uStart;i<=(uEnd);i++ ){                     /* 擦除整个芯片 */
		SPI_Flash_Erase_Sector(i);//擦除一个扇区 4k
	}
	
	return EXE_SUCCEED;
}

uint8_t uHistoryClear( uint8_t uPoempter )
{	
	if( UI_Y_PROMPT==uPoempter ){
		SPI_Flash_Erase_Sector(P25Q32H_CLEAR_SECTOR-2);               /* 清除第一页 ? */
		SPI_Flash_Erase_Sector(P25Q32H_CLEAR_SECTOR-1);               /* 清除第一页 */
		SPI_Flash_Erase_Sector(P25Q32H_CLEAR_SECTOR);                 /* 清除第一页 */
		g_projectSerial.history_count = 0;                            /* 从第一页开始 */
		g_projectSerial.history_max = 1;                              /* 只有一页 */
		uConfirmPage( TJC_INSTRUMENT_PAGE );
		
		//uDisParameterInit();
		//uDisplayHistoryData( HISTORY1_PAGE );                       /* 显示历史页 */		
		//uPromptInformation( (uint8_t *)"Clear Ok" );
		
		if( EXE_SUCCEED==SPI_Flash_Write_Page( (uint8_t *)&g_projectSerial,SPIFLASH_SERIAL_BASE_ADDR,sizeof(PRO_SERIAL) ) ){ /* clear */
			return EXE_SUCCEED;
		}else{
			return EXE_FAILED;
		}
	}else{
		memset( &g_projectSerial,0,sizeof(PRO_SERIAL) );           /* 清除流水号 */	
		/* 流水号初始化 */
		uSerialFileInit();
	
	}	
	
	return EXE_SUCCEED;
}

uint8_t uReferenceClear( void )
{
	memset( &g_stuUserReference,0,sizeof(USER_REFERRENCE) );   /* 清除参考区间 */
	
	if( EXE_SUCCEED==SPI_Flash_Write_Page( (uint8_t *)&g_stuUserReference,SPIFLASH_USER_REFER_ADDR,sizeof(USER_REFERRENCE) ) ){
		return EXE_SUCCEED;
	}else{
		uTjc4832tSetPage( TJC_WARN_PAGE );         /*  */
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Rerference error" ); 
		return EXE_FAILED;
	}
}

uint8_t uConfigUpgrade( void )
{
	return 0;
}

uint8_t uSetIdReturnPage( void )
{	
	return 0;
}

uint8_t uSemclear( OS_SEM* pSem )
{
	OS_ERR err = OS_ERR_NONE;
	
	OSSemSet( pSem,0,(OS_ERR *)&err );
	if( OS_ERR_NONE==err ){
		return EXE_SUCCEED;
	}else{
		return EXE_FAILED;
	}
}

uint8_t* vPutFloat( uint8_t* pArr, float fTemp )
{
	uint8_t* puTemp = (uint8_t *)&fTemp;
	uint8_t i = 0;
	uint8_t* pTempArr = pArr;
	
	for( i=0;i<4;i++ )
	{
		*pTempArr++ = *puTemp++;
	}
	
	return pArr;
}

float vGetFloat( uint8_t* pArr )
{
	float fTemp = 0;
	uint8_t* puTemp = (uint8_t *)&fTemp;
	uint8_t i = 0;

	for( i=0;i<4;i++ )
	{
		*puTemp++ = *pArr++;
	}
	
	return fTemp;
}

/* 不能增加结果判断 会导致通讯失败 */
uint8_t* ReadIDTou8Arr( uint8_t* u8Arr,uint16_t u16Addr,uint8_t size )
{
	uint8_t i=0;
	
	for( i=0;i<size;i++ ){	
//		u8Arr[i] = At24c32ReadByte( _gp_ID,u16Addr+i );	
	}
	
	return u8Arr;
}

uint16_t* ReadIDTou16Arr( uint16_t* u16Arr,uint16_t u16Addr,uint8_t size )
{
	uint8_t i=0;
	
	for( i=0;i<size;i++ )
	{
//		u16Arr[i] = At24c32ReadTwoByte( _gp_ID,u16Addr+(i*2) );
	}
	
	return u16Arr;
}

uint8_t WriteIDTou8Arr( uint8_t* u8Arr,uint16_t u16Addr,uint8_t size )
{
	uint8_t i=0;
	
	for( i=0;i<size;i++ ){	
//		if( !At24c32WriteByte(_gp_ID,u16Addr+i,u8Arr[i]) ){
//			return EXE_FAILED;
//		}	
	}
	
	return EXE_SUCCEED;
}

void vEnableUsartPrintf( uint8_t uUsart )
{
	CPU_SR_ALLOC();                                             /*申请临界区变量*/
	
	OS_CRITICAL_ENTER();          /* 临界资源保护 */
	g_UsartPrintfFlag = uUsart;   //标识串口号
	OS_CRITICAL_EXIT();           /* 临界资源保护 */
}

uint8_t uGetUsartPrintf( void )
{
	return g_UsartPrintfFlag;                  //标识串口号
}

uint8_t uErrorInvalidId( uint8_t uBuzzer )
{
	OS_ERR err;
	
	uConfirmPage( TJC_WARN_PAGE );                                                               /* 设置为强制警告页 */
	uTjc4832tSetLableValuePco( TJC_WARN_PAGE,WARN_ID_NUM,TJC_RED );                              /* 设置为红色字体 */
	OSTimeDlyHMSM(0, 0, 0, 20,OS_OPT_TIME_HMSM_STRICT,&err);
	uTjc4832tSetLableValuePco( TJC_WARN_PAGE,WARN_ID_NUM,TJC_RED );                              /* 设置为红色字体 */
	if( EN_ON==gp_stuConfigFile->uCutEnCu ){
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Invalid ID data" );	     //ID数据错误
	}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"无效ID卡" );	             //ID数据错误
	}else{
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Invalid" );	             //ID数据错误
	}
	
	if( BUZZER_ON==uBuzzer ){
		uBuzzerTimes( BUZZER_ONE_TIME );
	}
	
	return EXE_SUCCEED;
}

/* 返回0时 没有存储过相同条码 */
int8_t uVerifyIDBar( uint8_t* puArrBarCode )
{
	uint8_t i = 0;
	uint8_t uArrBarCodeTemp[5] = {0};
	ID_Info* pIDData = NULL;
	
	pIDData = (ID_Info *)calloc( sizeof(ID_Info),sizeof(uint8_t) );
	if( NULL==pIDData ){
		return EXE_FAILED;
	}
	
	for( i=0;i<g_projectSerial.uid_max;i++ ){
		pIDData = uReadStoreIdItemCope( i,pIDData );//uReadStoreIdItem( i );					
		if( NULL!=pIDData ){
			/* ID卡数据校验 */
			//uReadStoreIdItem( uGetIdCountValue() );     /* 重新读取 */					
			if( EXE_FAILED==uVerifyId( pIDData ) ){
				//uErrorInvalidId( BUZZER_OFF );                        /* ID卡无效报错 */
				continue;           
			}
			
			if( NULL==uBarTransition( pIDData,uArrBarCodeTemp ) ){    /* 转换条码 */
				memset( uArrBarCodeTemp,0,sizeof(uArrBarCodeTemp) );
			}				
		}
		if( (barcompare((const char *)uArrBarCodeTemp,(const char *)puArrBarCode,sizeof(uArrBarCodeTemp))) ){  /* 不相同返回1 */
			if( (i>(g_projectSerial.uid_max-1)) ){//if( (i>=(g_projectSerial.uid_max-1)) ){
				if( NULL!=pIDData ){
					free( pIDData );
				}
				return EXE_SPECIAL_FAILED;//uRecBarError = EXE_FAILED;
			}
		}else{
			if( NULL!=pIDData ){
				free( pIDData );
			}
			return i+1;//uRecIdCardNum = i;
			//break;
		}
	}
	
	if( NULL!=pIDData ){
		free( pIDData );
	}
	return EXE_SUCCEED;	
}

uint8_t uInitIdInfo( ID_Info* stuIdInfo )
{
//	USER_REFERRENCE stuTempRerfence = {0};
//	OS_ERR err = OS_ERR_NONE;
//	
//	uint8_t* pu8At24ReadBuff = NULL;
//	uint8_t uRecNum = 18;
//	uint8_t i = 0;
//	uint8_t uRecBarStrage = 0;
//	uint8_t uArrBarCodeTemp[5] = {0};
//#if DEBUH_UART1		
//	uint32_t uTestTimeStart = 0;
//	uint32_t uTestTimeEnd = 0;
//	
//	uTestTimeStart = OSTimeGet( &err );
//#endif
//	
//	pu8At24ReadBuff = (uint8_t *)calloc( uRecNum,sizeof(uint8_t) );
//	if( NULL==pu8At24ReadBuff )	{
//		return EXE_FAILED;
//	}
//	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x003b,uRecNum );	 /* 读项目名称 */	
//	memcpy( stuIdInfo->project_name,pu8At24ReadBuff,uRecNum );	
//	stuIdInfo->project_name[19] = '\0'; 
//	memset( pu8At24ReadBuff,0,uRecNum );	
//	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x06F5,1 );	 /* 项目代码 */	
//	stuIdInfo->product_code = pu8At24ReadBuff[0];
//	memset( pu8At24ReadBuff,0,uRecNum );	
//	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x06F4,1 );	 /* 仪器类型 */	
//	stuIdInfo->Instrument = pu8At24ReadBuff[0];
//	memset( pu8At24ReadBuff,0,uRecNum );	
//	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x009C,2 );	 /* 预读时间 */	
//	stuIdInfo->prepare_time = (uint16_t)pu8At24ReadBuff[0] + (((uint16_t)pu8At24ReadBuff[1])<<8);
//	memset( pu8At24ReadBuff,0,uRecNum );
//	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x009E,2 );	 /* 测试时间 */	
//	stuIdInfo->test_time = (uint16_t)pu8At24ReadBuff[0] + (((uint16_t)pu8At24ReadBuff[1])<<8);
//	memset( pu8At24ReadBuff,0,uRecNum );
//	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x06EE,2 );	 /* 读加样量 */	
//	stuIdInfo->sample_measure = (uint16_t)pu8At24ReadBuff[0] + (((uint16_t)pu8At24ReadBuff[1])<<8);
//	memset( pu8At24ReadBuff,0,uRecNum );	
//	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x06F0,2 );	 /* 缓冲液量 */	
//	stuIdInfo->buffer_measure = (uint16_t)pu8At24ReadBuff[0] + (((uint16_t)pu8At24ReadBuff[1])<<8);
//	memset( pu8At24ReadBuff,0,uRecNum );	
//	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x09F2,2 );	 /* 混合液量 */	
//	stuIdInfo->mix_measure = (uint16_t)pu8At24ReadBuff[0] + (((uint16_t)pu8At24ReadBuff[1])<<8);
//	memset( pu8At24ReadBuff,0,uRecNum );	
//	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x06ec,1 );	 /* 读封个数 */	
//	stuIdInfo->peak_num = 0x0f&(*pu8At24ReadBuff);             
//	stuIdInfo->c_peak = (0xf0&(*pu8At24ReadBuff))>>4;                /* 读基准峰 */	
//	memset( pu8At24ReadBuff,0,uRecNum );	
//	
//	for( i=0; i<stuIdInfo->peak_num;i++ )       /* 读5个峰的起点和终点 */
//	{			
//		pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x0060+(i*6),2 );	 /* 读S1 */	
//		stuIdInfo->interval_s[i] = (uint16_t)pu8At24ReadBuff[0] + (((uint16_t)pu8At24ReadBuff[1])<<8);
//		memset( pu8At24ReadBuff,0,uRecNum );
//						
//		pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x0062+(i*6),2 );	 /* 读E1 */	
//		stuIdInfo->interval_e[i] = (uint16_t)pu8At24ReadBuff[0] + (((uint16_t)pu8At24ReadBuff[1])<<8);	
//		memset( pu8At24ReadBuff,0,uRecNum );		

//		/* 读取值和取峰算法 */		
//		pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x0064+(i*6),1 );
//		stuIdInfo->se_value[i] = pu8At24ReadBuff[0];
//		memset( pu8At24ReadBuff,0,uRecNum );
//		
//		pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x0065+(i*6),1 );
//		stuIdInfo->se_algorithm[i] = pu8At24ReadBuff[0];
//		memset( pu8At24ReadBuff,0,uRecNum );		
//	}
//	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x00A8,1 );	 /* 峰序号 */	
//	stuIdInfo->wavenumber = pu8At24ReadBuff[0];
//	memset( pu8At24ReadBuff,0,uRecNum );
//	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x00A9,1 );	 /* 判定未加样 */	
//	stuIdInfo->nullsample = pu8At24ReadBuff[0];
//	memset( pu8At24ReadBuff,0,uRecNum );
//	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x00A0,1 );	 /* 值 */	
//	stuIdInfo->samplevalue = pu8At24ReadBuff[0];
//	memset( pu8At24ReadBuff,0,uRecNum );
//	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x002b,7 );	 /* 读项目批号 */
//	memcpy(stuIdInfo->lot_num,pu8At24ReadBuff,7 );
//	stuIdInfo->lot_num[7] = '\0'; 
//	memset( pu8At24ReadBuff,0,uRecNum );		
//	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x06FA,1 );	 /* 有效月数 */	
//	stuIdInfo->month_num = pu8At24ReadBuff[0];
//	memset( pu8At24ReadBuff,0,uRecNum );		
//	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x004B,5 );	 /* 地区 */
//	memcpy(stuIdInfo->area_limit,pu8At24ReadBuff,5 );
//	stuIdInfo->area_limit[7] = '\0'; 
//	memset( pu8At24ReadBuff,0,uRecNum );
//	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x06F6,2 );	 /* 生产年 */	
//	stuIdInfo->produce_years = (uint16_t)pu8At24ReadBuff[0] + (((uint16_t)pu8At24ReadBuff[1])<<8);
//	memset( pu8At24ReadBuff,0,uRecNum );
//	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x06F8,1 );	 /* 生产月 */	
//	stuIdInfo->produce_month = pu8At24ReadBuff[0];
//	memset( pu8At24ReadBuff,0,uRecNum );	
//	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x06F9,1 );	 /* 批次 */	
//	stuIdInfo->lot = pu8At24ReadBuff[0];
//	memset( pu8At24ReadBuff,0,uRecNum );	

//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x001e,5 );	 /* 读条形码 */
//	memcpy(stuIdInfo->barcode,pu8At24ReadBuff,5 );
//	stuIdInfo->barcode[7] = '\0'; 
//	memset( pu8At24ReadBuff,0,uRecNum );	
//	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x06ED,1 );	 /* 子项目数 */	
//	stuIdInfo->children_num = pu8At24ReadBuff[0];
//	memset( pu8At24ReadBuff,0,uRecNum );	
//	
//	if( NULL!=pu8At24ReadBuff )	{
//		free( pu8At24ReadBuff );
//	}
//	
//#if DEBUH_UART1		
//	uTestTimeEnd = OSTimeGet(&err);
//	myprintf( "IDTime1:%d \r\n",uTestTimeEnd-uTestTimeStart );
//#endif
//	
//#if DEBUH_UART1			
//	vIDAllPrint( stuIdInfo );			
//#endif
//#if DEBUH_UART1		
//	uTestTimeEnd = OSTimeGet( &err );
//	myprintf( "IDTime2:%d \r\n",uTestTimeEnd-uTestTimeStart );
//#endif
//     
//	if( (EXE_FAILED==uVerifyId( stuIdInfo )) ){                                  /* 效验ID卡 */		
//		uErrorInvalidId( BUZZER_ON );                                            /* 报错 */
//		return EXE_FAILED;
//	}else{
//		uChangeIdCard( stuIdInfo );                                              /* 映射id卡内容 */
//		
//		if( NULL==uBarTransition( stuIdInfo,uArrBarCodeTemp ) ){                 /* 转换条码 */
//			memset( uArrBarCodeTemp,0,sizeof(uArrBarCodeTemp) );
//		}
//		uRecBarStrage = uVerifyIDBar(uArrBarCodeTemp);
//		if( EXE_SUCCEED!=uRecBarStrage ){
//			g_uRecordIdCardCover = uRecBarStrage-1;                              /* 记录覆盖ID卡 */
//			if( EN_ON==gp_stuConfigFile->uCutEnCu ){
//				uPrompterWarn( (uint8_t *)"Cover ID?" );                                /* 提示用户 让用户选择 */
//			}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
//				uPrompterWarn( (uint8_t *)"覆盖?" );                                           
//			}else{
//				uPrompterWarn( (uint8_t *)"Invalid" ); 
//			}				
//			
//			uBuzzerTimes( BUZZER_ONE_TIME );

//			return EXE_FAILED;
//		}
//		
//		memcpy( stuTempRerfence.ureference_name,stuIdInfo->project_name,uRecNum );             /* 项目名字现在最长20个 */
//		uSetMassRerference( &stuTempRerfence,&g_projectSerial );                               /* 设置全部参考值 g_projectSerial内部使用 */
//	
//		/* 将读出的信息存储在FLASH */	
//		if( EXE_SUCCEED==SPI_Flash_Write_Page( (uint8_t *)stuIdInfo,SPIFLASH_IDA_BASE_ADDR+(g_projectSerial.uid_count*SPIFLASH_ID_NUM_BASE),sizeof(ID_Info) ) ){	
//		}else{
//#if DEBUH_UART1		
//			myprintf( "FlashWriteError \r\n" );
//#endif
//		}		
//	}	

	return EXE_SUCCEED;
}

uint8_t uInitIdChildren( UINTE_DATA_TYPE* stuIdInfo,uint8_t uChildren,uint8_t uSpcIndex )
{
//	OS_ERR err = OS_ERR_NONE;
//	uint8_t i = 0;
//	uint8_t uRecNum = 18;
//	uint8_t* pu8At24ReadBuff = NULL;
//#if DEBUH_UART1		
//	uint32_t uTestTimeStart = 0;
//	uint32_t uTestTimeEnd = 0;
//	
//	uTestTimeStart = OSTimeGet(&err);
//#endif
//	
//	pu8At24ReadBuff = (uint8_t *)calloc( 18,sizeof(uint8_t) );
//	if( NULL==pu8At24ReadBuff )	{
//		return EXE_FAILED;
//	}
//	
//	for( i=0; i<15;i++ )      /* 读取15个浓度值和反应值 */
//	{
//		memset( pu8At24ReadBuff,0,uRecNum );	
//		pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x0708+(i*4)+(uChildren*0xc8),4 );	 /* 反应值  */	
//		stuIdInfo->children_density[i] = vGetFloat( pu8At24ReadBuff );		
//		
//		memset( pu8At24ReadBuff,0,uRecNum );	
//		pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x075c+(i*4)+(uChildren*0xc8),4 );	 /* 浓度值 */			
//		stuIdInfo->children_pesponse[i] = vGetFloat( pu8At24ReadBuff );
//	}	
//	
//	memset( pu8At24ReadBuff,0,uRecNum );	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x0702+(uChildren*0xc8),1 );	 /* 反应值变换 */	
//	stuIdInfo->children_vary_pesponse = pu8At24ReadBuff[0];
//		
//	memset( pu8At24ReadBuff,0,uRecNum );
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x0701+(uChildren*0xc8),1 );	 /* 浓度变换 */	
//	stuIdInfo->children_vary_density = pu8At24ReadBuff[0];
//	
//	memset( pu8At24ReadBuff,0,uRecNum );
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x0703+(uChildren*0xc8),1 );	 /* 读取反应值和浓度值小数位 */	
//	stuIdInfo->children_pesponse_dot = 0x0f&(*pu8At24ReadBuff);                      /* 反应值小数 */
//	stuIdInfo->children_density_dot = (0xf0&(*pu8At24ReadBuff))>>4;                  /* 浓度值小数 */
//	
//	memset( pu8At24ReadBuff,0,uRecNum );	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x0704+(uChildren*0xc8),1 );	 /* 拟合算法 */	
//	stuIdInfo->children_ufitt = pu8At24ReadBuff[0];

//	memset( pu8At24ReadBuff,0,uRecNum );				
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x07b0+(uChildren*0xc8),4 );	 /* 读a */	
//	stuIdInfo->children_para_a = vGetFloat( pu8At24ReadBuff );
//	
//	memset( pu8At24ReadBuff,0,uRecNum );		
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x07b4+(uChildren*0xc8),4 );	 /* 读b */
//	stuIdInfo->children_para_b = vGetFloat( pu8At24ReadBuff );	

//	memset( pu8At24ReadBuff,0,uRecNum );				
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x07b8+(uChildren*0xc8),4 );	 /* 读c */	
//	stuIdInfo->children_para_c = vGetFloat( pu8At24ReadBuff );
//	
//	memset( pu8At24ReadBuff,0,uRecNum );	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x07bc+(uChildren*0xc8),4 );	 /* 读d */	
//	stuIdInfo->children_para_d = vGetFloat( pu8At24ReadBuff );	
//	
//	/* 以下地址间隔不一致需要注意 */
//	memset( pu8At24ReadBuff,0,uRecNum );	
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x0175+(uChildren*0x140),1 );	 /* P1 */	
//	stuIdInfo->children_c_1p = pu8At24ReadBuff[0];
//	
//	memset( pu8At24ReadBuff,0,uRecNum );
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x0176+(uChildren*0x140),1 );	 /* P2 */	
//	stuIdInfo->children_c_2p = pu8At24ReadBuff[0];
//		
//	memset( pu8At24ReadBuff,0,uRecNum );
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x0177+(uChildren*0x140),1 );	 /* P3 */	
//	stuIdInfo->children_c_3p = pu8At24ReadBuff[0];	
//	
//	memset( pu8At24ReadBuff,0,uRecNum );
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x0178+(uChildren*0x140),1 );	 /* T/C公式 */	
//	stuIdInfo->children_formula_tc = pu8At24ReadBuff[0];	
//	
//	memset( pu8At24ReadBuff,0,uRecNum );
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x00AC+(uChildren*0x140),18 );	 /* 子项名称 */
//	memcpy(stuIdInfo->children_name,pu8At24ReadBuff,18 );
//	stuIdInfo->children_name[19] = '\0'; 

//	memset( pu8At24ReadBuff,0,uRecNum );
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x00FC+(uChildren*0x140),7 );	 /* 单位 */
//	memcpy(stuIdInfo->children_unit_name,pu8At24ReadBuff,7 );
//	stuIdInfo->children_unit_name[7] = '\0'; 

//	memset( pu8At24ReadBuff,0,uRecNum );
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x014C+(uChildren*0x140),4 );	 /* 范围小 */	
//	stuIdInfo->children_limits_min = vGetFloat( pu8At24ReadBuff );
//	
//	memset( pu8At24ReadBuff,0,uRecNum );
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x0160+(uChildren*0x140),4 );	 /* 范围大 */	
//	stuIdInfo->children_limits_max = vGetFloat( pu8At24ReadBuff );

//	memset( pu8At24ReadBuff,0,uRecNum );
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x0174+(uChildren*0x140),1 );	 /* 范围小数位 */	
//	stuIdInfo->children_limits_dot = pu8At24ReadBuff[0];
//	
//	memset( pu8At24ReadBuff,0,uRecNum );
//	pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x017e+(uChildren*0x140),1 );	 /* 系数小数位 */	
//	stuIdInfo->children_coefficient_dot = pu8At24ReadBuff[0];
//	
//	/* 样品系数不止两个暂时只读两个 */
//	for( i=0;i<10;i++ ){
//		memset( pu8At24ReadBuff,0,uRecNum );
//		pu8At24ReadBuff = ReadIDTou8Arr( pu8At24ReadBuff,0x0180+(i*4)+(uChildren*0x140),4 );	 /* 样品系数 */	
//		stuIdInfo->children_sample_coefficient[i] = vGetFloat( pu8At24ReadBuff );
//	}
//	
//	if( NULL!=pu8At24ReadBuff )	{
//		free( pu8At24ReadBuff );
//	}
//	
//#if DEBUH_UART1		
//	uTestTimeEnd = OSTimeGet(&err);
//	myprintf( "ChildrenTime1:%d \r\n",uTestTimeEnd-uTestTimeStart );
//#endif
//	
//#if DEBUH_UART1			
//	vIDChildrenPrint( stuIdInfo,uChildren );			
//#endif
//	
//#if DEBUH_UART1		
//	uTestTimeEnd = OSTimeGet(&err);
//	myprintf( "ChildrenTime2:%d \r\n",uTestTimeEnd-uTestTimeStart );
//#endif

//	if( EXE_FAILED==uVerifyIdChildren( stuIdInfo ) ){
//		uErrorInvalidId( BUZZER_ON );                                            /* 报错 */
//		return EXE_FAILED;
//	}else{
//		if( COVER_ID_CHI_OFF==uSpcIndex ){
//			/* 将读出的信息存储在FLASH */	
//			if( EXE_SUCCEED==SPI_Flash_Write_Page( (uint8_t *)(stuIdInfo),SPIFLASH_IDB_BASE_ADDR+(uChildren*SPIFLASH_PAGE_BASE_ADDR)+(g_projectSerial.uid_count*SPIFLASH_ID_NUM_BASE),sizeof(UINTE_DATA_TYPE) ) ){	
//			}else{
//#if DEBUH_UART1		
//			myprintf( "FlashWriteError \r\n" );
//#endif
//			}
//		}else{						/* 将读出的信息存储在FLASH */	
//			if( EXE_SUCCEED==SPI_Flash_Write_Page( (uint8_t *)(stuIdInfo),SPIFLASH_IDB_BASE_ADDR+(uChildren*SPIFLASH_PAGE_BASE_ADDR)+(g_uRecordIdCardCover*SPIFLASH_ID_NUM_BASE),sizeof(UINTE_DATA_TYPE) ) ){	
//			}else{
//#if DEBUH_UART1		
//			myprintf( "FlashWriteError \r\n" );
//#endif
//			}
//		}		
//	}
	
	return EXE_SUCCEED;
}

uint8_t uReadChildrenData( UINTE_DATA_TYPE* stuIdInfo,uint8_t uChildren,uint8_t uIdNum )
{
	if( (uIdNum<MAX_IDCARD_NUM) ){
		//SPI_Flash_Init();  		//SPI FLASH 初始化 ;   /* 后续可能不需要再初始化 */
		SPI_Flash_Read( (uint8_t *)(stuIdInfo),SPIFLASH_IDB_BASE_ADDR+(uChildren*SPIFLASH_PAGE_BASE_ADDR)+(uIdNum*SPIFLASH_ID_NUM_BASE),sizeof(UINTE_DATA_TYPE) );
		return EXE_SUCCEED;
	}else{
		return EXE_FAILED;
	}
}

uint8_t uDisplayHistoryData( uint8_t pageid )
{
//	uint8_t err = 0;
	
//	OSMutexPend( (OS_MUTEX *)&g_Historysem,0,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	          /* 等待信号量 */	
//	if( OS_ERR_NONE==err ){
//		DisplayHistoryData( pageid );          /* 显示历史页 */
//		OSMutexPost( (OS_MUTEX *)&g_Historysem,OS_OPT_POST_NO_SCHED,( OS_ERR *)&err );                                    /* 释放信号量 */              
//	}
	return EXE_SUCCEED;
}

uint8_t DisplayHistoryData( uint8_t pageid )
{
	uint8_t i = 0;
	GYK950E* pHistoryMyForm = NULL;
	
	pHistoryMyForm = calloc( 1,sizeof(GYK950E) );
	if( NULL==pHistoryMyForm ){
		return NULL;
	}
#if DEBUH_UART1			
	myprintf( "GYK950E Size:%d\r\n",sizeof(GYK950E) );
#endif
	
	SPI_Flash_Read( (uint8_t *)&g_projectSerial,SPIFLASH_SERIAL_BASE_ADDR,sizeof(g_projectSerial) );
#if DEBUH_UART1			
	myprintf( "history num:%d serial_num:%d\r\n",g_projectSerial.history_count,g_projectSerial.serial_num );
#endif
	
	if( BUTTON_VALUE_HISTORY_PRINT==pageid ){			
		SPI_Flash_Read( (uint8_t *)pHistoryMyForm,(SPIFLASH_DENSITY_BASE_ADDR+(g_uRecordHistoryPage*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );
		
		//DisplayHistoryDataTxt( pHistoryMyForm );
		
		sprintf( (char *)pHistoryMyForm->uGyk_printtime,"%04d-%02d-%02d %02d:%02d:%02d",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec );
			
		GyK950ePrintForm( pHistoryMyForm );
	}else{
		if( BUTTON_VALUE_HISTORY_DOWN==pageid ){
			if( g_projectSerial.history_max-1>g_uRecordHistoryPage ){  //STORAGE_DENSITY_MAX>g_uRecordHistoryPage ){
				g_uRecordHistoryPage++;
			}else{
				g_uRecordHistoryPage = 0;
			}				
		}else if( BUTTON_VALUE_HISTORY_UP==pageid ){
			if( g_uRecordHistoryPage>0 ){
				g_uRecordHistoryPage--;
			}else{	
				g_uRecordHistoryPage = g_projectSerial.history_max-1;     
				if( g_uRecordHistoryPage<=0 ){
					g_uRecordHistoryPage = 0;
				}
			}		
		}else{		
			if( g_projectSerial.history_count-1>=0 ){
				g_uRecordHistoryPage = g_projectSerial.history_count-1;  //g_uRecordHistoryPage = 0;      /* 当前最近的一条数据 */
			}else{
				g_uRecordHistoryPage = 0;
			}	
		}
		
		SPI_Flash_Read( (uint8_t *)pHistoryMyForm,(SPIFLASH_DENSITY_BASE_ADDR+(g_uRecordHistoryPage*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );				
		DisplayHistoryDataTxt( pHistoryMyForm );	
	}
#if DEBUH_UART1			
	myprintf( "g_uRecordHistoryPage num:%d \r\n",g_uRecordHistoryPage );
#endif
	
	if( NULL!=pHistoryMyForm ){
		free( pHistoryMyForm );
	}
	return i;
}

uint8_t uDisplayHistoryDataSpecifiedPage( const uint16_t uSpecpageid )
{
	uint8_t i = 0;
	GYK950E* pHistoryMyForm = NULL;
	
	pHistoryMyForm = calloc( 1,sizeof(GYK950E) );
	if( NULL==pHistoryMyForm ){
		return NULL;
	}
#if DEBUH_UART1			
	myprintf( "SpecifiedPage:%d\r\n",uSpecpageid );
#endif
	
	SPI_Flash_Read( (uint8_t *)pHistoryMyForm,(SPIFLASH_DENSITY_BASE_ADDR+(uSpecpageid*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) );				
	DisplayHistoryDataTxt( pHistoryMyForm );			
	
	
	if( NULL!=pHistoryMyForm ){
		free( pHistoryMyForm );
	}
	return i;
}

uint8_t uDisplayReferenceData( uint8_t pageid )
{
//	uint8_t err = 0;
	
//	OSMutexPend( (OS_MUTEX *)&g_Referencesem,0,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	        /* 等待信号量 */	
//	if( OS_ERR_NONE==err ){
//		DisplayReferenceData( pageid );                                                                         /* 显示参考页 */
//		OSMutexPost( (OS_MUTEX *)&g_Referencesem,OS_OPT_POST_NO_SCHED,( OS_ERR *)&err );                        /* 释放信号量 */              
//	}
	
	return EXE_SUCCEED;
}

uint8_t DisplayReferenceData( uint8_t pageid )
{
	uint8_t i = 0;
	
	SPI_Flash_Read( (uint8_t *)&g_projectSerial,SPIFLASH_SERIAL_BASE_ADDR,sizeof(g_projectSerial) );
#if DEBUH_UART1			
	myprintf( "ureference count:%d \r\n",g_projectSerial.ureference_count );
#endif
	
	if( BUTTON_VALUE_REFERENCE_DOWN==pageid ){
		if( g_projectSerial.ureference_max-1>g_uRecordReferencePage ){  //STORAGE_DENSITY_MAX>g_uRecordHistoryPage ){
			g_uRecordReferencePage++;
		}else{
			g_uRecordReferencePage = 0;
		}		
	}else if( BUTTON_VALUE_REFERENCE_UP==pageid ){
		if( g_uRecordReferencePage>0 ){
			g_uRecordReferencePage--;
		}else{	
			g_uRecordReferencePage = g_projectSerial.ureference_max-1;     
			if( g_uRecordReferencePage<=0 ){
				g_uRecordReferencePage = 0;
			}
		}				
	}else{		
		if( (g_projectSerial.ureference_count!=0xff)&&(g_projectSerial.ureference_count-1>=0) ){
			g_uRecordReferencePage = g_projectSerial.ureference_count-1;  //g_uRecordHistoryPage = 0;      /* 当前最近的一条数据 */
		}else{
			g_uRecordReferencePage = 0;
		}		
	}
	
	SPI_Flash_Read( (uint8_t *)&g_stuUserReference,(SPIFLASH_USER_REFER_ADDR+((g_uRecordReferencePage)*SPIFLASH_PAGE_BASE_ADDR)),sizeof(USER_REFERRENCE) );
	uDisInputReferenceInit( &g_stuUserReference,(g_uRecordReferencePage+1) );	
	
#if DEBUH_UART1			
	myprintf( "ureference num:%d \r\n",g_uRecordReferencePage );
#endif

	return i;
}

/* 查找成功后返回查找号 未查找到返回0 */
uint8_t uFindReferenceName( uint8_t* uNameStr )
{
	uint8_t i = 0;
	USER_REFERRENCE* pTempReference = NULL;
	uint8_t uRecLenA = 0;
	uint8_t uRecLenB = 0;
	uint8_t uRecResult = 0;
	
	pTempReference = calloc( 1,sizeof(USER_REFERRENCE) );
	if( NULL==pTempReference ){
		return NULL;
	}
	
	for( i=0;i<g_projectSerial.ureference_max;i++){
		SPI_Flash_Read( (uint8_t *)pTempReference,(SPIFLASH_USER_REFER_ADDR+((i)*SPIFLASH_PAGE_BASE_ADDR)),sizeof(USER_REFERRENCE) );
		uRecLenA = strlen( (const char *)uNameStr);
		uRecLenB = strlen( (const char *)pTempReference->ureference_name);
		if( 0==strncmp( (const char *)uNameStr,(const char *)pTempReference->ureference_name,(uRecLenA<uRecLenB)?(uRecLenB):(uRecLenA) ) ){
			uRecResult = i+1;
			break;
		}
	}

	if( NULL!=pTempReference ){
		free( pTempReference );
	}
	return uRecResult;
}


uint8_t *cReverse(uint8_t *p_num,uint8_t size){	/*补充：把数组第一个存储区地址当做返回值使用，不加const关键字 */
    uint8_t *p_head = p_num, *p_tail = p_num + size - 1, tmp = 0;
	
    while (p_head < p_tail){    
        tmp = *p_head;		/*补充：将头指针和尾指针所捆绑的存储区做交换*/
        *p_head = *p_tail;
        *p_tail = tmp;
        p_head++;    
        p_tail--;    
    }
    return p_num;    
}

int *iReverse(int *p_num,int size){	
    int *p_head = p_num, *p_tail = p_num + size - 1, tmp = 0;
	
    while (p_head < p_tail){   
        tmp = *p_head;		
        *p_head = *p_tail;
        *p_tail = tmp;
        p_head++;    /*交换后前面的地址+1 数字向后移1位*/
        p_tail--;    /*交换后后面的地址-1 数字向前移1位*/
    }
    return p_num;    /*返回数组第一个地址*/
}

void vIDAllPrint( ID_Info* stuIdInfo )
{
	uint8_t i = 0;
	
	myprintf( " \r\nID public information ... \r\n" );
//	myprintf( "g_IdMemory:%d \r\n",sizeof(ID_Info) );
	
	myprintf( "project_name: %s \r\n",stuIdInfo->project_name );
	myprintf( "product_code:%d \r\n",stuIdInfo->product_code );
	myprintf( "Instrument:%d \r\n",stuIdInfo->Instrument );      /* 仪器类型 */
	myprintf( "prepare_time:%d \r\n",stuIdInfo->prepare_time ); 
	myprintf( "test_time:%d \r\n",stuIdInfo->test_time ); 	
	myprintf( "sample_measure:%d \r\n",stuIdInfo->sample_measure );  /* 加样量 */
	myprintf( "buffer_measure:%d \r\n",stuIdInfo->buffer_measure ); 
	myprintf( "mix_measure:%d \r\n",stuIdInfo->mix_measure ); 
	myprintf( "peak_num:%d c_peak:%d \r\n",stuIdInfo->peak_num,stuIdInfo->c_peak );

	myprintf( "interval: \r\n" );
	for( i=0;i<stuIdInfo->peak_num;i++ )    /* 有几个峰 读几个区间 */
	{
		myprintf( "  %5d ",stuIdInfo->interval_s[i] );	
		myprintf( "%5d ",stuIdInfo->interval_e[i] );
		myprintf( "%5d ",stuIdInfo->se_value[i] );	
		myprintf( "%5d \r\n",stuIdInfo->se_algorithm[i] );
	}
	
	myprintf( "wavenumber:%d \r\n",stuIdInfo->wavenumber );      /* 峰序号 */
	myprintf( "nullsample:%d \r\n",stuIdInfo->nullsample );      /* 判定未加样 */
	myprintf( "samplevalue:%d \r\n",stuIdInfo->samplevalue );    /* 值 */
	myprintf( "lot_num:%s \r\n",stuIdInfo->lot_num );            /* 项目批号 	*/
	myprintf( "month_num:%d produce_years:%d produce_month:%d \r\n",stuIdInfo->month_num,stuIdInfo->produce_years,stuIdInfo->produce_month  );   /* 有效月数 生产年月 */
	myprintf( "area_limit:%s \r\n",stuIdInfo->area_limit );    
	myprintf( "lot:%d \r\n",stuIdInfo->lot );   /* 批次 */
	
	myprintf( "barcode: %s \r\n",stuIdInfo->barcode);          /* 条码 */	
	myprintf( "children_num:%d \r\n",stuIdInfo->children_num );           /* 子项数目 */
		
}

void vIDChildrenPrint( UINTE_DATA_TYPE* pstuTemp,uint8_t uChildren )
{
	uint8_t i = 0;
	
	myprintf( " \r\nChildren:%d \r\n",uChildren );
	myprintf( "UINTE_DATA_TYPE:%d \r\n",sizeof(UINTE_DATA_TYPE) );	
	myprintf( " pesponse density: \r\n");
	for( i=0;i<15;i++ )
	{
		myprintf( " %.4f ",pstuTemp->children_pesponse[i] );	
		myprintf( "%.4f \r\n",pstuTemp->children_density[i] );
	}
	
	myprintf( "children_vary_pesponse:%d children_vary_density:%d \r\n",pstuTemp->children_vary_pesponse,pstuTemp->children_vary_density );
	
	myprintf( "children_pesponse_dot:%d children_density_dot:%d \r\n",pstuTemp->children_pesponse_dot,pstuTemp->children_density_dot );
	
	myprintf( "children_ufitt:%d \r\n",pstuTemp->children_ufitt );
	
	myprintf( "children_para_a:%f \r\n",pstuTemp->children_para_a );	
	myprintf( "children_para_b:%f \r\n",pstuTemp->children_para_b );	
	myprintf( "children_para_c:%f \r\n",pstuTemp->children_para_c );	
	myprintf( "children_para_d:%f \r\n",pstuTemp->children_para_d );	
	
	myprintf( "P1:%d P2:%d P3:%d \r\n",pstuTemp->children_c_1p,pstuTemp->children_c_2p,pstuTemp->children_c_3p );
	
	myprintf( "children_formula_tc:%d \r\n",pstuTemp->children_formula_tc );
	
	myprintf( "children_name : %s \r\n",pstuTemp->children_name );
	
	myprintf( "children_unit_name : %s \r\n",pstuTemp->children_unit_name );
	
	myprintf( "limits_min:%f \r\n",pstuTemp->children_limits_min );	
	myprintf( "limits_max:%f \r\n",pstuTemp->children_limits_max );
	
	myprintf( "children_limits_dot:%d children_coefficient_dot:%d \r\n",pstuTemp->children_limits_dot,pstuTemp->children_coefficient_dot );
	
	for( i=0;i<10;i++ )
	{
		myprintf( "children_sample_coefficient%d:%f \r\n",i,pstuTemp->children_sample_coefficient[i] );
	}
}

/* 不相同返回1 */
uint8_t barcompare( const char *stra,const char *strb,uint32_t size )
{
	int i = 0;
	for( i=0;i<size;i++ ){
		if( *(stra++)!=*(strb++) ){
			return 1;
		}
	}
	return 0;
}

uint8_t arrcompare( const unsigned char *stra,const unsigned char *strb,uint32_t size )
{
	int i = 0;
#if DEBUH_UART1	
	int j = 0;
#endif	
	for( i=0;i<size;i++ ){
		if( *(stra+i)!=*(strb+i) ){			
#if DEBUH_UART1	
			myprintf( "Compare i:%d %02x %02x \r\n",i,*(stra+i),*(strb+i) );
#endif	
#if DEBUH_UART1	
			for( j=0;j<size;j++ ){
				myprintf( "stra strb j:%d %02x %02x \r\n",j,*(stra+j),*(strb+j) );
			}
#endif	
			return 1;
		}
	}
	return 0;
}

uint8_t uReportSemErr( OS_SEM *pSem,uint16_t uTime,uint8_t *uErrStr )
{
	OS_ERR err = OS_ERR_NONE;

	OSSemPend( (OS_SEM *)pSem, uTime,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	           /* 等待WIFI信号量 */
	if( OS_ERR_NONE==err ){
		return EXE_SUCCEED;
	}else{
#if DEBUH_UART1	
		myprintf( "%s\r\n",uErrStr );
#endif
		return EXE_FAILED;
	}
}

uint8_t uReportSem( OS_SEM *pSem,uint16_t uTime )
{
	OS_ERR err = OS_ERR_NONE;

	OSSemPend( (OS_SEM *)pSem, uTime,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	           /* 等待WIFI信号量 */
	if( OS_ERR_NONE==err ){
		return EXE_SUCCEED;
	}else{
		return EXE_FAILED;
	}
}

uint8_t uBuzzerTimes( uint8_t uTimes )
{
	uint8_t i=0;
	OS_ERR err;
	
	for( i=0;i<uTimes;i++ ){
		uBuzzer( BUZZER_ON ); 
		OSTimeDlyHMSM(0, 0, 0, 100,OS_OPT_TIME_HMSM_STRICT,&err);	 /* 延时10ms   */
		uBuzzer( BUZZER_OFF ); 
	}
	
	return EXE_SUCCEED;
}

uint8_t* ReadEEPTou8Arr( uint8_t* u8Arr,uint16_t u16Addr,uint8_t size )
{
	
	return 0;
}

uint16_t* ReadEEPTou16Arr( uint16_t* u16Arr,uint16_t u16Addr,uint8_t size )
{
	
	return u16Arr;
}

uint8_t WriteEEPTou8Arr( uint8_t* u8Arr,uint16_t u16Addr,uint8_t size )
{
	
	return 0;
}

uint8_t ResetEEP( void )
{	
	
	return 0;
}

#ifdef STM32F10X_HD


#endif
