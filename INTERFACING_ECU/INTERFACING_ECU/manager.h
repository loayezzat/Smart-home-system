/*
 * manager.h
 *
 *  Author: Loay
 */ 


#ifndef MANAGER_H_
#define MANAGER_H_
#define F_CPU 1000000UL

#include "LCD_int.h"
#include "std_types.h"
#include <util/delay.h>
#include "comm_manager.h"
#define STATE_READINGS 0
#define STATE_LOGIN    1
#define STATE_MANUAL   2

void system_init (void ) ;
void system_manage (u8 key_value) ; 
void screen_readings_refresh (void) ;

void serveDataPacket (void) ;

#endif /* MANAGER_H_ */