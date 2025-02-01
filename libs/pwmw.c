#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdbool.h>

/* Send fast PWM signals on the pins with alternate timer/counter functionality.
 *
 * Analogous to analogWrite() from the Arduino library.
 *
 * This is for pins PB1, PB2, and PB3 (Arduino pins 9, 10, & 11).
 */
uint8_t pwm_write_fast(uint8_t pin, bool use_b, uint8_t cycle) {
    // Prescaler 64: 16Mhz / (256 * 64) = 976.5625 Hz

    /*
     * https://wellys.com/posts/avr_c_step3/
     * Each of the following pins is assigned to a PWM.
     * Uno  328     Reg     Tmr/Cntr    Bits    CtrlRegs        Scalars
     * 9    PB1     OC1A    1           16      TCCR1A/TCCR1B   1/8/64/256/1024
     * 10   PB2     OC1B    1           16      TCCR1A/TCCR1B   1/8/64/256/1024
     * 11   PB3     OC2A    2           8       TCCR2A/TCCR2B 1/8/32/64/256/1024
     * 3    PD3     OC2B    2           8       TCCR2A/TCCR2B 1/8/32/64/256/1024
     * 5    PD5     OC0B    0           8       TCCR0A/TCCR0B   1/8/64/256/1024
     * 6    PD6     OC0A    0           8       TCCR0A/TCCR0B   1/8/64/256/1024
     */

    if (use_b && pin == PORTB1) {
        /*
         * TCCR1A (Timer/Counter 1 Control Register A)
         * COM1A1, COM1A0: Clear OC1A on Compare Match                  10xxxxxx
         * COM1B1, COM1B0: Normal port operation, OC1B disconnected     xx00xxxx
         * WGM11, WGM10: Fast 8-bit PWM, TOP = 0xFF                     xxxxxx01
         */
        TCCR1A |= (_BV(COM1A1) | _BV(WGM10));
        /*
         * TCCR1B (Timer/Counter 1 Control Register B)
         * FOC1A, FOC1B: Irrelevant; non-PWM mode                       00xxxxxx
         * WGM12: Fast 8-bit PWM, TOP = 0xFF                            xxxx1xxx
         * CS12, CS11, CS10: Prescaler 64 (~976 Hz)                     xxxxx011
         */
        TCCR1B |= (_BV(WGM12) | _BV(CS11) | _BV(CS10));

        OCR1A = cycle;
        return 0;
    } else if (use_b && pin == PORTB2) {
        /*
         * TCCR1A (Timer/Counter 1 Control Register A)
         * COM1A1, COM1A0: Normal port operation, OC1A disconnected     00xxxxxx
         * COM1B1, COM1B0: Clear OC1B on Compare Match                  xx10xxxx
         * WGM11, WGM10: Fast 8-bit PWM, TOP = 0xFF                     xxxxxx01
         */
        TCCR1A |= (_BV(COM1B1) | _BV(WGM10));
        /*
         * TCCR1B (Timer/Counter 1 Control Register B)
         * FOC1A, FOC1B: Irrelevant; non-PWM mode                       00xxxxxx
         * WGM12: Fast 8-bit PWM, TOP = 0xFF                            xxxx1xxx
         * CS12, CS11, CS10: Prescaler 64 (~976 Hz)                     xxxxx011
         */
        TCCR1B |= (_BV(WGM12) | _BV(CS11) | _BV(CS10));

        OCR1B = cycle;
        return 0;
    } else if (use_b && pin == PORTB3) {
        /*
         * TCCR2A (Timer/Counter 2 Control Register A)
         * COM2A1, COM2A0: Clear OC2A on Compare Match                  10xxxxxx
         * COM2B1, COM2B0: Normal port operation, OC2B disconnected     xx00xxxx
         * WGM21, WGM20: Fast PWM, TOP = 0xFF                           xxxxxx11
         */
        TCCR2A |= (_BV(COM2A1) | _BV(WGM21) | _BV(WGM20));
        /*
         * TCCR2B (Timer/Counter 2 Control Register B)
         * FOC2A, FOC2B: Irrelevant; non-PWM mode                       00xxxxxx
         * WGM22: Fast PWM, TOP = 0xFF                                  xxxx0xxx
         * CS22, CS21, CS20: Prescaler 64 (~976 Hz)                     xxxxx100
         */
        TCCR2B |= (_BV(CS22));

        OCR2A = cycle;
        return 0;
    } else if (!use_b && pin == PORTD3) {
        /*
         * TCCR2A (Timer/Counter 2 Control Register A)
         * COM2A1, COM2A0: Normal port operation, OC2A disconnected     00xxxxxx
         * COM2B1, COM2B0: Clear OC2B on Compare Match                  xx10xxxx
         * WGM21, WGM20: Fast PWM, TOP = 0xFF                           xxxxxx11
         */
        TCCR2A |= (_BV(COM2B1) | _BV(WGM21) | _BV(WGM20));
        /*
         * TCCR2B (Timer/Counter 2 Control Register B)
         * FOC2A, FOC2B: Irrelevant; non-PWM mode                       00xxxxxx
         * WGM22: Fast PWM, TOP = 0xFF                                  xxxx0xxx
         * CS22, CS21, CS20: Prescaler 64 (~976 Hz)                     xxxxx100
         */
        TCCR2B |= (_BV(CS22));

        OCR2B = cycle;
        return 0;
    } else if (!use_b && pin == PORTD5) {
        /*
         * TCCR0A (Timer/Counter 0 Control Register A)
         * COM0A1, COM0A0: Normal port operation, OC0A disconnected     00xxxxxx
         * COM0B1, COM0B0: Clear OC0B on Compare Match                  xx10xxxx
         * WGM01, WGM00: Fast PWM, TOP = 0xFF                           xxxxxx11
         */
        TCCR0A |= (_BV(COM0B1) | _BV(WGM01) | _BV(WGM00));
        /*
         * TCCR0B (Timer/Counter 0 Control Register B)
         * FOC0A, FOC0B: Irrelevant; non-PWM mode                       00xxxxxx
         * WGM02: Fast PWM, TOP = 0xFF                                  xxxx0xxx
         * CS02, CS01, CS00: Prescaler 64 (~976 Hz)                     xxxxx011
         */
        TCCR0B |= (_BV(CS01) | _BV(CS00));

        OCR0B = cycle;
        return 0;
    } else if (!use_b && pin == PORTD6) {
        /*
         * TCCR0A (Timer/Counter 0 Control Register A)
         * COM0A1, COM0A0: Clear OC0A on Compare Match                  10xxxxxx
         * COM0B1, COM0B0: Normal port operation, OC0B disconnected     xx00xxxx
         * WGM01, WGM00: Fast PWM, TOP = 0xFF                           xxxxxx11
         */
        TCCR0A |= (_BV(COM0A1) | _BV(WGM01) | _BV(WGM00));
        /*
         * TCCR0B (Timer/Counter 0 Control Register B)
         * FOC0A, FOC0B: Irrelevant; non-PWM mode                       00xxxxxx
         * WGM02: Fast PWM, TOP = 0xFF                                  xxxx0xxx
         * CS02, CS01, CS00: Prescaler 64 (~976 Hz)                     xxxxx011
         */
        TCCR0B |= (_BV(CS01) | _BV(CS00));

        OCR0A = cycle;
        return 0;
    } else {
        // Not a PWM pin!!
        return 1;
    }
}
