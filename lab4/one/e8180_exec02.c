#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    const char *filename = "scriptas.sh";

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Nepavyko sukurti skripto");
        return 1;
    }

    fprintf(fp,
        "#!/bin/sh\n"
        "echo \"Skriptas paleistas!\"\n"
        "echo \"Vykdomas naudotojas: $(whoami)\"\n"
        "echo \"Data: $(date)\"\n"
    );
    fclose(fp);

    if (chmod(filename, 0755) == -1) {
        perror("Nepavyko nustatyti vykdymo teisiu");
        return 1;
    }

    execlp("./scriptas.sh", "scriptas.sh", NULL);

    perror("Nepavyko paleisti skripto su execlp");
    return 1;
}
