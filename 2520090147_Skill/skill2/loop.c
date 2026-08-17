#include <stdio.h>
#include <string.h>

int main() {
    char cmd[100];

    while (1) {
        printf("Enter command: ");
        fgets(cmd, sizeof(cmd), stdin);

        if (strncmp(cmd, "exit", 4) == 0) {
            printf("Exiting...\n");
            break;
        }

        printf("You entered: %s", cmd);
    }

    return 0;
}
