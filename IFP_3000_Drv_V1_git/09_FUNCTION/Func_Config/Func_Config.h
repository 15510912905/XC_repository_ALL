#ifndef _FUNC_CONFIG_H_
#define _FUNC_CONFIG_H_

#define CONFIG_DUBUG_TEXT                 (0)                /* ���õ��Կ��� */
									     
#define MAX5402_CHOISE                    (0)
#define P25Q32H_CHOISE                    (0)
#define SEM_MUTEX_CHOISE                  (1)                /* �ź������� */
#define CONFIG_DIT_SCAN                   (1)		         /* ɨ�����ѡ�� */							     
#define DOWN_TJC_BIN                      (0)                /* ��ʱ���� */
#define TJC_ONLY_EN                       (0)                /* ֻʹ��Ӣ�� */
#define BAR_SCAN_EN                       (0)                /* ����ɨ��ر� */
#define TJC_REPORT_ERROR                  (0)                /* ��Ļ������ */

#define STORT_STL                         (0)                /* (1)run out of memory */

#define DEBUH_POWER                       (1)//(0)//(1)
#define DEBUH_UART1                       (1)//(0)//(1)      /* ����1�����ܿ��� */
#define DEBUH_UART2                       (1)//(0)//(1)      /* ����2�����ܿ��� */
#define DEBUH_UART3                       (1)//(0)//(1)      /* ����3�����ܿ��� */
#define DEBUH_UART4                       (1)//(0)//(1)      /* ����4�����ܿ��� */
								         
#define PRIVATE_ADC_UART1                 (1)//(0)//(1)      /* ����ӫ��ɨ��Ĵ�ӡ */
#define PRIVATE_BAR_UART1                 (1)//(0)//(1)      /* ���������ӡ */
#define HINT_BARCODE_CHECK                (1)                /* ��������ʾ���� */

#define PRIVATE_ELECTRIC_TJC              (0)                /* ���Ե������� */
#define PRIVATE_REALTIME_UART1            (0)//(0)//(1)      /* ����RTC��ӡ */
#define PRIVATE_SPCIAL_AD_UART1           (0)                /* ӫ��ɼ�ԭʼ���ݵ��� */

#define EXE_SUCCEED                       (0)
#define EXE_FAILED                        (1)

#define USER_RAND                         (0)                /* �ͼ�����������Ũ�� */
#define READCARD_DECTECT                  (1)                /* ������λ��鿪�� */
#define WIFI_AUTO_UP                      (0)                /* WIFI�Զ��ϴ�LIS���� */ 

#define TITLES_PRINT_NULL                 (0)                /* ��ӡ̧ͷ���� */
#define ERASE_SECTOR_CONFIG               (0)                /* ����������Ϣ���� */

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
	
