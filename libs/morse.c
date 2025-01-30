#include <util/delay.h>

#include "./datachk.h"
#include "./morse.h"

#define ALPHABET_INDEX_START 10

static const char *morse_strs[36] = {
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...",
    "---..", "----.", ".-",    "-...",  "-.-.",  "-..",   ".",     "..-.",
    "--.",   "....",  "..",    ".---",  "-.-",   ".-..",  "--",    "-.",
    "---",   ".--.",  "--.-",  ".-.",   "...",   "-",     "..-",   "...-",
    ".--",   "-..-",  "-.--",  "--..",
};

/* Match the given char to its index in morse_strs, defaulting to 0. */
uint8_t char_to_index(char c) {
    int8_t num_attempt = C_TO_NUM(c);
    if (num_attempt != -1) {
        return num_attempt;
    }

    if (C_IS_LOWER_ALPH(c)) {
        return (c - LOWER_ASCII_START) + ALPHABET_INDEX_START;
    } else if (C_IS_UPPER_ALPH(c)) {
        return (c - UPPER_ASCII_START) + ALPHABET_INDEX_START;
    }

    return 0;
}

void blink_char(char input_c, void (*dit_fn)(void), void (*dah_fn)(void)) {
    uint8_t i = char_to_index(input_c);
    for (char c = *morse_strs[i]; c != '\0'; c = *++morse_strs[i]) {
        if (c == '-') {
            dah_fn();
        } else if (c == '.') {
            dit_fn();
        }
        _delay_ms(SPACE);
    }
    _delay_ms(L_SPACE_AFTER);
}
