#include <stdio.h>
#include <stdlib.h>
#include "./saes.h"

/* Max plaintext/ciphertext message size in bytes */
#define MAX_TEXT_SIZE (2048u)

/**
 * @brief Driver program for encrypting the plaintext read from STDIN and print
 *        the ciphertext to STDOUT. The key is taken as a command line argument
 *
 * @param argc
 * @param argv
 */
void main(int argc, char *argv[]) {

    i8_t plaintext[MAX_TEXT_SIZE];
    i8_t ciphertext[MAX_TEXT_SIZE];
    i16_t key;
    i64_t size = 0;

    /* Check the arguments */
    if (argc < 2) {

        fprintf(stderr, "Pass the KEY as a command line argument\n");
        return;
    }

    /* Get the key from the cmd arg */
    key = atoi(argv[1]);

    /* Read the plaintext message */
    while (scanf("%c", &plaintext[size]) != -1) {

        size++;
    }

    /* Pad the message with a NULL byte if its size is odd */
    if (size & 1) {

        plaintext[size] = '\0';
        size++;
    }

    /* Encrypt the plaintext message */
    saes_encrypt(plaintext, ciphertext, size, key);

    /* Print the ciphertext message */
    for (int i = 0; i < size; i++) {

        printf("%c", ciphertext[i]);
    }
}