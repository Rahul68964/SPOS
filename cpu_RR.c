#include <stdio.h>

typedef struct {
    int pid, arrivalTime, burstTime, remainingTime;
    int completionTime, turnaroundTime, waitingTime;
} Process;

void RoundRobin(Process p[], int n, int quantum) {
    int time = 0, completed = 0;
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++)
        p[i].remainingTime = p[i].burstTime;

    while (completed != n) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (p[i].remainingTime > 0 && p[i].arrivalTime <= time) {
                done = 0;
                if (p[i].remainingTime > quantum) {
                    time += quantum;
                    p[i].remainingTime -= quantum;
                } else {
                    time += p[i].remainingTime;
                    p[i].completionTime = time;
                    p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
                    p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;
                    totalWT += p[i].waitingTime;
                    totalTAT += p[i].turnaroundTime;
                    p[i].remainingTime = 0;
                    completed++;
                }
            }
        }
        if (done)
            time++;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrivalTime, p[i].burstTime, p[i].completionTime, p[i].turnaroundTime, p[i].waitingTime);

    printf("\nAvg WT = %.2f\nAvg TAT = %.2f\n", totalWT/n, totalTAT/n);
}

int main() {
    int n, quantum;
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
    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);
    RoundRobin(p, n, quantum);
    return 0;
}
