/* Aistis */
/* FileName: two.c */

#define _XOPEN_SOURCE 500

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ftw.h>
#include <dirent.h>

void isEmpty(const char *dir);
int printFileType(const char *fpath, const struct stat *sb);
int processFile(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf);
int isScript(const char *filepath);

void isEmpty(const char *dir) {
	DIR *d = opendir(dir);
	if (d == NULL) {
		abort();
	}

	struct dirent *entry = readdir(d);
	if (entry == NULL && strcmp(entry->d_name, ".") == 0 && strcmp(entry->d_name, "..") == 0) {
		exit(125);
	}

	entry = readdir(d);
	closedir(d);

	if (entry == NULL) {
		exit(125);
	}
}

int printFileType(const char *fpath, const struct stat *sb) {
	if (S_ISDIR(sb->st_mode)) {
        	printf("%s - katalogas\n", fpath);
    	} else if (S_ISREG(sb->st_mode)) {
        	printf("%s - paprastas failas\n", fpath);
    	} else if (S_ISLNK(sb->st_mode)) {
        	printf("%s - simboline nuoroda\n", fpath);
    	} else if (S_ISBLK(sb->st_mode)) {
        	printf("%s - blokinis irenginio failas\n", fpath);
   	} else if (S_ISCHR(sb->st_mode)) {
        	printf("%s - simbolinis irenginio failas\n", fpath);
    	} else {
        	printf("%s - nezinomas tipas\n", fpath);
    	}
}

int isScript(const char *filepath) {
	char buffer[4];

	int fd = open(filepath, O_RDONLY);
	if (fd == -1) {
		abort();
	}

	if (read(fd, buffer, 3) != 3) {
		abort();
	}

	if (strcmp(buffer, "#!/") == 0) {
		close(fd);
		return 1;
	}

	close(fd);
	return 0;
}

int processFile(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    	if (strcmp(fpath, ".") != 0 && strcmp(fpath, "..") != 0) {
        	printFileType(fpath, sb);
    	}

	if (S_ISREG(sb->st_mode)) {
		if (isScript(fpath)) {
			printf("Skriptas\n");

			mode_t mode = sb->st_mode;

			if ((mode & S_IWGRP) || (mode & S_IWOTH)) {
				printf("Failas: %s, inode: %ld\n", fpath, sb->st_ino);
			}

		} else {
			printf("Ne skriptas\n");
		}
	}

    return 0;
}

int main(int argc, char *argv[]){
        printf( "(C) 2025 Aistis Jakutonis, %s\n", __FILE__ );

        if (argc != 2) {
                printf("Naudojimas:\n");
		printf("%s failas\n", argv[0]);
                exit(100);
        }

	printf("Priimtas argumentas: %s\n", argv[1]);

	isEmpty(argv[1]);

	if (nftw(argv[1], processFile, 20, FTW_PHYS) == -1) {
		abort();
	}

        return 0;
}
