#ifndef UARTR_H
#define UARTR_H

#include <stdio.h>

int uart_getc(FILE *stream);

extern FILE uart_in;

#endif // UARTR_H
