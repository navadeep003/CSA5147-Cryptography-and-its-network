#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void caesar_cipher(char *text, int shift);

int main() {
    char text[100];
    int shift;

    printf("Enter the text to be encrypted: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter the shift value (1-25): ");
    scanf("%d", &shift);
    if (shift < 1 || shift > 25) {
        printf("Shift value must be between 1 and 25.\n");
        return 1;
    }

    caesar_cipher(text, shift);

    printf("Encrypted text: %s\n", text);

    return 0;
}

void caesar_cipher(char *text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - offset + shift) % 26 + offset;
        }
    }
}

