#include <stdio.h>
#include <math.h>

int main() {
    int data[10], code[10];
    int m, r = 0, i, j, k = 0, parity;

    // Step 1: Read the number of data bits
    printf("Enter number of data bits: ");
    scanf("%d", &m);

    // Step 2: Read data bits
    printf("Enter the data bits one by one: ");
    for (i = m - 1; i >= 0; i--)
        scanf("%d", &data[i]);

    // Step 3: Calculate number of parity bits required
    while (pow(2, r) < (m + r + 1))
        r++;

    printf("\nNumber of parity bits: %d", r);
    printf("\nTotal bits (code word length): %d\n", m + r);

    // Step 4: Place parity bits at positions 1,2,4,8,... (powers of 2)
    j = 0;
    for (i = 1; i <= m + r; i++) {
        if (i == pow(2, j)) {
            code[i] = 0;   // temporary 0 for parity bit
            j++;
        } else {
            code[i] = data[k++]; // fill data bits
        }
    }

    // Step 5: Calculate parity bits (even parity)
    for (i = 0; i < r; i++) {
        int p = pow(2, i);
        parity = 0;
        for (j = p; j <= m + r; j++) {
            if (((j >> i) & 1) == 1)   // check bit position
                parity = parity ^ code[j]; // XOR for even parity
        }
        code[p] = parity;  // store parity bit
    }

    // Step 6: Display final Hamming code
    printf("\nGenerated Hamming Code (Code Word): ");
    for (i = m + r; i > 0; i--)
        printf("%d", code[i]);

    printf("\n");
    return 0;
}
