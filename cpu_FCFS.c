#include <stdio.h>

typedef struct {
    int pid, arrivalTime, burstTime;
    int completionTime, turnaroundTime, waitingTime;
} Process;

void FCFS(Process p[], int n) {
    int currentTime = 0;
    float totalWT = 0, totalTAT = 0;

    // Sort by arrival time
    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (p[i].arrivalTime > p[j].arrivalTime) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }

    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].arrivalTime)
            currentTime = p[i].arrivalTime;
        p[i].completionTime = currentTime + p[i].burstTime;
        p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;
        currentTime = p[i].completionTime;
        totalWT += p[i].waitingTime;
        totalTAT += p[i].turnaroundTime;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrivalTime, p[i].burstTime, p[i].completionTime, p[i].turnaroundTime, p[i].waitingTime);

    printf("\nAvg WT = %.2f\nAvg TAT = %.2f\n", totalWT/n, totalTAT/n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process p[n];
    for (int i = 0; i < n; i++) {
        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &p[i].arrivalTime);
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &p[i].burstTime);
        p[i].pid = i + 1;
    }
    FCFS(p, n);
    return 0;
}
