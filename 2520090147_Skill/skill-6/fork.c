#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();

    if(pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }
    else if(pid == 0)
    {
        printf("Child Process\n");
        printf("Child PID: %d\n", getpid());

        execl("/bin/ls", "ls", "-l", NULL);

        printf("Execution Failed\n");
    }
    else
    {
        printf("Parent Process\n");
        printf("Parent PID: %d\n", getpid());

        wait(NULL);

        printf("Child Process Completed\n");
    }

    return 0;
}
