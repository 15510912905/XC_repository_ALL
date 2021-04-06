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

OS_TCB TaskPowerOnTCB;                                                        //任务控制块
static __align(8) CPU_STK POWER_ON_TASK_STK[POWER_ON_SIZE];                   //任务堆栈

OS_TCB Led0TaskTCB;                                                           //任务控制块
static __align(8) CPU_STK LED0_TASK_STK[LED0_STK_SIZE];                       //任务堆栈
  
#if TEST_STACK_ON			  	
OS_TCB Led1TaskTCB;                                                           //任务控制块
static __align(8) CPU_STK LED1_TASK_STK[LED1_STK_SIZE];                       //任务堆栈	
                                                                              
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

OS_TCB TaskWifiReceiveTCB;                                                    //任务控制块
static __align(8) CPU_STK WIFI_RECEIVE_TASK_STK[WIFI_RECEIVE_SIZE];           //任务堆栈

OS_TCB TaskWifiSendTCB;                                                       //任务控制块
static __align(8) CPU_STK WIFI_SEND_TASK_STK[WIFI_SEND_SIZE];                 //任务堆栈

OS_TCB TaskBackShutDownTCB;                                                   //任务控制块
static __align(8) CPU_STK BACK_SHUTDOWN_TASK_STK[BACK_SHUTDOWN_SIZE];         //任务堆栈

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

 #if TEST_STACK_ON				 
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

//关机任务函数  优先级第四高
static void TaskPowerOn(void *p_arg)
{
	OS_ERR err = OS_ERR_NONE;
	
	p_arg = p_arg;
		
	bFuncFlashP25Q32hInit();                                                                        /* 初始化FLASH */
//	uTjc4832tSetPage( TJC_WARN_PAGE );                                                              /* 设置为强制警告页 */
//	uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Program upgrading" );	//
//	uTjc4832tTouchEnable( TJC_TOUCH_OFF );                                                          /* 整页关闭触摸 */ 	
	
	while(1){
		OSSemPend( (OS_SEM *)&g_TjcUpdata, 0,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	           /* 等待WIFI信号量 */
		if( OS_ERR_NONE==err ){		
			uUart1Parsing( &g_Usart_Rx_Sta );
		}
	}

}

#if TEST_STACK_ON
//电源管理
static void TaskPowerManage(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg; 
			
	while(1){			
		
		OSTimeDlyHMSM(0,0,59,0,OS_OPT_TIME_HMSM_STRICT,&err);                //延时1min		
	}
}

//UI显示屏显示
static void TaskUserDisplay(void* p_arg)
{	
	OS_ERR err = OS_ERR_NONE;
	
	p_arg = p_arg;
	
	while(1){		
		
		OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	 /* 延时10ms   */		
	}
}

//显示屏通讯任务函数
static void TaskTjc4832tInterface(void *p_arg)
{
	OS_ERR err = OS_ERR_NONE;	
	p_arg = p_arg;
	
	while(1){	
		
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);  /* 延时10ms */	
			
	}
}

//读ID卡任务函数
static void TaskReadIDCard(void *p_arg)
{
	OS_ERR err;		
	p_arg = p_arg;
	
	while(1){
		
		OSTimeDlyHMSM(0, 0, 0, 500,OS_OPT_TIME_HMSM_STRICT,&err);	 /* 延时500ms   */		
	}
}

//登录管理任务函数
static void TaskLogIn(void *p_arg)
{
	OS_ERR err;	
	p_arg = p_arg;
	
	while(1)	{
	
		OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	 /* 延时10ms   */		
	}
}

//时间更新任务函数
static void TaskUpdataTime(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	
	while(1)
	{		
		OSTimeDlyHMSM(0, 0, 0, 990,OS_OPT_TIME_HMSM_STRICT,&err);	                    //延时//OSTimeDlyHMSM(0, 1, 1, 900);	//延时		
	
	}
}

//WIFI接受任务函数
static void TaskWifiReceive(void *p_arg)
{
	OS_ERR err;	
	
	p_arg = p_arg;
	
	while(1){
			
		OSTimeDlyHMSM(0,0,30,0,OS_OPT_TIME_HMSM_STRICT,&err);                                                        /* 延时500ms */
		
	}
}

//WIFI发送任务函数
static void TaskWifiSend(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;	                                                                                          /* 经典蓝牙初始化 */
																									                    
	while(1)                                                                                                            
	{                                                                                                                   

		OSTimeDlyHMSM(0, 1, 0, 0,OS_OPT_TIME_HMSM_STRICT,&err);	
		
	}
}

//后台关机任务函数
static void TaskBackShutDown(void *p_arg)
{
	OS_ERR err;
	
	p_arg = p_arg;
	while(1)
	{
		OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	 /* 延时10ms   */
	}
}

//led1任务函数用作关机确认
static void led1_task(void *p_arg)
{
	OS_ERR err = OS_ERR_NONE;

	p_arg = p_arg;
	
	while(1)
	{
			
		OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	 /* 延时10ms   */	
	}
}

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
