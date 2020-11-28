#ifndef SAES_SHFT_ROWS_H
#define SAES_SHFT_ROWS_H

#include "./saes_types.h"

/* Shift rows operation for encryption */
void shft_rows(i8_t block[4]);

/* Inverse shift rows operation decryption */
#define inv_shft_rows shft_rows

#endif