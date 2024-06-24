#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_LEN 100
void preprocessText(char input[], char output[]) {
    int i, j = 0;
    for (i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            output[j++] = toupper(input[i]);
        }
    }
    output[j] = '\0';
}
void generateKey(char text[], char key[], char newKey[]) {
    int i, j = 0;
    int textLen = strlen(text);
    int keyLen = strlen(key);
    for (i = 0; i < textLen; i++) {
        newKey[i] = toupper(key[j]);
        j = (j + 1) % keyLen;
    }
    newKey[textLen] = '\0';
}
void encrypt(char text[], char key[], char ciphertext[]) {
    int i;
    int textLen = strlen(text);
    for (i = 0; i < textLen; i++) {
        ciphertext[i] = ((text[i] + key[i]) % 26) + 'A';
    }
    ciphertext[textLen] = '\0';
}
void decrypt(char ciphertext[], char key[], char decryptedText[]) {
    int i;
    int textLen = strlen(ciphertext);
    for (i = 0; i < textLen; i++) {
        decryptedText[i] = (((ciphertext[i] - key[i]) + 26) % 26) + 'A';
    } 
    decryptedText[textLen] = '\0';
}
int main() {
    char key[MAX_LEN], plaintext[MAX_LEN], processedText[MAX_LEN];
    char newKey[MAX_LEN], ciphertext[MAX_LEN], decryptedText[MAX_LEN];
    printf("Enter the keyword: ");
    gets(key);
    printf("Enter the plaintext: ");
    gets(plaintext);
    preprocessText(plaintext, processedText);
    generateKey(processedText, key, newKey);
    encrypt(processedText, newKey, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);
    decrypt(ciphertext, newKey, decryptedText);
    printf("Decrypted text: %s\n", decryptedText);
    return 0;
}
