#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global_var = 100;

int main()
{
    static int static_var = 200;
    int stack_var = 300;
    int *heap_var = malloc(sizeof(int));

    printf("Code Segment (main) : %p\n", main);
    printf("Global Variable     : %p\n", &global_var);
    printf("Static Variable     : %p\n", &static_var);
    printf("Heap Variable       : %p\n", heap_var);
    printf("Stack Variable      : %p\n", &stack_var);

    printf("PID: %d\n", getpid());

    sleep(60);

    free(heap_var);
    return 0;
}
