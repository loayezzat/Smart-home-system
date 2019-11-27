/*
 * manager.h
 *
 *  Author: Loay
 */ 


#ifndef MANAGER_H_
#define MANAGER_H_

#include "LCD_int.h"
#include "std_types.h"
#include <util/delay.h>
/*Defining system states*/

#define STATE_INIT 0 
#define STATE_SHOW_DATA 1

#define STATE_LOGIN 4
#define STATE_SETTINGS 5

void system_init (void ) ;
void system_manage (u8 key_value) ; 


#endif /* MANAGER_H_ */