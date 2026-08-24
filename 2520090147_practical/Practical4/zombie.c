#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();

    if(pid == 0)
    {
        printf("Child Process Exiting\n");
        exit(0);
    }
    else
    {
        printf("Parent Sleeping\n");
        sleep(30);
    }

    return 0;
}
