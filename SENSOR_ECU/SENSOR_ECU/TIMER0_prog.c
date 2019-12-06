#include "std_types.h"
#include "utils.h"
#include <util/delay.h>
#include <avr/interrupt.h>

#include "TIMER0_priv.h"
#include "TIMER0_config.h"
#include "TIMER0_int.h"

void (*OVF_ISR)(void)  = '\0';
void (*COMP_ISR)(void) = '\0';

void TIMER0_voidInit(void)
{
    /*** SET TIMER0 MODE ***/
    #if (TIMER0_MODE == TIMER0_NORMAL_MODE)
        CLRBIT(TCCR0, WGM00);
        CLRBIT(TCCR0, WGM01);

    #elif (TIMER0_MODE == TIMER0_CTC_MODE)
    	CLRBIT(TCCR0, WGM00);
        SETBIT(TCCR0, WGM01);
        /*** SET OC0 MODE ***/
        #if (OC0_MODE == TIMER0_NON_PWM_DISCONNECT_OC0)
            CLRBIT(TCCR0, COM00);
            CLRBIT(TCCR0, COM01);
        #elif (OC0_MODE == TIMER0_NON_PWM_TOGGLE_OC0)
            SETBIT(TCCR0, COM00);
            CLRBIT(TCCR0, COM01);
        #elif (OC0_MODE == TIMER0_NON_PWM_CLEAR_OC0)
            CLRBIT(TCCR0, COM00);
            SETBIT(TCCR0, COM01);
        #elif (OC0_MODE == TIMER0_NON_PWM_SET_OC0)
            SETBIT(TCCR0, COM00);
            SETBIT(TCCR0, COM01);
        #endif

    #elif (TIMER0_MODE == TIMER0_FAST_PWM_MODE)
        SETBIT(TCCR0, WGM00);
        SETBIT(TCCR0, WGM01);
        /*** SET OC0 MODE ***/
        #if (OC0_MODE == TIMER0_FAST_PWM_DISCONNECT_OC0)
            CLRBIT(TCCR0, COM00);
            CLRBIT(TCCR0, COM01);
        #elif (OC0_MODE == TIMER0_FAST_PWM_SET_OC0_AT_TOP)
            CLRBIT(TCCR0, COM00);
            SETBIT(TCCR0, COM01);
        #elif (OC0_MODE == TIMER0_FAST_PWM_CLEAR_OC0_AT_TOP)
            SETBIT(TCCR0, COM00);
            SETBIT(TCCR0, COM01);
        #endif

    #elif (TIMER0_MODE == TIMER0_PHASE_CORRECT_PWM_MODE)
        SETBIT(TCCR0, WGM00);
        CLRBIT(TCCR0, WGM01);
                /*** SET OC0 MODE ***/
        #if (OC0_MODE == TIMER0_PHASE_CORRECT_PWM_DISCONNECT_OC0)
            CLRBIT(TCCR0, COM00);
            CLRBIT(TCCR0, COM01);
        #elif (OC0_MODE == TIMER0_PHASE_CORRECT_PWM_CLEAR_OC0_AT_UP_COUNT)
            CLRBIT(TCCR0, COM00);
            SETBIT(TCCR0, COM01);
        #elif (OC0_MODE == TIMER0_PHASE_CORRECT_PWM_SET_OC0_AT_UP_COUNT)
            SETBIT(TCCR0, COM00);
            SETBIT(TCCR0, COM01);
        #endif
    #endif

    /*** CLOCK SELECT ***/
    #if (TIMER0_PRESCALER == TIMER0_PRESCALER_1)
        SETBIT(TCCR0, CS00);
        CLRBIT(TCCR0, CS01);
        CLRBIT(TCCR0, CS02);
    #elif (TIMER0_PRESCALER == TIMER0_PRESCALER_8)
        CLRBIT(TCCR0, CS00);
        SETBIT(TCCR0, CS01);
        CLRBIT(TCCR0, CS02);
    #elif (TIMER0_PRESCALER == TIMER0_PRESCALER_64)
        SETBIT(TCCR0, CS00);
        SETBIT(TCCR0, CS01);
        CLRBIT(TCCR0, CS02);
    #elif (TIMER0_PRESCALER == TIMER0_PRESCALER_256)
        CLRBIT(TCCR0, CS00);
        CLRBIT(TCCR0, CS01);
        SETBIT(TCCR0, CS02);
    #elif (TIMER0_PRESCALER == TIMER0_PRESCALER_1024)
        SETBIT(TCCR0, CS00);
        CLRBIT(TCCR0, CS01);
        SETBIT(TCCR0, CS02);
    #endif

    /*** Enable the interrupts ***/ /*we need no ISR to be executed in PWM mode*/
	//SETBIT(TIMSK, TOIE0);
	//SETBIT(TIMSK, OCIE0);
}

void TIMER0_voidLoad_TCNT(u8 Local_Value)
{
    TCNT0 = Local_Value;
}

void TIMER0_voidLoad_OCR(u8 Local_Value)
{
    OCR0 = Local_Value;
}

void TIMER0_voidSetCompareMatch_ISR(void (*Local_COMP_ISR)(void))
{
    COMP_ISR = Local_COMP_ISR;
}

void TIMER0_voidSetOverFlow_ISR(void (*Local_OV_ISR)(void))
{
    OVF_ISR = Local_OV_ISR;
}

ISR(TIMER0_OVF_vect)
{
    OVF_ISR();
}

ISR(TIMER0_COMP_vect)
{
    COMP_ISR();
}
