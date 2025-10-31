#include <stdio.h>

int main() {
    int bucket_size, output_rate, input_rate, n, stored = 0;

    printf("Enter bucket size (in packets): ");
    scanf("%d", &bucket_size);

    printf("Enter output rate (packets per second): ");
    scanf("%d", &output_rate);

    printf("Enter number of seconds to simulate: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        printf("\nSecond %d:\n", i);
        printf("Enter number of packets arriving: ");
        scanf("%d", &input_rate);

        stored += input_rate;  // Incoming packets added

        if (stored > bucket_size) {
            printf("Bucket overflow! %d packet(s) lost.\n", stored - bucket_size);
            stored = bucket_size;  // Bucket full
        }

        printf("Packets in bucket before leak: %d\n", stored);

        // Send packets (leak out)
        if (stored >= output_rate) {
            stored -= output_rate;
            printf("%d packet(s) sent out.\n", output_rate);
        } else {
            printf("%d packet(s) sent out.\n", stored);
            stored = 0;
        }

        printf("Packets remaining in bucket: %d\n", stored);
    }

    printf("\nSimulation ended.\n");

    return 0;
}
