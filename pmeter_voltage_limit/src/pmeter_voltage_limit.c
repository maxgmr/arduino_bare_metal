#include "../../libs/bitops.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL
#define BAUD 57600

#include <util/setbaud.h>

#define V_CAUTION 3.
#define V_WARNING 4.

#define ADC_TO_V(adc) ((5. / 1023.) * adc)

#define CAUTION_PORT PORTB0
#define WARNING_PORT PORTB1

#define PMETER_CHANNEL PORTC5

void main(void) __attribute__((noreturn));
void init_uart() {
    // Enable double speed mode
    SET_BIT(UCSR0A, U2X0);

    // Set UART speed
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

    // Data frame size = 8 bits
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

    // Enable transmission
    UCSR0B = (1 << TXEN0);
}

void init_adc() {
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

unsigned short analogue_read(unsigned char channel) {
    // Select the ADC channel (0-7) & clear MUX bits
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

    // Start conversion
    SET_BIT(ADCSRA, ADSC);

    // Busy wait until conversion is complete...
    while (CHK_BIT(ADCSRA, ADSC))
        ;

    return ADC;
}

void voltage_check(unsigned char pin, float voltage, float voltage_limit) {
    if (voltage > voltage_limit) {
        SET_BIT(PORTB, pin);
    } else {
        CLR_BIT(PORTB, pin);
    }
}

void main(void) {
    // Set pins 8 & 9 to output mode
    DDRB |= 0x03;
    // Ensure pin A5 is in read mode
    CLR_BIT(DDRC, DDC5);
    // ADC setup
    init_adc();
    // UART setup
    init_uart();

    for (;;) {
        // Read potentiometer
        unsigned short pmeter_read = analogue_read(PMETER_CHANNEL);
        float voltage = ADC_TO_V(pmeter_read);

        voltage_check(WARNING_PORT, voltage, V_WARNING);
        voltage_check(CAUTION_PORT, voltage, V_CAUTION);
    }
}
