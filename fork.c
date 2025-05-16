#include <stdio.h>
#include <unistd.h>

int main()
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int pid = fork();

    if (pid == 0)
    {
        int product = 1;
        for (int i = 0; i < 10; i++)
        {
            product *= arr[i];
        }
        printf("Child Process: Product = %d\n", product);
    }
    else
    {
        int sum = 0;
        for (int i = 0; i < 10; i++)
        {
            sum += arr[i];
        }
        printf("Parent Process: Sum = %d\n", sum);
    }

    return 0;
}