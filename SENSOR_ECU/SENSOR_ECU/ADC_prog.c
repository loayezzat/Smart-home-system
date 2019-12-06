/*
 * ADC_prog.c
 *
 *  Created on: Nov 23, 2019
 *      Author: Ahmed
 */

#include "ADC_config.h"
#include "ADC_priv.h"
#include "ADC_int.h"

#include "std_types.h"
#include "utils.h"

#include <avr/io.h>

#include <avr/interrupt.h>

void (*fptr)(void) = '\0';

void ADC_voidInit(void)
{

#if (ADC_VREF == ADC_AREF)
	CLRBIT(ADMUX, REFS1);
	CLRBIT(ADMUX, REFS0);
#elif (ADC_VREF == ADC_AVCC)
	CLRBIT(ADMUX, REFS1);
	SETBIT(ADMUX, REFS0);
#elif (ADC_VREF == ADC_INT2_5V)
	SETBIT(ADMUX, REFS1);
	SETBIT(ADMUX, REFS0);
#endif

	CLRBIT(ADMUX, ADLAR);

	// default channel (you can change channel during runtime)
	ADC_voidChangeChannel(0);

	SETBIT(ADCSRA, ADEN);

	CLRBIT(ADCSRA, ADATE);

	SETBIT(ADCSRA, ADIE);

#if (ADC_CLKDIV == ADC_DIV2)
	CLRBIT(ADCSRA, ADPS2);
	CLRBIT(ADCSRA, ADPS1);
	CLRBIT(ADCSRA, ADPS0);
#elif (ADC_CLKDIV == ADC_DIV4)
	CLRBIT(ADCSRA, ADPS2);
	SETBIT(ADCSRA, ADPS1);
	CLRBIT(ADCSRA, ADPS0);
#elif (ADC_CLKDIV == ADC_DIV8)
	CLRBIT(ADCSRA, ADPS2);
	SETBIT(ADCSRA, ADPS1);
	SETBIT(ADCSRA, ADPS0);
#endif

	CLRBIT(SFIOR, ADTS2);
	CLRBIT(SFIOR, ADTS1);
	CLRBIT(SFIOR, ADTS0);

	SETBIT(ADCSRA, ADIF);
	


}



u16 ADC_u16GetData(void)
{
	return ADCW;
}

void ADC_voidStartConv(void)
{
	SETBIT(ADCSRA, ADSC);
}

void ADC_voidChangeChannel(u8 local_channelNo)
{
		
	local_channelNo &= 0x07; /* channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | local_channelNo;
}

void ADC_voidSetISRPtr(void (*local_fptr)(void))
{
	fptr = local_fptr;
}

ISR(ADC_vect)
{
	(*fptr)();
}
