#ifndef _FUNC_ERROR_H_
#define _FUNC_ERROR_H_

#include "Func_IFP_300_Drv.h"
#include "Func_ADHandler.h"
#include "Global_Variable.h"

#define ERROE001_CODE     ("001")   //"25Q64 Check Failed!"//"Please Check!      "
#define ERROE002_CODE     ("002")   //"RTC ERROR!" //"RTC Trying...");	
#define ERROE003_CODE     ("Password")//("003")   //��¼���� 1s�Ӿ���
#define ERROE004_CODE     ("004")   //��¼���� 1���ӵȴ�
#define ERROE005_CODE     ("005")   //û��ID��
#define ERROE006_CODE     ("006")   //ID���ݴ���
#define ERROE007_CODE     ("007")   //���벻��ȷ
#define ERROE008_CODE     ("008")   //����ʱ�����ݲ���
#define ERROE009_CODE     ("009")   //�����������ݲ��Ϸ�
#define ERROE010_CODE     ("010")   //�Ժ�����



#pragma pack(1)	/*��1�ֽڶ���*/


uint8_t ErrorHandler( void );
	
#endif
	
