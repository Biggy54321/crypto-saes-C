#include "./saes_types.h"
#include "./saes_gf.h"

/**
 * @brief Return the galois field addition of a and b in GF(2^4)
 *
 * @param a
 * @param b
 * @return i8_t
 */
i8_t gf_add(i8_t a, i8_t b) {

    return (a & 0x0F) ^ (b & 0x0F);
}

/**
 * @brief Return the galois field multiplication of a and b in GF(2^4)
 *
 * @param a
 * @param b
 * @return i8_t
 */
i8_t gf_mul(i8_t a, i8_t b) {

    i8_t p = 0;

    /* Mask the unwanted bits */
    a = a & 0x0F;
    b = b & 0x0F;

    /* While both the multiplicands are non-zero */
    while (a && b) {

        /* If LSB of b is 1 */
        if (b & 1) {

            /* Add the current a to p */
            p = p ^ a;
        }

        /* Update both a and b */
        a = a << 1;
        b = b >> 1;

        /* If a overflows beyond the 4th bit */
        if (a & (1 << GF_DEGREE)) {

            a = a ^ GF_REDUCING_POLY;
        }
    }

    return p;
}

