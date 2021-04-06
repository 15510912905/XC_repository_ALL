#ifndef _FUNC_BARCODE_H_
#define _FUNC_BARCODE_H_

#include "Func_IFP_300_Drv.h"
#include "Func_ADHandler.h"
#include "Global_Variable.h"

#pragma pack(1)	/*按1字节对齐*/

#if CONFIG_DIT_SCAN
	/* 0/1 对应500点数时 */   
	#define F_BAR_1_00_RANG      (0)//(0)
	#define F_BAR_1_01_RANG      (17)//(35)
	#define F_BAR_1_02_RANG      (12)//(17)//(30)
	#define F_BAR_1_03_RANG      (28)//(180)
	#define F_BAR_1_04_RANG      (39)//(55)

	#define F_BAR_1_05_RANG      (51)//(78)
	#define F_BAR_1_06_RANG      (62)//(90)
	#define F_BAR_1_07_RANG      (73)//(110)
	#define F_BAR_1_08_RANG      (84)//(140)

	#define F_BAR_1_09_RANG      (96)//(160)
	#define F_BAR_1_10_RANG      (107)//(200)
	#define F_BAR_1_11_RANG      (118)//(220)
	#define F_BAR_1_12_RANG      (129)//(258)
									  //
	#define F_BAR_1_13_RANG      (141)//(278)
	#define F_BAR_1_14_RANG      (152)//(300)
	#define F_BAR_1_15_RANG      (163)//(320)
	#define F_BAR_1_16_RANG      (174)//(350)
									  //
	#define F_BAR_1_17_RANG      (186)//(370)
	#define F_BAR_1_18_RANG      (197)//(390)
	#define F_BAR_1_19_RANG      (208)//(0)
	#define F_BAR_1_20_RANG      (219)//(35)

	#define F_BAR_1_21_RANG      (231)//(30)
	#define F_BAR_1_22_RANG      (264)//(55)
	#define F_BAR_1_23_RANG      (276)//(78)
	#define F_BAR_1_24_RANG      (287)//(90)

	#define F_BAR_1_25_RANG      (298)//(110)
	#define F_BAR_1_26_RANG      (309)//(140)
	#define F_BAR_1_27_RANG      (321)//(160)                                 
	#define F_BAR_1_28_RANG      (332)//(180)

	#define F_BAR_1_29_RANG      (343)//(200)
	#define F_BAR_1_30_RANG      (354)//(220)
	#define F_BAR_1_31_RANG      (366)//(258)
	#define F_BAR_1_32_RANG      (377)//(278)

	#define F_BAR_1_33_RANG      (388)//(300)
	#define F_BAR_1_34_RANG      (399)//(320)
	#define F_BAR_1_35_RANG      (411)//(350)
	#define F_BAR_1_36_RANG      (422)//(370)
#else
	/* 0/1 对应438点数时 */   
	#define F_BAR_1_00_RANG      (0)//(0)
	#define F_BAR_1_01_RANG      (15)//(35)
	#define F_BAR_1_02_RANG      (10)//(17)//(30)
	#define F_BAR_1_03_RANG      (25)//(180)
	#define F_BAR_1_04_RANG      (35)//(55)

	#define F_BAR_1_05_RANG      (44)//(78)
	#define F_BAR_1_06_RANG      (54)//(90)
	#define F_BAR_1_07_RANG      (64)//(110)
	#define F_BAR_1_08_RANG      (74)//(140)

	#define F_BAR_1_09_RANG      (84)//(160)
	#define F_BAR_1_10_RANG      (94)//(200)
	#define F_BAR_1_11_RANG      (103)//(220)
	#define F_BAR_1_12_RANG      (113)//(258)
									  //
	#define F_BAR_1_13_RANG      (123)//(278)
	#define F_BAR_1_14_RANG      (133)//(300)
	#define F_BAR_1_15_RANG      (143)//(320)
	#define F_BAR_1_16_RANG      (153)//(350)
									  //
	#define F_BAR_1_17_RANG      (162)//(370)
	#define F_BAR_1_18_RANG      (172)//(390)
	#define F_BAR_1_19_RANG      (182)//(0)
	#define F_BAR_1_20_RANG      (192)//(35)

	#define F_BAR_1_21_RANG      (202)//(30)
	#define F_BAR_1_22_RANG      (212)//(55)
	#define F_BAR_1_23_RANG      (222)//(78)
	#define F_BAR_1_24_RANG      (231)//(90)

	#define F_BAR_1_25_RANG      (241)//(110)
	#define F_BAR_1_26_RANG      (251)//(140)
	#define F_BAR_1_27_RANG      (261)//(160)                                 
	#define F_BAR_1_28_RANG      (271)//(180)

	#define F_BAR_1_29_RANG      (281)//(200)
	#define F_BAR_1_30_RANG      (291)//(220)
	#define F_BAR_1_31_RANG      (300)//(258)
	#define F_BAR_1_32_RANG      (310)//(278)

	#define F_BAR_1_33_RANG      (320)//(300)
	#define F_BAR_1_34_RANG      (330)//(320)
	#define F_BAR_1_35_RANG      (340)//(350)
	#define F_BAR_1_36_RANG      (350)//(370)
#endif

/* 0 */
#define BAR_0_00_RANG        (0)//(0)
#define BAR_0_01_RANG        (34)//(35)
#define BAR_0_02_RANG        (34)//(30)
#define BAR_0_03_RANG        (56)//(55)
#define BAR_0_04_RANG        (79)//(78)
                             //
#define BAR_0_05_RANG        (101)//(90)
#define BAR_0_06_RANG        (124)//(110)
#define BAR_0_07_RANG        (146)//(140)
#define BAR_0_08_RANG        (169)//(160)
                             //
#define BAR_0_09_RANG        (191)//(180)
#define BAR_0_10_RANG        (214)//(200)
#define BAR_0_11_RANG        (236)//(220)
#define BAR_0_12_RANG        (259)//(258)
                             //
#define BAR_0_13_RANG        (281)//(278)
#define BAR_0_14_RANG        (304)//(300)
#define BAR_0_15_RANG        (326)//(320)
#define BAR_0_16_RANG        (349)//(350)
                             //
#define BAR_0_17_RANG        (371)//(370)
#define BAR_0_18_RANG        (394)//(390)
/* 1 */                     
#define BAR_1_00_RANG        (0)//(0)
#define BAR_1_01_RANG        (34)//(35)
#define BAR_1_02_RANG        (34)//(30)
#define BAR_1_03_RANG        (56)//(55)
#define BAR_1_04_RANG        (79)//(78)
                             //
#define BAR_1_05_RANG        (101)//(90)
#define BAR_1_06_RANG        (124)//(110)
#define BAR_1_07_RANG        (146)//(140)
#define BAR_1_08_RANG        (169)//(160)
                             //
#define BAR_1_09_RANG        (191)//(180)
#define BAR_1_10_RANG        (214)//(200)
#define BAR_1_11_RANG        (236)//(220)
#define BAR_1_12_RANG        (259)//(258)
                             //
#define BAR_1_13_RANG        (281)//(278)
#define BAR_1_14_RANG        (304)//(300)
#define BAR_1_15_RANG        (326)//(320)
#define BAR_1_16_RANG        (349)//(350)
                             //
#define BAR_1_17_RANG        (371)//(370)
#define BAR_1_18_RANG        (394)//(390)

#define BARCODE_FFFF         (200)    //(100)
#define BARCODE_DIT_NUMBER   (17)     //

#define VARIOUS_MEDIAN_DIT   (1)

void Adc_Init(void);
uint16_t  Get_Adc(uint8_t ch); 
uint16_t Get_Adc_Average(uint8_t ch,uint8_t times); 
uint8_t* uBarTransition( ID_Info* pIDdata,uint8_t* uArrTemp );
void vbar_line_smoth_slid( uint16_t* pOneBuffer,uint16_t len );
uint8_t* uBarNumTransitionAscii( const uint8_t *uOriginal,uint8_t* uArrTemp );
uint8_t* uWaveCrestTrough( const uint16_t* upArrData,uint8_t* upArrBar,int len );
uint8_t uBarCalValue( uint8_t *piBar,uint8_t uInsert,uint8_t uNum,uint8_t uStatus );
uint8_t uEstimateTheRange( uint8_t* puArrDit,uint16_t uBarData,uint8_t uNumData );
uint8_t uEstimateTheDitNum( uint8_t* puArrDit,uint16_t uBarData,uint8_t uNumData );
float uEstimateHalfTheRange( uint16_t uBarData );
int16_t uCalculateMedianValue( uint16_t* puBarArrMin,uint16_t uArrAlen,uint16_t* puBarArrMax,uint16_t uArrBlen );
int iGetIntergeNumber( int *pNum );
int iGetHalfIntergeNumber( unsigned short int *pNum );
uint8_t uSeekCrestTroughAbout( const uint16_t* upArrData,int16_t len,uint16_t* uArrCrest,uint16_t uArrCrestLen,uint16_t* uArrTrough,uint16_t uArrTroughLen );
uint8_t uSeekCrestTroughAbsolute( const uint16_t* upArrData,int16_t len,uint16_t* uArrCrest,uint16_t uArrCrestLen,uint16_t* uArrTrough,uint16_t uArrTroughLen,
	                              uint16_t* uBarArrMin,uint16_t uBarArrMinLen,uint16_t* uBarArrMax,uint16_t uBarArrMaxLen );
uint8_t uSeekCrestTroughMedianA( const uint16_t* upArrData,int16_t len,uint16_t* uArrCrest,uint16_t uArrCrestLen,uint16_t* uArrTrough,uint16_t uArrTroughLen,
								uint16_t* uBarArrMin,uint16_t uBarArrMinLen,uint16_t* uBarArrMax,uint16_t uBarArrMaxLen,uint16_t* uBarArrMinMaxMed,uint16_t uBarArrMinMaxMedLen,
								uint16_t* uBarArrMinMaxMedValue,uint16_t uBarArrMinMaxMedValueLen );
uint8_t uSeekCrestTroughMedianB( uint16_t* uBarArrMin,uint16_t uBarArrMinLen,uint16_t* uBarArrMax,uint16_t uBarArrMaxLen );
uint8_t uArrCrestAndTrough( uint16_t* uArrCrest,uint16_t uArrCrestLen,uint16_t* uArrTrough,uint16_t uArrTroughLen,uint16_t* uArrAndTrough,uint16_t uArrAndTroughLen );
uint8_t uSeekMedianValueAboutA( const uint16_t* upArrData,int16_t len,uint16_t* uBarArrMinMaxMedValue,uint16_t uBarArrMinMaxMedValueLen,
	                           uint16_t* uArrAndTrough,uint16_t uArrAndTroughLen,uint16_t* uBarArr1ExtentTemp,uint16_t uBarArr1ExtentTempLen,
                               uint16_t* uBarArr2ExtentTemp,uint16_t uBarArr2ExtentTempLen,uint16_t* uBarArrExtent,uint16_t uBarArrExtentLen,uint16_t uCrstAndTroghNum );
uint8_t uSeekMedianValueAboutB( const uint16_t* upArrData,int16_t len,uint16_t* uArrAndTrough,uint16_t uArrAndTroughLen,uint16_t* uBarArrExtentTemp,uint16_t uBarArrExtentTempLen,
                               uint16_t* uBarArrExtent,uint16_t uBarArrExtentLen,uint16_t uCrstAndTroghNum,uint16_t uMedianValue );
uint8_t uArrCrestMiddleAndTroughMiddleA( uint16_t* uBarArrExtent,uint16_t uBarArrExtentLen,uint16_t* uBarArrExtentMedian,uint16_t uBarArrExtentMedianLen );
uint8_t uArrCrestMiddleAndTroughMiddleB( uint16_t* uBarArrExtent,uint16_t uBarArrExtentLen,uint16_t* uBarArrExtentMedian,uint16_t uBarArrExtentMedianLen );
uint8_t uCalArrMedianDifference( uint16_t* uBarArrExtentMedian,uint16_t uBarArrExtentMedianLen,uint16_t* uBarArrExtentDifference,uint16_t uBarArrExtentDifferenceLen);
uint8_t uCalArrDitNum( uint16_t* uBarArrExtentDifference,uint16_t uBarArrExtentDifferenceLen,float fRecDitNum,uint8_t* uBarBinValue,uint16_t uBarBinValueLen );
uint8_t uGetArrBarAssiiValue( uint8_t* uBarBinValue,uint16_t uBarBinValueLen,uint8_t* uBarBinValueTemp,uint16_t uBarBinValueTempLen,
							  uint8_t* uBarExtentValue,uint16_t uBarExtentValueLen,uint8_t* upArrBar );
uint8_t uGetFirstTroughValue( const uint16_t* upArrData,int len,int16_t* uTroughValue,uint16_t* puTroughMax );

#endif
	
