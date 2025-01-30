#include <avr/io.h>
#include <stdio.h>

#include "./bitops.h"

int uart_putc(char c, FILE *stream) {
    if (c == '\n') {
        uart_putc('\r', stream);
    }
    while (!CHK_BIT(UCSR0A, UDRE0))
        ;
    UDR0 = c;
    return 0;
}

FILE uart_out = FDEV_SETUP_STREAM(uart_putc, NULL, _FDEV_SETUP_WRITE);
