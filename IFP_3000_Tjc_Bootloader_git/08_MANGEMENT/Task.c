/********************************************************
   ��Ȩ���� (C), 2001-2100, �Ĵ��½���������ɷ����޹�˾
  -------------------------------------------------------

				Ƕ��ʽ����ƽ̨����������

  -------------------------------------------------------
   �� �� ��   : Task.c
   �� �� ��   : V1.0.0.0
   ��    ��   : ZR
   ��������   : 2020��10��01��
   ��������   : ���岢������
   ������     : uC/OS-III V3.0.03
   ע         �����ļ���������Ӳ����·�� 
********************************************************/
 
#include "Task.h"
/*--------------------------------------------------------------*/
//UCOSIII���������ȼ��û�������ʹ�ã�ALIENTEK
//����Щ���ȼ��������UCOSIII��5��ϵͳ�ڲ�����
//���ȼ�0���жϷ������������� OS_IntQTask()
//���ȼ�1��ʱ�ӽ������� OS_TickTask()
//���ȼ�2����ʱ���� OS_TmrTask()
//���ȼ�OS_CFG_PRIO_MAX-2��ͳ������ OS_StatTask()
//���ȼ�OS_CFG_PRIO_MAX-1���������� OS_IdleTask()
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/*���������ջ*/
OS_TCB StartTaskTCB;                                                          //������ƿ�	
CPU_STK START_TASK_STK[START_STK_SIZE];                                       //�����ջ

OS_TCB TaskPowerOnTCB;                                                        //������ƿ�
static __align(8) CPU_STK POWER_ON_TASK_STK[POWER_ON_SIZE];                   //�����ջ

OS_TCB Led0TaskTCB;                                                           //������ƿ�
static __align(8) CPU_STK LED0_TASK_STK[LED0_STK_SIZE];                       //�����ջ
  
#if TEST_STACK_ON			  	
OS_TCB Led1TaskTCB;                                                           //������ƿ�
static __align(8) CPU_STK LED1_TASK_STK[LED1_STK_SIZE];                       //�����ջ	
                                                                              
OS_TCB TaskPowerManageTCB;                                                    //������ƿ�
static __align(8) CPU_STK POWER_MANAGE_TASK_STK[POWER_MANAGESTK_SIZE];        //�����ջ	

OS_TCB TaskUserDisplayTCB;                                                    //������ƿ�
static __align(8) CPU_STK USER_DISPLAY_TASK_STK[USER_DISPLAY_SIZE];           //�����ջ

OS_TCB TaskTjc4832tInterfaceTCB;                                              //������ƿ�
static __align(8) CPU_STK TJC_INTERFACE_TASK_STK[TJC_INTERFACE_SIZE];          //�����ջ

OS_TCB TaskReadIDCardTCB;                                                     //������ƿ�
static __align(8) CPU_STK READ_ID_CARD_TASK_STK[READ_ID_CARD_SIZE];           //�����ջ

OS_TCB TaskLogInTCB;                                                          //������ƿ�
static __align(8) CPU_STK LOGIN_TASK_STK[LOGIN_SIZE];                         //�����ջ

OS_TCB TaskUpdataTimeTCB;                                                     //������ƿ�
static __align(8) CPU_STK UPDATA_TASK_STK[UPDATA_SIZE];                       //�����ջ

OS_TCB TaskWifiReceiveTCB;                                                    //������ƿ�
static __align(8) CPU_STK WIFI_RECEIVE_TASK_STK[WIFI_RECEIVE_SIZE];           //�����ջ

OS_TCB TaskWifiSendTCB;                                                       //������ƿ�
static __align(8) CPU_STK WIFI_SEND_TASK_STK[WIFI_SEND_SIZE];                 //�����ջ

OS_TCB TaskBackShutDownTCB;                                                   //������ƿ�
static __align(8) CPU_STK BACK_SHUTDOWN_TASK_STK[BACK_SHUTDOWN_SIZE];         //�����ջ

OS_TCB	FloatTaskTCB;                                                         //������ƿ�
static __align(8) CPU_STK FLOAT_TASK_STK[FLOAT_STK_SIZE];                     //�����ջ
#endif
/*--------------------------------------------------------------*/

/*����ȫ�ֱ���*/

/*----------------------------------------------------��������*/
/* ��ʼ���� ��ʼ������ */
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//ͳ������                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();	
#endif
	
#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	//ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,4,&err);  
#endif		

	OS_CRITICAL_ENTER();	//�����ٽ���
#if TEST_STK_SIZE
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		  //����ʼ����
	OSTaskDel((OS_TCB*)&StartTaskTCB,&err);		          //ɾ����ʼ����	
#else
	bFuncIFP300UcosValInit();                             /* ����USOS���ֱ��� */	

	//�ػ�������
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
				 
	//����LED0����
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
	//����LED1����
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
				 
	//������Դ��������
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
				 
	//UI�û���ʾ����
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
				 
	//��ʾ��ͨѶ������
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

	//��ID��������
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
				 
	//��¼����������
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
				 
	//ʱ�����������
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
				 	 
	//WIFI����������
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
				 
	//WIFI����������
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
				 
	//��̨�ػ�������
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
				 
	//����������������
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
				 
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//����ʼ����			 
#endif				 
	OS_CRITICAL_EXIT();	//�˳��ٽ���
}

//led0������
static void led0_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	
	while(1){
		LED_INDI_CONTROL_OUT = LED_INDI_CONTROL_TRUE;
		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ1s
		LED_INDI_CONTROL_OUT = LED_INDI_CONTROL_FALSE;
		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ1s
	}
}

//�ػ�������  ���ȼ����ĸ�
static void TaskPowerOn(void *p_arg)
{
	OS_ERR err = OS_ERR_NONE;
	
	p_arg = p_arg;
		
	bFuncFlashP25Q32hInit();                                                                        /* ��ʼ��FLASH */
//	uTjc4832tSetPage( TJC_WARN_PAGE );                                                              /* ����Ϊǿ�ƾ���ҳ */
//	uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Program upgrading" );	//
//	uTjc4832tTouchEnable( TJC_TOUCH_OFF );                                                          /* ��ҳ�رմ��� */ 	
	
	while(1){
		OSSemPend( (OS_SEM *)&g_TjcUpdata, 0,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	           /* �ȴ�WIFI�ź��� */
		if( OS_ERR_NONE==err ){		
			uUart1Parsing( &g_Usart_Rx_Sta );
		}
	}

}

#if TEST_STACK_ON
//��Դ����
static void TaskPowerManage(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg; 
			
	while(1){			
		
		OSTimeDlyHMSM(0,0,59,0,OS_OPT_TIME_HMSM_STRICT,&err);                //��ʱ1min		
	}
}

//UI��ʾ����ʾ
static void TaskUserDisplay(void* p_arg)
{	
	OS_ERR err = OS_ERR_NONE;
	
	p_arg = p_arg;
	
	while(1){		
		
		OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	 /* ��ʱ10ms   */		
	}
}

//��ʾ��ͨѶ������
static void TaskTjc4832tInterface(void *p_arg)
{
	OS_ERR err = OS_ERR_NONE;	
	p_arg = p_arg;
	
	while(1){	
		
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);  /* ��ʱ10ms */	
			
	}
}

//��ID��������
static void TaskReadIDCard(void *p_arg)
{
	OS_ERR err;		
	p_arg = p_arg;
	
	while(1){
		
		OSTimeDlyHMSM(0, 0, 0, 500,OS_OPT_TIME_HMSM_STRICT,&err);	 /* ��ʱ500ms   */		
	}
}

//��¼����������
static void TaskLogIn(void *p_arg)
{
	OS_ERR err;	
	p_arg = p_arg;
	
	while(1)	{
	
		OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	 /* ��ʱ10ms   */		
	}
}

//ʱ�����������
static void TaskUpdataTime(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	
	while(1)
	{		
		OSTimeDlyHMSM(0, 0, 0, 990,OS_OPT_TIME_HMSM_STRICT,&err);	                    //��ʱ//OSTimeDlyHMSM(0, 1, 1, 900);	//��ʱ		
	
	}
}

//WIFI����������
static void TaskWifiReceive(void *p_arg)
{
	OS_ERR err;	
	
	p_arg = p_arg;
	
	while(1){
			
		OSTimeDlyHMSM(0,0,30,0,OS_OPT_TIME_HMSM_STRICT,&err);                                                        /* ��ʱ500ms */
		
	}
}

//WIFI����������
static void TaskWifiSend(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;	                                                                                          /* ����������ʼ�� */
																									                    
	while(1)                                                                                                            
	{                                                                                                                   

		OSTimeDlyHMSM(0, 1, 0, 0,OS_OPT_TIME_HMSM_STRICT,&err);	
		
	}
}

//��̨�ػ�������
static void TaskBackShutDown(void *p_arg)
{
	OS_ERR err;
	
	p_arg = p_arg;
	while(1)
	{
		OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	 /* ��ʱ10ms   */
	}
}

//led1�����������ػ�ȷ��
static void led1_task(void *p_arg)
{
	OS_ERR err = OS_ERR_NONE;

	p_arg = p_arg;
	
	while(1)
	{
			
		OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	 /* ��ʱ10ms   */	
	}
}

//�����������
static void float_task(void *p_arg)
{
	OS_ERR err;
	uint8_t i = 0;
	OS_TCB *stuArr[13] = { &Led0TaskTCB,&TaskPowerManageTCB,&TaskUserDisplayTCB,&TaskTjc4832tInterfaceTCB,&TaskReadIDCardTCB,&TaskLogInTCB,
		                   &TaskUpdataTimeTCB,&TaskPowerOnTCB,&TaskWifiReceiveTCB,&TaskWifiSendTCB,&TaskBackShutDownTCB,&Led1TaskTCB,&FloatTaskTCB };    /* ָ������ */	
	
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
			
			OSTimeDlyHMSM(0,0,30,0,OS_OPT_TIME_HMSM_STRICT,&err);       //��ʱ500ms		//delay_ms(500); //��ʱ500ms
		}else{
			OSTimeDlyHMSM(0, 1, 0, 0,OS_OPT_TIME_HMSM_STRICT,&err);	
		}
	}
}
#endif
