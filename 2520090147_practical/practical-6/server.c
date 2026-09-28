/* server.c */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    char *fifo = "/tmp/myfifo";
    mkfifo(fifo, 0666);

    char msg[100];
    int fd = open(fifo, O_RDONLY);

    while (1) {
        int n = read(fd, msg, sizeof(msg));
        if (n > 0) {
            msg[n] = '\0';
            printf("Received: %s\n", msg);
        }
    }

    close(fd);
    unlink(fifo);
    return 0;
}
