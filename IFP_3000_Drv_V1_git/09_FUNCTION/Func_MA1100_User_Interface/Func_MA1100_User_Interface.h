#ifndef _FUNC_MA1100_USER_INTERFACE_H_
#define _FUNC_MA1100_USER_INTERFACE_H_

#include "BSP_Sys.h"
#include "Func_IFP_300_Drv.h"
#include "string.h"
#include "stdio.h"
#include "Func_MA1100_Queue.h"
#include "Func_ADHandler.h"
#include "Func_Tjc4832t.h"
//#include "Task.h"

#define INIT_PAGE					(0)
#define KEY_PAGE                    (1)
#define REGISTER_PAGE               (2)//
#define LOGIN_PAGE                  (3)      
#define MAIN_PAGE					(4)      /* 主界面页面 */
#define TEST1_PAGE				    (5)      /* 全血测试页面 */
#define WARN_PAGE                   (6)      /* 警告页面 */
#define WARNING_PAGE                (7)      /* 强制警告页面 */
#define HISTORY1_PAGE               (8)      /* 历史页面 */
#define QUICK_RESULT_PAGE           (9)      /* 显示浓度结果页面 */
#define TEST2_PAGE				    (10)     /* 其它血测试页面 */
#define ID_PAGE                     (11)     /* 读ID页面 */
#define SET1_PAGE                   (12)     /* 提示页面 */
#define SET2_PAGE                   (13)     /* 设置页面 */
#define SET3_PAGE                   (14)     /* 显示时间页面 */
#define SET4_PAGE                   (15)     /* 设置时间页面 */
#define CONFIG_PAGE                 (16)     /* 配置文件设置 */
#define STANDARD_RESULT_PAGE        (17)     /* 显示浓度结果页面 */

#define HISTORY2_PAGE               (50)
#define HISTORY3_PAGE               (50)
#define HISTORY4_PAGE               (50)
#define MORE1_PAGE                  (50)
#define MORE2_PAGE                  (50)
//#define ERROE1_PAGE				    (10)
//#define ERROE2_PAGE				    (11)
//#define BACKGROUND_PAGE				(3)
//#define KEYPWD_PAGE                 (5)
//#define TEST3_PAGE				    (16)   //(0xff)
//#define STANDARD_RESULT_PAGE        (9)

#define QC_PAGE                     (50)
//#define ID1_PAGE                    (23)



//#define READ_ID_PAGE                (18)

//#define TEST_PAGE                   (0x35)
//#define TEST4_PAGE				    (0xff);//(0x0c)//(0x0C)
//#define TEST5_PAGE				    (0x03)//(0x0C)
#define BUTTON_VALUE_CURVE          (140)
#define BUTTON_VALUE_BLUE_A_MAC     (141)
#define BUTTON_VALUE_BLUE_B_MAC     (142)
#define BUTTON_VALUE_BLUE_C_MAC     (143)
#define BUTTON_VALUE_BLUE_D_MAC     (144)
#define BUTTON_VALUE_BLUE_E_MAC     (145)
#define BUTTON_VALUE_BLUE_F_MAC     (146)
#define BUTTON_VALUE_BLUE_G_MAC     (147)
#define BUTTON_VALUE_BLUE_H_MAC     (148)
#define BUTTON_VALUE_BLUE_SCAN_AP   (149)
#define BUTTON_VALUE_SN_STR         (150)
#define BUTTON_VALUE_NO_OVER_ID     (151)
#define BUTTON_VALUE_OVER_ID        (152)
#define BUTTON_VALUE_SWITCH_ONOFF   (153)
#define BUTTON_VALUE_LANBO_BASE     (154)
#define BUTTON_VALUE_ADBAR_DIS      (155)
#define BUTTON_VALUE_SERVER_CLEAR   (156)
#define BUTTON_VALUE_TIME_CLEAR     (157)
#define BUTTON_VALUE_SYSTEM_CLEAR   (158)
#define BUTTON_VALUE_REF_CLEAR      (159)
#define BUTTON_VALUE_MORE_CLEAR     (160)
#define BUTTON_VALUE_LIS_AFFIRM     (161)
#define BUTTON_VALUE_LIS_CANCLE     (162)
#define BUTTON_VALUE_LIS_UPLOAD     (163) 
#define BUTTON_VALUE_SERVER_CONF    (164) 
#define BUTTON_VALUE_P_TITLES       (165)
#define BUTTON_VALUE_FORCE_ASS      (166)
#define BUTTON_VALUE_DIS_VER        (167)
#define BUTTON_VALUE_POST_PAGE      (168)
#define BUTTON_VALUE_COEFF          (169)
#define BUTTON_VALUE_BAR_ERR        (170)
#define BUTTON_VALUE_PARAMET_INIT   (171)
#define BUTTON_VALUE_REF_COVER      (172)
#define BUTTON_VALUE_REFERENCE_DOWN (173)
#define BUTTON_VALUE_REFERENCE_UP   (174)
#define BUTTON_VALUE_S_MORE      	(175)
#define BUTTON_VALUE_SYSTEM_CIG  	(176)
#define BUTTON_VALUE_SYSTEM_INIT    (177)
#define BUTTON_VALUE_WIFI_PAS       (178)
#define BUTTON_VALUE_WIFI_SCAN_AP   (179)
#define BUTTON_VALUE_PROM_CLEHIS    (180)
#define BUTTON_VALUE_PROM_FACTORY   (181)
#define BUTTON_VALUE_HISTORY_CLEAR  (182)
#define BUTTON_VALUE_PRINT_1BAR     (183)
#define BUTTON_VALUE_WIFI_ONOFF     (184)
#define BUTTON_VALUE_SCAN_BAR       (185)
#define BUTTON_VALUE_INSTR_INIT     (186)
#define BUTTON_VALUE_PRINT_BAR      (187)
#define BUTTON_VALUE_PRINT_AD       (188)
#define BUTTON_VALUE_AUTO_FEXIT     (189)
#define BUTTON_VALUE_AUTO_TEST      (190)
#define BUTTON_VALUE_B6REFERENCE    (191)
#define BUTTON_VALUE_B5REFERENCE    (192)
#define BUTTON_VALUE_B4REFERENCE    (193)
#define BUTTON_VALUE_B3REFERENCE    (194)
#define BUTTON_VALUE_FAMALE   	    (195)
#define BUTTON_VALUE_MALE   	    (196)
#define BUTTON_VALUE_WARN_CANCEL   	(197)
#define BUTTON_VALUE_SIDO_ROOT    	(198)
#define BUTTON_VALUE_LED_CTRL    	(199)
#define BUTTON_VALUE_REFERENCE_DIS	(200)
#define BUTTON_VALUE_USER_INFO_DIS	(201)
#define BUTTON_VALUE_AUTO_TIME		(202)
#define BUTTON_VALUE_BUZZER         (203)
#define BUTTON_VALUE_IDCARD_DOWN    (204)
#define BUTTON_VALUE_IDCARD_UP      (205)
#define BUTTON_VALUE_IDCARD_INFO    (206)
#define BUTTON_VALUE_MORE_INFO      (207)
#define BUTTON_VALUE_B1REFERENCE    (208)
#define BUTTON_VALUE_B2REFERENCE    (209)
#define BUTTON_VALUE_REFERENCE      (210)
#define BUTTON_VALUE_SPECIAL_PAS    (211)
#define BUTTON_VALUE_TEST_FEXIT     (212)
#define BUTTON_VALUE_SERUM      	(213)
#define BUTTON_VALUE_WHOLE       	(214)
#define BUTTON_VALUE_VARI_INVALID 	(215)
#define BUTTON_VALUE_TJC_START 		(216)
#define BUTTON_VALUE_SHUTDOWN  		(217)
#define BUTTON_VALUE_YEARS  		(218)
#define BUTTON_VALUE_MONTH          (219)
#define BUTTON_VALUE_DAY            (220)
#define BUTTON_VALUE_HOURS          (221)
#define BUTTON_VALUE_MINUTES        (222)
#define BUTTON_VALUE_ALL_CIG  		(223)
#define BUTTON_VALUE_BAROFFSET      (224)
#define BUTTON_VALUE_OFFSET         (225)
#define BUTTON_VALUE_GAIN           (226)
#define BUTTON_VALUE_1DENSITY       (227)
#define BUTTON_VALUE_2DENSITY       (228)
#define BUTTON_VALUE_AFFIRM         (229)
#define BUTTON_VALUE_HISTORY_PRINT  (230)
#define BUTTON_VALUE_2SUB           (231)
#define BUTTON_VALUE_2ADD           (232)
#define BUTTON_VALUE_1SUB           (233)
#define BUTTON_VALUE_1ADD           (234)
#define BUTTON_VALUE_PRINTF         (235)    
#define BUTTON_VALUE_SLEEP          (236)
#define BUTTON_VALUE_CALENDAR       (237)
#define BUTTON_VALUE_TIME           (238)
#define BUTTON_VALUE_IDRETURN       (239)
#define BUTTON_VALUE_FACTORY        (240)
#define BUTTON_VALUE_RELOGIN        (241)    //241
#define BUTTON_VALUE_MOTOR_DOWN     (242)    //242
#define BUTTON_VALUE_MOTOR_UP       (243)    //243
#define BUTTON_VALUE_HISTORY_DOWN   (244)    //247  (231)//
#define BUTTON_VALUE_HISTORY_UP     (245)    //248  (230)//
#define BUTTON_VALUE_RESET_MOTOR    (246)    //249 
#define BUTTON_VALUE_LOGIN          (247)    //253
#define BUTTON_VALUE_REGISTER       (248)    //254

//#define BUTTON_VALUE_UPGRADE        (239)
//#define BUTTON_VALUE_PRINTFA         (0xf0)    //240
//#define BUTTON_VALUE_EEPROM         (0xf4)    //244
//#define BUTTON_VALUE_QUICK1_TEST    (0xf5)    //245
//#define BUTTON_VALUE_STANDARD1_TEST (0xf6)    //246
//#define BUTTON_VALUE_READ_ID        (0xfa)    //250
//#define BUTTON_VALUE_QUICK_TEST     (0xfb)    //251
//#define BUTTON_VALUE_STANDARD_TEST  (0xfc)    //252

#define TJC_DEMARCATION_POINT       (250)

#define SPC_BUTTON_VALUE_SHUTDOWN  	(251)

#define WARN_ID_NUM                 (0x01)
#define WARNING_ID_NUM              (0x00)

#define SERVER_IP_ID_NUM            (0x00)
#define SERVER_PORT_ID_NUM          (0x02)

#define TIME_ID_4NUM                 (0x01)
#define TIME_ID_5NUM                 (0x02)
#define TIME_ID_6NUM                 (0x03)

#define AUTOTEST_ID_NUM              (0x00)
#define AUTOTEST_ID_TXT_DIS          (0x03)

#define PROMPTER_ID_TXT              (0x01)

#define WIFI_BUTTER_ID_0NUM          (0x00)
#define WIFI_BUTTER_ID_1NUM          (0x01)

#define WIFI_BUTTER_PAS_ID_0NUM      (0x00)

#define BarGauge_PAGE				1
#define CircleGauge_PAGE			2
#define Keyboard_PAGE				3

#define Setting_PAGE				5
#define Slider_PAGE					6
#define Temperture_PAGE				7
#define Text_PAGE					8
#define Waveform_PAGE				9

#define SLA_WR	       (0xee)  /*0x77*/
/* 指令列表 */
#define READ_PAGE_ID_CMD             (0x70)
#define SET_BACKLIGHT_CMD            (0x42)
#define SET_TOUCH_PANE_OPTION_CMD    (0x51)
#define CALIBRATE_TOUCH_PANE_CMD     (0x50)
#define TEST_TOUCH1_CMD              (0x04)
#define TEST_TOUCH2_CMD              (0x54)
#define GUI_LINE_CMD                 (0x4c)
#define GUI_RECTANGLE_FILL_CMD       (0x46)
#define GUI_RECTANGLE_CMD            (0x52)
#define DISPLAY_MESSAGE_CMD          (0x4d)
#define DISPLAY_STRING_CMD           (0x53)
#define GUI_CLEAN_SCREEN_CMD         (0x43)
#define DISPLAY_CUT_IMAGE_CMD        (0x4f)
#define DISPLAY_IMAGE_CMD            (0x49)
#define SET_RESET1_CMD               (0x4a)
#define SET_RESET2_CMD               (0x52)
#define SET_RESET3_CMD               (0x65)
#define SET_RESET4_CMD               (0x73)
#define SET_RESET5_CMD               (0x65)
#define SET_RESET6_CMD               (0x74)
#define SET_CONNECT_CMD              (0x48)
#define SET_NUMBER_VALUE_CMD         (0x6e)
#define SET_LABLE_VALUE_CMD          (0x74)
#define SET_EDIT_CMD                 (0x65)
#define GET_EDIT_TEXT_CMD            (0x75)
#define GET_EDIT_TEXT_KEY_CMD        (0x7c)
#define SET_SCHEDULE_CMD             (0x6f)
#define SET_UP_EDIT_BOX_CMD          (0x63)
#define SET_EDIT_BOX_CMD             (0x64)
#define UP_POINTER_CMD               (0x7a)
#define UP_SCALE_CMD                 (0x61)
#define UP_STAGE_CMD                 (0x77)
#define UP_TEMPERATURE_CMD           (0x6d)
#define UP_BATTERY_CMD               (0x79)
#define GET_WAVE_CMD                 (0x66)
#define CLEAR_WAVE_CMD               (0x76)
#define INPUT_WAVE_CMD               (0x6a)
#define UP_WAVE_CMD                  (0x6b)
#define READ_SLIDER_CMD              (0x68)
#define UP_SLIDER_CMD                (0x5f)



#define NOTIFY_TOUCH_BUTTON		0x62     /* 触摸Button返回起始字节 */
#define NOTIFY_TOUCH_CHECKBOX	0x60     /* Check Box */
#define NOTIFY_TOUCH_SLIDER		0x67     /* Slider */
#define NOTIFY_TOUCH_EDIT		0x7B	 /* Edit */

#define NOTIFY_GET_EDIT			0x75
#define NOTIFY_GET_PAGE			0x71     /* Page Instruct */
#define NOTIFY_GET_CHECKBOX		0x64
#define NOTIFY_GET_SLIDER		0x68
#define NOTIFY_GET_TOUCH_EDIT	0x7C

#define NOTIFY_SET_PAGE			0x70
#define NOTIFY_SET_NUMBER		0x6E

#define NOTIFY_SET_PROGRESS		0x6F
#define NOTIFY_SET_CHECKOUT		0x63
#define NOTIFY_SET_CIRCLEGAUGE 	0x7a
#define NOTIFY_SET_BARGAUGE 	0x61
#define NOTIFY_SET_WATERGAUGE 	0x77
#define NOTIFY_SET_THERMOMETER 	0x6d
#define NOTIFY_SET_WAVEFORM 	0x66
#define NOTIFY_SET_BATTERY 		0x79

#define NOTIFY_CLEAR_WAVEFORM 		0x76
#define NOTIFY_INSER_WAVEFORM_DATA	0x6a
#define NOTIFY_REFRESS_WAVEFORM		0x6b

/* 按键功能类型 */
#define  CHAR						0X30			/* */
#define  CLEAR						0X31
#define  BACK_SPACE					0X32
#define  SPACE 						0X33
#define  ENTER						0X34            /* 确认功能 */
#define  CHANGE_PAGE				0X35            /* 切换页面 */
#define  UPLOAD_CONTROL_ID			0X36         	/* 上传按键ID */
#define  KEYTYPE_RETURN             0X37
#define  KEYTYPE_SIGNE              0X38

#define PAGE_SUCCESS						0x6f
#define PAGE_FAILURE						0x65

#define GET_EDIT_VALUE				(0x75)	/* (0X01) */
#define GET_TOUCH_EDIT_VALUE 		(0x7c)
#define GET_READ_SUCCEED            (0x6f)

/* 按键状态 */
#define KEY_DOWN					0x44    		/*按键按下*/
#define KEY_RELEASE 				0x55			/*按键抬起*/

#define SELECT						0X53
#define UNSELECT					0X55

#define TOUCH_CMD_LEN               (6)

#define USER_NAME_PAGE                  (0x05)
#define USER_NAME_CONTROL_ID			(0x03)

#define USER_PWD_PAGE                  (0x05)
#define USER_PWD_CONTROL_ID			   (0x04)

#define LOGIN_PAGE_VER_ID			   (0x07)
#define TIME_PAGE_VER_ID			   (0x04)
#define LOGIN_PAGE_VERVIS_ID	       (0x04)

#define REG1_PWD_CONTROL_ID			   (4)
#define REG2_PWD_CONTROL_ID			   (6)
#define REG3_PWD_CONTROL_ID			   (8)

#define TIME_PAGE_1CONTROL_ID		   (0)
#define TIME_PAGE_2CONTROL_ID		   (1)
#define TIME_PAGE_3CONTROL_ID		   (2)
#define TIME_PAGE_4CONTROL_ID		   (3)
#define TIME_PAGE_5CONTROL_ID		   (4)
#define TIME_PAGE_6CONTROL_ID		   (5)

#define CONFIG_PAGE_OFFSET_ID		   (0)
#define CONFIG_PAGE_GAIN_ID		       (1)
#define CONFIG_PAGE_BAROFFSET_ID	   (2)
#define CONFIG_PAGE_SHUT_ID	           (3)
#define CONFIG_PAGE_TITLE_ID	       (0)
#define CONFIG_PAGE_LANBO_ID           (3)

#define CONFIG_PAGE_SN_ID              (0)

#define CONFIG_PAGE_COEFF_ID	       (0)

#define MORE_PAGE_USER_ID	   (0)
#define MORE_PAGE_SEX_ID	   (1)
#define MORE_PAGE_AGE_ID	   (2)

#define SERVER_PAGE_IP_ID	   (0)
#define SERVER_PAGE_PORT_ID	   (2)

#define REFERENCE_PAGE_00_TXT_ID		   (0)
#define REFERENCE_PAGE_00_TXT_NUM_ID	   (1)

#define REFERENCE_PAGE_00_MIN_ID		   (0)
#define REFERENCE_PAGE_00_MAX_ID		   (1)
#define REFERENCE_PAGE_01_MIN_ID		   (2)
#define REFERENCE_PAGE_01_MAX_ID		   (3)
#define REFERENCE_PAGE_02_MIN_ID		   (4)
#define REFERENCE_PAGE_02_MAX_ID		   (5)

#define INSTR_BT0_ID		   (0)
#define INSTR_BT1_ID		   (1)
#define INSTR_BT2_ID		   (2)
#define INSTR_BT3_ID		   (3)
#define INSTR_BT4_ID		   (4)
#define INSTR_BT5_ID		   (5)
#define INSTR_BT6_ID		   (6)
#define INSTR_BT7_ID		   (7)

#define PARAMTER_BT0_ID		   (0)
#define PARAMTER_BT1_ID		   (1)
#define PARAMTER_BT2_ID		   (2)
#define PARAMTER_BT3_ID		   (3)
#define PARAMTER_BT4_ID		   (4)
#define PARAMTER_BT5_ID		   (5)
#define PARAMTER_BT6_ID		   (6)
#define PARAMTER_BT7_ID		   (7)


#define BACK_LIGHT_1_VALUE             (0)
#define BACK_LIGHT_2_VALUE             (50)//(35)

#define PAGE_ONLINE                      (1)
#define PAGE_NOLINE                      (0)

#define DIS_MAX1_STRING                   (48)
#define DIS_MAX2_STRING                   (58)

typedef struct
{
	uint8_t cmd_type;    //命令类型
	uint8_t control_id;  //产生消息的控件ID
	uint8_t page_id;     //产生消息的画面ID
	uint8_t status;
	uint8_t key_type;    //控件类型
	uint8_t key_value;
	uint8_t cmd_tail;   //帧尾
}CTRL_MSG,*PCTRL_MSG;

typedef struct
{
	uint8_t cmd_type;    //命令类型
	uint8_t control_id;  //产生消息的控件ID
	uint8_t page_id;     //产生消息的画面ID
	uint8_t status;      //读取状态 6f成功
	uint8_t cmd_fixed;   //固定值
	uint8_t str_size;    //字符串长度
	uint8_t param[57];   //可变长度参数，最多个字节	
}EDIT_MSG,*PEDIT_MSG;

uint8_t ProcessMessage( PCTRL_MSG msg, uint16_t size );
void UpdateUI( uint8_t* page_Id );
void UpdateSpcUI( uint8_t* page_Id );
void vUpdateUISend( uint8_t uTempOrder);


void SetNumberValue(uint8_t page_id,uint8_t control_id,uint16_t number);
void SetEditValue(uint8_t page_id,uint8_t control_id,uint8_t *str);
void GetEditValue(uint8_t page_id,uint8_t control_id);
void GetTouchEditValue(uint8_t page_id,uint8_t control_id);
void SetProgressbarValue(uint8_t page_id,uint8_t control_id,uint8_t value);
void SetCheckboxValue(uint8_t page_id,uint8_t control_id,uint8_t value);
void GetCheckboxValue(uint8_t page_id,uint8_t control_id);
void SetCircleGaugeValue(uint8_t page_id,uint8_t control_id,uint16_t value);
void SetBarGaugeValue(uint8_t page_id,uint8_t control_id,uint16_t value);
void SetWaterGaugeValue(uint8_t page_id,uint8_t control_id,uint16_t value);
void SetThermometerValue(uint8_t page_id,uint8_t control_id,uint16_t value);	
void SetBatteryValue(uint8_t page_id,uint8_t control_id,uint16_t value);
void SetWaveformValue(uint8_t page_id,uint8_t control_id,uint8_t channelNo,uint8_t value);
void WaveformDataClear(uint8_t page_id,uint8_t control_id);
void WaveformDataInsert(uint8_t page_id,uint8_t control_id,uint8_t channelNo,uint8_t value);
void WaveformDataRefress(uint8_t page_id,uint8_t control_id,uint8_t channelNo);
void GetSliderValue(uint8_t page_id,uint8_t control_id);
void SetSliderValue(uint8_t page_id,uint8_t control_id,uint8_t value);

void SetLableValue(uint8_t page_id,uint8_t control_id,uint8_t *str);
void SetPage(uint8_t page_id);
uint8_t ISendByte(uint8_t *p,uint8_t len);
unsigned char IRcvByte(void);
void Add_Data(uint8_t c);
void Begin_Cmd( void );
void SetBackLight(uint8_t light_level);
void SetTouchPaneOption(uint8_t enbale);
void CalibrateTouchPane(void);
void TestTouchPane(uint8_t enbale);
void GUI_Line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,uint16_t ForeColor);
void GUI_RectangleFill(uint16_t x0, uint16_t y0, uint16_t x1,uint16_t y1,uint16_t ForeColor);
void GUI_Rectangle(uint16_t x0, uint16_t y0, uint16_t x1,uint16_t y1 ,uint16_t ForeColor);
void Display_Message(uint8_t FontSize,uint8_t time,uint8_t *strings );
void Display_String(uint16_t x, uint16_t y,uint8_t DisplayType,uint8_t FontSize,uint8_t ImageNo,uint16_t BackColor,uint16_t ForeColor, uint8_t *strings );
void GUI_CleanScreen(uint16_t color);
void DisplayCut_Image(uint16_t image_x,uint16_t image_y,uint16_t image_w, uint16_t image_h,uint8_t  image_id);
void Display_Image(uint16_t x,uint16_t y,uint8_t image_id);
void SetReset(void);
void SetConnect(void);
void ReadPageConnect(void);

uint8_t NotifyGetPage(uint8_t page_id,uint8_t status);
uint8_t NotifySetPage(uint8_t status);
uint8_t NotifyTouchButton(uint8_t page_id, uint8_t control_id, uint8_t  state,uint8_t type,uint8_t value);
//uint8_t NotifyTouchCheckbox(uint8_t page_id, uint8_t control_id, uint8_t  state,uint8_t type,uint8_t value);
uint8_t NotifyTouchCheckbox(uint8_t page_id, uint8_t control_id, uint8_t  state,uint8_t type,uint8_t value);
uint8_t NotifyGetCheckbox(uint8_t page_id, uint8_t control_id, uint8_t  state,uint8_t type,uint8_t value);
uint8_t NotifyTouchSlider(uint8_t page_id, uint8_t control_id, uint8_t  state,uint8_t type,uint8_t value);
uint8_t NotifyTouchEdit(uint8_t page_id, uint8_t control_id, uint8_t  state,uint8_t type,uint8_t value);
uint8_t NotifyGetEdit(PEDIT_MSG msg, uint16_t size);
uint8_t NotifyGetTouchEdit(PEDIT_MSG msg, uint16_t size);
uint8_t uGetTouchEditPage( uint8_t page_id, uint8_t control_id );
//uint8_t uAsciiToInt( PEDIT_MSG msgTemp,uint32_t * pu32RecTemp );
uint8_t uGetEditTime( uint8_t umsgID,PEDIT_MSG msgTemp );
uint8_t uGetEditFigInfo( uint8_t umsgID,PEDIT_MSG msgTemp );
uint8_t uGetTouchEditControl( uint8_t control_id );
uint8_t NotifyGetSlider(uint8_t page_id, uint8_t control_id, uint8_t  state,uint8_t type,uint8_t value);
uint8_t NotifyLable(uint8_t page_id, uint8_t control_id,uint8_t status);
uint8_t NotifyNumber(uint8_t page_id, uint8_t control_id,uint8_t status);


//void SendStrings(const char *str);

#endif
