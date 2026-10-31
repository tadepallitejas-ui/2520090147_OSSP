/*
 * debug_runner.c
 * ------------------------------------------------------------
 * This is the "debugging system" driver referred to in the
 * abstract: it uses fork(), exec(), and wait()/waitpid() to
 * launch a target program under test, monitor its process
 * state, and report how it terminated (normally, or via a
 * signal such as SIGSEGV from a bug).
 *
 * Usage: ./debug_runner <path-to-target> [args...]
 *
 * OS concepts demonstrated (Section 5 of the abstract):
 *   fork()            - create a child process for testing
 *   exec()             - execute the program under analysis
 *   wait()/waitpid()   - monitor child termination and status
 * ------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

static void log_line(FILE *log, const char *fmt, ...) __attribute__((format(printf, 2, 3)));

static void log_line(FILE *log, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stdout, fmt, args);
    va_end(args);
    va_start(args, fmt);
    if (log) vfprintf(log, fmt, args);
    va_end(args);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <target-program> [args...]\n", argv[0]);
        return 1;
    }

    FILE *log = fopen("reports/process_monitor.log", "a");

    time_t now = time(NULL);
    log_line(log, "\n[debug_runner] ---- run started %s", ctime(&now));
    log_line(log, "[debug_runner] target: %s\n", argv[1]);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        if (log) fclose(log);
        return 1;
    }

    if (pid == 0) {
        /* Child: exec() the program under analysis */
        execv(argv[1], &argv[1]);
        /* execv only returns on failure */
        perror("execv failed");
        _exit(127);
    }

    /* Parent: monitor the child with waitpid() */
    log_line(log, "[debug_runner] spawned child pid=%d, waiting...\n", pid);

    int status;
    pid_t result = waitpid(pid, &status, 0);
    if (result < 0) {
        perror("waitpid failed");
        if (log) fclose(log);
        return 1;
    }

    if (WIFEXITED(status)) {
        log_line(log, "[debug_runner] child pid=%d exited normally, code=%d\n",
                  pid, WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        log_line(log, "[debug_runner] child pid=%d TERMINATED BY SIGNAL %d (%s)\n",
                  pid, WTERMSIG(status), strsignal(WTERMSIG(status)));
        log_line(log, "[debug_runner] -> this indicates a runtime error such as "
                       "invalid memory access; re-run under gdb/valgrind to locate it.\n");
    } else {
        log_line(log, "[debug_runner] child pid=%d ended with unknown status\n", pid);
    }

    if (log) fclose(log);
    return 0;
}
