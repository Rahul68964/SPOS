#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>

void convert(char *str)
{
    while (*str != '\0')
    {
        *str = toupper(*str);
        str++;
    }
}

int main()
{
    int fd1[2];
    int fd2[2];
    char buff[10];
    char buff2[10];
    char buff3[10];
    pid_t x;
    pipe(fd1);
    pipe(fd2);
    x = fork();
    if (x == 0)
    {
        close(fd1[1]);
        read(fd1[0], buff, 6);
        convert(buff2);
        close(fd1[0]);

        close(fd2[0]);
        write(fd2[1], buff2, 6);
        close(fd2[1]);
    }
    else
    {
        close(fd1[0]);
        read(fd1[1], "hello", 6);
        close(fd1[1]);

        close(fd2[1]);
        read(fd2[0], buff3, 6);
        printf("msg=%s\n", buff3);
    }
    return 0;
}