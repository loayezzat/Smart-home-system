/*
 * manager.c
 *

 *  Author: Loay
 */ 
#include "manager.h"

static u8 system_state = STATE_INIT ; 
static u8 entered_password [10] ; 
static const u8 system_password[10] = "1234" ; 
static u8 pw_id = 0 ; 
static u8 pass_tries = 0 ;

static void system_show_data (u8 key_v) ; /*not completed yet */
static void system_init_loginState (void) ; /*not implemented yet */
static void check_password (void) ;
//static void wrong_password_alarm (void) ;
//static void system_settings_init (void) ;

void system_init (void ) 
{
	system_state = STATE_INIT ; 
	LCD_voidClearScreen();		/*Go to the beginning of the first line */
	LCD_voidDisplayString("1:Temp");
	LCD_voidGoToRowColumn(0,8) ;/*Go to the middle of the first line */
	LCD_voidDisplayString("2:Pump");
	LCD_voidGoToRowColumn(1,0) ;/*Go to the beginning of the second line */
	LCD_voidDisplayString("3:Tank");
	LCD_voidGoToRowColumn(1,8) ;/*Go to the middle of the second line */
	LCD_voidDisplayString("4:config");
}

void system_manage (u8 key_value) 
{
	/*system reset(by on/c key)*/
	if ( key_value == 13)
	{
		system_init() ;
	}else
	{

		if (system_state == STATE_INIT)		// managing main(initial) frame
		{
			if (key_value == '1'  || key_value == '2' ||  key_value == '3')
			{
				system_state = STATE_SHOW_DATA ; 
				system_show_data (key_value) ;

			}else if (key_value == '4')
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
				check_password() ;
			
			}
		
		
		}
		else if (system_state == STATE_SHOW_DATA)
		{
			/*do nothing*/
			/*Requires no more user interaction unless the reset to main frame which is already checked */
		}
		
	
	}
}

static void system_init_loginState (void)
{
	
	  LCD_voidClearScreen();
	  LCD_voidDisplayString("Enter Pass try:");
	  LCD_voidDisplayCharacter(pass_tries + '1') ; 
	  LCD_voidGoToRowColumn(1,0) ;
	  pw_id = 0 ;
	  
}

static void check_password (void)
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
	
	
	if (pass_validity == 1 ) {
		/*system_state = STATE_SETTINGS ; 
		system_settings_init() ;*/
		LCD_voidClearScreen();
		LCD_voidDisplayString("Login successful"); 
	}else
	{
		if (pass_tries >= 3 )
		{
			
			//wrong_password_alarm () ;
			LCD_voidClearScreen();
			LCD_voidDisplayString("wrong pass alarm on");
		}else 
		{
			LCD_voidClearScreen();
			LCD_voidDisplayString("give another try");
			_delay_ms(1000) ; 
			system_init_loginState() ; /*give another try*/
		}
	}
	
	
	
}



static void system_show_data (u8 key_v) {
	switch (key_v){
		case  '1' : LCD_voidClearScreen() ; 
					LCD_voidDisplayString("showing temp");
					break ;
		case  '2' : LCD_voidClearScreen() ;
					LCD_voidDisplayString("showing pump");
					break ;
		case  '3' : LCD_voidClearScreen() ;
					LCD_voidDisplayString("showing tank");
					break ;		
	}
}