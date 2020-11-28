# Simplified Advanced Encryption Standard Algorithm

* The S-AES algorithm is implemented in two different programs each using the
same set of library routines.
* The two programs are **saes_enc.c** and **saes_dec.c**, for encryption and
decryption of the input messages respectively.
* Both the programs take the key as a command line argument and the message through
the standard input and prints the result message on the standard output.
* The library routine implemented involves the code for the following operations
    + Different data types required
    + Add round key
    + Substitute nibbles / Inverse substitute nibbles
    + Shift rows / Inverse shift rows
    + Mix columns / Inverse mix columns
    + Key expansion
    + Galois field operations
* The parameters of S-DES implemented

    |**Parameter**|**Value**|
    |-|-|
    |Plaintext block size| 16 bits|
    |Key size|16 bits|
    |Number of rounds|2|
    |Operation mode|Electronic Code Book (ECB)|

### Program source

#### Data types code (saes_types.h)

Provides the different data types of various sizes required for S-AES

#### Add round key code (saes_add_rnd_key.h and saes_add_rnd_key.c)

Provides the function for adding (xoring) the given subkey with the block of data
(plaintext or intermediate block), where the subkey and block of data are originally
16 bit values separated over an array of 4 nibbles.

#### Substitution and Inverse Substitution code (saes_sub_nibbles.h and saes_sub_nibbles.c)

Provides the code for performing the substitution of the 4 nibbles in the 16 bit
block using two separate S-Boxes for encryption and decryption.


#### Shift rows and Inverse shift rows code (saes_shft_rows.h and saes_shft_rows.c)

Provides the functions for performing the shifting of the rows (i.e. the 16 bit blocks
are visualized as a matrix of size 2x2 where each element is a nibble).


#### Galois field arithmetic code (saes_gf.h and saes_gf.c)

Provides the functions to perform Galois Field addition and multiplication
in the field **GF(2^4)** where the reducing polynomial is **x^4 + x + 1**.
[These functions are required for the mix-columns operation]


#### Mix columns and Inverse mix columns code (saes_mix_cols.h and saes_mix_cols.c)

Provides the functions for mixing the columns i.e. performing matrix multiplication
of the 16 bit data block with some data block depending on encryption and decryption.


#### Key expansion (Subkey generation) code (saes_key_exp.h and saes_key_exp.c)

Provides the function to expand the given 16 bit key entered by the user to
three 16 bit subkeys required for the initial round and the two normal rounds
of S-AES.

#### S-AES Encryption and Decryption code (saes.h and saes.c)

Provides the functions which uses all of the above modules to perform the
encryption and decryption of the input array of 16 bit blocks and key.

#### Driver programs for encryption and decryption (saes_enc.c and saes_dec.c)

Provides the two application programs which use the above implemented library
functions to provide users a program that they can use to encrypt and decrypt
random strings using S-AES algorithm.

### Program usage

The programs can be compiled as follows

```zsh
$> # For encryption program (saes_enc)
$> cc saes_add_rnd_key.c saes.c saes_enc.c saes_gf.c saes_key_exp.c \
    saes_mix_cols.c saes_shft_rows.c saes_sub_nibbles.c -o saes_enc
$> # For decryption program (saes_dec)
$> cc saes_add_rnd_key.c saes.c saes_dec.c saes_gf.c saes_key_exp.c \
    saes_mix_cols.c saes_shft_rows.c saes_sub_nibbles.c -o saes_dec
```

The programs can be used as follows:

```zsh
$> # For encryption
$> ./saes_enc <key>
<plaintext_msg> (input)
<ciphertext_msg> (output)
```

```zsh
$> # For decryption
$> ./saes_dec <key>
<ciphertext_msg> (input)
<plaintext_msg> (output)
```

### Program output

To test the correctness of the programs, we can run the encryption program,
and give the output of the encryption program i.e. the ciphertext immediately
to the decryption program. If the output of the decryption program at the end
as same as the input then, both the programs are correct

For doing that test do the following

```zsh
$> ./saes_enc <key> | ./saes_dec <key>
<plaintext_msg> (input)
<plaintext_msg> (output)
```

### References

http://read.pudn.com/downloads222/ebook/1044300/%E9%99%84%E5%BD%95P%20Simplified%20AES%20(S-AES).pdf