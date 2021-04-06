#ifndef _FUNC_TJC4832T_H_
#define _FUNC_TJC4832T_H_ 

#include "Func_IFP_300_Drv.h"

#define TJC_USART_NUM    (_USART4_)//(_USART3_)

#define TJC_TOUCH_EVENT           (0x65)
#define TJC_PAGE_ID               (0x66)
#define TJC_TOUCH_DIT_EVENT       (0x67)
#define TJC_SLEEP_EVENT           (0x68)

#define TJC_STR_RE_EVENT          (0x70)
#define TJC_NUM_RE_EVENT          (0x71)
#define TJC_AUTO_SLEEP_EVENT      (0x86)
#define TJC_AUTO_WAKUP_EVENT      (0x87)

#define TJC_START_EVENT           (0x88)
#define TJC_SD_UPDATA_EVENT       (0x89)
#define TJC_DATA_SUCCEED_EVENT    (0xFD)
#define TJC_DATA_READY_EVENT      (0xFE)

#define TJC_INVALID_ORDER         (0x00)
#define TJC_ORDER_SUCCEED         (0x01)
#define TJC_ORDERID_INVALID       (0x02)
#define TJC_ORDERPAGE_INVALID     (0x03)

#define TJC_ORDERPIC_INVALID      (0x04)
#define TJC_ORDERWORD_INVALID     (0x05)
#define TJC_BAUDS_INVALID         (0x11)
#define TJC_CURVE_INVALID         (0x12)

#define TJC_VARIABLE_INVALID      (0x1A)
#define TJC_OPERATOR_INVALID      (0x1B)
#define TJC_ASSIGN_INVALID        (0x1C)
#define TJC_EEPROM_INVALID        (0x1D)

#define TJC_PARAM_INVALID         (0x1E)
#define TJC_IO_INVALID            (0x1F)
#define TJC_TRANMEAN_INVALID      (0x20)
#define TJC_VARLONG_INVALID       (0x23)
							      
								  
#define TJC_TOUCH_ON              (0x01)
#define TJC_TOUCH_OFF             (0x00)
//#define TJC_REGISTER_PAGE               (4)//
//#define TJC_DIS_TIME_PAGE               (10)     /* 显示时间页面 */

#define STOCK_TIMES              (20)

#define TJC_NULL_PAGE					(0)
#define TJC_INIT_PAGE					(0)
#define TJC_KEY0_PAGE                   (0)
#define TJC_KEY1_PAGE                   (1)
#define TJC_KEY2_PAGE                   (2)
#define TJC_KEY3_PAGE                   (3)
#define TJC_LOGIN_PAGE                  (4)   
#define TJC_TEST_PAGE				    (5)      /* 全血测试页面 */
#define TJC_MAIN_PAGE					(6)      /* 主界面页面 */
#define TJC_SET_PAGE                    (7)      /* 设置页面 */
#define TJC_HISTORY1_PAGE               (8)      /* 历史页面 */
#define TJC_SET_TIME_PAGE               (9)      /* 设置时间页面 */
#define TJC_CONFIG_PAGE                 (10)     /* 配置文件设置 */
#define TJC_WARN_PAGE                   (11)     /* 警告页面 */
#define TJC_WARNING_PAGE                (12)     /* 强制警告页面 */
#define TJC_ID_PAGE                     (13)     /* 读ID页面 */
#define TJC_QUICK_RESULT_PAGE           (14)     /* 显示浓度结果页面 */
#define TJC_PROMPTER_PAGE               (15)     /* 提示关机页面 */
#define TJC_FORCE_EXIT_PAGE             (16)     /* 强制退出 */
#define TJC_PASSWORD_PAGE               (17)     /* 设置密码 */
#define TJC_MORE_PAGE                   (18)     /* 用户信息 */
#define TJC_REFERENCE_PAGE              (19)     /* 参考值 */
#define TJC_AUTOTEST_PAGE               (20)     /* 自动测试 */
#define TJC_WIFI_SSID_PAGE              (21)     /* WIFI管理页 */
#define TJC_WIFI_PAS_PAGE               (22)     /* WIFI密码页 */
#define TJC_SET_SELECT_PAGE             (23)     /* 设置选择页 */
#define TJC_INSTRUMENT_PAGE             (24)     /* 功能设置页 */
#define TJC_SYSTEM_PAR_PAGE             (25)     /* 系统设置页 */
#define TJC_SERVER_CONF_PAGE            (26)     /* 服务器设置页 */
#define TJC_BLUETOOTH_PAGE              (27)     /* 蓝牙设置页 */

#define TJC_PROMPT_PAGE                 (12)     /* 提示页面 */

//#define TJC_TEST2_PAGE				    (10)     /* 其它血测试页面 */

#define TJC_SLEEP_ON        (1)
#define TJC_SLEEP_OFF       (0)

#define REF_MULTIPLE_RANGE  (100)            /* 两位小数 */

#define DEBUG_TEST          (0)
#define STANDARD_TEST       (1)

typedef struct
{
	uint8_t page_id;     //产生消息的画面ID
	uint8_t control_id;  //产生消息的控件ID
	//uint8_t status;
}TJC_CTRL_MSG,*TJC_PCTRL_MSG;

extern TJC_CTRL_MSG gp_stuTjcCtrlMsg;

uint8_t uOrderAnalysis( uint8_t uOrder,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uPageButton( uint8_t uPage,uint8_t pButton );
uint8_t	uPageIdNumber( uint8_t uPage );
uint8_t uReplyStr( uint8_t uPage,uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uReplyNum( uint8_t uPage,uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uInitButton( uint8_t pButton );
uint8_t uLoginButton( uint8_t pButton );
uint8_t uTestButton( uint8_t pButton );
uint8_t uMainButton( uint8_t pButton );
uint8_t uHistoryButton( uint8_t pButton );
uint8_t uSetButton( uint8_t pButton );
uint8_t uDisTimeButton( uint8_t pButton );
uint8_t uSetTimeButton( uint8_t pButton );
uint8_t uConfigButton( uint8_t pButton );
uint8_t uWarnButton( uint8_t pButton );
uint8_t uWarningButton( uint8_t pButton );
uint8_t uIdButton( uint8_t pButton );
uint8_t uPrompterButton( uint8_t pButton );
uint8_t uQuickResultButton( uint8_t pButton );
uint8_t uAutoTestPageButton( uint8_t pButton );
uint8_t uSelSelectPageButton( uint8_t pButton );
uint8_t uInstrumentAPageButton( uint8_t pButton );
uint8_t uSystemPageButton( uint8_t pButton );
uint8_t uServerPageButton( uint8_t pButton );
uint8_t uReferencePageButton( uint8_t pButton );
uint8_t uWifiSsidPageButton( uint8_t pButton );
uint8_t uWifiPasswordPageButton( uint8_t pButton );
uint8_t uPasswordButton( uint8_t pButton );
uint8_t uMorePageButton( uint8_t pButton );
uint8_t uForceExitButton( uint8_t pButton );
uint8_t uReplyStrRegisterButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uReplyStrLoginButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uReplyStrServerConfig( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uReplyStrMoreButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uReplyStrButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uReplyStrConfigButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uReplyStrSystemButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uReplyNumTimeButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uReplyNumRegisterButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uReplyNumLoginButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uReplyStrPassword( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uReplyStrReferenceButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uReplyStrPrompter( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uReplyStrWarn( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uReplyStrWifiSsidName( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uReplyStrWifiPassword( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uReplyNumConfigButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uReplyNumReferenceButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uReplyNumAutoTestButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uReplyNumInstrumentButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uReplyNumParameterButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uReplyNumSystemButton( uint8_t pButton,uint8_t *puOrdArr,uint8_t uSize );
uint8_t uTjc4832tTouchEnable( uint8_t uenable );
uint8_t uTjcAsciiToInt( uint8_t* msgTemp,int32_t * pu32RecTemp,uint8_t strSize );
uint8_t uTjcErrorEvent( uint8_t uEvent );
uint8_t uBluetoothPageButton( uint8_t pButton );
uint8_t uTjcErrorInvalidOrderEvent( uint8_t uEvent );

#endif
