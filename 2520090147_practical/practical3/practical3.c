#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid;

    printf("Parent Process Started\n");
    printf("PID = %d, PPID = %d\n", getpid(), getppid());

    pid = fork();

    if(pid < 0)
    {
        printf("Fork Failed\n");
        return 1;
    }
    else if(pid == 0)
    {
        printf("\nChild Process\n");
        printf("PID = %d\n", getpid());
        printf("PPID = %d\n", getppid());

        printf("Child Running...\n");
        sleep(10);

        printf("Child Terminating...\n");
        exit(0);
    }
    else
    {
        printf("\nParent Process\n");
        printf("PID = %d\n", getpid());
        printf("Child PID = %d\n", pid);

        printf("Parent Waiting for Child...\n");
        wait(NULL);

        printf("Child Completed\n");
        printf("Parent Terminating...\n");
    }

    return 0;
}
