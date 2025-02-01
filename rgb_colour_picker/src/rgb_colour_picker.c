#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdbool.h>
#include <stdio.h>
#include <util/delay.h>

#include "../../libs/bitops.h"
#include "../../libs/datachk.h"
#include "../../libs/pwmw.h"

// Enable UART transmission and reception
#define UART_TX 1
#define UART_RX 1

#include "../../libs/cltc.h"
#include "../../libs/uarti.h"
#include "../../libs/uartr.h"
#include "../../libs/uartw.h"

#define USE_B_PORTS true

#define INPUT_LEN 6

#define ASCII_UC_OFFSET 0x41
#define ASCII_LC_OFFSET 0x61

#define ERROR false
#define OK true

#if USE_B_PORTS
// Version that uses ports 9, 10, 11
#define DATA_REG PORTB
#define RED_PORT PORTB1
#define GRN_PORT PORTB2
#define BLU_PORT PORTB3
#define DD_REG DDRB
#define RED_DD DDB1
#define GRN_DD DDB2
#define BLU_DD DDB3
#else
// Version that uses ports 3, 5, 6
#define DATA_REG PORTD
#define RED_PORT PORTD3
#define GRN_PORT PORTD5
#define BLU_PORT PORTD6
#define DD_REG DDRD
#define RED_DD DDD3
#define GRN_DD DDD5
#define BLU_DD DDD6
#endif

void main(void) __attribute__((noreturn));
bool read_n_chars(char *buf, uint8_t n) {
    for (uint8_t i = 0; i < n; ++i) {
        int c = getchar();
        if (c == EOF || c == '\n') {
            return ERROR;
        }
        putc(c, stdout);
        buf[i] = (char)c;
    }
    return OK;
}

uint8_t parse_hex_c(char c, bool *status) {
    // 0-9
    int8_t num_attempt = C_TO_NUM(c);
    if (C_TO_NUM(c) != -1) {
        return num_attempt;
    }

    // a-f
    int8_t lc_diff = c - ASCII_LC_OFFSET;
    if ((lc_diff >= 0) && (lc_diff <= 5)) {
        return lc_diff + 10;
    }

    // A-F
    int8_t uc_diff = c - ASCII_UC_OFFSET;
    if ((uc_diff >= 0) && (uc_diff <= 5)) {
        return uc_diff + 10;
    }

    *status = ERROR;
    return 0;
}

bool parse_hex(char c1, char c0, uint8_t *output) {
    bool status = OK;
    *output = parse_hex_c(c0, &status) + (parse_hex_c(c1, &status) * 16);
    return status;
}

void main(void) {
    // Set up UART
    init_uart();
    stdin = &uart_in;
    stdout = &uart_out;
    // Place to store input hex code
    char input_hex[INPUT_LEN];
    // Places to store hex values
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    for (;;) {
        printf("\nRGB Hexcode: #");
        if (!read_n_chars(input_hex, INPUT_LEN) ||
            !parse_hex(input_hex[0], input_hex[1], &r) ||
            !parse_hex(input_hex[2], input_hex[3], &g) ||
            !parse_hex(input_hex[4], input_hex[5], &b)) {
            // Bad input!
            printf("\nInvalid input- enter 6-character hex code.");
        } else {
            printf("\n#%02X%02X%02X", r, g, b);
            // Input OK, set LED
            clear_tc();
            if (r) {
                SET_BIT(DD_REG, RED_DD);
                pwm_write_fast(RED_PORT, USE_B_PORTS, r);
            } else {
                CLR_BIT(DD_REG, RED_DD);
            }
            if (g) {
                SET_BIT(DD_REG, GRN_DD);
                pwm_write_fast(GRN_PORT, USE_B_PORTS, g);
            } else {
                CLR_BIT(DD_REG, GRN_DD);
            }
            if (b) {
                SET_BIT(DD_REG, BLU_DD);
                pwm_write_fast(BLU_PORT, USE_B_PORTS, b);
            } else {
                CLR_BIT(DD_REG, BLU_DD);
            }
        }
    }
}
