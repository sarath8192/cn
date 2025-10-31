#include <stdio.h>
#include <stdlib.h>

#define MIN(x, y) ((x > y) ? y : x)

int main() {
    int orate, drop = 0, cap, x, count = 0;
    int inp[10] = {0};
    int i = 0, nsec, ch;

    printf("\nEnter bucket size (in packets): ");
    scanf("%d", &cap);

    printf("Enter output rate (packets/sec): ");
    scanf("%d", &orate);

    // Input the packets for each second
    do {
        printf("\nEnter number of packets coming at second %d: ", i + 1);
        scanf("%d", &inp[i]);
        i++;
        printf("Enter 1 to continue or 0 to quit: ");
        scanf("%d", &ch);
    } while (ch);

    nsec = i;

    printf("\nSecond\tReceived\tSent\tDropped\tRemaining\n");

    for (i = 0; count || i < nsec; i++) {
        printf("%d\t", i + 1);
        printf("%d\t\t", inp[i]);

        // Calculate how many packets can be sent
        printf("%d\t", MIN((inp[i] + count), orate));

        x = inp[i] + count - orate;

        // Handle overflow and dropped packets
        if (x > 0) {
            if (x > cap) {
                count = cap;
                drop = x - cap;
            } else {
                count = x;
                drop = 0;
            }
        } else {
            drop = 0;
            count = 0;
        }

        printf("%d\t%d\n", drop, count);
    }

    return 0;
}
