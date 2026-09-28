#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int global_var = 100;

int main() {

    printf("Before fork:\n");
    printf("Global Variable Address = %p\n", &global_var);
    printf("Global Variable Value   = %d\n\n", global_var);

    pid_t pid = fork();

    if(pid == 0) {

        printf("Child Process:\n");
        printf("Before Modification: %d\n", global_var);

        global_var = 200;

        printf("After Modification : %d\n", global_var);
        printf("Address            : %p\n\n", &global_var);

    } else {

        sleep(2);

        printf("Parent Process:\n");
        printf("Value              : %d\n", global_var);
        printf("Address            : %p\n", &global_var);
    }

    return 0;
}
