 #include <stdio.h>
 int main() {
    int frames, window, i, sent = 0;
    printf("Enter number of frames: ");
    scanf("%d",&frames);
    printf("Enter window size: ");
    scanf("%d",&window);
    while (sent < frames) {
        printf("\nSender sends frames: ");
        for (i = sent; i < sent + window && i < frames; i++)
            printf("%d ", i);
        printf("\nReceiver ACK for frame: %d", sent);
        sent++; // Simulating error-free, so only 1 ACK at a time
    }
    printf("\nAll Frames Sent Successfully\n");
    return 0;
 }
