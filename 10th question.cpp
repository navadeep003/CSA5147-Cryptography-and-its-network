#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void prepareText(char text[], char preparedText[]);
void encrypt(char plaintext[], char ciphertext[], char matrix[SIZE][SIZE]);
void findPosition(char matrix[SIZE][SIZE], char ch, int *row, int *col);
void removeSpaces(char text[]);

int main() {
    char plaintext[] = "Must see you over Cadogan West. Coming at once.";  // Example plaintext message
    char preparedText[100];
    char ciphertext[100];
    
    char matrix[SIZE][SIZE] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };

    // Remove spaces and punctuation from the plaintext
    removeSpaces(plaintext);

    // Prepare the plaintext
    prepareText(plaintext, preparedText);

    // Encrypt the prepared plaintext
    encrypt(preparedText, ciphertext, matrix);
    printf("Encrypted Text: %s\n", ciphertext);

    return 0;
}

void removeSpaces(char text[]) {
    int i, j;
    char temp[100];

    j = 0;
    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            temp[j++] = toupper(text[i]);
        }
    }
    temp[j] = '\0';
    strcpy(text, temp);
}

void prepareText(char text[], char preparedText[]) {
    int i, len, k;

    len = strlen(text);
    k = 0;

    for (i = 0; i < len; i++) {
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

