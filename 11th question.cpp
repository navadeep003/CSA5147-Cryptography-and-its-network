#include <stdio.h>
#include <math.h>

// Function to calculate factorial
unsigned long long factorial(int n) {
    if (n == 0) return 1;
    unsigned long long fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

// Function to calculate log base 2
double log2(double x) {
    return log(x) / log(2);
}

int main() {
    // Total possible keys
    unsigned long long totalKeys = factorial(25);
    printf("Total possible keys (25!): %llu\n", totalKeys);

    // Convert to approximate power of 2
    double log2Keys = log2(totalKeys);
    printf("Total possible keys as an approximate power of 2: 2^%.2f\n", log2Keys);

    // Calculate effective unique keys considering redundancies
    // There are 25 positions and each position can be filled by 25 letters
    // Considering each letter is unique and the key space is divided by the symmetrical factor
    double effectiveUniqueKeys = totalKeys / (2 * 25);
    double log2EffectiveKeys = log2(effectiveUniqueKeys);
    printf("Effectively unique keys as an approximate power of 2: 2^%.2f\n", log2EffectiveKeys);

    return 0;
}

