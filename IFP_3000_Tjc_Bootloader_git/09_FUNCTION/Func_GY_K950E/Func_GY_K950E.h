#ifndef _FUNC_GY_K950E_
#define _FUNC_GY_K950E_

#include "Func_IFP_300_Drv.h"
#include "Func_ADHandler.h"
#include "Global_Variable.h"

#define SIZE0_DFT    (0x00)     //x000 0000 //0x00 正常默认值
#define SIZE1_DFT    (0x02)     //x000 0010 //0x02 正常反白
#define SIZE2_DFT    (0x04)     //x000 0100 //0x04 正常倒置
#define SIZE3_DFT    (0x08)     //x000 1000 //0x08 正常粗体
#define SIZE4_DFT    (0x10)     //x001 0000 //0x10 正常倍高
#define SIZE5_DFT    (0x20)     //x010 0000 //0x20 正常倍宽
#define SIZE6_DFT    (0x30)     //x011 0000 //0x30 正常倍高倍宽
#define SIZE7_DFT    (0x40)     //x100 0000 //0x40 正常加下划线
#define SIZE8_DFT    (0x38)     //x011 1000 //0x38 正常粗体倍高倍宽 
#define SIZE9_DFT    (0x78)     //x111 1000 //0x78 正常粗体倍高倍宽加下划线 

#define DENSITY_ARR_SIZE  (12)
#define CLASSIC_BLUETOOTH_PACK            (500)

#define PRINT_DIS_COMPANY  (1)

#pragma pack(1)	/*按1字节对齐*/

/*//用户信息结构体  //不能超过255*/
typedef struct Form{	
	uint8_t uGyk_printname[48];                   /* 用户名    */
	uint8_t uGyk_report[20];                      /* 报告      */
	uint8_t uGyk_serialnumber[20];                /* 流水号    */
	uint8_t uGyk_samplenumber[8];                 /* 样本号    */
	uint8_t uGyk_sampletype[20];                  /* 样本类型  */
	uint8_t uGyk_densityresult[DENSITY_ARR_SIZE]; /* 浓度值    */
	uint8_t uGyk_barcode[8];                      /* 条码值    */
	uint8_t uGyk_reference[2*DENSITY_ARR_SIZE+2]; /* 参考值    */
	uint8_t uGyk_testtime[24];                    /* 测试时间  */
	uint8_t uGyk_printtime[24];                   /* 打印时间  */
	uint8_t uGyk_printunit[8];                    /* 单位      */
	uint8_t uGyk_username[20];                    /* 测试者姓名  */               
	uint8_t uGyk_usersex[8];                      /* 测试者性别 */
	uint8_t uGyk_userage[4];                      /* 测试者年龄 */
	uint8_t uGyk_children_num;                    /* 子项数 */
	uint8_t uGyk_children_index;                  /* 当前子项 */
}GYK950E;  /*目前总大小  */

uint8_t GyK950eTestForm( void );
uint8_t GyK950ePrintForm( GYK950E* stuForm );
uint8_t GyK950ePrintEnForm( GYK950E* stuForm );
uint8_t GyK950ePrintChForm( GYK950E* stuForm );
uint8_t GyK950ePrintTest( void );
uint8_t uStorageData( GYK950E* pPrintForm,ID_Info* pIDData,UINTE_DATA_TYPE* pstuIdInfo,uint8_t *pfDensity,uint8_t uChildrenNum );
uint8_t uStorageDataEn( GYK950E* pPrintForm,ID_Info* pIDData,UINTE_DATA_TYPE* pstuIdInfo,uint8_t *pfDensity,uint8_t uChildrenNum );
uint8_t uStorageDataCh( GYK950E* pPrintForm,ID_Info* pIDData,UINTE_DATA_TYPE* pstuIdInfo,uint8_t *pfDensity,uint8_t uChildrenNum );
uint8_t DisplayHistoryDataTxt( GYK950E* pHistory );

uint8_t uLisFrameHeardLoad( uint8_t *uLisTemp,const GYK950E *pHistoryTemp );
uint8_t uLisFrameDensityResultdLoad( uint8_t *uLisTemp,const GYK950E *pHistoryTemp );
uint8_t uLisFrameTailLoad( uint8_t *uLisTemp,const GYK950E *pHistoryTemp );
uint8_t uLisFramePatientLoad( uint8_t *uLisTemp,const GYK950E *pHistoryTemp,USER_MORE_INFO* pUserMore  );
uint8_t uLisFrameOUnitLoad( uint8_t *uLisTemp,const GYK950E *pHistoryTemp );
uint8_t uLisFrameDataPackSend( GYK950E* pHistoryMyFormTemp[3],uint8_t uChildrenNumTemp );
uint8_t GyK950ePrintEnBlueForm( GYK950E* stuForm );
uint8_t GyK950ePrintChBlueForm( GYK950E* stuForm );
unsigned int uMyStrlength(const char *str);


#endif
	
