#include <avr/io.h>
#include <util/delay.h>

#include "../../libs/bitops.h"
#include "../../libs/datachk.h"

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

#define BLINK_DURATION_MS 250

void main(void) __attribute__((noreturn));

void blink(uint8_t led_channel) {
    _delay_ms(BLINK_DURATION_MS);
    SET_BIT(LED_REG, led_channel);
    _delay_ms(BLINK_DURATION_MS);
    CLR_BIT(LED_REG, led_channel);
}

void main(void) {
    // Set up UART
    init_uart();
    stdin = &uart_in;
    stdout = &uart_out;
    // Place to store input char
    char in_char;

    for (;;) {
        printf("Enter a number (1-9):");
        in_char = getchar();
        uint8_t in_num = C_TO_NUM(in_char);

        if (in_num > 0) {
            printf("\nBlinking %u time(s)...\n", in_num);
            for (uint8_t i = 0; i < in_num; ++i) {
                blink(LED_PIN);
            }
        } else {
            printf("\nInvalid value!\n");
        }
    }
}
