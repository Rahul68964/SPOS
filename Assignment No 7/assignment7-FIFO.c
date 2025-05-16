#include <stdio.h>

int main() {
    int frames, pages, page[50], temp[50], faults = 0;
    int i, j, k = 0, flag;

    printf("Enter number of pages: ");
    scanf("%d", &pages);

    printf("Enter the page reference string: ");
    for(i = 0; i < pages; i++)
        scanf("%d", &page[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    for(i = 0; i < frames; i++)
        temp[i] = -1;

    printf("\nPage\tFrames\n");
    for(i = 0; i < pages; i++) {
        flag = 0;
        for(j = 0; j < frames; j++) {
            if(temp[j] == page[i]) {
                flag = 1;
                break;
            }
        }

        if(flag == 0) {
            temp[k] = page[i];
            k = (k + 1) % frames;
            faults++;

            printf("%d\t", page[i]);
            for(j = 0; j < frames; j++) {
                if(temp[j] != -1)
                    printf("%d ", temp[j]);
                else
                    printf("- ");
            }
            printf("\n");
        }
    }

    printf("\nTotal Page Faults = %d\n", faults);
    return 0;
}
