#include <avr/io.h>
#include <stdio.h>

#include "./bitops.h"

int uart_getc(__attribute__((unused)) FILE *stream) {
    while (!CHK_BIT(UCSR0A, RXC0))
        ;
    return UDR0;
}

FILE uart_in = FDEV_SETUP_STREAM(NULL, uart_getc, _FDEV_SETUP_READ);
