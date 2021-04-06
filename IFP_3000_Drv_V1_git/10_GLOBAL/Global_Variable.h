#ifndef _GLOBAL_VARIABLE_H_
#define _GLOBAL_VARIABLE_H_

#include "Func_IFP_300_Drv.h"

//#define SYSTEM_SUPPORT_OS       1
#define USART_REC_LEN  		     	(128)  	//定义最大接收字节数 200
#define USART2_REC_LEN  			(2048)  //定义最大接收字节数 200
#define USART3_REC_LEN  			(128)  	//定义最大接收字节数 200
#define USART4_REC_LEN  			(128)  	//定义最大接收字节数 200

#define TJC_FILE_DOWNLOAD_OFF       (0)
#define TJC_FILE_DOWNLOAD_ON        (1)

#define TEST_STK_SIZE           (0)//(1)//(0)      /* 1使能测试堆栈大小 0不使能 */
#define ARR_SAMPLE_TYPE_SIZE    (20)

#define GY_K950E_ON  (1)   
#define GY_K950E_OFF (0)  

#define  N_MSG_NUM                   (4)//(16)     
#define  N_MSG_SIZE                  (4)//(100)    

#define  N_MSG_SPC_NUM                   (4)//(16)     
#define  N_MSG_SPC_SIZE                  (4)//(100) 

#define  N_SHUT_MSG_NUM                   (4)     
#define  N_SHUT_MSG_SIZE                  (4)

extern uint8_t  g_Usart_Rx_Buf[USART_REC_LEN];   //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern uint16_t g_Usart_Rx_Sta;         		 //接收状态标记	

extern uint8_t  g_Usart2_Rx_Buf[USART2_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern uint16_t g_Usart2_Rx_Sta;         		 //接收状态标记	

extern uint8_t  g_Usart3_Rx_Buf[USART3_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern uint16_t g_Usart3_Rx_Sta;         		 //接收状态标记	

extern uint8_t  g_Usart4_Rx_Buf[USART4_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern uint16_t g_Usart4_Rx_Sta;         		 //接收状态标记	

extern uint8_t g_MacAddr[8][20];

//extern uint8_t g_WifiBluetooth[USART2_REC_LEN]; 

#if SEM_MUTEX_CHOISE
extern OS_MUTEX g_Historysem;                /* 开机信号量 */
extern OS_MUTEX g_Acquisition;               /* 读ID卡信号量 */
extern OS_MUTEX g_FlashCom;                  /* FLASH共用 */
extern OS_MUTEX g_DisUI;                     /* 显示互斥信号量 */
extern OS_MUTEX g_MutIDTask;                 /* 显示互斥信号量 */
extern OS_MUTEX g_Referencesem; 

extern OS_SEM g_TjcTouchsem;                 /* 第二代屏幕 */
extern OS_SEM g_ReadIDsem;                   /* 读ID卡信号量 */
extern OS_SEM g_LogInsem;                    /* 触摸屏信号量 */
extern OS_SEM g_ResetLogInsem;               /* 触摸屏信号量 */
extern OS_SEM g_PowerOnsem;                  /* 开机信号量 */
extern OS_SEM g_ForceExit;                   /* 强制退出 */
extern OS_SEM g_WarnCencle;                  /* 警告取消 */
extern OS_SEM g_GetPageId;                   /* 获取页面 */
extern OS_SEM g_WifiReceive;                 /* WIFI接收 */
//extern OS_SEM g_WifiBlueOrder;
//extern OS_MUTEX g_Touchsem;                  /* 触摸屏信号量 */
//extern OS_MUTEX g_MotorReset;                /* 电机复位信号量 */
#else
extern OS_SEM *gp_Touchsem;
extern OS_SEM *gp_TjcTouchsem;
extern OS_SEM *gp_ReadIDsem;
extern OS_SEM *gp_Acquisition;
extern OS_SEM *gp_LogInsem;
extern OS_SEM *gp_ResetLogInsem;
extern OS_SEM *gp_MotorReset;
extern OS_SEM *gp_PowerOnsem;
extern OS_SEM *gp_Historysem;
extern OS_SEM *gp_ForceExit;
extern OS_SEM *gp_WarnCencle;
extern OS_SEM *gp_GetPageId;
extern OS_SEM *gp_WifiReceive;
//extern OS_EVENT *gp_WifiDataReceive;
#endif

extern OS_Q g_TouchMsgQue;
extern OS_Q g_TouchSpcMsgQue;
extern OS_Q g_ShutDownMsgQue;                /*消息邮箱*/

extern DRV_PWM_TIMERDRIVEN_TYPE* _gp_PWM1;          /* 声明报错与头文件包含顺序有关 */


extern DRV_AT24C32_TYPE* _gp_ID;                      /*  */
extern ID_Info g_IdMemory;
extern PRO_SERIAL g_projectSerial;

extern DRV_HARDAD7685_TYPE* _gp_HardAD7685;
extern DRV_FLASH_P25Q32H_TYPE* _gp_HardFlashP25Q32H;

#if MAX5402_CHOISE
extern DRV_MAX5402EUA_HARD_TYPE* _gp_MAX5402Hard;
#else
extern DRV_MAX5402EUA_TYPE* _gp_MAX5402;
#endif

extern uint8_t g_userName[9+1],g_userNamePas[6+1];
extern uint8_t g_uSpecialNamePas[6+1];//extern uint8_t g_uSpecialNamePas[USER_PASSWORD_SIZE+1];
extern uint8_t g_uWifiSsidName[20];
extern uint8_t g_uWifiNamePas[20];
extern uint8_t g_uPrintTitles[48];
extern uint8_t g_uInputPrintTitles[48];
extern uint8_t g_ServerIPAddr[16],g_ServerPort[6];

extern USER_REFERRENCE g_stuUserReference;
extern USER_MORE_INFO g_stuUserMoreInfo;
extern int16_t g_uRecordHistoryPage;
extern int8_t g_uRecordReferencePage;
extern int8_t g_uRecordCoverPage;
extern int8_t g_uRecordIdCardCover;
extern uint8_t g_uSampleType[ARR_SAMPLE_TYPE_SIZE];

extern CONFIG_FILE* gp_stuConfigFile;
extern USER_TIME_FILE* gp_stuEditTime;
extern USER_INPUT_CONFIG_FILE* gp_stuEditInputConfig;

extern uint8_t g_ReadPageIDStatus;
extern uint8_t g_uRecAutoDownTime;
extern uint8_t g_RecPageID;
extern uint16_t g_uAutoTestTimes;
extern uint16_t g_uElectricValue;
extern uint8_t g_uChargeStauts;
extern uint8_t g_uTransparentStatus;
extern uint8_t g_uWifiConnect;
extern uint8_t g_uTjcFileDownload;
extern uint8_t g_ShutdownError;
////extern uint8_t g_uWifiStatus;
////extern uint32_t g_RecDe;

////extern uint8_t g_uOrdereEven;
////extern uint8_t g_Temp;
////extern DRV_AT24C32_TYPE* _gp_EEP;
////extern DRV_AD7685_TYPE* _gp_AD7685;

#endif
