#ifndef SAES_ADD_RND_KEY_H
#define SAES_ADD_RND_KEY_H

#include "./saes_types.h"

/* Add the round key to the given block */
void add_rnd_key(i8_t block[4], i8_t rnd_key[4]);

#endif