#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("mypipe", "w");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "Hello from writer!\n");
    fclose(fp);

    return 0;
}
