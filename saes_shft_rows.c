#include "./saes_types.h"
#include "./saes_shft_rows.h"

/**
 * @brief Shift the second row to the left/right by one nibble, i.e. swap the
 *        nibbles
 *
 * @param block
 */
void shft_rows(i8_t block[4]) {

    /* Swap the nibbles n1 and n3, which are the elements 0 and 2 of the
     * nibble array
     */
    i8_t temp = block[0];
    block[0] = block[2];
    block[2] = temp;
}