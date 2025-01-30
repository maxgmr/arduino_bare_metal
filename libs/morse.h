#ifndef MORSE_H
#define MORSE_H

#ifndef MORSE_BASE
#define MORSE_BASE 200
#endif

#define DIT MORSE_BASE
#define DAH (3 * DIT)
#define SPACE DIT
#define L_SPACE (3 * DIT)
#define L_SPACE_AFTER (L_SPACE - SPACE)
#define W_SPACE (7 * DIT)
#define W_SPACE_AFTER (W_SPACE - L_SPACE)

void blink_char(char input_c, void (*dit_fn)(void), void (*dah_fn)(void));

#endif // MORSE_H
