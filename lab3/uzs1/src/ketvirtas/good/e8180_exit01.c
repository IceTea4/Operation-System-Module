#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void func1() {
    printf("Priregistruota funkcija 1\n");
}

void func2() {
    printf("Priregistruota funkcija 2\n");
}

void func3() {
    printf("Priregistruota funkcija 3\n");
}

int main(int argc, char *argv[]) {
    atexit(func1);
    atexit(func2);
    atexit(func3);

    if (argc < 2) {
        printf("Truksta parametro! Naudokite: _Exit(), exit(), abort(), return.\n");
        return 1;
    }

    if (strcmp(argv[1], "_Exit") == 0) {
        printf("Naudojamas _Exit()...\n");
        _Exit(0);
    } else if (strcmp(argv[1], "exit") == 0) {
        printf("Naudojamas exit()...\n");
        exit(0);
    } else if (strcmp(argv[1], "abort") == 0) {
        printf("Naudojamas abort()...\n");
        abort();
    } else if (strcmp(argv[1], "return") == 0) {
        printf("Naudojamas return...\n");
        return 0;
    } else {
        printf("Nepatvirtintas parametras: %s\n", argv[1]);
        return 1;
    }

    return 0;
}
