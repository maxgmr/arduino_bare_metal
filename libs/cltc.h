#ifndef CLTC_H
#define CLTC_H

#include <avr/io.h>

/* Reset timer/counter registers */
#define clear_tc()                                                             \
    TCCR0A = 0;                                                                \
    TCCR0B = 0;                                                                \
    TCCR1A = 0;                                                                \
    TCCR1B = 0;                                                                \
    TCCR2A = 0;                                                                \
    TCCR2B = 0;

#endif // CLTC_H
