#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	pid_t pid1, pid2;

	printf("Tevas start: PID = %d, PPID = %d\n", getpid(), getppid());

    	pid1 = fork();

	if (pid1 == 0) {
		printf("Pirmas vaikas: PID = %d, PPID = %d\n", getpid(), getppid());
		return 0;
	}

    	pid2 = fork();

	if (pid2 == 0) {
		printf("Antras vaikas: PID = %d, PPID = %d\n", getpid(), getppid());
		return 0;
	}

    return 0;
}
