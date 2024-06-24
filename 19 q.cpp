#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 8  // 64 bits
#define KEY_SIZE 24   // 192 bits

// 3DES encryption function
void encrypt_3des(unsigned char *plaintext, unsigned char *ciphertext, unsigned char *key) {
    unsigned char temp[BLOCK_SIZE];
    unsigned char block[BLOCK_SIZE];

    // Encrypt the plaintext using 3DES
    memcpy(block, plaintext, BLOCK_SIZE);
    des_encrypt(block, key, temp);
    des_decrypt(temp, key + 8, block);
    des_encrypt(block, key + 16, ciphertext);
}

// CBC encryption function
void encrypt_cbc(unsigned char *plaintext, unsigned char *ciphertext, unsigned char *key, unsigned char *iv, int length) {
    unsigned char prev_block[BLOCK_SIZE] = {0};
    unsigned char block[BLOCK_SIZE];

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        // XOR the plaintext block with the previous ciphertext block
        for (int j = 0; j < BLOCK_SIZE; j++) {
            block[j] = plaintext[i + j] ^ prev_block[j];
        }

        // Encrypt the block using 3DES
        encrypt_3des(block, ciphertext + i, key);

        // Update the previous ciphertext block
        memcpy(prev_block, ciphertext + i, BLOCK_SIZE);
    }
}

int main() {
    unsigned char plaintext[] = "This is a secret message.";
    unsigned char key[KEY_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    unsigned char iv[BLOCK_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char ciphertext[sizeof(plaintext)];

    // Encrypt the plaintext using CBC mode with 3DES
    encrypt_cbc(plaintext, ciphertext, key, iv, sizeof(plaintext));

    // Print the ciphertext
    printf("Ciphertext: ");
    for (int i = 0; i < sizeof(plaintext); i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    return 0;
}
