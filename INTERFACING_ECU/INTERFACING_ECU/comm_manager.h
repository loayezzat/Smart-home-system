/*
 * comm_manager.h
 *
 * Created: 2019-11-29 10:16:24 AM
 *  Author: Loay
 *This Module is built to serve communications 
 *this is built on the top of UART driver
 */ 
#include "UART_int.h"
#include <avr/interrupt.h>

#ifndef COMM_MANAGER_H_
#define COMM_MANAGER_H_
/*end of data packet character*/
#define EOP ('#')

#define BUFFER_SIZE 10 

void initComm(void) ; 
void transmitt_packet (u8 *dataPacket) ; 
u8 transmitt_available (void) ;/*you need to check this function before overwriting the buffer*/




#endif /* COMM_MANAGER_H_ */