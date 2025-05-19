#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork nepavyko");
        return 1;
    }

    if (pid == 0) {
        sleep(2);
        printf("Vaikas: PID = %d, naujas PPID = %d\n", getpid(), getppid());
    } else {
        printf("Tevas: PID = %d, baigia\n", getpid());
        exit(0);
    }

    return 0;
}
