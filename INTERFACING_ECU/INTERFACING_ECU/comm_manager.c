/*
 * comm_mannager.c
 *
 * Created: 2019-11-29 10:16:04 AM
 *  Author: Loay
 *This Module is built to serve communications
 *this is built on the top of UART driver
 */ 
#include "comm_manager.h"

 u8 receiveBuffer [BUFFER_SIZE] ; 
 u8 transmittBuffer [BUFFER_SIZE] ;
 
static u8 receiveID = 0 ;
static u8 transmittID = 0 ; 



static u8 transmittState = 1 ; /*This will hold (0) if we currently transmitting a data packet */


static void receive_byte (void) ; 
static void transmitt_byte (void) ;
static void serveDataPacket (void ) ;



void initComm(void) {
	
	UART_voidInit() ; 
	receiveID = 0 ;
	transmittID = 0 ;
	transmittState = 1 ; 
	UART_voidSetTxComplete_ISR(transmitt_byte);
	UART_voidSetRxComplete_ISR(receive_byte);
}



void receive_byte (void) /*This function will be executed if a receive interrupt happens*/
{
	receiveBuffer[receiveID] = UART_u8GetDataRegister() ; 
	if (receiveBuffer[receiveID] == EOP)
	{
		serveDataPacket () ;	/*serve data packet function*/
		receiveID = 0 ;
	}else {
		receiveID++ ;
	}
}

u8 transmitt_available (void )
{
	return transmittState ;
}

void transmitt_packet (u8 *dataPacket) 
{
	u8 i = 0 ; 
	transmittState = 0 ;
	while(dataPacket[i]!= '#')
	{
		transmittBuffer[i] = dataPacket[i] ; 
		i++ ; 
	}
	transmittBuffer[i] = dataPacket[i] ;
	UART_voidSetDataRegister(transmittBuffer[0]) ; 
	transmittID = 1 ; 
	
	
}

static void transmitt_byte (void) 
{
	if (transmittState == 0 )
	{
		if (transmittBuffer[transmittID] == EOP ){
			UART_voidSetDataRegister(transmittBuffer[transmittID]) ;
			transmittState = 1 ;
			}else{
			UART_voidSetDataRegister(transmittBuffer[transmittID]) ;
			transmittID ++ ;
		}
	}
}


static void serveDataPacket (void ) 
{
	
}