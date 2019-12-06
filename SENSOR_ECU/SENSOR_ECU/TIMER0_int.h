#ifndef TIMER0_INT_H_
#define TIMER0_INT_H_

#include "STD_TYPES.h"
#include "TIMER0_priv.h"

void TIMER0_voidInit(void);
void TIMER0_voidLoad_TCNT(u8 Local_Value);
void TIMER0_voidLoad_OCR(u8 Local_Value);
void TIMER0_voidSetCompareMatch_ISR(void (*Local_COMP_ISR)(void));
void TIMER0_voidSetOverFlow_ISR(void (*Local_OV_ISR)(void));

#endif /* TIMER0_INT_H_ */
