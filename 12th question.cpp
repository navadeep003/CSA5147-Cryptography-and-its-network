#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 2

void prepareText(char text[], char preparedText[]);
void convertToNumbers(char text[], int numbers[]);
void matrixMultiplication(int key[SIZE][SIZE], int textNumbers[], int result[]);
void convertToLetters(int numbers[], char text[], int length);
void printMatrix(int matrix[SIZE][SIZE]);

int main() {
    char plaintext[] = "meet me at the usual place at ten rather than eight oclock";  // Example plaintext message
    char preparedText[100];
    int textNumbers[100];
    int encryptedNumbers[100];
    char ciphertext[100];
    
    int key[SIZE][SIZE] = {
        {9, 4},
        {5, 7}
    };

    // Prepare the plaintext
    prepareText(plaintext, preparedText);
    int len = strlen(preparedText);
    
    // Convert prepared text to numerical values
    convertToNumbers(preparedText, textNumbers);

    // Encrypt the prepared text numbers
    for (int i = 0; i < len; i += SIZE) {
        matrixMultiplication(key, &textNumbers[i], &encryptedNumbers[i]);
    }

    // Convert encrypted numbers back to letters
    convertToLetters(encryptedNumbers, ciphertext, len);
    
    printf("Encrypted Text: %s\n", ciphertext);

    return 0;
}

void prepareText(char text[], char preparedText[]) {
    int i, j = 0;
    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            preparedText[j++] = tolower(text[i]);
        }
    }
    if (j % 2 != 0) {
        preparedText[j++] = 'x';  // Padding if the length is odd
    }
    preparedText[j] = '\0';
}

void convertToNumbers(char text[], int numbers[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        numbers[i] = text[i] - 'a';
    }
}

void matrixMultiplication(int key[SIZE][SIZE], int textNumbers[], int result[]) {
    for (int i = 0; i < SIZE; i++) {
        result[i] = 0;
        for (int j = 0; j < SIZE; j++) {
            result[i] += key[i][j] * textNumbers[j];
        }
        result[i] %= 26;
    }
}

void convertToLetters(int numbers[], char text[], int length) {
    for (int i = 0; i < length; i++) {
        text[i] = numbers[i] + 'a';
    }
    text[length] = '\0';
}

void printMatrix(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

