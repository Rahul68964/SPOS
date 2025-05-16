#include <stdio.h>

int main() {
    int frames, pages, page[50], temp[50], time[50], faults = 0;
    int i, j, pos, counter = 0, flag1, flag2, min;

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
        flag1 = flag2 = 0;

        for(j = 0; j < frames; j++) {
            if(temp[j] == page[i]) {
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }

        if(flag1 == 0) {
            for(j = 0; j < frames; j++) {
                if(temp[j] == -1) {
                    counter++;
                    faults++;
                    temp[j] = page[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }

        if(flag2 == 0) {
            pos = 0;
            min = time[0];
            for(j = 1; j < frames; j++) {
                if(time[j] < min) {
                    min = time[j];
                    pos = j;
                }
            }

            counter++;
            faults++;
            temp[pos] = page[i];
            time[pos] = counter;
        }

        printf("%d\t", page[i]);
        for(j = 0; j < frames; j++) {
            if(temp[j] != -1)
                printf("%d ", temp[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);
    return 0;
}
