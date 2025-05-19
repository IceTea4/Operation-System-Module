/* Aistis Jakutonis IFF3/1 e8180 */
/* Failas: e8180_readdir01.c */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

int task_opendir();

//atidaryti direktorija ir ciklu eiti per kiekviena jos el.
int task_opendir() {
	DIR *dir;
	struct dirent *dp;

	if ((dir = opendir(".")) == NULL) {
		perror("Cannot open .");
		exit(1);
	}

	while ((dp = readdir (dir)) != NULL) {
		printf("Failo: %s, i-Node numeris: %lu\n", dp->d_name, dp->d_ino);
	}

	closedir(dir);
	return 0;
}

int main ( int argc, char * argv[] ) {
	task_opendir();

	return 0;
}
