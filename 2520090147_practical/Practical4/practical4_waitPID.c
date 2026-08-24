#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid1, pid2;

    pid1 = fork();

    if(pid1 == 0)
    {
        sleep(5);
        printf("Child 1 Finished\n");
        exit(0);
    }

    pid2 = fork();

    if(pid2 == 0)
    {
        sleep(2);
        printf("Child 2 Finished\n");
        exit(0);
    }

    waitpid(pid2, NULL, 0);
    printf("Parent collected Child 2\n");

    waitpid(pid1, NULL, 0);
    printf("Parent collected Child 1\n");

    return 0;
}
