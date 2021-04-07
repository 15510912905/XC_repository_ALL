#ifndef _FUNC_ADHANDLER_H_
#define _FUNC_ADHANDLER_H_

#include "Drv_AD7685.h"
#include "Func_IFP_300_Drv.h"
#include "math.h"
#include "stdlib.h"
#include "stdio.h"
#include "Func_MA1100_User_Interface.h"
#include "Func_GY_K950E.h"

#if CONFIG_DIT_SCAN
	#define SCAN_LENGTH                  (312)//(274)//(312)//(455)//
	#define BARVODE_LENGTH               (500)//(500)//(512)//(512)
	#define ADJUST_DOT                   (-107)//(-69)//(-107)//(-262)//    //不能小于-312
	#define MOTOR_PULSE                  (14)//(31)(36)//    /* 与扫描条码精度有关 */
#else
	#define SCAN_LENGTH                  (274)//(312)//(274)//(312)//(455)//
	#define BARVODE_LENGTH               (438)//(500)//(500)//(512)//(512)
	#define ADJUST_DOT                   (-91)//(-107)//(-69)//(-107)//(-262)//    //不能小于-312
	#define MOTOR_PULSE                  (16)//(14)//(31)(36)//    /* 与扫描条码精度有关 */
#endif

#define MOTOR_U_SECURITY_STEP  			 (10*MOTOR_PULSE)

#define MOTOR_MAX_STEP               (0xFFFFFFFE)
#define MOTOR_RESET_TIME             (4000)
#define MOTOR_PULSE_TEST             (32)//

#define MOTOR_STEP_NUMBER            (SCAN_LENGTH+BARVODE_LENGTH+ADJUST_DOT+1)//(SCAN_LENGTH)   
#define EXCURSION_LENGTH             (MOTOR_STEP_NUMBER-BARVODE_LENGTH-1)//(596)//(384)//20
#define SCAN_BAR_NUMBER              (255)

#define MOTOR_STEP_RESERVE           (1000)

#define MOTOR_FREQUENCY              (1000)//(1000)//(2000)//(1000)    //越小越快
#define PULSE_TIME_BASE              (4000000)
#define NUMBER_PULSE_BASE            ((MOTOR_FREQUENCY*1000000)/PULSE_TIME_BASE)
#define MOTOR_DELAY                  (((NUMBER_PULSE_BASE*MOTOR_PULSE)/1000)+1)       /*(((NUMBER_PULSE_BASE*MOTOR_PULSE)/1000)+1) ((NUMBER_PULSE_BASE*MOTOR_PULSE)/1000) */
#define MOTOR_TIME_SLICE             (5)
#define MOTOR_TIMEOUT                (12000)

#define BAR_START_ADDR               (233)//(240)
#define BAR_BASE_START_ADDR          (399)//(430) /* //不能随意改动  17位为400 20位445*/
#define BAR_BASE_ADDR                (22.5)//(22.5)//(22)//(8)
#define BAR_BASE_BLACK_ADDR          (21)//(23)
#define BAR_BASE_WHITE_ADDR          (23)//(21)
#define BAR_SBASE_ADDR               ((unsigned char)28)//((unsigned char)BAR_BASE_ADDR/2)

#define BAR_COEFF_THRESHOLD          (0.5)//(0.8)//(0.7)
#define BAR_THRESHOLD                (3700)//(3500) 
#define BAR_BIT_NUMBER               (17) 
#define BAR_BIT_Eff_NUMBER           (16) 
#define BAR_START_THRESHOLD          (5)//(10)//(8)//(10)//(20)
#define BAR_SPECIAL_THRESHOLD        (150)

#define BAR_AVERAGE_NUM              (7)
#define BAR_AVE_NUM                  (4)

#define LINE_METHOD                  (0xfe)
#define ID_LINE_METHOD               (0)
#define FOUR_ARGUMENT                (2)
#define SPLINE                       (3)

#define D_VALUE_INTERVAL             (500)
#define CONTINUOUS_NUM               (5)

#define AVERAGE_MIN                  (1)
#define AVERAGE_MAX                  (0)

#define AD_COLLECT_TIMES             (8)
#define AD_COLLECT_MAX               (65536)
#define AD_VALUE_MAX                 (AD_COLLECT_TIMES*AD_COLLECT_MAX)

#define BAR_COLLECT_TIMES            (4)
#define BAR_COLLECT_MAX              (4096)
#define BAR_VALUE_MAX                (AD_COLLECT_TIMES*AD_COLLECT_MAX)

#define EN_REVERSE_INT_ARR           (0)

#define SORT_MAX                     (1)
#define SORT_MIN                     (0)

#define BAR_REF_DIT                  (435)

#define APPROXIMATION                (100)
#define ADC_CRITICAL 				 (260)

#pragma pack(8)	/*按1字节对齐*/
typedef struct{	
	float result1;
	float result2;
	float result3;
	float result4;	
}ALGORITHM_DATA_TYPE;

typedef struct{
	float a;
	float b;
	float c;
	
}LINE_QUATION;

extern uint32_t g_ADC_Buffer[SCAN_LENGTH];
extern uint16_t g_ADC_BarCode[BARVODE_LENGTH];
extern uint16_t AD_Num;
extern ALGORITHM_DATA_TYPE g_stuMyAlgorithm;

uint8_t uTestInformationRef( void );
uint8_t uTestInformationPrompt( void );
uint32_t* readAD( uint32_t* puArr );
uint8_t uTestInformation( void );
uint8_t uTestInformationRefresh( void );
uint8_t AcquisitionSystem( void );
uint8_t uAcquisitionSystem( uint8_t uStandardQuist );
uint8_t AcquisitionQuickSystem( uint8_t uStandardQuist,uint8_t uDebug ) ;
uint8_t uCollectFluorescenceValueBarValue( uint32_t* puArrTemp,uint16_t* puArrBarCode );

void line_smoth_slid( uint32_t* pOneBuffer,uint16_t len );
uint8_t uReverseIntArr( uint32_t* pTempArr,int32_t uLength );
uint8_t uVerifyId( ID_Info *pAraParam );
uint8_t uVerifyIdChildren( UINTE_DATA_TYPE *pChildrenParam );
uint8_t LineMethod( UINTE_DATA_TYPE* pstuAlg,ALGORITHM_DATA_TYPE* pAra,float fTC,uint8_t uChildrenNum ); 
uint8_t Result_Calculate( uint32_t* pOneBuffer,ID_Info* pIdAra,ALGORITHM_DATA_TYPE* pAra,uint8_t uIdCardNum );
uint8_t CalculateWave( ID_Info* pstuAlg,uint32_t* uArr ,uint16_t uSize );

LINE_QUATION* SolveLineearEquation( float x1,float y1,float x2,float y2,LINE_QUATION* stuLinEquation );
uint8_t TC_Calculate(uint32_t* pOneBuffer, uint16_t T_s, uint16_t T_e, uint16_t C_s, uint16_t C_e, uint8_t peakT_sample,uint8_t peakC_sample,float* fpCalPes);

uint32_t Average(uint32_t *Buffer, uint16_t len, uint8_t num,uint8_t uMinMax );
int cmpfuncintmax(const void * a, const void * b);
int cmpfuncintmin(const void * a, const void * b);
int cmpfuncint16max(const void * a, const void * b);
int cmpfuncint16min(const void * a, const void * b);
void InsertionSortUint32_t(uint32_t arr[], uint32_t len,uint8_t uMaxMin);
void InsertionSortUint16_t(uint16_t arr[], uint16_t len,uint8_t uMaxMin);
uint8_t uCalculateCE( UINTE_DATA_TYPE* stuIdInfo,uint8_t* upRecRel );
uint8_t uCalculatePesponse( uint32_t* pOneBuffer,ID_Info* pstuIdInfo,uint8_t uRecRel,float* fpCalPes );
float fChildrenCoefficient( UINTE_DATA_TYPE* pstuIdInfo,float fPesponse );
uint8_t uDisplayDensity( ID_Info* pIDData,UINTE_DATA_TYPE* pstuIdInfo,ALGORITHM_DATA_TYPE* pAra,uint8_t uChildrenNum,USER_REFERRENCE* puRefTemp );
uint8_t uChildrenReferenceStorage( char *pStrff,float fDensity,uint8_t uChildren,USER_REFERRENCE* puRefTemp );
uint8_t uCirculateStorage( ID_Info* pIDData,UINTE_DATA_TYPE* pstuIdInfo,uint8_t* pfDensity,uint8_t uChildrenNum );
uint8_t uCalculateDensity( UINTE_DATA_TYPE* pstuIdInfo,ALGORITHM_DATA_TYPE* pstuAlg,float fPesponse,uint8_t uChildrenNum );
uint8_t pstuAlforithmFourArgument( UINTE_DATA_TYPE* pstuIdInfo,ALGORITHM_DATA_TYPE* pstuAlg,float fPesponse,uint8_t uChildrenNum );
uint8_t pstuAlforithmLineMethod( UINTE_DATA_TYPE* pstuIdInfo,ALGORITHM_DATA_TYPE* pstuAlg,float fPesponse,uint8_t uChildrenNum );
uint8_t pstuAlforithmSpline( UINTE_DATA_TYPE* pstuIdInfo,ALGORITHM_DATA_TYPE* pstuAlg,float fPesponse,uint8_t uChildrenNum );
uint8_t pstuAlforithmResult( ALGORITHM_DATA_TYPE* pstuAlg,uint8_t uChildrenNum,float fVaule );

uint8_t uClearItemData( void );
uint8_t uAutoQuckTest( void );
float fUseRandCondition( uint8_t* upCondStr,float fTempData );
uint8_t uForceAssociateDensity( void );
uint8_t uGetFluorescenceBarValue( void );
uint8_t uGetFluoerscenceMaxValue( const uint32_t* puArrTemp,int len,int16_t* piFluoerMaxIndex,uint32_t* puFluoerMax );
uint8_t uChildrenReferenceAnalyse( char *pStrff,float fDensity,float fLimitsMin,float fLimitsMax );
uint8_t uTheCalibrationCurve( uint32_t* pBuffer,uint32_t uSize );

void InsertionSortDouble(double arr[], uint32_t len,uint8_t uMaxMin);
int cmpfuncintdoublemax(const void * a, const void * b);
int cmpfuncintdoublemin(const void * a, const void * b);
float uSolveLineearY( float fX,LINE_QUATION* stuLinEquation );
float uSolveLineearX( float fY,LINE_QUATION* stuLinEquation );
//ALGORITHM_DATA_TYPE* InitAlforithmData( ALGORITHM_DATA_TYPE* stuIdInfo );

#endif
