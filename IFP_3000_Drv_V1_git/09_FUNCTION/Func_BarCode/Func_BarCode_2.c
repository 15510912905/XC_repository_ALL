#include "Func_BarCode_2.h"

/*  */
uint8_t* uWaveCrestTroughFirstDerivative( const uint16_t* upArrData,uint8_t* upArrBar,int len )
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

uint8_t uLinearSmooth( const uint16_t* in, int32_t N )
{
	uint16_t i = 0;
	uint16_t* out[2] = {0};
	
	out[0] = (uint16_t *)calloc( BARVODE_LENGTH,sizeof(uint16_t) );
	out[1] = (uint16_t *)calloc( BARVODE_LENGTH,sizeof(uint16_t) );
	if( (NULL==out[0])||(NULL==out[1]) ){
		if( NULL!=out[0] ){
			free( out[0] );
		}
		if( NULL!=out[1] ){
			free( out[1] );
		}	
		return NULL;
	}
	
	uLinearSmooth7( in,out[0],N );	
	uQuadraticSmooth7( out[0],out[1],N );
	uCubicSmooth7( out[1],out[0],N );
	
#if DEBUH_UART1	
	#if PRIVATE_BAR_UART1
		myprintf( "uLinearSmooth:\r\n" );		
		for( i=0;i<(N);i++){
			printf( "%8d \r\n",out[0][i] );  				//myprintf( "O-%4d:%8d \r\n",i,g_ADC_BarCode[i] );
		}
		myprintf( "\r\n" );
	#endif
#endif	
	
	if( NULL!=out[0] ){
		free( out[0] );
	}
	if( NULL!=out[1] ){
		free( out[1] );
	}
	
	return EXE_SUCCEED;
}

uint8_t uLinearSmooth7 ( const uint16_t* in, uint16_t* out, int32_t N )
{
    int i;
    if ( N < 7 )
    {
        for ( i = 0; i <= N - 1; i++ )
        {
            out[i] = in[i];
        }
    }
    else
    {
        out[0] = ( 13.0 * in[0] + 10.0 * in[1] + 7.0 * in[2] + 4.0 * in[3] +
                  in[4] - 2.0 * in[5] - 5.0 * in[6] ) / 28.0;

        out[1] = ( 5.0 * in[0] + 4.0 * in[1] + 3 * in[2] + 2 * in[3] +
                  in[4] - in[6] ) / 14.0;

        out[2] = ( 7.0 * in[0] + 6.0 * in [1] + 5.0 * in[2] + 4.0 * in[3] +
                  3.0 * in[4] + 2.0 * in[5] + in[6] ) / 28.0;

        for ( i = 3; i <= N - 4; i++ )
        {
            out[i] = ( in[i - 3] + in[i - 2] + in[i - 1] + in[i] + in[i + 1] + in[i + 2] + in[i + 3] ) / 7.0;
        }

        out[N - 3] = ( 7.0 * in[N - 1] + 6.0 * in [N - 2] + 5.0 * in[N - 3] +
                      4.0 * in[N - 4] + 3.0 * in[N - 5] + 2.0 * in[N - 6] + in[N - 7] ) / 28.0;

        out[N - 2] = ( 5.0 * in[N - 1] + 4.0 * in[N - 2] + 3.0 * in[N - 3] +
                      2.0 * in[N - 4] + in[N - 5] - in[N - 7] ) / 14.0;

        out[N - 1] = ( 13.0 * in[N - 1] + 10.0 * in[N - 2] + 7.0 * in[N - 3] +
                      4 * in[N - 4] + in[N - 5] - 2 * in[N - 6] - 5 * in[N - 7] ) / 28.0;
    }
	
	return EXE_SUCCEED;
}

uint8_t uQuadraticSmooth7( const uint16_t* in, uint16_t* out, int32_t N )
{
    int i;
    if ( N < 7 )
    {
        for ( i = 0; i <= N - 1; i++ )
        {
            out[i] = in[i];
        }
    }
    else
    {
        out[0] = ( 32.0 * in[0] + 15.0 * in[1] + 3.0 * in[2] - 4.0 * in[3] -
                  6.0 * in[4] - 3.0 * in[5] + 5.0 * in[6] ) / 42.0;

        out[1] = ( 5.0 * in[0] + 4.0 * in[1] + 3.0 * in[2] + 2.0 * in[3] +
                  in[4] - in[6] ) / 14.0;

        out[2] = ( 1.0 * in[0] + 3.0 * in [1] + 4.0 * in[2] + 4.0 * in[3] +
                  3.0 * in[4] + 1.0 * in[5] - 2.0 * in[6] ) / 14.0;
        for ( i = 3; i <= N - 4; i++ )
        {
            out[i] = ( -2.0 * (in[i - 3] + in[i + 3]) +
                       3.0 * (in[i - 2] + in[i + 2]) +
                      6.0 * (in[i - 1] + in[i + 1]) + 7.0 * in[i] ) / 21.0;
        }
        out[N - 3] = ( 1.0 * in[N - 1] + 3.0 * in [N - 2] + 4.0 * in[N - 3] +
                      4.0 * in[N - 4] + 3.0 * in[N - 5] + 1.0 * in[N - 6] - 2.0 * in[N - 7] ) / 14.0;

        out[N - 2] = ( 5.0 * in[N - 1] + 4.0 * in[N - 2] + 3.0 * in[N - 3] +
                      2.0 * in[N - 4] + in[N - 5] - in[N - 7] ) / 14.0;

        out[N - 1] = ( 32.0 * in[N - 1] + 15.0 * in[N - 2] + 3.0 * in[N - 3] -
                      4.0 * in[N - 4] - 6.0 * in[N - 5] - 3.0 * in[N - 6] + 5.0 * in[N - 7] ) / 42.0;
    }
	
	return EXE_SUCCEED;
}

uint8_t uCubicSmooth7( const uint16_t* in, uint16_t* out, int32_t N )
{
    int i;
    if ( N < 7 )
    {
        for ( i = 0; i <= N - 1; i++ )
        {
            out[i] = in[i];
        }
    }
    else
    {
        out[0] = ( 39.0 * in[0] + 8.0 * in[1] - 4.0 * in[2] - 4.0 * in[3] +
                  1.0 * in[4] + 4.0 * in[5] - 2.0 * in[6] ) / 42.0;
        out[1] = ( 8.0 * in[0] + 19.0 * in[1] + 16.0 * in[2] + 6.0 * in[3] -
                  4.0 * in[4] - 7.0* in[5] + 4.0 * in[6] ) / 42.0;
        out[2] = ( -4.0 * in[0] + 16.0 * in [1] + 19.0 * in[2] + 12.0 * in[3] +
                  2.0 * in[4] - 4.0 * in[5] + 1.0 * in[6] ) / 42.0;
        for ( i = 3; i <= N - 4; i++ )
        {
            out[i] = ( -2.0 * (in[i - 3] + in[i + 3]) +
                       3.0 * (in[i - 2] + in[i + 2]) +
                      6.0 * (in[i - 1] + in[i + 1]) + 7.0 * in[i] ) / 21.0;
        }
        out[N - 3] = ( -4.0 * in[N - 1] + 16.0 * in [N - 2] + 19.0 * in[N - 3] +
                      12.0 * in[N - 4] + 2.0 * in[N - 5] - 4.0 * in[N - 6] + 1.0 * in[N - 7] ) / 42.0;
        out[N - 2] = ( 8.0 * in[N - 1] + 19.0 * in[N - 2] + 16.0 * in[N - 3] +
                      6.0 * in[N - 4] - 4.0 * in[N - 5] - 7.0 * in[N - 6] + 4.0 * in[N - 7] ) / 42.0;
        out[N - 1] = ( 39.0 * in[N - 1] + 8.0 * in[N - 2] - 4.0 * in[N - 3] -
                      4.0 * in[N - 4] + 1.0 * in[N - 5] + 4.0 * in[N - 6] - 2.0 * in[N - 7] ) / 42.0;
    }
	
	return EXE_SUCCEED;
}


//void linearSmooth7 ( double in[], double out[], int N )
//{
//    int i;
//    if ( N < 7 )
//    {
//        for ( i = 0; i <= N - 1; i++ )
//        {
//            out[i] = in[i];
//        }
//    }
//    else
//    {
//        out[0] = ( 13.0 * in[0] + 10.0 * in[1] + 7.0 * in[2] + 4.0 * in[3] +
//                  in[4] - 2.0 * in[5] - 5.0 * in[6] ) / 28.0;

//        out[1] = ( 5.0 * in[0] + 4.0 * in[1] + 3 * in[2] + 2 * in[3] +
//                  in[4] - in[6] ) / 14.0;

//        out[2] = ( 7.0 * in[0] + 6.0 * in [1] + 5.0 * in[2] + 4.0 * in[3] +
//                  3.0 * in[4] + 2.0 * in[5] + in[6] ) / 28.0;

//        for ( i = 3; i <= N - 4; i++ )
//        {
//            out[i] = ( in[i - 3] + in[i - 2] + in[i - 1] + in[i] + in[i + 1] + in[i + 2] + in[i + 3] ) / 7.0;
//        }

//        out[N - 3] = ( 7.0 * in[N - 1] + 6.0 * in [N - 2] + 5.0 * in[N - 3] +
//                      4.0 * in[N - 4] + 3.0 * in[N - 5] + 2.0 * in[N - 6] + in[N - 7] ) / 28.0;

//        out[N - 2] = ( 5.0 * in[N - 1] + 4.0 * in[N - 2] + 3.0 * in[N - 3] +
//                      2.0 * in[N - 4] + in[N - 5] - in[N - 7] ) / 14.0;

//        out[N - 1] = ( 13.0 * in[N - 1] + 10.0 * in[N - 2] + 7.0 * in[N - 3] +
//                      4 * in[N - 4] + in[N - 5] - 2 * in[N - 6] - 5 * in[N - 7] ) / 28.0;
//    }
//}

//void quadraticSmooth7(double in[], double out[], int N)
//{
//    int i;
//    if ( N < 7 )
//    {
//        for ( i = 0; i <= N - 1; i++ )
//        {
//            out[i] = in[i];
//        }
//    }
//    else
//    {
//        out[0] = ( 32.0 * in[0] + 15.0 * in[1] + 3.0 * in[2] - 4.0 * in[3] -
//                  6.0 * in[4] - 3.0 * in[5] + 5.0 * in[6] ) / 42.0;

//        out[1] = ( 5.0 * in[0] + 4.0 * in[1] + 3.0 * in[2] + 2.0 * in[3] +
//                  in[4] - in[6] ) / 14.0;

//        out[2] = ( 1.0 * in[0] + 3.0 * in [1] + 4.0 * in[2] + 4.0 * in[3] +
//                  3.0 * in[4] + 1.0 * in[5] - 2.0 * in[6] ) / 14.0;
//        for ( i = 3; i <= N - 4; i++ )
//        {
//            out[i] = ( -2.0 * (in[i - 3] + in[i + 3]) +
//                       3.0 * (in[i - 2] + in[i + 2]) +
//                      6.0 * (in[i - 1] + in[i + 1]) + 7.0 * in[i] ) / 21.0;
//        }
//        out[N - 3] = ( 1.0 * in[N - 1] + 3.0 * in [N - 2] + 4.0 * in[N - 3] +
//                      4.0 * in[N - 4] + 3.0 * in[N - 5] + 1.0 * in[N - 6] - 2.0 * in[N - 7] ) / 14.0;

//        out[N - 2] = ( 5.0 * in[N - 1] + 4.0 * in[N - 2] + 3.0 * in[N - 3] +
//                      2.0 * in[N - 4] + in[N - 5] - in[N - 7] ) / 14.0;

//        out[N - 1] = ( 32.0 * in[N - 1] + 15.0 * in[N - 2] + 3.0 * in[N - 3] -
//                      4.0 * in[N - 4] - 6.0 * in[N - 5] - 3.0 * in[N - 6] + 5.0 * in[N - 7] ) / 42.0;
//    }
//}

//void cubicSmooth7(double in[], double out[], int N)
//{
//    int i;
//    if ( N < 7 )
//    {
//        for ( i = 0; i <= N - 1; i++ )
//        {
//            out[i] = in[i];
//        }
//    }
//    else
//    {
//        out[0] = ( 39.0 * in[0] + 8.0 * in[1] - 4.0 * in[2] - 4.0 * in[3] +
//                  1.0 * in[4] + 4.0 * in[5] - 2.0 * in[6] ) / 42.0;
//        out[1] = ( 8.0 * in[0] + 19.0 * in[1] + 16.0 * in[2] + 6.0 * in[3] -
//                  4.0 * in[4] - 7.0* in[5] + 4.0 * in[6] ) / 42.0;
//        out[2] = ( -4.0 * in[0] + 16.0 * in [1] + 19.0 * in[2] + 12.0 * in[3] +
//                  2.0 * in[4] - 4.0 * in[5] + 1.0 * in[6] ) / 42.0;
//        for ( i = 3; i <= N - 4; i++ )
//        {
//            out[i] = ( -2.0 * (in[i - 3] + in[i + 3]) +
//                       3.0 * (in[i - 2] + in[i + 2]) +
//                      6.0 * (in[i - 1] + in[i + 1]) + 7.0 * in[i] ) / 21.0;
//        }
//        out[N - 3] = ( -4.0 * in[N - 1] + 16.0 * in [N - 2] + 19.0 * in[N - 3] +
//                      12.0 * in[N - 4] + 2.0 * in[N - 5] - 4.0 * in[N - 6] + 1.0 * in[N - 7] ) / 42.0;
//        out[N - 2] = ( 8.0 * in[N - 1] + 19.0 * in[N - 2] + 16.0 * in[N - 3] +
//                      6.0 * in[N - 4] - 4.0 * in[N - 5] - 7.0 * in[N - 6] + 4.0 * in[N - 7] ) / 42.0;
//        out[N - 1] = ( 39.0 * in[N - 1] + 8.0 * in[N - 2] - 4.0 * in[N - 3] -
//                      4.0 * in[N - 4] + 1.0 * in[N - 5] + 4.0 * in[N - 6] - 2.0 * in[N - 7] ) / 42.0;
//    }
//}


