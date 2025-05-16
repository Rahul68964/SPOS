#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main()
{
    int fd[2];
    char str[] = "Hello";
    char str2[10];
    pid_t x;
    pipe(fd);
    pipe(fd);
    x = fork();
    if (x == 0)
    {
        close(fd[0]);
        write(fd[1], str, strlen(str) + 1);
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        read(fd[0], str2, strlen(str) + 1);
        close(fd[0]);
        printf("msg=%s\n", str2);
    }
    return 0;
}