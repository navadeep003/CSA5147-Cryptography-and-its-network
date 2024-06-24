#include <stdio.h>
#include <ctype.h>
#include <string.h> // Needed for strlen function

// Function to compute the greatest common divisor (gcd)
int gcd(int a, int b) {
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to compute the multiplicative inverse of a modulo m
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // If inverse does not exist
}

// Function to decrypt a ciphertext character using affine cipher
char decryptChar(int a, int b, char cipherChar) {
    if (isalpha(cipherChar)) {
        // Convert ciphertext character to 0-25
        int c = toupper(cipherChar) - 'A';
        // Compute plaintext character
        int a_inv = modInverse(a, 26);
        if (a_inv == -1) {
            printf("Error: Decryption not possible for this key.\n");
            return cipherChar;
        } else {
            int p = (a_inv * (c - b + 26)) % 26;
            return 'A' + p;
        }
    } else {
        return cipherChar; // Return character as is if not a letter
    }
}

int main() {
    // Given ciphertext most frequent letters
    char mostFrequent = 'B'; // Corresponds to 'E'
    char secondMostFrequent = 'U'; // Corresponds to 'T'

    // Positions in the alphabet (0-based)
    int C1 = mostFrequent - 'A';
    int C2 = secondMostFrequent - 'A';
    int P1 = 'E' - 'A';
    int P2 = 'T' - 'A';

    // Set up the equations
    // (a * P1 + b) % 26 = C1
    // (a * P2 + b) % 26 = C2

    // Solve for a and b
    int a, b;
    int found = 0; // Flag to indicate when we found the keys
    for (a = 0; a < 26; a++) {
        if (gcd(a, 26) != 1) continue; // a must be coprime with 26

        for (b = 0; b < 26; b++) {
            if ((a * P1 + b) % 26 == C1 && (a * P2 + b) % 26 == C2) {
                found = 1; // Set flag to indicate keys are found
                break;
            }
        }
        if (found) break;
    }

    if (!found) {
        printf("Error: No valid key found.\n");
        return 1;
    }


    printf("Found keys: a = %d, b = %d\n", a, b);

    // Ciphertext to decrypt
    char ciphertext[] = "B U ZZZ U B"; // Example ciphertext, replace with actual ciphertext
    char decryptedtext[100];

    // Decrypt the ciphertext
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        decryptedtext[i] = decryptChar(a, b, ciphertext[i]);
    }
    decryptedtext[strlen(ciphertext)] = '\0';

    printf("Ciphertext: %s\n", ciphertext);
    printf("Decrypted:  %s\n", decryptedtext);

    return 0;
}
