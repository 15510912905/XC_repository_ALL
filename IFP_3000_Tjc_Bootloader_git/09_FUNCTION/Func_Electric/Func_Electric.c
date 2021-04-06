#include "Func_Electric.h"

int16_t iElectricQuantityDis( uint8_t uDisplay )
{
	static uint8_t uCount = 0;
	static uint8_t uRec1Time = 0;
	static uint8_t uRec2Time = 0;
	static uint8_t uRec3Time = 0;	
	static int16_t iRecTemp = 0;
	static int16_t iRec1Temp = 0;
	static int16_t iRec2Temp = 0;
	
	//uint8_t uArrStr[6] = {0};
	
	if( 0==uCount%2 ){
		iRec1Temp = (uint16_t)iRealElectricValue(ELECTRIC_AVE_TIME);
	}else{	
		iRec2Temp = (uint16_t)iRealElectricValue(ELECTRIC_AVE_TIME);
	}
	uCount++;
	
	/* �������� */
	if( ((iRec1Temp-iRec2Temp>=VOLTAGE_AD_TH1_VALUES)&&(iRec1Temp-iRec2Temp<=VOLTAGE_AD_TH2_VALUES))||	\
		((iRec2Temp-iRec1Temp>=VOLTAGE_AD_TH1_VALUES)&&(iRec2Temp-iRec1Temp<=VOLTAGE_AD_TH2_VALUES)) ){	
//	if( ((uRec1Temp-uRec2Temp>=0)&&(uRec1Temp-uRec2Temp<=3)) ){                /* �ݼ� */
			
		iRecTemp = (iRec1Temp+iRec2Temp)/2;		                               /* ��ƽ�� */
			
		if( uDisplay ){
			if( (iRecTemp>=VOLTAGE_AD_1_VALUES)&&(iRecTemp<=VOLTAGE_AD_2_VALUES) ){  /* (uRecTemp>=0)&& */
				if( BSP_ReadPin(CHARGE_STATUS_PORT,CHARGE_STATUS_PIN) ){           /* ʹ�õ��ʱ */ /* ���ʱ�����е͵�����ʾ */
					if( iRecTemp<VOLTAGE_THRESHOLD_PERCENTAGE ){                   /* ���������� */			
						uRec1Time++;
						if( uRec1Time==VOLTAGE_TIMES ){                            /* ֻ��ִ��һ�� */
							g_ShutdownError = VOLTAGE_TIMES;
							vPromptShutDown( POWER_FORCE,POWER_FORCE_15_SECOND );  /* ����ʾ�ػ� ����ȡ�� */
						}
					
						//return EXE_SPECIAL_FAILED;
					}else if( iRecTemp<VOLTAGE_THRESHOLD_PROMPT ){      
						uRec2Time++;
						if( uRec2Time>VOLTAGE_PROMPT_TIMES ){                        /* �������������һ�� */
							uRec2Time = 0;                                         
							//vPromptElectricQuantity();                             /* ��ʾ�������� ��ȡ�� */
						}		
						
						//return PROMPT_VOLTAGE;
					}else{
						//sprintf( (char *)uArrStr,"%d%c",uRecTemp,'%' );
						//uTjc4832tWriterStr( 265,1,60,25,2,TJC_RED,0xffff,2,1,1,(uint8_t *)uArrStr );
					}
				}
			}else{
				if( iRecTemp>VOLTAGE_AD_2_VALUES ){
					iRecTemp = VOLTAGE_AD_2_VALUES;
				}else{
					uRec3Time++;
					if( uRec3Time>VOLTAGE_PROMPT1_TIMES ){
						uRec3Time = 0;
						//vPromptElectricQuantity();                          /* ��ʾ�������� */
						vPromptShutDown( POWER_FORCE,POWER_FORCE_15_SECOND ); /* ����ʾ�ػ� ����ȡ�� */
					}					
					return EXE_SPECIAL_FAILED;
				}
			}
		}
	}else{
		return EXE_SPECIAL_FAILED;
	}
		
#if DEBUH_UART1	
	#if PRIVATE_REALTIME_UART1	
		myprintf( "uRecADCTemp: %2d \r\n",iRecTemp ); 
	#endif
#endif	
	
	return iRecTemp;//return EXE_SUCCEED;
}

/* �ɼ�����ADֵ uAverage���ܳ���10 */
int16_t iRealElectricValue( uint8_t uAverage )
{
	int32_t iRecTemp = 0;
	uint16_t uRecElectric[10] = {0};
	uint8_t i = 0;
#if PRIVATE_ELECTRIC_TJC
	char strff[32] = {0};  
#endif
	
	for( i=0;i<uAverage;i++ ){
		uRecElectric[i] = BSP_ReadAdc( VSENSE_PORT,VSENSE_PIN );       /* ����AD�ɼ� */
	}
#if STORT_STL
		qsort(uRecElectric, (sizeof(uRecElectric)/sizeof(uint16_t)), sizeof(uint16_t), cmpfuncint16max);  /*������*/
#else
		InsertionSortUint16_t( (uint16_t *)uRecElectric,(sizeof(uRecElectric)/sizeof(uint16_t)),SORT_MAX );
#endif
	for( i=1;i<uAverage-1;i++ ){                                      /* ȥ�����ֵ����Сֵ */
		iRecTemp += uRecElectric[i];
	}
	iRecTemp = iRecTemp/(uAverage-2);
	
#if DEBUH_UART1	
	#if PRIVATE_ELECTRIC_UART1
		myprintf( "ElectricValue:%d \r\n",iRecTemp );
	#endif	
#endif	
		
#if PRIVATE_ELECTRIC_TJC
	uConfirmPage( TJC_WARN_PAGE ); //uTjc4832tSetPage( TJC_WARN_PAGE );        /*����Ϊǿ�ƾ���ҳ*/
	sprintf( strff,"%d",iRecTemp );
	uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)strff );
#endif
	
	if( (iRecTemp>=VOLTAGE_AD_1_VALUES)&&(iRecTemp<=VOLTAGE_AD_2_VALUES)  ){
		return iRecTemp; 
	}else if( (iRecTemp>VOLTAGE_AD_2_VALUES) ){
		return VOLTAGE_AD_2_VALUES;
	}else{
		return VOLTAGE_AD_1_VALUES;
	}
}

uint8_t iElectricInit( void )
{
//	OS_ERR err;
	int16_t i = 0;
	int16_t iRecElecValue = 0;
	
	while( (EXE_SPECIAL_FAILED==iElectricAve(&iRecElecValue))&&(i<ELECTRIC_TIME) ){	
		i++;
//		OSTimeDlyHMSM(0, 0, 0, 100,OS_OPT_TIME_HMSM_STRICT,&err);	                            /* ��ʱ100ms   */		
	}
	
	if(i>ELECTRIC_TIME){
		uTjc4832tSetPage( TJC_WARN_PAGE );                                                                                                    /*����Ϊǿ�ƾ���ҳ*/
		uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"power failure" );	                                                  //"25Q64 Check Failed!"//"Please Check!      "
		return EXE_FAILED;
	}else{
		if( iRecElecValue<VOLTAGE_THRESHOLD_PERCENTAGE ){
			uTjc4832tSetPage( TJC_WARN_PAGE ); 
			uTjc4832tSetLableValue( TJC_WARN_PAGE,WARN_ID_NUM,(uint8_t *)"Low power" );	             //
			/* ��ʱ */
			vShutDown();                          /* �ػ� */
			return EXE_FAILED;
		}
	}	
	
	return EXE_SUCCEED;
}

int16_t iElectricAve( int16_t* pElecValue )
{
	int16_t i = 0;
	int16_t iRecElec[2] = {0};
	
	for( i=0;i<(sizeof(iRecElec)/sizeof(int16_t));i++ ){
		iRecElec[i] = (uint16_t)iRealElectricValue(ELECTRIC_AVE_TIME);
	}
	
	if( (iRecElec[0]-iRecElec[1]<30)||(iRecElec[1]-iRecElec[0]<30) ){
		*pElecValue = (iRecElec[0]+iRecElec[1])/2;
		return (iRecElec[0]+iRecElec[1])/2;
	}else{
		return EXE_SPECIAL_FAILED;
	}
}

uint8_t uElecRefresh( uint8_t uDisplay )
{
	static int16_t l_uRecDraw = ELECTRIC_4_VALUE;   
	static int16_t l_iRecTemp = VOLTAGE_AD_4_VALUES;   /* Ĭ�������� */
	
	uTjc4832tFill( 288,1,318,19,TJC_WHITE );
	
	l_iRecTemp = iElectricQuantityDis( uDisplay );           /* ������ʾ ELECTRIC_QUANTITY_OFF */					
	
	if( (VOLTAGE_AD_1_VALUES<=l_iRecTemp)&&(l_iRecTemp<=VOLTAGE_AD_2_VALUES) ){
		g_uElectricValue = l_iRecTemp;                                  /* ȫ�ֲ鿴���� */
		l_uRecDraw = l_iRecTemp;  //(uint8_t )(l_iRecTemp*(float)((float)26/(float)100));
		if( BSP_ReadPin(CHARGE_STATUS_PORT,CHARGE_STATUS_PIN) ){                        /* ʹ�õ��ʱ */
			if( (l_uRecDraw<=VOLTAGE_AD_3_VALUES) ){
				l_uRecDraw = ELECTRIC_1_VALUE;
			}else if( (VOLTAGE_AD_3_VALUES<l_uRecDraw)&&(l_uRecDraw<=VOLTAGE_AD_4_VALUES) ){
				l_uRecDraw = ELECTRIC_2_VALUE;
			}else if( (VOLTAGE_AD_4_VALUES<l_uRecDraw) ){
				l_uRecDraw = ELECTRIC_3_VALUE;
			}else{
				l_uRecDraw = ELECTRIC_4_VALUE;
			}
		}else{                                                                          /* ���ʱ */
			if( (l_uRecDraw<=VOLTAGE_AD_6_VALUES) ){
				l_uRecDraw = ELECTRIC_1_VALUE;
			}else if( (VOLTAGE_AD_6_VALUES<l_uRecDraw)&&(l_uRecDraw<=VOLTAGE_AD_7_VALUES) ){
				l_uRecDraw = ELECTRIC_2_VALUE;
			}else if( (VOLTAGE_AD_7_VALUES<l_uRecDraw) ){
				l_uRecDraw = ELECTRIC_3_VALUE;
			}else{
				l_uRecDraw = ELECTRIC_4_VALUE;
			}
		}
	}else{
		l_uRecDraw = ELECTRIC_4_VALUE;
	}
	
	if( ELECTRIC_4_VALUE!=l_uRecDraw ){                                                         /* ����ˢ�� */
		uTjc4832tDraw( 288,1,318,19,TJC_1_GREEN );                                              /* ������ʾ���ο� */
		if( ELECTRIC_1_VALUE==l_uRecDraw ){
			uTjc4832tFill( 290,3,l_uRecDraw,15,TJC_YELLOW );
		}else{
			uTjc4832tFill( 290,3,l_uRecDraw,15,TJC_1_GREEN );
		}
	}
	
	return EXE_SUCCEED;
}



