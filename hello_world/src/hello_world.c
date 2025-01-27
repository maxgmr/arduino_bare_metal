#include "../../libs/bitops.h"

#include <avr/io.h>
#include <util/delay.h>

#define DIT 200
#define DAH (3 * DIT)
#define SPACE DIT
#define L_SPACE (3 * DIT)
#define L_SPACE_AFTER (L_SPACE - SPACE)
#define W_SPACE (7 * DIT)
#define W_SPACE_AFTER (W_SPACE - L_SPACE)

#define MORSE_A ".-"
#define MORSE_B "-..."
#define MORSE_C "-.-."
#define MORSE_D "-.."
#define MORSE_E "."
#define MORSE_F "..-."
#define MORSE_G "--."
#define MORSE_H "...."
#define MORSE_I ".."
#define MORSE_J ".---"
#define MORSE_K "-.-"
#define MORSE_L ".-.."
#define MORSE_M "--"
#define MORSE_N "-."
#define MORSE_O "---"
#define MORSE_P ".--."
#define MORSE_Q "--.-"
#define MORSE_R ".-."
#define MORSE_S "..."
#define MORSE_T "-"
#define MORSE_U "..-"
#define MORSE_V "...-"
#define MORSE_W ".--"
#define MORSE_X "-..-"
#define MORSE_Y "-.--"
#define MORSE_Z "--.."
#define MORSE_1 ".----"
#define MORSE_2 "..---"
#define MORSE_3 "...--"
#define MORSE_4 "....-"
#define MORSE_5 "....."
#define MORSE_6 "-...."
#define MORSE_7 "--..."
#define MORSE_8 "---.."
#define MORSE_9 "----."
#define MORSE_0 "-----"

void main(void) __attribute__((noreturn));

void dit() {
    SET_BIT(PORTB, PORTB5);
    _delay_ms(DIT);
    CLR_BIT(PORTB, PORTB5);
    _delay_ms(SPACE);
}

void dah() {
    SET_BIT(PORTB, PORTB5);
    _delay_ms(DAH);
    CLR_BIT(PORTB, PORTB5);
    _delay_ms(SPACE);
}

/* Input string MUST be a null-terminated string of '.'s (dits) and '-'s (dahs)
 */
void flash_letter(char *input_str) {
    for (char c = *input_str; c != '\0'; c = *++input_str) {
        if (c == '-') {
            dah();
        } else if (c == '.') {
            dit();
        }
    }
    _delay_ms(L_SPACE_AFTER);
}

void main(void) {
    // Set pin 13 as output pin
    SET_BIT(DDRB, DDB5);

    for (;;) {
        // Hello, world!
        flash_letter(MORSE_H);
        flash_letter(MORSE_E);
        flash_letter(MORSE_L);
        flash_letter(MORSE_L);
        flash_letter(MORSE_O);
        _delay_ms(W_SPACE_AFTER);
        flash_letter(MORSE_W);
        flash_letter(MORSE_O);
        flash_letter(MORSE_R);
        flash_letter(MORSE_L);
        flash_letter(MORSE_D);
        _delay_ms(W_SPACE_AFTER);
        _delay_ms(W_SPACE);
    }
}
