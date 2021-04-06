#ifndef _FUNC_MA1100_QUEUE_H_
#define _FUNC_MA1100_QUEUE_H_

#include "BSP_Sys.h"
#include "Func_IFP_300_Drv.h"
#include "Func_MA1100_User_Interface.h"
#include "string.h"
#include "stdio.h"

#define CMD_MAX_SIZE   65        /*!<单条指令大小，根据需要调整，尽量设置大一些*/
#define QUEUE_MAX_SIZE 128       /*!< 指令接收缓冲区大小，根据需要调整，尽量设置大一些*/

#define CMD_DATA_LENGTH		6


extern uint8_t g_Cmd_Buffer[CMD_MAX_SIZE];
	
typedef struct{
	uint16_t head;
	uint16_t tail;
	uint8_t data[QUEUE_MAX_SIZE];	
}QUEUE;

void Queue_Reset( void );
void Queue_Push(uint8_t udata);
static void Queue_Pop(uint8_t* udata);
static uint16_t Queue_Size( void );
uint16_t Queue_Find_Cmd(uint8_t *buffer,uint16_t buf_len);


#endif
