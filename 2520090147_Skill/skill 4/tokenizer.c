#include <stdio.h>
#include <string.h>

int main() {
    char input[100];

    printf("Enter command: ");
    fgets(input, sizeof(input), stdin);

    char *token = strtok(input, " \t\n");

    printf("Tokens:\n");

    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, " \t\n");
    }

    return 0;
}
