#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid[3];

    for(int i = 0; i < 3; i++)
    {
        pid[i] = fork();

        if(pid[i] == 0)
        {
            printf("Child %d: PID = %d\n", i + 1, getpid());
            sleep(2 + i);
            printf("Child %d Finished\n", i + 1);
            exit(0);
        }
    }

    printf("Parent PID = %d\n", getpid());

    for(int i = 0; i < 3; i++)
    {
        wait(NULL);
        printf("One Child Collected using wait()\n");
    }

    return 0;
}
