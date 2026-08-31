#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    char data[] = "Hello from Producer";
    char buffer[100];

    pipe(fd);

    if (fork() == 0) {
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));
        printf("Consumer received: %s\n", buffer);
        close(fd[0]);
    } else {
        close(fd[0]);
        write(fd[1], data, strlen(data) + 1);
        printf("Producer sent: %s\n", data);
        close(fd[1]);
        wait(NULL);
    }

    return 0;
}
