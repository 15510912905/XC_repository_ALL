/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

		嵌入式开发平台——XC2000液压检测功能定义

  -------------------------------------------------------
   文 件 名   : Func_XC2000_Liquid_Pressure.c
   版 本 号   : V1.0.0.0
   作    者   : ryc
   生成日期   : 2020年04月17日
   功能描述   : XC2000遮挡模块功能定义
   依赖于     : 
 ********************************************************/
 
/*------------------------------------------------------*/
/* 头文件												*/
/*------------------------------------------------------*/
#include "Func_IFP_300_Drv.h"

/*------------------------------------------------------*/
/* 下层对象声明											*/
/*------------------------------------------------------*/

/*------------------------------------------------------*/
/* 本层参数声明											*/
/*------------------------------------------------------*/


/*------------------------------------------------------*/
/* 初始化接口											*/
/*------------------------------------------------------*/

bool bFuncPrivateInit1( void )
{
	_bFuncIFP300DrvInit();                       /* 硬件初始化 */
	_bFuncIFP300ModuleInit();                    /* 模块初始化 */
	_bFuncIFP300SoftWareInit();                  /* 软件变量初始化 */
	
#if DEBUH_UART1	
//	myprintf( "\r\nInit Successful\r\n" );       /* 系统未初始化 */
#endif	
	
	return true;
}

/* 申请临界区变量 本函数在初始化前已经进入临界区 */
bool bFuncIFP300UcosValInit( void )
{
	_bFuncIFP300UcosValInit();                  /* UCOS变量初始化 */
	
	return true;
}

bool bFuncIFP300FlashValInit( void )
{
	SPI_Flash_Read( (u8 *)gp_stuConfigFile,SPIFLASH_CONFIG_FILE_BASE_ADDR,sizeof(CONFIG_FILE) );	
	uConfigAllFileInit();                                                                             /* 默认配置信息初始化 必须第一个配置 */
	SPI_Flash_Read( (uint8_t *)&g_projectSerial,SPIFLASH_SERIAL_BASE_ADDR,sizeof(PRO_SERIAL) );	      /* 流水号信息	*/	
	uSerialFileInit();                                                                                /* 流水号初始化 */
	uSpecialMoreInformationInit();                                                                    /* 初始化用户信息 */	
	uSetPrintTitlesInit();                                                                            /* 打印抬头初始化 */
	uSetRerferenceInit();	                                                                          /* 参考范围信息 */
	
	return true;
}

bool bFuncFlashP25Q32hInit( void )
{
	return _bFuncFlashP25Q32hInit();                                                                          /* FLASH_P25Q32H初始化 */
}

/*------------------------------------------------------*/
/* 模块初始化											*/
/*------------------------------------------------------*/

/* 初始化 _Func_IFP_300_Drv_Init
  ------------------------------
  返回值：true，成功；false，失败
*/
static bool _bFuncIFP300DrvInit(void)
{			
	/* 各种初始化  */
	BSP_Init_Pin(POWER_CONTROL_PORT,POWER_CONTROL_PIN,_OUT_PP_);                                                    /* 电源自动控制 最好放在第一行 */
	POWER_CONTROL_OUT = POWER_CONTROL_TRUE;                                                                         /* 电源输出高 */                                     
	                                                                                                                
	BSP_Init_Pin(POWER3_CONTROL_PORT,POWER3_CONTROL_PIN,_OUT_PP_);                                                  /* 控制3.3v电源  */   
	POWER3_CONTROL_OUT = POWER3_CONTROL_TRUE;                                                                       /* 3.3v电源输出高 */   
	                                                                                                                
	BSP_Init_Pin(POWER5_CONTROL_PORT,POWER5_CONTROL_PIN,_OUT_PP_);                                                  /* 控制5v电源  */	
	POWER5_CONTROL_OUT = POWER5_CONTROL_TRUE;                                                                       /* 5v电源输出高 */  
	                                                                                                                
	BSP_Init_Pin(LED_INDI_CONTROL_PORT,LED_INDI_CONTROL_PIN,_OUT_PP_);                                              /* LED呼吸灯 */
	LED_INDI_CONTROL_OUT = LED_INDI_CONTROL_TRUE;                                                                   /*  默认配置 开启呼吸LED灯	*/
                                                                                                                    
	BSP_Init_Pin(BUZZER_CONTORL_PORT,BUZZER_CONTORL_PIN,_OUT_PP_ );	                                                /* 蜂鸣器 */
	BUZZER_CONTORL_OUT = BUZZER_CONTORL_FALSE;                                                                      /* 默认配置 关闭Buzzer	*/
	
	BSP_Init_Pin(WIFI_RST_PORT,WIFI_RST_PIN,_OUT_PP_);                                                              /* WIFI RST */	
	WIFI_RST_OUT = WIFI_RST_TRUE;                                                                                  /* 默认配置 WIFI关闭	*/
	                                                                                             
	BSP_Init_PinInterrupt(POWER_AUTO_CONTROL_PORT,POWER_AUTO_CONTROL_PIN);                                          /* 外部中断检测电源 */
//	BSP_Init_PinInterrupt(READCARD_DEC_CONTROL_PORT,READCARD_DEC_CONTROL_PIN);                                      /* 插卡检查微动开关 */	
	BSP_Init_PinInterruptIpu(READCARD_DEC_CONTROL_PORT,READCARD_DEC_CONTROL_PIN);                                   /* 插卡检查微动开关 */
	                                                                                                                
	BSP_Init_PinInterrupt(CHARGE_STATUS_PORT,CHARGE_STATUS_PIN);                                                    /* 增加电量充满检查 */
	//BSP_Init_PinInterrupt(HOME_WAK_UP_PORT,HOME_WAK_UP_PIN);                                                      /* 硬件V2.0不需要外部唤醒 wkup换醒 为外部中断 */	
		
//	BSP_Init_UsartInterrupt( _USART1_,UART1_BAUD_RATE,USART1_TX_PORT,USART1_TX_PIN,USART1_RX_PORT,USART1_RX_PIN );	/* 初始化串口1 调试 */
	BSP_Init_UsartInterrupt( _USART2_,UART2_BAUD_RATE,USART2_TX_PORT,USART2_TX_PIN,USART2_RX_PORT,USART2_RX_PIN );	/* 初始化串口2 wifi */
	BSP_Init_UsartInterrupt( _USART3_,UART3_BAUD_RATE,USART3_TX_PORT,USART3_TX_PIN,USART3_RX_PORT,USART3_RX_PIN );	/* 初始化串口3 打印机 */
//	BSP_Init_UsartInterrupt( _USART4_,UART4_BAUD_RATE,USART4_TX_PORT,USART4_TX_PIN,USART4_RX_PORT,USART4_RX_PIN );	/* 初始化串口4 屏幕 */	
	
	USART1_Init( UART1_BAUD_RATE );
	USART1_DMA_Init();                                                                                              /* 串口DMA初始化 */
	USART4_Init( UART4_BAUD_RATE );
	USART4_DMA_Init();   
	
	//BSP_Init_Adc( BAR_CODE_PORT,BAR_CODE_PIN,VSENSE_PIN,_CH_BUTT_,_CH_BUTT_ );                                    /* 条码DATA采集 配置为AD采集 */ //Adc_Init();
	BSP_Init_Adc( VSENSE_PORT,VSENSE_PIN,_CH_BUTT_,_CH_BUTT_,_CH_BUTT_ );                                           /* 采集电池电量 配置为AD采集 */
	Adc_Init();
	
	BSP_Init_Pin(LED_GLOW_CONTORL_PORT,LED_GLOW_CONTORL_PIN,_OUT_PP_);        	                                    /* 引脚特殊  荧光灯硬件PWM控制  */
	LED_GLOW_CONTORL_OUT = LED_GLOW_CONTORL_FALSE;                             	                                    /* 默认配置 关闭CTRL_LED灯	*/

	return true;
}

/* 初始化 _Func_IFP_300_Drv_Init
  ------------------------------
  返回值：true，成功；false，失败
*/
static bool _bFuncIFP300ModuleInit(void)
{			
	/* 各种模块初始化  */	
	_bFuncSteopMotorInit();                                                /* 步进电机引脚初始化 */
	_bFuncIDCardInit();                                                    /* ID卡初始化 */
//	_bFuncFlashP25Q32hInit();                                              /* FLASH_P25Q32H初始化 */
	_bFuncMax5402eInit(MAX5402_INIT_VALUE);                                /* Max5402e初始化 */	
	_bFuncAd7685Init();                                                    /* Ad7685初始化 */	

	return true;
}

/* 步进电机引脚初始化 */
static bool _bFuncSteopMotorInit( void )
{
	BSP_Init_PinInterrupt(MOTOR_RESET_PORT,MOTOR_RESET_PIN);               /* 用于电机复位开关量检测 外部中断 */	
	BSP_Init_Pin(MOTOR_SLEEP_PORT,MOTOR_SLEEP_PIN,_OUT_PP_);               /* Sleep 高电平使能  低电平休眠 */
	BSP_Init_Pin(MOTOR_EN_PORT,MOTOR_EN_PIN,_OUT_PP_);                     /* En */
	BSP_Init_Pin(MOTOR_DIR_PORT,MOTOR_DIR_PIN,_OUT_PP_);                   /* Dir */
	
//	BSP_Init_Pin(MOTOR_DECAYA_PORT,MOTOR_DECAYA_PIN,_OUT_PP_);             /* DECAYA */
//	MOTOR_DECAYA_OUT = MOTOR_DECAYA_TRUE; 
//	BSP_Init_Pin(MOTOR_DECAYB_PORT,MOTOR_DECAYB_PIN,_OUT_PP_);             /* DECAYB */
//	MOTOR_DECAYB_OUT = MOTOR_DECAYB_TRUE; 		
	
//	_gp_PWM1 = PWM_Init(PWM_1, _T2_, MOTOR_STEP_PORT, MOTOR_STEP_PIN);     /*初始化PWM波*/
	
	return true;
}

/* ID卡初始化 */
static bool _bFuncIDCardInit( void )
{	
	BSP_Init_PinInterrupt(ID_DETECT_PORT, ID_DETECT_PIN);                                                                                     /* 外部中断 用于ID插卡检测 */	
//	_gp_ID = At24c32Init(AT24C32_2,AT24C32_ID_ADDR,ID_IIC_CLK_PORT,ID_IIC_CLK_PIN,ID_IIC_SDA_PORT,ID_IIC_SDA_PIN);                            /* 外接 读ID卡 	*/
	
	return true;
}

/* FLASH_P25Q32H初始化 */
static bool _bFuncFlashP25Q32hInit( void )
{	
#if P25Q32H_CHOISE
	/* 使用硬件SPI1 8位数据传输   */
	_gp_HardFlashP25Q32H = Drv_FlashP25Q32hInit( FLASH_P25Q32H_1,_SPI1_,0, \
								                 P25Q32H_SPI_CS_PORT,P25Q32H_SPI_CS_PIN,P25Q32H_SPI_CLK_PORT,P25Q32H_SPI_CLK_PIN, \
								                 P25Q32H_SPI_SDI_PORT,P25Q32H_SPI_SDI_PIN,P25Q32H_SPI_SDO_PORT,P25Q32H_SPI_SDO_PIN );         /* SPI硬件读写	*/	

	if( uSPI_FlashReadID(_gp_HardFlashP25Q32H)!=W25Q128J ){                                                                                    /* 读取FLASH_ID号 */
		//return false;
	}
	
#else
	SPI_Flash_Init();  		                                                                                                                  //SPI FLASH 初始化 ;   /* 后续可能不需要再初始化 */
	if( SPI_Flash_ReadID()!=W25Q128J )							                                                                              //检测不到W25Q64
	{
		uTjc4832tSetPage( TJC_WARN_PAGE );                                                                                                    /*设置为强制警告页*/
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Hardware error" );	                                                  //"25Q64 Check Failed!"//"Please Check!      "
		uBuzzerTimes( BUZZER_ONE_TIME );
		return false;
	}else{
		return true;
	}
#endif

}

/* Max5402e初始化 */
static bool _bFuncMax5402eInit( uint16_t uGain )
{
#if MAX5402_CHOISE
	/* 使用硬件SPI1 8位数据传输 只用于主机输出 */
	_gp_MAX5402Hard = Max5402euaHardInit( MAX5402EUA_HARD_1,uGain,_SPI1_,0, \
	                                      MAX5402_SPI_SDI_PORT,MAX5402_SPI_SDI_PIN,MAX5402_SPI_SDO_PORT,MAX5402_SPI_SDO_PIN,  \
                                          MAX5402_SPI_CLK_PORT,MAX5402_SPI_CLK_PIN,MAX5402_SPI_CS_PORT,MAX5402_SPI_CS_PIN );                   /* 调解接受光的放大倍数 设置初始值 */
	
#else	
	/* 使用软件SPI1 8位数据传输 只用于主机输出 */	
	//uMax5402GainInitSet( gp_stuConfigFile->uMax5402Gain,UI_N_PROMPT );	                                                                       /* Max5402eua初始化 软件SPI */
	
#endif
	return true;
}

/* Ad7685初始化 */
static bool _bFuncAd7685Init( void )
{
    /* 使用硬件SPI2 16位数据传输 */
//	_gp_HardAD7685 = Drv_HardAd7685Init( HARDAD7685_1,_SPI2_, \
//								         AD7685_SPI_CS_PORT,AD7685_SPI_CS_PIN,AD7685_SPI_CLK_PORT,AD7685_SPI_CLK_PIN, \
//								         AD7685_SPI_SDI_PORT,AD7685_SPI_SDI_PIN,_PORT_BUTT_,_PIN_BUTT_ );                                       /* 16ADC  SPI硬件读写	*/

	return true;
}

static bool _bFuncIFP300SoftWareInit(void)
{		
	/* 配置信息初始化 */
	gp_stuEditTime = (USER_TIME_FILE *)calloc( 1,sizeof(USER_TIME_FILE) );                            /* 配置时间编辑框信息 */
	if( NULL==gp_stuEditTime ){
#if DEBUH_UART1	
		myprintf( "Init Fail EditTime\r\n" );       
#endif	
	}
	gp_stuEditInputConfig = (USER_INPUT_CONFIG_FILE *)calloc( 1,sizeof(USER_INPUT_CONFIG_FILE) );     /* 用户输入配置信息 */
	if( NULL==gp_stuEditInputConfig ){
#if DEBUH_UART1	
		myprintf( "Init Fail EditInputConfig\r\n" );       
#endif	
	}
	gp_stuConfigFile = (CONFIG_FILE *)calloc( 1,sizeof(CONFIG_FILE) );                                /* 默认配置信息 */
	if( NULL==gp_stuConfigFile ){
#if DEBUH_UART1	
		myprintf( "Init Fail ConfigFile\r\n" );       
#endif	
	}	

	uTjc4832tReset();                                                                                 /* 复位屏幕 */	
	
	return true;
}

/* 申请临界区变量 本函数在初始化前已经进入临界区 */
static bool _bFuncIFP300UcosValInit(void)
{                                                                                                       
	uint16_t err = 0;
																														    
#if SEM_MUTEX_CHOISE	                                                                                                    
//	OSMutexCreate( (OS_MUTEX *)&g_Historysem,"gp_Historysem",(OS_ERR *)&err );                                              /* 创建读历史信号量 */
//	OSMutexCreate( (OS_MUTEX *)&g_Acquisition,"gp_Acquisition",(OS_ERR *)&err );                                            /* 创建采集信号量 */
	OSMutexCreate( (OS_MUTEX *)&g_FlashCom,"gp_FlashCom",(OS_ERR *)&err );                                                  /* 创建FLASH控制 */
//	OSMutexCreate( (OS_MUTEX *)&g_DisUI,"gp_FlashCom",(OS_ERR *)&err );                                                     /* 创建UI显示 */
//	OSMutexCreate( (OS_MUTEX *)&g_MutIDTask,"gp_MutIDTask",(OS_ERR *)&err );                                                /* 创建ID互斥 */
//	OSMutexCreate( (OS_MUTEX *)&g_Referencesem,"gp_Referencesem",(OS_ERR *)&err );
//	
//	OSSemCreate( (OS_SEM *)&g_ReadIDsem,"gp_ReadIDsem",0,(OS_ERR *)&err );                                                  /* 创建读ID卡信号量 */
	OSSemCreate( (OS_SEM *)&g_TjcTouchsem,"gp_TjcTouchsem",0,(OS_ERR *)&err );                                              /* 创建第二代屏幕信号量 OSMutexCreate */
//	OSSemCreate( (OS_SEM *)&g_LogInsem,"gp_LogInsem",0,(OS_ERR *)&err );                                                    /* 创建登录信号量 */
//	OSSemCreate( (OS_SEM *)&g_ResetLogInsem,"gp_ResetLogInsem",0,(OS_ERR *)&err );                                          /* 创建再次登录信号量 */
	OSSemCreate( (OS_SEM *)&g_PowerOnsem,"gp_PowerOnsem",0,(OS_ERR *)&err );                                                /* 创建开机信号量 */
//	OSSemCreate( (OS_SEM *)&g_ForceExit,"gp_ForceExit",0,(OS_ERR *)&err );                                                  /* 创建强制退出 */
//    OSSemCreate( (OS_SEM *)&g_WarnCencle,"gp_WarnCencle",0,(OS_ERR *)&err );                                                /* 创建警告 */ 
//	OSSemCreate( (OS_SEM *)&g_GetPageId,"gp_GetPageId",0,(OS_ERR *)&err );                                                  /* 创建获取页面id */	
	OSSemCreate( (OS_SEM *)&g_WifiReceive,"gp_WifiReceive",0,(OS_ERR *)&err );                                              /* 创建WIFI*/
	
	
	OSSemCreate( (OS_SEM *)&g_TjcUpdata,"g_TjcUpdata",0,(OS_ERR *)&err );                                                /*  */	                                                 
	OSSemCreate( (OS_SEM *)&g_TjcUpgarde,"g_TjcUpgarde",0,(OS_ERR *)&err ); 

	
//	OSSemCreate( (OS_SEM *)&g_WifiBlueOrder,"gp_WifiBlueOrder",0,(OS_ERR *)&err );                                          /* 创建确认指令 */	
//	OSMutexCreate( (OS_MUTEX *)&g_Touchsem,"gp_Touchsem",(OS_ERR *)&err );                                                  /* 创建触摸屏信号量 */
//	OSMutexCreate( (OS_MUTEX *)&g_MotorReset,"gp_MotorReset",(OS_ERR *)&err );                                              /* 创建电机信号量 */	
//	OSMutexCreate( gp_WifiDataReceive,"gp_WifiDataReceive",(OS_ERR *)&err );                                                /* 创建WIFIData*/
#else                                                                                                                      
	OSSemCreate( gp_Touchsem,"gp_Touchsem",0,(OS_ERR *)&err );                                                              /* 创建触摸屏信号量 */	
	OSSemCreate( gp_ReadIDsem,"gp_ReadIDsem",0,(OS_ERR *)&err );                                                            /* 创建读ID卡信号量 */
	OSSemCreate( gp_Historysem,"gp_Historysem",1,(OS_ERR *)&err );                                                          /* 创建读历史信号量 */
	OSSemCreate( gp_Acquisition,"gp_Acquisition",1,(OS_ERR *)&err );                                                        /* 创建采集信号量 */
	OSSemCreate( gp_TjcTouchsem,"gp_TjcTouchsem",0,(OS_ERR *)&err );                                                        /* 创建第二代屏幕信号量 OSMutexCreate */
	OSSemCreate( gp_LogInsem,"gp_LogInsem",0,(OS_ERR *)&err );                                                              /* 创建登录信号量 */
	OSSemCreate( gp_ResetLogInsem,"gp_ResetLogInsem",0,(OS_ERR *)&err );                                                    /* 创建再次登录信号量 */
	OSSemCreate( gp_MotorReset,"gp_MotorReset",0,(OS_ERR *)&err );                                                          /* 创建电机信号量 */
	OSSemCreate( gp_PowerOnsem,"gp_PowerOnsem",0,(OS_ERR *)&err );                                                          /* 创建开机信号量 */
	OSSemCreate( gp_ForceExit,"gp_ForceExit",0,(OS_ERR *)&err );                                                            /* 创建强制退出 */
    OSSemCreate( gp_WarnCencle,"gp_WarnCencle",0,(OS_ERR *)&err );                                                          /* 创建警告 */ 
	OSSemCreate( gp_GetPageId,"gp_GetPageId",0,(OS_ERR *)&err );                                                            /* 创建获取页面id */
	OSSemCreate( gp_WifiReceive,"gp_WifiReceive",0,(OS_ERR *)&err );                                                        /* 创建WIFI*/         
	//OSSemCreate( gp_WifiDataReceive,"gp_WifiDataReceive",0,(OS_ERR *)&err );                                              /* 创建WIFIData*/
#endif	                                                                             
	OSQCreate( (OS_Q *)&g_TouchMsgQue,"gp_TouchMsgQue",(OS_MSG_QTY )N_MSG_SIZE,(OS_ERR *)&err );                            /*创建一个消息*/
	OSQCreate( (OS_Q *)&g_TouchSpcMsgQue,"gp_TouchSpcMsgQue",(OS_MSG_QTY )N_MSG_SPC_SIZE,(OS_ERR *)&err );                  /*创建一个消息*/
	OSQCreate( (OS_Q *)&g_ShutDownMsgQue,"gp_ShutDownMsgQue",(OS_MSG_QTY )N_SHUT_MSG_SIZE,(OS_ERR *)&err );                 /*创建一个消息*/																													            		
	
	return true;
}
