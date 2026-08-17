#include <stdio.h>

int main() {
    char input[100];

    printf("Type something: ");
    fgets(input, sizeof(input), stdin);

    printf("You typed: %s", input);

    return 0;
}
