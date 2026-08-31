#include <stdio.h>
#include <string.h>

int main() {
    char command[20];

    printf("Enter command: ");
    scanf("%s", command);

    if(strcmp(command, "ls") == 0)
        printf("Valid command: List files\n");
    else if(strcmp(command, "pwd") == 0)
        printf("Valid command: Print working directory\n");
    else if(strcmp(command, "date") == 0)
        printf("Valid command: Show date\n");
    else
        printf("Syntax Error: Invalid command\n");

    return 0;
}
