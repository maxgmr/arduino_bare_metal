#include <avr/interrupt.h>
#include <avr/io.h>

#include "./bitops.h"

void init_adc(void) {
    // Disable interrupts whilst modifying ADC settings
    unsigned char old_sreg = SREG;
    cli();

    // Disable power reduction ADC bit to power on the ADC
    CLR_BIT(PRR, PRADC);
    /*
     * ADMUX:
     * AVCC reference voltage (5V)  01xxxxxx
     * Right aligned                xx0xxxxx
     * MUX 0                        xxx00000
     */
    ADMUX = 0x40;
    /*
     * ADCSRB:
     * Disable comparator muxer     x0xxxxxx
     * Highest mux bit set to 0     xxxx0xxx
     * Free running trigger mode    xxxxx000
     */
    ADCSRB = 0x00;
    /*
     * ADCSRA:
     * Enable ADC                   1xxxxxxx
     * Don't convert immediately    x0xxxxxx
     * Disable autotriggering       xx0xxxxx
     * Clear interrupt flag         xxx1xxxx
     * Disable interrupt            xxxx0xxx
     * Prescaler select (/128)      xxxxx111
     */
    ADCSRA = 0x97;

    // Restore interrupt flags
    SREG = old_sreg;
}
