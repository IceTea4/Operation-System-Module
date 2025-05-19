/* Aistis Jakutonis IFF3/1 e8180 */
/* Failas: e8180_loginas_pathconf.c */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main ( int argc, char * argv[] ) {
	long name_max;
	const char *path;
	long path_max;

	if (argc != 2) {
		printf("Naudojimas:\n %s <katalogo_kelias>\n", argv[0]);
		exit(1);
	}

	path = argv[1];
	errno = 0;

	//maximalus failo vardo ilgis
	name_max = pathconf(path, _PC_NAME_MAX);

	//maksimalus kelio ilgis
	path_max = pathconf(path, _PC_PATH_MAX);

	if (name_max == -1) {
	        if (errno != 0) {
			perror("pathconf klaida");
			exit(1);
	        } else {
	        	printf("Parametras _PC_NAME_MAX, _PC_PATH_MAX siame kelyje nera apribotas.\n");
		}
    	} else {
    		printf("Maksimalus failo vardo ilgis kataloge '%s' yra: %ld simboliu\n", path, name_max);
		printf("Maximalaus kelio ilgis kataloge '%s' yra: %ld\n", path, path_max);
	}

	return 0;
}
