#include "Func_Motor.h"

void MotorForward( void )
{
//	BSP_WritePin(MOTOR_SLEEP_PORT,MOTOR_SLEEP_PIN,MOTOR_SLEEP_TRUE);    /* 高电平使能  低电平休眠 */	

//	PWM_Config(_gp_PWM1, MOTOR_PULSE_TEST, MOTOR_FREQUENCY);    /* 配置PWM方波 */	
//	BSP_WritePin(MOTOR_DIR_PORT,MOTOR_DIR_PIN,MOTOR_DIR_TRUE);	  /* 方向控制 前进方向*/		

//	PWM_Enable(_gp_PWM1);	           /*使能PWM方波 电机走*/
}

void MotorBackward( void )
{
//	BSP_WritePin(MOTOR_SLEEP_PORT,MOTOR_SLEEP_PIN,MOTOR_SLEEP_TRUE);    /* 高电平使能  低电平休眠 */	

//	PWM_Config(_gp_PWM1, MOTOR_PULSE_TEST, MOTOR_FREQUENCY);    /* 配置PWM方波 */	
//	BSP_WritePin(MOTOR_DIR_PORT,MOTOR_DIR_PIN,MOTOR_DIR_FALSE);	  /* 方向控制 回退方向*/		

//	PWM_Enable(_gp_PWM1);	           /*使能PWM方波 电机走*/
}

/* 电机按照步数复位 */
uint8_t ResetMotor( void )
{	
//	BSP_WritePin(MOTOR_SLEEP_PORT,MOTOR_SLEEP_PIN,MOTOR_SLEEP_TRUE);         /* 高电平使能  低电平休眠 */	
//	BSP_WritePin(MOTOR_DIR_PORT,MOTOR_DIR_PIN,MOTOR_DIR_FALSE);	             /* 方向控制 回退方向*/
//	
//	PWM_Config(_gp_PWM1, MOTOR_PULSE*MOTOR_STEP_NUMBER, MOTOR_FREQUENCY);    /* 配置PWM方波 */	

//	PWM_Enable(_gp_PWM1);	                                                 /*使能PWM方波 电机走*/
		
	return 1;
}

/* 电机按等待信号量时间来复位 暂时不使用 */
void vResetMotorStauts( void )
{
	//uint8_t err = OS_ERR_NONE;	
	
	if( BSP_ReadPin(MOTOR_RESET_PORT,MOTOR_RESET_PIN) ){	
//		BSP_WritePin(MOTOR_SLEEP_PORT,MOTOR_SLEEP_PIN,MOTOR_SLEEP_TRUE);    /* 高电平使能  低电平休眠 */	
//		PWM_Config(_gp_PWM1, MOTOR_MAX_STEP, MOTOR_FREQUENCY);    /* 配置PWM方波 */	
//		BSP_WritePin(MOTOR_DIR_PORT,MOTOR_DIR_PIN,MOTOR_DIR_FALSE);	  /* 方向控制 回退方向*/
//		
//		PWM_Enable(_gp_PWM1);	           /*使能PWM方波 电机走*/
//		
//		//OSMutexPend(gp_MotorReset, MOTOR_RESET_TIME, &err);	/* 等待电机复位信号量 */
//		
//		PWM_Disable( _gp_PWM1 );	/*停止当前运动*/;
	}else{
		
	}
}

/* 无提示传感器复位 */
uint8_t uResetMotorInteriorStauts( uint8_t uPrompt )
{
//	OS_ERR err;
//	int32_t  iTemp = 6500;         /* 大约6s */

//	if( BSP_ReadPin(MOTOR_RESET_PORT,MOTOR_RESET_PIN ) ){
//		if( UI_Y_PROMPT==uPrompt ){
//			uTjc4832tSetLableValue( TJC_INSTRUMENT_PAGE,INSTRUMENT_DIS_CON_ID,(uint8_t *)"Motor ..." );
//		}
//		
//		BSP_WritePin(MOTOR_SLEEP_PORT,MOTOR_SLEEP_PIN,MOTOR_SLEEP_TRUE);    /* 高电平使能  低电平休眠 */	
//		PWM_Config(_gp_PWM1, MOTOR_MAX_STEP, MOTOR_FREQUENCY);    /* 配置PWM方波 */	
//		BSP_WritePin(MOTOR_DIR_PORT,MOTOR_DIR_PIN,MOTOR_DIR_FALSE);	  /* 方向控制 回退方向*/
//		
//		PWM_Enable(_gp_PWM1);	           /*使能PWM方波 电机走*/
//		
//		do
//		{
//			if( !BSP_ReadPin(MOTOR_RESET_PORT,MOTOR_RESET_PIN) )
//			{	
//				OSTimeDlyHMSM(0, 0, 0, MOTOR_TIME_SLICE,OS_OPT_TIME_HMSM_STRICT,&err);	
//				if( !BSP_ReadPin(MOTOR_RESET_PORT,MOTOR_RESET_PIN) )
//				{
//					PWM_Disable( _gp_PWM1 );	/*停止当前运动*/;
//					/* 此时再走10步防止临界问题 */
//					PWM_Config( _gp_PWM1,MOTOR_U_SECURITY_STEP,MOTOR_FREQUENCY );    /* 配置PWM方波 300起 0.13mm */			
//					PWM_Enable( _gp_PWM1 );	          	                     /*使能PWM方波 电机走 */					
//					if( UI_Y_PROMPT==uPrompt ){
//						uTjc4832tSetLableValue( TJC_INSTRUMENT_PAGE,INSTRUMENT_DIS_CON_ID,(uint8_t *)"Motor Ok" );
//					}
//					
//					return EXE_SUCCEED;
//				}
//			}
//			OSTimeDlyHMSM(0, 0, 0, 5,OS_OPT_TIME_HMSM_STRICT,&err);
//			iTemp--;
//		}while( iTemp>0 );		
//		PWM_Disable( _gp_PWM1 );	/*停止当前运动*/;
//		
//		if( UI_Y_PROMPT==uPrompt ){
//			uTjc4832tSetLableValue( TJC_INSTRUMENT_PAGE,INSTRUMENT_DIS_CON_ID,(uint8_t *)"Motor Error" );
//		}
//		return EXE_FAILED;
//	}else{
//		if( UI_Y_PROMPT==uPrompt ){
//			uTjc4832tSetLableValue( TJC_INSTRUMENT_PAGE,INSTRUMENT_DIS_CON_ID,(uint8_t *)"Motor Ok" );
//		}
//		return EXE_STAUTS;
//	}

	return EXE_STAUTS;
}

void MotorLock( uint8_t lock )
{
	if( MOTOR_UNLOCK==lock )
	{
		BSP_WritePin(MOTOR_EN_PORT,MOTOR_EN_PIN,MOTOR_EN_TRUE);              /* 高电平失能  低电平使能 */
		BSP_WritePin(MOTOR_SLEEP_PORT,MOTOR_SLEEP_PIN,MOTOR_SLEEP_FALSE);    /* 高电平使能  低电平休眠 */		
	}else
	{
		BSP_WritePin(MOTOR_SLEEP_PORT,MOTOR_SLEEP_PIN,MOTOR_SLEEP_TRUE);     /* 高电平使能  低电平休眠 */
		BSP_WritePin(MOTOR_EN_PORT,MOTOR_EN_PIN,MOTOR_EN_FALSE);             /* 高电平失能  低电平使能 */		
	}
}

bool bMotorResetStatus( void )
{
//	bool bTemp;
//	OS_ERR err;
//	
//	OSMutexPend( (OS_MUTEX *)&g_Referencesem,0,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	        /* 等待信号量 */
//	bTemp = BSP_ReadPin(MOTOR_RESET_PORT,MOTOR_RESET_PIN);
//	OSMutexPost( (OS_MUTEX *)&g_Referencesem,OS_OPT_POST_NO_SCHED,( OS_ERR *)&err );                        /* 释放信号量 */  
	
	return 0;
}
