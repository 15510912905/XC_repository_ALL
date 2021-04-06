#ifndef _FUNC_CONFIG_H_
#define _FUNC_CONFIG_H_

#define CONFIG_DUBUG_TEXT                 (0)
									     
#define MAX5402_CHOISE                    (0)
#define P25Q32H_CHOISE                    (0)
#define SEM_MUTEX_CHOISE                  (1)
#define CONFIG_DIT_SCAN                   (1)									     
#define DOWN_TJC_BIN                      (0)

#define STORT_STL                         (0)/* (1)run out of memory */

#define DEBUH_POWER                       (1)//(0)//(1)
#define DEBUH_UART1                       (0)//(0)//(1)
#define DEBUH_UART2                       (1)//(0)//(1)
#define DEBUH_UART3                       (1)//(0)//(1)
#define DEBUH_UART4                       (0)//(0)//(1)
								         
#define PRIVATE_ADC_UART1                 (1)//(0)//(1)
#define PRIVATE_BAR_UART1                 (1)//(0)//(1)

#define PRIVATE_ELECTRIC_TJC              (0)
#define PRIVATE_REALTIME_UART1            (0)//(0)//(1)
#define PRIVATE_SPCIAL_AD_UART1           (0)

#define EXE_SUCCEED                       (0)
#define EXE_FAILED                        (1)

#define USER_RAND                         (0)
#define READCARD_DECTECT                  (1)
#define WIFI_AUTO_UP                      (0)

#define TITLES_PRINT_NULL                 (0)
#define ERASE_SECTOR_CONFIG               (0)

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
	
