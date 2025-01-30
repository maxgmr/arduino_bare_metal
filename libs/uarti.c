#include <avr/io.h>

#include "./bitops.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef BAUD
#define BAUD 57600
#endif

#ifndef UART_TX
#define UART_TX 1
#endif

#ifndef UART_RX
#define UART_RX 1
#endif

#include <util/setbaud.h>

void init_uart(void) {
    // Set UART speed
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    SET_BIT(UCSR0A, U2X0);
#else
    CLR_BIT(USCR0A, U2X0);
#endif

    // Data frame size = 8 bits
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

#if UART_TX && UART_RX
    // Enable transmission and reception
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
#elif UART_TX
    // Enable transmission
    SET_BIT(UCSR0B, TXEN0);
#elif UART_RX
    // Enable reception
    SET_BIT(UCSR0B, RXEN0);
#endif
}
