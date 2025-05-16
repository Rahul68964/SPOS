#include <stdio.h>
#include <limits.h>

typedef struct {
    int pid, arrivalTime, burstTime, remainingTime;
    int completionTime, turnaroundTime, waitingTime;
} Process;

void SJF_Preemptive(Process p[], int n) {
    int completed = 0, currentTime = 0;
    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++)
        p[i].remainingTime = p[i].burstTime;

    while (completed != n) {
        int idx = -1, minRT = INT_MAX;
        for (int i = 0; i < n; i++)
            if (p[i].arrivalTime <= currentTime && p[i].remainingTime > 0 && p[i].remainingTime < minRT) {
                minRT = p[i].remainingTime;
                idx = i;
            }

        if (idx != -1) {
            p[idx].remainingTime--;
            currentTime++;
            if (p[idx].remainingTime == 0) {
                p[idx].completionTime = currentTime;
                p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
                p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
                totalWT += p[idx].waitingTime;
                totalTAT += p[idx].turnaroundTime;
                completed++;
            }
        } else {
            currentTime++;
        }
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
    SJF_Preemptive(p, n);
    return 0;
}
