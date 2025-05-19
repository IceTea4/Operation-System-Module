#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int signum) {
    printf("Caught signal %d\n", signum);
    abort(); // Specialiai sukuriame core dump
}

int main() {
    struct rlimit rl;
    int counter = 0;

    rl.rlim_cur = 0;  // Soft limit
    rl.rlim_max = 0;  // Hard limit
    if (setrlimit(RLIMIT_CORE, &rl) != 0) {
        perror("setrlimit failed for RLIMIT_CORE");
        exit(EXIT_FAILURE);
    }

    rl.rlim_cur = 1;  // Soft limit
    rl.rlim_max = 1;  // Hard limit
    if (setrlimit(RLIMIT_CPU, &rl) != 0) {
        perror("setrlimit failed");
        exit(EXIT_FAILURE);
    }

    signal(SIGXCPU, signal_handler);

    while (1) {
        counter++;
    }

    return 0;
}
