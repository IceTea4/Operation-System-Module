#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_FILE_SIZE (100 * 1024 * 1024)

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Naudojimas: %s <skaitomas failas> <rasomas failas>\n", argv[0]);
        return 1;
    }

    const char *src_filename = argv[1];
    const char *dst_filename = argv[2];

    int src_fd = open(src_filename, O_RDONLY);
    if (src_fd == -1) {
        perror("Nepavyko atidaryti skaitomo failo");
        return 1;
    }

    struct stat src_stat;
    if (fstat(src_fd, &src_stat) == -1) {
        perror("Nepavyko gauti failo informacijos");
        close(src_fd);
        return 1;
    }

    size_t file_size = src_stat.st_size;
    if (file_size > MAX_FILE_SIZE) {
        fprintf(stderr, "Failas per didelis! Maksimalus dydis 100 MB.\n");
        close(src_fd);
        return 1;
    }

    int dst_fd = open(dst_filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (dst_fd == -1) {
        perror("Nepavyko atidaryti rasomo failo");
        close(src_fd);
        return 1;
    }

    if (ftruncate(dst_fd, file_size) == -1) {
        perror("Nepavyko pakeisti rasomo failo dydzio");
        close(src_fd);
        close(dst_fd);
        return 1;
    }

    void *src_map = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, src_fd, 0);
    if (src_map == MAP_FAILED) {
        perror("Nepavyko prijungti skaitomo failo");
        close(src_fd);
        close(dst_fd);
        return 1;
    }

    void *dst_map = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, dst_fd, 0);
    if (dst_map == MAP_FAILED) {
        perror("Nepavyko prijungti rasomo failo");
        munmap(src_map, file_size);
        close(src_fd);
        close(dst_fd);
        return 1;
    }

    memcpy(dst_map, src_map, file_size);

    if (munmap(src_map, file_size) == -1) {
        perror("Nepavyko atjungti skaitomo failo");
    }
    if (munmap(dst_map, file_size) == -1) {
        perror("Nepavyko atjungti rasomo failo");
    }

    close(src_fd);
    close(dst_fd);

    printf("Failas sekmingai nukopijuotas.\n");
    return 0;
}
