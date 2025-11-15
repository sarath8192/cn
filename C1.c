#include <stdio.h>
#include <math.h>

int main() {
    int data[20], hamming[20], received[20];
    int m, r = 0, i, j, k, pos, parity, error_pos = 0;

    // Input data bits
    printf("Enter number of data bits: ");
    scanf("%d", &m);

    printf("Enter data bits (MSB first): ");
    for (i = 0; i < m; i++)
        scanf("%d", &data[i]);

    // Find number of parity bits needed
    while (pow(2, r) < (m + r + 1))
        r++;

    int total = m + r;   // total bits including parity

    j = 0; // For parity bit positions
    k = 0; // For data bit positions

    // Place data bits + 0 for parity positions
    for (i = 1; i <= total; i++) {
        if (i == pow(2, j)) {
            hamming[i] = 0; // parity bit placeholder
            j++;
        } else {
            hamming[i] = data[k];
            k++;
        }
    }

    // Calculate parity bits
    for (i = 0; i < r; i++) {
        int p = pow(2, i);
        parity = 0;

        for (j = p; j <= total; j += 2 * p) {
            for (k = j; k < j + p && k <= total; k++) {
                parity ^= hamming[k];
            }
        }
        hamming[p] = parity;
    }

    // Print generated Hamming Code
    printf("\nGenerated Hamming Code: ");
    for (i = 1; i <= total; i++)
        printf("%d ", hamming[i]);

    // Input error position
    printf("\n\nEnter position to introduce error (0 for none): ");
    scanf("%d", &pos);

    for (i = 1; i <= total; i++)
        received[i] = hamming[i];

    if (pos != 0)
        received[pos] ^= 1; // flip bit

    printf("Received bits: ");
    for (i = 1; i <= total; i++)
        printf("%d ", received[i]);

    // Detect error
    error_pos = 0;
    for (i = 0; i < r; i++) {
        int p = pow(2, i);
        parity = 0;

        for (j = p; j <= total; j += 2 * p) {
            for (k = j; k < j + p && k <= total; k++) {
                parity ^= received[k];
            }
        }

        if (parity != 0)
            error_pos += p;
    }

    if (error_pos == 0) {
        printf("\n\nNo error detected.\n");
    } else {
        printf("\n\nError detected at position: %d\n", error_pos);

        // Correct the error
        received[error_pos] ^= 1;

        printf("Corrected Code: ");
        for (i = 1; i <= total; i++)
            printf("%d ", received[i]);
        printf("\n");
    }

    return 0;
}
