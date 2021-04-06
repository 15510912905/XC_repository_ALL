#include "Func_BarCode.h"

/* 算平均线之间的距离 */
uint8_t* uWaveCrestTrough( const uint16_t* upArrData,uint8_t* upArrBar,int len )
{
	uint16_t uArrCrest[20] = {0};                          /* 存储波峰值 */
	uint16_t uArrTrough[20] = {0};                         /* 存储波谷值 */
	uint16_t uArrAndTrough[44] = {0};                      /* 存储波峰和波峰值合并 */
	
	uint16_t uBarArrExtent[44] = {0};                      /* 存储离每段中位值最接近的点 */
	uint16_t uBarArrMax[20] = {0};                         /* 存储绝对最大值 斜率为正找最大值 */
	uint16_t uBarArrMin[20] = {0};                         /* 存储绝对最小值 斜率为负找最小值 */
	uint16_t uBarArrExtentMedian[44] = {0};                /* 存储波峰中间值和波谷中间值合并 */
	uint16_t uBarArrExtentDifference[44] = {0};            /* 存储波峰中间值和波谷中间值的差值 */	
	uint8_t uBarBinValue[44] = {0};                        /* 存储条码0/1个数 */
	uint8_t uBarBinValueTemp[44] = {0};                    /* 存储转换条码的临时数据 */
	uint8_t uBarExtentValue[5] = {0};	                   /* 存储最终得到的条码 */
	
	uint8_t uCrstAndTroghNum = 0;                          /* 记录波峰和波谷总点数 */   
	uint8_t uRecError = 0;	                               /* 记录错误 */
	float fRecDitNum = 0.5;                                /* 初始值已知恒定为0.5 */
	
#if VARIOUS_MEDIAN_DIT		
	uint16_t uBarArrMinMaxMed[44] = {0};                   /* 存储绝对最小值和最大值合并 */
	uint16_t uBarArrMinMaxMedValue[44] = {0};              /* 存储计算出来的中间值 */
	uint16_t uBarArr1ExtentTemp[44] = {0};                 /* 存储临时中间值 斜率为正找最大值 */
	uint16_t uBarArr2ExtentTemp[44] = {0};		           /* 存储临时中间值 斜率为负找最小值 */
#else
	uint16_t uBarArrExtentTemp[44] = {0};
	uint16_t uMedianValue = 0;
#endif	
	
	/* 相对波峰和波谷点 */
	uSeekCrestTroughAbout( upArrData,len,uArrCrest,(sizeof(uArrCrest)/sizeof(uint16_t)),uArrTrough,(sizeof(uArrTrough)/sizeof(uint16_t)) );
	
	/* 找到波峰和波谷中绝对的最小值和最大值 */
	uRecError = uSeekCrestTroughAbsolute( upArrData,len,uArrCrest,(sizeof(uArrCrest)/sizeof(uint16_t)),uArrTrough,(sizeof(uArrTrough)/sizeof(uint16_t)),
		                                  uBarArrMin,(sizeof(uBarArrMin)/sizeof(uint16_t)),uBarArrMax,(sizeof(uBarArrMax)/sizeof(uint16_t)) );
	if( EXE_SUCCEED!=uRecError ){
		return NULL;
	}	
		
#if VARIOUS_MEDIAN_DIT
	/* 求每个波峰波谷绝对最小值和最大值的中位线 或者 求绝对最小值和最大值的中位线 */
	uSeekCrestTroughMedianA( upArrData,len,uArrCrest,(sizeof(uArrCrest)/sizeof(uint16_t)),uArrTrough,(sizeof(uArrTrough)/sizeof(uint16_t)),
						    uBarArrMin,(sizeof(uBarArrMin)/sizeof(uint16_t)),uBarArrMax,(sizeof(uBarArrMax)/sizeof(uint16_t)),
						    uBarArrMinMaxMed,(sizeof(uBarArrMinMaxMed)/sizeof(uint16_t)),uBarArrMinMaxMedValue,(sizeof(uBarArrMinMaxMedValue)/sizeof(uint16_t)) );
#else
	/* 求绝对最小值和最大值的中位线 */
	uMedianValue = uSeekCrestTroughMedianB( uBarArrMin,(sizeof(uBarArrMin)/sizeof(uint16_t)),uBarArrMax,(sizeof(uBarArrMax)/sizeof(uint16_t)) );						   
#endif
	
	/* 将波峰波谷按顺序合并 */ 
	uArrCrestAndTrough( uArrCrest,(sizeof(uArrCrest)/sizeof(uint16_t)),uArrTrough,(sizeof(uArrTrough)/sizeof(uint16_t)),uArrAndTrough,(sizeof(uArrAndTrough)/sizeof(uint16_t)) );

	/* 计算波峰中间值加波谷中间值一共有多少个 */	
	uCrstAndTroghNum = iGetHalfIntergeNumber(uArrAndTrough);
#if DEBUH_UART1	
#if PRIVATE_UART1	
	#if PRIVATE_SPCIAL_BAR_UART1
	myprintf( "uCrstAndTroghNum:%4d \r\n",uCrstAndTroghNum );     
	#endif
#endif
#endif

#if VARIOUS_MEDIAN_DIT						
	/* 找到所有与中位值最接近的点 */	
	uSeekMedianValueAboutA( upArrData,len,uBarArrMinMaxMedValue,(sizeof(uBarArrMinMaxMedValue)/sizeof(uint16_t)),uArrAndTrough,(sizeof(uArrAndTrough)/sizeof(uint16_t)),
                            uBarArr1ExtentTemp,(sizeof(uBarArr1ExtentTemp)/sizeof(uint16_t)),uBarArr2ExtentTemp,(sizeof(uBarArr2ExtentTemp)/sizeof(uint16_t)),
						    uBarArrExtent,(sizeof(uBarArrExtent)/sizeof(uint16_t)),uCrstAndTroghNum );
/* 将波峰中间值和波谷中间值合并 计算所有中位值与曲线交点的中间值 */
	uArrCrestMiddleAndTroughMiddleA( uBarArrExtent,sizeof(uBarArrExtent)/sizeof(uint16_t),uBarArrExtentMedian,sizeof(uBarArrExtentMedian)/sizeof(uint16_t) );   
#else
	uSeekMedianValueAboutB( upArrData,len,uArrAndTrough,(sizeof(uArrAndTrough)/sizeof(uint16_t)),uBarArrExtentTemp,(sizeof(uBarArrExtentTemp)/sizeof(uint16_t)),
                            uBarArrExtent,(sizeof(uBarArrExtent)/sizeof(uint16_t)),uCrstAndTroghNum,uMedianValue );
						 
	uArrCrestMiddleAndTroughMiddleB( uBarArrExtent,sizeof(uBarArrExtent)/sizeof(uint16_t),uBarArrExtentMedian,sizeof(uBarArrExtentMedian)/sizeof(uint16_t) );
#endif
	
	/* 每个中位值的差值点 */
	uCalArrMedianDifference( uBarArrExtentMedian,sizeof(uBarArrExtentMedian)/sizeof(uint16_t),uBarArrExtentDifference,sizeof(uBarArrExtentDifference)/sizeof(uint16_t) );

	
	/* 计算点数值 */
	uRecError = uCalArrDitNum( uBarArrExtentDifference,sizeof(uBarArrExtentDifference)/sizeof(uint16_t),fRecDitNum,uBarBinValue,sizeof(uBarBinValue)/sizeof(uint8_t) );
	if( EXE_SUCCEED!=uRecError ){
		return NULL;
	}	
	
	/* 将得到的条码值转换为0 1 数值并得出条码ASCII值 */
	uGetArrBarAssiiValue( uBarBinValue,sizeof(uBarBinValue)/sizeof(uint8_t),uBarBinValueTemp,sizeof(uBarBinValueTemp)/sizeof(uint8_t),
						  uBarExtentValue,sizeof(uBarExtentValue)/sizeof(uint8_t),upArrBar );
	
	return upArrBar;
}

/* 找到第一个波谷值 */
uint8_t uGetFirstTroughValue( const uint16_t* upArrData,int len,int16_t* uTroughValue,uint16_t* puTroughMax )
{
	int32_t i = 0;
	
	uint16_t uArrCrest[20] = {0};                          /* 存储波峰值 */
	uint16_t uArrTrough[20] = {0};                         /* 存储波谷值 */
	uint16_t uBarArrMax[20] = {0};                         /* 存储绝对最大值 斜率为正找最大值 */
	uint16_t uBarArrMin[20] = {0};                         /* 存储绝对最小值 斜率为负找最小值 */	
	
//	uint16_t uBarArrMinMaxMed[44] = {0};                   /* 存储绝对最小值和最大值合并 */
//	uint16_t uBarArrMinMaxMedValue[44] = {0};              /* 存储计算出来的中间值 */

	uint8_t uRecError = 0;	                               /* 记录错误 */
	
	/* 相对波峰和波谷点 */
	uSeekCrestTroughAbout( upArrData,len,uArrCrest,(sizeof(uArrCrest)/sizeof(uint16_t)),uArrTrough,(sizeof(uArrTrough)/sizeof(uint16_t)) );
	
	/* 找到波峰和波谷中绝对的最小值和最大值 */
	uRecError = uSeekCrestTroughAbsolute( upArrData,len,uArrCrest,(sizeof(uArrCrest)/sizeof(uint16_t)),uArrTrough,(sizeof(uArrTrough)/sizeof(uint16_t)),
		                                  uBarArrMin,(sizeof(uBarArrMin)/sizeof(uint16_t)),uBarArrMax,(sizeof(uBarArrMax)/sizeof(uint16_t)) );
	if( EXE_SUCCEED!=uRecError ){
		return EXE_FAILED;
	}
	
	*puTroughMax = uBarArrMin[0];
	
	if( 0!=uBarArrMin[0] ){
		for( i=len-1;i>=0;i-- ){
			if( *(upArrData+i)==uBarArrMin[0] ){
				*uTroughValue = i+1;
				return EXE_SUCCEED;
			}
		}
	}else{
		return EXE_FAILED;
	}
	
	return EXE_SUCCEED;
}

//初始化ADC
//这里我们仅以规则通道为例
//我们默认将开启通道0~3																	   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC |RCC_APB2Periph_ADC1	, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	//PA1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOC, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   
  
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}

//获得ADC值
//ch:通道值 0~3
uint16_t Get_Adc(uint8_t ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间  
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_7Cycles5 );//ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}

uint16_t Get_Adc_Average(uint8_t ch,uint8_t times)
{
	uint16_t temp_val=0;	
	uint8_t t=0;
	
	for(t=0;t<times;t++){
		temp_val+=Get_Adc(ch);		//delay_ms(5);
	}
	
	return temp_val/times;
//	return temp_val;
} 

/* 
平滑数组
下标0-4数组里5个数求平均装在下标为2的数组里  
下标(n-5)-(n-1)数组里5个数求平均装在下标为(n-3)的数组里
*/
void vbar_line_smoth_slid( uint16_t* pOneBuffer,uint16_t len )
{
	uint16_t *pArr, *pArrTem, temp;
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

uint8_t* uBarTransition( ID_Info* pIDdata,uint8_t* uArrTemp )
{
	uint8_t i = 0;
	uint8_t uSpArrTemp[5] = { 0xff,0xff,0xff,0xff,0xff };
	
	/* 判断ID数据是否为空 */
	if( 0==strncmp( (const char*)uSpArrTemp,(const char*)pIDdata->barcode,sizeof(pIDdata->barcode) ) ){
		return NULL;
	}
	
	for( i=0;i<5;i++ ){
		switch( pIDdata->barcode[i] ){			
			case 0x30:
				*(uArrTemp+i) = 0;
				break;
			case 0x31:
				*(uArrTemp+i) = 1;
				break;
			case 0x32:
				*(uArrTemp+i) = 2;
				break;
			case 0x33:
				*(uArrTemp+i) = 3;
				break;
			case 0x34:
				*(uArrTemp+i) = 4;
				break;
			case 0x35:
				*(uArrTemp+i) = 5;
				break;
			case 0x36:
				*(uArrTemp+i) = 6;
				break;
			case 0x37:
				*(uArrTemp+i) = 7;
				break;
			case 0x38:
				*(uArrTemp+i) = 8;
				break;
			case 0x39:
				*(uArrTemp+i) = 9;
				break;
			case 0x41:
				*(uArrTemp+i) = 10;
				break;
			case 0x42:
				*(uArrTemp+i) = 11;
				break;
			case 0x43:
				*(uArrTemp+i) = 12;
				break;
			case 0x44:
				*(uArrTemp+i) = 13;
				break;
			case 0x45:
				*(uArrTemp+i) = 14;
				break;
			case 0x46:
				*(uArrTemp+i) = 15;
				break;
			case 0x61:
				*(uArrTemp+i) = 10;
				break;
			case 0x62:
				*(uArrTemp+i) = 11;
				break;
			case 0x63:
				*(uArrTemp+i) = 12;
				break;
			case 0x64:
				*(uArrTemp+i) = 13;
				break;
			case 0x65:
				*(uArrTemp+i) = 14;
				break;
			case 0x66:
				*(uArrTemp+i) = 15;
				break;
			default:
				*(uArrTemp+i) = 0;
				break;
		}		
	}
	
	return uArrTemp;
}

uint8_t* uBarNumTransitionAscii( const uint8_t *uOriginal,uint8_t* uArrTemp )
{
	uint8_t i = 0;
	
	for( i=0;i<5;i++ ){
		switch( uOriginal[i] ){			
			case 0:
				*(uArrTemp+i) = 0x30;
				break;
			case 1:
				*(uArrTemp+i) = 0x31;
				break;
			case 2:
				*(uArrTemp+i) = 0x32;
				break;
			case 3:
				*(uArrTemp+i) = 0x33;
				break;
			case 4:
				*(uArrTemp+i) = 0x34;
				break;
			case 5:
				*(uArrTemp+i) = 0x35;
				break;
			case 6:
				*(uArrTemp+i) = 0x36;
				break;
			case 7:
				*(uArrTemp+i) = 0x37;
				break;
			case 8:
				*(uArrTemp+i) = 0x38;
				break;
			case 9:
				*(uArrTemp+i) = 0x39;
				break;
			case 10:
				*(uArrTemp+i) = 0x41;
				break;
			case 11:
				*(uArrTemp+i) = 0x42;
				break;
			case 12:
				*(uArrTemp+i) = 0x43;
				break;
			case 13:
				*(uArrTemp+i) = 0x44;
				break;
			case 14:
				*(uArrTemp+i) = 0x45;
				break;
			case 15:
				*(uArrTemp+i) = 0x46;
				break;
			
			default:
				*(uArrTemp+i) = 0;
				break;
		}
		
	}
	
	return uArrTemp;
}

//uint8_t uCalculateBarBreadthBit()
//{
//	return EXE_SUCCEED;
//}

/* 相对波峰和波谷点 */
uint8_t uSeekCrestTroughAbout( const uint16_t* upArrData,int16_t len,uint16_t* uArrCrest,uint16_t uArrCrestLen,uint16_t* uArrTrough,uint16_t uArrTroughLen )
{
	uint32_t i = 0;
	uint8_t uCrestTroughStatus = 0;
	
	uint8_t ua = 0;
	uint8_t ub = 0;
	uint8_t uc = 0;
	uint8_t ue = 0;
	uint8_t ug = 0;
	uint8_t uh = 0;
	
	/* 相对波峰和波谷点 */
	for( i=(len-1);i>(BAR_AVERAGE_NUM+1);i-- ){
		if( 0==uCrestTroughStatus ){  /* 找下降点 */      
			if( *(upArrData+i)-*(upArrData+(i-1))>BAR_START_THRESHOLD ){ /* 此处阈值需要大量测试 */
				while( ua<BAR_AVERAGE_NUM ){
					i--;
					if( *(upArrData+i)-*(upArrData+(i-1))>BAR_START_THRESHOLD ){
						ub++;
					}
					ua++;
				}				
#if DEBUH_UART1	
	#if PRIVATE_UART1
		#if PRIVATE_SPCIAL_BAR_UART1
				myprintf( "WaveCrest ub:%4d i:%4d \r\n",ub,i );
		#endif
	#endif
#endif
				if( (ub>=BAR_AVE_NUM) ){	
					if( uc<uArrCrestLen ){
						uArrCrest[uc++] = i+BAR_AVERAGE_NUM;
					}
					uCrestTroughStatus = 1;
				}
				ub = 0;
				ua = 0;
			}
		}else if( 1==uCrestTroughStatus ){    /* 找上升点 */ 
			if( *(upArrData+i)-*(upArrData+(i-1))<(-BAR_START_THRESHOLD) ){
				while( ue<BAR_AVERAGE_NUM ){
					i--;
					if( *(upArrData+i)-*(upArrData+(i-1))<(-BAR_START_THRESHOLD) ){
						ug++;
					}
					ue++;
				}
#if DEBUH_UART1	
	#if PRIVATE_UART1
		#if PRIVATE_SPCIAL_BAR_UART1
				myprintf( "WaveTrough ug:%4d i:%4d \r\n",ug,i );
		#endif
	#endif
#endif
				if( (ug>=BAR_AVE_NUM) ){
					if( uh<uArrTroughLen ){
						uArrTrough[uh++] = i+BAR_AVERAGE_NUM;
					}
					uCrestTroughStatus = 0;
				}
				ue = 0;
				ug = 0;
			}
		}			
	}
	
#if DEBUH_UART1	
#if PRIVATE_UART1
	#if PRIVATE_SPCIAL_BAR_UART1
	for( i=0;i<uArrCrestLen;i++ ){
		if(0!=uArrCrest[i]){
			myprintf( "uArrCrest:%4d \r\n",uArrCrest[i] );
		}
		if(0!=uArrTrough[i]){
			myprintf( "uArrTrough:%4d \r\n",uArrTrough[i] );
		}
	}
	#endif
	#endif
#endif

	return EXE_SUCCEED;
}

/* 找到波峰和波谷中绝对的最小值和最大值 */
uint8_t uSeekCrestTroughAbsolute( const uint16_t* upArrData,int16_t len,uint16_t* uArrCrest,uint16_t uArrCrestLen,uint16_t* uArrTrough,uint16_t uArrTroughLen,
	                              uint16_t* uBarArrMin,uint16_t uBarArrMinLen,uint16_t* uBarArrMax,uint16_t uBarArrMaxLen )
{
#if DEBUH_UART1	
	#if PRIVATE_UART1
	#if PRIVATE_SPCIAL_BAR_UART1
//	int k = 0;
	#endif
	#endif
#endif
	uint32_t i = 0;
	uint8_t uRecError = EXE_SUCCEED;
	uint16_t* puTempBarAdValue = NULL;
	
	puTempBarAdValue = (uint16_t *)calloc( BARVODE_LENGTH,sizeof(uint16_t) );
	if( NULL==puTempBarAdValue ){
		return NULL;
	}
	
	/* 找到波峰和波谷中绝对的最小值和最大值 */
	for( i=0;i<(uArrCrestLen);i++ ){
		if( (0!=uArrCrest[i])){		  /* &&(0!=uArrCrest[i+1]) */
			memcpy( (char *)puTempBarAdValue,(const char *)((uint16_t *)upArrData+uArrCrest[i+1]),(uArrCrest[i]-uArrCrest[i+1])*sizeof(uint16_t) );	
#if STORT_STL
			qsort( (uint16_t *)puTempBarAdValue,(uArrCrest[i]-uArrCrest[i+1]),sizeof(uint16_t),cmpfuncint16min );
#else
			InsertionSortUint16_t( (uint16_t *)puTempBarAdValue,(uArrCrest[i]-uArrCrest[i+1]),SORT_MIN );
			
	#if DEBUH_UART1	
		#if PRIVATE_UART1
			#if PRIVATE_SPCIAL_BAR_UART1
//			for( k=0;k<5;k++ ){
//				myprintf( "Min puTempBarAdValue:%d\r\n",puTempBarAdValue[i]);
//			}
			#endif
		#endif
	#endif
			
#endif
			if( 0!=puTempBarAdValue[0] ){
				uBarArrMin[i] = puTempBarAdValue[0];		
			}else{
				uRecError = EXE_FAILED;
			}				

#if DEBUH_UART1	
	#if PRIVATE_UART1
			#if PRIVATE_SPCIAL_BAR_UART1
			myprintf( "uBarArrMin:%4d %4d %4d %d \r\n",uArrCrest[i+1],uArrCrest[i],uBarArrMin[i],puTempBarAdValue[0] );  /* 下一个波峰 当前波峰 最小条码AD值 确认是否是第一个值 */
			#endif
		#endif
#endif
			memset( puTempBarAdValue,0,(BARVODE_LENGTH)*sizeof(uint16_t) );
		}
		if( (0!=uArrTrough[i])){		/* &&(0!=uArrTrough[i+1])  */
			memcpy( (char *)puTempBarAdValue,(const char *)((uint16_t *)upArrData+uArrTrough[i+1]),(uArrTrough[i]-uArrTrough[i+1])*sizeof(uint16_t) );		
#if STORT_STL
			qsort( (uint16_t *)puTempBarAdValue,(uArrTrough[i]-uArrTrough[i+1]),sizeof(uint16_t),cmpfuncint16max );
#else
			InsertionSortUint16_t( (uint16_t *)puTempBarAdValue,(uArrTrough[i]-uArrTrough[i+1]),SORT_MAX );
			
	#if DEBUH_UART1	
		#if PRIVATE_UART1
			#if PRIVATE_SPCIAL_BAR_UART1
//			for( k=0;k<5;k++ ){
//				myprintf( "Max puTempBarAdValue:%d\r\n",puTempBarAdValue[i]);
//			}
			#endif
		#endif
	#endif
			
#endif
			if( 0!=puTempBarAdValue[0] ){
				uBarArrMax[i] = puTempBarAdValue[0];
			}else{
				uRecError = EXE_FAILED;
			}
			
#if DEBUH_UART1	
	#if PRIVATE_UART1
			#if PRIVATE_SPCIAL_BAR_UART1
			myprintf( "uBarArrMax:%4d %4d %4d %d \r\n",uArrTrough[i+1],uArrTrough[i],uBarArrMax[i],puTempBarAdValue[0] );
			#endif
		#endif
#endif
			memset( puTempBarAdValue,0,(BARVODE_LENGTH)*sizeof(uint16_t) );
		}
	}
	
	if( NULL!=puTempBarAdValue ){
		free( puTempBarAdValue );
	}
	
	return uRecError;
}

/* 求每个波峰波谷绝对最小值和最大值的中位线 或者 求绝对最小值和最大值的中位线 */
uint8_t uSeekCrestTroughMedianA( const uint16_t* upArrData,int16_t len,uint16_t* uArrCrest,uint16_t uArrCrestLen,uint16_t* uArrTrough,uint16_t uArrTroughLen,
								uint16_t* uBarArrMin,uint16_t uBarArrMinLen,uint16_t* uBarArrMax,uint16_t uBarArrMaxLen,uint16_t* uBarArrMinMaxMed,uint16_t uBarArrMinMaxMedLen,
								uint16_t* uBarArrMinMaxMedValue,uint16_t uBarArrMinMaxMedValueLen )
{
	uint32_t i = 0;
			
	uint8_t uCountA = 0;
	uint8_t uk = 0;
			
	/* 求每个波峰波谷绝对最小值和最大值的中位线 */
	uBarArrMinMaxMed[uk++] = *(upArrData+uArrCrest[0]);            /* 起点 */
	for( i=0;i<(uBarArrMinLen);i++ ){		   /* 将最小值和最大值合并 */
		if(0!=uBarArrMin[i]){
			uBarArrMinMaxMed[uk++] = uBarArrMin[i];
		}
		if(0!=uBarArrMax[i]){
			uBarArrMinMaxMed[uk++] = uBarArrMax[i];
		}
	}	
#if DEBUH_UART1	
#if PRIVATE_UART1	
	#if PRIVATE_SPCIAL_BAR_UART1
	for( i=0;i<(sizeof(uBarArrMinMaxMed)/sizeof(uint16_t));i++ ){
		if( 0!=uBarArrMinMaxMed[i] ){
			myprintf( "uBarArrMinMaxMed %2d:%4d \r\n",i,uBarArrMinMaxMed[i] );        /*  */
		}
	}
	#endif
#endif
#endif
	
	for( i=0;i<(uBarArrMinMaxMedLen);i++ ){   /* 将计算出的中位值存储到数组 */
		if( (0!=uBarArrMinMaxMed[i])&&(0!=uBarArrMinMaxMed[i+1])&&(0!=uBarArrMinMaxMed[i+2]) ){
			uBarArrMinMaxMedValue[uCountA++] = (uBarArrMinMaxMed[i]+uBarArrMinMaxMed[i+1])/2;
			uBarArrMinMaxMedValue[uCountA++] = (uBarArrMinMaxMed[i+1]+uBarArrMinMaxMed[i+2])/2;
		}
	}		
#if DEBUH_UART1	
#if PRIVATE_UART1	
	#if PRIVATE_SPCIAL_BAR_UART1
	for( i=0;i<(sizeof(uBarArrMinMaxMedValue)/sizeof(uint16_t));i++ ){
		if( 0!=uBarArrMinMaxMedValue[i] ){
			myprintf( "uBarArrMinMaxMedValue %2d:%4d \r\n",i,uBarArrMinMaxMedValue[i] );        /* 找到中位值最接近的点 */
		}
	}
	#endif
#endif
#endif
	
	return EXE_SUCCEED;
}

uint8_t uSeekCrestTroughMedianB( uint16_t* uBarArrMin,uint16_t uBarArrMinLen,uint16_t* uBarArrMax,uint16_t uBarArrMaxLen )
{
	uint16_t uBarArrMaxTemp[20] = {0};
	uint16_t uBarArrMinTemp[20] = {0};
	uint16_t uMedianValue = 0;
	
		/* 求绝对最小值和最大值的中位线 */
	uBarArrMinLen = iGetHalfIntergeNumber(uBarArrMin);            /* 长度 */
	uBarArrMaxLen = iGetHalfIntergeNumber(uBarArrMax);            /* 长度 */
	memcpy( uBarArrMinTemp,uBarArrMin,uBarArrMinLen );
	memcpy( uBarArrMaxTemp,uBarArrMax,uBarArrMaxLen );
	
	uMedianValue = uCalculateMedianValue( uBarArrMinTemp,uBarArrMinLen,uBarArrMaxTemp,uBarArrMaxLen );    /* 中位值计算 */	
	
	return uMedianValue;
}

/* 将波峰波谷按顺序合并 */ 
uint8_t uArrCrestAndTrough( uint16_t* uArrCrest,uint16_t uArrCrestLen,uint16_t* uArrTrough,uint16_t uArrTroughLen,uint16_t* uArrAndTrough,uint16_t uArrAndTroughLen )
{
	uint32_t i = 0;
	uint16_t uj = 0;
	
	/* 将波峰波谷按顺序合并 */ 
	for( i=0;i<(uArrCrestLen);i++ ){
		if(0!=uArrCrest[i]){
			uArrAndTrough[uj++] = uArrCrest[i];
		}
		if(0!=uArrTrough[i]){
			uArrAndTrough[uj++] = uArrTrough[i];
		}
	}
	
	/* 打印波峰和波谷合并的数据 */
#if DEBUH_UART1	
#if PRIVATE_UART1	
	#if PRIVATE_SPCIAL_BAR_UART1
	for( i=0;i<(uArrAndTroughLen);i++ ){
		if( 0!=uArrAndTrough[i] ){
			myprintf( "uArrAndTrough %2d:%4d \r\n",i,uArrAndTrough[i] );       
		}
	}
	#endif
#endif
#endif
	
	return EXE_SUCCEED;
}


/* 找到与中位值最接近的点 */
uint8_t uSeekMedianValueAboutA( const uint16_t* upArrData,int16_t len,uint16_t* uBarArrMinMaxMedValue,uint16_t uBarArrMinMaxMedValueLen,
	                           uint16_t* uArrAndTrough,uint16_t uArrAndTroughLen,uint16_t* uBarArr1ExtentTemp,uint16_t uBarArr1ExtentTempLen,
                               uint16_t* uBarArr2ExtentTemp,uint16_t uBarArr2ExtentTempLen,uint16_t* uBarArrExtent,uint16_t uBarArrExtentLen,uint16_t uCrstAndTroghNum )
{
	uint8_t uCountB = 0;
	uint16_t uMedianValue = 0;
	uint16_t uExtent1NumTemp = 0;
	uint16_t uExtent2NumTemp = 0;
	uint16_t uExtentNum = 0;
	
	uint32_t j = 0;
	uint32_t i = 0;
	
	for( j=0;j<uCrstAndTroghNum-1;j++ ){   /* 需要保证最后两位都有数据 */
		if( 0==j%2 ){
			if( uBarArrMinMaxMedValue[uCountB]<=uBarArrMinMaxMedValue[uCountB+1] ){
				uMedianValue = uBarArrMinMaxMedValue[uCountB];
			}else{
				uMedianValue = uBarArrMinMaxMedValue[uCountB+1];
			}
			uCountB += 2;
		}else{
			if( uBarArrMinMaxMedValue[uCountB]<=uBarArrMinMaxMedValue[uCountB+1] ){
				uMedianValue = uBarArrMinMaxMedValue[uCountB+1];
			}else{
				uMedianValue = uBarArrMinMaxMedValue[uCountB];				
			}
			uCountB += 2;
		}
#if DEBUH_UART1	
#if PRIVATE_UART1	
	#if PRIVATE_SPCIAL_BAR_UART1
		myprintf( "uMedianValue %4d \r\n",uMedianValue );        /* 找到中位值最接近的点 */
	#endif
#endif
#endif		
		/* 多个中位值情况 */
		if( (0!=uArrAndTrough[j])&&(0!=uArrAndTrough[j+1])&&(0!=uMedianValue) ){			
			for( i=uArrAndTrough[j];i>uArrAndTrough[j+1];i-- ){				
				if( ((*(upArrData+i)-uMedianValue)>0)&&(*(upArrData+i)-uMedianValue)<BARCODE_FFFF ){
					if( uExtent1NumTemp<(uBarArr1ExtentTempLen) ){
						uBarArr1ExtentTemp[uExtent1NumTemp++] = i;			
					}
				}
			}
			for( i=uArrAndTrough[j+1];i>uArrAndTrough[j+2];i-- ){
				if( ((*(upArrData+i)-uMedianValue)>0)&&(*(upArrData+i)-uMedianValue)<BARCODE_FFFF ){
					if( uExtent2NumTemp<(uBarArr2ExtentTempLen) ){
						uBarArr2ExtentTemp[uExtent2NumTemp++] = i;			
					}
				}
			}
		}	

		if( 0==j%2 ){
#if STORT_STL
			qsort( uBarArr1ExtentTemp,uExtent1NumTemp,sizeof(uint16_t),cmpfuncint16min );
			qsort( uBarArr2ExtentTemp,uExtent2NumTemp,sizeof(uint16_t),cmpfuncint16max );
#else
			InsertionSortUint16_t( (uint16_t *)uBarArr1ExtentTemp,(uExtent1NumTemp),SORT_MIN );
			InsertionSortUint16_t( (uint16_t *)uBarArr2ExtentTemp,(uExtent2NumTemp),SORT_MAX );
#endif
		}else{
#if STORT_STL
			qsort( uBarArr1ExtentTemp,uExtent1NumTemp,sizeof(uint16_t),cmpfuncint16max );
			qsort( uBarArr2ExtentTemp,uExtent2NumTemp,sizeof(uint16_t),cmpfuncint16min );
#else
			InsertionSortUint16_t( (uint16_t *)uBarArr1ExtentTemp,(uExtent1NumTemp),SORT_MAX );
			InsertionSortUint16_t( (uint16_t *)uBarArr2ExtentTemp,(uExtent2NumTemp),SORT_MIN );
#endif
		}
		
#if DEBUH_UART1	
#if PRIVATE_UART1	
	#if PRIVATE_SPCIAL_BAR_UART1
		myprintf( "uBarArrExtentTemp %2d: %4d %4d \r\n",j,uBarArr1ExtentTemp[0],uBarArr2ExtentTemp[0] );        /* 找到中位值最接近的点 */
	#endif
#endif
#endif			
		uExtent1NumTemp = 0;
		if( 0!=uBarArr1ExtentTemp[0] ){
			uBarArrExtent[uExtentNum++] = uBarArr1ExtentTemp[0];
		}else{
			return NULL;
		}	
		uExtent2NumTemp = 0;
		if( 0!=uBarArr2ExtentTemp[0] ){
			uBarArrExtent[uExtentNum++] = uBarArr2ExtentTemp[0];
		}else{
			return NULL;
		}
		memset( uBarArr1ExtentTemp,0,(uBarArr1ExtentTempLen) );
		memset( uBarArr2ExtentTemp,0,(uBarArr2ExtentTempLen) );
	}
	
#if DEBUH_UART1	
	#if PRIVATE_UART1
	#if PRIVATE_SPCIAL_BAR_UART1
	for( i=0;i<(sizeof(uBarArrExtent)/sizeof(uint16_t));i++ ){
		if(0!=uBarArrExtent[i]){
			myprintf( "uBarArrExtent:%4d \r\n",uBarArrExtent[i] );
		}
	}
	#endif
	#endif
#endif
	
	return EXE_SUCCEED;
}

uint8_t uSeekMedianValueAboutB( const uint16_t* upArrData,int16_t len,uint16_t* uArrAndTrough,uint16_t uArrAndTroughLen,uint16_t* uBarArrExtentTemp,uint16_t uBarArrExtentTempLen,
                               uint16_t* uBarArrExtent,uint16_t uBarArrExtentLen,uint16_t uCrstAndTroghNum,uint16_t uMedianValue )
{
	uint16_t uExtentNumTemp = 0;
	uint16_t uExtentNum = 0;	
	uint32_t j = 0;
	uint32_t i = 0;
	

	for( j=0;j<uCrstAndTroghNum;j++){
#if DEBUH_UART1	
	#if PRIVATE_UART1	
		#if PRIVATE_SPCIAL_BAR_UART1
		myprintf( "uArrAndTrough:%4d %d uBarArrMedian:%d\r\n",uArrAndTrough[j],uArrAndTrough[j+1],uMedianValue );        /* 找到中位值最接近的点 */
		#endif
	#endif
#endif
		/* 单个中位值情况 */
		if( (0!=uArrAndTrough[j])&&(0!=uMedianValue) ){
			for( i=uArrAndTrough[j];i>uArrAndTrough[j+1];i-- ){				
				if( ((*(upArrData+i)-uMedianValue)>0)&&(*(upArrData+i)-uMedianValue)<BARCODE_FFFF ){
					if( uExtentNumTemp<(uBarArrExtentTempLen) ){
						uBarArrExtentTemp[uExtentNumTemp++] = i;			
					}
				}
			}
		}

		if( 0==j%2 ){
#if STORT_STL
			qsort( uBarArrExtentTemp,uExtentNumTemp,sizeof(uint16_t),cmpfuncint16min );
#else
			InsertionSortUint16_t( (uint16_t *)uBarArrExtentTemp,(uExtentNumTemp),SORT_MIN );
#endif
		}else{
#if STORT_STL
			qsort( uBarArrExtentTemp,uExtentNumTemp,sizeof(uint16_t),cmpfuncint16max );
#else
			InsertionSortUint16_t( (uint16_t *)uBarArrExtentTemp,(uExtentNumTemp),SORT_MAX );
#endif
		}
		
		uExtentNumTemp = 0;
		if( 0!=uBarArrExtentTemp[0] ){
			uBarArrExtent[uExtentNum++] = uBarArrExtentTemp[0];
		}else{
			return NULL;
		}		
		memset( uBarArrExtentTemp,0,uBarArrExtentTempLen );
	}

	
#if DEBUH_UART1	
	#if PRIVATE_UART1
	#if PRIVATE_SPCIAL_BAR_UART1
	for( i=0;i<(uBarArrExtentLen);i++ ){
		if(0!=uBarArrExtent[i]){
			myprintf( "uBarArrExtent:%4d \r\n",uBarArrExtent[i] );
		}
	}
	#endif
	#endif
#endif
	
	return EXE_SUCCEED;
}

/* 将波峰中间值和波谷中间值合并 计算所有中位值与曲线交点的中间值 */
uint8_t uArrCrestMiddleAndTroughMiddleA( uint16_t* uBarArrExtent,uint16_t uBarArrExtentLen,uint16_t* uBarArrExtentMedian,uint16_t uBarArrExtentMedianLen )
{
	uint32_t i = 0;
	uint8_t uCountC = 0;
	
	/* 寻找所有交点的中位值 */
	for( i=0;i<(uBarArrExtentLen);i+=2 ){
		if( (0!=uBarArrExtent[i])&&(0!=uBarArrExtent[i+1]) ){
			uBarArrExtentMedian[uCountC++] = ((uBarArrExtent[i]+uBarArrExtent[i+1])/2);
#if DEBUH_UART1	
	#if PRIVATE_UART1
	#if PRIVATE_SPCIAL_BAR_UART1
			myprintf( "uBarArrExtentMedian:%4d \r\n",uBarArrExtentMedian[uCountC-1] );
	#endif
	#endif
#endif
		}
	}

	return EXE_SUCCEED;
}

uint8_t uArrCrestMiddleAndTroughMiddleB( uint16_t* uBarArrExtent,uint16_t uBarArrExtentLen,uint16_t* uBarArrExtentMedian,uint16_t uBarArrExtentMedianLen )
{
	uint32_t i = 0;

	/* 寻找所有交点的中位值 */
	for( i=0;i<(uBarArrExtentLen);i++ ){
		if( (0!=uBarArrExtent[i])&&(0!=uBarArrExtent[i+1]) ){
			uBarArrExtentMedian[i] = ((uBarArrExtent[i]+uBarArrExtent[i+1])/2);
#if DEBUH_UART1	
	#if PRIVATE_UART1
	#if PRIVATE_SPCIAL_BAR_UART1
			myprintf( "uBarArrExtentMedian:%4d \r\n",uBarArrExtentMedian[i] );
	#endif
	#endif
#endif
		}
	}

	return EXE_SUCCEED;
}


/* 每个中位值的差值点 */
uint8_t uCalArrMedianDifference( uint16_t* uBarArrExtentMedian,uint16_t uBarArrExtentMedianLen,uint16_t* uBarArrExtentDifference,uint16_t uBarArrExtentDifferenceLen)
{
	uint32_t i = 0;
	/* 每个中位值的差值点 */
	for( i=0;i<(uBarArrExtentMedianLen);i++ ){
		if( (0!=uBarArrExtentMedian[i])&&(0!=uBarArrExtentMedian[i+1]) ){
			uBarArrExtentDifference[i] = uBarArrExtentMedian[i]-uBarArrExtentMedian[i+1];
#if DEBUH_UART1	
	#if PRIVATE_UART1
	#if PRIVATE_SPCIAL_BAR_UART1
			myprintf( "uBarArrExtentDifference:%4d \r\n",uBarArrExtentDifference[i] );
	#endif
	#endif
#endif
		}
	}
	
	return EXE_SUCCEED;
}

/* 计算点数值 */
uint8_t uCalArrDitNum( uint16_t* uBarArrExtentDifference,uint16_t uBarArrExtentDifferenceLen,float fRecDitNum,uint8_t* uBarBinValue,uint16_t uBarBinValueLen )
{
	uint32_t i = 0;
	uint8_t uRecDitNum = 0;
	uint8_t uCrstAndTroghMedianNum = 0;
	
	float fRecDitRealNum = 0;
	
	/* 计算点数值 */
	for( i=0;i<(uBarArrExtentDifferenceLen);i++ ){
		if( (0!=uBarArrExtentDifference[i]) ){			
			fRecDitRealNum = uEstimateHalfTheRange( uBarArrExtentDifference[i] );                       /* 寻找到有多少个点 */
			uRecDitNum = (fRecDitRealNum - fRecDitNum)*2;                                               /* 得到当前的点数 */
#if DEBUH_UART1	
	#if PRIVATE_UART1
		#if PRIVATE_SPCIAL_BAR_UART1
			myprintf( "uBarArrExtentDifference%2d: %4d %2.2f %2.2f %2.2f %2.2f %4d \r\n",i,uBarArrExtentDifference[i],fRecDitRealNum,fRecDitNum,(fRecDitRealNum - fRecDitNum),(fRecDitRealNum - fRecDitNum)*2,uRecDitNum );
		#endif
	#else
		myprintf( "uBarArrExtentDifference%2d: %4d %2.2f %2.2f %2.2f %2.2f %4d \r\n",i,uBarArrExtentDifference[i],fRecDitRealNum,fRecDitNum,(fRecDitRealNum - fRecDitNum),(fRecDitRealNum - fRecDitNum)*2,uRecDitNum );	
	#endif
#endif			
			fRecDitNum = (fRecDitRealNum - fRecDitNum);		                                            /* 保留上一个点的数据 */
			if( fRecDitNum<=0 ){
#if DEBUH_UART1	
				myprintf( "The critical value: %4d %4d %4d \r\n",uBarArrExtentDifference[i-1],uBarArrExtentDifference[i],uBarArrExtentDifference[i+1] );   /* 将临界值打印出来 */
#endif	
				return EXE_FAILED;
			}
			uCrstAndTroghMedianNum = strlen((const char *)uBarBinValue);
			if( (uCrstAndTroghMedianNum+uRecDitNum)<(uBarBinValueLen) ){
				uEstimateTheDitNum( (uint8_t *)(uBarBinValue+uCrstAndTroghMedianNum),uRecDitNum,i );		/* 将当前的点数存储到数组 */
			}else{
#if DEBUH_UART1	
				myprintf( "uBarBinValue Overflow \r\n" );   /* 将临界值打印出来 */
#endif	
			}				
		}
	}
	
	return EXE_SUCCEED;
}
	
/* 将得到的条码值转换为0 1 数值并得出条码值 */
uint8_t uGetArrBarAssiiValue( uint8_t* uBarBinValue,uint16_t uBarBinValueLen,uint8_t* uBarBinValueTemp,uint16_t uBarBinValueTempLen,
							  uint8_t* uBarExtentValue,uint16_t uBarExtentValueLen,uint8_t* upArrBar )
{
	uint32_t i = 0;
	
	/* 将起转换为0 1 数值 */
	for( i=0;i<(uBarBinValueLen);i++ ){	
		if( 50==uBarBinValue[i] ){
			uBarBinValueTemp[i] = 0;
		}else if( 49==uBarBinValue[i] ){
			uBarBinValueTemp[i] = 1;
		}	
	}
	/* 打印条码二进制数据 */
#if DEBUH_UART1	
	#if PRIVATE_UART1
	myprintf( "uBarBinValueTemp:\r\n" ); 
	//for( i=0;i<(sizeof(uBarBinValueTemp)/sizeof(uint8_t));i++ ){
	for( i=0;i<(BARCODE_DIT_NUMBER);i++ ){
		myprintf( "%1d",uBarBinValueTemp[i] );
	}
	myprintf( "\r\n" ); 
	#endif
#endif
	
	/* 得出条码值 */
	for( i=0;i<4;i++ ){
		uBarExtentValue[i] = (uBarBinValueTemp[(i*4)+0]<<3)|(uBarBinValueTemp[(i*4)+1]<<2)|(uBarBinValueTemp[(i*4)+2]<<1)|(uBarBinValueTemp[(i*4)+3]<<0);
	}
	if( 0==uBarBinValueTemp[16] )	{
		uBarExtentValue[4] = 0;
	}else{
		uBarExtentValue[4] = 8;
	}
	
	memcpy( (char *)upArrBar,(const char *)uBarExtentValue,uBarExtentValueLen );
#if DEBUH_UART1	
	#if PRIVATE_UART1
	myprintf( "uBarExtentValue: " );
	for( i=0;i<(uBarExtentValueLen);i++ ){
		myprintf( "%2x ",uBarExtentValue[i] );
	}
	myprintf( "\r\n");
	#endif
#endif
	
	return EXE_SUCCEED;
}

/*  */
int16_t uCalculateMedianValue( uint16_t* puBarArrMin,uint16_t uArrAlen,uint16_t* puBarArrMax,uint16_t uArrBlen )
{
#if DEBUH_UART1	
	#if PRIVATE_UART1
	#if PRIVATE_SPCIAL_BAR_UART1
	int i = 0;
	#endif
	#endif
#endif
	uint16_t uMedianValue = 0;
	
	if( (0==uArrAlen)||(0==uArrBlen) ){
		return EXE_SPECIAL_FAILED;
	}else{
#if STORT_STL
		qsort( puBarArrMin,uArrAlen,sizeof(uint16_t),cmpfuncint16max );
		qsort( puBarArrMax,uArrBlen,sizeof(uint16_t),cmpfuncint16min );
#else
		InsertionSortUint16_t( (uint16_t *)puBarArrMin,(uArrAlen),SORT_MAX );
		InsertionSortUint16_t( (uint16_t *)puBarArrMax,(uArrBlen),SORT_MIN );
#endif
	}
#if DEBUH_UART1	
	#if PRIVATE_UART1
	#if PRIVATE_SPCIAL_BAR_UART1
	for( i=0;i<((uArrAlen+uArrBlen)/2);i++ ){
		if(0!=puBarArrMin[i]){
			myprintf( "qsortuBarArrMin:%4d \r\n",puBarArrMin[i] );
		}
		if(0!=puBarArrMax[i]){
			myprintf( "qsortuBarArrMax:%4d \r\n",puBarArrMax[i] );
		}
	}
	#endif
	#endif
#endif
	
	if( (0!=puBarArrMin[0])&&(0!=puBarArrMax[0]) ){
		uMedianValue = ((puBarArrMin[0]+puBarArrMax[0])/2);   /* 中位值计算 */
	}else{
		return EXE_SPECIAL_FAILED;
	}
#if DEBUH_UART1	
	#if PRIVATE_UART1	
	#if PRIVATE_SPCIAL_BAR_UART1
		myprintf( "uMedianValue: %6d %6d %6d \r\n",puBarArrMin[0],puBarArrMax[0],uMedianValue );
	#endif
	#endif
#endif	
	
	return uMedianValue;
}

uint8_t uEstimateTheRange( uint8_t* puArrDit,uint16_t uBarData,uint8_t uNumData )
{
	uint8_t uDitNumber = 0;
	
	if(0==uNumData%2){
		if( (BAR_0_00_RANG<uBarData)&&(uBarData<BAR_0_02_RANG) ){	
			sprintf( (char *)(puArrDit),"%s","2" ); 
			uDitNumber = 1;
		}else if( (BAR_0_02_RANG<=uBarData)&&(uBarData<BAR_0_03_RANG) ){
			sprintf( (char *)(puArrDit),"%s","22" ); 
			uDitNumber = 2;
		}else if( (BAR_0_03_RANG<=uBarData)&&(uBarData<BAR_0_04_RANG) ){
			sprintf( (char *)(puArrDit),"%s","222" ); 
			uDitNumber = 3;
		}else if( (BAR_0_04_RANG<=uBarData)&&(uBarData<BAR_0_05_RANG) ){
			sprintf( (char *)(puArrDit),"%s","2222" ); 
			uDitNumber = 4;
		}else if( (BAR_0_05_RANG<=uBarData)&&(uBarData<BAR_0_06_RANG) ){   /* 5 */
			sprintf( (char *)(puArrDit),"%s","22222" ); 
			uDitNumber = 5;
		}else if( (BAR_0_06_RANG<=uBarData)&&(uBarData<BAR_0_07_RANG) ){   /* 6 */
			sprintf( (char *)(puArrDit),"%s","222222" ); 
			uDitNumber = 6;
		}else if( (BAR_0_07_RANG<=uBarData)&&(uBarData<BAR_0_08_RANG) ){   /* 7 */
			sprintf( (char *)(puArrDit),"%s","2222222" ); 
			uDitNumber = 7;
		}else if( (BAR_0_08_RANG<=uBarData)&&(uBarData<BAR_0_09_RANG) ){   /* 8 */
			sprintf( (char *)(puArrDit),"%s","22222222" ); 
			uDitNumber = 8;
		}else if( (BAR_0_09_RANG<=uBarData)&&(uBarData<BAR_0_10_RANG) ){   /* 9 */
			sprintf( (char *)(puArrDit),"%s","222222222" ); 
			uDitNumber = 9;
		}else if( (BAR_0_10_RANG<=uBarData)&&(uBarData<BAR_0_11_RANG) ){   /* 10 */
			sprintf( (char *)(puArrDit),"%s","2222222222" ); 
			uDitNumber = 10;
		}else if( (BAR_0_11_RANG<=uBarData)&&(uBarData<BAR_0_12_RANG) ){   /* 11 */
			sprintf( (char *)(puArrDit),"%s","22222222222" ); 
			uDitNumber = 11;
		}else if( (BAR_0_12_RANG<=uBarData)&&(uBarData<BAR_0_13_RANG) ){   /* 12 */
			sprintf( (char *)(puArrDit),"%s","222222222222" ); 
			uDitNumber = 12;
		}else if( (BAR_0_13_RANG<=uBarData)&&(uBarData<BAR_0_14_RANG) ){   /* 13 */
			sprintf( (char *)(puArrDit),"%s","2222222222222" ); 
			uDitNumber = 13;
		}else if( (BAR_0_14_RANG<=uBarData)&&(uBarData<BAR_0_15_RANG) ){  /* 14 */
			sprintf( (char *)(puArrDit),"%s","22222222222222" ); 
			uDitNumber = 14;
		}else if( (BAR_0_15_RANG<=uBarData)&&(uBarData<BAR_0_16_RANG) ){   /* 15 */
			sprintf( (char *)(puArrDit),"%s","222222222222222" ); 
			uDitNumber = 15;
		}else if( (BAR_0_16_RANG<=uBarData)&&(uBarData<BAR_0_17_RANG) ){  /* 16 */
			sprintf( (char *)(puArrDit),"%s","2222222222222222" ); 
			uDitNumber = 16;
		}else if( (BAR_0_17_RANG<=uBarData)&&(uBarData<BAR_0_18_RANG) ){   /* 17 */
			sprintf( (char *)(puArrDit),"%s","22222222222222222" ); 
			uDitNumber = 17;
		}else{
#if DEBUH_UART1	
	#if PRIVATE_UART1
			myprintf( "ET\r\n" );
	#endif
#endif
		}
	}else{
		if( (BAR_1_00_RANG<uBarData)&&(uBarData<BAR_1_02_RANG) ){				
			sprintf( (char *)(puArrDit),"%s","1" ); 
			uDitNumber = 1;
		}else if( (BAR_1_02_RANG<=uBarData)&&(uBarData<BAR_1_03_RANG) ){
			sprintf( (char *)(puArrDit),"%s","11" ); 
			uDitNumber = 2;
		}else if( (BAR_1_03_RANG<=uBarData)&&(uBarData<BAR_1_04_RANG) ){
			sprintf( (char *)(puArrDit),"%s","111" ); 
			uDitNumber = 3;
		}else if( (BAR_1_04_RANG<=uBarData)&&(uBarData<BAR_1_05_RANG) ){
			sprintf( (char *)(puArrDit),"%s","1111" ); 
			uDitNumber = 4;
		}else if( (BAR_1_05_RANG<=uBarData)&&(uBarData<BAR_1_06_RANG) ){  /* 5 */
			sprintf( (char *)(puArrDit),"%s","11111" ); 
			uDitNumber = 5;
		}else if( (BAR_1_06_RANG<=uBarData)&&(uBarData<BAR_1_07_RANG) ){  /* 6 */
			sprintf( (char *)(puArrDit),"%s","111111" ); 
			uDitNumber = 6;
		}else if( (BAR_1_07_RANG<=uBarData)&&(uBarData<BAR_1_08_RANG) ){  /* 7 */
			sprintf( (char *)(puArrDit),"%s","1111111" ); 
			uDitNumber = 7;
		}else if( (BAR_1_08_RANG<=uBarData)&&(uBarData<BAR_1_09_RANG) ){  /* 8 */
			sprintf( (char *)(puArrDit),"%s","11111111" ); 
			uDitNumber = 8;
		}else if( (BAR_1_09_RANG<=uBarData)&&(uBarData<BAR_1_10_RANG) ){  /* 9 */
			sprintf( (char *)(puArrDit),"%s","111111111" ); 
			uDitNumber = 9;
		}else if( (BAR_1_10_RANG<=uBarData)&&(uBarData<BAR_1_11_RANG) ){  /* 10 */
			sprintf( (char *)(puArrDit),"%s","1111111111" ); 
			uDitNumber = 10;
		}else if( (BAR_1_11_RANG<=uBarData)&&(uBarData<BAR_1_12_RANG) ){  /* 11 */
			sprintf( (char *)(puArrDit),"%s","11111111111" ); 
			uDitNumber = 11;
		}else if( (BAR_1_12_RANG<uBarData)&&(uBarData<BAR_1_13_RANG) ){   /* 12 */
			sprintf( (char *)(puArrDit),"%s","111111111111" ); 
			uDitNumber = 12;
		}else if( (BAR_1_13_RANG<=uBarData)&&(uBarData<BAR_1_14_RANG) ){  /* 13 */
			sprintf( (char *)(puArrDit),"%s","1111111111111" ); 
			uDitNumber = 13;
		}else if( (BAR_1_14_RANG<=uBarData)&&(uBarData<BAR_1_15_RANG) ){  /* 14 */
			sprintf( (char *)(puArrDit),"%s","11111111111111" ); 
			uDitNumber = 14;
		}else if( (BAR_1_15_RANG<=uBarData)&&(uBarData<BAR_1_16_RANG) ){  /* 15 */
			sprintf( (char *)(puArrDit),"%s","111111111111111" ); 
			uDitNumber = 15;
		}else if( (BAR_1_16_RANG<=uBarData)&&(uBarData<BAR_1_17_RANG) ){  /* 16 */
			sprintf( (char *)(puArrDit),"%s","1111111111111111" ); 
			uDitNumber = 16;
		}else if( (BAR_1_17_RANG<=uBarData)&&(uBarData<BAR_1_18_RANG) ){  /* 17 */
			sprintf( (char *)(puArrDit),"%s","11111111111111111" ); 
			uDitNumber = 17;
		}else{
#if DEBUH_UART1	
	#if PRIVATE_UART1
			myprintf( "EC\r\n" );
	#endif
#endif
		}
	}	
	
	return uDitNumber;
}

float uEstimateHalfTheRange( uint16_t uBarData )
{
	float uDitNumber = 0;	

	if( (F_BAR_1_00_RANG<uBarData)&&(uBarData<=F_BAR_1_02_RANG) ){			
		uDitNumber = 0.5;
	}else if( (F_BAR_1_02_RANG<uBarData)&&(uBarData<=F_BAR_1_03_RANG) ){
		uDitNumber = 1;
	}else if( (F_BAR_1_03_RANG<uBarData)&&(uBarData<=F_BAR_1_04_RANG) ){
		uDitNumber = 1.5;
	}else if( (F_BAR_1_04_RANG<uBarData)&&(uBarData<=F_BAR_1_05_RANG) ){
		uDitNumber = 2;
	}else if( (F_BAR_1_05_RANG<uBarData)&&(uBarData<=F_BAR_1_06_RANG) ){   /* 5 */
		uDitNumber = 2.5;
	}else if( (F_BAR_1_06_RANG<uBarData)&&(uBarData<=F_BAR_1_07_RANG) ){   /* 6 */
		uDitNumber = 3;
	}else if( (F_BAR_1_07_RANG<uBarData)&&(uBarData<=F_BAR_1_08_RANG) ){   /* 7 */
		uDitNumber = 3.5;
	}else if( (F_BAR_1_08_RANG<uBarData)&&(uBarData<=F_BAR_1_09_RANG) ){   /* 8 */
		uDitNumber = 4;
	}else if( (F_BAR_1_09_RANG<uBarData)&&(uBarData<=F_BAR_1_10_RANG) ){   /* 9 */ 
		uDitNumber = 4.5;
	}else if( (F_BAR_1_10_RANG<uBarData)&&(uBarData<=F_BAR_1_11_RANG) ){   /* 10 */
		uDitNumber = 5;
	}else if( (F_BAR_1_11_RANG<uBarData)&&(uBarData<=F_BAR_1_12_RANG) ){   /* 11 */
		uDitNumber = 5.5;
	}else if( (F_BAR_1_12_RANG<uBarData)&&(uBarData<=F_BAR_1_13_RANG) ){   /* 12 */
		uDitNumber = 6;
	}else if( (F_BAR_1_13_RANG<uBarData)&&(uBarData<=F_BAR_1_14_RANG) ){   /* 13 */
		uDitNumber = 6.5;
	}else if( (F_BAR_1_14_RANG<uBarData)&&(uBarData<=F_BAR_1_15_RANG) ){  /* 14 */
		uDitNumber = 7;
	}else if( (F_BAR_1_15_RANG<uBarData)&&(uBarData<=F_BAR_1_16_RANG) ){   /* 15 */
		uDitNumber = 7.5;
	}else if( (F_BAR_1_16_RANG<uBarData)&&(uBarData<=F_BAR_1_17_RANG) ){  /* 16 */
		uDitNumber = 8;
	}else if( (F_BAR_1_17_RANG<uBarData)&&(uBarData<=F_BAR_1_18_RANG) ){   /* 17 */
		uDitNumber = 8.5;
	}else if( (F_BAR_1_18_RANG<uBarData)&&(uBarData<=F_BAR_1_19_RANG) ){			
		uDitNumber = 9;
	}else if( (F_BAR_1_19_RANG<uBarData)&&(uBarData<=F_BAR_1_20_RANG) ){
		uDitNumber = 9.5;
	}else if( (F_BAR_1_20_RANG<uBarData)&&(uBarData<=F_BAR_1_21_RANG) ){
		uDitNumber = 10;
	}else if( (F_BAR_1_21_RANG<uBarData)&&(uBarData<=F_BAR_1_22_RANG) ){
		uDitNumber = 10.5;
	}else if( (F_BAR_1_22_RANG<uBarData)&&(uBarData<=F_BAR_1_23_RANG) ){   /* 5 */
		uDitNumber = 11;
	}else if( (F_BAR_1_23_RANG<uBarData)&&(uBarData<=F_BAR_1_24_RANG) ){   /* 6 */
		uDitNumber = 11.5;
	}else if( (F_BAR_1_24_RANG<uBarData)&&(uBarData<=F_BAR_1_25_RANG) ){   /* 7 */
		uDitNumber = 12;
	}else if( (F_BAR_1_25_RANG<uBarData)&&(uBarData<=F_BAR_1_26_RANG) ){   /* 8 */
		uDitNumber = 12.5;
	}else if( (F_BAR_1_26_RANG<uBarData)&&(uBarData<=F_BAR_1_27_RANG) ){   /* 9 */ 
		uDitNumber = 13;
	}else if( (F_BAR_1_27_RANG<uBarData)&&(uBarData<=F_BAR_1_28_RANG) ){   /* 10 */
		uDitNumber = 13.5;
	}else if( (F_BAR_1_28_RANG<uBarData)&&(uBarData<=F_BAR_1_29_RANG) ){   /* 11 */
		uDitNumber = 14;
	}else if( (F_BAR_1_29_RANG<uBarData)&&(uBarData<=F_BAR_1_30_RANG) ){   /* 12 */
		uDitNumber = 14.5;
	}else if( (F_BAR_1_30_RANG<uBarData)&&(uBarData<=F_BAR_1_31_RANG) ){   /* 13 */
		uDitNumber = 15;
	}else if( (F_BAR_1_31_RANG<uBarData)&&(uBarData<=F_BAR_1_32_RANG) ){  /* 14 */
		uDitNumber = 15.5;
	}else if( (F_BAR_1_32_RANG<uBarData)&&(uBarData<=F_BAR_1_33_RANG) ){   /* 15 */
		uDitNumber = 16;
	}else if( (F_BAR_1_33_RANG<uBarData)&&(uBarData<=F_BAR_1_34_RANG) ){  /* 16 */
		uDitNumber = 16.5;
	}else if( (F_BAR_1_34_RANG<uBarData)&&(uBarData<=F_BAR_1_35_RANG) ){   /* 17 */
		uDitNumber = 17;
	}else{
#if DEBUH_UART1	
	#if PRIVATE_UART1
		myprintf( "ET\r\n" );
	#endif
#endif
	}
	
	return uDitNumber;
}

uint8_t uEstimateTheDitNum( uint8_t* puArrDit,uint16_t uBarData,uint8_t uNumData )
{
	uint8_t uDitNumber = 0;
	
	if(0==uNumData%2){
		switch( uBarData ){
			case 1:
				sprintf( (char *)(puArrDit),"%s","2" ); 
				uDitNumber = 1;
				break;
			case 2:
				sprintf( (char *)(puArrDit),"%s","22" ); 
				uDitNumber = 2;
				break;
			case 3:
				sprintf( (char *)(puArrDit),"%s","222" ); 
				uDitNumber = 3;
				break;
			case 4:
				sprintf( (char *)(puArrDit),"%s","2222" ); 
				uDitNumber = 4;
				break;
			case 5:
				sprintf( (char *)(puArrDit),"%s","22222" ); 
				uDitNumber = 5;
				break;
			case 6:
				sprintf( (char *)(puArrDit),"%s","222222" ); 
				uDitNumber = 6;
				break;
			case 7:
				sprintf( (char *)(puArrDit),"%s","2222222" ); 
				uDitNumber = 7;
				break;
			case 8:
				sprintf( (char *)(puArrDit),"%s","22222222" ); 
				uDitNumber = 8;
				break;
			case 9:
				sprintf( (char *)(puArrDit),"%s","222222222" ); 
				uDitNumber = 9;
				break;
			case 10:
				sprintf( (char *)(puArrDit),"%s","2222222222" ); 
				uDitNumber = 10;
				break;
			case 11:
				sprintf( (char *)(puArrDit),"%s","22222222222" ); 
				uDitNumber = 11;
				break;
			case 12:
				sprintf( (char *)(puArrDit),"%s","222222222222" ); 
				uDitNumber = 12;
				break;
			case 13:
				sprintf( (char *)(puArrDit),"%s","2222222222222" ); 
				uDitNumber = 13;
				break;
			case 14:
				sprintf( (char *)(puArrDit),"%s","22222222222222" ); 
				uDitNumber = 14;
				break;
			case 15:
				sprintf( (char *)(puArrDit),"%s","222222222222222" ); 
				uDitNumber = 15;
				break;
			case 16:
				sprintf( (char *)(puArrDit),"%s","2222222222222222" ); 
				uDitNumber = 16;
				break;
			case 17:
				sprintf( (char *)(puArrDit),"%s","22222222222222222" ); 
				uDitNumber = 17;
				break;
		
			default:
#if DEBUH_UART1	
	#if PRIVATE_UART1
			myprintf( "D_B_ET\r\n" );
	#endif
#endif
				break;
		}
		
	}else{
		switch( uBarData ){
			case 1:
				sprintf( (char *)(puArrDit),"%s","1" ); 
				uDitNumber = 1;
				break;
			case 2:
				sprintf( (char *)(puArrDit),"%s","11" ); 
				uDitNumber = 2;
				break;
			case 3:
				sprintf( (char *)(puArrDit),"%s","111" ); 
				uDitNumber = 3;
				break;
			case 4:
				sprintf( (char *)(puArrDit),"%s","1111" ); 
				uDitNumber = 4;
				break;
			case 5:
				sprintf( (char *)(puArrDit),"%s","11111" ); 
				uDitNumber = 5;
				break;
			case 6:
				sprintf( (char *)(puArrDit),"%s","111111" ); 
				uDitNumber = 6;
				break;
			case 7:
				sprintf( (char *)(puArrDit),"%s","1111111" ); 
				uDitNumber = 7;
				break;
			case 8:
				sprintf( (char *)(puArrDit),"%s","11111111" ); 
				uDitNumber = 8;
				break;
			case 9:
				sprintf( (char *)(puArrDit),"%s","111111111" ); 
				uDitNumber = 9;
				break;
			case 10:
				sprintf( (char *)(puArrDit),"%s","1111111111" ); 
				uDitNumber = 10;
				break;
			case 11:
				sprintf( (char *)(puArrDit),"%s","11111111111" ); 
				uDitNumber = 11;
				break;
			case 12:
				sprintf( (char *)(puArrDit),"%s","111111111111" ); 
				uDitNumber = 12;
				break;
			case 13:
				sprintf( (char *)(puArrDit),"%s","1111111111111" ); 
				uDitNumber = 13;
				break;
			case 14:
				sprintf( (char *)(puArrDit),"%s","11111111111111" ); 
				uDitNumber = 14;
				break;
			case 15:
				sprintf( (char *)(puArrDit),"%s","111111111111111" ); 
				uDitNumber = 15;
				break;
			case 16:
				sprintf( (char *)(puArrDit),"%s","1111111111111111" ); 
				uDitNumber = 16;
				break;
			case 17:
				sprintf( (char *)(puArrDit),"%s","11111111111111111" ); 
				uDitNumber = 17;
				break;
		
			default:
#if DEBUH_UART1	
	#if PRIVATE_UART1
			myprintf( "D_W_ET\r\n" );
	#endif
#endif
				break;
		}
	}	
	
	return uDitNumber;
}

uint8_t uBarCalValue( uint8_t *piBar,uint8_t uInsert,uint8_t uNum,uint8_t uStatus )
{
	int i = 0;
	if( uInsert+uNum<38 ){
		if( 0==uStatus ){
			for( i=uInsert;i<uInsert+uNum;i++ ){
				*(piBar+i) = 0;
			}
		}else{
			for( i=uInsert;i<uInsert+uNum;i++ ){
				*(piBar+i) = 1;
			}
		}
	}
	
	return EXE_SUCCEED;
}

int iGetIntergeNumber( int *pNum )
{
	int iNum = 0;
	
	while( 0!=*(pNum+iNum) ){
		iNum++;
	}
	
	return iNum-1;
}

/* 计算短整形数据的个数 */
int iGetHalfIntergeNumber( unsigned short int *pNum )
{
	int iNum = 0;
	
	while( 0!=*(pNum+iNum) ){
		iNum++;
	}
	
	return iNum;
}

///* 算平均线之间的距离 */
//uint8_t* uWaveCrestTrough( const uint16_t* upArrData,uint8_t* upArrBar,int len )
//{
//	uint8_t uCrestTroughStatus = 0;
//	int i = 0;
//	int j = 0;
//	uint8_t ua = 0;
//	uint8_t ub = 0;
//	uint8_t uc = 0;
//	uint8_t ue = 0;
//	uint8_t ug = 0;
//	uint8_t uh = 0;
//	uint8_t uj = 0;
//	uint16_t uArrCrest[20] = {0};
//	uint16_t uArrTrough[20] = {0};
//	uint16_t uArrAndTrough[44] = {0};

//	/* 此处增加 */
//	uint16_t uExtentNum = 0;
//	uint16_t uBarArrExtent[44] = {0};
//	uint16_t uBarArrExtentMedian[44] = {0};
//	uint16_t uBarArrExtentDifference[44] = {0};
//	uint16_t uBarArrMax[20] = {0};
//	uint16_t uBarArrMin[20] = {0};
//	uint8_t uBarBinValue[44] = {0};
//	uint8_t uBarBinValueTemp[44] = {0};
//	uint8_t uBarExtentValue[5] = {0};
//	uint8_t uCrstAndTroghNum = 0;
//	uint8_t uCrstAndTroghMedianNum = 0;
//	uint8_t uRecDitNum = 0;
//	uint16_t uMedianValue = 0;
//	float fRecDitNum = 0;
//	float fRecDitRealNum = 0;
//#if VARIOUS_MEDIAN_DIT			
//	uint8_t uCountA = 0;
//	uint8_t uCountB = 0;
//	uint8_t uCountC = 0;
//	uint8_t uk = 0;
//	uint8_t uRecError = 0;
//	uint16_t uBarArrMinMaxMed[44] = {0};
//	uint16_t uBarArrMinMaxMedValue[44] = {0};
//	uint16_t uExtent1NumTemp = 0;
//	uint16_t uBarArr1ExtentTemp[44] = {0};
//	uint16_t uExtent2NumTemp = 0;
//	uint16_t uBarArr2ExtentTemp[44] = {0};
//#else
//	uint16_t uBarArrMaxLen = 0;
//	uint16_t uBarArrMinLen = 0;
//	uint16_t uBarArrMaxTemp[20] = {0};
//	uint16_t uBarArrMinTemp[20] = {0};
//	uint16_t uExtentNumTemp = 0;
//	uint16_t uBarArrExtentTemp[44] = {0};
//#endif
//#if DEBUH_UART1	
//#if PRIVATE_UART1
//#if PRIVATE_SPCIAL_BAR_UART1
//	int k = 0;
//#endif
//#endif
//#endif

//	uint16_t* puTempBarAdValue = NULL;
//	puTempBarAdValue = (uint16_t *)calloc( BARVODE_LENGTH,sizeof(uint16_t) );
//	if( NULL==puTempBarAdValue ){
//		return NULL;
//	}
//	/* 此处增加 */
//		
//	/* 相对波峰和波谷点 */
//	for( i=(len-1);i>(BAR_AVERAGE_NUM+1);i-- ){
//		if( 0==uCrestTroughStatus ){  /* 找下降点 */      
//			if( *(upArrData+i)-*(upArrData+(i-1))>BAR_START_THRESHOLD ){ /* 此处阈值需要大量测试 */
//				while( ua<BAR_AVERAGE_NUM ){
//					i--;
//					if( *(upArrData+i)-*(upArrData+(i-1))>BAR_START_THRESHOLD ){
//						ub++;
//					}
//					ua++;
//				}				
//#if DEBUH_UART1	
//	#if PRIVATE_UART1
//		#if PRIVATE_SPCIAL_BAR_UART1
//				myprintf( "WaveCrest ub:%4d i:%4d \r\n",ub,i );
//		#endif
//	#endif
//#endif
//				if( (ub>=BAR_AVE_NUM) ){	
//					if( uc<sizeof(uArrCrest) ){
//						uArrCrest[uc++] = i+BAR_AVERAGE_NUM;
//					}
//					uCrestTroughStatus = 1;
//				}
//				ub = 0;
//				ua = 0;
//			}
//		}else if( 1==uCrestTroughStatus ){    /* 找上升点 */ 
//			if( *(upArrData+i)-*(upArrData+(i-1))<(-BAR_START_THRESHOLD) ){
//				while( ue<BAR_AVERAGE_NUM ){
//					i--;
//					if( *(upArrData+i)-*(upArrData+(i-1))<(-BAR_START_THRESHOLD) ){
//						ug++;
//					}
//					ue++;
//				}
//#if DEBUH_UART1	
//	#if PRIVATE_UART1
//		#if PRIVATE_SPCIAL_BAR_UART1
//				myprintf( "WaveTrough ug:%4d i:%4d \r\n",ug,i );
//		#endif
//	#endif
//#endif
//				if( (ug>=BAR_AVE_NUM) ){
//					if( uh<sizeof(uArrTrough) ){
//						uArrTrough[uh++] = i+BAR_AVERAGE_NUM;
//					}
//					uCrestTroughStatus = 0;
//				}
//				ue = 0;
//				ug = 0;
//			}
//		}			
//	}
//	
//#if DEBUH_UART1	
//#if PRIVATE_UART1
//	#if PRIVATE_SPCIAL_BAR_UART1
//	for( i=0;i<(sizeof(uArrCrest)/sizeof(uint16_t));i++ ){
//		if(0!=uArrCrest[i]){
//			myprintf( "uArrCrest:%4d \r\n",uArrCrest[i] );
//		}
//		if(0!=uArrTrough[i]){
//			myprintf( "uArrTrough:%4d \r\n",uArrTrough[i] );
//		}
//	}
//	#endif
//	#endif
//#endif
//	/* 找到波峰和波谷中绝对的最小值和最大值 */
//	for( i=0;i<(sizeof(uArrCrest)/sizeof(uint16_t));i++ ){
//		if( (0!=uArrCrest[i])){		  /* &&(0!=uArrCrest[i+1]) */
//			memcpy( (char *)puTempBarAdValue,(const char *)((uint16_t *)upArrData+uArrCrest[i+1]),(uArrCrest[i]-uArrCrest[i+1])*sizeof(uint16_t) );	
//#if STORT_STL
//			qsort( (uint16_t *)puTempBarAdValue,(uArrCrest[i]-uArrCrest[i+1]),sizeof(uint16_t),cmpfuncint16min );
//#else
//			InsertionSortUint16_t( (uint16_t *)puTempBarAdValue,(uArrCrest[i]-uArrCrest[i+1]),SORT_MIN );
//			
//	#if DEBUH_UART1	
//		#if PRIVATE_UART1
//			#if PRIVATE_SPCIAL_BAR_UART1
//			for( k=0;k<5;k++ ){
//				myprintf( "Min puTempBarAdValue:%d\r\n",puTempBarAdValue[i]);
//			}
//			#endif
//		#endif
//	#endif
//			
//#endif
//			if( 0!=puTempBarAdValue[0] ){
//				uBarArrMin[i] = puTempBarAdValue[0];		
//			}else{
//				uRecError = EXE_FAILED;
//			}				

//#if DEBUH_UART1	
//	#if PRIVATE_UART1
//			#if PRIVATE_SPCIAL_BAR_UART1
//			myprintf( "uBarArrMin:%4d %4d %4d %d \r\n",uArrCrest[i+1],uArrCrest[i],uBarArrMin[i],puTempBarAdValue[0] );  /* 下一个波峰 当前波峰 最小条码AD值 确认是否是第一个值 */
//			#endif
//		#endif
//#endif
//			memset( puTempBarAdValue,0,BARVODE_LENGTH );
//		}
//		if( (0!=uArrTrough[i])){		/* &&(0!=uArrTrough[i+1])  */
//			memcpy( (char *)puTempBarAdValue,(const char *)((uint16_t *)upArrData+uArrTrough[i+1]),(uArrTrough[i]-uArrTrough[i+1])*sizeof(uint16_t) );		
//#if STORT_STL
//			qsort( (uint16_t *)puTempBarAdValue,(uArrTrough[i]-uArrTrough[i+1]),sizeof(uint16_t),cmpfuncint16max );
//#else
//			InsertionSortUint16_t( (uint16_t *)puTempBarAdValue,(uArrTrough[i]-uArrTrough[i+1]),SORT_MAX );
//			
//	#if DEBUH_UART1	
//		#if PRIVATE_UART1
//			#if PRIVATE_SPCIAL_BAR_UART1
//			for( k=0;k<5;k++ ){
//				myprintf( "Max puTempBarAdValue:%d\r\n",puTempBarAdValue[i]);
//			}
//			#endif
//		#endif
//	#endif
//			
//#endif
//			if( 0!=puTempBarAdValue[0] ){
//				uBarArrMax[i] = puTempBarAdValue[0];
//			}else{
//				uRecError = EXE_FAILED;
//			}
//			
//#if DEBUH_UART1	
//	#if PRIVATE_UART1
//			#if PRIVATE_SPCIAL_BAR_UART1
//			myprintf( "uBarArrMax:%4d %4d %4d %d \r\n",uArrTrough[i+1],uArrTrough[i],uBarArrMax[i],puTempBarAdValue[0] );
//			#endif
//		#endif
//#endif
//			memset( puTempBarAdValue,0,sizeof(BARVODE_LENGTH) );
//		}
//	}	
//	
//	if( NULL!=puTempBarAdValue ){
//		free( puTempBarAdValue );
//	}
//	if( EXE_FAILED==uRecError ){
//		return EXE_SUCCEED;
//	}	

//#if VARIOUS_MEDIAN_DIT		
//	/* 求绝对最小值和最大值的中位线 */
//	uBarArrMinMaxMed[uk++] = *(upArrData+uArrCrest[0]);            /* 起点 */
//	for( i=0;i<(sizeof(uBarArrMin)/sizeof(uint16_t));i++ ){		   /* 将最小值和最大值合并 */
//		if(0!=uBarArrMin[i]){
//			uBarArrMinMaxMed[uk++] = uBarArrMin[i];
//		}
//		if(0!=uBarArrMax[i]){
//			uBarArrMinMaxMed[uk++] = uBarArrMax[i];
//		}
//	}	
//#if DEBUH_UART1	
//#if PRIVATE_UART1	
//	#if PRIVATE_SPCIAL_BAR_UART1
//	for( i=0;i<(sizeof(uBarArrMinMaxMed)/sizeof(uint16_t));i++ ){
//		if( 0!=uBarArrMinMaxMed[i] ){
//			myprintf( "uBarArrMinMaxMed %2d:%4d \r\n",i,uBarArrMinMaxMed[i] );        /*  */
//		}
//	}
//	#endif
//#endif
//#endif

////	uBarArrMinMaxMedValue[uCountA++] = (uBarArrMinMaxMed[0]+uBarArrMinMaxMed[1])/2;   /* 第一个值特殊 */
////	uBarArrMinMaxMedValue[uCountA++] = (uBarArrMinMaxMed[0]+uBarArrMinMaxMed[1])/2;   /* 第一个值特殊 */	
//	for( i=0;i<(sizeof(uBarArrMinMaxMed)/sizeof(uint16_t));i++ ){   /* 将计算出的中位值存储到数组 */
//		if( (0!=uBarArrMinMaxMed[i])&&(0!=uBarArrMinMaxMed[i+1])&&(0!=uBarArrMinMaxMed[i+2]) ){
//			uBarArrMinMaxMedValue[uCountA++] = (uBarArrMinMaxMed[i]+uBarArrMinMaxMed[i+1])/2;
//			uBarArrMinMaxMedValue[uCountA++] = (uBarArrMinMaxMed[i+1]+uBarArrMinMaxMed[i+2])/2;
//		}
//	}		
//#if DEBUH_UART1	
//#if PRIVATE_UART1	
//	#if PRIVATE_SPCIAL_BAR_UART1
//	for( i=0;i<(sizeof(uBarArrMinMaxMedValue)/sizeof(uint16_t));i++ ){
//		if( 0!=uBarArrMinMaxMedValue[i] ){
//			myprintf( "uBarArrMinMaxMedValue %2d:%4d \r\n",i,uBarArrMinMaxMedValue[i] );        /* 找到中位值最接近的点 */
//		}
//	}
//	#endif
//#endif
//#endif
//#else	
//	 /* 中位值计算 */
//	uBarArrMinLen = iGetHalfIntergeNumber(uBarArrMin);            /* 长度 */
//	uBarArrMaxLen = iGetHalfIntergeNumber(uBarArrMax);            /* 长度 */
//	memcpy( uBarArrMinTemp,uBarArrMin,sizeof(uBarArrMin) );
//	memcpy( uBarArrMaxTemp,uBarArrMax,sizeof(uBarArrMax) );
//	uMedianValue = uCalculateMedianValue( uBarArrMinTemp,uBarArrMinLen,uBarArrMaxTemp,uBarArrMaxLen );    /* 中位值计算 */	
//#endif

//#if VARIOUS_MEDIAN_DIT	
//	 /* 将波峰波谷按顺序合并 */ 
//	for( i=0;i<(sizeof(uArrCrest)/sizeof(uint16_t));i++ ){
//		if(0!=uArrCrest[i]){
//			uArrAndTrough[uj++] = uArrCrest[i];
//		}
//		if(0!=uArrTrough[i]){
//			uArrAndTrough[uj++] = uArrTrough[i];
//		}
//	}
//#else
//	 /* 将波峰波谷按顺序合并 */ 
//	for( i=0;i<(sizeof(uArrCrest)/sizeof(uint16_t));i++ ){
//		if(0!=uArrCrest[i]){
//			uArrAndTrough[uj++] = uArrCrest[i];
//		}
//		if(0!=uArrTrough[i]){
//			uArrAndTrough[uj++] = uArrTrough[i];
//		}
//	}
//#endif

///* 打印波峰和波谷合并的数据 */
//#if DEBUH_UART1	
//#if PRIVATE_UART1	
//	#if PRIVATE_SPCIAL_BAR_UART1
//	for( i=0;i<(sizeof(uArrAndTrough)/sizeof(uint16_t));i++ ){
//		if( 0!=uArrAndTrough[i] ){
//			myprintf( "uArrAndTrough %2d:%4d \r\n",i,uArrAndTrough[i] );       
//		}
//	}
//	#endif
//#endif
//#endif	
//	
//	/* 此处增加 */
//	/* 与中位值最接近的点 */	
//	uCrstAndTroghNum = iGetHalfIntergeNumber(uArrAndTrough);
//#if DEBUH_UART1	
//#if PRIVATE_UART1	
//	#if PRIVATE_SPCIAL_BAR_UART1
//	myprintf( "uCrstAndTroghNum:%4d \r\n",uCrstAndTroghNum );     
//	#endif
//#endif
//#endif
//	
//#if VARIOUS_MEDIAN_DIT
//	for( j=0;j<uCrstAndTroghNum-1;j++ ){   /* 需要保证最后两位都有数据 */
//		if( 0==j%2 ){
//			if( uBarArrMinMaxMedValue[uCountB]<=uBarArrMinMaxMedValue[uCountB+1] ){
//				uMedianValue = uBarArrMinMaxMedValue[uCountB];
//			}else{
//				uMedianValue = uBarArrMinMaxMedValue[uCountB+1];
//			}
//			uCountB += 2;
//		}else{
//			if( uBarArrMinMaxMedValue[uCountB]<=uBarArrMinMaxMedValue[uCountB+1] ){
//				uMedianValue = uBarArrMinMaxMedValue[uCountB+1];
//			}else{
//				uMedianValue = uBarArrMinMaxMedValue[uCountB];				
//			}
//			uCountB += 2;
//		}
//#if DEBUH_UART1	
//#if PRIVATE_UART1	
//	#if PRIVATE_SPCIAL_BAR_UART1
//		myprintf( "uMedianValue %4d \r\n",uMedianValue );        /* 找到中位值最接近的点 */
//	#endif
//#endif
//#endif		
//		/* 多个中位值情况 */
//		if( (0!=uArrAndTrough[j])&&(0!=uArrAndTrough[j+1])&&(0!=uMedianValue) ){			
//			for( i=uArrAndTrough[j];i>uArrAndTrough[j+1];i-- ){				
//				if( ((*(upArrData+i)-uMedianValue)>0)&&(*(upArrData+i)-uMedianValue)<BARCODE_FFFF ){
//					if( uExtent1NumTemp<sizeof(uBarArr1ExtentTemp) ){
//						uBarArr1ExtentTemp[uExtent1NumTemp++] = i;			
//					}
//				}
//			}
//			for( i=uArrAndTrough[j+1];i>uArrAndTrough[j+2];i-- ){
//				if( ((*(upArrData+i)-uMedianValue)>0)&&(*(upArrData+i)-uMedianValue)<BARCODE_FFFF ){
//					if( uExtent2NumTemp<sizeof(uBarArr2ExtentTemp) ){
//						uBarArr2ExtentTemp[uExtent2NumTemp++] = i;			
//					}
//				}
//			}
//		}	

//		if( 0==j%2 ){
//#if STORT_STL
//			qsort( uBarArr1ExtentTemp,uExtent1NumTemp,sizeof(uint16_t),cmpfuncint16min );
//			qsort( uBarArr2ExtentTemp,uExtent2NumTemp,sizeof(uint16_t),cmpfuncint16max );
//#else
//			InsertionSortUint16_t( (uint16_t *)uBarArr1ExtentTemp,(uExtent1NumTemp),SORT_MIN );
//			InsertionSortUint16_t( (uint16_t *)uBarArr2ExtentTemp,(uExtent2NumTemp),SORT_MAX );
//#endif
//		}else{
//#if STORT_STL
//			qsort( uBarArr1ExtentTemp,uExtent1NumTemp,sizeof(uint16_t),cmpfuncint16max );
//			qsort( uBarArr2ExtentTemp,uExtent2NumTemp,sizeof(uint16_t),cmpfuncint16min );
//#else
//			InsertionSortUint16_t( (uint16_t *)uBarArr1ExtentTemp,(uExtent1NumTemp),SORT_MAX );
//			InsertionSortUint16_t( (uint16_t *)uBarArr2ExtentTemp,(uExtent2NumTemp),SORT_MIN );
//#endif
//		}
//		
//#if DEBUH_UART1	
//#if PRIVATE_UART1	
//	#if PRIVATE_SPCIAL_BAR_UART1
//		myprintf( "uBarArrExtentTemp %2d: %4d %4d \r\n",j,uBarArr1ExtentTemp[0],uBarArr2ExtentTemp[0] );        /* 找到中位值最接近的点 */
//	#endif
//#endif
//#endif			
//		uExtent1NumTemp = 0;
//		if( 0!=uBarArr1ExtentTemp[0] ){
//			uBarArrExtent[uExtentNum++] = uBarArr1ExtentTemp[0];
//		}else{
//			return NULL;
//		}	
//		uExtent2NumTemp = 0;
//		if( 0!=uBarArr2ExtentTemp[0] ){
//			uBarArrExtent[uExtentNum++] = uBarArr2ExtentTemp[0];
//		}else{
//			return NULL;
//		}
//		memset( uBarArr1ExtentTemp,0,sizeof(uBarArr1ExtentTemp) );
//		memset( uBarArr2ExtentTemp,0,sizeof(uBarArr2ExtentTemp) );
//	}
//#else
//	for( j=0;j<uCrstAndTroghNum;j++){
//#if DEBUH_UART1	
//	#if PRIVATE_UART1	
//		#if PRIVATE_SPCIAL_BAR_UART1
//		myprintf( "uArrAndTrough:%4d %d uBarArrMedian:%d\r\n",uArrAndTrough[j],uArrAndTrough[j+1],uMedianValue );        /* 找到中位值最接近的点 */
//		#endif
//	#endif
//#endif
//		/* 单个中位值情况 */
//		if( (0!=uArrAndTrough[j])&&(0!=uMedianValue) ){
//			for( i=uArrAndTrough[j];i>uArrAndTrough[j+1];i-- ){				
//				if( ((*(upArrData+i)-uMedianValue)>0)&&(*(upArrData+i)-uMedianValue)<BARCODE_FFFF ){
//					if( uExtentNumTemp<sizeof(uBarArrExtentTemp) ){
//						uBarArrExtentTemp[uExtentNumTemp++] = i;			
//					}
//				}
//			}
//		}

//		if( 0==j%2 ){
//#if STORT_STL
//			qsort( uBarArrExtentTemp,uExtentNumTemp,sizeof(uint16_t),cmpfuncint16min );
//#else
//			InsertionSortUint16_t( (uint16_t *)uBarArrExtentTemp,(uExtentNumTemp),SORT_MIN );
//#endif
//		}else{
//#if STORT_STL
//			qsort( uBarArrExtentTemp,uExtentNumTemp,sizeof(uint16_t),cmpfuncint16max );
//#else
//			InsertionSortUint16_t( (uint16_t *)uBarArrExtentTemp,(uExtentNumTemp),SORT_MAX );
//#endif
//		}
//		
//		uExtentNumTemp = 0;
//		if( 0!=uBarArrExtentTemp[0] ){
//			uBarArrExtent[uExtentNum++] = uBarArrExtentTemp[0];
//		}else{
//			return NULL;
//		}		
//		memset( uBarArrExtentTemp,0,sizeof(uBarArrExtentTemp) );
//	}
//#endif
//	
//#if DEBUH_UART1	
//	#if PRIVATE_UART1
//	#if PRIVATE_SPCIAL_BAR_UART1
//	for( i=0;i<(sizeof(uBarArrExtent)/sizeof(uint16_t));i++ ){
//		if(0!=uBarArrExtent[i]){
//			myprintf( "uBarArrExtent:%4d \r\n",uBarArrExtent[i] );
//		}
//	}
//	#endif
//	#endif
//#endif
//	
//#if VARIOUS_MEDIAN_DIT
//	/* 寻找所有交点的中位值 */
//	for( i=0;i<(sizeof(uBarArrExtent)/sizeof(uint16_t));i+=2 ){
//		if( (0!=uBarArrExtent[i])&&(0!=uBarArrExtent[i+1]) ){
//			uBarArrExtentMedian[uCountC++] = ((uBarArrExtent[i]+uBarArrExtent[i+1])/2);
//#if DEBUH_UART1	
//	#if PRIVATE_UART1
//	#if PRIVATE_SPCIAL_BAR_UART1
//			myprintf( "uBarArrExtentMedian:%4d \r\n",uBarArrExtentMedian[uCountC-1] );
//	#endif
//	#endif
//#endif
//		}
//	}
//#else
//	/* 寻找所有交点的中位值 */
//	for( i=0;i<(sizeof(uBarArrExtent)/sizeof(uint16_t));i++ ){
//		if( (0!=uBarArrExtent[i])&&(0!=uBarArrExtent[i+1]) ){
//			uBarArrExtentMedian[i] = ((uBarArrExtent[i]+uBarArrExtent[i+1])/2);
//#if DEBUH_UART1	
//	#if PRIVATE_UART1
//	#if PRIVATE_SPCIAL_BAR_UART1
//			myprintf( "uBarArrExtentMedian:%4d \r\n",uBarArrExtentMedian[i] );
//	#endif
//	#endif
//#endif
//		}
//	}
//#endif
//	
//	/* 每个中位值的差值点 */
//	for( i=0;i<(sizeof(uBarArrExtentMedian)/sizeof(uint16_t));i++ ){
//		if( (0!=uBarArrExtentMedian[i])&&(0!=uBarArrExtentMedian[i+1]) ){
//			uBarArrExtentDifference[i] = uBarArrExtentMedian[i]-uBarArrExtentMedian[i+1];
//#if DEBUH_UART1	
//	#if PRIVATE_UART1
//	#if PRIVATE_SPCIAL_BAR_UART1
//			myprintf( "uBarArrExtentDifference:%4d \r\n",uBarArrExtentDifference[i] );
//	#endif
//	#endif
//#endif
//		}
//	}
//	
//	/* 计算点数值 */
//	fRecDitNum = 0.5;
//	for( i=0;i<(sizeof(uBarArrExtentDifference)/sizeof(uint16_t));i++ ){
//		if( (0!=uBarArrExtentDifference[i]) ){			
//			fRecDitRealNum = uEstimateHalfTheRange( uBarArrExtentDifference[i] );                       /* 寻找到有多少个点 */
//			uRecDitNum = (fRecDitRealNum - fRecDitNum)*2;                                               /* 得到当前的点数 */
//#if DEBUH_UART1	
//	#if PRIVATE_UART1
//		#if PRIVATE_SPCIAL_BAR_UART1
//			myprintf( "uBarArrExtentDifference%2d: %4d %2.2f %2.2f %2.2f %2.2f %4d \r\n",i,uBarArrExtentDifference[i],fRecDitRealNum,fRecDitNum,(fRecDitRealNum - fRecDitNum),(fRecDitRealNum - fRecDitNum)*2,uRecDitNum );
//		#endif
//	#else
//		myprintf( "uBarArrExtentDifference%2d: %4d %2.2f %2.2f %2.2f %2.2f %4d \r\n",i,uBarArrExtentDifference[i],fRecDitRealNum,fRecDitNum,(fRecDitRealNum - fRecDitNum),(fRecDitRealNum - fRecDitNum)*2,uRecDitNum );	
//	#endif
//#endif			
//			fRecDitNum = (fRecDitRealNum - fRecDitNum);		                                            /* 保留上一个点的数据 */
//			if( fRecDitNum<=0 ){
//#if DEBUH_UART1	
//				myprintf( "The critical value: %4d %4d %4d \r\n",uBarArrExtentDifference[i-1],uBarArrExtentDifference[i],uBarArrExtentDifference[i+1] );   /* 将临界值打印出来 */
//#endif	
//				return NULL;
//			}
//			uCrstAndTroghMedianNum = strlen((const char *)uBarBinValue);
//			if( (uCrstAndTroghMedianNum+uRecDitNum)<sizeof(uBarBinValue) ){
//				uEstimateTheDitNum( (uint8_t *)(uBarBinValue+uCrstAndTroghMedianNum),uRecDitNum,i );		/* 将当前的点数存储到数组 */
//			}else{
//#if DEBUH_UART1	
//				myprintf( "uBarBinValue Overflow \r\n" );   /* 将临界值打印出来 */
//#endif	
//			}				
//		}
//	}

//	/* 将起转换为0 1 数值 */
//	for( i=0;i<(sizeof(uBarBinValue)/sizeof(uint8_t));i++ ){	
//		if( 50==uBarBinValue[i] ){
//			uBarBinValueTemp[i] = 0;
//		}else if( 49==uBarBinValue[i] ){
//			uBarBinValueTemp[i] = 1;
//		}	
//	}
//	/* 打印条码二进制数据 */
//#if DEBUH_UART1	
//	#if PRIVATE_UART1
//	myprintf( "uBarBinValueTemp:\r\n" ); 
//	//for( i=0;i<(sizeof(uBarBinValueTemp)/sizeof(uint8_t));i++ ){
//	for( i=0;i<(BARCODE_DIT_NUMBER);i++ ){
//		myprintf( "%1d",uBarBinValueTemp[i] );
//	}
//	myprintf( "\r\n" ); 
//	#endif
//#endif
//	
//	/* 得出条码值 */
//	for( i=0;i<4;i++ ){
//		uBarExtentValue[i] = (uBarBinValueTemp[(i*4)+0]<<3)|(uBarBinValueTemp[(i*4)+1]<<2)|(uBarBinValueTemp[(i*4)+2]<<1)|(uBarBinValueTemp[(i*4)+3]<<0);
//	}
//	if( 0==uBarBinValueTemp[16] )	{
//		uBarExtentValue[4] = 0;
//	}else{
//		uBarExtentValue[4] = 8;
//	}
//	
//	memcpy( (char *)upArrBar,(const char *)uBarExtentValue,sizeof(uBarExtentValue) );
//#if DEBUH_UART1	
//	#if PRIVATE_UART1
//	myprintf( "uBarExtentValue: " );
//	for( i=0;i<(sizeof(uBarExtentValue));i++ ){
//		myprintf( "%2x ",uBarExtentValue[i] );
//	}
//	myprintf( "\r\n");
//	#endif
//#endif
//	/* 此处增加 */
//	
//	return upArrBar;
//}



