#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
#define MAX_CIPHER_LENGTH 1000
float english_frequencies[ALPHABET_SIZE] = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,  
    0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,  
    0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,  
    0.00978, 0.02360, 0.00150, 0.01974, 0.00074                     
};
typedef struct {
    char plaintext[MAX_CIPHER_LENGTH];
    float score;
} FrequencyResult;
float calculate_frequency_score(char *plaintext) {
    int letter_counts[ALPHABET_SIZE] = {0};
    int total_letters = 0;   
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            int index = tolower(plaintext[i]) - 'a';
            letter_counts[index]++;
            total_letters++;
        }
    }   
    float score = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        float expected_frequency = english_frequencies[i] * total_letters;
        float observed_frequency = (float)letter_counts[i];
        float difference = observed_frequency - expected_frequency;
        score += (difference * difference) / expected_frequency;
    }
    return score;
}
void decrypt_with_shift(char *ciphertext, int shift, char *plaintext) {
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = ((ciphertext[i] - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[length] = '\0';
}
void frequency_analysis_attack(char *ciphertext, int num_results) {
    FrequencyResult results[num_results];
   for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        char plaintext[MAX_CIPHER_LENGTH];
        decrypt_with_shift(ciphertext, shift, plaintext);
        float score = calculate_frequency_score(plaintext);
       int i = num_results - 1;
        while (i >= 0 && score > results[i].score) {
            if (i + 1 < num_results) {
                strcpy(results[i + 1].plaintext, results[i].plaintext);
                results[i + 1].score = results[i].score;
            }
            i--;
        }
        if (i + 1 < num_results) {
            strcpy(results[i + 1].plaintext, plaintext);
            results[i + 1].score = score;
        }
    }  
    printf("Top %d possible plaintexts in rough order of likelihood:\n", num_results);
    for (int i = 0; i < num_results; i++) {
        printf("%d. Score: %.2f\n   Plaintext: %s\n\n", i + 1, results[i].score, results[i].plaintext);
    }
}
int main() {
    char ciphertext[MAX_CIPHER_LENGTH];
    int num_results;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 

    printf("Enter the number of top possible plaintexts to show: ");
    scanf("%d", &num_results);
    frequency_analysis_attack(ciphertext, num_results);

    return 0;
}
