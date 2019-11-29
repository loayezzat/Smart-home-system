#include "std_types.h"
#include "utils.h"

#include <avr/interrupt.h>

#include "UART_priv.h"
#include "UART_config.h"
#include "UART_int.h"

void (*TX_COMPLETE_ISR)(void)  = '\0';
void (*RX_COMPLETE_ISR)(void)  = '\0';

void UART_voidInit(void)
{
    /*** Double the transmission speed ***/
    SETBIT(UCSRA, U2X);

    /*** Enable Tx and Rx ***/
    SETBIT(UCSRB, RXEN);
    SETBIT(UCSRB, TXEN);

    /*** Enable Tx and Rx Complete Interrupts ***/
    SETBIT(UCSRB, RXCIE);
    SETBIT(UCSRB, TXCIE);

    /*** Set 8-bit mode ***/
    CLRBIT(UCSRB, UCSZ2);

    /*** Select UCSRC Register ***/
    SETBIT(UCSRC, URSEL);

    /*** Set 8-bit mode ***/
    SETBIT(UCSRC, UCSZ0);
    SETBIT(UCSRC, UCSZ1);


    /*** Set Parity mode ***/
    #if (UART_PARITY == NO_PARITY)
        CLRBIT(UCSRC, UPM0);
        CLRBIT(UCSRC, UPM1);
    #elif (UART_PARITY == EVEN_PARITY)
        CLRBIT(UCSRC, UPM0);
        SETBIT(UCSRC, UPM1);
    #elif (UART_PARITY == ODD_PARITY)
        SETBIT(UCSRC, UPM0);
        SETBIT(UCSRC, UPM1);
    #endif

    /*** Set Stop bit ***/
    #if (UART_STOP_BIT == STOP_BIT_1)
        CLRBIT(UCSRC, USBS);
    #elif (UART_STOP_BIT == STOP_BIT_2)
        SETBIT(UCSRC, USBS);
    #endif


    /*** Set Baud Rate ***/
    #if (UART_BAUD_RATE == BAUD_RATE_4800)
        UBRRH = 0;
        UBRRL = 25;
    #elif (UART_BAUD_RATE == BAUD_RATE_9600)
        UBRRH = 0;
        UBRRL = 12;
    #elif (UART_BAUD_RATE == BAUD_RATE_14400)
        UBRRH = 0;
        UBRRL = 8;
    #elif (UART_BAUD_RATE == BAUD_RATE_19200)
        UBRRH = 0;
        UBRRL = 6;
    #elif (UART_BAUD_RATE == BAUD_RATE_28800)
        UBRRH = 0;
        UBRRL = 3;
    #elif (UART_BAUD_RATE == BAUD_RATE_38400)
        UBRRH = 0;
        UBRRL = 2;
    #elif (UART_BAUD_RATE == BAUD_RATE_57600)

    #elif (UART_BAUD_RATE == BAUD_RATE_115200)
        UBRRH = 0;
        UBRRL = 0;
    #endif

}

void UART_voidSetDataRegister(u8 Local_Data)
{
    UDR = Local_Data;
}

u8 UART_u8GetDataRegister(void)
{
    return UDR;
}

void UART_voidSetTxComplete_ISR(void (*Local_ISR)(void))
{
    TX_COMPLETE_ISR = Local_ISR;
}

void UART_voidSetRxComplete_ISR(void (*Local_ISR)(void))
{
    RX_COMPLETE_ISR = Local_ISR;
}

ISR(USART_TXC_vect)
{
    TX_COMPLETE_ISR();
}

ISR(USART_RXC_vect)
{
    RX_COMPLETE_ISR();
}

