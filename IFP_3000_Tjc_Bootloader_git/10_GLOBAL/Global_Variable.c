#include "Global_Variable.h"

///*全局变量*/
uint16_t g_Usart_Rx_Sta=0;                                              /*接收状态标记	 */
uint8_t g_Usart_Rx_Buf[USART_REC_LEN];                                  /* 接收缓冲,最大USART_REC_LEN个字节. */
uint8_t g_Usart_Tx_Buf[USART_REC_LEN];                                  /* 接收缓冲,最大USART_REC_LEN个字节. */
											                            
uint16_t g_Usart2_Rx_Sta=0;                                             /*接收状态标记	 */
uint8_t g_Usart2_Rx_Buf[USART2_REC_LEN];                                /* 接收缓冲,最大USART_REC_LEN个字节. */
											                            
uint16_t g_Usart3_Rx_Sta=0;                                             /*接收状态标记	 */
uint8_t g_Usart3_Rx_Buf[USART3_REC_LEN];                                /* 接收缓冲,最大USART_REC_LEN个字节. */
											                            
uint16_t g_Usart4_Rx_Sta=0;                                             /*接收状态标记	 */
uint8_t g_Usart4_Rx_Buf[USART4_REC_LEN];                                /* 接收缓冲,最大USART_REC_LEN个字节. */
uint8_t g_Usart4_Tx_Buf[USART4_REC_LEN];                                /* 接收缓冲,最大USART_REC_LEN个字节. */

uint8_t g_MacAddr[WIFI_AP_MAX][WIFI_SSID_NAME_MAX] ={ 0 };

//uint8_t g_WifiBluetooth[USART2_REC_LEN];                                /* 接收缓冲,最大USART_REC_LEN个字节. */
											                            
#if SEM_MUTEX_CHOISE                                                    
//OS_MUTEX g_Historysem;                                                  /* 历史信号量 */
//OS_MUTEX g_Acquisition;                                                 /* 采光信号量 */
OS_MUTEX g_FlashCom;                               	                    /* FLASH共用 */
//OS_MUTEX g_DisUI;                                                       /* 显示互斥信号量 */
//OS_MUTEX g_MutIDTask;                                                   /* 显示互斥信号量 */
//OS_MUTEX g_Referencesem;                                                /* 参考信号量 */
//	
OS_SEM g_TjcTouchsem;                                                   /* 第二代屏幕 */
//OS_SEM g_ReadIDsem;                                                     /* 读ID卡信号量 */
//OS_SEM g_LogInsem;                                                      /* 登录信号量 */
//OS_SEM g_ResetLogInsem;                                                 /* 再次登录信号量 */
OS_SEM g_PowerOnsem;                                                    /* 开机信号量 */
//OS_SEM g_ForceExit;                                                     /* 强制退出 */
//OS_SEM g_WarnCencle;                                                    /* 警告取消 */
//OS_SEM g_GetPageId;                                                     /* 获取页面 */
OS_SEM g_WifiReceive;                                                   /* WIFI接收 */

OS_SEM g_TjcUpdata;                                                    /*  */
OS_SEM g_TjcUpgarde;                                                    /*  */

//OS_SEM g_WifiBlueOrder;                                                 /* WIFI接收 */
//OS_MUTEX g_Touchsem;                                                  /* 触摸屏信号量 */
//OS_MUTEX g_MotorReset;                                                /* 电机复位信号量 */
//OS_SEM *gp_WifiDataReceive = NULL;                                    /* WIFI */
#else                                                                   
OS_SEM *gp_Touchsem = NULL;                                             /* 触摸屏信号量 */
OS_SEM *gp_TjcTouchsem = NULL;                                          /* 第二代屏幕 */
OS_SEM *gp_ReadIDsem = NULL;                                            /* 读ID卡信号量 */
OS_SEM *gp_Acquisition = NULL;                                          /* 读ID卡信号量 */
OS_SEM *gp_LogInsem = NULL;                                             /* 触摸屏信号量 */
OS_SEM *gp_ResetLogInsem = NULL;                                        /* 触摸屏信号量 */
OS_SEM *gp_MotorReset = NULL;                                           /* 电机复位信号量 */
OS_SEM *gp_PowerOnsem = NULL;                                           /* 开机信号量 */
OS_SEM *gp_Historysem = NULL;                                           /* 开机信号量 */
OS_SEM *gp_ForceExit = NULL;                                            /* 强制退出 */
OS_SEM *gp_WarnCencle = NULL;                                           /* 警告取消 */
OS_SEM *gp_GetPageId = NULL;                                            /* 获取页面 */
OS_SEM *gp_WifiReceive = NULL;                                          /* WIFI接收 */
//OS_SEM *gp_WifiDataReceive = NULL;                                    /* WIFI */
#endif                                                                  
											                            
OS_Q g_TouchMsgQue = {0};                                               /*消息邮箱*/
OS_Q g_TouchSpcMsgQue = {0};                                            /*消息邮箱*/
OS_Q g_ShutDownMsgQue = {0};                                            /*消息邮箱*/
											                            
//DRV_PWM_TIMERDRIVEN_TYPE* _gp_PWM1 = NULL;                              
//DRV_AT24C32_TYPE* _gp_ID = NULL;                                        /* 记录ID卡信息 */

#if MAX5402_CHOISE
DRV_MAX5402EUA_HARD_TYPE* _gp_MAX5402Hard = NULL;
#else
//DRV_MAX5402EUA_TYPE* _gp_MAX5402 = NULL;
#endif

//DRV_HARDAD7685_TYPE* _gp_HardAD7685 = NULL;
DRV_FLASH_P25Q32H_TYPE* _gp_HardFlashP25Q32H = NULL;

//ID_Info g_IdMemory = {0}; 
PRO_SERIAL g_projectSerial = {0};

AUTO_REMEMBER g_stuAutoRemenber = {0};

USER_REFERRENCE g_stuUserReference = {0};
USER_MORE_INFO g_stuUserMoreInfo = {0};
CONFIG_FILE* gp_stuConfigFile = NULL;
USER_TIME_FILE* gp_stuEditTime = NULL;
USER_INPUT_CONFIG_FILE* gp_stuEditInputConfig = NULL;
TJC_CTRL_MSG gp_stuTjcCtrlMsg = {0};
ALGORITHM_DATA_TYPE g_stuMyAlgorithm ={0};
//uint32_t g_ADC_Buffer[SCAN_LENGTH] = {0};           /* 用于存放AD7685采集的数据 */
//uint16_t g_ADC_BarCode[BARVODE_LENGTH] = {0};       /* 用于存放AD7685采集的数据 */
uint16_t g_uAutoTestTimes = 0;                            /* 自动测试时间 */
int16_t g_uRecordHistoryPage = 0;
int8_t g_uRecordReferencePage = 0;
int8_t g_uRecordCoverPage = 0;
int8_t g_uRecordIdCardCover = 0;

uint8_t g_userName[USER_NAME_SIZE+1] = {0},g_userNamePas[USER_PASSWORD_SIZE+1] = {0};
#if LOGIN_CODE
uint8_t g_userRegistName[USER_NAME_SIZE+1] = {0},g_userRegistNamePas[USER_PASSWORD_SIZE+1] = {0},g_userRegistNamePas1[USER_PASSWORD_SIZE+1] = {0};
#endif
uint8_t g_ServerIPAddr[16] = {0},g_ServerPort[5] = {0};

uint8_t g_uSpecialNamePas[USER_PASSWORD_SIZE+1] = {0};
uint8_t g_uWifiSsidName[WIFI_SSID_NAME_MAX] = {0};
uint8_t g_uWifiNamePas[WIFI_SSID_NAME_MAX] = {0};
uint8_t g_uSampleType[ARR_SAMPLE_TYPE_SIZE] = {0};
uint8_t g_uPrintTitles[48] = {0};
uint8_t g_uInputPrintTitles[48] = {0};

uint8_t g_ReadPageIDStatus = PAGE_ONLINE;
uint8_t g_uRecAutoDownTime = 0;
uint8_t g_RecPageID = 0;                                  /* 记录当前ID页面 */
uint16_t g_uElectricValue = VOLTAGE_AD_4_VALUES;          /* 默认有电量值 */
uint8_t g_uChargeStauts = 0;   /*  */
uint8_t g_uTransparentStatus = TRANSFER_EXIT_STATION;
uint8_t g_uWifiConnect = WIFI_CONNEST_DISLINE;

uint8_t g_ShutdownError = 0;


#if DOWN_TJC_BIN
uint8_t g_uTjcFileDownload = TJC_FILE_DOWNLOAD_ON;
#else
uint8_t g_uTjcFileDownload = TJC_FILE_DOWNLOAD_OFF;       /* 开机不用下载 */
#endif


////uint8_t g_uWifiStatus = WIFI_W01_E03_OFF;
////uint8_t g_uOrdereEven = 0;
////uint8_t g_Temp = 0;
////DRV_AT24C32_TYPE* _gp_EEP = NULL;      /* Recvice EEP */
////DRV_AD7685_TYPE* _gp_AD7685 = NULL;



