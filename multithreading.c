#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 4

typedef struct
{
    int row;
    int col;
    int **matrix_a;
    int **matrix_b;
    int **result;
    int size;
} ThreadData;

void *multiply(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    int sum = 0;

    for (int k = 0; k < data->size; k++)
    {
        sum += data->matrix_a[data->row][k] * data->matrix_b[k][data->col];
    }

    // Store the result in the thread data structure
    data->result[data->row][data->col] = sum;

    // Prepare the return value (sum)
    int *return_value = malloc(sizeof(int));
    *return_value = sum;

    pthread_exit(return_value);
}

int main()
{
    int size;
    printf("Enter the size of the square matrices: ");
    scanf("%d", &size);

    // Allocate memory for matrices
    int **matrix_a = (int **)malloc(size * sizeof(int *));
    int **matrix_b = (int **)malloc(size * sizeof(int *));
    int **result = (int **)malloc(size * sizeof(int *));

    for (int i = 0; i < size; i++)
    {
        matrix_a[i] = (int *)malloc(size * sizeof(int));
        matrix_b[i] = (int *)malloc(size * sizeof(int));
        result[i] = (int *)malloc(size * sizeof(int));
    }

    // Initialize matrices with sample values
    printf("Matrix A:\n");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrix_a[i][j] = i + j;
            printf("%d ", matrix_a[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B:\n");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrix_b[i][j] = i - j;
            printf("%d ", matrix_b[i][j]);
        }
        printf("\n");
    }

    pthread_t threads[MAX_THREADS];
    ThreadData thread_data[MAX_THREADS];
    int thread_count = 0;
    int total_sum = 0;

    // Create threads to compute matrix multiplication
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            // Set up thread data
            thread_data[thread_count].row = i;
            thread_data[thread_count].col = j;
            thread_data[thread_count].matrix_a = matrix_a;
            thread_data[thread_count].matrix_b = matrix_b;
            thread_data[thread_count].result = result;
            thread_data[thread_count].size = size;

            // Create thread
            if (pthread_create(&threads[thread_count], NULL, multiply, &thread_data[thread_count]))
            {
                fprintf(stderr, "Error creating thread\n");
                return 1;
            }

            thread_count++;

            // If we've reached max threads, wait for them to finish
            if (thread_count == MAX_THREADS)
            {
                for (int k = 0; k < MAX_THREADS; k++)
                {
                    int *thread_sum;
                    pthread_join(threads[k], (void **)&thread_sum);
                    total_sum += *thread_sum;
                    free(thread_sum);
                }
                thread_count = 0;
            }
        }
    }

    // Wait for remaining threads to finish
    for (int k = 0; k < thread_count; k++)
    {
        int *thread_sum;
        pthread_join(threads[k], (void **)&thread_sum);
        total_sum += *thread_sum;
        free(thread_sum);
    }

    // Print the result matrix
    printf("\nResult Matrix:\n");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    // Print the total sum of all elements
    printf("\nTotal sum of all elements: %d\n", total_sum);

    // Free allocated memory
    for (int i = 0; i < size; i++)
    {
        free(matrix_a[i]);
        free(matrix_b[i]);
        free(result[i]);
    }
    free(matrix_a);
    free(matrix_b);
    free(result);

    return 0;
}