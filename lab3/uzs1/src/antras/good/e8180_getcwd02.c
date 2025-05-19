/* Aistis Jakutonis IFF3/1 e8180 */
/* Failas: e8180_loginas_getcwd02.c */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

int task_getcwd();
int open_dir();
int task_chdir();
int task_fchdir();

//current work directory
int task_getcwd() {
	char *cwd;

	cwd = getcwd(NULL, pathconf(".", _PC_PATH_MAX));
	if (cwd == NULL) {
		perror("getcwd klaida");
		exit(1);
	}

	printf("Esamas darbo katalogas: %s\n", cwd);
	free(cwd);
	return 0;
}

//open directory ir grazina deskriptoriu
int open_dir() {
	int dskr = open(".", O_RDONLY);

	if (dskr == -1) {
		perror(".");
		exit(1);
	}

	printf("dskr = %d\n", dskr);
	return dskr;
}

//pakeicia esama direktorija
int task_chdir() {
	if (chdir("/tmp") == -1) {
		perror("chdir klaida");
		exit(1);
	}
	printf("Pakeistas darbo katalogas\n");
	return 0;
}

//grazina i buvusia direktorija naudojant seniau gauta deskriptoriu
int task_fchdir(int d) {
	if (fchdir(d) == -1) {
		perror("fchdir klaida");
		exit(1);
	}
	printf("Pereita i pradini kataloga\n");
	return 0;
}

int main ( int argc, char * argv[] ) {
	int d;

	task_getcwd();

	d = open_dir();

	task_chdir();

	task_getcwd();

	task_fchdir(d);

	close(d);

	task_getcwd();

	return 0;
}
