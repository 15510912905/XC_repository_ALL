/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

				嵌入式开发平台——任务定义

  -------------------------------------------------------
   文 件 名   : Task.c
   版 本 号   : V1.0.0.0
   作    者   : ZR
   生成日期   : 2020年10月01日
   功能描述   : 定义并行任务。
   依赖于     : uC/OS-III V3.0.03
   注         ：该文件不依赖于硬件电路。 
********************************************************/
 
#include "Task.h"
/*--------------------------------------------------------------*/
//UCOSIII中以下优先级用户程序不能使用，ALIENTEK
//将这些优先级分配给了UCOSIII的5个系统内部任务
//优先级0：中断服务服务管理任务 OS_IntQTask()
//优先级1：时钟节拍任务 OS_TickTask()
//优先级2：定时任务 OS_TmrTask()
//优先级OS_CFG_PRIO_MAX-2：统计任务 OS_StatTask()
//优先级OS_CFG_PRIO_MAX-1：空闲任务 OS_IdleTask()
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/*定义任务堆栈*/
OS_TCB StartTaskTCB;                                                          //任务控制块	
CPU_STK START_TASK_STK[START_STK_SIZE];                                       //任务堆栈
                                                                                                                                    
OS_TCB Led0TaskTCB;                                                           //任务控制块
static __align(8) CPU_STK LED0_TASK_STK[LED0_STK_SIZE];                       //任务堆栈	
                                                                              
OS_TCB TaskPowerManageTCB;                                                    //任务控制块
static __align(8) CPU_STK POWER_MANAGE_TASK_STK[POWER_MANAGESTK_SIZE];        //任务堆栈	

OS_TCB TaskUserDisplayTCB;                                                    //任务控制块
static __align(8) CPU_STK USER_DISPLAY_TASK_STK[USER_DISPLAY_SIZE];           //任务堆栈

OS_TCB TaskTjc4832tInterfaceTCB;                                              //任务控制块
static __align(8) CPU_STK TJC_INTERFACE_TASK_STK[TJC_INTERFACE_SIZE];          //任务堆栈

OS_TCB TaskReadIDCardTCB;                                                     //任务控制块
static __align(8) CPU_STK READ_ID_CARD_TASK_STK[READ_ID_CARD_SIZE];           //任务堆栈

OS_TCB TaskLogInTCB;                                                          //任务控制块
static __align(8) CPU_STK LOGIN_TASK_STK[LOGIN_SIZE];                         //任务堆栈

OS_TCB TaskUpdataTimeTCB;                                                     //任务控制块
static __align(8) CPU_STK UPDATA_TASK_STK[UPDATA_SIZE];                       //任务堆栈

OS_TCB TaskPowerOnTCB;                                                        //任务控制块
static __align(8) CPU_STK POWER_ON_TASK_STK[POWER_ON_SIZE];                   //任务堆栈

OS_TCB TaskWifiReceiveTCB;                                                    //任务控制块
static __align(8) CPU_STK WIFI_RECEIVE_TASK_STK[WIFI_RECEIVE_SIZE];           //任务堆栈

OS_TCB TaskWifiSendTCB;                                                       //任务控制块
static __align(8) CPU_STK WIFI_SEND_TASK_STK[WIFI_SEND_SIZE];                 //任务堆栈

OS_TCB TaskBackShutDownTCB;                                                   //任务控制块
static __align(8) CPU_STK BACK_SHUTDOWN_TASK_STK[BACK_SHUTDOWN_SIZE];         //任务堆栈

OS_TCB Led1TaskTCB;                                                           //任务控制块
static __align(8) CPU_STK LED1_TASK_STK[LED1_STK_SIZE];                       //任务堆栈	

#if TEST_STACK_ON
OS_TCB	FloatTaskTCB;                                                         //任务控制块
static __align(8) CPU_STK FLOAT_TASK_STK[FLOAT_STK_SIZE];                     //任务堆栈
#endif
/*--------------------------------------------------------------*/

/*定义全局变量*/

/*----------------------------------------------------定义任务*/
/* 初始任务 开始任务函数 */
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//统计任务                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//如果使能了测量中断关闭时间
    CPU_IntDisMeasMaxCurReset();	
#endif
	
#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	//使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,4,&err);  
#endif		

	OS_CRITICAL_ENTER();	//进入临界区
#if TEST_STK_SIZE
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		  //挂起开始任务
	OSTaskDel((OS_TCB*)&StartTaskTCB,&err);		          //删除开始任务	
#else
	bFuncIFP300UcosValInit();                             /* 创建USOS各种变量 */	

	//创建LED0任务
	OSTaskCreate((OS_TCB 	* )&Led0TaskTCB,		
				 (CPU_CHAR	* )"led0 task", 		
                 (OS_TASK_PTR )led0_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )LED0_TASK_PRIO,     
                 (CPU_STK   * )&LED0_TASK_STK[0],	
                 (CPU_STK_SIZE)LED0_STK_SIZE/10,	
                 (CPU_STK_SIZE)LED0_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);				
				 
	//创建电源管理任务
	OSTaskCreate((OS_TCB 	* )&TaskPowerManageTCB,		
				 (CPU_CHAR	* )"Power Manage task", 		
                 (OS_TASK_PTR )TaskPowerManage, 			
                 (void		* )0,					
                 (OS_PRIO	  )POWER_MANAGESTKTASK_PRIO,     	
                 (CPU_STK   * )&POWER_MANAGE_TASK_STK[0],	
                 (CPU_STK_SIZE)POWER_MANAGESTK_SIZE/10,	
                 (CPU_STK_SIZE)POWER_MANAGESTK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);	
				 
	//UI用户显示界面
	OSTaskCreate((OS_TCB 	* )&TaskUserDisplayTCB,		
				 (CPU_CHAR	* )"User Display", 		
                 (OS_TASK_PTR )TaskUserDisplay, 			
                 (void		* )0,					
                 (OS_PRIO	  )USER_DISPLAY_PRIO,     	
                 (CPU_STK   * )&USER_DISPLAY_TASK_STK[0],	
                 (CPU_STK_SIZE)USER_DISPLAY_SIZE/10,	
                 (CPU_STK_SIZE)USER_DISPLAY_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);
				 
	//显示屏通讯任务函数
	OSTaskCreate((OS_TCB 	* )&TaskTjc4832tInterfaceTCB,		
				 (CPU_CHAR	* )"Tjc Interface", 		
                 (OS_TASK_PTR )TaskTjc4832tInterface, 			
                 (void		* )0,					
                 (OS_PRIO	  )TJC_INTERFACE_PRIO,     	
                 (CPU_STK   * )&TJC_INTERFACE_TASK_STK[0],	
                 (CPU_STK_SIZE)TJC_INTERFACE_SIZE/10,	
                 (CPU_STK_SIZE)TJC_INTERFACE_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);

	//读ID卡任务函数
	OSTaskCreate((OS_TCB 	* )&TaskReadIDCardTCB,		
				 (CPU_CHAR	* )"ReadIDCard", 		
                 (OS_TASK_PTR )TaskReadIDCard, 			
                 (void		* )0,					
                 (OS_PRIO	  )READ_ID_CARD_PRIO,     	
                 (CPU_STK   * )&READ_ID_CARD_TASK_STK[0],	
                 (CPU_STK_SIZE)READ_ID_CARD_SIZE/10,	
                 (CPU_STK_SIZE)READ_ID_CARD_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);
				 
	//登录管理任务函数
	OSTaskCreate((OS_TCB 	* )&TaskLogInTCB,		
				 (CPU_CHAR	* )"LogIn", 		
                 (OS_TASK_PTR )TaskLogIn, 			
                 (void		* )0,					
                 (OS_PRIO	  )LOGIN_PRIO,     	
                 (CPU_STK   * )&LOGIN_TASK_STK[0],	
                 (CPU_STK_SIZE)LOGIN_SIZE/10,	
                 (CPU_STK_SIZE)LOGIN_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);
				 
	//时间更新任务函数
	OSTaskCreate((OS_TCB 	* )&TaskUpdataTimeTCB,		
				 (CPU_CHAR	* )"Updata Time", 		
                 (OS_TASK_PTR )TaskUpdataTime, 			
                 (void		* )0,					
                 (OS_PRIO	  )UPDATA_PRIO,     	
                 (CPU_STK   * )&UPDATA_TASK_STK[0],	
                 (CPU_STK_SIZE)UPDATA_SIZE/10,	
                 (CPU_STK_SIZE)UPDATA_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);
				 
	//关机任务函数
	OSTaskCreate((OS_TCB 	* )&TaskPowerOnTCB,		
				 (CPU_CHAR	* )"Power On", 		
                 (OS_TASK_PTR )TaskPowerOn, 			
                 (void		* )0,					
                 (OS_PRIO	  )POWER_ON_PRIO,     	
                 (CPU_STK   * )&POWER_ON_TASK_STK[0],	
                 (CPU_STK_SIZE)POWER_ON_SIZE/10,	
                 (CPU_STK_SIZE)POWER_ON_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);
				 
	//WIFI接受任务函数
	OSTaskCreate((OS_TCB 	* )&TaskWifiReceiveTCB,		
				 (CPU_CHAR	* )"Wifi Receive", 		
                 (OS_TASK_PTR )TaskWifiReceive, 			
                 (void		* )0,					
                 (OS_PRIO	  )WIFI_RECEIVE_PRIO,     	
                 (CPU_STK   * )&WIFI_RECEIVE_TASK_STK[0],	
                 (CPU_STK_SIZE)WIFI_RECEIVE_SIZE/10,	
                 (CPU_STK_SIZE)WIFI_RECEIVE_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);
				 
	//WIFI发送任务函数
	OSTaskCreate((OS_TCB 	* )&TaskWifiSendTCB,		
				 (CPU_CHAR	* )"Wifi Send", 		
                 (OS_TASK_PTR )TaskWifiSend, 			
                 (void		* )0,					
                 (OS_PRIO	  )WIFI_SEND_PRIO,     	
                 (CPU_STK   * )&WIFI_SEND_TASK_STK[0],	
                 (CPU_STK_SIZE)WIFI_SEND_SIZE/10,	
                 (CPU_STK_SIZE)WIFI_SEND_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);
				 
	//后台关机任务函数
	OSTaskCreate((OS_TCB 	* )&TaskBackShutDownTCB,		
				 (CPU_CHAR	* )"Back ShutDown", 		
                 (OS_TASK_PTR )TaskBackShutDown, 			
                 (void		* )0,					
                 (OS_PRIO	  )BACK_SHUTDOWN_PRIO,     	
                 (CPU_STK   * )&BACK_SHUTDOWN_TASK_STK[0],	
                 (CPU_STK_SIZE)BACK_SHUTDOWN_SIZE/10,	
                 (CPU_STK_SIZE)BACK_SHUTDOWN_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);
			 	
	//创建LED1任务
	OSTaskCreate((OS_TCB 	* )&Led1TaskTCB,		
				 (CPU_CHAR	* )"led1 task", 		
                 (OS_TASK_PTR )led1_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )LED1_TASK_PRIO,     	
                 (CPU_STK   * )&LED1_TASK_STK[0],	
                 (CPU_STK_SIZE)LED1_STK_SIZE/10,	
                 (CPU_STK_SIZE)LED1_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);	
#if TEST_STACK_ON				 
	//浮点数测试任务函数
	OSTaskCreate((OS_TCB 	* )&FloatTaskTCB,		
				 (CPU_CHAR	* )"float test task", 		
                 (OS_TASK_PTR )float_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )FLOAT_TASK_PRIO,     	
                 (CPU_STK   * )&FLOAT_TASK_STK[0],	
                 (CPU_STK_SIZE)FLOAT_STK_SIZE/10,	
                 (CPU_STK_SIZE)FLOAT_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);	
 #endif
				 
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//挂起开始任务			 
#endif				 
	OS_CRITICAL_EXIT();	//退出临界区
}

//led0任务函数
static void led0_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	
	while(1){
		LED_INDI_CONTROL_OUT = LED_INDI_CONTROL_TRUE;
		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //延时1s
		LED_INDI_CONTROL_OUT = LED_INDI_CONTROL_FALSE;
		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //延时1s
	}
}

//电源管理
static void TaskPowerManage(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg; 
			
	while(1){		
		if( gp_stuConfigFile->uAutoShutDown>=AUTO_SHUTDOWN_90_TIME ){        /* 不自动关机 */
				
		}else{
			if( g_uRecAutoDownTime>=gp_stuConfigFile->uAutoShutDown ){
				vPromptShutDown( POWER_WARN,POWER_FORCE_30_SECOND );        /* 自动关机 可以取消 */
			}
		}
		
		g_uRecAutoDownTime++;                                               /* 记录自动关机时间 */		
		
		OSTimeDlyHMSM(0,0,59,0,OS_OPT_TIME_HMSM_STRICT,&err);                //延时1min		
	}
}

//UI显示屏显示
static void TaskUserDisplay(void* p_arg)
{
#if DEBUH_UART1

#endif
	
	OS_ERR err = OS_ERR_NONE;
	OS_ERR uTempErr = OS_ERR_NONE;
	OS_MSG_SIZE size = 0;
	void *puTempArrMsg = NULL; 
	
	p_arg = p_arg;
	
	while(1){		
		puTempArrMsg = (uint8_t *)OSQPend( (OS_Q *)&g_TouchMsgQue,(OS_TICK )0,(OS_OPT )OS_OPT_PEND_BLOCKING,(OS_MSG_SIZE *)&size,(CPU_TS *)NULL,&uTempErr );   /*等待一个消息*/
		
		if( (OS_ERR_NONE==uTempErr) ){
#if TJC_TOUCH_ENABLE			
			uTjc4832tTouchEnable( TJC_TOUCH_OFF );   /* 整页关闭触摸 */
#endif			
			OSTimeDlyHMSM(0, 0, 0, 60,OS_OPT_TIME_HMSM_STRICT,&err);      /* 20-160 */
#if TJC_TOUCH_ENABLE	
			uTjc4832tTouchEnable( TJC_TOUCH_ON );    /* 整页打开触摸 */
#endif	
			
			OSMutexPend( (OS_MUTEX *)&g_DisUI, 0,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err );	              /* 等待信号量 */
			if( (0!=(*(uint8_t *)puTempArrMsg)) ){
				UpdateUI( (uint8_t *)puTempArrMsg );		                                                          /* 更新UI */ 
			}
			OSMutexPost( (OS_MUTEX *)&g_DisUI,OS_OPT_POST_NO_SCHED,&err );                                            /* 释放信号量 */
		}else{	
#if DEBUH_UART1
			myprintf( "uTempPendErr:%d \r\n",uTempErr );
#endif				
			OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	 /* 延时10ms   */	
		}	
		if( NULL!=puTempArrMsg ){
			free( puTempArrMsg );                                                                                 /* 释放内存 */  
		}
	}
}

//显示屏通讯任务函数
static void TaskTjc4832tInterface(void *p_arg)
{
	CPU_SR_ALLOC();                                             /*申请临界区变量*/
	OS_ERR err = OS_ERR_NONE;
	static uint8_t l_uTempOrder = 0;	
	uint8_t uTouchArrTemp[128] = {0};	
	uint16_t uUsart4RxStaTemp = 0;
#if DEBUH_UART1
	#if PRIVATE_UART1
	uint8_t i = 0;
	#endif
#endif
	
	p_arg = p_arg;
	
	while(1)
	{		
		OSSemPend( (OS_SEM *)&g_TjcTouchsem, 0,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);   /*等待触摸屏信号量*/
		if( OS_ERR_NONE==err ){
			OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */
			uUsart4RxStaTemp = g_Usart4_Rx_Sta;
			g_Usart4_Rx_Sta = 0;
			memcpy( (char *)uTouchArrTemp,(const char *)g_Usart4_Rx_Buf,uUsart4RxStaTemp );   /* 复制 */
			memset( g_Usart4_Rx_Buf,0,sizeof(g_Usart4_Rx_Buf) );
			OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */				
			
			if( (0xff==uTouchArrTemp[uUsart4RxStaTemp-1])&&(0xff==uTouchArrTemp[uUsart4RxStaTemp-2])&&(0xff==uTouchArrTemp[uUsart4RxStaTemp-3]) ){							
				uUsart4RxStaTemp = uUsart4RxStaTemp-3;                                                   /* 去掉结束符 */
				memset( uTouchArrTemp+uUsart4RxStaTemp,0,3 );                                            /* 将结束符替换为空 */
			    
				l_uTempOrder = uOrderAnalysis( uTouchArrTemp[0],uTouchArrTemp,uUsart4RxStaTemp );        /* 解析指令 */
				vUpdateUISend( l_uTempOrder );                                                           /* 发送通讯指令 */
				l_uTempOrder = 0;                                                                        /* 归零 */
#if DEBUH_UART1
	#if PRIVATE_UART1
				myprintf( "Tjc: %d- ",uUsart4RxStaTemp );
				for( i=0;i<uUsart4RxStaTemp;i++ ){
					myprintf( "%2x ",uTouchArrTemp[i] );  
				}
				myprintf( "\r\n");
	#endif
#endif
			}else{
#if DEBUH_UART1
	#if PRIVATE_UART1
				myprintf( "TjcE:%d ",uUsart4RxStaTemp );
				for( i=0;i<uUsart4RxStaTemp;i++ ){
					myprintf( "%2x ",uTouchArrTemp[i] );  
				}
				myprintf( "\r\n");
	#endif
#endif	
			}
			
			memset( uTouchArrTemp,0,sizeof(uTouchArrTemp) );      /* 必须清空 */		
		}else{		
#if DEBUH_UART1
			myprintf( "uTjcsemErr:%d \r\n",err );
#endif			
			OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);  /* 延时10ms */	
		}		
	}
}

//读ID卡任务函数
static void TaskReadIDCard(void *p_arg)
{
	OS_ERR err;	
	uint8_t uRecError = 0;
	
	p_arg = p_arg;
		
	if( BSP_ReadPin(ID_DETECT_PORT,ID_DETECT_PIN) ){ 
		if( NULL==uReadStoreIdItem( uGetIdCountValue() ) ){                              /*  */
			uTjc4832tSetPage( TJC_WARN_PAGE );                                           /*设置为强制警告页*/
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"ID Number" );	 //没有ID卡
			uBuzzerTimes( BUZZER_ONE_TIME );
		}else{
		
		}
	}
	
	OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);				/* 开机延时1秒检查 */
#if TURN_READ_ID		                    /* 开机就读ID卡 */	
	if( !BSP_ReadPin(ID_DETECT_PORT,ID_DETECT_PIN) ){ 	
		iRecPageIDTemp = uTjc4832tGetPage();            /* 获取当前页面ID */
		uTjc4832tSetPage( TJC_PROMPT_PAGE );            /* 设置为 */
		uTjc4832tSetLableValue( TJC_PROMPT_PAGE,SET1_TEXT_DIS_CON_ID,(uint8_t *)"Reading ID Card ..." );
		                        
		uRecError = uReadIdItem();    /* 读id卡 */
		
		if( EXE_SPECIAL_FAILED!=iRecPageIDTemp ){
			uTjc4832tSetPage( iRecPageIDTemp );            /* 设置为 */
			if( TJC_TEST_PAGE==iRecPageIDTemp ){
				uTestInformation();                                         /* 显示测试信息 */
			}
		}else{
			vPromptShutDown( POWER_FORCE,POWER_FORCE_03_SECOND );                          /* 有提示关机 不可取消 */
		}
	}else{
#endif
		if( NULL==uReadStoreIdItem( uGetIdCountValue() ) ){                              /*  */
			uBuzzerTimes( BUZZER_ONE_TIME );
			uTjc4832tSetPage( TJC_WARN_PAGE );                                           /*设置为强制警告页*/
			if( EN_ON==gp_stuConfigFile->uCutEnCu ){
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"ID Number" );	 //没有ID卡
			}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"卡数" );	     //没有ID卡
			}else{
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"ID Number" );	 //没有ID卡
			}			
		}else{
			if( (0==strlen((const char *)g_IdMemory.project_name))||(0xff==g_IdMemory.project_name[0]) ){				
				uBuzzerTimes( BUZZER_ONE_TIME );
				uTjc4832tSetPage( TJC_WARN_PAGE );        /*设置为强制警告页*/		
				if( EN_ON==gp_stuConfigFile->uCutEnCu ){
					uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"No ID" );	//没有ID卡
				}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
					uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"无ID" );	     //没有ID卡
				}else{
					uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"No ID" );	//没有ID卡
				}
#if DEBUH_UART1		
				myprintf( "No ID \r\n");
#endif	
			}
		}	
#if TURN_READ_ID
	}
#endif	
	
	while(1)
	{
		OSSemPend( (OS_SEM *)&g_ReadIDsem, 0,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	/* 等待读ID卡信号量*/			
		if( OS_ERR_NONE==err ){			
			/* 检查ID卡 */					
			if( NULL==_gp_ID ){					
				OSTimeDlyHMSM(0, 0, 0, 500,OS_OPT_TIME_HMSM_STRICT,&err);	//出错需要处理			
			}else{		
				if( !BSP_ReadPin(ID_DETECT_PORT,ID_DETECT_PIN) ){
					OSMutexPend( (OS_MUTEX *)&g_MutIDTask, 0,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err );	              /*等待信号量*/					
					
					uClearIdData();            /* 清空ID数据 */					
//					/* 需要读6张卡数据 */				
					uConfirmPage( TJC_WARN_PAGE );            /* 设置为 */
					uTjc4832tSetLableValuePco( TJC_WARN_PAGE,WARN_ID_NUM,TJC_GREEN );        /* 设置为绿色字体 */
					uTjc4832tSetLableValuePco( TJC_WARN_PAGE,WARN_ID_NUM,TJC_GREEN );        /* 设置为绿色字体 */
					uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Reading ID Card ..." );
					
					uTjc4832tTouchEnable( TJC_TOUCH_OFF );                                             /* 整页关闭触摸 */					
					uRecError = uReadIdItem();                        /* 读id卡 */					
					
//					uTjc4832tSetPage( TJC_WARN_PAGE );                /* 设置为 */
					OSTimeDlyHMSM(0, 0, 0, 100,OS_OPT_TIME_HMSM_STRICT,&err);
//					/* 效验是否成功 不成功就关机 */
//					if( EXE_SUCCEED!=uConfirmPage( TJC_PROMPTER_PAGE ) ) {
//						if( EXE_FAILED==uConfirmIdCardPage(TJC_PROMPTER_PAGE) ){                           /* 页面与控制不同步 只能强制关机 */
//							vPromptShutDown( POWER_FORCE,POWER_FORCE_03_SECOND );                          /* 有提示关机 不可取消 */
//						}
//					}
					
					if( EXE_SUCCEED==uRecError ){		
						uIdDisplay( uGetIdCountValue() );	                                      /* 显示当前读取的ID内容 */
//						uTestInformationRefresh();                                                /* 显示测试信息 */
//						uTestInformationRefresh();                                                /* 显示测试信息 */
					}
					uTjc4832tTouchEnable( TJC_TOUCH_ON );                                              /* 整页打开触摸 */

					OSMutexPost( (OS_MUTEX *)&g_MutIDTask,OS_OPT_POST_NO_SCHED,&err );                                            /*释放信号量 */
				}else{
					uTjc4832tSetPage( TJC_WARN_PAGE );        /*设置为*/
					uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Please insert the ID card" );		
					uBuzzerTimes( BUZZER_ONE_TIME );
				}  		
			}	
			
		}else{
			OSTimeDlyHMSM(0, 0, 0, 500,OS_OPT_TIME_HMSM_STRICT,&err);	 /* 延时500ms   */
		}
	}
}

//登录管理任务函数
static void TaskLogIn(void *p_arg)
{
	OS_ERR err;
	
	p_arg = p_arg;
	
	while(1)
	{
		OSSemPend( (OS_SEM *)&g_ResetLogInsem,0,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	          /* 等待信号量 */	
		if( OS_ERR_NONE==err ){
#if LOGIN_CODE
			vLogInInit();                                 /* 登录系统初始化 */
#else
			uUserPasswordInit();
#endif
		}else{
			OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	 /* 延时10ms   */
		}
		
		if( EXE_FAILED==uSemclear( (OS_SEM*)&g_ResetLogInsem ) ){                /* 清空再登陆信号量 首次上电会有屏幕和登陆按钮同时发送 */
#if DEBUH_UART1	
			myprintf( "ClearSem Error  \r\n" );
#endif
		}
	}
}

//时间更新任务函数
static void TaskUpdataTime(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
		
	while( RTC_Init() ){		                                                        //RTC初始化	，一定要初始化成功				
		uTjc4832tSetPage( TJC_WARN_PAGE );                                              /*设置为强制警告页*/
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"RTC ERROR!" );	//出错需要处理//"RTC ERROR!" //"RTC Trying...");	
		uBuzzerTimes( BUZZER_ONE_TIME );		
	}
	
	while(1)
	{		
		OSTimeDlyHMSM(0, 0, 0, 990,OS_OPT_TIME_HMSM_STRICT,&err);	                    //延时//OSTimeDlyHMSM(0, 1, 1, 900);	//延时		
		
		if( !bMotorResetStatus() ){
			UpdataRealTime( REAL_TIME_ON );	                                            /* 实时刷新屏幕 REAL_TIME_OFF */					
		}
	}
}

//关机任务函数  优先级第四高
static void TaskPowerOn(void *p_arg)
{
	OS_ERR err;
	
	p_arg = p_arg;
	
	bFuncFlashP25Q32hInit();                                                                        /* 初始化FLASH */
#if ERASE_SECTOR_CONFIG
	uEraseSectorFromStartToEnd( (SPIFLASH_CONFIG_FILE_BASE_ADDR/SPIFLASH_PAGE_BASE_ADDR),P25Q32H_CLEAR_SECTOR );
	while(1)
	{
		OSTimeDlyHMSM(1, 0, 0, 0,OS_OPT_TIME_HMSM_STRICT,&err);	                            /* 延时10ms   */
	}
#else	
	bFuncIFP300FlashValInit();																        /* 初始化默认信息 */
	uMax5402GainInitSet( gp_stuConfigFile->uMax5402Gain,UI_N_PROMPT );	                            /* Max5402eua初始化 软件SPI */
	uResetMotorInteriorStauts( UI_N_PROMPT );                                                       /* 传感器无提示复位电机 */ 
	ChooseCoefficient( BUTTON_VALUE_SERUM );                                                        /* 每次开机都默认是Serum 可以做成配置信息记住 */	
//	uWifiPowerInit( 2 );                                                                            /* WIFI重启一下电源 */
	iElectricInit();                                                                                /* 电源初始化电量 */
	
	while(1)
	{
		OSSemPend( (OS_SEM *)&g_PowerOnsem,0,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err );	/*等待信号量*/
		
		if( OS_ERR_NONE==err ){
			vShutDownPrompter();                                                                    /* 关机提示 需要用户自己确认 */
		}else{
			OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	                            /* 延时10ms   */
		}	
	}
#endif
}

#if 0
//WIFI接受任务函数
static void TaskWifiReceive(void *p_arg)
{
	OS_ERR err;	
	uint8_t uWifiArrTemp[USART2_REC_LEN] = {0};
	
	p_arg = p_arg;
	
	while(1)
	{
		OSSemPend( (OS_SEM *)&g_WifiReceive,WAIT_SEM_7_TIME,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);   /* 等待WIFI信号量 响应优先级需要小于指令接受优先级 */
		
		if( OS_ERR_NONE==err ){
//			vCopyWifiBlueBuffer( uWifiArrTemp );                                                                        /* COPY缓存 */
//			vClearWifiBlueBuffer();                                                                                     /* 清空WIFI缓存 */
			
//			uWifiBuleOrder( uWifiArrTemp );
//			
//			if( (0x4F==uWifiArrTemp[0])&&(0x4B==uWifiArrTemp[1]) ){
//				OSSemPost( (OS_SEM *)&g_WifiBlueOrder,OS_OPT_POST_NO_SCHED,&err ); 
//			}
			
#if DEBUH_UART1
			myprintf( "uWifiReceive:%s \r\n",uWifiArrTemp );
#endif		
			memset( uWifiArrTemp,0,sizeof(uWifiArrTemp) );
		}else{
			OSTimeDlyHMSM(0,0,5,0,OS_OPT_TIME_HMSM_STRICT,&err);                                                    /* 延时500ms */
		}	
	}
}
#else
//WIFI接受任务函数
static void TaskWifiReceive(void *p_arg)
{
	OS_ERR err;	
//	uint8_t uWifiArrTemp[USART2_REC_LEN] = {0};
	
	p_arg = p_arg;
	
	while(1)
	{
		if( TRANSFER_AP_STATION==g_uTransparentStatus ){
//			OSSemPend( (OS_SEM *)&g_WifiReceive,WAIT_SEM_4_TIME,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);   /* 等待WIFI信号量 响应优先级需要小于指令接受优先级 */
//			
//			if( OS_ERR_NONE==err ){
//				vCopyWifiBuffer( uWifiArrTemp );                                                                        /* COPY缓存 */
//				vClearWifiBuffer();                                                                                     /* 清空WIFI缓存 */
//				
//#if DEBUH_UART1
//				myprintf( "uWifiReceive:%s \r\n",uWifiArrTemp );
//#endif		
//				memset( uWifiArrTemp,0,sizeof(uWifiArrTemp) );
//			}else{
//				OSTimeDlyHMSM(0,0,5,0,OS_OPT_TIME_HMSM_STRICT,&err);                                                    /* 延时500ms */
//			}	
			OSTimeDlyHMSM(0,0,30,0,OS_OPT_TIME_HMSM_STRICT,&err);                                                    /* 延时500ms */
		}else{			
			OSTimeDlyHMSM(0,0,30,0,OS_OPT_TIME_HMSM_STRICT,&err);                                                        /* 延时500ms */
		}
	}
}
#endif

//WIFI发送任务函数
static void TaskWifiSend(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;	
	
	OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);                                                             /* 等待Wifi启动 */	
	uWifiInit();                                                                                                        /* 初始化 */ 	
	uClassicBluetoothInit();                                                                                            /* 经典蓝牙初始化 */
																									                    
	while(1)                                                                                                            
	{                                                                                                                   
		if( !bMotorResetStatus() ){			
			
			OSTimeDlyHMSM(0, 0, 5, 0,OS_OPT_TIME_HMSM_STRICT,&err);	  
//			OSTimeDlyHMSM(0, 1, 0, 0,OS_OPT_TIME_HMSM_STRICT,&err);	
			
#if WIFI_AUTO_UP			
			if( EXE_SUCCEED==uWifiConnentEnv() ){                                                                       /* 优先级必须高于WIFI接受函数 */
//				uWifiUploaTheHistoryData();	  
//				uLisSendTest();
				
				uLisSendHistory();                                                   /* 自动上传 */
			}
#endif
			
		}else{
			OSTimeDlyHMSM(0, 1, 0, 0,OS_OPT_TIME_HMSM_STRICT,&err);	
		}		
	}
}

//后台关机任务函数
static void TaskBackShutDown(void *p_arg)
{
	OS_ERR err;
	OS_ERR uTempErr;
	OS_MSG_SIZE size = 0;
	void *puShutTempArrMsg = NULL;
	
	p_arg = p_arg;
	while(1)
	{
		puShutTempArrMsg = OSQPend( (OS_Q *)&g_ShutDownMsgQue,(OS_TICK )0,(OS_OPT )OS_OPT_PEND_BLOCKING,(OS_MSG_SIZE *)&size,(CPU_TS *)NULL,&uTempErr );   /* 等待一个消息 */		
		if( OS_ERR_NONE==uTempErr ){
#if DEBUH_UART1
			myprintf( "uShutdown:%d ",*(uint8_t *)puShutTempArrMsg );
#endif				
			vBackgrounderShutDown( (uint8_t *)puShutTempArrMsg );
		}else{
			OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	 /* 延时10ms   */
#if DEBUH_UART1
			myprintf( "uTempShutPendErr:%d ",uTempErr );
#endif	
		}
	}
}

//led1任务函数用作关机确认
static void led1_task(void *p_arg)
{
	OS_ERR err = OS_ERR_NONE;
	OS_ERR uTempErr = OS_ERR_NONE;
	OS_MSG_SIZE size = 0;
	void *puTempArrMsg = NULL; 

	p_arg = p_arg;
	
	while(1)
	{
		puTempArrMsg = (uint8_t *)OSQPend( (OS_Q *)&g_TouchSpcMsgQue,(OS_TICK )0,(OS_OPT )OS_OPT_PEND_BLOCKING,(OS_MSG_SIZE *)&size,(CPU_TS *)NULL,&uTempErr );   /*等待一个消息*/			
		if( OS_ERR_NONE==uTempErr ){
			OSTimeDlyHMSM(0, 0, 0, 500,OS_OPT_TIME_HMSM_STRICT,&err);      /* 300-500 */		
			
			UpdateSpcUI( puTempArrMsg );		                                                                      /* 更新UI */ 
		}else{	
#if DEBUH_UART1
			myprintf( "uTempSpcPendErr:%d ",uTempErr );
#endif				
			OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	 /* 延时10ms   */	
		}
		if( NULL!=puTempArrMsg ){
			free( puTempArrMsg );                                                                                 /* 释放内存 */
		}
	}
}

#if TEST_STACK_ON
//浮点测试任务
static void float_task(void *p_arg)
{
	OS_ERR err;
	uint8_t i = 0;
	OS_TCB *stuArr[13] = { &Led0TaskTCB,&TaskPowerManageTCB,&TaskUserDisplayTCB,&TaskTjc4832tInterfaceTCB,&TaskReadIDCardTCB,&TaskLogInTCB,
		                   &TaskUpdataTimeTCB,&TaskPowerOnTCB,&TaskWifiReceiveTCB,&TaskWifiSendTCB,&TaskBackShutDownTCB,&Led1TaskTCB,&FloatTaskTCB };    /* 指针数组 */	
	
	p_arg = p_arg;	
	
	while(1){		
		
		if( !bMotorResetStatus() ){
			
			myprintf("CPU: %4d %.2f%% \r\n",OSStatTaskCPUUsage,(float)((float)OSStatTaskCPUUsage/(float)100) );
			
			for( i=0;i<sizeof(stuArr)/sizeof(OS_TCB *);i++ ){				
				myprintf("Name%2d:           StkFree StkUsed CPUUsage CPUUsageMax CtxSwCtr CyclesStart CyclesTotal CyclesTotalPrev\r\n",i);
				myprintf("%s%2d: %8d %8d %8d %8d %8d %8d %8d %8d\r\n",stuArr[i]->NamePtr,i,stuArr[i]->StkFree,stuArr[i]->StkUsed,        \
						 stuArr[i]->CPUUsage,stuArr[i]->CPUUsageMax,stuArr[i]->CtxSwCtr,stuArr[i]->CyclesStart,stuArr[i]->CyclesTotal,
						 stuArr[i]->CyclesTotalPrev);					
			}
			
			OSTimeDlyHMSM(0,0,30,0,OS_OPT_TIME_HMSM_STRICT,&err);       //延时500ms		//delay_ms(500); //延时500ms
		}else{
			OSTimeDlyHMSM(0, 1, 0, 0,OS_OPT_TIME_HMSM_STRICT,&err);	
		}
	}
}
#endif
