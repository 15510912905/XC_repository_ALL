#include "Func_MA1100_User_Interface.h"

/*  */
void UpdateUI( uint8_t* page_Id )
{	
//	OS_ERR err = OS_ERR_NONE;
	
	switch( *page_Id )
	{
		case INIT_PAGE:
#if DEBUH_UART1		
			myprintf( "INIT_PAGE \r\n");                                                /*��ʼ��ҳ*/
#endif                                                                               
			break;                                                                   
		case KEY_PAGE:                                                               
#if DEBUH_UART1		                                                                 
			myprintf( "ErrOrKEY_PAGE \r\n");                                            /*���������*/
#endif                                                                               
			break;                                                                   
																			         
		case MAIN_PAGE:                                                              
#if DEBUH_UART1		                                                                 
			myprintf( "MAIN_PAGE\r\n");                                                
#endif                                                                               
			MotorLock( MOTOR_UNLOCK );                                                /* ��������� */	
																			         
			break;	                                                                 
																			         
		case TEST2_PAGE:                                                             
#if DEBUH_UART1		                                                                 
			myprintf( "TEST2_PAGE\r\n");                                               
#endif	                                                                             
			uTestInformation();                                                       /* ��ʾ������Ϣ */
																			         
			break;                                                                   
																			         
		case HISTORY1_PAGE:                                                          
#if DEBUH_UART1		                                                                 
			myprintf( "HISTORY1_PAGE\r\n");                                            
#endif			                                                                     
			uDisplayHistoryData( HISTORY1_PAGE );                                     /* ��ʾ��ʷҳ */
		
			break;
		
		case QUICK_RESULT_PAGE:
#if DEBUH_UART1		
			myprintf( "QUICK_RESULT_PAGE\r\n");
#endif					
			uAcquisitionSystem( QUICK_RESULT_PAGE );                                  /* ���ٲ��� �ɼ����̿��� *///OSTimeDlyHMSM(0, 0, 1, 0 );
		
			break;	
		
		case STANDARD_RESULT_PAGE:
#if DEBUH_UART1		
			myprintf( "STANDARD_RESULT_PAGE\r\n");
#endif					
			uAcquisitionSystem( STANDARD_RESULT_PAGE );                                /* ��׼���� �ɼ����̿��� */	                  	
		
			break;
			
		case ID_PAGE:
#if DEBUH_UART1		
			myprintf( "ID_PAGE\r\n");
#endif	
//			OSSemPost( (OS_SEM *)&g_ReadIDsem,OS_OPT_POST_NO_SCHED,&err );         /* ��ID���ź��� */	
		
			break;
		
		case SET2_PAGE:
#if DEBUH_UART1		
			myprintf( "SET2_PAGE\r\n");                                            /* ����ҳ���ʼ�� */
#endif	
			uSetPageInit();
		
			break;
		
		case SET3_PAGE:
#if DEBUH_UART1		
			myprintf( "SET3_PAGE\r\n");                                            /* Ԥ�� */
#endif
		
			break;
		
		case SET4_PAGE:	
#if DEBUH_UART1		
			myprintf( "SET4_PAGE\r\n");
#endif				
			uSetTimeEditInit();                                                        /* ����ʱ��ҳ���ʼ�� */
				
			break;
		
		case CONFIG_PAGE:	
#if DEBUH_UART1		
			myprintf( "CONFIG_PAGE\r\n");
#endif				
			uSetInputConfigEditInit( gp_stuConfigFile );                              /* �����û��������ó�ʼ�� */
				
			break;		
		
		case BUTTON_VALUE_ADBAR_DIS:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_ADBAR_DIS\r\n");
#endif	
			uGetFluorescenceBarValue();                                              /* �õ�ӫ�����ֵ�������һ������ֵ */
		
		break;
		
		case BUTTON_VALUE_FORCE_ASS:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_FORCE_ASS\r\n");
#endif				
			uForceAssociateDensity();                                                 /* ǿ�ƹ���Ũ������ */
		
			break;
		
		case BUTTON_VALUE_DIS_VER:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_DIS_VER \r\n");
#endif	
			uDisplayVersion();                                                          /* ��ʾ�汾�� */
			
			break;
				
		case BUTTON_VALUE_POST_PAGE:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_POST_PAGE\r\n");                                  /* ҳ��ID��ȡ���� */    
			myprintf( "Error postpage \r\n");                                          
#endif	

			break;
		
		case BUTTON_VALUE_SYSTEM_INIT:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_SYSTEM_INIT\r\n");
#endif	
			uSetSystemEditInit( gp_stuConfigFile );                                  /* ��ʾϵͳ����ҳ */                    
		
			break;
		
		case BUTTON_VALUE_WIFI_SCAN_AP:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_WIFI_SCAN_AP\r\n");
#endif	
			uWifiScanAll();                                                         /* ɨ��WIFI�ȵ� */                    
		
			break;
		
		case BUTTON_VALUE_BLUE_SCAN_AP:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BLUE_SCAN_AP\r\n");
#endif	
			uClassicBluetoothScan();                                                        /* ����ɨ�� */                    
		
			break;
		
		case BUTTON_VALUE_WIFI_PAS:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_WIFI_PAS\r\n");
#endif	
//			uWifiConfig();                                                              /* ����WIFI */
			uWifiConfigSSID();                                                          /* ֻ����WIFI���� �����÷����� */
		
			break;
		
		case BUTTON_VALUE_BLUE_A_MAC:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BLUE_A_MAC\r\n");
#endif
			uBluetoothMacAddrConnet( *(g_MacAddr+0) );                                 /* �������� */
		
			break;
		
		case BUTTON_VALUE_BLUE_B_MAC:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BLUE_B_MAC\r\n");
#endif
			uBluetoothMacAddrConnet( *(g_MacAddr+1) );                             /* �������� */
		
			break;
		
		case BUTTON_VALUE_BLUE_C_MAC:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BLUE_C_MAC\r\n");
#endif
			uBluetoothMacAddrConnet( *(g_MacAddr+2) );                            /* �������� */
		
			break;
		
		case BUTTON_VALUE_BLUE_D_MAC:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BLUE_D_MAC\r\n");
#endif
			uBluetoothMacAddrConnet( *(g_MacAddr+3) );                          /* �������� */
		
			break;
		
		case BUTTON_VALUE_BLUE_E_MAC:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BLUE_E_MAC\r\n");
#endif
			uBluetoothMacAddrConnet( *(g_MacAddr+4) );                        /* �������� */
		
			break;
		
		case BUTTON_VALUE_BLUE_F_MAC:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BLUE_F_MAC\r\n");
#endif
			uBluetoothMacAddrConnet( *(g_MacAddr+5) );                      /* �������� */
		
			break;
		
		case BUTTON_VALUE_BLUE_G_MAC:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BLUE_G_MAC\r\n");
#endif
			uBluetoothMacAddrConnet( *(g_MacAddr+6) );                     /* �������� */
		
			break;
		
		case BUTTON_VALUE_BLUE_H_MAC:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BLUE_H_MAC\r\n");
#endif
			uBluetoothMacAddrConnet( *(g_MacAddr+7) );                      /* �������� */
		
			break;
		
		case BUTTON_VALUE_SERVER_CONF:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_SERVER_CONF\r\n");
#endif	
			uWifiConfigServer();                                          /* WIFI ���÷����� */
		
			break;
		
		case BUTTON_VALUE_AUTO_TEST:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_AUTO_TEST\r\n");
#endif				
			uAutoQuckTest();                                                        /* ִ���Զ����Դ��� */
		 
			break;
		
		case BUTTON_VALUE_WARN_CANCEL:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_WARN_CANCEL\r\n");
#endif		
			uWarnCancel();                                                          /* ����ȡ�������ź��� */
		
			break;
		
		case BUTTON_VALUE_SIDO_ROOT:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_SIDO_ROOT\r\n");
#endif		
			uInitSidoRoot();                                                         /* ����û�����ֵ */
		
			break;
		
		case BUTTON_VALUE_LED_CTRL:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_LED_CTRL\r\n");
#endif
			uOpenCloseLed();                                                         /* ����LED�� */
		
			break;
		
		case BUTTON_VALUE_SWITCH_ONOFF:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_SWITCH_ONOFF \r\n");
#endif
			uConfigMicSwitch();                                                         /* ����΢������ */
		
			break;
		
		case BUTTON_VALUE_PARAMET_INIT:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_PARAMET_INIT\r\n");
#endif
			uDisParameterInit();                                                     /* Instrument ��ʼ����ʾ */  
		
			break;
		
		case BUTTON_VALUE_INSTR_INIT:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_INSTR_INIT\r\n");
#endif
			uDisInstrumentInit();                                                    /* Instrument ��ʼ����ʾ */  
		
			break;

		case BUTTON_VALUE_REFERENCE_DOWN:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_REFERENCE_DOWN\r\n");
#endif
			uDisplayReferenceData(BUTTON_VALUE_REFERENCE_DOWN);                            /* �û��ο�ֵ ��ʾ */  
		
			break;
		
		case BUTTON_VALUE_REFERENCE_UP:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_REFERENCE_UP\r\n");
#endif
			uDisplayReferenceData(BUTTON_VALUE_REFERENCE_UP);                            /* �û��ο�ֵ ��ʾ */  
		
			break;
		
		case BUTTON_VALUE_REFERENCE_DIS:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_REFERENCE_DIS\r\n");
#endif
			uDisplayReferenceData(BUTTON_VALUE_REFERENCE_DIS);                            /* �û��ο�ֵ ��ʾ */  
		
			break;
		
		case BUTTON_VALUE_USER_INFO_DIS:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_USER_INFO_DIS\r\n");
#endif		
			uDisInputUserInfoInit( &g_stuUserMoreInfo );                            /* ��ʾ�û���Ϣ��ʼ�� */
		
			break;
		
		case BUTTON_VALUE_MORE_CLEAR:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_MORE_CLEAR\r\n");
#endif		
			uClearInputUserInfo();                                                 /* ����û���Ϣ */
		
			break;
		
		case BUTTON_VALUE_SERVER_CLEAR:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_SERVER_CLEAR\r\n");
#endif		
			//uClearInputServer();                                                 /* ��������� */
		
			break;
		
		case BUTTON_VALUE_TIME_CLEAR:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_TIME_CLEAR\r\n");
#endif		
			uClearInputTimeValue();                                                 /* �������ʱ�� */
		
			break;
		
		case BUTTON_VALUE_SYSTEM_CLEAR:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_SYSTEM_CLEAR\r\n");
#endif		
			uClearInputSystem();                                                  /* ���ϵͳ��Ϣ */

			break;
		
		case BUTTON_VALUE_REF_CLEAR:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_REF_CLEAR\r\n");
#endif		
			uClearInputReference();                                                 /* ����ο���Χ */
		
			break;
		
		case BUTTON_VALUE_BUZZER:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BUZZER\r\n");
#endif	
			uConfigBuzzerFile();                                                    /* ���������� */
		
			break;
		
		case BUTTON_VALUE_SCAN_BAR:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_SCAN_BAR\r\n");
#endif	
			uConfigScanBarFile();                                                   /* ɨ�����뿪�� */
		
			break;
		
		case BUTTON_VALUE_PRINT_AD:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_PRINT_AD\r\n");
#endif	
			uConfigPrintADFile();                                                  /* ADֵ�������� */
		
			break;
		
		case BUTTON_VALUE_PRINT_BAR:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_PRINT_BAR\r\n");
#endif	
			uConfigPrintBarFile();                                                /* ����ֵ�������� */
		
			break;
		
		case BUTTON_VALUE_WIFI_ONOFF:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_WIFI_ONOFF\r\n");
#endif	
			uConfigWifiBluetoothFile();                                                   /* WIFI�������� */
		
			break;
		
		case BUTTON_VALUE_PRINT_1BAR:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_PRINT_1BAR\r\n");
#endif	
			uConfigPrint1BarFile();                                              /* ����ֵ�������� */
		
			break;
		
		case BUTTON_VALUE_IDCARD_DOWN: 
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_IDCARD_DOWN\r\n");
#endif	
			uIdDisplayUpDown( BUTTON_VALUE_IDCARD_DOWN );                        /* ID�·� */
		
			break;
		
		case BUTTON_VALUE_IDCARD_UP: 
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_IDCARD_UP\r\n");
#endif	
			uIdDisplayUpDown( BUTTON_VALUE_IDCARD_UP );                         /* ID�Ϸ� */
		
			break;
		
		case BUTTON_VALUE_IDCARD_INFO: 
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_IDCARD_INFO\r\n");
#endif	
			uIdDisplayUpDown( BUTTON_VALUE_IDCARD_INFO );                      /* Ĭ����ʾ���ĵ�һ�ſ� */
		
			break;
				
		case BUTTON_VALUE_MORE_INFO:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_MORE_INFO\r\n");
#endif				
			uSpecialMoreInformation();                                        /* ���������û���Ϣ */
		
			break;
		
		case BUTTON_VALUE_COEFF:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_COEFF\r\n");
#endif				
			uSetCoeffValue( gp_stuEditInputConfig->fstuCoeff,UI_Y_PROMPT );               /* ���õ���ϵ�� */
		
			break;
		
		case BUTTON_VALUE_LANBO_BASE:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_LANBO_BASE\r\n");
#endif	
			uSetLanboRefValue( gp_stuEditInputConfig->ustuInputLanRef,UI_Y_PROMPT );                /* ������������ */
		
			break;				
		
		case BUTTON_VALUE_SN_STR:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_SN_STR\r\n");
#endif	
			uSetSNStr( gp_stuEditInputConfig->ustuSNStrNum,strlen((const char *)gp_stuEditInputConfig->ustuSNStrNum),UI_Y_PROMPT );     /* ������������ */              
		
			break;	
			
		case BUTTON_VALUE_B1REFERENCE:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_B1REFERENCE\r\n");
#endif				
			uSetRerference( BUTTON_VALUE_B1REFERENCE );                      /* ����ȫ���ο�ֵ1 */
		
			break;
			
		case BUTTON_VALUE_B2REFERENCE:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_B2REFERENCE\r\n");
#endif				
			uSetRerference( BUTTON_VALUE_B2REFERENCE );                      /* ����ȫ���ο�ֵ2  */
		
			break;
		
		case BUTTON_VALUE_B3REFERENCE:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_B3REFERENCE\r\n");
#endif				
			uSetRerference( BUTTON_VALUE_B3REFERENCE );                     /* ����ȫ���ο�ֵ3 */
		
			break;
			
		case BUTTON_VALUE_B4REFERENCE:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_B4REFERENCE\r\n");
#endif				
			uSetRerference( BUTTON_VALUE_B4REFERENCE );                     /* ����ȫ���ο�ֵ4  */
		
			break;
		
		case BUTTON_VALUE_B5REFERENCE:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_B5REFERENCE\r\n");
#endif				
			uSetRerference( BUTTON_VALUE_B5REFERENCE );                     /* ����ȫ���ο�ֵ5 */
		
			break;
			
		case BUTTON_VALUE_B6REFERENCE:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_B6REFERENCE\r\n");
#endif				
			uSetRerference( BUTTON_VALUE_B6REFERENCE );                     /* ����ȫ���ο�ֵ6  */
		
			break;
			
		case BUTTON_VALUE_REFERENCE:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_REFERENCE\r\n");
#endif				
			uSetRerference( BUTTON_VALUE_REFERENCE );                       /* ����ȫ���ο�ֵ */
		
			break;
				
		case BUTTON_VALUE_REF_COVER:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_REF_COVER\r\n");
#endif		
			uStoreReferenceCover();		                                  /* ȫ���ο�ֵ���Ǵ洢 */
		
			break;
		
		case BUTTON_VALUE_OVER_ID:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_OVER_ID\r\n");
#endif		
			uTjc4832tTouchEnable( TJC_TOUCH_OFF );                                             /* ��ҳ�رմ��� */ 
			uStoreIDCardCover();		                                                       /* ID���ݸ��Ǵ洢 */
			uTjc4832tTouchEnable( TJC_TOUCH_ON );                                              /* ��ҳ�򿪴��� */	
		
			break;
		
		case BUTTON_VALUE_NO_OVER_ID:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_NO_OVER_ID\r\n");
#endif		
			uReadStoreIdItem( g_uRecordIdCardCover );		             /* ID���ݲ����Ǵ洢,��ȡ֮ǰ������ */
	 	
			break;
		
		case BUTTON_VALUE_BAR_ERR:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BAR_ERR\r\n");
#endif				
			uBarErrorProcess();                                            /* ����ֵ������ */
		
			break;
		
		case BUTTON_VALUE_SPECIAL_PAS:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_SPECIAL_PAS\r\n");
#endif				
			uSpecialPasswordInit();                                        /* ����������֤ */
		
			break;
		
		case BUTTON_VALUE_WHOLE:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_WHOLE\r\n");                             /* ѡ��ȫѪ */
#endif	
			ChooseCoefficient( BUTTON_VALUE_WHOLE );
		
			break;
		
		case BUTTON_VALUE_SERUM:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_SERUM\r\n");                             /* ѡ��ĩ��Ѫ */
#endif	
			ChooseCoefficient( BUTTON_VALUE_SERUM );
		
			break;
		
		case BUTTON_VALUE_S_MORE:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_S_MORE\r\n");                             /* ѡ��ȫѪ */
#endif	
			ChooseCoefficient( BUTTON_VALUE_S_MORE );
		
			break;                                                         
																			  
		case BUTTON_VALUE_SHUTDOWN:                                           
#if DEBUH_UART1		                                                          
			myprintf( "BUTTON_VALUE_SHUTDOWN\r\n");                              /* �ػ� */
#endif				                                                                                                            
																			  
			break;                                                            
																			  
		case BUTTON_VALUE_ALL_CIG:                                            
#if DEBUH_UART1		                                                          
			myprintf( "BUTTON_VALUE_ALL_CIG\r\n");                               /* У׼ҳ��������һ������ */
#endif				
			uAllConfigSet( gp_stuEditInputConfig );
		
			break;
		
		case BUTTON_VALUE_SYSTEM_CIG:                                            
#if DEBUH_UART1		                                                          
			myprintf( "BUTTON_VALUE_SYSTEM_CIG\r\n");                               /* ϵͳ����ҳ��������һ������ */
#endif				
			uSystemAllConfigSet( gp_stuEditInputConfig );
		
			break;
		
		case BUTTON_VALUE_P_TITLES:                                            
#if DEBUH_UART1		                                                          
			myprintf( "BUTTON_VALUE_P_TITLES\r\n");                               /* �������ô�ӡ̧ͷ */
#endif				
			uSetPrintTitles(g_uInputPrintTitles,strlen((const char *)g_uInputPrintTitles),UI_Y_PROMPT);
		
			break;
		
		case BUTTON_VALUE_AUTO_TIME:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_AUTO_TIME\r\n");                                         
#endif	
			uAutoShutdownSet( gp_stuEditInputConfig->ustuAutoTime,UI_Y_PROMPT );                          /* �����Զ��ػ� */
		
			break;
		
		case BUTTON_VALUE_BAROFFSET:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_BAROFFSET\r\n");                                                        
#endif		
			uSampleBarOffsetSet( gp_stuEditInputConfig->ustuBarOffset,UI_Y_PROMPT );                      /* ��������ƫ�� */
		
			break;
				
		case BUTTON_VALUE_OFFSET:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_OFFSET\r\n");
#endif		
			uSampleOffsetSet( gp_stuEditInputConfig->ustuOffset,UI_Y_PROMPT );                           /* ����ƫ���� */
		
			break;
		
		case BUTTON_VALUE_GAIN:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_GAIN\r\n");                                                            
#endif		
			uMax5402GainInitSet( gp_stuEditInputConfig->ustuGain,UI_Y_PROMPT );                          /* �������� */
		
			break;	
		
		case BUTTON_VALUE_PRINTF:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_PRINTF\r\n");
#endif				
			uConfigPrintfFile();                                                                        /* ���Ĵ�ӡ�������� */
				
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
			uConfigTimeYears();                                                                       /* ֻ������ */
														                                             
			break;                                                                                   
														                                             
		case BUTTON_VALUE_MONTH:                                                                     
#if DEBUH_UART1		                                                                                 
			myprintf( "BUTTON_VALUE_MONTH\r\n");                                                       
#endif		                                                                                         
			uConfigTimeMonth();                                                                         /* ֻ������ */
														                                             
			break;                                                                                   
														                                             
		case BUTTON_VALUE_DAY:                                                                       
#if DEBUH_UART1		                                                                                 
			myprintf( "BUTTON_VALUE_DAY\r\n");                                                         
#endif		                                                                                         
			uConfigTimeData();                                                                        /* ֻ������ */
														                                             
			break;                                                                                   
														                                             
		case BUTTON_VALUE_HOURS:                                                                     
#if DEBUH_UART1		                                                                                 
			myprintf( "BUTTON_VALUE_HOURS\r\n");                                                       
#endif		                                                                                         
			uConfigTimeHour();                                                                        /* ֻ����ʱ */
														                                             
			break;                                                                                   
														                                             
		case BUTTON_VALUE_MINUTES:                                                                   
#if DEBUH_UART1		                                                                                 
			myprintf( "BUTTON_VALUE_MINUTES\r\n");                                                     
#endif		                                                                                         
			uConfigTimeMinutes();                                                                     /* ֻ���÷� */
														                                             
			break;                                                                                   
														                                             
		case BUTTON_VALUE_TIME:                                                                      /* ȷ������ʱ�� */
#if DEBUH_UART1		                                                                                 
			myprintf( "BUTTON_VALUE_TIME\r\n");                                                        
#endif	                                                                                             
			uConfigTime();                                                                           /* ����ʱ������� */
														                                             
			break;                                                                                   
														                                             
		case BUTTON_VALUE_FACTORY:	                                                                 
#if DEBUH_UART1		                                                                                 
			myprintf( "BUTTON_VALUE_FACTORY\r\n");                                                     
#endif				                                                                                 
			uFactoryReset();                                                                           /* �ָ��������� */
														                                             
			break;                                                                                   
														                                             
		case BUTTON_VALUE_PROM_FACTORY:	                                                             
#if DEBUH_UART1		                                                                                 
			myprintf( "BUTTON_VALUE_PROM_FACTORY\r\n");                                                
#endif			
			if( EN_ON==gp_stuConfigFile->uCutEnCu ){
				uPrompterWarn( (uint8_t *)"Reset?" );                                                      /* ��ʾ���� �ָ��������� */
			}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
				uPrompterWarn( (uint8_t *)"��λ?" ); 
			}else{
				uPrompterWarn( (uint8_t *)"Invalid" ); 
			}		
				
			break;
		
		case BUTTON_VALUE_HISTORY_CLEAR:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_HISTORY_CLEAR\r\n");
#endif				
			uHistoryClear( UI_Y_PROMPT );                                                            /* �����ʷ���� */
																	                              
			break;                                                                                
																	                              
		case BUTTON_VALUE_PROM_CLEHIS:	                                                          
#if DEBUH_UART1		                                                                              
			myprintf( "BUTTON_VALUE_PROM_CLEHIS\r\n");                                              
#endif		
			if( EN_ON==gp_stuConfigFile->uCutEnCu ){
				uPrompterWarn( (uint8_t *)"Clear History?" );                                             /* ��ʾ���� �����ʷ���� */
			}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
				uPrompterWarn( (uint8_t *)"���?" );                                           
			}else{
				uPrompterWarn( (uint8_t *)"Invalid" ); 
			}			
				
			break;
		
		case BUTTON_VALUE_MOTOR_DOWN:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_MOTOR_DOWN\r\n");
#endif				
			MotorBackward();                                                                      /* ������� */
															                                      
			break;                                                                                
															                                      
		case BUTTON_VALUE_MOTOR_UP:	                                                              
#if DEBUH_UART1		                                                                              
			myprintf( "BUTTON_VALUE_MOTOR_UP\r\n");                                                 
#endif			                                                                                  
			MotorForward();                                                                       /* ���ǰ�� */
															                                      
			break;
		
		case BUTTON_VALUE_LIS_AFFIRM:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_LIS_AFFIRM\r\n");
#endif		
			uTjc4832tTouchEnable( TJC_TOUCH_OFF );                                             /* ��ҳ�رմ��� */ 
			uLisSendHistoryPage( g_uRecordHistoryPage,0 );                                     /* LIS���������ϴ� */
			uTjc4832tTouchEnable( TJC_TOUCH_ON );                                              /* ��ҳ�򿪴��� */
		
			break;	
				
		case BUTTON_VALUE_LIS_CANCLE:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_LIS_CANCLE\r\n");
#endif				
			uDisplayHistoryDataSpecifiedPage( g_uRecordHistoryPage );	                      /* ȡ���ϴ� */
				
			break;	
		
		case BUTTON_VALUE_LIS_UPLOAD:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_LIS_UPLOAD\r\n");
#endif			
			uTjc4832tTouchEnable( TJC_TOUCH_OFF );                                             /* ��ҳ�رմ��� */ 
			uLisSendHistoryPage( g_uRecordHistoryPage,1 );                                     /* LIS���������ϴ� */
			uTjc4832tTouchEnable( TJC_TOUCH_ON );                                              /* ��ҳ�򿪴��� */
				
			break;		
															                                   	
		case BUTTON_VALUE_HISTORY_PRINT:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_HISTORY_PRINT\r\n");
#endif			
			uTjc4832tTouchEnable( TJC_TOUCH_OFF );                                               /* ��ҳ�رմ��� */ 
			uDisplayHistoryData( BUTTON_VALUE_HISTORY_PRINT );                                   /* ��ӡ������ʾ����ʷ���� */			
			uTjc4832tTouchEnable( TJC_TOUCH_ON );                                                /* ��ҳ�򿪴��� */
																                                
			break;		                                                                        
																                                
		case BUTTON_VALUE_HISTORY_DOWN:                                                         
#if DEBUH_UART1		                                                                            
			myprintf( "BUTTON_VALUE_HISTORY_DOWN\r\n");                                           
#endif			                                                                                
			uDisplayHistoryData( BUTTON_VALUE_HISTORY_DOWN );                                    /* �·���ʾ��ʷ���� */		
																                                
			break;                                                                              
																                                
		case BUTTON_VALUE_HISTORY_UP:                                                           
#if DEBUH_UART1		                                                                            
			myprintf( "BUTTON_VALUE_HISTORY_UP\r\n");                                             
#endif			                                                                                
			uDisplayHistoryData( BUTTON_VALUE_HISTORY_UP );                                      /* �Ϸ���ʾ��ʷ���� */		
			
			break;
		
		case BUTTON_VALUE_RESET_MOTOR:	
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_RESET_MOTOR\r\n");
#endif		
			uResetMotorInteriorStauts( UI_Y_PROMPT );          /* ������ ��λ�������ʼλ�� */  //ResetMotor();          /* ���� ��λ�������ʼλ�� */						
			
			break;
		
		case BUTTON_VALUE_REGISTER:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_REGISTER\r\n");
#endif					
			uLoginBottonValue();                                                             /*�ͷ��ź��� ע��ȷ�� */  
			
			break;
		
		case BUTTON_VALUE_LOGIN:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_LOGIN \r\n");
#endif		
			uLoginBottonValue();                                                             /*�ͷ��ź��� ��¼ȷ�� */	      		
			
			break;	
		
		case BUTTON_VALUE_TJC_START:
#if DEBUH_UART1		
			myprintf( "BUTTON_VALUE_TJC_START\r\n");                                         /* ��Ļ�����ɹ� */
#endif				
			uResetLoginBottonValue();                                                        /*�ͷ��ź��� �ٴε�¼ */
													                                         
			break;                                                                           
													                                         
		case BUTTON_VALUE_RELOGIN:                                                           
#if DEBUH_UART1		                                                                         
			myprintf( "BUTTON_VALUE_RELOGIN \r\n");                                          
#endif					                                                                     
			uResetLoginBottonValue();                                                        /*�ͷ��ź��� �ٴε�¼ */
			
			break;	
		
//		case BUTTON_VALUE_VARI_INVALID:
//#if DEBUH_UART1		
//			myprintf( "BUTTON_VALUE_VARI_INVALID\r\n");                          /* ��Ч������ */
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
//			myprintf( "BUTTON_VALUE_TEST_FEXIT \r\n");                       /* ��׼����ǿ���˳� */
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
//			uDensityAffirmPage();                                                                 /* ȷ��Ũ�ȷ���ҳ�� */
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
//			myprintf( "SPC_INIT_PAGE \r\n");                                                /*��ʼ��ҳ*/
//#endif                                                                               
//			break;   
		
		case SPC_BUTTON_VALUE_SHUTDOWN:                                           
#if DEBUH_UART1		                                                          
			myprintf( "SPC_BUTTON_VALUE_SHUTDOWN\r\n");                                     /* �ػ� */
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
		l_puAnalyzeOrder = (uint8_t *)calloc( 1,sizeof(uint8_t) );                           /* �����ڴ� */
		if( NULL!=l_puAnalyzeOrder ){
			(*l_puAnalyzeOrder) = uTempOrder;			
			if( (*l_puAnalyzeOrder)<TJC_DEMARCATION_POINT ){							
				OSQPost( (OS_Q *)&g_TouchMsgQue,(void *)(l_puAnalyzeOrder),(OS_MSG_SIZE )1,OS_OPT_POST_FIFO+ OS_OPT_POST_NO_SCHED,&uTempErr );	
				if( OS_ERR_NONE!=uTempErr ) {  /*����һ����Ϣ*/
					if( NULL!=l_puAnalyzeOrder ){
						free( l_puAnalyzeOrder );
					}
#if DEBUH_UART1
					myprintf( "uTempPostErr1:%d ",uTempErr );
#endif	
				}else{
					OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	 /* ��ʱ10ms   */
				}
			}else{
				OSQPost( (OS_Q *)&g_TouchSpcMsgQue,(void *)(l_puAnalyzeOrder),(OS_MSG_SIZE )1,OS_OPT_POST_FIFO+ OS_OPT_POST_NO_SCHED,&uTempErr );
				if( OS_ERR_NONE!=uTempErr ) {  /*����һ����Ϣ*/
					if( NULL!=l_puAnalyzeOrder ){
						free( l_puAnalyzeOrder );
					}
#if DEBUH_UART1
					myprintf( "uTempPostErr2:%d ",uTempErr );
#endif	
				}else{
					OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	 /* ��ʱ10ms   */
				}
			}					
		}else{
#if DEBUH_UART1
			myprintf( "myMallocErr\r\n" );
#endif	
		}				
	}
}
