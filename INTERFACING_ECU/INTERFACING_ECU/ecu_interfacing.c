/*
 * ecu_interfacing.c
 *
 *  Author: Loay
 */ 

#include "std_types.h"
#include <util/delay.h>
#include "manager.h"
#include "DIO_int.h" 
#include "LCD_int.h"
int main(){
	
	u8 value ; 
	DIO_voidInit() ;
	LCD_voidInit () ;

	/*LCD_voidDisplayString("Welcome"); 
	_delay_ms(1000);
	LCD_voidClearScreen();*/
	
	system_init () ; /*initiating the system state */

	while(1)
	{
	value = KeyPad_u8GetPressedKey() ;
	if (value != 255) system_manage(value) ; /*If key is pressed*/
	_delay_ms(200) ; 
	}


	return 0 ; 	
}