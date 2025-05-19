/* Aistis Jakutonis IFF3/1 e8180 */
/* Failas: e8180_nftw02.c */

#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>
#include <string.h>
#include <stdint.h>

int print_file_name(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
	//const char *fileName = strrchr(fpath, '/');
        if (typeflag == FTW_F || typeflag == FTW_D) {
                printf("%s\n", fpath);
	}

        return 0;
}

int main ( int argc, char * argv[] ) {
        const char *home_dir = getenv("HOME");
        if (home_dir == NULL) {
                perror("Nepavyko gauti namu katalogo");
                return 1;
        }

        if (nftw(home_dir, print_file_name, 20, FTW_PHYS) == -1) {
                perror("nftw klaida");
                return 1;
        }

        return 0;
}
