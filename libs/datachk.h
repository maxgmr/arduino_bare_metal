#ifndef DATACHK_H
#define DATACHK_H

#define NUM_ASCII_START 0x30
#define NUM_ASCII_END 0x3A
#define UPPER_ASCII_START 0x41
#define UPPER_ASCII_END 0x5B
#define LOWER_ASCII_START 0x61
#define LOWER_ASCII_END 0x7B

// Check if the given ASCII character is a numerical value.
#define C_IS_NUM(char) ((char >= NUM_ASCII_START) && (char < NUM_ASCII_END))

// Return the numerical value of a single ASCII character, or -1 if invalid.
#define C_TO_NUM(char) ((C_IS_NUM(char)) ? (char - NUM_ASCII_START) : -1)

// Check if the given ASCII character is a lowercase alphabetical value.
#define C_IS_LOWER_ALPH(char)                                                  \
    ((char >= LOWER_ASCII_START) && (char < LOWER_ASCII_END))

// Check if the given ASCII character is an uppercase alphabetical value.
#define C_IS_UPPER_ALPH(char)                                                  \
    ((char >= UPPER_ASCII_START) && (char < UPPER_ASCII_END))

// Check if the given ASCII character is an alphabetical value.
#define C_IS_ALPH(char) ((C_IS_LOWER_ALPH(char)) || (C_IS_UPPER_ALPH(char)))

#endif // DATACONV_H
