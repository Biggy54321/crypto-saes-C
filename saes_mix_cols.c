#include "./saes_types.h"
#include "./saes_gf.h"
#include "./saes_mix_cols.h"

/**
 * @brief Matrix muliply two 2x2 matrices under GF(2^4) field
 *
 * @param _tab
 * @param block
 */
void _mat_mul(i8_t const_mat[4], i8_t block[4]) {

    /* Get the constant matrix nibbles */
    i8_t c0 = const_mat[3];
    i8_t c1 = const_mat[2];
    i8_t c2 = const_mat[1];
    i8_t c3 = const_mat[0];

    /* Get the block matrix nibbles */
    i8_t n0 = block[3];
    i8_t n1 = block[2];
    i8_t n2 = block[1];
    i8_t n3 = block[0];

    /* Compute each element and store the result in the block array */
    block[3] = gf_add(gf_mul(c0, n0), gf_mul(c2, n1));
    block[2] = gf_add(gf_mul(c1, n0), gf_mul(c3, n1));
    block[1] = gf_add(gf_mul(c0, n2), gf_mul(c2, n3));
    block[0] = gf_add(gf_mul(c1, n2), gf_mul(c3, n3));
}

/**
 * @brief Mix the columns of the given 4 nibbles, used for encryption
 *        using galois field matrix multiplication
 *
 * @param block
 */
void mix_cols(i8_t block[4]) {

    static i8_t _tab[4] = {1, 4, 4, 1};

    _mat_mul(_tab, block);
}

/**
 * @brief Mix the columns of the given 4 nibbles, used for decryption
 *        using galois field matrix multiplication
 *
 * @param block
 */
void inv_mix_cols(i8_t block[4]) {

    static i8_t _tab[4] = {9, 2, 2, 9};

    _mat_mul(_tab, block);
}
