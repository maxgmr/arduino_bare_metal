#ifndef DATACHK_H
#define DATACHK_H

// Return the numerical value of a single ASCII character, or -1 if invalid.
#define C_TO_NUM(char) (((char >= 0x30) && (char <= 0x39)) ? (char - 0x30) : -1)

#endif // DATACONV_H
