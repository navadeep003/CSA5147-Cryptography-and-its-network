#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define CIPHERTEXT "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;"

void frequencyAnalysis(const char *ciphertext) {
    int freq[256] = {0};
    int length = strlen(ciphertext);
    
    // Count frequency of each character
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] != ' ') {
            freq[(unsigned char)ciphertext[i]]++;
        }
    }
    
    // Print frequency analysis
    printf("Frequency Analysis:\n");
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            printf("'%c' : %d\n", i, freq[i]);
        }
    }
}

void applySubstitution(const char *ciphertext, const char *substitution) {
    int length = strlen(ciphertext);
    char decrypted[length + 1];
    
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] != ' ') {
            decrypted[i] = substitution[(unsigned char)ciphertext[i]];
        } else {
            decrypted[i] = ' ';
        }
    }
    decrypted[length] = '\0';
    
    printf("Decrypted Text:\n%s\n", decrypted);
}

int main() {
    // Perform frequency analysis
    frequencyAnalysis(CIPHERTEXT);
    
    // Substitution table, initially identity mapping
    char substitution[256];
    for (int i = 0; i < 256; i++) {
        substitution[i] = i;
    }
    
    // Initial guesses based on frequency and common English patterns
    substitution['‡'] = 'E';
    substitution['†'] = 'T';
    substitution['5'] = 'H';
    substitution['3'] = 'R';
    substitution['0'] = 'O';
    substitution['6'] = 'S';
    substitution['*'] = 'N';
    substitution[';'] = 'D';
    substitution['4'] = 'I';
    substitution['8'] = 'A';
    substitution[')'] = 'L';
    substitution['¶'] = 'U';
    substitution[']'] = 'Y';
    substitution[':'] = 'P';
    substitution['?'] = 'W';
    substitution['('] = 'F';
    substitution['1'] = 'B';
    substitution['2'] = 'M';
    substitution['9'] = 'C';
    substitution['—'] = 'K';
    
    // Apply initial substitution and print result
    applySubstitution(CIPHERTEXT, substitution);
    
    // Manually refine the substitution based on output and context

    // Example refinement, adjust based on the partially decrypted text
    substitution['8'] = 'A'; // Repeated adjustments like these may be necessary
    
    // Apply refined substitution and print result
    applySubstitution(CIPHERTEXT, substitution);
    
    return 0;
}

