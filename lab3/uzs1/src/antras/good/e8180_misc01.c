/* Aistis Jakutonis IFF3/1 e8180 */
/* Failas: e8180_misc01.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int test_link() {
    if (link("test_file.txt", "test_file_link.txt") == -1) {
        perror("link klaida");
        return 1;
    }

    printf("Nuoroda i faila sukurta\n");

    return 0;
}

int test_unlink() {
    if (unlink("test_file_link.txt") == -1) {
        perror("unlink klaida");
        return 1;
    }

    printf("Nuoroda pasalinta\n");

    return 0;
}

int test_symlink() {
    if (symlink("test_file.txt", "test_file_symlink.txt") == -1) {
        perror("symlink klaida");
        return 1;
    }

    printf("Simboline nuoroda sukurta\n");

    return 0;
}

int test_remove() {
    if (remove("test_file.txt") == -1) {
        perror("remove klaida");
        return 1;
    }

    printf("Failas pasalintas\n");

    return 0;
}

int test_rename() {
    if (rename("test_file_symlink.txt", "test_file_renamed.txt") == -1) {
        perror("rename klaida");
        return 1;
    }

    printf("Failas pervadintas\n");

    return 0;
}

int test_mkdir() {
    if (mkdir("test_dir", 0755) == -1) {
        perror("mkdir klaida");
        return 1;
    }

    printf("Katalogas sukurtas\n");

    return 0;
}

int test_rmdir() {
    if (rmdir("test_dir") == -1) {
        perror("rmdir klaida");
        return 1;
    }

    printf("Katalogas pasalintas\n");

    return 0;
}

int test_creat() {
    int fd = creat("test_creat_file.txt", 0644);

    if (fd == -1) {
        perror("creat klaida");
        return 1;
    }

    close(fd);

    printf("Failas sukurtas su creat()\n");

    return 0;
}

int test_umask() {
    mode_t old_umask = umask(0022);

    printf("Senasis umask: %o, naujas umask: %o\n", old_umask, umask(0));

    return 0;
}

int test_chmod() {
    if (chmod("test_creat_file.txt", 0644) == -1) {
        perror("chmod klaida");
        return 1;
    }

    printf("Failo leidimai pakeisti su chmod()\n");

    return 0;
}

int test_fchmod() {
    int fd = open("test_creat_file.txt", O_RDONLY);

    if (fd == -1) {
        perror("open klaida");
        return 1;
    }

    if (fchmod(fd, 0666) == -1) {
        perror("fchmod klaida");
        close(fd);
        return 1;
    }

    close(fd);

    printf("Failo leidimai pakeisti su fchmod()\n");

    return 0;
}

int test_futimens() {
    struct timespec times[2];

    times[0].tv_sec = 0;
    times[0].tv_nsec = 0;
    times[1].tv_sec = time(NULL);
    times[1].tv_nsec = 0;

    int fd = open("test_creat_file.txt", O_RDWR);

    if (fd == -1) {
        perror("open klaida");
        return 1;
    }

    if (futimens(fd, times) == -1) {
        perror("futimens klaida");
        close(fd);
        return 1;
    }

    close(fd);

    printf("Failo laiko pakeitimas su futimens()\n");

    return 0;
}

int main() {
    test_link();

    test_unlink();

    test_symlink();

    test_remove();

    test_rename();

    test_mkdir();

    test_rmdir();

    test_creat();

    test_umask();

    test_chmod();

    test_fchmod();

    test_futimens();

    return 0;
}
