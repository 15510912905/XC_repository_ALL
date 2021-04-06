#ifndef _FUNC_LogIn_H_
#define _FUNC_LogIn_H_

//#include "Func_XC2000_Liquid_Pressure.h"
#include "stdlib.h"
#include "stdint.h"
#include "Drv_Flash_P25Q32h.h"

#define LOGIN_CODE                      (0)
							          
#define EEP_USER_NUMBER_ARR             (0x0040)
#define EEP_USER_BASE_ADDR              (0x0060)

/* ĿǰоƬ��16M 4096���� */
#define SPIFLASH_SECTOR_BASE_ADDR       (16)
#define SPIFLASH_PAGE_BASE_ADDR         (SPIFLASH_SECTOR_BASE_ADDR*(SPIFLASH_PAGE+1)) /* //(SPIFLASH_PAGE+1) */
                                        
#define SPIFLASH_CONFIG_FILE_BASE_ADDR  (0*SPIFLASH_PAGE_BASE_ADDR)      /* ���������ļ� ����ʱֻ��Ҫ�����  */

#define SPIFLASH_USER_NUMBER_ADRR       (1*SPIFLASH_PAGE_BASE_ADDR)      /* �û��� */
#define SPIFLASH_AUTO_REMEM_ADRR        (2*SPIFLASH_PAGE_BASE_ADDR)      /* ����״̬ */
#define SPIFLASH_USER_BASE_ADDR         (3*SPIFLASH_PAGE_BASE_ADDR)      /* ��¼��Ϣ */
#define SPIFLASH_USER_MORE_ADDR         (5*SPIFLASH_PAGE_BASE_ADDR)      /* �û���Ϣ */
#define SPIFLASH_SERIAL_BASE_ADDR       (6*SPIFLASH_PAGE_BASE_ADDR)	     /* ��ˮ�� */ 
#define SPIFLASH_P_TITLES_BASE_ADDR     (7*SPIFLASH_PAGE_BASE_ADDR)	     /* ��ӡ���� */ 

#define SPIFLASH_ID_NUM_BASE            (4*SPIFLASH_PAGE_BASE_ADDR)      /* �ǻ�׼ ����ҳ�� */
#define SPIFLASH_IDA_BASE_ADDR          (100*SPIFLASH_PAGE_BASE_ADDR)    /* ID������ */ //(30*SPIFLASH_PAGE_BASE_ADDR)
#define SPIFLASH_IDB_BASE_ADDR          (101*SPIFLASH_PAGE_BASE_ADDR)    /* ID������ */
#define SPIFLASH_IDC_BASE_ADDR          (102*SPIFLASH_PAGE_BASE_ADDR)    /* ID������ */

#define SPIFLASH_USER_REFER_ADDR        (200*SPIFLASH_PAGE_BASE_ADDR)    /* �ο���Χ */

#define SPIFLASH_START_BASE_ADDR        (300*SPIFLASH_PAGE_BASE_ADDR)    /* ��ʷ���� 9+6*4+1*4 */
#define SPIFLASH_DENSITY_BASE_ADDR      (301*SPIFLASH_PAGE_BASE_ADDR)    /* ��ʷ���� */

#define P25Q32H_CLEAR_SECTOR            ((SPIFLASH_DENSITY_BASE_ADDR/SPIFLASH_PAGE_BASE_ADDR)+1)

#define TOUCH_ON                        (0x01)
#define TOUCH_OFF                       (0x00)
				                        
#define POWER_ON                        (0x00)
#define POWER_OFF                       (0x01)

#define POWER_FORCE                     (0x01)
#define POWER_WARN                      (0x00)

#define POWER_FORCE_30_SECOND (30)
#define POWER_FORCE_15_SECOND (15)
#define POWER_FORCE_05_SECOND (5)
#define POWER_FORCE_03_SECOND (3)

#define RIGISTER_ID_0NUM            (0)
#define RIGISTER_ID_1NUM            (1)
#define RIGISTER_ID_2NUM            (2)
#define RIGISTER_CID_0NUM            (0)
#define RIGISTER_CID_1NUM            (1)
#define RIGISTER_CID_1NUM            (1)

#define LOGIN_CID_0NUM               (0)
#define LOGIN_VAL_1NUM               (1)

#define LOGIN_ID_0NUM            (0)
#define LOGIN_ID_1NUM            (1)
#define LOGIN_ID_4NUM            (4)
#define TJC_PRESS_DOWN           (1)
#define TJC_PUT_UP               (0)

#define LOGIN_ENTER              (1)
#define LOGIN_EXIT               (0)

#define MAX_USER_ID              (3)
#define USER_FILE_SIZE           (1)
#define USER_ID_SIZE             (1)
#define USER_NAME_SIZE           (9)
#define USER_PASSWORD_SIZE       (6)
#define USER_DATA_SIZE           (USER_ID_SIZE+USER_NAME_SIZE+USER_PASSWORD_SIZE)

#define PWD_SET 1          //�״�ʹ�����ʱ��������
#define PWD_ALTER 2        //�޸�����
#define PWD_CHECK 3        //ʹ��������޸�����ʱȷ������
#define PWD_ERROR_ALL_TIMES (255)  //��������Ĵ������
#define PWD_ERROR_TIMES 4  //��������Ĵ������

#define PWD_LEN (6)  //������󳤶�

#pragma pack(1)	/*��1�ֽڶ���*/
//�û���Ϣ�ṹ��
typedef struct _STU{
	uint8_t id;             //�û�ID
	uint8_t username[USER_NAME_SIZE];    //�û���
	uint8_t password[USER_PASSWORD_SIZE];    //����
}STU;

typedef struct _AUTO_REMEMBER{
	uint8_t uauto;              //�Զ���½
	uint8_t uremember;          //��ס����
	uint8_t uloginstatus; 
}AUTO_REMEMBER;

//����ڵ�
typedef struct _NODE{
	STU data;
	struct _NODE *next;
}NODE;

//����ͷ���
typedef struct{
	int num;  //ѧ������
	NODE *link;  //����ָ��
}HEADER;

extern AUTO_REMEMBER g_stuAutoRemenber;

uint8_t uUserPasswordInit( void );

//long getFileSize();
uint8_t getFileSize( void );
AUTO_REMEMBER* getPasswordStatus( AUTO_REMEMBER* pstuAutoRem );
uint8_t remPasswordStatus( AUTO_REMEMBER* pstuAutoRem );
void vLogInInit( void );
void vLogNoPwdInInit( void );
void setPwd(int flag);
int checkPwd(int flag);
void getpwd(char *pwd, int pwdlen);
void showAllStu( void );  //administrator
void addUserInfo( void );
void deleteUserInfo( void );
void alterUserInfo( void );
void getUserID(uint8_t* id);
uint8_t checkUserID(uint8_t stuID);
void getUserName( uint8_t name[] );
uint8_t checkUserName(uint8_t name[]);
void getUserPassword( uint8_t password[] );
uint8_t checkUserPassword(uint8_t password[]);
void updateFile( void );
uint8_t *findUserByName( uint8_t *uName,uint8_t *getPwd );
uint8_t vShutDown( void );
uint8_t vPromptShutDown( uint8_t uPrompt,uint8_t uSecond );
uint8_t vPromptElectricQuantity( void );
uint8_t vBackgrounderShutDown( uint8_t* uSecond );
uint8_t vForceWarn( void );
uint8_t vShutDownPrompter( void );
uint8_t vStartingUp( void );
uint8_t uLoginBottonValue( void );
uint8_t uResetLoginBottonValue( void );
void vClassifyShutdown( void );

#endif
