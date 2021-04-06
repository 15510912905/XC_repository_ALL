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
                                                                                                                                    
OS_TCB Led0TaskTCB;                                                           //������ƿ�
static __align(8) CPU_STK LED0_TASK_STK[LED0_STK_SIZE];                       //�����ջ	
                                                                              
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

OS_TCB TaskPowerOnTCB;                                                        //������ƿ�
static __align(8) CPU_STK POWER_ON_TASK_STK[POWER_ON_SIZE];                   //�����ջ

OS_TCB TaskWifiReceiveTCB;                                                    //������ƿ�
static __align(8) CPU_STK WIFI_RECEIVE_TASK_STK[WIFI_RECEIVE_SIZE];           //�����ջ

OS_TCB TaskWifiSendTCB;                                                       //������ƿ�
static __align(8) CPU_STK WIFI_SEND_TASK_STK[WIFI_SEND_SIZE];                 //�����ջ

OS_TCB TaskBackShutDownTCB;                                                   //������ƿ�
static __align(8) CPU_STK BACK_SHUTDOWN_TASK_STK[BACK_SHUTDOWN_SIZE];         //�����ջ

OS_TCB Led1TaskTCB;                                                           //������ƿ�
static __align(8) CPU_STK LED1_TASK_STK[LED1_STK_SIZE];                       //�����ջ	

#if TEST_STACK_ON
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
#if TEST_STACK_ON				 
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

//��Դ����
static void TaskPowerManage(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg; 
			
	while(1){		
		if( gp_stuConfigFile->uAutoShutDown>=AUTO_SHUTDOWN_90_TIME ){        /* ���Զ��ػ� */
				
		}else{
			if( g_uRecAutoDownTime>=gp_stuConfigFile->uAutoShutDown ){
				vPromptShutDown( POWER_WARN,POWER_FORCE_30_SECOND );        /* �Զ��ػ� ����ȡ�� */
			}
		}
		
		g_uRecAutoDownTime++;                                               /* ��¼�Զ��ػ�ʱ�� */		
		
		OSTimeDlyHMSM(0,0,59,0,OS_OPT_TIME_HMSM_STRICT,&err);                //��ʱ1min		
	}
}

//UI��ʾ����ʾ
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
		puTempArrMsg = (uint8_t *)OSQPend( (OS_Q *)&g_TouchMsgQue,(OS_TICK )0,(OS_OPT )OS_OPT_PEND_BLOCKING,(OS_MSG_SIZE *)&size,(CPU_TS *)NULL,&uTempErr );   /*�ȴ�һ����Ϣ*/
		
		if( (OS_ERR_NONE==uTempErr) ){
#if TJC_TOUCH_ENABLE			
			uTjc4832tTouchEnable( TJC_TOUCH_OFF );   /* ��ҳ�رմ��� */
#endif			
			OSTimeDlyHMSM(0, 0, 0, 60,OS_OPT_TIME_HMSM_STRICT,&err);      /* 20-160 */
#if TJC_TOUCH_ENABLE	
			uTjc4832tTouchEnable( TJC_TOUCH_ON );    /* ��ҳ�򿪴��� */
#endif	
			
			OSMutexPend( (OS_MUTEX *)&g_DisUI, 0,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err );	              /* �ȴ��ź��� */
			if( (0!=(*(uint8_t *)puTempArrMsg)) ){
				UpdateUI( (uint8_t *)puTempArrMsg );		                                                          /* ����UI */ 
			}
			OSMutexPost( (OS_MUTEX *)&g_DisUI,OS_OPT_POST_NO_SCHED,&err );                                            /* �ͷ��ź��� */
		}else{	
#if DEBUH_UART1
			myprintf( "uTempPendErr:%d \r\n",uTempErr );
#endif				
			OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	 /* ��ʱ10ms   */	
		}	
		if( NULL!=puTempArrMsg ){
			free( puTempArrMsg );                                                                                 /* �ͷ��ڴ� */  
		}
	}
}

//��ʾ��ͨѶ������
static void TaskTjc4832tInterface(void *p_arg)
{
	CPU_SR_ALLOC();                                             /*�����ٽ�������*/
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
		OSSemPend( (OS_SEM *)&g_TjcTouchsem, 0,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);   /*�ȴ��������ź���*/
		if( OS_ERR_NONE==err ){
			OS_CRITICAL_ENTER();  		                    /* ���±��뿼���ٽ���Դ������ */
			uUsart4RxStaTemp = g_Usart4_Rx_Sta;
			g_Usart4_Rx_Sta = 0;
			memcpy( (char *)uTouchArrTemp,(const char *)g_Usart4_Rx_Buf,uUsart4RxStaTemp );   /* ���� */
			memset( g_Usart4_Rx_Buf,0,sizeof(g_Usart4_Rx_Buf) );
			OS_CRITICAL_EXIT();                            /* ���ϱ��뿼���ٽ���Դ������ */				
			
			if( (0xff==uTouchArrTemp[uUsart4RxStaTemp-1])&&(0xff==uTouchArrTemp[uUsart4RxStaTemp-2])&&(0xff==uTouchArrTemp[uUsart4RxStaTemp-3]) ){							
				uUsart4RxStaTemp = uUsart4RxStaTemp-3;                                                   /* ȥ�������� */
				memset( uTouchArrTemp+uUsart4RxStaTemp,0,3 );                                            /* ���������滻Ϊ�� */
			    
				l_uTempOrder = uOrderAnalysis( uTouchArrTemp[0],uTouchArrTemp,uUsart4RxStaTemp );        /* ����ָ�� */
				vUpdateUISend( l_uTempOrder );                                                           /* ����ͨѶָ�� */
				l_uTempOrder = 0;                                                                        /* ���� */
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
			
			memset( uTouchArrTemp,0,sizeof(uTouchArrTemp) );      /* ������� */		
		}else{		
#if DEBUH_UART1
			myprintf( "uTjcsemErr:%d \r\n",err );
#endif			
			OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);  /* ��ʱ10ms */	
		}		
	}
}

//��ID��������
static void TaskReadIDCard(void *p_arg)
{
	OS_ERR err;	
	uint8_t uRecError = 0;
	
	p_arg = p_arg;
		
	if( BSP_ReadPin(ID_DETECT_PORT,ID_DETECT_PIN) ){ 
		if( NULL==uReadStoreIdItem( uGetIdCountValue() ) ){                              /*  */
			uTjc4832tSetPage( TJC_WARN_PAGE );                                           /*����Ϊǿ�ƾ���ҳ*/
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"ID Number" );	 //û��ID��
			uBuzzerTimes( BUZZER_ONE_TIME );
		}else{
		
		}
	}
	
	OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);				/* ������ʱ1���� */
#if TURN_READ_ID		                    /* �����Ͷ�ID�� */	
	if( !BSP_ReadPin(ID_DETECT_PORT,ID_DETECT_PIN) ){ 	
		iRecPageIDTemp = uTjc4832tGetPage();            /* ��ȡ��ǰҳ��ID */
		uTjc4832tSetPage( TJC_PROMPT_PAGE );            /* ����Ϊ */
		uTjc4832tSetLableValue( TJC_PROMPT_PAGE,SET1_TEXT_DIS_CON_ID,(uint8_t *)"Reading ID Card ..." );
		                        
		uRecError = uReadIdItem();    /* ��id�� */
		
		if( EXE_SPECIAL_FAILED!=iRecPageIDTemp ){
			uTjc4832tSetPage( iRecPageIDTemp );            /* ����Ϊ */
			if( TJC_TEST_PAGE==iRecPageIDTemp ){
				uTestInformation();                                         /* ��ʾ������Ϣ */
			}
		}else{
			vPromptShutDown( POWER_FORCE,POWER_FORCE_03_SECOND );                          /* ����ʾ�ػ� ����ȡ�� */
		}
	}else{
#endif
		if( NULL==uReadStoreIdItem( uGetIdCountValue() ) ){                              /*  */
			uBuzzerTimes( BUZZER_ONE_TIME );
			uTjc4832tSetPage( TJC_WARN_PAGE );                                           /*����Ϊǿ�ƾ���ҳ*/
			if( EN_ON==gp_stuConfigFile->uCutEnCu ){
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"ID Number" );	 //û��ID��
			}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"����" );	     //û��ID��
			}else{
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"ID Number" );	 //û��ID��
			}			
		}else{
			if( (0==strlen((const char *)g_IdMemory.project_name))||(0xff==g_IdMemory.project_name[0]) ){				
				uBuzzerTimes( BUZZER_ONE_TIME );
				uTjc4832tSetPage( TJC_WARN_PAGE );        /*����Ϊǿ�ƾ���ҳ*/		
				if( EN_ON==gp_stuConfigFile->uCutEnCu ){
					uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"No ID" );	//û��ID��
				}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
					uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"��ID" );	     //û��ID��
				}else{
					uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"No ID" );	//û��ID��
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
		OSSemPend( (OS_SEM *)&g_ReadIDsem, 0,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	/* �ȴ���ID���ź���*/			
		if( OS_ERR_NONE==err ){			
			/* ���ID�� */					
			if( NULL==_gp_ID ){					
				OSTimeDlyHMSM(0, 0, 0, 500,OS_OPT_TIME_HMSM_STRICT,&err);	//������Ҫ����			
			}else{		
				if( !BSP_ReadPin(ID_DETECT_PORT,ID_DETECT_PIN) ){
					OSMutexPend( (OS_MUTEX *)&g_MutIDTask, 0,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err );	              /*�ȴ��ź���*/					
					
					uClearIdData();            /* ���ID���� */					
//					/* ��Ҫ��6�ſ����� */				
					uConfirmPage( TJC_WARN_PAGE );            /* ����Ϊ */
					uTjc4832tSetLableValuePco( TJC_WARN_PAGE,WARN_ID_NUM,TJC_GREEN );        /* ����Ϊ��ɫ���� */
					uTjc4832tSetLableValuePco( TJC_WARN_PAGE,WARN_ID_NUM,TJC_GREEN );        /* ����Ϊ��ɫ���� */
					uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Reading ID Card ..." );
					
					uTjc4832tTouchEnable( TJC_TOUCH_OFF );                                             /* ��ҳ�رմ��� */					
					uRecError = uReadIdItem();                        /* ��id�� */					
					
//					uTjc4832tSetPage( TJC_WARN_PAGE );                /* ����Ϊ */
					OSTimeDlyHMSM(0, 0, 0, 100,OS_OPT_TIME_HMSM_STRICT,&err);
//					/* Ч���Ƿ�ɹ� ���ɹ��͹ػ� */
//					if( EXE_SUCCEED!=uConfirmPage( TJC_PROMPTER_PAGE ) ) {
//						if( EXE_FAILED==uConfirmIdCardPage(TJC_PROMPTER_PAGE) ){                           /* ҳ������Ʋ�ͬ�� ֻ��ǿ�ƹػ� */
//							vPromptShutDown( POWER_FORCE,POWER_FORCE_03_SECOND );                          /* ����ʾ�ػ� ����ȡ�� */
//						}
//					}
					
					if( EXE_SUCCEED==uRecError ){		
						uIdDisplay( uGetIdCountValue() );	                                      /* ��ʾ��ǰ��ȡ��ID���� */
//						uTestInformationRefresh();                                                /* ��ʾ������Ϣ */
//						uTestInformationRefresh();                                                /* ��ʾ������Ϣ */
					}
					uTjc4832tTouchEnable( TJC_TOUCH_ON );                                              /* ��ҳ�򿪴��� */

					OSMutexPost( (OS_MUTEX *)&g_MutIDTask,OS_OPT_POST_NO_SCHED,&err );                                            /*�ͷ��ź��� */
				}else{
					uTjc4832tSetPage( TJC_WARN_PAGE );        /*����Ϊ*/
					uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Please insert the ID card" );		
					uBuzzerTimes( BUZZER_ONE_TIME );
				}  		
			}	
			
		}else{
			OSTimeDlyHMSM(0, 0, 0, 500,OS_OPT_TIME_HMSM_STRICT,&err);	 /* ��ʱ500ms   */
		}
	}
}

//��¼����������
static void TaskLogIn(void *p_arg)
{
	OS_ERR err;
	
	p_arg = p_arg;
	
	while(1)
	{
		OSSemPend( (OS_SEM *)&g_ResetLogInsem,0,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	          /* �ȴ��ź��� */	
		if( OS_ERR_NONE==err ){
#if LOGIN_CODE
			vLogInInit();                                 /* ��¼ϵͳ��ʼ�� */
#else
			uUserPasswordInit();
#endif
		}else{
			OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	 /* ��ʱ10ms   */
		}
		
		if( EXE_FAILED==uSemclear( (OS_SEM*)&g_ResetLogInsem ) ){                /* ����ٵ�½�ź��� �״��ϵ������Ļ�͵�½��ťͬʱ���� */
#if DEBUH_UART1	
			myprintf( "ClearSem Error  \r\n" );
#endif
		}
	}
}

//ʱ�����������
static void TaskUpdataTime(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
		
	while( RTC_Init() ){		                                                        //RTC��ʼ��	��һ��Ҫ��ʼ���ɹ�				
		uTjc4832tSetPage( TJC_WARN_PAGE );                                              /*����Ϊǿ�ƾ���ҳ*/
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"RTC ERROR!" );	//������Ҫ����//"RTC ERROR!" //"RTC Trying...");	
		uBuzzerTimes( BUZZER_ONE_TIME );		
	}
	
	while(1)
	{		
		OSTimeDlyHMSM(0, 0, 0, 990,OS_OPT_TIME_HMSM_STRICT,&err);	                    //��ʱ//OSTimeDlyHMSM(0, 1, 1, 900);	//��ʱ		
		
		if( !bMotorResetStatus() ){
			UpdataRealTime( REAL_TIME_ON );	                                            /* ʵʱˢ����Ļ REAL_TIME_OFF */					
		}
	}
}

//�ػ�������  ���ȼ����ĸ�
static void TaskPowerOn(void *p_arg)
{
	OS_ERR err;
	
	p_arg = p_arg;
	
	bFuncFlashP25Q32hInit();                                                                        /* ��ʼ��FLASH */
#if ERASE_SECTOR_CONFIG
	uEraseSectorFromStartToEnd( (SPIFLASH_CONFIG_FILE_BASE_ADDR/SPIFLASH_PAGE_BASE_ADDR),P25Q32H_CLEAR_SECTOR );
	while(1)
	{
		OSTimeDlyHMSM(1, 0, 0, 0,OS_OPT_TIME_HMSM_STRICT,&err);	                            /* ��ʱ10ms   */
	}
#else	
	bFuncIFP300FlashValInit();																        /* ��ʼ��Ĭ����Ϣ */
	uMax5402GainInitSet( gp_stuConfigFile->uMax5402Gain,UI_N_PROMPT );	                            /* Max5402eua��ʼ�� ���SPI */
	uResetMotorInteriorStauts( UI_N_PROMPT );                                                       /* ����������ʾ��λ��� */ 
	ChooseCoefficient( BUTTON_VALUE_SERUM );                                                        /* ÿ�ο�����Ĭ����Serum ��������������Ϣ��ס */	
//	uWifiPowerInit( 2 );                                                                            /* WIFI����һ�µ�Դ */
	iElectricInit();                                                                                /* ��Դ��ʼ������ */
	
	while(1)
	{
		OSSemPend( (OS_SEM *)&g_PowerOnsem,0,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err );	/*�ȴ��ź���*/
		
		if( OS_ERR_NONE==err ){
			vShutDownPrompter();                                                                    /* �ػ���ʾ ��Ҫ�û��Լ�ȷ�� */
		}else{
			OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	                            /* ��ʱ10ms   */
		}	
	}
#endif
}

#if 0
//WIFI����������
static void TaskWifiReceive(void *p_arg)
{
	OS_ERR err;	
	uint8_t uWifiArrTemp[USART2_REC_LEN] = {0};
	
	p_arg = p_arg;
	
	while(1)
	{
		OSSemPend( (OS_SEM *)&g_WifiReceive,WAIT_SEM_7_TIME,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);   /* �ȴ�WIFI�ź��� ��Ӧ���ȼ���ҪС��ָ��������ȼ� */
		
		if( OS_ERR_NONE==err ){
//			vCopyWifiBlueBuffer( uWifiArrTemp );                                                                        /* COPY���� */
//			vClearWifiBlueBuffer();                                                                                     /* ���WIFI���� */
			
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
			OSTimeDlyHMSM(0,0,5,0,OS_OPT_TIME_HMSM_STRICT,&err);                                                    /* ��ʱ500ms */
		}	
	}
}
#else
//WIFI����������
static void TaskWifiReceive(void *p_arg)
{
	OS_ERR err;	
//	uint8_t uWifiArrTemp[USART2_REC_LEN] = {0};
	
	p_arg = p_arg;
	
	while(1)
	{
		if( TRANSFER_AP_STATION==g_uTransparentStatus ){
//			OSSemPend( (OS_SEM *)&g_WifiReceive,WAIT_SEM_4_TIME,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);   /* �ȴ�WIFI�ź��� ��Ӧ���ȼ���ҪС��ָ��������ȼ� */
//			
//			if( OS_ERR_NONE==err ){
//				vCopyWifiBuffer( uWifiArrTemp );                                                                        /* COPY���� */
//				vClearWifiBuffer();                                                                                     /* ���WIFI���� */
//				
//#if DEBUH_UART1
//				myprintf( "uWifiReceive:%s \r\n",uWifiArrTemp );
//#endif		
//				memset( uWifiArrTemp,0,sizeof(uWifiArrTemp) );
//			}else{
//				OSTimeDlyHMSM(0,0,5,0,OS_OPT_TIME_HMSM_STRICT,&err);                                                    /* ��ʱ500ms */
//			}	
			OSTimeDlyHMSM(0,0,30,0,OS_OPT_TIME_HMSM_STRICT,&err);                                                    /* ��ʱ500ms */
		}else{			
			OSTimeDlyHMSM(0,0,30,0,OS_OPT_TIME_HMSM_STRICT,&err);                                                        /* ��ʱ500ms */
		}
	}
}
#endif

//WIFI����������
static void TaskWifiSend(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;	
	
	OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);                                                             /* �ȴ�Wifi���� */	
	uWifiInit();                                                                                                        /* ��ʼ�� */ 	
	uClassicBluetoothInit();                                                                                            /* ����������ʼ�� */
																									                    
	while(1)                                                                                                            
	{                                                                                                                   
		if( !bMotorResetStatus() ){			
			
			OSTimeDlyHMSM(0, 0, 5, 0,OS_OPT_TIME_HMSM_STRICT,&err);	  
//			OSTimeDlyHMSM(0, 1, 0, 0,OS_OPT_TIME_HMSM_STRICT,&err);	
			
#if WIFI_AUTO_UP			
			if( EXE_SUCCEED==uWifiConnentEnv() ){                                                                       /* ���ȼ��������WIFI���ܺ��� */
//				uWifiUploaTheHistoryData();	  
//				uLisSendTest();
				
				uLisSendHistory();                                                   /* �Զ��ϴ� */
			}
#endif
			
		}else{
			OSTimeDlyHMSM(0, 1, 0, 0,OS_OPT_TIME_HMSM_STRICT,&err);	
		}		
	}
}

//��̨�ػ�������
static void TaskBackShutDown(void *p_arg)
{
	OS_ERR err;
	OS_ERR uTempErr;
	OS_MSG_SIZE size = 0;
	void *puShutTempArrMsg = NULL;
	
	p_arg = p_arg;
	while(1)
	{
		puShutTempArrMsg = OSQPend( (OS_Q *)&g_ShutDownMsgQue,(OS_TICK )0,(OS_OPT )OS_OPT_PEND_BLOCKING,(OS_MSG_SIZE *)&size,(CPU_TS *)NULL,&uTempErr );   /* �ȴ�һ����Ϣ */		
		if( OS_ERR_NONE==uTempErr ){
#if DEBUH_UART1
			myprintf( "uShutdown:%d ",*(uint8_t *)puShutTempArrMsg );
#endif				
			vBackgrounderShutDown( (uint8_t *)puShutTempArrMsg );
		}else{
			OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	 /* ��ʱ10ms   */
#if DEBUH_UART1
			myprintf( "uTempShutPendErr:%d ",uTempErr );
#endif	
		}
	}
}

//led1�����������ػ�ȷ��
static void led1_task(void *p_arg)
{
	OS_ERR err = OS_ERR_NONE;
	OS_ERR uTempErr = OS_ERR_NONE;
	OS_MSG_SIZE size = 0;
	void *puTempArrMsg = NULL; 

	p_arg = p_arg;
	
	while(1)
	{
		puTempArrMsg = (uint8_t *)OSQPend( (OS_Q *)&g_TouchSpcMsgQue,(OS_TICK )0,(OS_OPT )OS_OPT_PEND_BLOCKING,(OS_MSG_SIZE *)&size,(CPU_TS *)NULL,&uTempErr );   /*�ȴ�һ����Ϣ*/			
		if( OS_ERR_NONE==uTempErr ){
			OSTimeDlyHMSM(0, 0, 0, 500,OS_OPT_TIME_HMSM_STRICT,&err);      /* 300-500 */		
			
			UpdateSpcUI( puTempArrMsg );		                                                                      /* ����UI */ 
		}else{	
#if DEBUH_UART1
			myprintf( "uTempSpcPendErr:%d ",uTempErr );
#endif				
			OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,&err);	 /* ��ʱ10ms   */	
		}
		if( NULL!=puTempArrMsg ){
			free( puTempArrMsg );                                                                                 /* �ͷ��ڴ� */
		}
	}
}

#if TEST_STACK_ON
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
