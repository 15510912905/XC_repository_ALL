/********************************************************
   ��Ȩ���� (C), 2001-2100, �Ĵ��½���������ɷ����޹�˾
  -------------------------------------------------------

				Ƕ��ʽ����ƽ̨����ͨ�ù���

  -------------------------------------------------------
   �� �� ��   : Func_Common.c
   �� �� ��   : V1.0.0.0
   ��    ��   : ryc
   ��������   : 2019��06��27��
   ��������   : ͨ�ù��ܶ���
   ������     : 
 ********************************************************/

#ifndef _FUNC_COMMON_H_
#define _FUNC_COMMON_H_

#include "stdint.h"
//#include "Drv_CANProtocol.h"
#include "Drv_MotionControlComponents.h"
//#include "Drv_Valve.h"
//#include "Drv_Pump.h"
#include "Drv_AT24C32.h"
//#include "Prt_CmdDoubleList.h"
//#include "Func_LogIn.h"

#define MAPID_ADDRA                (312)
#define MAPID_ADDRB                (274)//(1.13)(270)(1.15)

#define TURN_READ_ID               (0)
#define TJC_SCE_WARN_OFF           (0)

#define TJC_TOUCH_ENABLE           (0)
#define TJC_TEST_TOUCH_ENABLE      (1)

#define EEP_START_BASE_ADDR     (0x0000)
#define EEP_DENSITY_BASE_ADDR   (0x0080)//(0x0020)

#define EEP_PAGE_SIZE           (0x0020)
#define FOLAT_BASE_SIZE         (0x04)

#define P25Q32H_ALL_SECTOR      (4096)
#define STORAGE_DENSITY_MAX     (999)//(254) //(100)//(24)
#define DENSITY_PAGE_NUMBER     (3)

#define STORAGE_REFERENCE_MAX   (30)

#define USE_TOTALIZE_PAGE         (10)

#define EXE_SUCCEED               (0)
#define EXE_FAILED                (1)

#define EXE_STAUTS                (2)
#define EXE_SPECIAL_FAILED        (-1)

#define LOAD_VOLTAGE              (20)

#define REF_SEEK_FAILE            (0)

#define VOLTAGE_THRESHOLD_PERCENTAGE        (2141)//(2)    // 2141 (3.45)
#define VOLTAGE_THRESHOLD_PROMPT            (2172)//(15)   // 2172 (3.5)

#define VOLTAGE_VALUES                      (34) //(40)//(40)  //
#define VOLTAGE_STEP                        (595)//(20)//(40)
#define VOLTAGE_THRESHOLD                   (680)//(VOLTAGE_VALUES*VOLTAGE_STEP)
#define VOLTAGE_COEF                        (32)
#define VOLTAGE_1_THRESHOLD                 (720)
#define VOLTAGE_1_COEF                      (32)
#define VOLTAGE_1_REF                       (100)

#define VOLTAGE_PLOT_SCALE                  (3)

#define VOLTAGE_LINE                        (430)//(30)
#define VOLTAGE_TIMES                       (6)//(10)
#define VOLTAGE_PROMPT_TIMES                (120/ELECTRIC_DIS_TIME) //(120)
#define VOLTAGE_PROMPT1_TIMES               (6)//(20)
#define PROMPT_VOLTAGE                      (-10)

#define VOLTAGE_AD_1_VALUES                 (2100)  //(3.4)
#define VOLTAGE_AD_2_VALUES                 (2792)  //(4.5)
#define VOLTAGE_AD_3_VALUES                 (2172)  //(3.5)
#define VOLTAGE_AD_4_VALUES                 (2420)  //(3.9)
#define VOLTAGE_AD_5_VALUES                 (2451)  //(3.95)
#define VOLTAGE_AD_6_VALUES                 (2234)  //(3.6)
#define VOLTAGE_AD_7_VALUES                 (2482)  //(4.0)

#define VOLTAGE_AD_TH1_VALUES               (0)  //(3.6)
#define VOLTAGE_AD_TH2_VALUES               (30)  //(4.0)

#define DISCHARGE_STATE                        (1)
#define CHARGE_STATE                           (2)

#define TJC_PAGE_ERROR_MAX                     (5)

#define SPI_TEST_DIS_CON_ID      (2)

#define ID_ITEM_DIS_CON_ID       (1)
#define ID_BAR_DIS_CON_ID        (2)
#define ID_WAVE_DIS_CON_ID       (3)
#define ID_NUM_DIS_CON_ID        (8)
#define ID_CURRENT_DIS_CON_ID    (9)

#define SET1_TEXT_DIS_CON_ID     (0)
#define EXIT_TEXT_DIS_CON_ID     (0)

#define MAIN_SERIAL_DIS_CON_ID   (2)//(9)
#define MAIN_ITEM_DIS_CON_ID     (4)//(10)
#define MAIN_BARCODE_DIS_CON_ID  (8)

#define MORE1_1_DIS_CON_ID       (11)
#define MORE1_2_DIS_CON_ID       (12)
#define MORE1_3_DIS_CON_ID       (13)
#define MORE1_4_DIS_CON_ID       (14)

#define MAIN_PROGRESS_DIS_CON_ID (0)
#define MAIN_DENSITY_DIS1_CON_ID  (1)
#define MAIN_DENSITY_DIS2_CON_ID  (2)
#define MAIN_DENSITY_DIS3_CON_ID  (3)
#define MAIN_DENSITY_DIS6_CON_ID  (6)
#define MAIN_DENSITY_DIS7_CON_ID  (7)
#define MAIN_DENSITY_DIS8_CON_ID  (8)
#define MAIN_DENSITY_DIS11_CON_ID  (11)
#define MAIN_DENSITY_DIS12_CON_ID  (12)
#define MAIN_DENSITY_DIS13_CON_ID  (13)

#define PASSWORD_PAGE_TEST_ID      (0)
#define INSTRUMENT_DIS_CON_ID      (2)

#define VIS_OBJ_PAGE6_ID       (0x0A)
#define VIS_OBJ_CON_ID         (3)
#define VIS_HIDE               (0)
#define VIS_SHOW               (1)
#define VIS_OBJ_WARN_CON_ID    (2)

#define STANDARD_DIS_CON_ID     (4)
#define QUICK_DIS_CON_ID        (5)

#define BACK_DATA_DIS_CON_ID     (12)
#define BACK_DATA1_DIS_CON_ID    (17)
#define BACK_DATA2_DIS_CON_ID    (18)

#define QC_ITEM_DIS_CON_ID      (15)
#define QC_SAMPLE_DIS_CON_ID    (16)
#define QC_PRODUCT_DIS_CON_ID   (17)
#define QC_REF_DIS_CON_ID       (18)

#define MAIN_PROGRESS1_VALUE     (5)
#define MAIN_PROGRESS2_VALUE     (30)
#define MAIN_PROGRESS3_VALUE     (65)
#define MAIN_PROGRESS4_VALUE     (90)
#define MAIN_PROGRESS5_VALUE     (100)

#define NAME_DENSITY1_DIS_CON_ID      (6)
#define NAME_DENSITY2_DIS_CON_ID      (7)
#define NAME_DENSITY3_DIS_CON_ID      (8)

#define SERIAL_DIS_CON_ID        (1)
#define NAME_DIS_CON_ID          (2)
#define LOT_DIS_CON_ID           (3)
#define SAMPLE_DIS_CON_ID        (4)
#define ITEM_DIS_CON_ID          (5)
#define DENSITY_DIS_CON_ID       (6)//(11)
#define DATA_DIS_CON_ID          (7)

#define FLUORESCENCE_ON           (0x01)
#define FLUORESCENCE_OFF          (0x00)

#define SCAN_BAR_ON           (0x01)
#define SCAN_BAR_OFF          (0x00)

#define BUZZER_ON           (0x01)
#define BUZZER_OFF          (0x00)

#define PRINT_AD_ON           (0x01)
#define PRINT_AD_OFF          (0x00)

#define PRINT_BAR_ON           (0x01)
#define PRINT_BAR_OFF          (0x00)

#define PRINT_1AD_ON           (0x01)
#define PRINT_1AD_OFF          (0x00)

#define WIFI_ON                (0x01)
#define WIFI_OFF               (0x00)

#define EN_ON           (0x01)
#define CH_ON           (0x00)

#define COVER_ID_CHI_ON           (0x00)
#define COVER_ID_CHI_OFF          (0x01)

#define SWITCH_MIC_ON           (0x01)
#define SWITCH_MIC_OFF          (0x00)

#define CONCERSION_COFFICIENT  (1.14)

#define CTRL_POWER3_ON           (0x01)
#define CTRL_POWER3_OFF          (0x00)

#define CTRL_POWER5_ON           (0x01)
#define CTRL_POWER5_OFF          (0x00)

#define CTRL_POWER_ON           (0x01)
#define CTRL_POWER_OFF          (0x00)

#define DISHIS_VALUE             (0x00)

#define UI_Y_PROMPT                (1)
#define UI_N_PROMPT                (0)

#define REAL_TIME_ON       (1)
#define REAL_TIME_OFF      (0)

#define ELECTRIC_QUANTITY_ON       (1)
#define ELECTRIC_QUANTITY_OFF      (0)

#define ELECTRIC_AVE_TIME          (8)
#define ELECTRIC_DIS_TIME          (10)

#define AUTO_SHUTDOWN_90_TIME      (99)

#define MAX_PEAK_NUM                (10)
#define MAX_CHILDER                (3)
#define MAX_IDCARD_NUM             (1)//(30)//(1)//(6)

#define MORE_TRADIO_0_BUTTON            (11)
#define MORE_TRADIO_1_BUTTON            (12)

#define CUT_EN_CH_BUTTON                (2)

#define DEF_COVER_ON                       (1)
#define DEF_COVER_OFF                      (0)

#define BUZZER_ONE_TIME                    (1)
#define BUZZER_THREE_TIME                  (3)

#define DIS_VER_ID			   (1)

#define SN_NUM  			   (15)

#define BLACK   (0x0000)  //? ��ɫ????
#define NAVY    (0x000F)  // ?����ɫ??
#define DGREEN  (0x03E0)  // ?����ɫ??
#define DCYAN   (0x03EF)  //? ����ɫ??
#define MAROON  (0x7800)  //? ���ɫ??????
#define PURPLE  (0x780F)  //? ��ɫ??
#define OLIVE   (0x7BE0)  //? �����??????
#define LGRAY   (0xC618)  //   �Ұ�ɫ
#define DGRAY   (0x7BEF)  // ?���ɫ??????
#define BLUE    (0x001F)  // ?��ɫ????
#define GREEN   (0x07E0)  // ?��ɫ??????????
#define CYAN    (0x07FF)  // ?��ɫ??
#define RED     (0xF800)  // ?��ɫ???????
#define MAGENTA (0xF81F)  // ?Ʒ��????
#define YELLOW  (0xFFE0)  // ?��ɫ????????
#define WHITE   (0xFFFF)  // ?��ɫ?

#define LINEAR_RANGE_MAX (1000000)
#define DIS_BAR_NUMBER (5)

#pragma pack(8)	/*��1�ֽڶ���*/
typedef struct{		
	uint16_t sample_measure;          /* 0x6EE */
	uint16_t buffer_measure;          /* 0x6F0 */
	uint16_t mix_measure;             /* 0x9F2 */
	uint16_t produce_years;           /* 0x6F6-0x6F7 */
	uint16_t test_time;               /* 0x9E(��λ) */
	uint16_t prepare_time;            /* 0x9C(��λ) */

	uint16_t interval_s[12];                    /* 0x60 */
	uint16_t interval_e[12];                    /* 0x61 */ 
	uint8_t se_value[12];              /* 0x64 */
	uint8_t se_algorithm[12];          /* 0x65 */
	uint8_t area_limit[8];            /* 0x4b */ 
	uint8_t barcode[8];    		      /* 0x1e */	
	uint8_t lot_num[8];               /* 0x2B */
	uint8_t project_name[20];         /* 0x3b��Ŀ���� */
	
	uint8_t Instrument;               /* 0x6F4 */
	uint8_t product_code;             /* 0x6F5 */
	uint8_t month_num;                /* 0x6FA */	
	uint8_t produce_month;            /* 0x6F8 */
	
	uint8_t lot;                      /* 0x6F9 */
	uint8_t wavenumber;               /* 0x00A8 */
	uint8_t children_num;             /* 0x06ed */
	uint8_t nullsample;		          /* 0xA9*/
	
	uint8_t samplevalue;		      /* 0xA0*/                               
	uint8_t peak_num;                 /* 0x6ec */
	uint8_t c_peak;                   /* 0x6ec */  
	uint8_t uidtempreserve;           /*  */	
	
}ID_Info;

#pragma pack(8)
typedef struct{
	float children_pesponse[16];             /* 0x075c */
	float children_density[16];	             /* 0x0708 */
	float children_sample_coefficient[10];    /* 0x0180 */
	
	float children_para_a;                   /* 0x07b0 */
	float children_para_b;                   /* 0x07b4 */
	float children_para_c;                   /* 0x07b8 */
	float children_para_d;                   /* 0x07bc */
	
	float children_limits_min;               /* 0x014C */
	float children_limits_max;               /* 0x0160 */
	
	uint8_t children_name[20];               /* 0x00ac */
	uint8_t children_unit_name[8];           /* 0x00FC */
	
	uint8_t children_vary_pesponse;	  		 /* 0x0702 */
	uint8_t children_vary_density;      	 /* 0x0701*/	
	uint8_t children_pesponse_dot;	  		 /* 0x0703 */
	uint8_t children_density_dot;      		 /* 0x0703 */
	
	uint8_t children_ufitt;                  /* 0x0704 */   	
	uint8_t children_c_1p;                   /* 0x0175 */
	uint8_t children_c_2p;                   /* 0x0176 */
	uint8_t children_c_3p;                   /* 0x0177 */
	
	uint8_t children_formula_tc;             /* 0x0178 */
	uint8_t children_limits_dot;	  		 /* 0x0174 */
	uint8_t children_coefficient_dot;        /* 0x017E */	
	uint8_t uuintetempreserve;               /*  */
	
}UINTE_DATA_TYPE;

typedef struct{	
	uint32_t temp_10_data[5];
	
	uint16_t history_max;
	uint16_t serial_num;            /* ��ˮ�� */
	uint16_t history_count;
	
	uint16_t temp_20_data[12];
	
	uint8_t serial_id[20];          /* ��ˮ�� �ж�*/
	uint8_t rec_day;                /* ���� */	
	uint8_t uid_count;              /* ��ʷ��¼ */
	uint8_t uid_max;                /* ��ʷ��¼���ֵ */
	uint8_t ureference_max;			/* �ο���Χ��¼���ֵ */
	uint8_t ureference_count;       /* �ο���Χ��¼ */
	
	uint8_t temp_30_data[20];	
}PRO_SERIAL;

typedef struct{
	uint8_t ureference_name[32];             /*  */  
	float fuser_00_limits_min;               /*  */
	float fuser_00_limits_max;               /*  */
	float fuser_01_limits_min;               /*  */
	float fuser_01_limits_max;               /*  */
	float fuser_02_limits_min;               /*  */
	float fuser_02_limits_max;               /*  */
}USER_REFERRENCE;

typedef struct{	
	uint8_t user_name[20];                /*  */               
	uint8_t user_sex[2];                  /*  */
	uint8_t user_age;                     /*  */
	uint8_t user_sexstatus;               /*  */
}USER_MORE_INFO;

typedef struct{	
	float fCoeff;                 /* ת��ϵ���ɵ� */
	uint16_t uStartOffset;        /* ��ʼ��ƫ���� */
	uint16_t uMax5402Gain;        /* �������� */
	uint16_t uBarOffset;          /* ����ƫ������ */
	uint16_t uLanReferValue;      /* �����ο�ֵ */
	uint8_t uAutoShutDown;        /* �Զ����ػ� */
	uint8_t uPrintfOnOff;         /* ��ӡ���ÿ��� */
	uint8_t uBuzzerOnOff;         /* ���������� */
	uint8_t uPrintAD;             /* ADֵ��ӡ */
	uint8_t uPrintBar;            /* Barֵ��ӡ */
	uint8_t uWifiOnOff;           /* WIFIֵ��ӡ */
	uint8_t uCutEnCu;             /* EN/CH�л� */
	uint8_t uLedOnOff;            /* LED�� */
	uint8_t uScanBar;             /* ɨ��Bar */
	uint8_t uSwitchOnOff;         /* ΢������ */
	uint8_t uSNStrNum[16];        /* SN���к� */
	
	uint8_t uReserveChar[12];     /* Ԥ���ռ� */
	uint16_t uReserve2Char[8];    /* Ԥ���ռ� */ 
	uint32_t uReserve4Char[5];    /* Ԥ���ռ� */ 
	float uReserve4FChar[5];      /* Ԥ���ռ� */ 
}CONFIG_FILE;

typedef struct{	
	uint8_t ustuYears;              /* ���� */
	uint8_t ustuMonth;               /* �� */

}USER_INF_FILE;

typedef struct{	
	uint16_t ustuTimeYears;               /* ���� */
	uint8_t ustuTimeMonth;               /* �� */
	uint8_t ustuTimeDay;                 /* �� */
	uint8_t ustuTimeHours;               /* ʱ */
	uint8_t ustuTimeMinuts;              /* �� */
	uint8_t ustuTimeSeconds;             /* �� */
}USER_TIME_FILE;

#pragma pack(8)
typedef struct{	
	float fstuCoeff;
	uint16_t ustuOffset;               /* ƫ���� */
	uint16_t ustuGain;                 /* ���� */
	uint16_t ustuBarOffset;            /* ���� */
	uint16_t ustuInputLanRef;          /* ���� */
	uint8_t ustuAutoTime;              /* ���� */
	uint8_t ustuSNStrNum[16];          /* */
}USER_INPUT_CONFIG_FILE;

/* ��ʼ������
 ********************************************************/

/* ͨ��������������
 ********************************************************/
uint8_t* vPutFloat( uint8_t* pArr, float fTemp );
uint8_t uConfigAllFileInit( void );
uint8_t uIdCountCheck( void );
int8_t uGetIdCountValue( void );
uint8_t uIdDisplay( uint8_t uCurrent );
uint8_t uIdDisplayUpDown( uint8_t uUpDown );
uint8_t uReadIdItem( void );
uint8_t uClearIdData( void );
uint8_t uChangeIdCard( ID_Info *pIdCard );
ID_Info* uReadStoreIdItem( int8_t iIdNum );
uint8_t uSetIdCount( void );
uint8_t uSetPageInit( void );
uint8_t uSerialFileInit( void );
uint8_t uConfigPrintfFile( void );
uint8_t uConfigBuzzerFile( void );
uint8_t uConfigPrintADFile( void );
uint8_t uConfigScanBarFile( void );
uint8_t uConfigWifiFile( void );
uint8_t uConfigPrintBarFile( void );
uint8_t uConfigPrint1BarFile( void );
uint8_t uInitSidoRoot( void );
uint8_t uWarnCancel( void );
uint8_t uOpenCloseLed( void );
uint8_t uPromptInformation( uint8_t* uArrInfo );
uint8_t uPromptParameter( uint8_t* uArrInfo );
uint8_t uConfigOf( uint8_t uTempOffset );
uint8_t uConfig1Add( void );
void vInquireScreen( void );
uint8_t uConfig2Add( void );
uint8_t uConfig1Sub( void );
uint8_t uConfig2Sub( void );
uint8_t uConfigAffirm( void );
uint8_t uDensityAffirmPage( void );
uint8_t uConfigCalendar( void );
int16_t iElectricQuantityDis( uint8_t uDisplay );
int16_t iRealElectricValue( uint8_t uAverage );
uint8_t uSetTimeEditInit( void );
uint8_t uSetInputConfigEditInit( CONFIG_FILE* pstuConfig );
uint8_t uSetSystemEditInit( CONFIG_FILE* pstuConfig );
uint8_t uLinearRangeWarn( uint8_t uWarn );
uint8_t uSpecialPasswordInit( void );
uint8_t uBarErrorProcess( void );
uint8_t uSpecialMoreInformationInit( void );
uint8_t uDisInputUserInfoInit( USER_MORE_INFO* pstuConfig );
uint8_t uDisInputReferenceInit( USER_REFERRENCE* pstuConfig,uint8_t uRefNumber );
uint8_t uDisParameterInit( void );
uint8_t uDisInstrumentInit( void );
uint8_t uSetRerferenceInit( void );
uint8_t uSetPrintTitlesInit( void );
uint8_t uSpecialMoreInformation( void );
uint8_t uSetRerference( uint8_t uDisInfo );
uint8_t uConfigTime( void );
uint8_t uConfigTimeYears( void );
uint8_t uConfigTimeMonth( void );
uint8_t uConfigTimeData( void );
uint8_t uConfigTimeHour( void );
uint8_t uConfigTimeMinutes( void );
uint8_t uPrompterWarn( uint8_t *pStr );
uint8_t uFactoryReset( void );
uint8_t uEraseSectorFromStartToEnd( uint16_t uStart,uint16_t uEnd );
uint8_t uHistoryClear( uint8_t uPoempter );
uint8_t uReferenceClear( void );
uint8_t uConfigUpgrade( void );
uint8_t uSetIdReturnPage( void );
uint8_t uSetTimeDisplay( void );
uint8_t uSetPageStatus( void );
uint8_t uSemclear( OS_SEM* pSem );
float vGetFloat( uint8_t* pArr );
uint8_t uSteopMotorInit( void );
uint8_t uMax5402GainInitSet( uint16_t uGain,uint8_t uPrompter );
uint8_t uConfirmIdCardPage( uint8_t uIdPage );
uint8_t uConfirmPage( uint8_t uPage );
uint8_t uAllConfigSet( USER_INPUT_CONFIG_FILE* pstuConfig );
uint8_t uSystemAllConfigSet( USER_INPUT_CONFIG_FILE* pstuConfig );
uint8_t uSampleOffsetSet( uint16_t uOffsetSet,uint8_t uPrompter );
uint8_t uSampleBarOffsetSet( uint16_t uOffsetSet,uint8_t uPrompter );
uint8_t uAutoShutdownSet( uint8_t uTimes,uint8_t uPrompter );
uint8_t uSetPrintTitles( uint8_t* puTempTitles,uint8_t uNum,uint8_t uPrompter );
uint8_t uFluorescenceLight( uint8_t uOnOff );
uint8_t uCtrl3VPower( uint8_t uOnOff );
uint8_t uCtrl5VPower( uint8_t uOnOff );
uint8_t uCtrlPower( uint8_t uOnOff );
uint8_t uBuzzer( uint8_t uOnOff );
uint8_t uInitIdChildren( UINTE_DATA_TYPE* stuIdInfo,uint8_t uChildren,uint8_t uSpcIndex );
uint8_t uInitIdInfo( ID_Info* stuIdInfo );
uint8_t uReadChildrenData( UINTE_DATA_TYPE* stuIdInfo,uint8_t uChildren,uint8_t uIdNum );
uint8_t uDisplayHistoryData( uint8_t pageid );
uint8_t DisplayHistoryData( uint8_t pageid );
uint8_t *cReverse(uint8_t *p_num,uint8_t size);
int *iReverse(int *p_num,int size);
uint8_t barcompare( const char *stra,const char *strb,uint32_t size );
uint8_t arrcompare( const unsigned char *stra,const unsigned char *strb,uint32_t size );
uint8_t uReportSemErr( OS_SEM *pSem,uint16_t uTime,uint8_t *uErrStr );
uint8_t* ReadEEPTou8Arr( uint8_t* u8Arr,uint16_t u16Addr,uint8_t size );
uint16_t* ReadEEPTou16Arr( uint16_t* u16Arr,uint16_t u16Addr,uint8_t size );
uint8_t WriteEEPTou8Arr( uint8_t* u8Arr,uint16_t u16Addr,uint8_t size );
uint8_t ResetEEP( void );
uint8_t* ReadIDTou8Arr( uint8_t* u8Arr,uint16_t u16Addr,uint8_t size );
uint16_t* ReadIDTou16Arr( uint16_t* u16Arr,uint16_t u16Addr,uint8_t size );
void vEnableUsartPrintf( uint8_t uUsart );
uint8_t uGetUsartPrintf( void );
void vIDAllPrint( ID_Info* stuIdInfo );
void vIDChildrenPrint( UINTE_DATA_TYPE* pstuTemp,uint8_t uChildren );
uint8_t uDisplayReferenceData( uint8_t pageid );
uint8_t DisplayReferenceData( uint8_t pageid );
uint8_t uFindReferenceName( uint8_t* uNameStr );
uint8_t uStoreReferencedata( uint8_t uCover,uint8_t uDisInfo );
uint8_t uStoreMassReferencedata( USER_REFERRENCE* pstuUserRerfence,PRO_SERIAL* pstuRecRerference );
uint8_t uStoreReferenceResult( uint8_t uDisInfo );
uint8_t uConfirmSetPage( uint8_t uPage,int16_t iGetPage );
uint8_t uSetCoeffValue( float fTempCoeff,uint8_t uPrompter );
uint8_t uSetMassRerference( USER_REFERRENCE* pstuUserRerf,PRO_SERIAL* pstuRecRerf );
uint8_t uDisplayVersion( void );
uint8_t uTemperatrueDisplay( void );
uint8_t WriteIDTou8Arr( uint8_t* u8Arr,uint16_t u16Addr,uint8_t size );
uint8_t uErrorInvalidId( uint8_t uBuzzer );
uint8_t uDisplayHistoryDataSpecifiedPage( const uint16_t uSpecpageid );
uint8_t uClearInputUserInfo( void );
uint8_t uClearInputReference( void );
uint8_t uClearInputSystem( void );
uint8_t uClearInputTimeValue( void );
uint8_t uClearInputServer( void );
uint8_t uIdPageDisplay( uint8_t uCurrent );
uint8_t uBuzzerTimes( uint8_t uTimes );
uint8_t uReferenceVerify( USER_REFERRENCE *pTempReference );
uint8_t uStoreReferenceCover( void );
uint8_t uSetLanboRefValue( uint16_t uTempLanboRef,uint8_t uPrompter );
uint8_t uConfigMicSwitch( void );
int8_t uVerifyIDBar( uint8_t* puArrBarCode );
uint8_t uStoreIDCardCover( void );
ID_Info* uReadStoreIdItemCope( int8_t iIdNum,ID_Info* pstuTempIDCard );
uint8_t uSetSNStr( uint8_t* puSnStr,uint8_t uStrNum,uint8_t uPrompter );
uint8_t uReportSem( OS_SEM *pSem,uint16_t uTime );
uint8_t uTestReadIdItem( void );
/* ͨ�ó�פ��������
 ********************************************************/
 
#endif
