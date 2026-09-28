#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *path;

    path = getenv("PATH");

    if(path == NULL)
    {
        printf("PATH variable not found\n");
        return 1;
    }

    printf("PATH Variable:\n%s\n", path);

    return 0;
}
