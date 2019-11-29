/*
 * SENSOR_ECU.c
 *
 * Created: 2019-11-29 08:41:58 PM
 * Author : Loay
 */ 
#define F_CPU 1000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "comm_manager.h"
u8 temp , ldr , led , pir , door , fan ; 
u8 data_packet[10] ; 

void generate_dataPacket(void) ; 

int main(void)
{
    /* Replace with your application code */
	sei() ; 
	 initComm() ; 
	 
	 temp =1 ; led =3 ; fan=7 ; 
    while (1) 
    {
		_delay_ms(500); 
		temp ++ ; led ++ ; fan++ ; 
		while (transmitt_available())
		{
			PORTA++ ; 
			generate_dataPacket() ;
			transmitt_packet(data_packet) ; 
		}
		
    }
}

void generate_dataPacket(void)
{
	data_packet[0]= 'd' ; 
	data_packet[1] = temp ; 
	data_packet[2] = ldr ;
	data_packet[3] = led ;
	data_packet[4] = pir ;
	data_packet[5] = door ;
	data_packet[6] = fan ;
	
	data_packet[7] = '#' ;
	data_packet[8] = 0 ;
	
	
}