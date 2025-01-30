#ifndef DATACONV_H
#define DATACONV_H

// Get the 10-bit analogue to digital converter reading as volts.
#define ADC_TO_V(adc) ((5. / 1023.) * adc)

#endif // DATACONV_H
