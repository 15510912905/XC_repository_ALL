#ifndef _FUNC_CONFIG_H_
#define _FUNC_CONFIG_H_

#define CONFIG_DUBUG_TEXT                 (0)                /* 常用调试开关 */
									     
#define MAX5402_CHOISE                    (0)
#define P25Q32H_CHOISE                    (0)
#define SEM_MUTEX_CHOISE                  (1)                /* 信号量开关 */
#define CONFIG_DIT_SCAN                   (1)		         /* 扫描点数选择 */							     
#define DOWN_TJC_BIN                      (0)                /* 暂时无用 */
#define TJC_ONLY_EN                       (0)                /* 只使用英文 */
#define BAR_SCAN_EN                       (0)                /* 条码扫描关闭 */
#define TJC_REPORT_ERROR                  (0)                /* 屏幕报错开关 */

#define STORT_STL                         (0)                /* (1)run out of memory */

#define DEBUH_POWER                       (1)//(0)//(1)
#define DEBUH_UART1                       (1)//(0)//(1)      /* 串口1控制总开关 */
#define DEBUH_UART2                       (1)//(0)//(1)      /* 串口2控制总开关 */
#define DEBUH_UART3                       (1)//(0)//(1)      /* 串口3控制总开关 */
#define DEBUH_UART4                       (1)//(0)//(1)      /* 串口4控制总开关 */
								         
#define PRIVATE_ADC_UART1                 (1)//(0)//(1)      /* 关于荧光扫描的打印 */
#define PRIVATE_BAR_UART1                 (1)//(0)//(1)      /* 关于条码打印 */
#define HINT_BARCODE_CHECK                (1)                /* 条码检查提示开关 */

#define PRIVATE_ELECTRIC_TJC              (0)                /* 调试电量开关 */
#define PRIVATE_REALTIME_UART1            (0)//(0)//(1)      /* 调试RTC打印 */
#define PRIVATE_SPCIAL_AD_UART1           (0)                /* 荧光采集原始数据调试 */

#define EXE_SUCCEED                       (0)
#define EXE_FAILED                        (1)

#define USER_RAND                         (0)                /* 型检测试随机数算浓度 */
#define READCARD_DECTECT                  (1)                /* 卡条到位检查开关 */
#define WIFI_AUTO_UP                      (0)                /* WIFI自动上传LIS数据 */ 

#define TITLES_PRINT_NULL                 (0)                /* 打印抬头开关 */
#define ERASE_SECTOR_CONFIG               (0)                /* 擦除配置信息开关 */

#if CONFIG_DUBUG_TEXT
	#define PRIVATE_UART1                 (1)//(0)//(1)
	#define PRIVATE_SPCIAL_UART1          (1)//(0)//(1)
	#define PRIVATE_ELECTRIC_UART1        (1)	
	#define PRIVATE_WIFIDUG_UART1         (1)
	#define TEST_STACK_ON                 (1)
	#define PRIVATE_SPCIAL_BAR_UART1      (1)
#else
	#define PRIVATE_UART1                 (0)//(0)//(1)
	#define PRIVATE_SPCIAL_UART1          (0)//(0)//(1)
	#define PRIVATE_ELECTRIC_UART1        (0)
	#define PRIVATE_WIFIDUG_UART1         (0)
	#define TEST_STACK_ON                 (0)
	#define PRIVATE_SPCIAL_BAR_UART1      (0)
#endif

#endif
	
