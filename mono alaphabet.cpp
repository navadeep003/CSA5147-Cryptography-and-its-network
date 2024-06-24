#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void monoalphabetic_substitution_cipher(char *text, char *key);

int main() {
    char text[100];
    char key[27];

    printf("Enter the text to be encrypted: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter the 26-letter key for substitution (unique letters): ");
    fgets(key, sizeof(key), stdin);

    // Remove newline character from the end of key if present
    key[strcspn(key, "\n")] = '\0';

    // Ensure the key is exactly 26 letters long
    if (strlen(key) != 26) {
        printf("The key must be exactly 26 characters long.\n");
        return 1;
    }

    // Ensure all letters in the key are unique and alphabetical
    int check[26] = {0};
    for (int i = 0; i < 26; i++) {
        if (!isalpha(key[i])) {
            printf("The key must contain only alphabetical characters.\n");
            return 1;
        }
        int index = tolower(key[i]) - 'a';
        if (check[index] == 1) {
            printf("The key must contain unique letters.\n");
            return 1;
        }
        check[index] = 1;
    }

    monoalphabetic_substitution_cipher(text, key);

    printf("Encrypted text: %s\n", text);

    return 0;
}

void monoalphabetic_substitution_cipher(char *text, char *key) {
    char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a';
            int index = tolower(text[i]) - 'a';
            text[i] = isupper(text[i]) ? toupper(key[index]) : key[index];
        }
    }
}

