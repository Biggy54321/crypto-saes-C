#include "./saes_types.h"
#include "./saes_sub_nibbles.h"

/**
 * @brief Substitute the given nibble using the given 4x4 S-box table
 *
 * @param nibble
 * @param _tab
 * @return i8_t
 */
static inline i8_t _sub(i8_t nibble, i8_t _tab[4][4]) {

    /* Get the row value */
    int row = (nibble & 0b1100) >> 2;
    int col = (nibble & 0b0011);

    /* Return the substitution */
    return _tab[row][col];
}

/**
 * @brief Substitute the given array of four nibbles with another four nibbles
 *        (for encryption)
 *
 * @param block
 */
void sub_nibbles(i8_t block[4]) {

    static i8_t _tab[4][4] = {
        {9, 4, 10, 11},
        {13, 1, 8, 5},
        {6, 2, 0, 3},
        {12, 14, 15, 7}
    };

    for (int i = 0; i < 4; i++) {

        block[i] = _sub(block[i], _tab);
    }
}

/**
 * @brief Substitute the given array of four nibbles with another four nibbles
 *        (for decryption)
 *
 * @param block
 */
void inv_sub_nibbles(i8_t block[4]) {

    static i8_t _tab[4][4] = {
        {10, 5, 9, 11},
        {1, 7, 8, 15},
        {6, 0, 2, 3},
        {12, 4, 13, 14}
    };

    for (int i = 0; i < 4; i++) {

        block[i] = _sub(block[i], _tab);
    }
}
