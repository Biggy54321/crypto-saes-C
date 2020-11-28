#ifndef SAES_KEY_EXP_H
#define SAES_KEY_EXP_H

#include "./saes_types.h"

/* Expand the given 16 bit key to three subkeys nibble array */
void key_exp(i16_t key, i8_t subkey[3][4]);

#endif