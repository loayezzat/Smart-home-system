/*
 * manager.c
 *

 *  Author: Loay
 */ 
#include "manager.h"

u8 system_state = STATE_READINGS ; 
static u8 readingToshow = 3 ; 

u8 reading_temp = 1 ; 
u8 reading_PIR  = 0 ; 
u8 reading_LDR = 5 ; 
u8 reading_LED = 1 ; 
u8 reaing_motor_fan =50 ; 
u8 reading_door = 1 ; 


static u8 entered_password [10] ; 
static const u8 system_password[10] = "1234" ; 
static u8 pw_id = 0 ; 
static u8 pass_tries = 0 ;



static void system_init_loginState (void) ; 
static u8 check_password (void) ;



//static void wrong_password_alarm (void) ;
//static void system_settings_init (void) ;

void system_init (void ) 
{
	system_state = STATE_READINGS ; 
	readingToshow = 1 ;

}

void system_manage (u8 key_value) 
{
	/*system reset(by on/c key)*/
	if ( key_value == 13)
	{
		system_init() ;
	}else
	{

		if (system_state == STATE_READINGS)		// managing main(initial) frame
		{
			if (key_value == '6')
			{
				if (readingToshow == 6 )  readingToshow = 1 ; /*to ensure looping within the six readings*/ 
				else readingToshow++ ; 
				
			}else if (key_value == '4')
			{
				if (readingToshow == 1 )  readingToshow = 6 ; /*to ensure looping within the six readings*/
				else readingToshow-- ;
				
				
			}else if (key_value == '1')
			{
				system_state = STATE_LOGIN ; 
				system_init_loginState () ;		
			}
		
		}
		else if (system_state == STATE_LOGIN) // managing the logging frame
		{
			if (key_value != '=')
			{
				entered_password[pw_id] = key_value ; /*concatenating the char in the password string*/
				pw_id++ ;/*incrementing the string index for next char assignment*/
				LCD_voidDisplayCharacter(key_value);
			
			}else if (key_value == '=')/*the user ends the password */
			{
				 
				entered_password[pw_id] = 0 ;  /*terminating the password string*/
				check_password(); 
			
			}
		
		
		}

		
	
	}
}

static void system_init_loginState (void)
{
	
	  LCD_voidClearScreen();
	  if (pass_tries < 3 )
	  {
		LCD_voidDisplayString("Enter Pass try:");
		LCD_voidDisplayCharacter(pass_tries + '1') ;
		LCD_voidGoToRowColumn(1,0) ;
	
	  }else 
	  {
		 LCD_voidDisplayString("You cannot enter");
	  }

	  pw_id = 0 ;
	  
}

static u8 check_password (void)
{
	
	
	/*Checking the password*/
	u8 i= 0 ;
	u8 pass_validity = 1 ;
	while (system_password[i] != 0 )
	{
		if (system_password[i] != entered_password[i]) {
			pass_validity = 0 ; 
			pass_tries ++ ;
			break ;
		}
		i++ ;
	}
	if (entered_password[i] != 0 ) /*checking if entered pass has the same length*/
	{
		pass_validity = 0 ; 
		pass_tries ++ ;
	}
	
	
	if (pass_validity == 1 )
	{
		pass_tries = 0 ;
		LCD_voidClearScreen();
		LCD_voidDisplayString("Login successful");
		return 1 ; 
	}else
	{
			if (pass_tries >= 3 )
			{
			
				//wrong_password_alarm () ;
				LCD_voidClearScreen();
				LCD_voidDisplayString("Wrong pass alarm on");
				return 0 ; 
			}else 
			{
				LCD_voidClearScreen();
				LCD_voidDisplayString("Give another try");
				_delay_ms(1000) ; 
				system_init_loginState() ; /*give another try*/
				return 2 ; 
			}
	}
	
	
	
}



void screen_readings_refresh (void) 
{
	
	switch (readingToshow)
	{
		case 1 : LCD_voidClearScreen();
				 LCD_voidDisplayString("TEMPRATURE");
				 LCD_voidGoToRowColumn(1,8) ; 
				 LCD_voidSendInt(reading_temp) ; 
				 LCD_voidDisplayString(" C"); 
				 break ; 
				 
		case 2 : LCD_voidClearScreen();
				 LCD_voidDisplayString("PIR SENSOR");
			 	 LCD_voidGoToRowColumn(1,0) ;
				 if (reading_PIR == 0 ) LCD_voidDisplayString("Object detected");
				 else LCD_voidDisplayString("No Objects");
				 break ;
		
		
		case 3 :LCD_voidClearScreen();
				LCD_voidDisplayString("LDR SENSOR");
				LCD_voidGoToRowColumn(1,8) ;
				LCD_voidSendInt(reading_LDR) ;
				LCD_voidDisplayString(" %");
				break ;
		
		case 4 :LCD_voidClearScreen();
				LCD_voidDisplayString("LED STATE");
				LCD_voidGoToRowColumn(1,12) ;
				if (reading_LED == 0 ) LCD_voidDisplayString("OFF");
				else LCD_voidDisplayString("ON");
				break ;
		
		case 5 :LCD_voidClearScreen();
				LCD_voidDisplayString("Fan Speed");
				LCD_voidGoToRowColumn(1,8) ;
				LCD_voidSendInt(reaing_motor_fan) ;
				LCD_voidDisplayString(" %");
				break ;
		
		case 6 :LCD_voidClearScreen();
				LCD_voidDisplayString("Door State");
				LCD_voidGoToRowColumn(1,8) ;
				if (reading_door == 0 ) LCD_voidDisplayString("OFF");
				else LCD_voidDisplayString("ON");
				break ;
		
	
	}
}