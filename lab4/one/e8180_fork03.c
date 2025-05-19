#include <sys/wait.h>
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
        printf("Vaikas (%d) baigesi\n", getpid());
        exit(0);
    } else {
        printf("Tevas (%d): vaikas paleistas, nelaukiu su wait()\n", getpid());
        sleep(3);

        system("ps -o pid,ppid,state,cmd");
        printf("========================================\n");

        wait(NULL);
        printf("Tevas (%d): wait() iskviestas, zombis pasalintas\n", getpid());
    }

    return 0;
}
