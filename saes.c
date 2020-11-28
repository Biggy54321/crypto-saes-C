#include "./saes_types.h"
#include "./saes_add_rnd_key.h"
#include "./saes_sub_nibbles.h"
#include "./saes_shft_rows.h"
#include "./saes_mix_cols.h"
#include "./saes_key_exp.h"
#include "./saes.h"

/**
 * @brief Encrypt a 16 bit block of plaintext
 *
 * @param plainblock
 * @param subkey
 * @return i16_t
 */
i16_t _saes_enc_block(i16_t plainblock, i8_t subkey[3][4]) {

    i8_t block[4];

    /* Convert the 16 bits to 4 nibble array */
    block[0] = (plainblock & 0x000F);
    block[1] = (plainblock & 0x00F0) >> 4;
    block[2] = (plainblock & 0x0F00) >> 8;
    block[3] = (plainblock & 0xF000) >> 12;

    /* Pre-round */

    /* Add round key */
    add_rnd_key(block, subkey[0]);

    /* Round 1 */

    /* Substitution */
    sub_nibbles(block);
    /* Shift rows */
    shft_rows(block);
    /* Mix columns */
    mix_cols(block);
    /* Add round key */
    add_rnd_key(block, subkey[1]);

    /* Round 2 */

    /* Substitution */
    sub_nibbles(block);
    /* Shift rows */
    shft_rows(block);
    /* Add round key */
    add_rnd_key(block, subkey[2]);

    /* Combine the 4 nibbles and return the 16 bits */
    return (((i16_t)block[3] << 12) |
            ((i16_t)block[2] << 8) |
            ((i16_t)block[1] << 4) |
            ((i16_t)block[0]));
}

/**
 * @brief Decrypt a 16 bit block of ciphertext
 *
 * @param cipherblock
 * @param subkey
 * @return i16_t
 */
i16_t _saes_dec_block(i16_t cipherblock, i8_t subkey[3][4]) {

    i8_t block[4];

    /* Convert the 16 bits to 4 nibble array */
    block[0] = (cipherblock & 0x000F);
    block[1] = (cipherblock & 0x00F0) >> 4;
    block[2] = (cipherblock & 0x0F00) >> 8;
    block[3] = (cipherblock & 0xF000) >> 12;

    /* Pre-round */

    /* Add round key */
    add_rnd_key(block, subkey[2]);

    /* First round */

    /* Inverse shift rows */
    inv_shft_rows(block);
    /* Inverse substitution */
    inv_sub_nibbles(block);
    /* Add round key */
    add_rnd_key(block, subkey[1]);
    /* Inverse mix columns */
    inv_mix_cols(block);

    /* Second round */

    /* Inverse shift rows */
    inv_shft_rows(block);
    /* Inverse substitution */
    inv_sub_nibbles(block);
    /* Add round key */
    add_rnd_key(block, subkey[0]);

    /* Combine the 4 nibbles and return the 16 bits */
    return (((i16_t)block[3] << 12) |
            ((i16_t)block[2] << 8) |
            ((i16_t)block[1] << 4) |
            ((i16_t)block[0]));
}

/**
 * @brief Encrypt the given plaintext message to the ciphertext
 *
 * @param plaintext
 * @param ciphertext
 * @param size
 * @param key
 */
void saes_encrypt(i8_t *plaintext, i8_t *ciphertext, i64_t size, i16_t key) {

    i8_t subkey[3][4];
    i16_t *plainblock = (i16_t *)plaintext;
    i16_t *cipherblock = (i16_t *)ciphertext;

    /* Generate the subkeys */
    key_exp(key, subkey);

    /* Encrypt block by block */
    while (plainblock < (i16_t *)(plaintext + size)) {

        *cipherblock = _saes_enc_block(*plainblock, subkey);

        plainblock++;
        cipherblock++;
    }
}

/**
 * @brief Decrypt the given ciphertext message to the plaintext
 *
 * @param ciphertext
 * @param plaintext
 * @param size
 * @param key
 */
void saes_decrypt(i8_t *ciphertext, i8_t *plaintext, i64_t size, i16_t key) {

    i8_t subkey[3][4];
    i16_t *plainblock = (i16_t *)plaintext;
    i16_t *cipherblock = (i16_t *)ciphertext;

    /* Generate the subkeys */
    key_exp(key, subkey);

    /* Encrypt block by block */
    while (plainblock < (i16_t *)(plaintext + size)) {

        *plainblock = _saes_dec_block(*cipherblock, subkey);

        plainblock++;
        cipherblock++;
    }
}
