#ifndef BITOPS_H
#define BITOPS_H

#define SET_BIT(byte, n) (byte |= (1 << n))  /* Set bit n of byte */
#define CLR_BIT(byte, n) (byte &= ~(1 << n)) /* Clear bit n of byte */
#define CHK_BIT(byte, n) (byte & (1 << n))   /* Check bit y in byte */

#endif // BITOPS_H
