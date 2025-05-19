#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <dirent.h>
#include <ftw.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <ftw.h>

int countDirectories(const char *p, const struct stat *st, int fl, struct FTW *fb);
int cnt = 0;
int reg = 0;

int countDirectories(const char *p, const struct stat *st, int fl, struct FTW *fb) {
    if (S_ISDIR(st->st_mode)) {
	//printf("Inode: %ld\n", st->st_ino);
        cnt++;
    }

    if (S_ISREG(st->st_mode)) {
	reg++;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Naudojimas:\n %s katalogas", argv[0]);
        exit(24);
    }

    struct stat st;
    if (stat(argv[1], &st) == -1) {
        perror("stat");
        abort();
    }

    if ((st.st_mode & S_IFMT) != S_IFDIR) {
        printf("Argumentas turi buti katalogas\n");
        abort();
    }

    DIR *dir = opendir(argv[1]);
    if (dir == NULL) {
        perror("opendir");
        abort();
    }

    int count = 0;
    struct dirent *d;
    while ((d = readdir(dir)) != NULL) {
        count++;
    }

    closedir(dir);
    if (count == 2) {
        printf("Katalogas tuscias\n");
        exit(25);
    } else {
        printf("Katalogas ne tuscias\n");

        int rv = nftw(argv[1], countDirectories, 20, FTW_PHYS);  
        if (rv == -1) {
            perror("nftw failed");
            abort();
        }

        printf("Pakatalogiu sk: %d\n", cnt);

	if (reg > 0) {
		printf("Yra paprastu failu\n");
	}

	return 0;
    }
}
