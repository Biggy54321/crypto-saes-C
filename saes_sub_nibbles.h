#ifndef SAES_SUB_NIBBLES_H
#define SAES_SUB_NIBBLES_H

#include "./saes_types.h"

/* Substitute the given array of four nibbles with another four nibbles
 * (for encryption)
 */
void sub_nibbles(i8_t block[4]);

/* Substitute the given array of four nibbles with another four nibbles
 * (for decryption)
 */
void inv_sub_nibbles(i8_t block[4]);

#endif