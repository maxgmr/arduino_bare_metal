#ifndef PWMW_H
#define PWMW_H

#include <stdint.h>

uint8_t pwm_write_fast(uint8_t pin, bool use_d, uint8_t cycle);

#endif // PWMW_H
