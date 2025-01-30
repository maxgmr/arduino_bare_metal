#ifndef UARTW_H
#define UARTW_H

#include <stdio.h>

int uart_putc(char c, FILE *stream);

extern FILE uart_out;

#endif // UARTW_H
