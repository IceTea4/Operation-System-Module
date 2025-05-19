#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Naudojimas: %s <sveikas_skaicius>\n", argv[0]);
        return 1;
    }

    int value = atoi(argv[1]);

    printf("PID: %d, PPID: %d, Argumentas: %d\n", getpid(), getppid(), value);

    if (value > 0) {
	char new_value_str[12];
	snprintf(new_value_str, sizeof(new_value_str), "%d", value - 1);

        char *args[] = {argv[0], new_value_str, NULL};

        execv(argv[0], args);

        perror("execv nepavyko");
        return 1;
    }

    return 0;
}
