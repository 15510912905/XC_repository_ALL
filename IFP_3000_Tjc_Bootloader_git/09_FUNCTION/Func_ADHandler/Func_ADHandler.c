#include "Func_ADHandler.h"

uint8_t uTestInformation( void )
{
//	uint8_t strff[ARR_SAMPLE_TYPE_SIZE] = {0};
//	
//	//OSTimeDlyHMSM(0, 0, 0, 150);                   /* 等待切换页面内容稳定下来 */
//	//uTjc4832tVisObjState( TJC_TEST_PAGE,VIS_OBJ_PAGE6_ID,VIS_HIDE );       /* 隐藏返回控件 */
//	
//	uConfirmPage( TJC_TEST_PAGE );                          /* 确定当前页面为主测试页 */
//		
//	memset( strff,0,sizeof(strff) );	

//	if( calendar.w_date!=g_projectSerial.rec_day ){
//		g_projectSerial.serial_num = 0;
//		g_projectSerial.rec_day = calendar.w_date; /* 记录当前天 */		
//	}		
//	sprintf( (char *)g_projectSerial.serial_id,"%04d%02d%02d%04d",calendar.w_year,calendar.w_month,calendar.w_date,(g_projectSerial.serial_num+1) );    /* 流水号的编码规则日期加流水号 */
//	memcpy( (char *)strff,(const char *)g_projectSerial.serial_id,sizeof(g_projectSerial.serial_id) );
//	if( (0xff==strff[0])||( 0x00==strff[0]) ){
//		uTjc4832tSetLableValue( TJC_TEST_PAGE,MAIN_SERIAL_DIS_CON_ID,(uint8_t *)"20200202001" );
//	}else{
//		uTjc4832tSetLableValue( TJC_TEST_PAGE,MAIN_SERIAL_DIS_CON_ID,(uint8_t *)strff );	
//	}
//	
//	memset( strff,0,sizeof(strff) );
//	memcpy( (char *)strff,(const char *)g_IdMemory.project_name,sizeof(g_IdMemory.project_name) );
//	if( 0xff==strff[0] ){
//		return 0;
//	}else{
//		uTjc4832tSetLableValue( TJC_TEST_PAGE,MAIN_ITEM_DIS_CON_ID,(uint8_t *)strff );
//	}	

//	memset( strff,0,sizeof(strff) );
//	memcpy( (char *)strff,(const char *)g_IdMemory.barcode,DIS_BAR_NUMBER);//sizeof(g_IdMemory.barcode) );
//	if( 0xff==strff[0] ){
//		return 0;
//	}else{
//		uTjc4832tSetLableValue( TJC_TEST_PAGE,MAIN_BARCODE_DIS_CON_ID,(uint8_t *)strff );
//	}
	
	//uTjc4832tVisObjState( TJC_TEST_PAGE,VIS_OBJ_PAGE6_ID,VIS_SHOW );       /* 显示返回控件 */
	//uClearItemData();                                                            /* 清空项目的名称和浓度信息 */
	
	return EXE_SUCCEED;
}

uint8_t uTestInformationRefresh( void )
{
//	uint8_t strff[ARR_SAMPLE_TYPE_SIZE] = {0};
//	
//	//OSTimeDlyHMSM(0, 0, 0, 150);                   /* 等待切换页面内容稳定下来 */
//	//uTjc4832tVisObjState( TJC_TEST_PAGE,VIS_OBJ_PAGE6_ID,VIS_HIDE );       /* 隐藏返回控件 */
//		
//	memset( strff,0,sizeof(strff) );	

//	if( calendar.w_date!=g_projectSerial.rec_day ){
//		g_projectSerial.serial_num = 0;
//		g_projectSerial.rec_day = calendar.w_date; /* 记录当前天 */		
//	}		
//	sprintf( (char *)g_projectSerial.serial_id,"%04d%02d%02d%04d",calendar.w_year,calendar.w_month,calendar.w_date,(g_projectSerial.serial_num+1) );    /* 流水号的编码规则日期加流水号 */
//	memcpy( (char *)strff,(const char *)g_projectSerial.serial_id,sizeof(g_projectSerial.serial_id) );
//	if( (0xff==strff[0])||( 0x00==strff[0]) ){
//		uTjc4832tSetLableValue( TJC_TEST_PAGE,MAIN_SERIAL_DIS_CON_ID,(uint8_t *)"202002020001" );
//	}else{
//		uTjc4832tSetLableValue( TJC_TEST_PAGE,MAIN_SERIAL_DIS_CON_ID,(uint8_t *)strff );	
//	}
//	
//	memset( strff,0,sizeof(strff) );
//	memcpy( (char *)strff,(const char *)g_IdMemory.project_name,sizeof(g_IdMemory.project_name) );
//	if( 0xff==strff[0] ){
//		return 0;
//	}else{
//		uTjc4832tSetLableValue( TJC_TEST_PAGE,MAIN_ITEM_DIS_CON_ID,(uint8_t *)strff );
//	}	

//	memset( strff,0,sizeof(strff) );
//	memcpy( (char *)strff,(const char *)g_IdMemory.barcode,DIS_BAR_NUMBER);//sizeof(g_IdMemory.barcode) );
//	if( 0xff==strff[0] ){
//		return 0;
//	}else{
//		uTjc4832tSetLableValue( TJC_TEST_PAGE,MAIN_BARCODE_DIS_CON_ID,(uint8_t *)strff );
//	}
	
	//uTjc4832tVisObjState( TJC_TEST_PAGE,VIS_OBJ_PAGE6_ID,VIS_SHOW );       /* 显示返回控件 */
	//uClearItemData();                                                            /* 清空项目的名称和浓度信息 */
	
	return EXE_SUCCEED;
}

uint8_t uAcquisitionSystem( uint8_t uStandardQuist )
{
//	OS_ERR err = OS_ERR_NONE;	

//	OSMutexPend( (OS_MUTEX *)&g_Acquisition, 0,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err );	              /*等待信号量*/
//	if( OS_ERR_NONE==err ){
//		if( QUICK_RESULT_PAGE==uStandardQuist ){
//			AcquisitionQuickSystem( uStandardQuist );                    /* 采集流程控制 *///OSTimeDlyHMSM(0, 0, 1, 0 );
//		}else{
//			AcquisitionSystem();                                         /* 采集流程控制 */	
//		}
//		
//		OSMutexPost( (OS_MUTEX *)&g_Acquisition,OS_OPT_POST_NO_SCHED,&err );                  /*释放信号量 */
//	}
	
	return EXE_SUCCEED;
}

///* 标准测试与快速测试的区别是等待时间不一致 */
uint8_t AcquisitionSystem( void )
{
//#if DEBUH_UART1		
//	uint32_t uTestTimeStart = 0;
//	uint32_t uTestTimeEnd = 0;
//#endif
//#if DEBUH_UART1	
//	#if PRIVATE_UART1	
//	uint32_t uTestTimeStartTemp = 0;
//	uint32_t uTestTimeEndTemp = 0;
//	#endif
//#endif
//	
//	uint16_t uTempTestTimeSecond = 0;
//	uint16_t uTempTestTime = 0;
//	uint8_t uArrAsciiTemp[30] = {0};
//	OS_ERR err = OS_ERR_NONE;	
//	ID_Info* pIDData = &g_IdMemory;                                                              /* ID公共数据访问指针 */
//																					             
//	if( g_uElectricValue<=VOLTAGE_THRESHOLD_PROMPT ){                                            /* 电量过低不允许标准测试 */
//		uTjc4832tSetPage( TJC_WARN_PAGE );                                                       /*设置为强制警告页*/
//		if( EN_ON==gp_stuConfigFile->uCutEnCu ){
//			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Low power" );	             //
//		}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
//			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"低电量" );	             //
//		}else{
//			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Invalid" );	             //
//		}	
//		uBuzzerTimes( BUZZER_ONE_TIME );
//		return EXE_FAILED;
//	}
//	
//	if( EXE_FAILED==uVerifyId( pIDData ) ){      	                                             /* ID卡数据校验 */
//		uErrorInvalidId( BUZZER_ON );                                                                       /* 报错 */
//		return EXE_FAILED;
//	}
//	
//	if( 0==g_IdMemory.test_time ){
//#if DEBUH_UART1
//	myprintf( "Time 0\r\n" );
//#endif
//	}else{
//		uTempTestTime = g_IdMemory.test_time;
//	}			
//	
//	if( EXE_STAUTS!=uResetMotorInteriorStauts(UI_N_PROMPT) ){
//		uTjc4832tSetPage( TJC_WARN_PAGE );         /*设置为强制警告页*/
//		if( EN_ON==gp_stuConfigFile->uCutEnCu ){
//			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Please insert the reagent again" );	//
//		}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
//			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"请从新插入试剂卡." );	//
//		}else{
//			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Invalid" );	             //ID数据错误
//		}
//		return EXE_FAILED;
//	}
//	
//	uConfirmPage( TJC_FORCE_EXIT_PAGE );        /*设置为*/ 
////	if( EXE_FAILED==uSemclear( (OS_SEM*)&g_ForceExit ) ){
////	}
//	
//#if DEBUH_UART1		
//		uTestTimeStart = OSTimeGet( &err );
//#endif	
//	
////	/* 使用有限次数循环 */
////	for( uTempTestTimeSecond=0;uTempTestTimeSecond<=(uTempTestTime);uTempTestTimeSecond++ ){			
////		uConfirmPage( TJC_FORCE_EXIT_PAGE );                           /* 确认在强制退出页 */		

////		sprintf( (char *)uArrAsciiTemp,"%s%3d%s","Please wait ",uTempTestTime-(uTempTestTimeSecond)," seconds." );
////		uTjc4832tSetLableValue( TJC_FORCE_EXIT_PAGE,EXIT_TEXT_DIS_CON_ID,(uint8_t *)uArrAsciiTemp );				
////		
////		OSSemPend( (OS_SEM *)&g_ForceExit,1,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	     	/* 退出信号量 不能超过50即一秒 */
////		if( OS_ERR_NONE==err ){
////			uTjc4832tSetPage( TJC_TEST_PAGE );                         /* 设置为 */
////			uTestInformation();                                        /* 显示测试信息 */
////#if DEBUH_UART1	
////			myprintf( "ExitStandard\r\n");
////#endif		
////			return EXE_FAILED;	
////		}	
////		
////		OSTimeDlyHMSM(0, 0, 0, 805,OS_OPT_TIME_HMSM_STRICT,&err );    /* 循环快一点 190+5+805=1000 */
////		g_uRecAutoDownTime = 0;                                       /* 此过程不允许自动关机 */		
////	} 

//	/* 使用有限次数循环 */
//	for( uTempTestTimeSecond=0;uTempTestTimeSecond<=(uTempTestTime*2);uTempTestTimeSecond++ ){	
//#if DEBUH_UART1		
//	#if PRIVATE_UART1	
//		uTestTimeStartTemp = OSTimeGet( &err );
//	#endif		
//#endif
//		uConfirmPage( TJC_FORCE_EXIT_PAGE );                           /* 确认在强制退出页 */
//		
//		if( 0==uTempTestTimeSecond%2 ){
//			sprintf( (char *)uArrAsciiTemp,"%s%3d%s","Please wait ",uTempTestTime-(uTempTestTimeSecond/2)," seconds." );
//			uTjc4832tSetLableValue( TJC_FORCE_EXIT_PAGE,EXIT_TEXT_DIS_CON_ID,(uint8_t *)uArrAsciiTemp );
//		}			
////		
////		OSSemPend( (OS_SEM *)&g_ForceExit,1,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	     	/* 退出信号量 不能超过50即一秒 */
//		if( OS_ERR_NONE==err ){
//			uTjc4832tSetPage( TJC_TEST_PAGE );                         /* 设置为 */
//			uTestInformation();                                        /* 显示测试信息 */
//#if DEBUH_UART1	
//			myprintf( "ExitStandard\r\n");
//#endif		
//			return EXE_FAILED;	
//		}	
//		
//		OSTimeDlyHMSM(0, 0, 0, 305,OS_OPT_TIME_HMSM_STRICT,&err );    /* 循环快一点 190+5+305=500 */
//		g_uRecAutoDownTime = 0;                                       /* 此过程不允许自动关机 */	

//#if DEBUH_UART1		
//	#if PRIVATE_UART1	
//		uTestTimeEndTemp = OSTimeGet( &err );
//		myprintf( "IDTime2:%d \r\n",((uTestTimeEndTemp-uTestTimeStartTemp)*5) );
//	#endif		
//#endif		
//	}  
//	
//#if DEBUH_UART1		
//		uTestTimeEnd = OSTimeGet(&err);
//		myprintf( "IDTime1:%d %d \r\n",((uTestTimeEnd-uTestTimeStart)*5),(((uTestTimeEnd-uTestTimeStart)*5)/1000) );
//#endif	
//                                                  									         
//	uBuzzer( BUZZER_ON );                                             /* Buzzer	*/
//	uConfirmPage( TJC_QUICK_RESULT_PAGE );                            /* 设置为*/		
//	AcquisitionQuickSystem( STANDARD_RESULT_PAGE );                   /* 标准测试 */
//	uBuzzer( BUZZER_OFF );                                            /* Buzzer	*/
	
	return EXE_SUCCEED;
}

///* 标准测试与快速测试的区别是等待时间不一致 */
uint8_t AcquisitionQuickSystem( uint8_t uStandardQuist )
{
//	OS_ERR err = OS_ERR_NONE;	
//	int32_t i = 0;		
//	char strff[32] = {0};
////	uint16_t travel = 0;
////	uint16_t uMotorTimeout = 0;
//	uint8_t uArrBarCode[5] = {0};
//	uint8_t uArrBarCodeTemp[5] = {0};
//	uint8_t uRecIdCardNum = 0;
//	uint8_t uRecError = 0;
//	uint8_t uRecBarError = 0;
//	
//	ID_Info* pIDData = &g_IdMemory;                                                                       /* ID公共数据访问指针 */	
//	ALGORITHM_DATA_TYPE* pAlgorithmData = &g_stuMyAlgorithm;                                              /* 浓度结果公共数据访问指针 */
//	uint32_t* puArrTemp = &g_ADC_Buffer[0];
//	uint16_t* puArrBarCode = &g_ADC_BarCode[0];
//	
//	/* 测试一下初始化一次 */
//	_gp_HardAD7685 = Drv_HardAd7685Init(HARDAD7685_1,_SPI2_, \
//								        AD7685_SPI_CS_PORT,AD7685_SPI_CS_PIN,AD7685_SPI_CLK_PORT,AD7685_SPI_CLK_PIN, \
//								        AD7685_SPI_SDI_PORT,AD7685_SPI_SDI_PIN,_PORT_BUTT_,_PIN_BUTT_);         /* 16ADC  SPI硬件读写	*/	
//	

//	if( (STANDARD_RESULT_PAGE==uStandardQuist) ){
//		//OSTimeDlyHMSM(0, 0, 0, 100,OS_OPT_TIME_HMSM_STRICT,&err);                                               /* 切换页面最小延时时间80ms */
//#if TJC_TEST_TOUCH_ENABLE		                                                                          
//		uTjc4832tTouchEnable( TJC_TOUCH_OFF );                                                                 /* 整页关闭触摸 */                          
//#else                                                                                                     
//		uTjc4832tVisObjState( TJC_QUICK_RESULT_PAGE,VIS_OBJ_CON_ID,VIS_HIDE );                                 /* 隐藏返回控件 */
//#endif		
//	}
//	
//	/* 申请变量初始化 */
//	memset( g_ADC_Buffer,0,sizeof(g_ADC_Buffer) );                     /* 清空荧光采集数据 */
//	memset( g_ADC_BarCode,0,sizeof(g_ADC_BarCode) );                   /* 清空条码AD数据 */	
//	memset( pAlgorithmData,0,sizeof(ALGORITHM_DATA_TYPE) );            /* 清空浓度结果 */	
//	
//	/* 荧光采集前的各个模块检查 */
//	if( (EXE_SUCCEED==uRecError)&&(g_uElectricValue<=VOLTAGE_THRESHOLD_PERCENTAGE) ){                                                       /* 电量过低不允许快速测试 */
//		uTjc4832tSetPage( TJC_WARN_PAGE );                                                                      /* 设置为强制警告页 */
//		if( EN_ON==gp_stuConfigFile->uCutEnCu ){
//			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Low power" );	             //
//		}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
//			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"低电量" );	             //
//		}else{
//			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Invalid" );	             //
//		}	
//		OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);                                                                  
//		uRecError = EXE_FAILED;                                                                                 
//	}                                                                                                           
//																							                    
//	if( (EXE_SUCCEED==uRecError)&&(STANDARD_RESULT_PAGE!=uStandardQuist) ){	                                                                
//		if( EXE_FAILED==uVerifyId( pIDData ) ){      	                                                        /* ID卡数据校验 */        
//			uErrorInvalidId( BUZZER_ON );                                                                                  /* 报错 */
//			OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);                                             
//			uRecError = EXE_FAILED;                                                                             
//		}                                                                                                       
//	}	                                                                                                        
//																							            
//	if( (EXE_SUCCEED==uRecError)&&(STANDARD_RESULT_PAGE!=uStandardQuist) ){	                                    /* 电机必须在复位状态 */   
//		if( EXE_STAUTS!=uResetMotorInteriorStauts(UI_N_PROMPT) ){                                               
//			uTjc4832tSetPage( TJC_WARN_PAGE );                                                                  /*设置为强制警告页*/
//			if( EN_ON==gp_stuConfigFile->uCutEnCu ){
//				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Please insert the reagent again" );	//
//			}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
//				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"请再次插入试剂卡." );	//
//			}else{
//				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Invalid" );	             //ID数据错误
//			}
//			uBuzzerTimes( BUZZER_ONE_TIME );
////			OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err); 
//			uRecError = EXE_FAILED;
//		}
//	}
//	
//#if READCARD_DECTECT
//	if(SWITCH_MIC_ON==gp_stuConfigFile->uSwitchOnOff){
//		if( BSP_ReadPin(READCARD_DEC_CONTROL_PORT,READCARD_DEC_CONTROL_PIN) ){            /* 未到位是读回来是1 到位读回来是0 */
//			OSTimeDlyHMSM(0, 0, 0, 15,OS_OPT_TIME_HMSM_STRICT,&err); 		
//			if( BSP_ReadPin(READCARD_DEC_CONTROL_PORT,READCARD_DEC_CONTROL_PIN) ){
//				uTjc4832tSetPage( TJC_WARN_PAGE );                                                                  /*设置为强制警告页*/
//				if( EN_ON==gp_stuConfigFile->uCutEnCu ){
//					uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Reagent card not in place." );	//
//				}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
//					uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"试剂卡未到位." );	//
//				}else{
//					uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Invalid" );	             //ID数据错误
//				}
//				uBuzzerTimes( BUZZER_ONE_TIME );
//				uRecError = EXE_FAILED;
//			}
//		}
//	}
//#endif
//	
//	if( (STANDARD_RESULT_PAGE!=uStandardQuist)&&(EXE_SUCCEED==uRecError) ){
//		uConfirmPage( TJC_QUICK_RESULT_PAGE );                                                                 /* 确认是测试结果显示页 */	
//#if TJC_TEST_TOUCH_ENABLE		                                                                          
//		uTjc4832tTouchEnable( TJC_TOUCH_OFF );                                                                 /* 整页关闭触摸 */                          
//#else                                                                                                     
//		uTjc4832tVisObjState( TJC_QUICK_RESULT_PAGE,VIS_OBJ_CON_ID,VIS_HIDE );                                 /* 隐藏返回控件 */
//#endif	
//	}

//	
//	if( EXE_SUCCEED==uRecError ){
//		//	uClearItemData();                                                                                      /* 清空项目的名称和浓度信息 */
//		uTjc4832tSetProgressbarValue( TJC_QUICK_RESULT_PAGE,MAIN_PROGRESS_DIS_CON_ID,MAIN_PROGRESS1_VALUE );       /* 进度条 */
//		uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,MAIN_DENSITY_DIS11_CON_ID,(uint8_t *)pIDData->barcode );	   /* 显示项目条码 */	
//		
////		/* 步进电机引脚 */
////		BSP_WritePin(MOTOR_SLEEP_PORT,MOTOR_SLEEP_PIN,MOTOR_SLEEP_TRUE);    /* 高电平使能  低电平休眠 */		
////		BSP_WritePin(MOTOR_DIR_PORT,MOTOR_DIR_PIN,MOTOR_DIR_TRUE);	        /* 方向控制 */		

//		uTjc4832tSetProgressbarValue( TJC_QUICK_RESULT_PAGE,MAIN_PROGRESS_DIS_CON_ID,MAIN_PROGRESS2_VALUE );   /* 进度条 */
//		uFluorescenceLight( FLUORESCENCE_ON );          /* 打开 CTRL_LED灯	 */
//#if PREHEAT_LED_GLOW_
//		OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);                      /* 光源灯需要预热1s 可以不需要 */
//#endif
//		uRecError = uCollectFluorescenceValueBarValue( puArrTemp,puArrBarCode );                                 /* 荧光和条码AD值采集 */	
//		uFluorescenceLight( FLUORESCENCE_OFF );                                                                  /* 关闭CTRL_LED灯	*/ 
//		line_smoth_slid( g_ADC_Buffer,SCAN_LENGTH );                                                             /* 平滑光学AD数据 */
//		uRecError += uTheCalibrationCurve( g_ADC_Buffer,(sizeof(g_ADC_Buffer)/sizeof(uint32_t)) );               /* 校准曲线 */
//		if( EXE_SUCCEED!=uRecError ){
//			uTjc4832tSetPage( TJC_WARN_PAGE );  
//			if( EN_ON==gp_stuConfigFile->uCutEnCu ){
//				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Abnormal test" );	//
//			}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
//				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"异常测试" );	//
//			}else{
//				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Invalid" );	             //ID数据错误
//			}
//			uBuzzerTimes( BUZZER_ONE_TIME );
//			return uRecError;
//		}
//		
//		uTjc4832tSetProgressbarValue( TJC_QUICK_RESULT_PAGE,MAIN_PROGRESS_DIS_CON_ID,MAIN_PROGRESS3_VALUE );     /* 进度条 */
//#if	EN_REVERSE_INT_ARR
//		uRecError = uReverseIntArr( g_ADC_Buffer,(sizeof(g_ADC_Buffer)/sizeof(uint32_t)) );                      /* 翻转数据 */
//#endif
//#if DEBUH_UART1	
//		myprintf( "peak_num:%d maxium_num:%d \r\n",pIDData->peak_num,pIDData->se_value[0] );	
//	#if PRIVATE_ADC_UART1
//		if( gp_stuConfigFile->uPrintAD ){
//			myprintf( "uStartOffset:%d line_smoth_slid:\r\n",gp_stuConfigFile->uStartOffset );	
//			for( i=0;i<(sizeof(g_ADC_Buffer)/sizeof(uint32_t));i++){	
//				myprintf( "%8d \r\n",g_ADC_Buffer[i] );  		                         //myprintf( "O-%4d:%8d \r\n",i,g_ADC_Buffer[i] );
//			}		
//			myprintf( "\r\n" );
//		}
//	#endif		
//#endif

//		/* 关闭扫描条码 */
//		if( gp_stuConfigFile->uScanBar ){
//			vbar_line_smoth_slid( g_ADC_BarCode,BARVODE_LENGTH );   /* 平滑条码数据 */
////			uLinearSmooth( g_ADC_BarCode,BARVODE_LENGTH );

//#if DEBUH_UART1	
//	#if PRIVATE_BAR_UART1
//			if( gp_stuConfigFile->uPrintBar ){
//				myprintf( "BarCode:\r\n" );		
//				for( i=0;i<(sizeof(g_ADC_BarCode)/sizeof(uint16_t));i++){
//					myprintf( "%8d \r\n",(uint32_t )g_ADC_BarCode[i] );  				//myprintf( "O-%4d:%8d \r\n",i,g_ADC_BarCode[i] );
//				}
//				myprintf( "\r\n" );
//			}
//	#endif
//#endif	

//			if( NULL==uWaveCrestTrough( g_ADC_BarCode,uArrBarCode,(sizeof(g_ADC_BarCode)/sizeof(uint16_t)) ) ){     /* 计算波峰波谷 */
//				memset( uArrBarCode,0,sizeof(uArrBarCode) );
//			}	
//		
//			if( NULL==uBarTransition( pIDData,uArrBarCodeTemp ) ){
//				memset( uArrBarCodeTemp,0,sizeof(uArrBarCodeTemp) );
//			}
//		
//			memset( strff,0,sizeof(strff) );	
//			uBarNumTransitionAscii( (const uint8_t *)uArrBarCode,(uint8_t *)strff );
//			if( EN_ON==gp_stuConfigFile->uCutEnCu ){
//				uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,MAIN_DENSITY_DIS10_CON_ID,(uint8_t *)"Test Bar:" );	/* 显示测试条码 */
//			}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
//				uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,MAIN_DENSITY_DIS10_CON_ID,(uint8_t *)"测试条码:" );	/* 显示测试条码 */
//			}else{
//				uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,MAIN_DENSITY_DIS10_CON_ID,(uint8_t *)"Invalid" );	             //ID数据错误
//			}
//			
//			uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,MAIN_DENSITY_DIS12_CON_ID,(uint8_t *)strff );	/* 显示测试条码 */
//			
//#if DEBUH_UART1	
//	#if PRIVATE_UART1
//			myprintf( "BarCode1:\r\n" );
//			for( i=0;i<(sizeof(uArrBarCode)/sizeof(uint8_t));i++)
//			{
//				myprintf( "O-%4d:%2x \r\n",i,pIDData->barcode[i] );
//			}	
//	#endif		
//			myprintf( "BarCode2:\r\n" );
//			for( i=0;i<(sizeof(uArrBarCode)/sizeof(uint8_t));i++)
//			{
//				myprintf( "O-%4d:%2x \r\n",i,uArrBarCode[i] );
//			}			
//			myprintf( "BarCode3:\r\n" );
//			for( i=0;i<(sizeof(uArrBarCode)/sizeof(uint8_t));i++)
//			{
//				myprintf( "O-%4d:%2x \r\n",i,uArrBarCodeTemp[i] );
//			}
//#endif		
//			uRecIdCardNum = uGetIdCountValue();                         /* 记录条码项目选项 */
//			/* 如果条码发现不匹配 自动查找库 */		
//			if( barcompare((const char *)uArrBarCodeTemp,(const char *)uArrBarCode,sizeof(uArrBarCode)) ){		/* 在什么情况下提示条码不正确 */				
//				for( i=0;i<g_projectSerial.uid_max;i++ ){
//					pIDData = uReadStoreIdItem( i );					
//					if( NULL!=pIDData ){
//						/* ID卡数据校验 */
//						//uReadStoreIdItem( uGetIdCountValue() );     /* 重新读取 */					
//						if( EXE_FAILED==uVerifyId( pIDData ) ){
//							uErrorInvalidId( BUZZER_OFF );                        /* ID卡无效报错 */
//							continue;           
//						}
//						uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,MAIN_DENSITY_DIS11_CON_ID,(uint8_t *)pIDData->barcode );	/* 显示项目条码 */
//						
//						if( NULL==uBarTransition( pIDData,uArrBarCodeTemp ) ){
//							memset( uArrBarCodeTemp,0,sizeof(uArrBarCodeTemp) );
//						}				
//					}
//					if( (barcompare((const char *)uArrBarCodeTemp,(const char *)uArrBarCode,sizeof(uArrBarCode))) ){
//						if( (i>=(g_projectSerial.uid_max-1)) ){							
////							uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,MAIN_DENSITY_DIS13_CON_ID,(uint8_t *)"Bar Error" );	//条码不正确
//							uRecBarError = EXE_FAILED;
//							uReadStoreIdItem( uRecIdCardNum );             /* 还原条码项目 */
//						}
//					}else{
//						uRecIdCardNum = i;
//						break;
//					}
//				}			
//			}else{
//				uRecIdCardNum = uGetIdCountValue();
//			}
//		}else{
//			uRecIdCardNum = uGetIdCountValue();
//		}

//		uTjc4832tSetProgressbarValue( TJC_QUICK_RESULT_PAGE,MAIN_PROGRESS_DIS_CON_ID,MAIN_PROGRESS4_VALUE );           /* 进度条 */	
//		/* 根据反应值利用不同的算法计算浓度 */   
//		if( EXE_FAILED!=uRecBarError ){
//			uRecError = Result_Calculate( g_ADC_Buffer,pIDData,pAlgorithmData,uRecIdCardNum );		                   /* 算法处理 */
//			if( EXE_SUCCEED==uRecError ){
//				uTjc4832tSetProgressbarValue( TJC_QUICK_RESULT_PAGE,MAIN_PROGRESS_DIS_CON_ID,MAIN_PROGRESS5_VALUE );   /* 进度条5 */				
//#if DEBUH_UART1	
//				myprintf( "Result_Calculate:\r\n" );
//				myprintf( "result1:%.4f \r\n",pAlgorithmData->result1 );
//				myprintf( "result2:%.4f \r\n",pAlgorithmData->result2 );
//				myprintf( "result3:%.4f \r\n",pAlgorithmData->result3 );
//#endif		
//			}
//		}
//				
////		ResetMotor();                                                                                         /* 电机按照步数复位 */		
////		OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err ); 	                                          /* 堵转时不能使用 */	
//		uResetMotorInteriorStauts(UI_N_PROMPT);                                                               /* 电机传感器复位 最后开始 */	

//		if( EXE_FAILED==uRecBarError ){
//			uTjc4832tSetPage( TJC_PROMPTER_PAGE );                                                                /* 设置为强制警告页*/			
//			if( EN_ON==gp_stuConfigFile->uCutEnCu ){
//				uTjc4832tSetLableValue( TJC_PROMPTER_PAGE,PROMPTER_ID_TXT,(uint8_t *)"Associated?" );	                  /* 条码不正确 */
//			}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
//				uTjc4832tSetLableValue( TJC_PROMPTER_PAGE,PROMPTER_ID_TXT,(uint8_t *)"匹配?" );	                  /* 条码不正确 */
//			}else{
//				uTjc4832tSetLableValue( TJC_PROMPTER_PAGE,PROMPTER_ID_TXT,(uint8_t *)"Invalid" );	             //ID数据错误
//			}
//			uBuzzerTimes( BUZZER_ONE_TIME );
//		}
//	}
//	
//#if TJC_TEST_TOUCH_ENABLE	
//	uTjc4832tTouchEnable( TJC_TOUCH_ON );                                                                     /* 整页打开触摸 */
//#else
//	uTjc4832tVisObjState( TJC_QUICK_RESULT_PAGE,VIS_OBJ_CON_ID,VIS_SHOW );  /* 显示返回控件 */
//#endif
//	
//#if DEBUH_UART1	
//	myprintf( "QuickTest:%d\r\n",uRecError );
//#endif	
//	
//	return uRecError;   /* 返回当前页面ID value值为切换后的页面ID  */
	return EXE_SUCCEED;
}

uint8_t uCollectFluorescenceValueBarValue( uint32_t* puArrTemp,uint16_t* puArrBarCode )
{
//	uint16_t travel = 0;
//	uint16_t uMotorTimeout = 0;
//	OS_ERR err = OS_ERR_NONE;	
//	
//	/* 步进电机引脚 */
//	BSP_WritePin(MOTOR_SLEEP_PORT,MOTOR_SLEEP_PIN,MOTOR_SLEEP_TRUE);    /* 高电平使能  低电平休眠 */		
//	BSP_WritePin(MOTOR_DIR_PORT,MOTOR_DIR_PIN,MOTOR_DIR_TRUE);	        /* 方向控制 */
//	
//	while( travel<MOTOR_STEP_NUMBER )
//	{			
//		PWM_Config( _gp_PWM1,MOTOR_PULSE,MOTOR_FREQUENCY );    /* 配置PWM方波 300起 */			
//		PWM_Enable( _gp_PWM1 );	          	                   /*使能PWM方波 电机走*/
//		if( (gp_stuConfigFile->uStartOffset<=travel)&&(travel<(SCAN_LENGTH+gp_stuConfigFile->uStartOffset)) ){
//			readAD( puArrTemp++ );	                           /*读Ad7685数据*/
//		}
//		if( ((EXCURSION_LENGTH-gp_stuConfigFile->uBarOffset)<travel)&&(travel<(MOTOR_STEP_NUMBER-gp_stuConfigFile->uBarOffset)) ){
//			*(puArrBarCode++) = Get_Adc_Average( ADC_Channel_10,BAR_COLLECT_TIMES );//Get_Adc( ADC_Channel_10 );  //*(puArrBarCode++) = BSP_ReadAdc( BAR_CODE_PORT,BAR_CODE_PIN );
//		}
//		
//		while( ((0<_gp_PWM1->remaining_pulse)&&(uMotorTimeout<MOTOR_TIMEOUT)) ){
//			OSTimeDlyHMSM(0, 0, 0, MOTOR_TIME_SLICE,OS_OPT_TIME_HMSM_STRICT,&err ); /* OSTimeDlyHMSM(0, 0, 0, MOTOR_DELAY,OS_OPT_TIME_HMSM_STRICT,&err ); */
//			uMotorTimeout++;
//			if( uMotorTimeout>=MOTOR_TIMEOUT ){
//				return EXE_FAILED;
//			}
//		}

//		travel++;
//	}
	
	return EXE_SUCCEED;
}

/* 采集求和 传入地址必须有效 */
uint32_t* readAD( uint32_t* puArr )
{
	uint8_t i = 0;
	uint16_t u16AD = 0;
	uint32_t u32Result = 0;

	
	for(i=0; i<AD_COLLECT_TIMES; i++)
	{		
//		u16AD = HardAd7685OneAcq(_gp_HardAD7685);  /*软件SPI 读Ad7685数据*/ //u16AD = Ad7685OneAcq(_gp_AD7685);          /*软件SPI 读Ad7685数据*/
#if DEBUH_UART1	
		#if PRIVATE_SPCIAL_AD_UART1
		myprintf( "Ori:%8d \r\n",u16AD );        /*  	*/	
		#endif
#endif	
		u32Result = u32Result + u16AD;
	}	

	*puArr = u32Result;	   
	
#if DEBUH_UART1
	#if PRIVATE_SPCIAL_AD_UART1
	myprintf( "Ori*8:%8d \r\n",*puArr );
	#endif
#endif	
	
	return puArr;
}

/* 
平滑数组
下标0-4数组里5个数求平均装在下标为2的数组里  
下标(n-5)-(n-1)数组里5个数求平均装在下标为(n-3)的数组里
*/
void line_smoth_slid( uint32_t* pOneBuffer,uint16_t len )
{
	uint32_t *pArr, *pArrTem, temp;
	uint16_t m = 0;
	uint8_t n = 0;
	
	pArr = pOneBuffer;
	pArrTem = pOneBuffer+2;	
	
	for( m = len - 4; m > 0; m-- )
	{		
		temp = 0;
		for( n = 5; n > 0; n--)
		{
			temp = temp + *(pArr++);
		}		
		pArr = pArr - 4;
		
		*(pArrTem++) = temp / 5;   /*每5个进行一下平均*/
	}
}

uint8_t uReverseIntArr( uint32_t* pTempArr,int32_t uLength )
{
//    int32_t i, j;
//	uint32_t* pTempStrArr = NULL;
//	
//	pTempStrArr = calloc( sizeof(uint32_t),uLength );
//	if( NULL==pTempStrArr ){
//#if DEBUH_UART1	
//		myprintf( "Error ReverseInt \r\n" );
//#endif
//		return EXE_FAILED;
//	}
//	
//    for( i=0,j=(uLength-1);(i<uLength)&&(j>=0);++i,--j)
//    {
//        *(pTempStrArr+i) = *(pTempArr+j);
//    }
//	
//	memcpy( pTempArr,pTempStrArr,(uLength*sizeof(uint32_t)));
//	
//	if( NULL!=pTempStrArr ){
//		free( pTempStrArr );
//	}
	
	return EXE_SUCCEED;
}

/* ID卡数据校验 */
uint8_t uVerifyId( ID_Info *pAraParam )
{
//	uint8_t i = 0;
//	
//	if( (0x00==pAraParam->project_name[0])||(0xff==pAraParam->project_name[0]) ){
//#if DEBUH_UART1	
//		myprintf( "ProjectName:%c \r\n",pAraParam->project_name[0] );		
//#endif
//		return EXE_FAILED;
//	}
//	
//	if( pAraParam->peak_num>MAX_PEAK_NUM ){
//#if DEBUH_UART1	
//			myprintf( "peak_num:%d \r\n",pAraParam->peak_num );		
//#endif
//			return EXE_FAILED;
//	}
//	
//	for( i=0;i<pAraParam->peak_num;i++ ){	
//		if( (pAraParam->interval_s[i]>=pAraParam->interval_e[i])||(pAraParam->interval_e[i]>=SCAN_LENGTH) ){			
//		//区间不对如何处理
//#if DEBUH_UART1	
//			myprintf( "Start-End:%d %d \r\n",pAraParam->interval_s[i],pAraParam->interval_e[i] );		
//#endif
//			return EXE_FAILED;
//		}
//		if( (0==pAraParam->se_value[i])||(pAraParam->se_value[i]>=(pAraParam->interval_e[i]-pAraParam->interval_s[i])) ){        /* 取几个最大值 */
//			pAraParam->se_value[i] = 5;
//		}
//	}	
//	
//	if( pAraParam->children_num>MAX_CHILDER ){
//#if DEBUH_UART1	
//			myprintf( "children_num:%d \r\n",pAraParam->children_num );		
//#endif
//			return EXE_FAILED;
//	}
	
	return EXE_SUCCEED;
}

/* ID卡子项数据校验 */
uint8_t uVerifyIdChildren( UINTE_DATA_TYPE *pChildrenParam )
{	
	if( (0==pChildrenParam->children_para_a)||(1==isnan(pChildrenParam->children_para_a)) ){
#if DEBUH_UART1	
		myprintf( "children_para_a:%.2f \r\n",pChildrenParam->children_para_a );		
#endif
		if(0xffffffff==pChildrenParam->children_para_a){
			return EXE_FAILED;
		}
	}
	
	if( (0==pChildrenParam->children_para_b)||(1==isnan(pChildrenParam->children_para_b)) ){
#if DEBUH_UART1	
		myprintf( "children_para_b:%.2f \r\n",pChildrenParam->children_para_b );		
#endif
		if(0xffffffff==pChildrenParam->children_para_b){
			return EXE_FAILED;
		}
	}
	
	if( (0==pChildrenParam->children_para_c)||(1==isnan(pChildrenParam->children_para_c)) ){
#if DEBUH_UART1	
		myprintf( "children_para_c:%.2f \r\n",pChildrenParam->children_para_c );		
#endif
		if(0xffffffff==pChildrenParam->children_para_c){
			return EXE_FAILED;
		}
	}
	
	if( (0==pChildrenParam->children_para_d)||(1==isnan(pChildrenParam->children_para_d)) ){
#if DEBUH_UART1	
		myprintf( "children_para_d:%.2f \r\n",pChildrenParam->children_para_d );		
#endif
		if(0xffffffff==pChildrenParam->children_para_d){
			return EXE_FAILED;
		}
	}
	
	if( (0==pChildrenParam->children_sample_coefficient[0])||(0==pChildrenParam->children_sample_coefficient[1])||
		(0==pChildrenParam->children_sample_coefficient[3]) ){
#if DEBUH_UART1	
		myprintf( "children_sample_coefficient:%.2f %.2f %.2f \r\n",pChildrenParam->children_sample_coefficient[0],pChildrenParam->children_sample_coefficient[1],
															        pChildrenParam->children_sample_coefficient[3] );		
#endif	
	}
	
	if( (1==isnan(pChildrenParam->children_sample_coefficient[0]))||(1==isnan(pChildrenParam->children_sample_coefficient[1]))||
		(1==isnan(pChildrenParam->children_sample_coefficient[1])) ){
#if DEBUH_UART1	
		myprintf( "children_sample_coefficient:%.2f %.2f  %.2f \r\n",pChildrenParam->children_sample_coefficient[0],pChildrenParam->children_sample_coefficient[1],
			                                                         pChildrenParam->children_sample_coefficient[3] );		
#endif
		return EXE_FAILED;		
	}
	
	if( (0xff==pChildrenParam->children_c_1p)||(0xff==pChildrenParam->children_c_2p) ){
#if DEBUH_UART1	
		myprintf( "children_c_p:%d %d \r\n",pChildrenParam->children_c_1p,pChildrenParam->children_c_2p );		
#endif
		return EXE_FAILED;
	}else{
		if( (pChildrenParam->children_c_1p>=10) ){
#if DEBUH_UART1	
			myprintf( "children_c_p:%d \r\n",pChildrenParam->children_c_1p );		
#endif		
		}
		if( (pChildrenParam->children_c_2p>=10) ){
#if DEBUH_UART1	
			myprintf( "children_c_p:%d \r\n",pChildrenParam->children_c_2p );		
#endif		
		}
	}
	
	return EXE_SUCCEED;
}

uint8_t uTheCalibrationCurve( uint32_t* pBuffer,uint32_t uSize )
{
	uint32_t i = 0;
	uint32_t uRecApproximation = 0;
	int32_t iRecValue = 0;
	
	for( i=0;i<uSize-2;i++ ){
		iRecValue = pBuffer[i]-pBuffer[i+1];
		if( ((iRecValue<0)&&(iRecValue>-APPROXIMATION))||((iRecValue>0)&&(iRecValue<APPROXIMATION)) ){
			uRecApproximation++;
		}
	}
	
	if( uRecApproximation>ADC_CRITICAL ){
		return EXE_FAILED;
	}else{
		return EXE_SUCCEED;
	}
	
}

/*  计算浓度值 目前支持三种算法 
    自己计算波峰波谷曲线 直线拟合算法
	已知直线方程的直线拟合算法
	已知四参数方程的参数法  */
uint8_t Result_Calculate( uint32_t* pOneBuffer,ID_Info* pIdAra,ALGORITHM_DATA_TYPE* pAra,uint8_t uIdCardNum )
{	
#if DEBUH_UART1	
	uint8_t i = 0;
#endif
	uint8_t uRecRelation = 0;
	uint8_t uChildrenNum = 0;
	uint8_t uRecReference = 0;
	uint8_t uRecError = 0;
	float x1=0, x2=0, x3=0;
	UINTE_DATA_TYPE* pTempUinteData = NULL;
	
	pTempUinteData = (UINTE_DATA_TYPE *)calloc( 1,sizeof(UINTE_DATA_TYPE) );
	if( NULL==pTempUinteData ){
		return EXE_FAILED;
	}
	
#if DEBUH_UART1	
	myprintf( "CalculateWave:%d \r\n",pIdAra->peak_num );		
	for( i=0;i<pIdAra->peak_num;i++ ){
		myprintf( "S%d:%d E%d:%d \r\n",i,pIdAra->interval_s[i],i,pIdAra->interval_e[i] );
	}
#endif
	
	/* 寻找是否有对应的参考区间 */
	uRecReference = uFindReferenceName( (uint8_t *)pIdAra->project_name );
	if( uRecReference>0 ){
		SPI_Flash_Read( (uint8_t *)&g_stuUserReference,(SPIFLASH_USER_REFER_ADDR+((uRecReference-1)*SPIFLASH_PAGE_BASE_ADDR)),sizeof(USER_REFERRENCE) );
	}else{
		memset( (uint8_t *)&g_stuUserReference,0,sizeof(g_stuUserReference) );
	}
	
	/* 遍历子项 求取T/C */
	for( uChildrenNum=0;uChildrenNum<pIdAra->children_num;uChildrenNum++ ){		
		uRecError = uReadChildrenData( pTempUinteData,uChildrenNum,uIdCardNum );   /* 读子项数据 */
		if( EXE_SUCCEED==uRecError ){
			uRecError = uVerifyIdChildren( pTempUinteData );
		}else{
			uErrorInvalidId( BUZZER_OFF );                                                                                          /* 报错 */
		}
		if( EXE_SUCCEED==uRecError ){			
			switch( uChildrenNum ){
				case 0:	
					if( pIdAra->children_num>1 ){
						uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,NAME_DENSITY1_DIS_CON_ID,(uint8_t *)pTempUinteData->children_name );
					}else{
						uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,NAME_DENSITY1_DIS_CON_ID,(uint8_t *)pIdAra->project_name );
					}
					uCalculateCE( pTempUinteData,&uRecRelation );
					uCalculatePesponse( pOneBuffer,pIdAra,uRecRelation,&x1 );
					uCalculateDensity( pTempUinteData,pAra,x1,uChildrenNum );
					uDisplayDensity( pIdAra,pTempUinteData,pAra,uChildrenNum,&g_stuUserReference );				
					break;
				case 1:
					uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,NAME_DENSITY2_DIS_CON_ID,(uint8_t *)pTempUinteData->children_name );
					uCalculateCE( pTempUinteData,&uRecRelation );
					uCalculatePesponse( pOneBuffer,pIdAra,uRecRelation,&x2 );
					uCalculateDensity( pTempUinteData,pAra,x2,uChildrenNum );
					uDisplayDensity( pIdAra,pTempUinteData,pAra,uChildrenNum,&g_stuUserReference );
					break;
				case 2:
					uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,NAME_DENSITY3_DIS_CON_ID,(uint8_t *)pTempUinteData->children_name );
					uCalculateCE( pTempUinteData,&uRecRelation );
					uCalculatePesponse( pOneBuffer,pIdAra,uRecRelation,&x3 );
					uCalculateDensity( pTempUinteData,pAra,x3,uChildrenNum );
					uDisplayDensity( pIdAra,pTempUinteData,pAra,uChildrenNum,&g_stuUserReference );
					break;

				default:
					break;  /* 错误码 */
			}
		}else{
			uErrorInvalidId( BUZZER_OFF );                                                                                              /* 报错 */
		}
	}	
	
	if( NULL!=pTempUinteData ){
		free( pTempUinteData ); /* 内存溢出 */
	}
	
	return EXE_SUCCEED;
}

/*  计算TC比 返回X  */
uint8_t TC_Calculate(uint32_t* pOneBuffer, uint16_t T_s, uint16_t T_e, uint16_t C_s, uint16_t C_e, uint8_t peakT_sample,uint8_t peakC_sample,float* fpCalPes)
{
	uint16_t i = 0;

	float  TCValue = 0;  	//double TCValue = 0;
	uint32_t T, C;
	uint32_t* pT_Peak = NULL;
	uint32_t* pC_Peak = NULL;
	uint16_t T_Len = 0, C_Len = 0;
	
#if DEBUH_UART1
	#if PRIVATE_UART1
	myprintf( "T:%d %d C:%d %d peakT:%d peakC:%d \r\n",T_s,T_e,C_s,C_e,peakT_sample,peakC_sample );
	#endif
#endif

	T_Len = T_e - T_s;
	if( (T_Len<=0)&&(T_Len>=SCAN_LENGTH) ){
		return EXE_FAILED;
	}
	C_Len = C_e - C_s;
	if( (C_Len<=0)&&(C_Len>=SCAN_LENGTH) ){
		return EXE_FAILED;
	}

	pT_Peak = (uint32_t*)calloc(T_Len, sizeof(uint32_t));
	if(NULL == pT_Peak){
		return EXE_FAILED;   /* 定义错误码 */
	}

	pC_Peak = (uint32_t*)calloc(C_Len, sizeof(uint32_t));
	if(NULL == pC_Peak){
		return EXE_FAILED;   /* 定义错误码 */
	}

	for (i = 0; i < T_Len; i++){
		pT_Peak[i] = pOneBuffer[T_s + i];  /* *(pT_Peak+i) = *(pOneBuffer+T_s+i); */		
#if DEBUH_UART1
		#if PRIVATE_SPCIAL_UART1
		myprintf( "pT_Peak%3d:%6d \r\n",i,*(pT_Peak+i) );
		#endif
#endif
	}
	
#if DEBUH_UART1
	#if PRIVATE_SPCIAL_UART1
		myprintf( "\r\n" );
	#endif
#endif	
	
	for (i = 0; i < C_Len; i++){
		pC_Peak[i] = pOneBuffer[C_s + i];
#if DEBUH_UART1
		#if PRIVATE_SPCIAL_UART1
		myprintf( "pC_Peak%3d:%6d \r\n",i,pC_Peak[i] );
		#endif
#endif
	}
	
	T = Average(pT_Peak, T_Len, peakT_sample,AVERAGE_MAX);
	C = Average(pC_Peak, C_Len, peakC_sample,AVERAGE_MAX);
	if( (T>AD_VALUE_MAX)||(C>AD_VALUE_MAX) ){
//		TCValue = (float)0;                      /* 错误处理 */
	}else{
		TCValue = (float)T / (float)C;           /* 需要确定T C的准确性*/
//		TCValue = (float)C / (float)T;
		*fpCalPes = TCValue;
	}
	
	if( NULL!=pT_Peak ){ 
		free(pT_Peak);
	}
	if(NULL != pC_Peak){
		free(pC_Peak);
	}
	
#if DEBUH_UART1
	myprintf( "T:%d C:%d TCValue:%.2f\r\n",T,C,TCValue );
#endif

	return EXE_SUCCEED;
}

/* 求区间平均值 */
uint32_t Average(uint32_t *Buffer, uint16_t len, uint8_t num,uint8_t uMinMax )
{
	uint8_t i = 0;
	uint32_t temp = 0;
	
	if( AVERAGE_MAX==uMinMax ){
#if STORT_STL
		qsort(Buffer, len, sizeof(int), cmpfuncintmax);  /*排序函数*/
#else
		InsertionSortUint32_t( (uint32_t *)Buffer,(len),SORT_MAX );
#endif
	}else{
#if STORT_STL
		qsort(Buffer, len, sizeof(int), cmpfuncintmin);  /*排序函数*/	
#else
		InsertionSortUint32_t( (uint32_t *)Buffer,(len),SORT_MIN );
#endif		
	}
		
	for (i = 0; i < num; i++){
		temp = temp + Buffer[i];
#if DEBUH_UART1
	#if PRIVATE_UART1
		myprintf( "max%2d: %d \r\n",i,Buffer[i] );
	#endif
#endif
	}

	return temp / num;
}

/* 比较函数 */
int cmpfuncintmax(const void * a, const void * b)
{
	return ( *(int*)b - *(int*)a );   /*从大到小*/
}

/* 比较函数 */
int cmpfuncintmin(const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b ); /*从小到大*/
}

/* 比较函数 */
int cmpfuncint16max(const void * a, const void * b)
{
	return ( *(uint16_t*)b - *(uint16_t*)a );   /*从大到小*/
}

/* 比较函数 */
int cmpfuncint16min(const void * a, const void * b)
{
	return ( *(uint16_t*)a - *(uint16_t*)b ); /*从小到大*/
}

/* 插入排序 从大到小排序 */
void InsertionSortUint32_t(uint32_t arr[], uint32_t len,uint8_t uMaxMin)
{
	int i, j, key;
	
	if( uMaxMin ){
		for (i = 1; i < len; i++){
			key = arr[i];
			j = i - 1;
			while ((j >= 0) && (arr[j] < key)) {
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j + 1] = key;
		}
	}else{
		for (i = 1; i < len; i++){
			key = arr[i];
			j = i - 1;
			while ((j >= 0) && (arr[j] > key)) {
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j + 1] = key;
		}
	}
}

void InsertionSortUint16_t(uint16_t arr[], uint16_t len,uint8_t uMaxMin )
{
	int i, j, key;
	
	if( uMaxMin ){ 
		/* 插入排序 从大到小排序 */
		for (i = 1; i < len; i++){
			key = arr[i];
			j = i - 1;
			while ((j >= 0) && (arr[j] < key)) {
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j + 1] = key;
		}
	}else{
		/* 插入排序 从小到大排序 */
		for (i = 1; i < len; i++){
			key = arr[i];
			j = i - 1;
			while ((j >= 0) && (arr[j] > key)) {
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j + 1] = key;
		}
	}
}

uint8_t uCalculateCE( UINTE_DATA_TYPE* stuIdInfo,uint8_t* upRecRel )
{
	if( (0==stuIdInfo->children_c_1p)&&(0==stuIdInfo->children_c_2p) ){
		*upRecRel = 0;
	}else if( (0==stuIdInfo->children_c_1p)&&(1==stuIdInfo->children_c_2p) ){
		*upRecRel = 1;
	}else if( (0==stuIdInfo->children_c_1p)&&(2==stuIdInfo->children_c_2p) ){
		*upRecRel = 2;
	}else if( (1==stuIdInfo->children_c_1p)&&(0==stuIdInfo->children_c_2p) ){
		*upRecRel = 3;
	}else if( (1==stuIdInfo->children_c_1p)&&(1==stuIdInfo->children_c_2p) ){
		*upRecRel = 4;
	}else if( (1==stuIdInfo->children_c_1p)&&(2==stuIdInfo->children_c_2p) ){
		*upRecRel = 5;
	}else if( (2==stuIdInfo->children_c_1p)&&(0==stuIdInfo->children_c_2p) ){
		*upRecRel = 6;
	}else if( (2==stuIdInfo->children_c_1p)&&(1==stuIdInfo->children_c_2p) ){
		*upRecRel = 7;
	}else if( (2==stuIdInfo->children_c_1p)&&(2==stuIdInfo->children_c_2p) ){
		*upRecRel = 8;
	}else{ 
		*upRecRel = 0xfe;
#if DEBUH_UART1		
			myprintf( "P1P2 Error\r\n");                             /* 选择全血 */
#endif	
	}	
	
	return EXE_SUCCEED;
}

uint8_t uCalculatePesponse( uint32_t* pOneBuffer,ID_Info* pstuIdInfo,uint8_t uRecRel,float* fpCalPes )
{
	switch ( uRecRel ){
		case 0:
			TC_Calculate(pOneBuffer, pstuIdInfo->interval_s[0], pstuIdInfo->interval_e[0], pstuIdInfo->interval_s[0], pstuIdInfo->interval_e[0], pstuIdInfo->se_value[0],pstuIdInfo->se_value[0],fpCalPes );  /* 读出来的值  pIdAra->se_algorithm[0] */  		
			break;		
		case 1:
			TC_Calculate(pOneBuffer, pstuIdInfo->interval_s[0], pstuIdInfo->interval_e[0], pstuIdInfo->interval_s[1], pstuIdInfo->interval_e[1], pstuIdInfo->se_value[0],pstuIdInfo->se_value[1],fpCalPes );  /* 读出来的值  pIdAra->se_algorithm[0] */  		
			break;
		case 2:
			TC_Calculate(pOneBuffer, pstuIdInfo->interval_s[0], pstuIdInfo->interval_e[0], pstuIdInfo->interval_s[2], pstuIdInfo->interval_e[2], pstuIdInfo->se_value[0],pstuIdInfo->se_value[2],fpCalPes );  /* 读出来的值  pIdAra->se_algorithm[0] */  		
			break;
		case 3:
			TC_Calculate(pOneBuffer, pstuIdInfo->interval_s[1], pstuIdInfo->interval_e[1], pstuIdInfo->interval_s[0], pstuIdInfo->interval_e[0], pstuIdInfo->se_value[1],pstuIdInfo->se_value[0],fpCalPes );  /* 读出来的值  pIdAra->se_algorithm[0] */  		
			break;		
		case 4:
			TC_Calculate(pOneBuffer, pstuIdInfo->interval_s[1], pstuIdInfo->interval_e[1], pstuIdInfo->interval_s[1], pstuIdInfo->interval_e[1], pstuIdInfo->se_value[1],pstuIdInfo->se_value[1],fpCalPes );  /* 读出来的值  pIdAra->se_algorithm[0] */  		
			break;
		case 5:
			TC_Calculate(pOneBuffer, pstuIdInfo->interval_s[1], pstuIdInfo->interval_e[1], pstuIdInfo->interval_s[2], pstuIdInfo->interval_e[2], pstuIdInfo->se_value[1],pstuIdInfo->se_value[2],fpCalPes );  /* 读出来的值  pIdAra->se_algorithm[0] */  		
			break;
		case 6:
			TC_Calculate(pOneBuffer, pstuIdInfo->interval_s[2], pstuIdInfo->interval_e[2], pstuIdInfo->interval_s[0], pstuIdInfo->interval_e[0], pstuIdInfo->se_value[2],pstuIdInfo->se_value[0],fpCalPes );  /* 读出来的值  pIdAra->se_algorithm[0] */  		
			break;		
		case 7:
			TC_Calculate(pOneBuffer, pstuIdInfo->interval_s[2], pstuIdInfo->interval_e[2], pstuIdInfo->interval_s[1], pstuIdInfo->interval_e[1], pstuIdInfo->se_value[2],pstuIdInfo->se_value[1],fpCalPes );  /* 读出来的值  pIdAra->se_algorithm[0] */  		
			break;
		case 8:
			TC_Calculate(pOneBuffer, pstuIdInfo->interval_s[2], pstuIdInfo->interval_e[2], pstuIdInfo->interval_s[2], pstuIdInfo->interval_e[2], pstuIdInfo->se_value[2],pstuIdInfo->se_value[2],fpCalPes );  /* 读出来的值  pIdAra->se_algorithm[0] */  					
			break;
		
		default:
			*fpCalPes = (float)0;
#if DEBUH_UART1
			myprintf( "uRecRel:%d \r\n",uRecRel );
#endif
			break;
	}
	
#if DEBUH_UART1
	#if PRIVATE_UART1
	myprintf( "uRecRel:%d \r\n",uRecRel );
	#endif
#endif	
	
	return EXE_SUCCEED;
}

uint8_t uCalculateDensity( UINTE_DATA_TYPE* pstuIdInfo,ALGORITHM_DATA_TYPE* pstuAlg,float fPesponse,uint8_t uChildrenNum )
{
	/* 确定算法使用哪种算法返回结果 */	
	switch( pstuIdInfo->children_ufitt ){   /* 确定拟合算法 */
		case LINE_METHOD:
			LineMethod( pstuIdInfo,pstuAlg,fPesponse,uChildrenNum );
			break;
		case ID_LINE_METHOD:
			pstuAlforithmLineMethod( pstuIdInfo,pstuAlg,fPesponse,uChildrenNum );
			break;		
		case FOUR_ARGUMENT:
			pstuAlforithmFourArgument( pstuIdInfo,pstuAlg,fPesponse,uChildrenNum );				
			break;
		
		default:
			break;		
	}
	
#if DEBUH_UART1
	#if PRIVATE_UART1
	myprintf( "children_ufitt:%d formula_tc:%d \r\n",pstuIdInfo->children_ufitt,pstuIdInfo->children_formula_tc );
	#endif
#endif	
	
	return EXE_SUCCEED;
}

/* 四参数求浓度 */
uint8_t pstuAlforithmFourArgument( UINTE_DATA_TYPE* pstuIdInfo,ALGORITHM_DATA_TYPE* pstuAlg,float fPesponse,uint8_t uChildrenNum )
{
	double doutesta = 0;
	double doutestb = 0;
	float fTempResult = 0;
	
	if( 0==fPesponse ){                        /* x在四参数中不能为0 */
		fPesponse = 0.01;
	}
	
#if DEBUH_UART1		
	myprintf( "FourArgument \r\n" );
	myprintf( "para_a:%f \r\n",pstuIdInfo->children_para_a );
	myprintf( "para_b:%f \r\n",pstuIdInfo->children_para_b );
	myprintf( "para_c:%f \r\n",pstuIdInfo->children_para_c );
	myprintf( "para_d:%f \r\n",pstuIdInfo->children_para_d );			
#endif
	if( (0!=pstuIdInfo->children_para_a)&&(0!=pstuIdInfo->children_para_b)&&(0!=pstuIdInfo->children_para_c)&&(0!=pstuIdInfo->children_para_d) ){
		if( (0!=(fPesponse-pstuIdInfo->children_para_a))&&(0!=(pstuIdInfo->children_para_c-fPesponse)) ){
			doutesta = (double)(((fPesponse-pstuIdInfo->children_para_a) * pstuIdInfo->children_para_b)/(pstuIdInfo->children_para_c-fPesponse));
			doutestb = (double)(1/pstuIdInfo->children_para_d);					
#if DEBUH_UART1		
			myprintf( "para_numerator:%.4f \r\n",fPesponse-pstuIdInfo->children_para_a );
			myprintf( "para_denominator:%.4f  \r\n",pstuIdInfo->children_para_c-fPesponse );
			myprintf( "para_numerator:%.4f  \r\n",doutesta );
			myprintf( "para_denominator:%.4f  \r\n",doutestb );					
#endif
			if( (doutesta<0)||(doutestb<0) ){
//				doutesta = fabs( doutesta );  /* 取绝对值 */ doutestb = fabs( doutestb );  /* 取绝对值 */				
				if( fPesponse<=pstuIdInfo->children_pesponse[0] ){      /*//if( x<=g_IdMemory.limits_min ){ */							
					fTempResult = pstuIdInfo->children_limits_min;					
				}else{
					fTempResult = pstuIdInfo->children_limits_max;	     
				}
			}else{			
				fTempResult = (float)pow( doutesta,doutestb );		                    /* 四参数求浓度 */				
				fTempResult = fChildrenCoefficient( pstuIdInfo,fTempResult );           /* 样本系数求解 */											
			}		
			pstuAlforithmResult( pstuAlg,uChildrenNum,fTempResult );			        /* 将结果放到对应的项目中 */
		}else{
#if DEBUH_UART1		
			myprintf( "Error numerator denominator \r\n" );		
#endif
		}				
	}else{
#if DEBUH_UART1		
		myprintf( "Error a b c d \r\n" );		
#endif
	}
			
	return EXE_SUCCEED;
}

/* 直线方程求浓度 */	
uint8_t pstuAlforithmLineMethod( UINTE_DATA_TYPE* pstuIdInfo,ALGORITHM_DATA_TYPE* pstuAlg,float fPesponse,uint8_t uChildrenNum )
{
	float fTempResult = 0;
	
#if DEBUH_UART1		
	myprintf( "ID LineMethod children_para_a:%.4f children_para_b:%.4f\r\n",pstuIdInfo->children_para_a,pstuIdInfo->children_para_b );				
#endif
	
	if( 0!=pstuIdInfo->children_para_b ){
		fTempResult = (fPesponse-pstuIdInfo->children_para_a)/pstuIdInfo->children_para_b;    /* 直线方程求浓度 */			
		if( fTempResult<=0 ){                                                                 /* 结果不允许为负数 */
			fTempResult = 0.01;
		}
		fTempResult = fChildrenCoefficient( pstuIdInfo,fTempResult );                         /* 样本系数求解 */			
	}else{
		fTempResult = 0.01;
	}
	
	pstuAlforithmResult( pstuAlg,uChildrenNum,fTempResult );                                  /* 将结果放到对应的项目中 */	
	
	return EXE_SUCCEED;
}

/* 自动找ab求直线方程求浓度 */	
uint8_t LineMethod( UINTE_DATA_TYPE* pstuAlg,ALGORITHM_DATA_TYPE* pAra,float fTC,uint8_t uChildrenNum )
{
	uint8_t i = 0;
	LINE_QUATION* pstuMylinEqu = NULL;
	float fTempResult = 0;
//	uint8_t uResWave = 0;

	pstuMylinEqu = (LINE_QUATION* )calloc( 1,sizeof(LINE_QUATION) );
	if(NULL == pstuMylinEqu){
		return EXE_SUCCEED;  /* 定义错误码 */
	}
	
	pstuMylinEqu->a = 1;
	pstuMylinEqu->b = 1;
	pstuMylinEqu->c = 0;		
	
//	/* 需要修改为使用局部变量 *//* 直线方法使用 四参数法不使用 */		
//	uResWave = CalculateWave( &g_IdMemory,(uint32_t *)g_ADC_Buffer,sizeof(g_ADC_Buffer)/sizeof(uint32_t) ); 	
//	if( uResWave<2 ){
//		g_IdMemory.peak_num = 2;         /* 临时改变 确定有几个波峰 */			
//		g_IdMemory.s[0] = 0;
//		g_IdMemory.e[0] = 39;
//		g_IdMemory.s[1] = 39;
//		g_IdMemory.e[1] = 120;
//		
//#if DEBUH_UART1					
//		myprintf( "s1:%d e1:%d \r\n",g_IdMemory.s[0],g_IdMemory.e[0] );
//		myprintf( "s2:%d e2:%d \r\n",g_IdMemory.s[1],g_IdMemory.e[1] ); 		 
//#endif
//	}
	
	if( NULL!=pstuMylinEqu ){
		
		while( i<14 ){
			if( (pstuAlg->children_pesponse[i]<fTC)&&(pstuAlg->children_pesponse[i+1]>fTC) ){				
				pstuMylinEqu = SolveLineearEquation( pstuAlg->children_pesponse[i],pstuAlg->children_pesponse[i],pstuAlg->children_pesponse[i+1],pstuAlg->children_pesponse[i+1], pstuMylinEqu );			
				fTempResult = ((fTC*pstuMylinEqu->a)+pstuMylinEqu->c)/(-pstuMylinEqu->b);
				fTempResult = fChildrenCoefficient( pstuAlg,fTempResult );                         /* 样本系数求解 */	
#if DEBUH_UART1	
				myprintf( "pesponse~pesponse %d:%.4f %.4f \r\n",i,pstuAlg->children_pesponse[i],pstuAlg->children_pesponse[i+1] );
				myprintf( "a:%.4f b:%.4f c:%.4f \r\n",pstuMylinEqu->a,pstuMylinEqu->b,pstuMylinEqu->c );
#endif
				break;
			}	
			i++;
		}	
		if( 14==i ){
			fTempResult = 0.01;
		}			
	}
	
	pstuAlforithmResult( pAra,uChildrenNum,fTempResult );                              /* 将结果放到对应的项目中 */
	
	free( pstuMylinEqu );
	
	return EXE_SUCCEED;
}

/* 循环存储 */	
uint8_t uCirculateStorage( ID_Info* pIDData,UINTE_DATA_TYPE* pstuIdInfo,uint8_t* pfDensity,uint8_t uChildrenNum )
{
	GYK950E* ptestMyForm = NULL;
	ptestMyForm = calloc( 1,sizeof(GYK950E) );
	if( NULL==ptestMyForm ){
		return EXE_FAILED;
	}
	
#if DEBUH_UART1		
	#if PRIVATE_UART1
	myprintf( "history num:%d serial_num:%d\r\n",g_projectSerial.history_count,g_projectSerial.serial_num );
	#endif
#endif

	if( calendar.w_date!=g_projectSerial.rec_day ){
		g_projectSerial.serial_num = 0;
		g_projectSerial.rec_day = calendar.w_date; /* 记录当前天 */
		sprintf( (char *)g_projectSerial.serial_id,"%04d%02d%02d%04d",calendar.w_year,calendar.w_month,calendar.w_date,(g_projectSerial.serial_num+1) );    /* 流水号的编码规则日期加流水号 */		
	}else{
		sprintf( (char *)g_projectSerial.serial_id,"%04d%02d%02d%04d",calendar.w_year,calendar.w_month,calendar.w_date,(g_projectSerial.serial_num+1) );    /* 流水号的编码规则日期加流水号 */
	}
	
	if( pIDData->children_num==(uChildrenNum+1) ){
		g_projectSerial.serial_num++;               /* 存储一次加一次 */
	}
	
	if( (0<(g_projectSerial.history_count))&&((g_projectSerial.history_count)<STORAGE_DENSITY_MAX) ){	
		uStorageData( ptestMyForm,pIDData,pstuIdInfo,pfDensity,uChildrenNum );	/* 需要存储的数据装载 */	
		
		if( EXE_SUCCEED==SPI_Flash_Write_Page( (uint8_t *)ptestMyForm,(SPIFLASH_DENSITY_BASE_ADDR+((g_projectSerial.history_count)*SPIFLASH_PAGE_BASE_ADDR)),sizeof(GYK950E) ) ){
		}else{
#if DEBUH_UART1		
			myprintf( "FlashWriteError \r\n" );
#endif
		}
		
		g_projectSerial.history_count++;	
		if( STORAGE_DENSITY_MAX!=g_projectSerial.history_max ){
			g_projectSerial.history_max = g_projectSerial.history_count;
		}
	}else{
		uStorageData( ptestMyForm,pIDData,pstuIdInfo,pfDensity,uChildrenNum );	/* 需要存储的数据装载 */
		
		if( EXE_SUCCEED==SPI_Flash_Write_Page( (uint8_t *)ptestMyForm,SPIFLASH_DENSITY_BASE_ADDR,sizeof(GYK950E) ) ){
		}else{
#if DEBUH_UART1		
			myprintf( "FlashWriteError \r\n" );
#endif
		}
		
		g_projectSerial.history_count = 1;	
	}	
	
#if DEBUH_UART1	
#if PRIVATE_UART1		
	myprintf( "history num:%d serial_num:%d\r\n",g_projectSerial.history_count,g_projectSerial.serial_num );
#endif
#endif	
	
	/* 记录流水号 */
	if( EXE_SUCCEED==SPI_Flash_Write_Page( (uint8_t *)&g_projectSerial,SPIFLASH_SERIAL_BASE_ADDR,sizeof(g_projectSerial) ) ){ /* clear */
	}else{
#if DEBUH_UART1		
		myprintf( "FlashWriteError \r\n" );
#endif
	}
	
//	SPI_Flash_Read( (uint8_t *)&g_projectSerial,SPIFLASH_SERIAL_BASE_ADDR,sizeof(g_projectSerial) );
//#if DEBUH_UART1			
//	myprintf( "history num:%d serial_num:%d\r\n",g_projectSerial.history_count,g_projectSerial.serial_num );
//#endif		

	if( GY_K950E_ON==gp_stuConfigFile->uPrintfOnOff ){		/* 打印测试结果数据 */		
		GyK950ePrintForm( ptestMyForm );
	}else{
		//GyK950ePrintTest();   //打印机测试页
	}
	
	if( NULL!=ptestMyForm ){
		free( ptestMyForm );
	}
	
	return EXE_SUCCEED;
}

/* sprintf转换float数据有危险 char strff[255] 不能设置太小 */
uint8_t uDisplayDensity( ID_Info* pIDData,UINTE_DATA_TYPE* pstuIdInfo,ALGORITHM_DATA_TYPE* pAra,uint8_t uChildrenNum,USER_REFERRENCE* puRefTemp )
{
	float fTempResult = 0;
	uint8_t uStrLen = 0;
	char strff[255] = {0};	
		
	switch( uChildrenNum ){
		case 0:
			fTempResult = pAra->result1;
			break;
		case 1:
			fTempResult = pAra->result2;
			break;
		case 2:
			fTempResult = pAra->result3;
			break;
		
		default:
			break;
	}
	
	memset( strff,0,sizeof(strff) );		
	if( pstuIdInfo->children_limits_min<pstuIdInfo->children_limits_max ){
		
		if( fTempResult<=pstuIdInfo->children_limits_min ){	
			if( 0>=pstuIdInfo->children_limits_min ){
				sprintf( strff,"%c%.2f",'<',0.01 );                                        /* 小于最小值 */
			}else{
//				sprintf( strff,"%c%.2f",'<',pstuIdInfo->children_limits_min );             /* 小于最小值 */
				sprintf( strff,"%c%.2f",' ',pstuIdInfo->children_limits_min+0.01 );        /* 最小值 */
			}
		}else if( fTempResult>=pstuIdInfo->children_limits_max ){                          
			sprintf( strff,"%c%.2f",'>',pstuIdInfo->children_limits_max );                 /* 大于最大值 */
		}else{
#if USER_RAND			
			fTempResult = fUseRandCondition( g_stuUserMoreInfo.user_name,fTempResult );    /* 根据姓名算浓度 */
#endif			
			uChildrenReferenceStorage( strff,fTempResult,uChildrenNum,puRefTemp );                   /* 根据参考范围算 */
		}
	}else{	
#if USER_RAND			
		fTempResult = fUseRandCondition( g_stuUserMoreInfo.user_name,fTempResult );        /* 根据姓名算浓度 */
#endif			                                                                           
		uChildrenReferenceStorage( strff,fTempResult,uChildrenNum,puRefTemp );                       /* 根据参考范围算 */
	}
	
	uStrLen = strlen( (const char*)strff );
	
	if( uStrLen<DENSITY_ARR_SIZE ){   /* 此处需要优化 */		
		switch( uChildrenNum ){
			case 0:
				uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,MAIN_DENSITY_DIS1_CON_ID,(uint8_t *)strff );	
				break;
			case 1:
				uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,MAIN_DENSITY_DIS2_CON_ID,(uint8_t *)strff );	
				break;
			case 2:
				uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,MAIN_DENSITY_DIS3_CON_ID,(uint8_t *)strff );	
				break;
		}
		
		/* 存储数据并打印 */
		uCirculateStorage( pIDData,pstuIdInfo,(uint8_t *)strff,uChildrenNum );
	}else{
#if DEBUH_UART1	
		myprintf( "Density calculation error \r\n" );
#endif	
	}	
	
	return EXE_SUCCEED;
}

uint8_t uChildrenReferenceStorage( char *pStrff,float fDensity,uint8_t uChildren,USER_REFERRENCE* puRefTemp )
{	
	switch( uChildren ){
		case 0:
			uChildrenReferenceAnalyse( pStrff,fDensity,puRefTemp->fuser_00_limits_min,puRefTemp->fuser_00_limits_max);
			break;
		case 1:
			uChildrenReferenceAnalyse( pStrff,fDensity,puRefTemp->fuser_01_limits_min,puRefTemp->fuser_01_limits_max);
			break;
		case 2:
			uChildrenReferenceAnalyse( pStrff,fDensity,puRefTemp->fuser_02_limits_min,puRefTemp->fuser_02_limits_max);
			break;
	}
	
	return EXE_SUCCEED;
}

uint8_t uChildrenReferenceAnalyse( char *pStrff,float fDensity,float fLimitsMin,float fLimitsMax )
{
	if( (0!=fLimitsMin)&&((0==fLimitsMax)) ){
		if( fDensity>fLimitsMin ){
			sprintf( (char *)pStrff,"%c%.2f",' ',fDensity );
		}else{
			sprintf( (char *)pStrff,"%.2f%c%c",fDensity,'\xa1','\xfd' );    /* 下降趋势 */
		}
	}else if( (0==fLimitsMin)&&((0!=fLimitsMax)) ){
		if( fDensity>fLimitsMax ){
			sprintf( (char *)pStrff,"%.2f%c%c",fDensity,'\xa1','\xfc' );    /* 上升趋势 */
		}else{
			sprintf( (char *)pStrff,"%c%.2f",' ',fDensity );
		}
	}else{
		if( fLimitsMin<fLimitsMax){
			if( fLimitsMin>fDensity ){						
				sprintf( (char *)pStrff,"%.2f%c%c",fDensity,'\xa1','\xfd' );    /* 下降趋势 */
			}else if( fLimitsMax<fDensity ){
				sprintf( (char *)pStrff,"%.2f%c%c",fDensity,'\xa1','\xfc' );    /* 上升趋势 */
			}else{
				sprintf( (char *)pStrff,"%c%.2f",' ',fDensity );
			}
		}else{
			sprintf( (char *)pStrff,"%c%.2f",' ',fDensity );
		}
	}
	
	return EXE_SUCCEED;
}

//uint8_t uChildrenReferenceStorage( char *pStrff,float fDensity,uint8_t uChildren )
//{	
//	switch( uChildren ){
//		case 0:
//			if( g_stuUserReference.fuser_00_limits_min<g_stuUserReference.fuser_00_limits_max){
//				if( g_stuUserReference.fuser_00_limits_min>fDensity ){						
//					sprintf( (char *)pStrff,"%.2f%c%c",fDensity,'\xa1','\xfd' );    /* 下降趋势 */
//				}else if( g_stuUserReference.fuser_00_limits_max<fDensity ){
//					sprintf( (char *)pStrff,"%.2f%c%c",fDensity,'\xa1','\xfc' );    /* 上升趋势 */
//				}else{
//					sprintf( (char *)pStrff,"%c%.2f",' ',fDensity );
//				}
//			}else{
//				sprintf( (char *)pStrff,"%c%.2f",' ',fDensity );
//			}
//			break;
//		case 1:
//			if( g_stuUserReference.fuser_01_limits_min<g_stuUserReference.fuser_01_limits_max){
//				if( g_stuUserReference.fuser_01_limits_min>fDensity ){						
//					sprintf( (char *)pStrff,"%.2f%c%c",fDensity,'\xa1','\xfd' );    /* 下降趋势 */
//				}else if( g_stuUserReference.fuser_01_limits_max<fDensity ){
//					sprintf( (char *)pStrff,"%.2f%c%c",fDensity,'\xa1','\xfc' );    /* 上升趋势 */
//				}else{
//					sprintf( (char *)pStrff,"%c%.2f",' ',fDensity );
//				}
//			}else{
//				sprintf( (char *)pStrff,"%c%.2f",' ',fDensity );
//			}
//			break;
//		case 2:
//			if( g_stuUserReference.fuser_02_limits_min<g_stuUserReference.fuser_02_limits_max){
//				if( g_stuUserReference.fuser_02_limits_min>fDensity ){						
//					sprintf( (char *)pStrff,"%.2f%c%c",fDensity,'\xa1','\xfd' );    /* 下降趋势 */
//				}else if( g_stuUserReference.fuser_02_limits_max<fDensity ){
//					sprintf( (char *)pStrff,"%.2f%c%c",fDensity,'\xa1','\xfc' );    /* 上升趋势 */
//				}else{
//					sprintf( (char *)pStrff,"%c%.2f",' ',fDensity );
//				}
//			}else{
//				sprintf( (char *)pStrff,"%c%.2f",' ',fDensity );
//			}
//			break;
//	}
//	
//	return EXE_SUCCEED;
//}

float fChildrenCoefficient( UINTE_DATA_TYPE* pstuIdInfo,float fPesponse )
{
	if( EN_ON==gp_stuConfigFile->uCutEnCu ){
		if( 0==strncmp((const char *)"Whole  blood",(const char *)g_uSampleType,sizeof(g_uSampleType)) ){
#if DEBUH_UART1	
			myprintf( "sample_coefficient2:%.4f %.4f \r\n",pstuIdInfo->children_sample_coefficient[1],fPesponse );
#endif	
			if( 0!=pstuIdInfo->children_sample_coefficient[1] ){				
				fPesponse = fPesponse * pstuIdInfo->children_sample_coefficient[1];
			}
		}else if( 0==strncmp((const char *)"Serum/Plasma",(const char *)g_uSampleType,sizeof(g_uSampleType)) ){				
#if DEBUH_UART1	
			myprintf( "sample_coefficient1:%.4f %.4f \r\n",pstuIdInfo->children_sample_coefficient[0],fPesponse );
#endif	
			if( 0!=pstuIdInfo->children_sample_coefficient[0] ){				
				fPesponse = fPesponse * pstuIdInfo->children_sample_coefficient[0];
			}
		}else{
#if DEBUH_UART1	
			myprintf( "sample_coefficient4:%.4f %.4f \r\n",pstuIdInfo->children_sample_coefficient[3],fPesponse );
#endif	
			if( 0!=pstuIdInfo->children_sample_coefficient[3] ){				
				fPesponse = fPesponse * pstuIdInfo->children_sample_coefficient[3];
			}	
		}
	}else{
		if( 0==strncmp((const char *)"全血",(const char *)g_uSampleType,sizeof(g_uSampleType)) ){
#if DEBUH_UART1	
			myprintf( "sample_coefficient2:%.4f %.4f \r\n",pstuIdInfo->children_sample_coefficient[1],fPesponse );
#endif	
			if( 0!=pstuIdInfo->children_sample_coefficient[1] ){				
				fPesponse = fPesponse * pstuIdInfo->children_sample_coefficient[1];
			}
		}else if( 0==strncmp((const char *)"血清/血浆",(const char *)g_uSampleType,sizeof(g_uSampleType)) ){				
#if DEBUH_UART1	
			myprintf( "sample_coefficient1:%.4f %.4f \r\n",pstuIdInfo->children_sample_coefficient[0],fPesponse );
#endif	
			if( 0!=pstuIdInfo->children_sample_coefficient[0] ){				
				fPesponse = fPesponse * pstuIdInfo->children_sample_coefficient[0];
			}
		}else{
#if DEBUH_UART1	
			myprintf( "sample_coefficient4:%.4f %.4f \r\n",pstuIdInfo->children_sample_coefficient[3],fPesponse );
#endif	
			if( 0!=pstuIdInfo->children_sample_coefficient[3] ){				
				fPesponse = fPesponse * pstuIdInfo->children_sample_coefficient[3];
			}	
		}
	}
	
	return fPesponse;
}

uint8_t pstuAlforithmResult( ALGORITHM_DATA_TYPE* pstuAlg,uint8_t uChildrenNum,float fVaule )
{	
	
	if( (0<=fVaule)&&(fVaule<=LINEAR_RANGE_MAX) ){

	}else{
#if DEBUH_UART1	
		myprintf( "LINEAR_RANGE_MAX ERROE \r\n" );
#endif	
		return EXE_FAILED;
	}
	
#if DEBUH_UART1	
	myprintf( "result:%.2f \r\n",fVaule );
#endif	
	
	switch( uChildrenNum ){
		case 0:
			pstuAlg->result1  = fVaule;       /* 暂时这样处理 */
			break;
		case 1:
			pstuAlg->result2  = fVaule;       /* 暂时这样处理 */
			break;								
		case 2:
			pstuAlg->result3  = fVaule;       /* 暂时这样处理 */
			break;
		default:
			break;
	}
	
	return EXE_SUCCEED;
}

LINE_QUATION* SolveLineearEquation( float x1,float y1,float x2,float y2,LINE_QUATION* stuLinEquation )
{
	stuLinEquation->a = y2-y1;
	stuLinEquation->b = x1-x2;
	stuLinEquation->c = x2*y1-x1*y2;
	
	return stuLinEquation;
}

/* 计算波峰区间 */
uint8_t CalculateWave( ID_Info* pstuAlg,uint32_t* uArr ,uint16_t uSize )
{
	uint16_t i = 0;
	uint8_t uResWave = 0;
	uint8_t uResAvg = 0;
	uint8_t uResStart = 0;
	//uint32_t uResTemp = 0;
//	uint16_t uResS[5] = {0},uResE[5] = {0};
	pstuAlg->peak_num = 0;

	
	pstuAlg->interval_s[pstuAlg->peak_num] = i;	
	for( i=0;i<uSize-1;i++ )
	{		
		if( 0==uResWave ){
			if( ((int )*(uArr+i+1)-(int )*(uArr+i))>D_VALUE_INTERVAL ){
				uResAvg++;
				if( uResAvg>CONTINUOUS_NUM){
					if( 0==uResStart ){					
						uResStart = 1;
					}else{
						pstuAlg->interval_e[pstuAlg->peak_num] = i-5;					
						uResStart = 0;
						if( pstuAlg->peak_num<4 ){
							pstuAlg->peak_num++;
						}
						pstuAlg->interval_s[pstuAlg->peak_num] = i-5;
					}
#if DEBUH_UART1	
					myprintf( "i2:%d %d \r\n",i,*(uArr+i+1)-*(uArr+i) );
#endif					
					uResWave = 1;
					uResAvg = 0;
				}
			}
		}else if( 1==uResWave ){
			if( ((int )*(uArr+i)-(int )*(uArr+i+1))>D_VALUE_INTERVAL ){
				uResAvg++;
				if( uResAvg>CONTINUOUS_NUM){
#if DEBUH_UART1	
					myprintf( "i3:%d %d \r\n",i,*(uArr+i)-*(uArr+i+1) );
#endif	
					uResWave = 0;	
					uResWave = 0;
				}
			}				
		}
	}
	pstuAlg->interval_e[pstuAlg->peak_num] = i;	
	
	pstuAlg->peak_num = pstuAlg->peak_num+1;

	return pstuAlg->peak_num;
}

uint8_t uClearItemData( void )
{
	uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,MAIN_DENSITY_DIS1_CON_ID,(uint8_t *)"" );	
	uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,MAIN_DENSITY_DIS2_CON_ID,(uint8_t *)"" );		
	uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,MAIN_DENSITY_DIS3_CON_ID,(uint8_t *)"" );	
	uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,NAME_DENSITY1_DIS_CON_ID,(uint8_t *)"" );
	uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,NAME_DENSITY2_DIS_CON_ID,(uint8_t *)"" );
	uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,NAME_DENSITY3_DIS_CON_ID,(uint8_t *)"" );
	
	uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,MAIN_DENSITY_DIS12_CON_ID,(uint8_t *)"" );	            /* 显示测试条码 */
	uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,MAIN_DENSITY_DIS13_CON_ID,(uint8_t *)"" );
	
	return EXE_SUCCEED;
}

uint8_t uAutoQuckTest( void )
{
//	OS_ERR err = OS_ERR_NONE;
//	char strff[32] = {0};	
//	uint16_t i = 0;
//	uint16_t uTestTimeStart = 0;
//	uint16_t uTestTimeEnd = 0;
//	uint8_t uRecError = 0;
//	uint16_t j = 0;
//	
//	if( (1<=g_uAutoTestTimes)&&(g_uAutoTestTimes<=9999) ){
////		if( EXE_FAILED==uSemclear( (OS_SEM*)&g_ForceExit ) ){
////		}
//		for( i=g_uAutoTestTimes;i>0;i-- ){	
//#if DEBUH_UART1	
//			uTestTimeStart = OSTimeGet(&err);
//			myprintf( "g_uAutoTestTimes:%d \r\n",i);
//#endif
//			sprintf( (char *)strff,"%d",i-1 );		
//					
//			OSTimeDlyHMSM(0, 0, 0, 100,OS_OPT_TIME_HMSM_STRICT,&err);                                            /* 延时2S */
//			uRecError = AcquisitionQuickSystem( QUICK_RESULT_PAGE );                                             /* 执行快速测试 */
//			if(EXE_SUCCEED!=uRecError) {                                                                         /* 执行快速测试 */
//#if DEBUH_UART1	
//				myprintf( "ErrAutoTest\r\n");
//#endif
//				return EXE_FAILED;//uRecError = EXE_FAILED;
//			}
//			
//			uConfirmPage( TJC_AUTOTEST_PAGE );                                                                   /* 确定自动测试页 */			
//			OSTimeDlyHMSM(0, 0, 0, 100,OS_OPT_TIME_HMSM_STRICT,&err);                                            /* 延时1S */
//			uTjc4832tSetLableValue( TJC_AUTOTEST_PAGE,AUTOTEST_ID_NUM,(uint8_t *)strff );                        
//			OSTimeDlyHMSM(0, 0, 2, 0,OS_OPT_TIME_HMSM_STRICT,&err);                                              /* 延时3S */
//			
//			for( j=0;j<40;j++ ){
//				if( 0==BSP_ReadPin(READCARD_DEC_CONTROL_PORT,READCARD_DEC_CONTROL_PIN) ){            /* 未到位是读回来是1 到位读回来是0 */
//					if( 0==BSP_ReadPin(READCARD_DEC_CONTROL_PORT,READCARD_DEC_CONTROL_PIN) ){ 						
//						uConfirmPage( TJC_AUTOTEST_PAGE );                                                                   /* 确定自动测试页 */			
//						OSTimeDlyHMSM(0, 0, 0, 100,OS_OPT_TIME_HMSM_STRICT,&err);                                            /* 延时1S */
//						uTjc4832tSetLableValue( TJC_AUTOTEST_PAGE,AUTOTEST_ID_NUM,(uint8_t *)strff );     
//						OSTimeDlyHMSM(0, 0, 2, 0,OS_OPT_TIME_HMSM_STRICT,&err);                                              /* 延时3S */
//						break;
//					}
//				}else{
////					OSSemPend( (OS_SEM *)&g_ForceExit, 50,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	     /* 退出信号量 */
//					if( OS_ERR_NONE==err ){
//#if DEBUH_UART1	
//						myprintf( "ExitAutoTest\r\n");
//#endif		
//						return EXE_FAILED;	
//					}
//					
//					if( SWITCH_MIC_ON==gp_stuConfigFile->uSwitchOnOff ){
//						if(j>=40-1){
//							uTjc4832tSetPage( TJC_WARN_PAGE );  
//							uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Card Overtime " );
//							return EXE_FAILED;
//						}
//					}
//				}
//			}	
//			
//#if DEBUH_UART1	
//			uTestTimeEnd = OSTimeGet(&err);
//			myprintf( "Time:%d \r\n",uTestTimeEnd-uTestTimeStart );
//#endif
//		}
//	}else{
//		uTjc4832tSetPage( TJC_WARN_PAGE );                                                                       /* 设置为警告页 */		
//		if( EN_ON==gp_stuConfigFile->uCutEnCu ){
//			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Range: 1-9999 " );
//		}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
//			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"范围: 1-9999 " );
//		}else{
//			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Invalid" );	             //
//		}	
//		uBuzzerTimes( BUZZER_ONE_TIME );
//	}
	
	return EXE_SUCCEED;
}

float fUseRandCondition( uint8_t* upCondStr,float fTempData )
{
	uint32_t uRandNum = 0;
	
	float fTempNum = 0;
	
	if( 0==strncmp((const char *)"pct",(const char *)upCondStr,10) ){
		uRandNum = uMyRand();
		fTempNum = (float)(((float)uRandNum)/((float)100));
	
		return fTempNum;
	}else{
		return fTempData;
	}
}

uint8_t uForceAssociateDensity( void )
{
//	ID_Info* pIDData = &g_IdMemory;                                                                                    /* ID公共数据访问指针 */
//	ALGORITHM_DATA_TYPE* pAlgorithmData = &g_stuMyAlgorithm;                                                           /* 浓度结果公共数据访问指针 */
//	uint8_t uRecIdCardNum = 0;        
//	uint8_t uRecError = 0;
//																													   
//	uConfirmPage( TJC_QUICK_RESULT_PAGE );                                                                             /* 确认是测试结果显示页 */

//	uTjc4832tTouchEnable( TJC_TOUCH_OFF );                                                                             /* 整页关闭触摸 */ 
//	uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,MAIN_DENSITY_DIS11_CON_ID,(uint8_t *)pIDData->barcode );	           /* 显示项目条码 */		
//	
//	uRecIdCardNum = uGetIdCountValue();                                                                                /* 得到当前ID卡的序号 */
//	uRecError = Result_Calculate( g_ADC_Buffer,pIDData,pAlgorithmData,uRecIdCardNum );		                           /* 算法处理 */
//	if( EXE_SUCCEED==uRecError ){
//		uTjc4832tSetProgressbarValue( TJC_QUICK_RESULT_PAGE,MAIN_PROGRESS_DIS_CON_ID,MAIN_PROGRESS5_VALUE );   /* 进度条5 */				
//#if DEBUH_UART1	
//		myprintf( "Result_Calculate:\r\n" );
//		myprintf( "result1:%.4f \r\n",pAlgorithmData->result1 );
//		myprintf( "result2:%.4f \r\n",pAlgorithmData->result2 );
//		myprintf( "result3:%.4f \r\n",pAlgorithmData->result3 );
//#endif		
//	}
//	
//	uTjc4832tTouchEnable( TJC_TOUCH_ON );                                                                              /* 整页打开触摸 */
	
	return EXE_SUCCEED;
}

uint8_t uGetFluorescenceBarValue( void )
{
//	char strff[32] = {0};
//	uint8_t uRecError = 0;
//	uint32_t uRecFluoresMax = 0;
//	int16_t iRecFluoresMaxIndex = 0;
//	int16_t iRecFistThoughIndex = 0;
//	uint16_t uRecFistThough = 0;
//	uint32_t* puArrTemp = &g_ADC_Buffer[0];
//	uint16_t* puArrBarCode = &g_ADC_BarCode[0];
//	
//	memset( g_ADC_Buffer,0,sizeof(g_ADC_Buffer) );                                                                /* 清空荧光采集数据 */
//	memset( g_ADC_BarCode,0,sizeof(g_ADC_BarCode) );                                                              /* 清空条码AD数据 */	
//			
//	if( (g_uElectricValue<=VOLTAGE_THRESHOLD_PERCENTAGE) ){                                                       /* 电量过低不允许快速测试 */
//		uTjc4832tSetPage( TJC_WARN_PAGE );                                                                      /* 设置为强制警告页 */
//		if( EN_ON==gp_stuConfigFile->uCutEnCu ){
//			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Low power" );	             //
//		}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
//			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"低电量" );	             //
//		}else{
//			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Invalid" );	             //
//		}	
//                                                                 
//		return EXE_FAILED;                                                                                 
//	} 
//	
//	uFluorescenceLight( FLUORESCENCE_ON );                                                                        /* 打开 CTRL_LED灯	 */
//	uRecError = uCollectFluorescenceValueBarValue( puArrTemp,puArrBarCode );                                      /* 荧光和条码AD值采集 */
//	uFluorescenceLight( FLUORESCENCE_OFF );                                                                       /* 关闭 CTRL_LED灯	 */
//	if( EXE_SUCCEED!=uRecError ){                                                                                 
//		return uRecError;                                                                                         
//	}                                                                                                             
//																				                                  
//	line_smoth_slid( puArrTemp,SCAN_LENGTH );                                                                     /* 平滑光学AD数据 */
//	vbar_line_smoth_slid( puArrBarCode,BARVODE_LENGTH );                                                          /* 平滑条码数据 */
//	
//	/* 找到荧光值最大的点 */
//	uGetFluoerscenceMaxValue( puArrTemp,SCAN_LENGTH,&iRecFluoresMaxIndex,&uRecFluoresMax );	
//	/* 找到第一个波谷值 */
//	uGetFirstTroughValue( puArrBarCode,BARVODE_LENGTH,&iRecFistThoughIndex,&uRecFistThough );
//#if DEBUH_UART1	
////	#if PRIVATE_UART1
//	myprintf( "iRecFluoresMaxIndex:%d uRecFluoresMax:%d iRecFistThoughIndex:%d uRecFistThough:%d  \r\n",iRecFluoresMaxIndex,uRecFluoresMax,iRecFistThoughIndex,uRecFistThough );
////	#endif	
//#endif	
//	
//	iRecFluoresMaxIndex = (int)((float)iRecFluoresMaxIndex-(((float)MAPID_ADDRB-(float)gp_stuConfigFile->uLanReferValue)*(float)gp_stuConfigFile->fCoeff));        /* 计算出偏移值 */
//	
//	iRecFistThoughIndex = BAR_REF_DIT-iRecFistThoughIndex;                                                                /* 计算出偏移值 条码起始点固定为435 */
//	
//	sprintf( (char *)strff,"Ad %d:%d && Bar %d:%d",iRecFluoresMaxIndex,uRecFluoresMax,iRecFistThoughIndex,uRecFistThough );
//	uConfirmPage( TJC_AUTOTEST_PAGE );                                                                            /* 确定自动测试页 */
//	uTjc4832tSetLableValue( TJC_AUTOTEST_PAGE,AUTOTEST_ID_TXT_DIS,(uint8_t *)strff );                              
//																								                   
//	uResetMotorInteriorStauts(UI_N_PROMPT);                                                                       /* 电机传感器复位 最后开始 */	
	
	return EXE_SUCCEED;
}

uint8_t uGetFluoerscenceMaxValue( const uint32_t* puArrTemp,int len,int16_t* piFluoerMaxIndex,uint32_t* puFluoerMax )
{
	uint32_t i = 0;
	uint32_t* puArrTempFluoer = NULL;
	
	puArrTempFluoer = (uint32_t *)calloc( len,sizeof(uint32_t));
	if( NULL==puArrTempFluoer ){
		return EXE_FAILED;
	}
	
	memcpy( puArrTempFluoer,puArrTemp,len*sizeof(uint32_t) );
#if STORT_STL
	qsort(Buffer, len, sizeof(int), cmpfuncintmax);  /*排序函数*/
#else	
	InsertionSortUint32_t( (uint32_t *)puArrTempFluoer,(SCAN_LENGTH),SORT_MAX );
#endif
	
	*puFluoerMax = puArrTempFluoer[0];
	
	if( NULL!=puArrTempFluoer ){
		free( puArrTempFluoer );
	}
	
	if( 0!=(*puFluoerMax) ){
		for( i=0;i<len;i++ ){
			if( *(puArrTemp+i)==(*puFluoerMax) ){
				*piFluoerMaxIndex = i+1;
				return EXE_SUCCEED;
			}
		}
	}else{
		return EXE_FAILED;
	}
	
	return EXE_SUCCEED;
}

///* 如果条码发现不匹配 自动查找库 */	
//uint8_t uBarSearchIDCard( uint8_t *uArrBarCodeTemp,const char *uArrBarCode )
//{
//	uint8_t i = 0;
//	uint8_t uRecBarError = 0;
//	uint8_t uRecIdCardNum = 0;
//	ID_Info* pIDData = &g_IdMemory;                                                                       /* ID公共数据访问指针 */	
//	
//	if( barcompare((const char *)uArrBarCodeTemp,(const char *)uArrBarCode,sizeof(uArrBarCode)) ){		/* 在什么情况下提示条码不正确 */				
//		for( i=0;i<g_projectSerial.uid_max;i++ ){
//			pIDData = uReadStoreIdItem( i );					
//			if( NULL!=pIDData ){
//				/* ID卡数据校验 */
//				//uReadStoreIdItem( uGetIdCountValue() );     /* 重新读取 */					
//				if( EXE_FAILED==uVerifyId( pIDData ) ){
//					uTjc4832tSetPage( TJC_WARN_PAGE );        /*设置为强制警告页*/
//					if( EN_ON==gp_stuConfigFile->uCutEnCu ){
//						uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Invalid ID data" );	     //ID数据错误
//					}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
//						uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"无效ID卡" );	             //ID数据错误
//					}else{
//						uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Invalid" );	             //ID数据错误
//					}
//					continue;           
//				}
//				uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,MAIN_DENSITY_DIS11_CON_ID,(uint8_t *)pIDData->barcode );	/* 显示项目条码 */
//				
//				if( NULL==uBarTransition( pIDData,uArrBarCodeTemp ) ){
////					memset( uArrBarCodeTemp,0,sizeof(uArrBarCodeTemp) );
//				}				
//			}
//			if( (barcompare((const char *)uArrBarCodeTemp,(const char *)uArrBarCode,sizeof(uArrBarCode))) ){
//				if( (i>=(g_projectSerial.uid_max-1)) ){							
////							uTjc4832tSetLableValue( TJC_QUICK_RESULT_PAGE,MAIN_DENSITY_DIS13_CON_ID,(uint8_t *)"Bar Error" );	//条码不正确
//					uRecBarError = EXE_FAILED;
//				}
//			}else{
//				uRecIdCardNum = i;
//				break;
//			}
//		}			
//	}else{
//		uRecIdCardNum = uGetIdCountValue();
//	}
//	
//	return EXE_SUCCEED;
//}


