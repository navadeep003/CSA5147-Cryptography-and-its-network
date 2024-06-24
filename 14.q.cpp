#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_TEXT_LENGTH 100
#define ALPHABET_SIZE 26

// Function to compute the greatest common divisor (GCD) of two numbers
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to find modular inverse using extended Euclidean algorithm
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;  // modular inverse doesn't exist
}

// Function to convert character to numeric equivalent (A=0, B=1, ..., Z=25)
int char_to_num(char ch) {
    return ch - 'A';
}

// Function to convert numeric equivalent to character (0=A, 1=B, ..., 25=Z)
char num_to_char(int num) {
    return num + 'A';
}

// Function to perform matrix multiplication in Hill cipher
void matrix_multiply(int key[3][3], int plaintext_vector[], int result_vector[], int size) {
    for (int i = 0; i < size; i++) {
        result_vector[i] = 0;
        for (int j = 0; j < size; j++) {
            result_vector[i] += key[i][j] * plaintext_vector[j];
        }
        result_vector[i] %= ALPHABET_SIZE;
    }
}

// Function to perform known plaintext attack on Hill cipher
void known_plaintext_attack(int key[3][3], char plaintext[], char ciphertext[]) {
    int plaintext_vector[3], ciphertext_vector[3], decrypted_vector[3];
    int determinant = key[0][0] * (key[1][1] * key[2][2] - key[1][2] * key[2][1])
                    - key[0][1] * (key[1][0] * key[2][2] - key[1][2] * key[2][0])
                    + key[0][2] * (key[1][0] * key[2][1] - key[1][1] * key[2][0]);
    
    int det_inverse = mod_inverse(determinant, ALPHABET_SIZE);
    
    // Calculate adjugate matrix
    int adj[3][3];
    adj[0][0] = key[1][1] * key[2][2] - key[1][2] * key[2][1];
    adj[0][1] = key[0][2] * key[2][1] - key[0][1] * key[2][2];
    adj[0][2] = key[0][1] * key[1][2] - key[0][2] * key[1][1];
    adj[1][0] = key[1][2] * key[2][0] - key[1][0] * key[2][2];
    adj[1][1] = key[0][0] * key[2][2] - key[0][2] * key[2][0];
    adj[1][2] = key[0][2] * key[1][0] - key[0][0] * key[1][2];
    adj[2][0] = key[1][0] * key[2][1] - key[1][1] * key[2][0];
    adj[2][1] = key[0][1] * key[2][0] - key[0][0] * key[2][1];
    adj[2][2] = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    
    // Find modular inverse of determinant
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            adj[i][j] = (adj[i][j] + ALPHABET_SIZE) % ALPHABET_SIZE;
        }
    }
    
    // Decrypt using the found key
    for (int i = 0; i < strlen(plaintext); i += 3) {
        plaintext_vector[0] = char_to_num(plaintext[i]);
        plaintext_vector[1] = char_to_num(plaintext[i+1]);
        plaintext_vector[2] = char_to_num(plaintext[i+2]);
        
        ciphertext_vector[0] = char_to_num(ciphertext[i]);
        ciphertext_vector[1] = char_to_num(ciphertext[i+1]);
        ciphertext_vector[2] = char_to_num(ciphertext[i+2]);
        
        matrix_multiply(adj, ciphertext_vector, decrypted_vector, 3);
        
        for (int j = 0; j < 3; j++) {
            plaintext[i + j] = num_to_char((det_inverse * decrypted_vector[j]) % ALPHABET_SIZE);
        }
    }
}
int main() {
    char plaintext[MAX_TEXT_LENGTH], ciphertext[MAX_TEXT_LENGTH];
    int key[3][3] = {{6, 24, 1}, {13, 16, 10}, {20, 17, 15}}; 
    printf("Enter the known plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
    printf("Enter the corresponding ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';
    known_plaintext_attack(key, plaintext, ciphertext);
    printf("Deduced Key Matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", key[i][j]);
        }
        printf("\n");
    }
    printf("Decrypted Plaintext: %s\n", plaintext);
    
    return 0;
}
