#include "Func_LogIn.h"
#include "Func_MA1100_User_Interface.h"
#include "Global_Variable.h"

uint8_t uUserPasswordInit( void )
{
	OS_ERR err = OS_ERR_NONE;
	static uint8_t uTempUser[6] = "admin";
	static uint8_t uTempArr[7] = "888888";
	//uint8_t uArrStr[24] = {0};
	//uint8_t i = 0;
	uint8_t uRecStatus = 0;	
//	int16_t iRecPageIDTemp = 0;
	
	OSTimeDlyHMSM(0, 0, 0, 100,OS_OPT_TIME_HMSM_STRICT,(OS_ERR *)&err);                               /* ������Ҫ���� */	
	uTjc4832tSetVariableValue( TJC_LOGIN_PAGE,CUT_EN_CH_BUTTON,gp_stuConfigFile->uCutEnCu );          /* ʹ�����Ļ���Ӣ��汾 */
	uTjc4832tSetLableValue( TJC_LOGIN_PAGE,LOGIN_PAGE_VERVIS_ID,(uint8_t *)DIS_FIRMWARE_VERSION );    /* ��¼ҳ����ʾ�汾�� */		
#if DEBUH_UART1	
	myprintf( "%s Firmware:%s_%s \r\n",__DATE__,MCU_FIRMWARE_VERSION,__TIME__ );
#endif
	
	if( EXE_FAILED==uConfirmPage( TJC_LOGIN_PAGE ) ){
		OSTimeDlyHMSM(0, 0, 0, 300,OS_OPT_TIME_HMSM_STRICT,(OS_ERR *)&err);                       /* ������Ҫ���� */	
		uTjc4832tSetPage( TJC_LOGIN_PAGE );
	}
			
	getPasswordStatus( &g_stuAutoRemenber );      /* ��ȡ����״̬ */
	if( 0xff!=g_stuAutoRemenber.uremember ){
		if( (1==g_stuAutoRemenber.uremember)||(0==g_stuAutoRemenber.uremember) ){
			uTjc4832tSetChexkBox( TJC_LOGIN_PAGE,LOGIN_CID_0NUM,g_stuAutoRemenber.uremember );          /* ��ʾ��ǰ����״̬ */
			uTjc4832tSetVariableValue( TJC_LOGIN_PAGE,LOGIN_VAL_1NUM,g_stuAutoRemenber.uremember );     /* ���ñ���ֵ������״̬ͬ�� */
		}else{
			g_stuAutoRemenber.uremember = 1;                                                            /* ���������ס���� */
			uTjc4832tSetChexkBox( TJC_LOGIN_PAGE,LOGIN_CID_0NUM,g_stuAutoRemenber.uremember );          /* ��ʾ��ǰ����״̬ */
			uTjc4832tSetVariableValue( TJC_LOGIN_PAGE,LOGIN_VAL_1NUM,g_stuAutoRemenber.uremember );     /* ���ñ���ֵ������״̬ͬ�� */
		}
	}else{
		g_stuAutoRemenber.uremember = 0;                                                                /* ���ο�������ס���� */
		uTjc4832tSetChexkBox( TJC_LOGIN_PAGE,LOGIN_CID_0NUM,g_stuAutoRemenber.uremember );              /* ��ʾ��ǰ����״̬ */
		uTjc4832tSetVariableValue( TJC_LOGIN_PAGE,LOGIN_VAL_1NUM,g_stuAutoRemenber.uremember );         /* ���ñ���ֵ������״̬ͬ�� */
	}
	
	if( 1==g_stuAutoRemenber.uremember ){    /* ��ס������ʾ */
		uTjc4832tSetLableValue( TJC_LOGIN_PAGE,LOGIN_ID_0NUM,(uint8_t *)uTempUser );
		uTjc4832tSetLableValue( TJC_LOGIN_PAGE,LOGIN_ID_1NUM,(uint8_t *)uTempArr );
	}else{
		uTjc4832tSetLableValue( TJC_LOGIN_PAGE,LOGIN_ID_0NUM,(uint8_t *)"" );
		uTjc4832tSetLableValue( TJC_LOGIN_PAGE,LOGIN_ID_1NUM,(uint8_t *)"" );
	}
	
	g_stuAutoRemenber.uloginstatus = LOGIN_ENTER;
	
	while( 1 ){				
		OSSemPend( (OS_SEM *)&g_LogInsem,0,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,&err );	            /* �ȴ��ź��� */	
		if( OS_ERR_NONE==err ){
			uRecStatus = 0 ;                    /* ״̬λ���� */
			if( 0==strncmp((const char*)uTempUser,(const char*)g_userName,sizeof(uTempUser)) ){
				uRecStatus =1;
			}
			if( 0==strncmp((const char*)uTempArr,(const char*)g_userNamePas,sizeof(uTempArr)) ){
				uRecStatus = (uRecStatus)|(0x01<<1);
			}
			
			if( 3==uRecStatus ){                               /* �����û�������ȷ */
				uTjc4832tSetPage( TJC_TEST_PAGE );             /* ����ȫѪ���Խ��� */			
				memset( g_userName,0,USER_NAME_SIZE+1 );       /* ��¼�ɹ������ */ 
				memset( g_userNamePas,0,USER_NAME_SIZE+1 );    /* ��¼�ɹ������ */
				g_stuAutoRemenber.uloginstatus = LOGIN_EXIT;   /* �˳���¼ϵͳ */
				remPasswordStatus( &g_stuAutoRemenber );       /* ��¼����״̬ */	
				uTestInformation();                            /* ��ʾ������Ϣ */
				return EXE_SUCCEED;
			}else if( 0==uRecStatus ){
				uTjc4832tSetPage( TJC_WARN_PAGE );         /*  */
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"User and Password error" );
			}else if( 1==uRecStatus ){
				uTjc4832tSetPage( TJC_WARN_PAGE );         /*  */
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Password error" ); 
			}else if( 2==uRecStatus ){
				uTjc4832tSetPage( TJC_WARN_PAGE );         /*  */
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"User error" ); 
			}else{
				uTjc4832tSetPage( TJC_WARN_PAGE );         /*  */
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Unknown error" ); 
			}
		}else{
			OSTimeDlyHMSM(0, 0, 0, 10,OS_OPT_TIME_HMSM_STRICT,(OS_ERR *)&err);	             /*  */
		}		
	}
}

uint8_t uLoginBottonValue( void )
{
	OS_ERR err = OS_ERR_NONE;
	
	if( LOGIN_EXIT==g_stuAutoRemenber.uloginstatus ){
		uResetLoginBottonValue();
	}
	
	OSSemPost( (OS_SEM *)&g_LogInsem,OS_OPT_POST_NO_SCHED,&err );                  /*�ͷ��ź��� ��¼ȷ�� */	  
	
	return EXE_SUCCEED;
}

uint8_t uResetLoginBottonValue( void )
{
	OS_ERR err = OS_ERR_NONE;
	
	OSSemPost( (OS_SEM *)&g_ResetLogInsem,OS_OPT_POST_NO_SCHED,&err );
	
	return EXE_SUCCEED;
}

uint8_t vForceWarn( void )
{	
	uTjc4832tSetPage( TJC_WARN_PAGE );                                          /* ��ʱ����Ϊ ���� */
	uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Important warning ");	//
	
	uBuzzerTimes( BUZZER_THREE_TIME );
	
	vPromptShutDown( POWER_FORCE,POWER_FORCE_03_SECOND ); 
	
	return EXE_SUCCEED;
}

uint8_t vPromptElectricQuantity( void )
{	
	uTjc4832tSetPage( TJC_WARN_PAGE );                                          /* ��ʱ����Ϊ ���� */
	if( EN_ON==gp_stuConfigFile->uCutEnCu ){
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Low power" );	             //
	}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"�͵���" );	             //
	}else{
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Invalid" );	             //
	}
	uBuzzerTimes( BUZZER_ONE_TIME );
	
	return 0;
}

uint8_t vPromptShutDown( uint8_t uPrompt,uint8_t uSecond )
{
	static uint8_t uRecTime = 0;    /*ȫ�ֱ������ܷ�����Ϣ*/
	uint8_t uReclen = 0;
	uint8_t uArrStr[48] = {0};
	OS_ERR uTempErr = OS_ERR_NONE;
	OS_ERR err = OS_ERR_NONE;

	if( !(0<uSecond)&&(uSecond<255) ){
		return EXE_FAILED;
	}
	uRecTime = 0;
	uTjc4832tSetPage( TJC_WARN_PAGE );                                                        /* �ɻָ����� */
	if( EXE_FAILED==uSemclear( (OS_SEM*)&g_WarnCencle ) ) {                                            /* ����ź��� */
		uConfirmPage( TJC_WARN_PAGE );
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)" Mandatory shutdown" );	
		OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);	
		vShutDown();                                                                          /* �ػ� */
	}
	uConfirmPage( TJC_WARN_PAGE ); 
	
	for( uRecTime=uSecond;uRecTime>0;uRecTime-- ){	
		sprintf( (char *)uArrStr,"%d",uRecTime );
		uReclen = strlen( (const char *)uArrStr );
		sprintf( (char *)uArrStr+uReclen,"%s",(const char *)" second" );
		uReclen = strlen( (const char *)uArrStr );
		sprintf( (char *)uArrStr+uReclen,"%s",(const char *)" left." );
		uReclen = strlen( (const char *)uArrStr );		
		if( POWER_FORCE==uPrompt ){ 
			sprintf( (char *)uArrStr+uReclen,"%s",(const char *)" Force " );
		}else{ 
			//sprintf( (char *)uArrStr+uReclen,"%s",(const char *)" Can " );
		}
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)uArrStr );	//
		
		if( POWER_FORCE==uPrompt ){    /* ����ȡ������ */
			OSSemPend( (OS_SEM *)&g_WarnCencle, 150, OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	   	/* �ȴ������ź��� ��Ҫ����150 */
			if( OS_ERR_NONE==err ){
				break;
			}
		}else{
			OSSemPend( (OS_SEM *)&g_WarnCencle, 150, OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	   	/* �ȴ������ź��� */
			if( OS_ERR_NONE==err ){
				return EXE_FAILED;
			}
		}	
		
		OSTimeDlyHMSM(0, 0, 0, 60,OS_OPT_TIME_HMSM_STRICT,&err);	 /* ѭ����һ�� 190+750+60=1000 */	
	}
	
	if( POWER_FORCE==uPrompt ){
		if( uRecTime>1 ){
			OSQPost( (OS_Q *)&g_ShutDownMsgQue,(void *)(&uRecTime),(OS_MSG_SIZE )1,OS_OPT_POST_FIFO+ OS_OPT_POST_NO_SCHED,&uTempErr );    /*����һ����Ϣ*/
			if( OS_ERR_NONE!=uTempErr ) {                                     /*����һ����Ϣ*/
#if DEBUH_UART1
				myprintf( "ShutDown uTempPostErr:%d ",uTempErr );
#endif	
			}
			return uRecTime;                                                  /* ��̨�����ػ� */
		}else{
			vClassifyShutdown();                                              /* ���������͹ػ� */
		}
	}else{
		vShutDown();                          /* �ػ� */
	}
	
	return EXE_SUCCEED;
}

uint8_t vShutDown( void )
{
	uCtrlPower( CTRL_POWER_OFF );        /* �ػ���Դ */	
	
	return EXE_SUCCEED;
}

uint8_t vShutDownPrompter( void )
{
	OS_ERR err;
	
	uint8_t i=0;
	for( i=0;i<10;i++ ){   /* ������ʱ��� ���� */
		OSTimeDlyHMSM(0, 0, 0, 500,OS_OPT_TIME_HMSM_STRICT,&err);	//
		if( BSP_ReadPin(POWER_AUTO_CONTROL_PORT,POWER_AUTO_CONTROL_PIN) ){  /* �����¶Ȳ��� */
			uTemperatrueDisplay();
			return EXE_FAILED;
		}
	}
	
	if( !BSP_ReadPin(POWER_AUTO_CONTROL_PORT,POWER_AUTO_CONTROL_PIN) ){
		if( EN_ON==gp_stuConfigFile->uCutEnCu ){
			uPrompterWarn( (uint8_t *)"Shutdown?" ); //(uint8_t *)"Are you sure you want to turn it off" );	                  /*  */
		}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
			uPrompterWarn( (uint8_t *)"�ػ�?" ); //(uint8_t *)"Are you sure you want to turn it off" );               /*  */
		}else{
			uPrompterWarn( (uint8_t *)"Invalid" ); //(uint8_t *)"Are you sure you want to turn it off" );	             //
		}
	}
	
	return EXE_SUCCEED;
}

uint8_t vBackgrounderShutDown( uint8_t* uSecond )
{
	OS_ERR err;
	uint8_t i = 0;
	
	for( i=(*uSecond);i>0;i-- ){
		OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);	
	}
	
	vClassifyShutdown(); /* ���������͹ػ� */
		
	return EXE_SUCCEED;
}

/* ���������͹ػ� */
void vClassifyShutdown( void )
{
	OS_ERR err;
	
	switch( g_ShutdownError ){
		case VOLTAGE_TIMES:
			g_ShutdownError = 0;
			if( BSP_ReadPin(CHARGE_STATUS_PORT,CHARGE_STATUS_PIN) ){          /* ʹ�õ��ʱ */
				OSTimeDlyHMSM(0, 0, 0, 100,OS_OPT_TIME_HMSM_STRICT,&err);	
				if( BSP_ReadPin(CHARGE_STATUS_PORT,CHARGE_STATUS_PIN) ){          /* ʹ�õ��ʱ */
					vShutDown();                      /* �ػ� */
				}
			}
			break;
			
		default:
			vShutDown();                      /* �ػ� */
			break;
	}
}

//��ȡ��ǰ�Ƿ��Ǽ�ס����
AUTO_REMEMBER* getPasswordStatus( AUTO_REMEMBER* pstuAutoRem ) 
{
	SPI_Flash_Read( (uint8_t *)pstuAutoRem,SPIFLASH_AUTO_REMEM_ADRR,sizeof( AUTO_REMEMBER ) );

	return pstuAutoRem;
}

//��¼��ǰ�Ƿ��Ǽ�ס����
uint8_t remPasswordStatus( AUTO_REMEMBER* pstuAutoRem ) 
{
	if( EXE_SUCCEED==SPI_Flash_Write_Page( (uint8_t *)pstuAutoRem,SPIFLASH_AUTO_REMEM_ADRR,sizeof( AUTO_REMEMBER ) ) ){
	
	}else{
#if DEBUH_UART1		
		myprintf( "FlashWriteError \r\n" );
#endif
	}

	return EXE_SUCCEED;
}

#if LOGIN_CODE
//��ʼ��
void vLogInInit( void )
{
	uint8_t fsize = 0;
	
	fsize = getFileSize();
	
	if((0x00==fsize)||(0xFF==fsize)){  //����ʹ�����ʱ��Ҫ��������
		setPwd( PWD_SET );             /* ��ʼ�����������ֱ����֤������� */
	}else if( !checkPwd(PWD_CHECK) ){  //�ٴ�ʹ�����ʱ��Ҫȷ������
#if DEBUH_UART1	
		myprintf("Later On ��\n");       //
#endif
	}else{	
		OSTimeDlyHMSM(0, 0, 0, 200);	//��ʱ
		uTjc4832tSetPage( TJC_TEST_PAGE );        /* ����ȫѪ����ҳ�� */
		uTestInformation();
		//SetPage( MAIN_PAGE );          /* ������ҳ */
	}
	
}

//����Ҫ��֤�����ʼ��
void vLogNoPwdInInit( void )
{
	uint8_t fsize = 0;
	
	fsize = getFileSize();
	
	if((0x00==fsize)||(0xFF==fsize)){  //����ʹ�����ʱ��Ҫ��������
		setPwd( PWD_SET );             /* ��ʼ�����������ֱ����֤������� */
	}else{	
		OSTimeDlyHMSM(0, 0, 0, 200);	//��ʱ
		/* �Զ������½��ť */		
		//uTjc4832tSetPage( TJC_TEST_PAGE );        /* ����ȫѪ����ҳ�� */
		uTestInformation();
	}
	
}

//���û��޸�����
void setPwd(int flag)
{	
	uint8_t i = 0;	
	uint8_t err;
	uint8_t RecDataSize = USER_DATA_SIZE;
	STU stu;	
	char pwdNew1[PWD_LEN+1]={0}, pwdNew2[PWD_LEN+1]={0}, userName[10]={0};
		
	if(flag == PWD_SET){
#if DEBUH_UART1	
		myprintf("Fist Use ��\n");
#endif		
		/*������ҳ��*/
		OSTimeDlyHMSM(0, 0, 0, 300);	//������Ҫ����	
		uTjc4832tSetPage( TJC_REGISTER_PAGE );      /*����Ϊע��ҳ*/
		g_stuAutoRemenber.uauto = 1;                /* Ĭ���Զ���½ */
		g_stuAutoRemenber.uremember =1;             /* Ĭ�ϼ�ס���� */
		uTjc4832tSetChexkBox( TJC_REGISTER_PAGE,RIGISTER_CID_0NUM,g_stuAutoRemenber.uauto );
		uTjc4832tSetChexkBox( TJC_REGISTER_PAGE,RIGISTER_CID_1NUM,g_stuAutoRemenber.uremember );
		uTjc4832tSetLableValue( TJC_REGISTER_PAGE,RIGISTER_ID_0NUM,(uint8_t *)"" );
		uTjc4832tSetLableValue( TJC_REGISTER_PAGE,RIGISTER_ID_1NUM,(uint8_t *)"" );
		uTjc4832tSetLableValue( TJC_REGISTER_PAGE,RIGISTER_ID_2NUM,(uint8_t *)"" );
	}else if( (flag==PWD_ALTER)&&(!checkPwd(PWD_ALTER)) ){  //У��ԭ������ʧ��
		uTjc4832tSetPage( TJC_WARN_PAGE );         /*����Ϊǿ�ƾ���ҳ*/
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Password Error!" );
	}

	do{
		if(flag == PWD_SET){
#if DEBUH_UART1				
			myprintf("Start Input Password: ");
#endif

			for(i=0; i<PWD_ERROR_ALL_TIMES; i++){			
				OSMutexPend(gp_LogInsem, 0, &err);	/*�ȴ��ź���*/				
				memcpy( userName,(const char *)g_userRegistName,USER_NAME_SIZE );
				memcpy( pwdNew1,(const char *)g_userRegistNamePas,PWD_LEN );
				memcpy( pwdNew2,(const char *)g_userRegistNamePas1,PWD_LEN );	
			
				if( (strlen((const char *)userName)&&strlen((const char *)pwdNew1)&&strlen((const char *)pwdNew2)) ){
					if( (1==g_stuAutoRemenber.uauto)&&(0==g_stuAutoRemenber.uremember) ) {
						uTjc4832tSetPage( TJC_WARN_PAGE );           /*����Ϊǿ�ƾ���ҳ*/
						uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Remember the password" );
					}else{
						remPasswordStatus( &g_stuAutoRemenber );      /* ��¼����״̬ */
						break;						
					}					
				}else{
					if( (PWD_ERROR_ALL_TIMES-1)==i ){
						uTjc4832tSetPage( TJC_WARN_PAGE );         /*����Ϊǿ�ƾ���ҳ*/
						uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Password error too" );  /*"Password error too many times!" */
						/* ��Ҫ���� */
					}else{
						uTjc4832tSetPage( TJC_WARN_PAGE );         /*����Ϊǿ�ƾ���ҳ*/
						uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Password error!" ); 
					}
				}
			}						
		}else if(flag == PWD_ALTER){
#if DEBUH_UART1	
			myprintf("Input New Password: ");
			myprintf("Password3: ");
#endif
			OSMutexPend(gp_LogInsem, 0, &err);	/*�ȴ��ź���*/	
			memcpy( pwdNew1,(const char *)g_userRegistNamePas,PWD_LEN ); //
			memcpy( pwdNew2,(const char *)g_userRegistNamePas1,PWD_LEN ); //		
		}

		if(strcmp(pwdNew1, pwdNew2) == 0){
			if(flag == PWD_SET){
				
				SPI_Flash_Write_Page( &RecDataSize,SPIFLASH_USER_NUMBER_ADRR,USER_FILE_SIZE );				
				stu.id = 1;
				memcpy( (char *)stu.username, userName,USER_NAME_SIZE );
				memcpy( (char *)stu.password, pwdNew1,USER_PASSWORD_SIZE );			
				SPI_Flash_Write_Page( (uint8_t *)&stu,SPIFLASH_USER_BASE_ADDR,USER_DATA_SIZE );
								
				//updateFile(); 			              /* �����ļ� */
#if DEBUH_UART1	
				myprintf("Set Password Succeed...");
#endif		
				
				if( !checkPwd(PWD_CHECK) ){  //�ٴ�ʹ�����ʱ��Ҫȷ������
#if DEBUH_UART1	
					myprintf("Later On ! \n");       //
#endif
				}else{	
					uTjc4832tSetPage( TJC_TEST_PAGE );        /* ����ȫѪ����ҳ�� */
					uTestInformation();
				}
				
			}else if(flag == PWD_ALTER){
#if DEBUH_UART1	
				myprintf("Alter Password Succeed...");
#endif					
				updateFile(); 			              /* �����ļ� */	
			}
			break;
		}else{
			uTjc4832tSetPage( TJC_WARN_PAGE );         /*����Ϊǿ�ƾ���ҳ*/
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Two inconsistencies!" ); 	  

#if DEBUH_UART1
			myprintf("Again Input...");
#endif
		}
	}while(1);
}

int checkPwd(int flag)
{
	NODE *preNode = NULL, *thisNode = NULL;
	uint8_t fsize = 0;
	uint8_t usernum = 0;
	STU stu;
	
	uint8_t err = 0;
	uint8_t userName[USER_NAME_SIZE+1] = {0};
	uint8_t pwd[PWD_LEN+1] = {0}, pwdFile[PWD_LEN+1] = {0};
	uint8_t i=0 /*ѭ�����Ʊ���*/, n /*����������*/;
	
	OSTimeDlyHMSM(0, 0, 0, 300);	//������Ҫ����	
	
	
	uTjc4832tSetPage( TJC_LOGIN_PAGE );      /*����Ϊ��¼ҳ*/
//	SetEditValue( LOGIN_PAGE,USER_NAME_CONTROL_ID,userName );
//	SetEditValue( LOGIN_PAGE,USER_PWD_CONTROL_ID,pwd );	
//	SetBackLight( BACK_LIGHT_2_VALUE );            /*����Ĭ�ϱ���*/

	getPasswordStatus( &g_stuAutoRemenber );      /* ��ȡ����״̬ */
	
	fsize = getFileSize();
	if( fsize ){  //����ļ��������ݣ���ô��������
		usernum = fsize/USER_DATA_SIZE;
		
		while( i<usernum ){			
			//stu.id = i;		
			SPI_Flash_Read( &stu.id,(SPIFLASH_USER_BASE_ADDR+(i*USER_DATA_SIZE)),USER_ID_SIZE );
			SPI_Flash_Read( stu.username,((SPIFLASH_USER_BASE_ADDR+(i*USER_DATA_SIZE))+USER_ID_SIZE),USER_NAME_SIZE );
			SPI_Flash_Read( stu.password,(((SPIFLASH_USER_BASE_ADDR+(i*USER_DATA_SIZE))+USER_ID_SIZE)+USER_NAME_SIZE),USER_PASSWORD_SIZE );
			
			thisNode = (NODE*)calloc(sizeof(NODE));
			thisNode->data = stu;
			thisNode->next = NULL;
			
			if(preNode==NULL){  //�����һ���ڵ�
				g_stuHeader.link = thisNode;
			}else{  //���ǵ�һ���ڵ�
				preNode->next = thisNode;
			}
			preNode = thisNode;
			g_stuHeader.num++;
			
			i++;
		}
		
		if( 1==g_stuAutoRemenber.uremember ){   /*  �����ס����  ֱ�ӵ�½  */
			uTjc4832tSetLableValue( TJC_LOGIN_PAGE,LOGIN_ID_0NUM,(uint8_t *)stu.username );
			uTjc4832tSetLableValue( TJC_LOGIN_PAGE,LOGIN_ID_1NUM,(uint8_t *)stu.password );
		}else{
			uTjc4832tSetLableValue( TJC_LOGIN_PAGE,LOGIN_ID_0NUM,(uint8_t *)"" );
			uTjc4832tSetLableValue( TJC_LOGIN_PAGE,LOGIN_ID_1NUM,(uint8_t *)"" );
		}
		
		if( 1==g_stuAutoRemenber.uauto ){   /*  �Զ���½  ֱ�ӵ�½  */
			uTjc4832tClickEvent( LOGIN_ID_4NUM,TJC_PRESS_DOWN );    /* ����ʡ�� */
			uTjc4832tClickEvent( LOGIN_ID_4NUM,TJC_PUT_UP );        /* ����ʡ�� */
			return 1;
		}
				
		for(i=0; i<PWD_ERROR_ALL_TIMES; i++){
			if(flag == PWD_CHECK){
#if DEBUH_UART1
				myprintf("Input Pad: ");
#endif				
			}else if(flag == PWD_ALTER){
#if DEBUH_UART1				
				myprintf("Input Old Pad: ");
#endif
			}		
			
			OSMutexPend(gp_LogInsem, 0, &err);	/*�ȴ��ź���*/	
			memcpy( (char *)userName,(const char *)g_userName,USER_NAME_SIZE );
			memcpy( (char *)pwd,(const char *)g_userNamePas,PWD_LEN );
						
			if( (strlen((const char *)userName))&&(strlen((const char *)pwd)) ){			
#if DEBUH_UART1					
				myprintf("Input userName:%s pwd:%s\r\n",userName,pwd );
#endif	
				
				findUserByName( userName,pwdFile );  /* �����û����ҵ����� */			

				if( strcmp( (const char *)pwdFile,(const char *)pwd)==0 ){
					break;
				}else{
					n = PWD_ERROR_TIMES - i - 1;
					if(n == 0){	
						uTjc4832tSetPage( TJC_WARN_PAGE );         /*����Ϊǿ�ƾ���ҳ*/
						uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Input Too Much" ); 																		
#if DEBUH_UART1					
						myprintf("Input Too Much ...");
#endif		
					}else{
						uTjc4832tSetPage( TJC_WARN_PAGE );         /*����Ϊǿ�ƾ���ҳ*/
						uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Remainder" ); 	
#if DEBUH_UART1
						myprintf("Remainder: %d ...", n);
#endif
					}
				}
				
			}else{
				uTjc4832tSetPage( TJC_WARN_PAGE );         /*����Ϊǿ�ƾ���ҳ*/
				uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"No user password" ); 			
			}
			
			if( (PWD_ERROR_ALL_TIMES-1)==i ){
				uTjc4832tSetPage( TJC_WARN_PAGE );         /*����Ϊǿ�ƾ���ҳ*/
			}
		}
		
	}else{  //����ļ���û�����ݣ���ô����Ϊ��
		g_stuHeader.num = 0;
		g_stuHeader.link = NULL;
	}	

	return 1;
}

/**
* ��ȡ�û����������
* @param  pwd     char*  ����������ڴ���׵�ַ
* @param  pwdlen  int    �������󳤶�
**/
void getpwd(char *pwd, int pwdlen)
{

}

//��ʾ�����û���Ϣ
void showAllStu( void )
{
//	STU thisStu;
//	NODE *thisNode;
//	//float mathTotal = 0, cnTotal = 0, enTotal = 0, ageTotal = 0, oneTotal = 0, allTotal = 0;
//	//int manTotal = 0, womanTotal = 0;
//	//int n = g_stuHeader.num;

//	if(!g_stuHeader.num){
//#if DEBUH_UART1		
//		myprintf(" No User \r\n");
//#endif
//		return;
//	}
//#if DEBUH_UART1
//	myprintf("-------------------------\n");
//	myprintf("  ID  |  User  |  Pass \n");
//	myprintf("--------+--------+--------\n");
//#endif
//	for(thisNode=g_stuHeader.link; thisNode!=NULL; thisNode=thisNode->next){
//		thisStu = thisNode->data;
//#if DEBUH_UART1		
//		myprintf("   %.2d   | %-9s |   %-6s  \n", thisStu.id, thisStu.username, thisStu.password );
//#endif
//	}
//#if DEBUH_UART1
//	myprintf( "\nAll User%d \r\n", g_stuHeader.num );
//#endif
}

//����û���Ϣ
void addUserInfo( void )
{
	STU stu;	
	int	isStuExist = 0;
	NODE *thisNode, *pnode = (NODE*)calloc(sizeof(NODE));
	uint8_t tempname[20] = {0};
	//int id;
	
	getUserName( tempname );	
	//getStuID(&stu.id);
	//id = stu.id;

	if(g_stuHeader.num == 0){  //�������Ϊ�գ�ֱ�Ӳ���
		g_stuHeader.link = pnode;
		pnode->next = NULL;
	}else{  //�������Ϊ�գ���Ҫ��������ȷ������λ��
		for(thisNode=g_stuHeader.link; thisNode!=NULL; thisNode=thisNode->next){
			stu = thisNode->data;			
			if( strstr( (const char *)stu.username,(const char *)tempname) ){     //���û���Ϣ����
				free(pnode);
				isStuExist = 1;
				//break;
			}
			
			if( thisNode->next==NULL ){  //�����Ҫ������ĩβ����
				thisNode->next = pnode;
				pnode->next = NULL;
				break;
			}
		}
	}

	if(isStuExist){  //���û�����
#if DEBUH_UART1
			myprintf("Rrror: Add User \r\n");
#endif
	}else{  //���û�������
		g_stuHeader.num++;
		memcpy( (char *)&stu.id,(const char *)g_stuHeader.num,sizeof(int) );   /* check */
		memcpy( (char *)stu.username,(const char *)tempname,USER_NAME_SIZE );
		getUserPassword( stu.password );
		pnode->data = stu;
		updateFile();
#if DEBUH_UART1		
		myprintf("User Add Success \r\n");
#endif
	}
}

//ɾ���û���Ϣ
void deleteUserInfo( void )
{
	STU stu;
	NODE *thisNode, *preNode;
	getUserID(&stu.id);

	for(thisNode=g_stuHeader.link, preNode=NULL; thisNode!=NULL; preNode=thisNode, thisNode=thisNode->next){
		if(thisNode->data.id == stu.id){
			
			if(preNode == NULL){  //����ǵ�һ���ڵ�
				g_stuHeader.link = thisNode->next;
			}else{  //������ǵ�һ���ڵ�
				preNode->next = thisNode->next;
			}
			
			free(thisNode);
			g_stuHeader.num--;
			updateFile();	
#if DEBUH_UART1			
			myprintf("User Delete Success \r\n");
#endif
			return;
		}else if(thisNode->data.id > stu.id){
			break;
		}
	}
#if DEBUH_UART1
	myprintf("Rrror: Delete User \r\n");	
#endif
}

//�޸��û���Ϣ
void alterUserInfo( void )
{
	STU stu;
	NODE *thisNode;
	getUserID(&stu.id);

	for(thisNode=g_stuHeader.link; thisNode!=NULL; thisNode=thisNode->next){
		if(thisNode->data.id == stu.id){	
			getUserName( stu.username );
			getUserPassword( stu.password );
			
			thisNode->data = stu;
			updateFile();
#if DEBUH_UART1
			myprintf("User Alter Success \r\n");
#endif	
			return;
		}else if(thisNode->data.id > stu.id){
			break;
		}
	}
#if DEBUH_UART1
		myprintf("Rrror: Alter User \r\n");	
#endif	
}

//�����û�ID
void getUserID(uint8_t* id)
{
	while(1){
#if DEBUH_UART1
		myprintf("Input Id: ");
#endif	
		
		if( checkUserID(*id) ){
			break;
		}
	}
}

//����û�ID�Ƿ���ȷ
uint8_t checkUserID(uint8_t stuID)
{
	if(stuID <= 0 || stuID > MAX_USER_ID){
#if DEBUH_UART1
		myprintf("Rrror: MAX_USER_ID\r\n");
#endif	
		return 0;
	}
	return 1;
}

//�����û���
void getUserName( uint8_t name[] )
{
	PEDIT_MSG pstPedit = NULL;
	
	pstPedit = (PEDIT_MSG)g_Cmd_Buffer;
#if DEBUH_UART1	
	myprintf("Input User: ");
#endif		
	
	memcpy( (char *)name,(const char*)pstPedit->param,pstPedit->str_size );

}

//����û����Ƿ�Ϸ�
uint8_t checkUserName(uint8_t name[])
{
	if( strlen( (const char *)name) > USER_NAME_SIZE ){
#if DEBUH_UART1
		myprintf("Rrror: USER_NAME_SIZE\r\n");
#endif	
		return 0;
	}
	return 1;
}

//�����û�����
void getUserPassword( uint8_t password[] )
{
	PEDIT_MSG pstPedit = NULL;
	
	pstPedit = (PEDIT_MSG)g_Cmd_Buffer;
#if DEBUH_UART1	
	myprintf("Input User: ");
#endif	
	//GetTouchEditValue( USER_NAME_PAGE,USER_NAME_CONTROL_ID );
	memcpy( (char *)password,(const char*)pstPedit->param,USER_PASSWORD_SIZE );	
	
}

//����û������Ƿ�Ϸ�
uint8_t checkUserPassword(uint8_t password[])
{
	if( strlen( (const char *)password) > USER_PASSWORD_SIZE ){
#if DEBUH_UART1
		myprintf("Rrror: USER_NAME_SIZE\r\n");
#endif	
		return 0;
	}
	return 1;
}

//�����û�����ѯ������Ϣ
uint8_t *findUserByName( uint8_t *uName,uint8_t *getPwd )
{
#if DEBUH_UART1
	//uint8_t name[20] = {0};
#endif
	STU stu;
	NODE *thisNode = NULL;
	uint8_t n = 0;  //ƥ�䵽����ѧ����¼

	
	//getUserName( userName );

	for(thisNode=g_stuHeader.link; thisNode!=NULL; thisNode=thisNode->next){
		stu = thisNode->data;
		if(strstr( (const char *)stu.username, (const char *)uName )){
			n++;				
			memcpy( (char *)getPwd,(const char *)stu.password,USER_PASSWORD_SIZE );
#if DEBUH_UART1
			myprintf("User:%s pwdFile:%s\r\n",uName,getPwd );		  //
#endif	
		}
	}

	if(n>0){
#if DEBUH_UART1
		myprintf("\nTotal :%d ...", n);
#endif	
		return getPwd;
	}else{
#if DEBUH_UART1
		myprintf("Err User...");
#endif		
		return 0;
	}
}

//�����ļ�
void updateFile( void )
{
	uint8_t fsize = 0;
	uint8_t i = 0;
	NODE *thisNode;
	
	fsize = g_stuHeader.num*USER_DATA_SIZE;
	SPI_Flash_Write_Page( &fsize,SPIFLASH_USER_NUMBER_ADRR,USER_FILE_SIZE );
	
	for(thisNode=g_stuHeader.link; thisNode!=NULL; thisNode=thisNode->next){
		SPI_Flash_Write_Page( (uint8_t *)(&thisNode->data),(((i++)*USER_DATA_SIZE)+SPIFLASH_USER_BASE_ADDR),USER_DATA_SIZE );		
		//SPI_Flash_Write_Page( (uint8_t *)(&thisNode->data),SPIFLASH_USER_BASE_ADDR,USER_DATA_SIZE );	
	}	
}

//��ȡ�ļ���С�����ֽڼƣ�
uint8_t getFileSize( void ) //FILE *fp)
{
	uint8_t fsize = 0;

	SPI_Flash_Read( &fsize,SPIFLASH_USER_NUMBER_ADRR,USER_FILE_SIZE );

	return fsize;
}

uint8_t vStartingUp( void )
{	

//	uTjc4832tSetWakup( TJC_TEST_PAGE );    
//	uTjc4832tSetSleep( TJC_SLEEP_OFF );		
//	OSTimeDlyHMSM(0, 0, 0, 120);	//
//	//OSMutexPost( gp_ResetLogInsem );            /*��ʱ���� �ͷ��ź��� �ٴε�¼ */
//	uBuzzer( BUZZER_OFF );   /*�ر�Buzzer	*/
//	OSTimeDlyHMSM(0, 0, 0, 120);	//
//	uTestInformation();

	return 0;
}
#endif


