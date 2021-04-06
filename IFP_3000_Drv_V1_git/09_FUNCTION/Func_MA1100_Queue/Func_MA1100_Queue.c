#include "Func_MA1100_Queue.h"

static QUEUE g_Que = {0,0,0};
static uint16_t g_Cmd_Pos = 0;
uint8_t g_Cmd_Buffer[CMD_MAX_SIZE] = {0};

/* 复位循环队列 */
void Queue_Reset( void )
{
	g_Que.head = g_Que.tail = 0;
	g_Cmd_Pos =  0;
}

/* 压栈 */
void Queue_Push(uint8_t udata)
{
	uint16_t pos = (g_Que.head+1)%QUEUE_MAX_SIZE;
	if(pos!=g_Que.tail){   /*非满状态*/	
		g_Que.data[g_Que.head] = udata;
		g_Que.head = pos;
	}
}

/* 出栈 */
static void Queue_Pop(uint8_t* udata)
{
	if(g_Que.tail!=g_Que.head){ //非空状态	
		*udata = g_Que.data[g_Que.tail];
		g_Que.tail = (g_Que.tail+1)%QUEUE_MAX_SIZE;
	}
}

/*  */
static uint16_t Queue_Size( void )
{
	return ((g_Que.head+QUEUE_MAX_SIZE-g_Que.tail)%QUEUE_MAX_SIZE);
}

/* GetInstruct Optimize */
uint16_t Queue_Find_Cmd(uint8_t *buffer,uint16_t buf_len)
{
	uint16_t CmdSize = 0;
	uint8_t Data = 0;
	uint8_t Cmd_Backup=0;
	uint8_t Cmd_Length=0;
	
	Cmd_Length = CMD_DATA_LENGTH-1;
	
	
	while( Queue_Size()>0 ){
		/*取一个数据*/
		Queue_Pop( &Data );

		if( (g_Cmd_Pos==0)&&(Data!=NOTIFY_TOUCH_BUTTON) &&(Data!=NOTIFY_TOUCH_CHECKBOX)&&(Data!=NOTIFY_TOUCH_SLIDER)
		    &&(Data!= NOTIFY_GET_EDIT)&&(Data!=NOTIFY_GET_PAGE)&&(Data!=NOTIFY_GET_CHECKBOX)&&(Data!=NOTIFY_GET_SLIDER)
		    &&(Data!=NOTIFY_TOUCH_EDIT)&&(Data!=NOTIFY_GET_TOUCH_EDIT) ){
		    continue;
		}

		if(g_Cmd_Pos<buf_len){  /* 防止缓冲区溢出 */		
			if(g_Cmd_Pos ==0){
				Cmd_Backup = Data;
			}
				
			if(g_Cmd_Pos ==(CMD_DATA_LENGTH-1)){
				 if(Cmd_Backup == NOTIFY_GET_EDIT ||Cmd_Backup == NOTIFY_GET_TOUCH_EDIT){
					Cmd_Length = CMD_DATA_LENGTH+ Data-1;
				 }
						
			}

			if(g_Cmd_Pos > (CMD_MAX_SIZE-1)){  /* Prevent Overflow */			
				g_Cmd_Pos =0;
				Cmd_Backup = 0;
			}
		
			buffer[g_Cmd_Pos++] = Data;
		}

		//
		if(g_Cmd_Pos>Cmd_Length){
			CmdSize = g_Cmd_Pos;
			g_Cmd_Pos = 0;
			return CmdSize;
		}
	}

	return 0;/* 没有形成完整的一帧 */
}
