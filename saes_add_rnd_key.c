#include "./saes_types.h"
#include "./saes_add_rnd_key.h"

/**
 * @brief Add the four nibbles of round key nibble by nibble to the block
 *
 * @param block
 * @param rnd_key
 */
void add_rnd_key(i8_t block[4], i8_t rnd_key[4]) {

    *((i32_t *)block) ^= *((i32_t *)rnd_key);
}