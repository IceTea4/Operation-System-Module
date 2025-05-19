#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	printf("Process start: PID = %d, PPID = %d\n", getpid(), getppid());

    	pid_t i = fork();

	if (i == 0) {
		printf("Vaikas: PID = %d, PPID = %d\n", getpid(), getppid());
	    	pid_t j = fork();

		if (j == 0) {
			printf("Anūkas: PID = %d, PPID = %d\n", getpid(), getppid());
		}
	}

    	return 0;
}
