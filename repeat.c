 #include <stdio.h>
 int main() {
    int frames, window, i;
    printf("Enter number of frames: ");
    scanf("%d",&frames);
    printf("Enter window size: ");
    scanf("%d",&window);
    for (i = 0; i < frames; i++) {
        printf("\nSender sends frame %d", i);
        printf("\nReceiver ACK frame %d", i);  // Assuming no loss
    }
    printf("\nAll Frames Sent & ACK Received\n");
    return 0;
 }
