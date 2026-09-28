#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if(pid < 0)
    {
        printf("Fork Failed\n");
        return 1;
    }
    else if(pid == 0)
    {
        printf("Child Process Running\n");
        sleep(5);
        printf("Child Process Completed\n");
        exit(10);
    }
    else
    {
        int status;

        printf("Parent Waiting for Child...\n");

        waitpid(pid, &status, 0);

        if(WIFEXITED(status))
        {
            printf("Child Exit Status: %d\n", WEXITSTATUS(status));
        }

        printf("Parent Process Resumed\n");
    }

    return 0;
}
