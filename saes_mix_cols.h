#ifndef SAES_MIX_COLS_H
#define SAES_MIX_COLS_H

#include "./saes_types.h"

/* Mix the columns of the given 4 nibbles, used for encryption */
void mix_cols(i8_t block[4]);

/* Mix the columns of the given 4 nibbles, used for decryption */
void inv_mix_cols(i8_t block[4]);

#endif