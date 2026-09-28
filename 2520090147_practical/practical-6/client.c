/* client.c */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    char *fifo = "/tmp/myfifo";
    char msg[100];

    int fd = open(fifo, O_WRONLY);

    printf("Enter message: ");
    fgets(msg, sizeof(msg), stdin);

    write(fd, msg, strlen(msg));
    close(fd);

    return 0;
}
