/* Aistis */
/* FileName: one.c */

#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int checkTheFile(const char *fileName);
#define FILE_SIZE (4 * 1024)
void handleError(const char *message);
void setCPULimit();
void mapFilesToMemory(const char *file1, const char *file2);

void handleError(const char *message) {
	perror(message);
	abort();
}

void setCPULimit() {
	struct rlimit rl;

	if (getrlimit(RLIMIT_CPU, &rl) == -1) {
		handleError("Nepavyko gauti esamu limitu\n");
	}

	printf("RLIMIT_CPU %ld (soft) %ld (hard)\n", rl.rlim_cur, rl.rlim_max);

	rl.rlim_cur = 5;
	rl.rlim_max = 6;

	if (setrlimit(RLIMIT_CPU, &rl) == -1) {
		handleError("Nepavyko nustatyti CPU limito\n");
	}

	printf("RLIMIT_CPU %ld (soft) %ld (hard)\n", rl.rlim_cur, rl.rlim_max);
}

void mapFilesToMemory(const char *file1, const char *file2) {
	int fd1 = open(file1, O_RDONLY);
	if (fd1 == -1) {
		handleError("Nepavyko atidaryti pirmo failo\n");
	}

	int fd2 = open(file2, O_RDWR);
	if (fd2 == -1) {
		handleError("Nepavyko atidaryti antro failo\n");
	}

	printf("dskr = %d\n", fd1);
	printf("dskr = %d\n", fd2);

	struct stat st1;
	if (fstat(fd1, &st1) == -1) {
		handleError("Nepavyko gauti pirmo failo dydzio\n");
	}

	struct stat st2;
	if (fstat(fd2, &st2) == -1) {
		handleError("Nepavyko gauti antro failo dydzio\n");
	}

	void *map1 = mmap(NULL, st1.st_size, PROT_READ, MAP_PRIVATE, fd1, 0);
	if (map1 == MAP_FAILED) {
		handleError("Nepavyko prijungti pirmo failo prie atminties\n");
	}

	void *map2 = mmap(NULL, st2.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);
        if (map2 == MAP_FAILED) {
                handleError("Nepavyko prijungti antro failo prie atminties\n");
        }
}

int checkTheFile(const char *fileName) {
	int dskr = open(fileName, O_CREAT | O_EXCL | O_WRONLY, 0644);
	printf("dskr = %d\n", dskr);

	if (dskr == -1) {
		if (errno == EEXIST) {
			printf("Toks failas jau egzistuoja\n");

			dskr = open(fileName, O_RDWR);
			if (dskr == -1) {
				handleError("Klaida atidarant faila\n");
			}

			struct stat st;
			if (fstat(dskr, &st) == -1) {
				handleError("Klaida gaunant failo info\n");
			}

			if (st.st_size == 0) {
				printf("Failas tuscias\n");
				close(dskr);
				return 0;
			}


			off_t position;
			if (st.st_size % 2 == 0){
				position = (st.st_size / 2) - 1;
			} else {
				position = st.st_size / 2;
			}

			printf("Dydis: %ld, vidurys: %ld\n", st.st_size, position);

			if (lseek(dskr, position, SEEK_SET) == -1) {
				handleError("Klaida perkeliant pozicija\n");
			}

			if (write(dskr, "S", 1) != 1) {
				handleError("Klaida rasant i faila\n");
			}

			printf("Baitas %ld pakeistas i simboli S\n", position);

			if (close(dskr) == -1) {
				handleError("Klaida uzdarant faila\n");
			}

			return 0;
		} else {
			handleError("Klaida kuriant faila\n");
		}
	}

	if (ftruncate(dskr, FILE_SIZE) == -1) {
		handleError("Klaida nustatant failo dydi\n");
	}

	if (close(dskr) == -1) {
		handleError("Close failed\n");
	} else {
		printf("closed\n");
	}

	return 0;
}

int main(int argc, char *argv[]){
        printf( "(C) Aistis Jakutonis, %s\n", __FILE__ );

        if (argc < 2 || argc > 3) {
                printf("Naudojimas:\n");
		printf("%s failas1 [failas2]\n", argv[0]);
                exit(1);
        }

	if (argc == 2) {
		printf("Nurodytas 1 argumentas: %s\n", argv[1]);
		checkTheFile(argv[1]);
	}

	if (argc == 3) {
		printf("Nurodyti 2 argumentai: %s %s\n", argv[1], argv[2]);
		setCPULimit();

		mapFilesToMemory(argv[1], argv[2]);

		printf("CPU time limit exceeded\n");
	}

        return 0;
}

