#ifndef UART_INT_H_
#define UART_INT_H_

#include "STD_TYPES.h"

void UART_voidInit(void);
void UART_voidSetDataRegister(u8 Local_Data);
u8   UART_u8GetDataRegister(void);
void UART_voidSetTxComplete_ISR(void (*Local_ISR)(void));
void UART_voidSetRxComplete_ISR(void (*Local_ISR)(void));

#endif /* UART_INT_H_ */
