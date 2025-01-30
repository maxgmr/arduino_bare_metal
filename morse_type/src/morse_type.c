#include <avr/io.h>
#include <util/delay.h>

#include "../../libs/bitops.h"
#include "../../libs/datachk.h"

#define MORSE_BASE 150

#include "../../libs/morse.h"

// Enable UART transmission and reception
#define UART_TX 1
#define UART_RX 1

#include "../../libs/uarti.h"
#include "../../libs/uartr.h"
#include "../../libs/uartw.h"

#define DD_REG DDRB
#define DD_PIN DDB0
#define LED_REG PORTB
#define LED_PIN PORTB0

void dit(void) {
    SET_BIT(LED_REG, LED_PIN);
    _delay_ms(DIT);
    CLR_BIT(LED_REG, LED_PIN);
}

void dah(void) {
    SET_BIT(LED_REG, LED_PIN);
    _delay_ms(DAH);
    CLR_BIT(LED_REG, LED_PIN);
}

void main(void) __attribute__((noreturn));

void main(void) {
    // Set up UART
    init_uart();
    stdin = &uart_in;
    stdout = &uart_out;
    // Place to store input char
    char in_char;

    for (;;) {
        printf("Enter an alphanumeric character:");
        in_char = getchar();

        if (!C_IS_ALPH(in_char) && !C_IS_NUM(in_char)) {
            printf("\nInvalid value!\n");
        } else {
            putc(in_char, stdout);
            blink_char(in_char, dit, dah);
            putc('\n', stdout);
        }
    }
}
