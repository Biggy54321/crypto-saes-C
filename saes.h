#ifndef SAES_H
#define SAES_H

#include "./saes_types.h"

/* Encrypt the given plaintext message to the ciphertext */
void saes_encrypt(i8_t *plaintext, i8_t *ciphertext, i64_t size, i16_t key);

/* Decrypt the given ciphertext message to the plaintext */
void saes_decrypt(i8_t *ciphertext, i8_t *plaintext, i64_t size, i16_t key);

#endif