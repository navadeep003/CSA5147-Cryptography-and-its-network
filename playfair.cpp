#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Function to create the key table
void createKeyTable(char key[], char keyTable[SIZE][SIZE]) {
    int dicty[26] = {0};
    int i, j, k, len = strlen(key);
    char currentChar;

    // Fill key table with the key
    for (i = 0, k = 0; i < len; i++) {
        if (key[i] != 'j') {
            currentChar = tolower(key[i]);
        } else {
            currentChar = 'i';  // 'j' is considered as 'i'
        }
        
        if (dicty[currentChar - 'a'] == 0) {
            keyTable[k / SIZE][k % SIZE] = currentChar;
            dicty[currentChar - 'a'] = 1;
            k++;
        }
    }

    // Fill the rest of the key table with remaining letters
    for (i = 0; i < 26; i++) {
        if (dicty[i] == 0 && i != 9) { // 'j' is not included
            keyTable[k / SIZE][k % SIZE] = 'a' + i;
            k++;
        }
    }
}

// Function to preprocess the plaintext
void preprocessPlaintext(char plaintext[], char processed[]) {
    int i, j = 0;
    int len = strlen(plaintext);

    for (i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            processed[j++] = tolower(plaintext[i]);
        }
    }

    processed[j] = '\0';

    for (i = 0; i < j; i += 2) {
        if (processed[i] == processed[i + 1]) {
            memmove(processed + i + 2, processed + i + 1, j - i);
            processed[i + 1] = 'x';
            j++;
        }
    }

    if (j % 2 != 0) {
        processed[j++] = 'x';
    }

    processed[j] = '\0';
}

// Function to search for the position of a character in the key table
void search(char keyTable[SIZE][SIZE], char a, char b, int pos[]) {
    int i, j;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (keyTable[i][j] == a) {
                pos[0] = i;
                pos[1] = j;
            }
            if (keyTable[i][j] == b) {
                pos[2] = i;
                pos[3] = j;
            }
        }
    }
}

// Function to encrypt the plaintext
void encrypt(char plaintext[], char keyTable[SIZE][SIZE], char ciphertext[]) {
    int i, aPos[4];

    for (i = 0; plaintext[i] != '\0'; i += 2) {
        search(keyTable, plaintext[i], plaintext[i + 1], aPos);

        if (aPos[0] == aPos[2]) {
            ciphertext[i] = keyTable[aPos[0]][(aPos[1] + 1) % SIZE];
            ciphertext[i + 1] = keyTable[aPos[2]][(aPos[3] + 1) % SIZE];
        } else if (aPos[1] == aPos[3]) {
            ciphertext[i] = keyTable[(aPos[0] + 1) % SIZE][aPos[1]];
            ciphertext[i + 1] = keyTable[(aPos[2] + 1) % SIZE][aPos[3]];
        } else {
            ciphertext[i] = keyTable[aPos[0]][aPos[3]];
            ciphertext[i + 1] = keyTable[aPos[2]][aPos[1]];
        }
    }

    ciphertext[i] = '\0';
}

int main() {
    char key[100], plaintext[100], processed[100], keyTable[SIZE][SIZE], ciphertext[100];

    printf("Enter the keyword: ");
    gets(key);
    printf("Enter the plaintext: ");
    gets(plaintext);

    createKeyTable(key, keyTable);
    preprocessPlaintext(plaintext, processed);
    encrypt(processed, keyTable, ciphertext);

    printf("Encrypted text: %s\n", ciphertext);

    return 0;
}

