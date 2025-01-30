#include <avr/io.h>

#include "../../libs/adci.h"
#include "../../libs/adcr.h"
#include "../../libs/bitops.h"
#include "../../libs/dataconv.h"
#include "../../libs/uarti.h"
#include "../../libs/uartw.h"

#define LOOPS_BEFORE_SERIAL_OUT 10000

#define PMETER_DD DDRC
#define PMETER_DD_CHANNEL DDC0
#define PMETER_REG PORTC
#define PMETER_CHANNEL PORTC0

#define LED_DD DDRD
/*
 * D7, D6 input             00xxxxxx
 * D5, D4, D3, D2 output    xx1111xx
 * D1, D0 input             xxxxxx00
 */
#define PMETER_DD_CHANNELS 0xff
#define LED_REG PORTD

#define BLU_CHANNEL PORTD5
#define GRN_CHANNEL PORTD4
#define YEL_CHANNEL PORTD3
#define RED_CHANNEL PORTD2

// Limits are in mV
#define BLU_LIMIT 1000
#define GRN_LIMIT 2000
#define YEL_LIMIT 3000
#define RED_LIMIT 4000

void main(void) __attribute__((noreturn));

void check_voltage(unsigned char channel, unsigned short mvoltage,
                   unsigned short mv_limit) {
    if (mvoltage > mv_limit) {
        SET_BIT(LED_REG, channel);
    } else {
        CLR_BIT(LED_REG, channel);
    }
}

void main(void) {
    // Ensure potentiometer input is set to read
    CLR_BIT(PMETER_DD, PMETER_DD_CHANNEL);
    // Set up analogue-digital converter
    init_adc();
    // Set up universal asynchronous receiver/transmitter
    init_uart();
    stdout = &uart_out;
    // Create counter for serial out frequency
    unsigned int serial_out_count = 0;

    for (;;) {
        unsigned short pmeter_in = adc_read(PMETER_CHANNEL);
        unsigned short mvoltage = ADC_TO_MILLIV(pmeter_in);

        // Turn LEDs on or off according to the voltage
        check_voltage(BLU_CHANNEL, mvoltage, BLU_LIMIT);
        check_voltage(GRN_CHANNEL, mvoltage, GRN_LIMIT);
        check_voltage(YEL_CHANNEL, mvoltage, YEL_LIMIT);
        check_voltage(RED_CHANNEL, mvoltage, RED_LIMIT);

        // Print the millivolts every once in a while
        if (++serial_out_count > LOOPS_BEFORE_SERIAL_OUT) {
            printf("%u mV\n", mvoltage);
            serial_out_count = 0;
        }
    }
}
