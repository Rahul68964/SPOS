#include <stdio.h>

typedef struct {
    int pid, arrivalTime, burstTime, priority;
    int completionTime, turnaroundTime, waitingTime;
} Process;

void PriorityNonPreemptive(Process p[], int n) {
    int completed = 0, currentTime = 0;
    float totalWT = 0, totalTAT = 0;
    int isCompleted[n];
    for (int i = 0; i < n; i++) isCompleted[i] = 0;

    while (completed != n) {
        int idx = -1, highest = 9999;
        for (int i = 0; i < n; i++)
            if (p[i].arrivalTime <= currentTime && !isCompleted[i] && p[i].priority < highest) {
                highest = p[i].priority;
                idx = i;
            }

        if (idx != -1) {
            currentTime += p[idx].burstTime;
            p[idx].completionTime = currentTime;
            p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
            isCompleted[idx] = 1;
            totalWT += p[idx].waitingTime;
            totalTAT += p[idx].turnaroundTime;
            completed++;
        } else {
            currentTime++;
        }
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrivalTime, p[i].burstTime, p[i].priority, p[i].completionTime, p[i].turnaroundTime, p[i].waitingTime);

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
        printf("P%d Priority (Lower = Higher): ", i + 1);
        scanf("%d", &p[i].priority);
        p[i].pid = i + 1;
    }
    PriorityNonPreemptive(p, n);
    return 0;
}
