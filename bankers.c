#include <stdio.h>

#define P 10
#define R 10

int available[R], max[P][R], allocation[P][R], need[P][R], work[R], safeSeq[P], finish[P];
int numP, numR;

void inputDetails()
{
    printf("Enter number of processes: ");
    scanf("%d", &numP);
    printf("Enter number of resources: ");
    scanf("%d", &numR);

    printf("Enter Maximum Demand Matrix:\n");
    for (int i = 0; i < numP; i++)
        for (int j = 0; j < numR; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < numP; i++)
        for (int j = 0; j < numR; j++)
            scanf("%d", &allocation[i][j]);

    for (int i = 0; i < numP; i++)
        for (int j = 0; j < numR; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    printf("Enter Available Resources:\n");
    for (int i = 0; i < numR; i++)
        scanf("%d", &available[i]);
}

void calculateSafeSequence()
{
    for (int i = 0; i < numP; i++)
        finish[i] = 0;

    for (int i = 0; i < numR; i++)
        work[i] = available[i];
        

    int count = 0;
    while (count < numP)
    {
        int found = 0;
        for (int i = 0; i < numP; i++)
        {
            if (!finish[i])
            {
                int j;
                for (j = 0; j < numR; j++)
                {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == numR)
                {
                    for (int k = 0; k < numR; k++)
                        work[k] += allocation[i][k];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found)
        {
            printf("System is in an unsafe state!\n");
            return;
        }
    }

    printf("Safe Sequence: ");
    for (int i = 0; i < numP; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
}

void displayMatrices()
{
    printf("\nMaximum Matrix:\n");
    for (int i = 0; i < numP; i++)
    {
        for (int j = 0; j < numR; j++)
            printf("%d ", max[i][j]);
        printf("\n");
    }

    printf("\nAllocation Matrix:\n");
    for (int i = 0; i < numP; i++)
    {
        for (int j = 0; j < numR; j++)
            printf("%d ", allocation[i][j]);
        printf("\n");
    }

    printf("\nNeed Matrix:\n");
    for (int i = 0; i < numP; i++)
    {
        for (int j = 0; j < numR; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    printf("\nAvailable Resources: ");
    for (int i = 0; i < numR; i++)
        printf("%d ", available[i]);
    printf("\n");
}

int main()
{
    int choice;
    while (1)
    {
        printf("\n=== Banker's Algorithm Menu ===\n");
        printf("1. Input details\n");
        printf("2. Display matrices\n");
        printf("3. Find safe sequence\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            inputDetails();
            break;
        case 2:
            displayMatrices();
            break;
        case 3:
            calculateSafeSequence();
            break;
        case 4:
            return 0;
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
}