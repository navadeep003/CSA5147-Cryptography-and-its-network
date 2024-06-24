#include <stdio.h>
#include <stdlib.h>

// Function to compute the gcd of two numbers
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Function to perform affine encryption
char affineEncrypt(char p, int a, int b) {
    if ('A' <= p && p <= 'Z') {
        return (char) ((((a * (p - 'A')) + b) % 26) + 'A');
    } else if ('a' <= p && p <= 'z') {
        return (char) ((((a * (p - 'a')) + b) % 26) + 'a');
    } else {
        // If character is not an alphabet, return it as is
        return p;
    }
}

// Function to find the multiplicative inverse of a under modulo m
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 0) {
            return x;
        }
    }
    return -1;
}

// Function to perform affine decryption
char affineDecrypt(char c, int a, int b) {
    int a_inv = modInverse(a, 26);
    if ('A' <= c && c <= 'Z') {
        return (char) ((a_inv * ((c - 'A' - b + 26) % 26)) % 26 + 'A');
    } else if ('a' <= c && c <= 'z') {
        return (char) ((a_inv * ((c - 'a' - b + 26) % 26)) % 26 + 'a');
    } else {
        // If character is not an alphabet, return it as is
        return c;
    }
}

int main() {
    char plaintext[] = "HELLO WORLD";
    int a = 5; // Choose a value of a
    int b = 8; // Choose a value of b

    // Check if a is valid (gcd(a, 26) should be 1)
    if (gcd(a, 26) != 1) {
        printf("The value of a is not valid. It must be coprime with 26.\n");
        return -1;
    }

    printf("Plaintext: %s\n", plaintext);

    // Encrypt the plaintext
    for (int i = 0; plaintext[i] != '\0'; i++) {
        plaintext[i] = affineEncrypt(plaintext[i], a, b);
    }
    printf("Ciphertext: %s\n", plaintext);

    // Decrypt the ciphertext
    for (int i = 0; plaintext[i] != '\0'; i++) {
        plaintext[i] = affineDecrypt(plaintext[i], a, b);
    }
    printf("Decrypted text: %s\n", plaintext);

    return 0;
}
