#include <avr/io.h>

#include "./bitops.h"

unsigned short adc_read(unsigned char channel) {
    // Select the ADC channel (0-7) & clear MUX bits
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

    // Start conversion
    SET_BIT(ADCSRA, ADSC);

    // Busy wait until conversion is complete...
    while (CHK_BIT(ADCSRA, ADSC))
        ;

    return ADC;
}
