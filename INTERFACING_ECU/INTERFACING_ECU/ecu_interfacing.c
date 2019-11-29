/*
 * ecu_interfacing.c
 *
 *  Author: Loay
 */ 
#define  F_CPU 1000000UL
#include "std_types.h"
#include <util/delay.h>
#include "manager.h"
#include "DIO_int.h" 
#include "LCD_int.h"
#include "comm_manager.h"
#include "KeyPad_int.h"

extern u8 system_state ; 

int main(){
	
	u8 value ; 
	DIO_voidInit() ;
	LCD_voidInit () ;

	sei() ; 
	system_init () ; /*initiating the system state */
	initComm() ;
	
	 
	while(1)
	{
	value = KeyPad_u8GetPressedKey() ; /*Serving the Keypad*/
	if (value != 255) system_manage(value) ; /*If key is pressed*/
	if (system_state == STATE_READINGS ) screen_readings_refresh() ; 
	_delay_ms(250) ; 
	}


	return 0 ; 	
}