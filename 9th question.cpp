#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void createMatrix(char key[], char matrix[SIZE][SIZE]);
void prepareText(char text[], char preparedText[]);
void encrypt(char plaintext[], char ciphertext[], char matrix[SIZE][SIZE]);
void decrypt(char ciphertext[], char decryptedText[], char matrix[SIZE][SIZE]);
void findPosition(char matrix[SIZE][SIZE], char ch, int *row, int *col);

int main() {
    char key[] = "KEYWORD";  // Example key
    char plaintext[] = "PT109MESSAGE";  // Example plaintext message
    char preparedText[100];
    char ciphertext[100];
    char decryptedText[100];
    
    char matrix[SIZE][SIZE];

    // Create the Playfair cipher matrix
    createMatrix(key, matrix);

    // Prepare the plaintext
    prepareText(plaintext, preparedText);

    // Encrypt the prepared plaintext
    encrypt(preparedText, ciphertext, matrix);
    printf("Encrypted Text: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, decryptedText, matrix);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}

void createMatrix(char key[], char matrix[SIZE][SIZE]) {
    int flag[26] = {0};
    int i, j, k, len;
    char current;

    len = strlen(key);
    k = 0;

    // Fill the matrix with the key
    for (i = 0; i < len; i++) {
        current = toupper(key[i]);
        if (current == 'J') {
            current = 'I';  // Treat I and J as the same letter
        }
        if (!flag[current - 'A']) {
            matrix[k / SIZE][k % SIZE] = current;
            flag[current - 'A'] = 1;
            k++;
        }
    }

    // Fill the remaining letters in the matrix
    for (i = 0; i < 26; i++) {
        if (!flag[i] && 'A' + i != 'J') {
            matrix[k / SIZE][k % SIZE] = 'A' + i;
            k++;
        }
    }
}

void prepareText(char text[], char preparedText[]) {
    int i, len, k;

    len = strlen(text);
    k = 0;

    for (i = 0; i < len; i++) {
        text[i] = toupper(text[i]);
        if (text[i] == 'J') {
            text[i] = 'I';
        }
    }

    for (i = 0; i < len; i++) {
        preparedText[k++] = text[i];
        if (i + 1 < len && text[i] == text[i + 1]) {
            preparedText[k++] = 'X';
        }
    }
    if (k % 2 != 0) {
        preparedText[k++] = 'X';
    }
    preparedText[k] = '\0';
}

void encrypt(char plaintext[], char ciphertext[], char matrix[SIZE][SIZE]) {
    int i, len, row1, col1, row2, col2;

    len = strlen(plaintext);

    for (i = 0; i < len; i += 2) {
        findPosition(matrix, plaintext[i], &row1, &col1);
        findPosition(matrix, plaintext[i + 1], &row2, &col2);

        if (row1 == row2) {
            ciphertext[i] = matrix[row1][(col1 + 1) % SIZE];
            ciphertext[i + 1] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            ciphertext[i] = matrix[(row1 + 1) % SIZE][col1];
            ciphertext[i + 1] = matrix[(row2 + 1) % SIZE][col2];
        } else {
            ciphertext[i] = matrix[row1][col2];
            ciphertext[i + 1] = matrix[row2][col1];
        }
    }
    ciphertext[len] = '\0';
}

void decrypt(char ciphertext[], char decryptedText[], char matrix[SIZE][SIZE]) {
    int i, len, row1, col1, row2, col2;

    len = strlen(ciphertext);

    for (i = 0; i < len; i += 2) {
        findPosition(matrix, ciphertext[i], &row1, &col1);
        findPosition(matrix, ciphertext[i + 1], &row2, &col2);

        if (row1 == row2) {
            decryptedText[i] = matrix[row1][(col1 - 1 + SIZE) % SIZE];
            decryptedText[i + 1] = matrix[row2][(col2 - 1 + SIZE) % SIZE];
        } else if (col1 == col2) {
            decryptedText[i] = matrix[(row1 - 1 + SIZE) % SIZE][col1];
            decryptedText[i + 1] = matrix[(row2 - 1 + SIZE) % SIZE][col2];
        } else {
            decryptedText[i] = matrix[row1][col2];
            decryptedText[i + 1] = matrix[row2][col1];
        }
    }
    decryptedText[len] = '\0';
}

void findPosition(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    int i, j;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

