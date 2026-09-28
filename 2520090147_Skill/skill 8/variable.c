#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *user = getenv("USER");
    char *home = getenv("HOME");
    char *path = getenv("PATH");

    printf("USER = %s\n", user ? user : "Undefined");
    printf("HOME = %s\n", home ? home : "Undefined");
    printf("PATH = %s\n", path ? path : "Undefined");

    char *test = getenv("ABC");

    if(test == NULL)
        printf("ABC = Undefined Variable\n");

    return 0;
}
