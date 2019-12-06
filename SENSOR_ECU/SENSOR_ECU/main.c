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
#include "ADC_int.h"
#include "utils.h"
#include "TIMER0_int.h"


#define LDR_THRESHOLD 256 
volatile u8  temp , ldr , pir , led  , door , fan ; 
/*
temp : holds temperature in degree C .
fan  : holds the fan speed in percentage  i.e. 100 for full speed.

ldr  : holds zero if it's dark 
led  : holds one if the LED is on. 

door : holds the state of the door (whether it's open or closed) , one if opened. 
pir  : holds one if it detects an object. 

*/
u8 fan_manual_flag , led_manual_flag , door_manual_flag ; /*a flag holds one in manual mode*/

u8 data_packet[10] ; 



//temp = (temp*150*5)/(1023*1.5); /* calculate the temp from the ADC value*/
void generate_dataPacket(void) ; 
void get_ADC_values (void) ;


void conrol_fan_speed (void ) ;
void control_led (void ) ;

void init_system (void) ;

int main(void)
{
	init_system() ; 
		

    while (1) 
    {
		
		
		/*Sending sensors and actuator states to the other ECU*/
		while (comm_transmitt_available()) 
		{
			
			generate_dataPacket() ;
			comm_transmitt_packet(data_packet) ; 
		}
		/*Starting a new ADC conversion*/ 
		ADC_voidChangeChannel(0) ; 
		ADC_voidStartConv(); 
		
		/*Serve fan motor*/ 
		if (fan_manual_flag == 0 ) { /*Automatic mode (rely on temp sensor)*/
			
			fan = 2*temp ;
			if (fan > 100 ) fan = 100 ; /*Verifying max speed*/
		}
		conrol_fan_speed () ; 
		
		
		if (led_manual_flag == 0 ) { /*Automatic mode (rely on LDR sensor)*/
				led = !ldr ; 
		}
		control_led () ;
		
		
		/*System Delay to prevent overriding events, since many system functions are asynchronous*/
		_delay_ms(100); 
		
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

void get_ADC_values (void) 
{
	
	static u8 channel_id  = 0 ; 
	u16 adc_value ;
	adc_value = ADC ;
	
	

	if (channel_id == 0 )
	{
		channel_id = 1 ;
		temp = ((u32)adc_value*150*5)/(1023*1.5); /* calculate the temp from the ADC value*/
		ADC_voidChangeChannel(1); /* read channel two where the temp sensor is connect */
		ADC_voidStartConv() ;
	
	}else if (channel_id ==1)
	{

		channel_id = 0 ;
		
		if (adc_value > LDR_THRESHOLD) ldr = 1 ; //LDR holds zero if it is dark
		else ldr = 0 ;
	}

	
}


void control_led (void ) 
{
	if (led == 0)
	{
		CLRBIT(PORTB , 7) ; 
	}else 
	{
		SETBIT(PORTB , 7) ; 
	}
}

void conrol_fan_speed (void ) 
{
	u8 timer_value ; 
	timer_value = (u16)fan*(255)/100 ; 
	TIMER0_voidLoad_OCR(timer_value) ; 
	
}

void init_system (void) 
{

	/* Replace with your application code */
	sei() ;
	
	initComm() ;
	ADC_voidSetISRPtr(get_ADC_values) ;
	ADC_voidInit() ;
	DDRB |= 1<<7 | 1<<3 ; /*Setting PB7 as output pin*/
	
	TIMER0_voidInit() ;
}