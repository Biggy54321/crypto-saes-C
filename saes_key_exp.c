#include "./saes_types.h"
#include "./saes_key_exp.h"

/* Round constants for two rounds */
#define R_CON_1 0x80
#define R_CON_2 0x30

/**
 * @brief Find the temporary word given the previous word and the round constant
 *
 * @param w
 * @param r_con
 * @return i8_t
 */
static i8_t _find_tmp_word(i8_t w, i8_t r_con) {

    i8_t tmp;
    i8_t row;
    i8_t col;

    /* Substitution box table */
    static i8_t _tab[4][4] = {
        {9, 4, 10, 11},
        {13, 1, 8, 5},
        {6, 2, 0, 3},
        {12, 14, 15, 7}
    };

    /* Rotate the nibbles of the given word */
    tmp = ((w & 0x0F) << 4) | ((w & 0xF0) >> 4);

    /* Substitute the first nibble */
    row = (tmp & 0x0C) >> 2;
    col = (tmp & 0x03);
    tmp = (tmp & 0xF0);
    tmp = (tmp | _tab[row][col]);

    /* Substitute the second nibble */
    row = (tmp & 0xC0) >> 6;
    col = (tmp & 0x30) >> 4;
    tmp = (tmp & 0x0F);
    tmp = (tmp | _tab[row][col] << 4);

    /* Exor with the round constant */
    tmp = tmp ^ r_con;

    return tmp;
}

/**
 * @brief Expand the given 16 bit key into nibble arrays for each of the three
 *        subkeys
 *
 * @param key
 * @param subkey
 */
void key_exp(i16_t key, i8_t subkey[3][4]) {

    i8_t w0;
    i8_t w1;
    i8_t w2;
    i8_t w3;
    i8_t w4;
    i8_t w5;
    i8_t t2;
    i8_t t4;

    /* Get the pre-round subkey */
    w0 = (key & 0xFF00) >> 8;
    w1 = (key & 0x00FF);

    /* Get the first round subkey */
    t2 = _find_tmp_word(w1, R_CON_1);
    w2 = t2 ^ w0;
    w3 = w2 ^ w1;

    /* Get the second round subkey */
    t4 = _find_tmp_word(w3, R_CON_2);
    w4 = t4 ^ w2;
    w5 = w4 ^ w3;

    /* Convert the 16 bit keys to the nibble arrays */
    subkey[0][0] = (w1 & 0x0F);
    subkey[0][1] = (w1 & 0xF0) >> 4;
    subkey[0][2] = (w0 & 0x0F);
    subkey[0][3] = (w0 & 0xF0) >> 4;

    subkey[1][0] = (w3 & 0x0F);
    subkey[1][1] = (w3 & 0xF0) >> 4;
    subkey[1][2] = (w2 & 0x0F);
    subkey[1][3] = (w2 & 0xF0) >> 4;

    subkey[2][0] = (w5 & 0x0F);
    subkey[2][1] = (w5 & 0xF0) >> 4;
    subkey[2][2] = (w4 & 0x0F);
    subkey[2][3] = (w4 & 0xF0) >> 4;
}