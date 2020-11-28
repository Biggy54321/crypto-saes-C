#ifndef SAES_GF_H
#define SAES_GF_H

#include "./saes_types.h"

/* Galois Field Degree */
#define GF_DEGREE        (0x04)
/* Reducing polynomial for GF(2^4) */
#define GF_REDUCING_POLY (0x13)

/* Addition in GF(2^4) */
i8_t gf_add(i8_t a, i8_t b);

/* Multiplication in GF(2^4) */
i8_t gf_mul(i8_t a, i8_t b);

#endif