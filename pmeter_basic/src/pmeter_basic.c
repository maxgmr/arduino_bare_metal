#include <avr/io.h>

#include "../../libs/adci.h"
#include "../../libs/adcr.h"
#include "../../libs/bitops.h"
#include "../../libs/dataconv.h"
#include "../../libs/uarti.h"
#include "../../libs/uartw.h"

#define MV_IN_V 1000

#define LOOPS_BEFORE_SERIAL_OUT 10000

#define PMETER_DD DDRC
#define PMETER_DD_CHANNEL DDC0
#define PMETER_REG PORTC
#define PMETER_CHANNEL PORTC0

void main(void) __attribute__((noreturn));

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
        float voltage = ADC_TO_V(pmeter_in);
        unsigned short mvoltage = (int)(voltage * MV_IN_V);

        if (++serial_out_count > LOOPS_BEFORE_SERIAL_OUT) {
            printf("%u mV\n", mvoltage);
            serial_out_count = 0;
        }
    }
}
