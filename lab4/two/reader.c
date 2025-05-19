#include <stdio.h>
#include <stdlib.h>

int main() {
    char buffer[1024];

    FILE *fp = fopen("mypipe", "r");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("Received: %s", buffer);
    }

    fclose(fp);

    return 0;
}
