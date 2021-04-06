#include "drv_mlx90614.h"

/*******************************************************************************
* Function Name  : Mlx90614_Configuration
* Description    : Mlx90614_Configuration
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Mlx96014_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin = SMBUS_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SMBUS_SDA_PORT,&GPIO_InitStructure);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin = SMBUS_SCK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SMBUS_SCK_PORT,&GPIO_InitStructure);

	SDA_H;
	SCL_H;
}

/*******************************************************************************
* Function Name  : SMBus_StartBit
* Description    : Generate START condition on SMBus
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SMBus_StartBit(void)
{
	SDA_OUTPUT;
	
	SDA_H;                // Set SDA line
	SCL_H;                
	SMBus_Delay(20);      // Wait a few microseconds
	SDA_L;                // Clear SDA line
	SMBus_Delay(20);      // Generate bus free time between Stop  
	SCL_L;                // Clear SCK line
}

/*******************************************************************************
* Function Name  : SMBus_StopBit
* Description    : Generate STOP condition on SMBus
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void SMBus_StopBit(void)
{
	SDA_OUTPUT;
	
	SCL_L;                // Clear SCK line
	SDA_L; 
	SMBus_Delay(20);      // Wait a few microseconds         
	SCL_H;                // Set SCK line
	SDA_H;                // Set SDA line
	SMBus_Delay(20);      // Stop condition setup time(Tsu:sto=4.0us min)
}
/*******************************************************************************
* Function Name  : SMBus_SendByte
* Description    : Send a byte on SMBus
* Input          : Tx_buffer
* Output         : None
* Return         : Ack_bit
*******************************************************************************/

uint8_t SMBus_SendByte(uint8_t data)
{
	uint8_t Bit_counter;
	uint8_t Ack_bit;
	
	SDA_OUTPUT;
	SCL_L;
	for(Bit_counter=8; Bit_counter; Bit_counter--){
		if (data&0x80){
		   SDA_H;      // If the current bit of Tx_buffer is 1 set bit_out
		}else{
			SDA_L;      // else clear bit_out
		}
			
		data<<=1;                    // Get next bit for checking
		SMBus_Delay(1);
		SCL_H;
		SMBus_Delay(20);
		SCL_L;
		SMBus_Delay(20);
	}
	Ack_bit = SMBus_ReceiveBit();           // Get acknowledgment bit
		
    return Ack_bit;

}
/*******************************************************************************
* Function Name  : SMBus_SendBit
* Description    : Send a bit on SMBus
* Input          : bit_out
* Output         : None
* Return         : None
*******************************************************************************/
void SMBus_SendBit(uint8_t bit_out)
{
	if(!bit_out){	
		SCL_L;
		SDA_OUTPUT;
		SDA_L;
		SMBus_Delay(20);
		SCL_H;
		SMBus_Delay(20);
		SCL_L;
	}else{
		SCL_L;
		SDA_OUTPUT;
		SDA_H;
		SMBus_Delay(20);
		SCL_H;
		SMBus_Delay(20);
		SCL_L;
	}
}
/*******************************************************************************
* Function Name  : SMBus_ReceiveBit
* Description    : Receive a bit on SMBus
* Input          : None
* Output         : None
* Return         : recv_bit
*******************************************************************************/
uint8_t SMBus_ReceiveBit(void)
{
	uint16_t err_t;
	
	SDA_INPUT;
	SDA_H;
	SMBus_Delay(4);
	SCL_H;
	SMBus_Delay(4);
	while(GPIO_ReadInputDataBit(SMBUS_SDA_PORT,SMBUS_SDA_PIN)){
		err_t++;
		if(err_t>UCEERTIME){
			SMBus_StopBit();
			return 1;
		}
	}
	SCL_L;
	
	return 0;
}

/*******************************************************************************
* Function Name  : SMBus_ReceiveByte
* Description    : Receive a byte on SMBus
* Input          : ack_nack
* Output         : None
* Return         : RX_buffer
*******************************************************************************/
uint8_t SMBus_ReceiveByte(uint8_t ack_nack)
{
    uint8_t RX_buffer;
    uint8_t Bit_Counter;
	
	SDA_INPUT;
    for(Bit_Counter=8; Bit_Counter; Bit_Counter--){
		SCL_L;
		SMBus_Delay(20);
		SCL_H;
		RX_buffer = (RX_buffer<<1)|GPIO_ReadInputDataBit(SMBUS_SDA_PORT,SMBUS_SDA_PIN);		
		SMBus_Delay(19);
	}
    SMBus_SendBit(ack_nack);           // Sends acknowledgment bit
	
    return RX_buffer;
}

/*******************************************************************************
* Function Name  : SMBus_Delay
* Description    : ??  ?????1us
* Input          : time
* Output         : None
* Return         : None
*******************************************************************************/
void SMBus_Delay(uint16_t time)
{
    uint16_t i, j;
    for (i=0; i<4; i++){
        for (j=0; j<time; j++);
    }
}

/*******************************************************************************
 * Function Name  : SMBus_ReadMemory
 * Description    : READ DATA FROM RAM/EEPROM
 * Input          : slaveAddress, command
 * Output         : None
 * Return         : Data
*******************************************************************************/
//uint16_t SMBus_ReadMemory(uint8_t slaveAddress, uint8_t command)
//{
//    uint16_t data;               // Data storage (DataH:DataL)
//    uint8_t Pec;                 // PEC byte storage
//    uint8_t DataL=0;             // Low data byte storage
//    uint8_t DataH=0;             // High data byte storage
//    uint8_t arr[6];              // Buffer for the sent bytes
//    uint8_t PecReg;              // Calculated PEC byte storage
//    uint8_t ErrorCounter;        // Defines the number of the attempts for communication with MLX90614

//    ErrorCounter=0x00;                                // Initialising of ErrorCounter
//    slaveAddress <<= 1;        //2-7 slave address

//repeat:
//        SMBus_StopBit();                //If slave send NACK stop comunication
//        --ErrorCounter;                 //Pre-decrement ErrorCounter
//        if(!ErrorCounter){               //ErrorCounter=0?    
//            //break;                      //Yes,go out from do-while{}
//        }

//        SMBus_StartBit();               //Start condition
//        if(SMBus_SendByte(slaveAddress)){
//            goto repeat;               //Repeat comunication again
//        }
//        if(SMBus_SendByte(command)){
//            goto repeat;             //Repeat comunication again
//        }

//        SMBus_StartBit();                //Repeated Start condition
//        if(SMBus_SendByte(slaveAddress+1)){
//            goto repeat;           //Repeat comunication again
//        }

//        DataL = SMBus_ReceiveByte(ACK);   //Read low data,master must send ACK
//        DataH = SMBus_ReceiveByte(ACK);   //Read high data,master must send ACK
//        Pec = SMBus_ReceiveByte(NACK);    //Read PEC byte, master must send NACK
//        SMBus_StopBit();                  //Stop condition

//        arr[5] = slaveAddress;
//        arr[4] = command;
//        arr[3] = slaveAddress+1;         //Load array arr
//        arr[2] = DataL;
//        arr[1] = DataH;
//        arr[0] = 0;
//		
//        PecReg=PEC_Calculation(arr);     //Calculate CRC
// // }
//		
// // while(PecReg != Pec);                //If received and calculated CRC are equal go out from do-while{}
//	if( PecReg==Pec ){
//	
//	}
//	data = (DataH<<8) | DataL;           //data=DataH:DataL
//		
//    return data;
//}
uint16_t SMBus_ReadMemory(uint8_t slaveAddress, uint8_t command)
{
    uint16_t data;               // Data storage (DataH:DataL)
    uint8_t Pec;                 // PEC byte storage
    uint8_t DataL=0;             // Low data byte storage
    uint8_t DataH=0;             // High data byte storage
    uint8_t arr[6];              // Buffer for the sent bytes
    uint8_t PecReg;              // Calculated PEC byte storage
    uint8_t ErrorCounter;        // Defines the number of the attempts for communication with MLX90614

    ErrorCounter=0x00;                                // Initialising of ErrorCounter
    slaveAddress <<= 1;        //2-7 slave address

	SMBus_StopBit();                //If slave send NACK stop comunication
	--ErrorCounter;                 //Pre-decrement ErrorCounter
	if(!ErrorCounter){               //ErrorCounter=0?    
		//break;                      //Yes,go out from do-while{}
	}

//	WriteIDTou8Arr();
	SMBus_StartBit();               //Start condition
	if(SMBus_SendByte(slaveAddress)){
		return 0xffff;
	}
	if(SMBus_SendByte(command)){
		return 0xffff;
	}

	SMBus_StartBit();                //Repeated Start condition
	if(SMBus_SendByte(slaveAddress+1)){
		return 0xffff;
	}

	DataL = SMBus_ReceiveByte(ACK);   //Read low data,master must send ACK
	DataH = SMBus_ReceiveByte(ACK);   //Read high data,master must send ACK
	Pec = SMBus_ReceiveByte(NACK);    //Read PEC byte, master must send NACK
	SMBus_StopBit();                  //Stop condition

	arr[5] = slaveAddress;
	arr[4] = command;
	arr[3] = slaveAddress+1;         //Load array arr
	arr[2] = DataL;
	arr[1] = DataH;
	arr[0] = 0;	
	PecReg=PEC_Calculation(arr);     //Calculate CRC

	if( PecReg==Pec ){
	
	}
	data = (DataH<<8) | DataL;           //data=DataH:DataL
		
    return data;
}

/*******************************************************************************
* Function Name  : PEC_calculation
* Description    : Calculates the PEC of received bytes
* Input          : pec[]
* Output         : None
* Return         : pec[0]-this byte contains calculated crc value
*******************************************************************************/
uint8_t PEC_Calculation(uint8_t pec[])
{
    uint8_t crc[6];
    uint8_t BitPosition=47;
    uint8_t shift;
    uint8_t i;
    uint8_t j;
    uint8_t temp;

    do{
        crc[5]=0;
        crc[4]=0;
        crc[3]=0;
        crc[2]=0;
        crc[1]=0x01;
        crc[0]=0x07;
        /*Set maximum bit position at 47 ( six bytes byte5...byte0,MSbit=47)*/
        BitPosition=47;
        /*Set shift position at 0*/
        shift=0;
        /*Find first "1" in the transmited message beginning from the MSByte byte5*/
        i=5;
        j=0;
        while((pec[i]&(0x80>>j))==0 && i>0){
            BitPosition--;
            if(j<7){
                j++;
            }else{
                j=0x00;
                i--;
            }
        }/*End of while */

        /*Get shift value for pattern value*/
        shift=BitPosition-8;
        /*Shift pattern value */
        while(shift){
            for(i=5; i<0xFF; i--){
                if((crc[i-1]&0x80) && (i>0)){
                    temp=1;
                }else{
                    temp=0;
                }
                crc[i]<<=1;
                crc[i]+=temp;
            }/*End of for*/
            shift--;
        }/*End of while*/
        /*Exclusive OR between pec and crc*/
        for(i=0; i<=5; i++){
            pec[i] ^=crc[i];
        }/*End of for*/
    }while(BitPosition>8); /*End of do-while*/

    return pec[0];
}

/*******************************************************************************
* Function Name  : delay_ms
* Description    : delay
* Input          : time
* Output         : None
* Return         : None
*******************************************************************************/
static void mxldelay_ms(uint16_t time)
{
	uint16_t i = 0;
	while(time--){
		i = 12000;
		while(i--);
	}
}
/*******************************************************************************
 * Function Name  : SMBus_ReadTemp
 * Description    : Calculate and return the temperature
 * Input          : None
 * Output         : None
 * Return         : SMBus_ReadMemory(0x00, 0x07)*0.02-273.15
*******************************************************************************/
//float SMBus_ReadTemp(void)
//{
//	uint16_t buff[5] = {0};
//	uint8_t i = 0;
//	uint16_t max;

//	for(i=0; i<5; i++){
//		buff[i] = SMBus_ReadMemory(SA, RAM_ACCESS|RAM_TOBJ1);
//		mxldelay_ms(50);
//	}
//	for(i=0; i<5; i++){
//		if(buff[i]>max){
//			max = buff[i];
//		}
//	}

//    return (float)max*0.02-273.15;  /* 特定公式 */
//}
float SMBus_ReadTemp(void)
{
	uint16_t buff[5] = {0};
	uint8_t i = 0;
	uint16_t max = 0;
	uint16_t uTempTemperature = 0;

	for(i=0; i<5; i++){
		uTempTemperature = SMBus_ReadMemory(SA, RAM_ACCESS|RAM_TOBJ1);
		if(	0xffff!=uTempTemperature ){
			buff[i] = uTempTemperature;
		}
		mxldelay_ms(50);
	}
	for(i=0; i<5; i++){
		if(buff[i]>max){
			max = buff[i];
		}
	}

    return (float)max*0.02-273.15;  /* 特定公式 */
}
