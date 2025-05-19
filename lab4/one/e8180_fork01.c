#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("Process start: PID = %d, PPID = %d\n", getpid(), getppid());

    fork();
    fork();

    printf("Hello from PID = %d, PPID = %d\n", getpid(), getppid());

    return 0;
}
