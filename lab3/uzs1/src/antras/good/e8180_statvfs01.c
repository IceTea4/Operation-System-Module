/* Aistis Jakutonis IFF3/1 e8180 */
/* Failas: e8180_stat01.c */

#include <sys/statvfs.h>
#include <unistd.h>
#include <sys/vfs.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>

int print_file_info(const char *file_path);

int print_file_info(const char *file_path) {
    struct stat file_stat;

    // Gauti failo informaciją
    if (stat(file_path, &file_stat) == -1) {
        perror("stat klaida");
        exit(1);
    }

    printf("Failo: %s informacija:\n", file_path);

    // Savininko informacija
    struct passwd *owner = getpwuid(file_stat.st_uid);
    printf("Savininko ID: %d (%s)\n", file_stat.st_uid, owner ? owner->pw_name : "N/A");

    // Failo dydis
    printf("Failo dydis: %ld baitai\n", file_stat.st_size);

    // i-node numeris
    printf("i-node numeris: %lu\n", file_stat.st_ino);

    // Failo leidimai
    printf("Failo leidimai: ");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    // Failo tipas
    printf("Failo tipas: ");
    if (S_ISREG(file_stat.st_mode)) {
        printf("Failas\n");
    } else if (S_ISDIR(file_stat.st_mode)) {
        printf("Katalogas\n");
    } else if (S_ISLNK(file_stat.st_mode)) {
        printf("Simbolinis ryšys\n");
    } else if (S_ISCHR(file_stat.st_mode)) {
        printf("Charakterio įrenginys\n");
    } else if (S_ISBLK(file_stat.st_mode)) {
        printf("Bloko įrenginys\n");
    } else if (S_ISFIFO(file_stat.st_mode)) {
        printf("Pipelinė\n");
    } else if (S_ISSOCK(file_stat.st_mode)) {
        printf("Soketas\n");
    } else {
        printf("Nežinomas tipas\n");
    }

    printf("\n");

    return 0;
}

void print_filesystem_info(const char *file_path);

void print_filesystem_info(const char *file_path) {
    struct statvfs fs_stat;

    // Gauti failų sistemos informaciją
    if (statvfs(file_path, &fs_stat) == -1) {
        perror("statvfs klaida");
        exit(1);
    }

    // Išvesti failų sistemos informaciją
    printf("Failų sistemos informacija:\n");

    // Failų sistemos bloko dydis
    printf("Failų sistemos bloko dydis: %lu baitai\n", fs_stat.f_bsize);

    // Failų sistemos ID
    printf("Failų sistemos ID: %lu\n", fs_stat.f_fsid);

    // Failų sistemos dydis (bendras dydis)
    printf("Failų sistemos dydis: %lu baitai\n", fs_stat.f_blocks * fs_stat.f_bsize);

    // Maksimalus failo kelio/vardo ilgis
    printf("Maksimalus failo kelio/vardo ilgis: %lu\n", fs_stat.f_namemax);

    printf("\n");
}

int main(int argc, char *argv[]) {
    // Patikrinti, ar įvestas tik vienas parametras
    if (argc != 2) {
        fprintf(stderr, "Naudojimas: %s <failo kelias>\n", argv[0]);
        exit(255);
    }

    // Išvedame failo informaciją
    print_file_info(argv[1]);

    // Išvedame failų sistemos informaciją
    print_filesystem_info(argv[1]);

    return 0;
}
