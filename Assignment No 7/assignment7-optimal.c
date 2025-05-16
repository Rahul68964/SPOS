#include <stdio.h>
#include <stdlib.h>

int search(int page[], int n, int key) {
    for(int i = 0; i < n; i++) {
        if(page[i] == key)
            return i;
    }
    return -1;
}

int predict(int page[], int n, int fr[], int index, int frames) {
    int res = -1, farthest = index;

    for(int i = 0; i < frames; i++) {
        int j;
        for(j = index; j < n; j++) {
            if(fr[i] == page[j]) {
                if(j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if(j == n)
            return i;
    }

    return (res == -1) ? 0 : res;
}

int main() {
    int n, frames;
    printf("Enter number of pages: ");
    scanf("%d", &n);

    int* page = (int*) malloc(n * sizeof(int));
    if (page == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the page reference string: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &page[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    int* fr = (int*) malloc(frames * sizeof(int));
    if (fr == NULL) {
        printf("Memory allocation failed.\n");
        free(page);
        return 1;
    }

    for(int i = 0; i < frames; i++)
        fr[i] = -1;

    int count = 0, page_faults = 0;

    printf("\nPage\tFrames\n");
    for(int i = 0; i < n; i++) {
        if(search(fr, frames, page[i]) == -1) {
            page_faults++;
            if(count < frames)
                fr[count++] = page[i];
            else {
                int j = predict(page, n, fr, i + 1, frames);
                fr[j] = page[i];
            }
        }

        printf("%d\t", page[i]);
        for(int j = 0; j < frames; j++) {
            if(fr[j] != -1)
                printf("%d ", fr[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", page_faults);

    free(page);
    free(fr);
    return 0;
}
