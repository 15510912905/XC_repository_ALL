#include "Func_MA1100_User_Interface.h"

/*  */
void UpdateUI( uint8_t* page_Id )
{	
//	OS_ERR err = OS_ERR_NONE;
	
	switch( *page_Id )
	{
		case INIT_PAGE:
#if DEBUH_UART1		
			myprintf( "INIT_PAGE \r\n");                                                /*初始化页*/
#endif                                                                               
			break;                                                                   
		case KEY_PAGE:                                                               
#if DEBUH_UART1		                                                                 
			myprintf( "ErrOrKEY_PAGE \r\n");                                            /*按键或错误*/
#endif                                                                               
			break;                                                                   
																			         
		case MAIN_PAGE:                                                              
#if DEBUH_UART1		                                                                 
			myprintf( "MAIN_PAGE\r\n");                                                
#endif                                                                               
			MotorLock( MOTOR_UNLOCK );                                                /* 电机不上锁 */	
																			         
			break;	                                                                 
																			         
		case TEST2_PAGE:                                                             
#if DEBUH_UART1		                                                                 
			myprintf( "TEST2_PAGE\r\n");                                               
#endif	                                                                             
			uTestInformation();                                                       /* 显示测试信息 */
																			         
			break;                                                                   
																			         
		case HISTORY1_PAGE:                                                          
#if DEBUH_UART1		                                                                 
			myprintf( "HISTORY1_PAGE\r\n");                                            
#endif			                                                                     
			uDisplayHistoryData( HISTORY1_PAGE );                                     /* 显示历史页 */
		
			break;
		
		case QUICK_RESULT_PAGE:
#if DEBUH_UART1		
			myprintf( "QUICK_RESULT_PAGE\r\n");
#endif					
			uAcquisitionSystem( QUICK_RESULT_PAGE );                                  /* 快速测试 采集流程控制 *///OSTimeDlyHMSM(0, 0, 1, 0 );
		
			break;	
		
		case STANDARD_RESULT_PAGE:
#if DEBUH_UART1		
			myprintf( "STANDARD_RESULT_PAGE\r\n");
#endif					
			uAcquisitionSystem( STANDARD_RESULT_PAGE );                                /* 标准测试 采集流程控制 */	                  	
		
			break;
			
		case ID_PAGE:
#if DEBUH_UART1		
			myprintf( "ID_PAGE\r\n");
#endif	
//			OSSemPost( (OS_SEM *)&g_ReadIDsem,OS_OPT_POST_NO_SCHED,&err );         /* 读ID卡信号量 */	
		
			break;
		
		case SET2_PAGE:
#if DEBUH_UART1		
			myprintf( "SET2_PAGE\r\n");                                            /* 设置页面初始化 */
#endif	
			uSetPageInit();
		
			break;
		
		case SET3_PAGE:
#if DEBUH_UART1		
			myprintf( "SET3_PAGE\r\n");                                            /* 预留 */
#endif
		
			break;
		
		case SET4_PAGE:	
#if DEBUH_UART1		
			myprintf( "SET4_PAGE\r\n");
#endif				
			uSetTimeEditInit();                                                        /* 设置时间页面初始化 */
				
			break;
		
		case CONFIG_PAGE:	
#if DEBUH_UART1		
			myprintf( "CONFIG_PAGE\r\n");
#endif				
			uSetInputConfigEditInit( gp_stuConfigFile );                              /* 设置用户输入配置初始化 */
				
			break;		
		
		case BUTTON_VALUE_ADBAR_DIS:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_ADBAR_DIS\r\n");
#endif	
			uGetFluorescenceBarValue();                                              /* 得到荧光最大值和条码第一个波谷值 */
		
		break;
		
		case BUTTON_VALUE_FORCE_ASS:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_FORCE_ASS\r\n");
#endif				
			uForceAssociateDensity();                                                 /* 强制关联浓度数据 */
		
			break;
		
		case BUTTON_VALUE_DIS_VER:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_DIS_VER \r\n");
#endif	
			uDisplayVersion();                                                          /* 显示版本号 */
			
			break;
				
		case BUTTON_VALUE_POST_PAGE:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_POST_PAGE\r\n");                                  /* 页面ID获取错误 */    
			myprintf( "Error postpage \r\n");                                          
#endif	

			break;
		
		case BUTTON_VALUE_SYSTEM_INIT:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_SYSTEM_INIT\r\n");
#endif	
			uSetSystemEditInit( gp_stuConfigFile );                                  /* 显示系统设置页 */                    
		
			break;
		
		case BUTTON_VALUE_WIFI_SCAN_AP:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_WIFI_SCAN_AP\r\n");
#endif	
			uWifiScanAll();                                                         /* 扫描WIFI热点 */                    
		
			break;
		
		case BUTTON_VALUE_BLUE_SCAN_AP:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BLUE_SCAN_AP\r\n");
#endif	
			uClassicBluetoothScan();                                                        /* 蓝牙扫描 */                    
		
			break;
		
		case BUTTON_VALUE_WIFI_PAS:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_WIFI_PAS\r\n");
#endif	
//			uWifiConfig();                                                              /* 配置WIFI */
			uWifiConfigSSID();                                                          /* 只配置WIFI网络 不配置服务器 */
		
			break;
		
		case BUTTON_VALUE_BLUE_A_MAC:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BLUE_A_MAC\r\n");
#endif
			uBluetoothMacAddrConnet( *(g_MacAddr+0) );                                 /* 蓝牙连接 */
		
			break;
		
		case BUTTON_VALUE_BLUE_B_MAC:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BLUE_B_MAC\r\n");
#endif
			uBluetoothMacAddrConnet( *(g_MacAddr+1) );                             /* 蓝牙连接 */
		
			break;
		
		case BUTTON_VALUE_BLUE_C_MAC:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BLUE_C_MAC\r\n");
#endif
			uBluetoothMacAddrConnet( *(g_MacAddr+2) );                            /* 蓝牙连接 */
		
			break;
		
		case BUTTON_VALUE_BLUE_D_MAC:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BLUE_D_MAC\r\n");
#endif
			uBluetoothMacAddrConnet( *(g_MacAddr+3) );                          /* 蓝牙连接 */
		
			break;
		
		case BUTTON_VALUE_BLUE_E_MAC:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BLUE_E_MAC\r\n");
#endif
			uBluetoothMacAddrConnet( *(g_MacAddr+4) );                        /* 蓝牙连接 */
		
			break;
		
		case BUTTON_VALUE_BLUE_F_MAC:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BLUE_F_MAC\r\n");
#endif
			uBluetoothMacAddrConnet( *(g_MacAddr+5) );                      /* 蓝牙连接 */
		
			break;
		
		case BUTTON_VALUE_BLUE_G_MAC:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BLUE_G_MAC\r\n");
#endif
			uBluetoothMacAddrConnet( *(g_MacAddr+6) );                     /* 蓝牙连接 */
		
			break;
		
		case BUTTON_VALUE_BLUE_H_MAC:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BLUE_H_MAC\r\n");
#endif
			uBluetoothMacAddrConnet( *(g_MacAddr+7) );                      /* 蓝牙连接 */
		
			break;
		
		case BUTTON_VALUE_SERVER_CONF:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_SERVER_CONF\r\n");
#endif	
			uWifiConfigServer();                                          /* WIFI 配置服务器 */
		
			break;
		
		case BUTTON_VALUE_AUTO_TEST:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_AUTO_TEST\r\n");
#endif				
			uAutoQuckTest();                                                        /* 执行自动测试次数 */
		 
			break;
		
		case BUTTON_VALUE_WARN_CANCEL:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_WARN_CANCEL\r\n");
#endif		
			uWarnCancel();                                                          /* 发送取消警告信号量 */
		
			break;
		
		case BUTTON_VALUE_SIDO_ROOT:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_SIDO_ROOT\r\n");
#endif		
			uInitSidoRoot();                                                         /* 清空用户密码值 */
		
			break;
		
		case BUTTON_VALUE_LED_CTRL:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_LED_CTRL\r\n");
#endif
			uOpenCloseLed();                                                         /* 控制LED灯 */
		
			break;
		
		case BUTTON_VALUE_SWITCH_ONOFF:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_SWITCH_ONOFF \r\n");
#endif
			uConfigMicSwitch();                                                         /* 控制微动开关 */
		
			break;
		
		case BUTTON_VALUE_PARAMET_INIT:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_PARAMET_INIT\r\n");
#endif
			uDisParameterInit();                                                     /* Instrument 初始化显示 */  
		
			break;
		
		case BUTTON_VALUE_INSTR_INIT:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_INSTR_INIT\r\n");
#endif
			uDisInstrumentInit();                                                    /* Instrument 初始化显示 */  
		
			break;

		case BUTTON_VALUE_REFERENCE_DOWN:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_REFERENCE_DOWN\r\n");
#endif
			uDisplayReferenceData(BUTTON_VALUE_REFERENCE_DOWN);                            /* 用户参考值 显示 */  
		
			break;
		
		case BUTTON_VALUE_REFERENCE_UP:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_REFERENCE_UP\r\n");
#endif
			uDisplayReferenceData(BUTTON_VALUE_REFERENCE_UP);                            /* 用户参考值 显示 */  
		
			break;
		
		case BUTTON_VALUE_REFERENCE_DIS:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_REFERENCE_DIS\r\n");
#endif
			uDisplayReferenceData(BUTTON_VALUE_REFERENCE_DIS);                            /* 用户参考值 显示 */  
		
			break;
		
		case BUTTON_VALUE_USER_INFO_DIS:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_USER_INFO_DIS\r\n");
#endif		
			uDisInputUserInfoInit( &g_stuUserMoreInfo );                            /* 显示用户信息初始化 */
		
			break;
		
		case BUTTON_VALUE_MORE_CLEAR:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_MORE_CLEAR\r\n");
#endif		
			uClearInputUserInfo();                                                 /* 清除用户信息 */
		
			break;
		
		case BUTTON_VALUE_SERVER_CLEAR:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_SERVER_CLEAR\r\n");
#endif		
			//uClearInputServer();                                                 /* 清除服务器 */
		
			break;
		
		case BUTTON_VALUE_TIME_CLEAR:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_TIME_CLEAR\r\n");
#endif		
			uClearInputTimeValue();                                                 /* 清除设置时间 */
		
			break;
		
		case BUTTON_VALUE_SYSTEM_CLEAR:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_SYSTEM_CLEAR\r\n");
#endif		
			uClearInputSystem();                                                  /* 清除系统信息 */

			break;
		
		case BUTTON_VALUE_REF_CLEAR:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_REF_CLEAR\r\n");
#endif		
			uClearInputReference();                                                 /* 清除参考范围 */
		
			break;
		
		case BUTTON_VALUE_BUZZER:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BUZZER\r\n");
#endif	
			uConfigBuzzerFile();                                                    /* 蜂鸣器设置 */
		
			break;
		
		case BUTTON_VALUE_SCAN_BAR:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_SCAN_BAR\r\n");
#endif	
			uConfigScanBarFile();                                                   /* 扫描条码开关 */
		
			break;
		
		case BUTTON_VALUE_PRINT_AD:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_PRINT_AD\r\n");
#endif	
			uConfigPrintADFile();                                                  /* AD值开关配置 */
		
			break;
		
		case BUTTON_VALUE_PRINT_BAR:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_PRINT_BAR\r\n");
#endif	
			uConfigPrintBarFile();                                                /* 条码值开关配置 */
		
			break;
		
		case BUTTON_VALUE_WIFI_ONOFF:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_WIFI_ONOFF\r\n");
#endif	
			uConfigWifiBluetoothFile();                                                   /* WIFI开关配置 */
		
			break;
		
		case BUTTON_VALUE_PRINT_1BAR:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_PRINT_1BAR\r\n");
#endif	
			uConfigPrint1BarFile();                                              /* 条码值开关配置 */
		
			break;
		
		case BUTTON_VALUE_IDCARD_DOWN: 
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_IDCARD_DOWN\r\n");
#endif	
			uIdDisplayUpDown( BUTTON_VALUE_IDCARD_DOWN );                        /* ID下翻 */
		
			break;
		
		case BUTTON_VALUE_IDCARD_UP: 
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_IDCARD_UP\r\n");
#endif	
			uIdDisplayUpDown( BUTTON_VALUE_IDCARD_UP );                         /* ID上翻 */
		
			break;
		
		case BUTTON_VALUE_IDCARD_INFO: 
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_IDCARD_INFO\r\n");
#endif	
			uIdDisplayUpDown( BUTTON_VALUE_IDCARD_INFO );                      /* 默认显示读的第一张卡 */
		
			break;
				
		case BUTTON_VALUE_MORE_INFO:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_MORE_INFO\r\n");
#endif				
			uSpecialMoreInformation();                                        /* 设置特殊用户信息 */
		
			break;
		
		case BUTTON_VALUE_COEFF:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_COEFF\r\n");
#endif				
			uSetCoeffValue( gp_stuEditInputConfig->fstuCoeff,UI_Y_PROMPT );               /* 设置调试系数 */
		
			break;
		
		case BUTTON_VALUE_LANBO_BASE:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_LANBO_BASE\r\n");
#endif	
			uSetLanboRefValue( gp_stuEditInputConfig->ustuInputLanRef,UI_Y_PROMPT );                /* 设置蓝博基数 */
		
			break;				
		
		case BUTTON_VALUE_SN_STR:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_SN_STR\r\n");
#endif	
			uSetSNStr( gp_stuEditInputConfig->ustuSNStrNum,strlen((const char *)gp_stuEditInputConfig->ustuSNStrNum),UI_Y_PROMPT );     /* 设置蓝博基数 */              
		
			break;	
			
		case BUTTON_VALUE_B1REFERENCE:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_B1REFERENCE\r\n");
#endif				
			uSetRerference( BUTTON_VALUE_B1REFERENCE );                      /* 设置全部参考值1 */
		
			break;
			
		case BUTTON_VALUE_B2REFERENCE:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_B2REFERENCE\r\n");
#endif				
			uSetRerference( BUTTON_VALUE_B2REFERENCE );                      /* 设置全部参考值2  */
		
			break;
		
		case BUTTON_VALUE_B3REFERENCE:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_B3REFERENCE\r\n");
#endif				
			uSetRerference( BUTTON_VALUE_B3REFERENCE );                     /* 设置全部参考值3 */
		
			break;
			
		case BUTTON_VALUE_B4REFERENCE:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_B4REFERENCE\r\n");
#endif				
			uSetRerference( BUTTON_VALUE_B4REFERENCE );                     /* 设置全部参考值4  */
		
			break;
		
		case BUTTON_VALUE_B5REFERENCE:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_B5REFERENCE\r\n");
#endif				
			uSetRerference( BUTTON_VALUE_B5REFERENCE );                     /* 设置全部参考值5 */
		
			break;
			
		case BUTTON_VALUE_B6REFERENCE:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_B6REFERENCE\r\n");
#endif				
			uSetRerference( BUTTON_VALUE_B6REFERENCE );                     /* 设置全部参考值6  */
		
			break;
			
		case BUTTON_VALUE_REFERENCE:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_REFERENCE\r\n");
#endif				
			uSetRerference( BUTTON_VALUE_REFERENCE );                       /* 设置全部参考值 */
		
			break;
				
		case BUTTON_VALUE_REF_COVER:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_REF_COVER\r\n");
#endif		
			uStoreReferenceCover();		                                  /* 全部参考值覆盖存储 */
		
			break;
		
		case BUTTON_VALUE_OVER_ID:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_OVER_ID\r\n");
#endif		
			uTjc4832tTouchEnable( TJC_TOUCH_OFF );                                             /* 整页关闭触摸 */ 
			uStoreIDCardCover();		                                                       /* ID内容覆盖存储 */
			uTjc4832tTouchEnable( TJC_TOUCH_ON );                                              /* 整页打开触摸 */	
		
			break;
		
		case BUTTON_VALUE_NO_OVER_ID:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_NO_OVER_ID\r\n");
#endif		
			uReadStoreIdItem( g_uRecordIdCardCover );		             /* ID内容不覆盖存储,读取之前的内容 */
	 	
			break;
		
		case BUTTON_VALUE_BAR_ERR:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BAR_ERR\r\n");
#endif				
			uBarErrorProcess();                                            /* 条码值错误处理 */
		
			break;
		
		case BUTTON_VALUE_SPECIAL_PAS:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_SPECIAL_PAS\r\n");
#endif				
			uSpecialPasswordInit();                                        /* 特殊密码验证 */
		
			break;
		
		case BUTTON_VALUE_WHOLE:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_WHOLE\r\n");                             /* 选择全血 */
#endif	
			ChooseCoefficient( BUTTON_VALUE_WHOLE );
		
			break;
		
		case BUTTON_VALUE_SERUM:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_SERUM\r\n");                             /* 选择末梢血 */
#endif	
			ChooseCoefficient( BUTTON_VALUE_SERUM );
		
			break;
		
		case BUTTON_VALUE_S_MORE:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_S_MORE\r\n");                             /* 选择全血 */
#endif	
			ChooseCoefficient( BUTTON_VALUE_S_MORE );
		
			break;                                                         
																			  
		case BUTTON_VALUE_SHUTDOWN:                                           
#if DEBUH_UART1		                                                          
			myprintf( "BUTTON_VALUE_SHUTDOWN\r\n");                              /* 关机 */
#endif				                                                                                                            
																			  
			break;                                                            
																			  
		case BUTTON_VALUE_ALL_CIG:                                            
#if DEBUH_UART1		                                                          
			myprintf( "BUTTON_VALUE_ALL_CIG\r\n");                               /* 校准页所有配置一起设置 */
#endif				
			uAllConfigSet( gp_stuEditInputConfig );
		
			break;
		
		case BUTTON_VALUE_SYSTEM_CIG:                                            
#if DEBUH_UART1		                                                          
			myprintf( "BUTTON_VALUE_SYSTEM_CIG\r\n");                               /* 系统设置页所有配置一起设置 */
#endif				
			uSystemAllConfigSet( gp_stuEditInputConfig );
		
			break;
		
		case BUTTON_VALUE_P_TITLES:                                            
#if DEBUH_UART1		                                                          
			myprintf( "BUTTON_VALUE_P_TITLES\r\n");                               /* 单独设置打印抬头 */
#endif				
			uSetPrintTitles(g_uInputPrintTitles,strlen((const char *)g_uInputPrintTitles),UI_Y_PROMPT);
		
			break;
		
		case BUTTON_VALUE_AUTO_TIME:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_AUTO_TIME\r\n");                                         
#endif	
			uAutoShutdownSet( gp_stuEditInputConfig->ustuAutoTime,UI_Y_PROMPT );                          /* 配置自动关机 */
		
			break;
		
		case BUTTON_VALUE_BAROFFSET:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BAROFFSET\r\n");                                                        
#endif		
			uSampleBarOffsetSet( gp_stuEditInputConfig->ustuBarOffset,UI_Y_PROMPT );                      /* 配置条码偏移 */
		
			break;
				
		case BUTTON_VALUE_OFFSET:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_OFFSET\r\n");
#endif		
			uSampleOffsetSet( gp_stuEditInputConfig->ustuOffset,UI_Y_PROMPT );                           /* 配置偏移量 */
		
			break;
		
		case BUTTON_VALUE_GAIN:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_GAIN\r\n");                                                            
#endif		
			uMax5402GainInitSet( gp_stuEditInputConfig->ustuGain,UI_Y_PROMPT );                          /* 配置增益 */
		
			break;	
		
		case BUTTON_VALUE_PRINTF:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_PRINTF\r\n");
#endif				
			uConfigPrintfFile();                                                                        /* 更改打印配置设置 */
				
			break;
		
		case BUTTON_VALUE_SLEEP:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_SLEEP\r\n");
#endif									
		
			break;	
	
		case BUTTON_VALUE_YEARS:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_YEARS\r\n");
#endif		
			uConfigTimeYears();                                                                       /* 只设置年 */
														                                             
			break;                                                                                   
														                                             
		case BUTTON_VALUE_MONTH:                                                                     
#if DEBUH_UART1		                                                                                 
			myprintf( "BUTTON_VALUE_MONTH\r\n");                                                       
#endif		                                                                                         
			uConfigTimeMonth();                                                                         /* 只设置月 */
														                                             
			break;                                                                                   
														                                             
		case BUTTON_VALUE_DAY:                                                                       
#if DEBUH_UART1		                                                                                 
			myprintf( "BUTTON_VALUE_DAY\r\n");                                                         
#endif		                                                                                         
			uConfigTimeData();                                                                        /* 只设置日 */
														                                             
			break;                                                                                   
														                                             
		case BUTTON_VALUE_HOURS:                                                                     
#if DEBUH_UART1		                                                                                 
			myprintf( "BUTTON_VALUE_HOURS\r\n");                                                       
#endif		                                                                                         
			uConfigTimeHour();                                                                        /* 只设置时 */
														                                             
			break;                                                                                   
														                                             
		case BUTTON_VALUE_MINUTES:                                                                   
#if DEBUH_UART1		                                                                                 
			myprintf( "BUTTON_VALUE_MINUTES\r\n");                                                     
#endif		                                                                                         
			uConfigTimeMinutes();                                                                     /* 只设置分 */
														                                             
			break;                                                                                   
														                                             
		case BUTTON_VALUE_TIME:                                                                      /* 确认设置时间 */
#if DEBUH_UART1		                                                                                 
			myprintf( "BUTTON_VALUE_TIME\r\n");                                                        
#endif	                                                                                             
			uConfigTime();                                                                           /* 配置时间和日历 */
														                                             
			break;                                                                                   
														                                             
		case BUTTON_VALUE_FACTORY:	                                                                 
#if DEBUH_UART1		                                                                                 
			myprintf( "BUTTON_VALUE_FACTORY\r\n");                                                     
#endif				                                                                                 
			uFactoryReset();                                                                           /* 恢复出厂设置 */
														                                             
			break;                                                                                   
														                                             
		case BUTTON_VALUE_PROM_FACTORY:	                                                             
#if DEBUH_UART1		                                                                                 
			myprintf( "BUTTON_VALUE_PROM_FACTORY\r\n");                                                
#endif			
			if( EN_ON==gp_stuConfigFile->uCutEnCu ){
				uPrompterWarn( (uint8_t *)"Reset?" );                                                      /* 提示警告 恢复出厂设置 */
			}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
				uPrompterWarn( (uint8_t *)"复位?" ); 
			}else{
				uPrompterWarn( (uint8_t *)"Invalid" ); 
			}		
				
			break;
		
		case BUTTON_VALUE_HISTORY_CLEAR:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_HISTORY_CLEAR\r\n");
#endif				
			uHistoryClear( UI_Y_PROMPT );                                                            /* 清除历史数据 */
																	                              
			break;                                                                                
																	                              
		case BUTTON_VALUE_PROM_CLEHIS:	                                                          
#if DEBUH_UART1		                                                                              
			myprintf( "BUTTON_VALUE_PROM_CLEHIS\r\n");                                              
#endif		
			if( EN_ON==gp_stuConfigFile->uCutEnCu ){
				uPrompterWarn( (uint8_t *)"Clear History?" );                                             /* 提示警告 清除历史数据 */
			}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
				uPrompterWarn( (uint8_t *)"清除?" );                                           
			}else{
				uPrompterWarn( (uint8_t *)"Invalid" ); 
			}			
				
			break;
		
		case BUTTON_VALUE_MOTOR_DOWN:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_MOTOR_DOWN\r\n");
#endif				
			MotorBackward();                                                                      /* 电机后退 */
															                                      
			break;                                                                                
															                                      
		case BUTTON_VALUE_MOTOR_UP:	                                                              
#if DEBUH_UART1		                                                                              
			myprintf( "BUTTON_VALUE_MOTOR_UP\r\n");                                                 
#endif			                                                                                  
			MotorForward();                                                                       /* 电机前进 */
															                                      
			break;
		
		case BUTTON_VALUE_LIS_AFFIRM:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_LIS_AFFIRM\r\n");
#endif		
			uTjc4832tTouchEnable( TJC_TOUCH_OFF );                                             /* 整页关闭触摸 */ 
			uLisSendHistoryPage( g_uRecordHistoryPage,0 );                                     /* LIS网络数据上传 */
			uTjc4832tTouchEnable( TJC_TOUCH_ON );                                              /* 整页打开触摸 */
		
			break;	
				
		case BUTTON_VALUE_LIS_CANCLE:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_LIS_CANCLE\r\n");
#endif				
			uDisplayHistoryDataSpecifiedPage( g_uRecordHistoryPage );	                      /* 取消上传 */
				
			break;	
		
		case BUTTON_VALUE_LIS_UPLOAD:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_LIS_UPLOAD\r\n");
#endif			
			uTjc4832tTouchEnable( TJC_TOUCH_OFF );                                             /* 整页关闭触摸 */ 
			uLisSendHistoryPage( g_uRecordHistoryPage,1 );                                     /* LIS网络数据上传 */
			uTjc4832tTouchEnable( TJC_TOUCH_ON );                                              /* 整页打开触摸 */
				
			break;		
															                                   	
		case BUTTON_VALUE_HISTORY_PRINT:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_HISTORY_PRINT\r\n");
#endif			
			uTjc4832tTouchEnable( TJC_TOUCH_OFF );                                               /* 整页关闭触摸 */ 
			uDisplayHistoryData( BUTTON_VALUE_HISTORY_PRINT );                                   /* 打印现在显示的历史数据 */			
			uTjc4832tTouchEnable( TJC_TOUCH_ON );                                                /* 整页打开触摸 */
																                                
			break;		                                                                        
																                                
		case BUTTON_VALUE_HISTORY_DOWN:                                                         
#if DEBUH_UART1		                                                                            
			myprintf( "BUTTON_VALUE_HISTORY_DOWN\r\n");                                           
#endif			                                                                                
			uDisplayHistoryData( BUTTON_VALUE_HISTORY_DOWN );                                    /* 下翻显示历史数据 */		
																                                
			break;                                                                              
																                                
		case BUTTON_VALUE_HISTORY_UP:                                                           
#if DEBUH_UART1		                                                                            
			myprintf( "BUTTON_VALUE_HISTORY_UP\r\n");                                             
#endif			                                                                                
			uDisplayHistoryData( BUTTON_VALUE_HISTORY_UP );                                      /* 上翻显示历史数据 */		
			
			break;
		
		case BUTTON_VALUE_RESET_MOTOR:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_RESET_MOTOR\r\n");
#endif		
			uResetMotorInteriorStauts( UI_Y_PROMPT );          /* 传感器 复位电机到初始位置 */  //ResetMotor();          /* 步数 复位电机到初始位置 */						
			
			break;
		
		case BUTTON_VALUE_REGISTER:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_REGISTER\r\n");
#endif					
			uLoginBottonValue();                                                             /*释放信号量 注册确认 */  
			
			break;
		
		case BUTTON_VALUE_LOGIN:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_LOGIN \r\n");
#endif		
			uLoginBottonValue();                                                             /*释放信号量 登录确认 */	      		
			
			break;	
		
		case BUTTON_VALUE_TJC_START:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_TJC_START\r\n");                                         /* 屏幕启动成功 */
#endif				
			uResetLoginBottonValue();                                                        /*释放信号量 再次登录 */
													                                         
			break;                                                                           
													                                         
		case BUTTON_VALUE_RELOGIN:                                                           
#if DEBUH_UART1		                                                                         
			myprintf( "BUTTON_VALUE_RELOGIN \r\n");                                          
#endif					                                                                     
			uResetLoginBottonValue();                                                        /*释放信号量 再次登录 */
			
			break;	
		
//		case BUTTON_VALUE_VARI_INVALID:
//#if DEBUH_UART1		
//			myprintf( "BUTTON_VALUE_VARI_INVALID\r\n");                          /* 无效变量名 */
//#endif	                                                                      
//#if	TJC_SCE_WARN_OFF                                                          
//			vForceWarn();                                                     
//#endif		                                                                  
//			break;   		
//		case BUTTON_VALUE_AUTO_FEXIT:
//#if DEBUH_UART1		
//			myprintf( "BUTTON_VALUE_AUTO_FEXIT \r\n");
//#endif				
//		
//			break;
//		case BUTTON_VALUE_TEST_FEXIT:
//#if DEBUH_UART1		
//			myprintf( "BUTTON_VALUE_TEST_FEXIT \r\n");                       /* 标准测试强制退出 */
//#endif							
//			
//			break;	
//		case BUTTON_VALUE_1DENSITY:                                                               
//#if DEBUH_UART1		                                                                              
//			myprintf( "BUTTON_VALUE_1DENSITY\r\n");                                                 
//#endif	                                                                                          
//			uDensityAffirmPage();                                                                 /* */
//															                                      
//			break;                                                                                
//															                                      
//		case BUTTON_VALUE_2DENSITY:                                                               
//#if DEBUH_UART1		                                                                              
//			myprintf( "BUTTON_VALUE_2DENSITY\r\n");                                                 
//#endif	                                                                                          
//			uDensityAffirmPage();                                                                 /* 确认浓度返回页面 */
//			
//			break;
		
		default:		
			
			break;
	}
}

/*  */
void UpdateSpcUI( uint8_t* page_Id )
{	
//	OS_ERR err = OS_ERR_NONE;
	
	switch( *page_Id )
	{
//		case SPC_INIT_PAGE:
//#if DEBUH_UART1		
//			myprintf( "SPC_INIT_PAGE \r\n");                                                /*初始化页*/
//#endif                                                                               
//			break;   
		
		case SPC_BUTTON_VALUE_SHUTDOWN:                                           
#if DEBUH_UART1		                                                          
			myprintf( "SPC_BUTTON_VALUE_SHUTDOWN\r\n");                                     /* 关机 */
#endif				                                                          
			vShutDown();                                                    
																			  
			break; 					
					
		default:	
			
			break;
	}
}

void vUpdateUISend( uint8_t uTempOrder)
{
	OS_ERR uTempErr = OS_ERR_NONE;
	OS_ERR err = OS_ERR_NONE;
	uint8_t* l_puAnalyzeOrder = 0;
	
	if( 0!=uTempOrder ){				
		l_puAnalyzeOrder = (uint8_t *)calloc( 1,sizeof(uint8_t) );                           /* 申请内存 */
		if( NULL!=l_puAnalyzeOrder ){
			(*l_puAnalyzeOrder) = uTempOrder;			
			if( (*l_puAnalyzeOrder)<TJC_DEMARCATION_POINT ){							
				OSQPost( (OS_Q *)&g_TouchMsgQue,(void *)(l_puAnalyzeOrder),(OS_MSG_SIZE )1,OS_OPT_POST_FIFO+ OS_OPT_POST_NO_SCHED,&uTempErr );	
				if( OS_ERR_NONE!=uTempErr ) {  /*发送一个消息*/
					if( NULL!=l_puAnalyzeOrder ){
						free( l_puAnalyzeOrder );
					}
#if DEBUH_UART1
					myprintf( "uTempPostErr1:%d ",uTempErr );
#endif	
				}else{
					OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	 /* 延时10ms   */
				}
			}else{
				OSQPost( (OS_Q *)&g_TouchSpcMsgQue,(void *)(l_puAnalyzeOrder),(OS_MSG_SIZE )1,OS_OPT_POST_FIFO+ OS_OPT_POST_NO_SCHED,&uTempErr );
				if( OS_ERR_NONE!=uTempErr ) {  /*发送一个消息*/
					if( NULL!=l_puAnalyzeOrder ){
						free( l_puAnalyzeOrder );
					}
#if DEBUH_UART1
					myprintf( "uTempPostErr2:%d ",uTempErr );
#endif	
				}else{
					OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	 /* 延时10ms   */
				}
			}					
		}else{
#if DEBUH_UART1
			myprintf( "myMallocErr\r\n" );
#endif	
		}				
	}
}
