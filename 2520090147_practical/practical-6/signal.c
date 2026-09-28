#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int sig) {
    printf("\nSIGINT received (Ctrl+C)\n");
}

void handle_sigterm(int sig) {
    printf("\nSIGTERM received\n");
}

void handle_sigusr1(int sig) {
    printf("\nSIGUSR1 received\n");
}

int main() {
    signal(SIGINT, handle_sigint);
    signal(SIGTERM, handle_sigterm);
    signal(SIGUSR1, handle_sigusr1);

    printf("Process ID: %d\n", getpid());
    printf("Waiting for signals...\n");

    while (1) {
        pause();
    }

    return 0;
}
